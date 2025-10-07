# Caffe U-Net 实现

这是一个使用 Caffe 框架实现的 U-Net 网络架构，U-Net 是一个用于图像分割的经典卷积神经网络。

## 文件说明

- **unet_train.prototxt**: U-Net 训练网络定义文件
- **unet_deploy.prototxt**: U-Net 部署网络定义文件（用于推理）
- **solver.prototxt**: 训练求解器配置文件

## 网络架构

U-Net 采用编码器-解码器结构：

### 编码器路径（收缩路径）
- **层1**: 2个3x3卷积 (64通道) + 2x2最大池化
- **层2**: 2个3x3卷积 (128通道) + 2x2最大池化
- **层3**: 2个3x3卷积 (256通道) + 2x2最大池化
- **层4**: 2个3x3卷积 (512通道) + 2x2最大池化

### 瓶颈层
- 2个3x3卷积 (1024通道)

### 解码器路径（扩张路径）
- **层1**: 2x2上采样 + 跳跃连接 + 2个3x3卷积 (512通道)
- **层2**: 2x2上采样 + 跳跃连接 + 2个3x3卷积 (256通道)
- **层3**: 2x2上采样 + 跳跃连接 + 2个3x3卷积 (128通道)
- **层4**: 2x2上采样 + 跳跃连接 + 2个3x3卷积 (64通道)

### 输出层
- 1x1卷积 (2通道，二分类，可根据任务修改)
- Softmax 激活

## 关键特性

1. **跳跃连接**: 编码器的特征图通过裁剪（Crop层）后与解码器特征图拼接，保留空间信息
2. **无填充卷积**: 使用 `pad: 0`，导致输出尺寸小于输入尺寸
3. **输入尺寸**: 572x572
4. **输出尺寸**: 388x388（由于无填充卷积造成的尺寸减小）

## 使用方法

### 1. 准备数据

首先需要准备训练和测试数据，并转换为 LMDB 格式：

```bash
# 创建 LMDB 数据库
# train_lmdb: 训练数据
# test_lmdb: 测试数据
```

### 2. 修改配置

根据您的任务修改以下参数：

#### 在 unet_train.prototxt 中：
- **输入通道数**: 如果使用RGB图像，需要修改输入通道
- **输出类别数**: 在最后的卷积层 `conv10` 中修改 `num_output` 参数
- **数据路径**: 修改 `data_param` 中的 `source` 路径
- **批次大小**: 修改 `batch_size`

#### 在 solver.prototxt 中：
- **学习率**: 修改 `base_lr`
- **最大迭代次数**: 修改 `max_iter`
- **GPU/CPU模式**: 修改 `solver_mode`

### 3. 训练模型

```bash
caffe train -solver solver.prototxt -gpu 0
```

或者使用 CPU：
```bash
caffe train -solver solver.prototxt
```

### 4. 从快照恢复训练

```bash
caffe train -solver solver.prototxt -snapshot unet_iter_5000.solverstate -gpu 0
```

### 5. 模型部署/推理

```bash
caffe test -model unet_deploy.prototxt -weights unet_iter_100000.caffemodel -gpu 0 -iterations 100
```

## 自定义修改建议

### 增加填充以保持尺寸
如果希望输出与输入尺寸一致，可以在卷积层中添加 `pad: 1`：

```
convolution_param {
    num_output: 64
    kernel_size: 3
    pad: 1  # 添加填充
}
```

### 修改为多类分割
修改最后一层的 `num_output` 为类别数：

```
layer {
  name: "conv10"
  type: "Convolution"
  bottom: "conv9_2"
  top: "conv10"
  convolution_param {
    num_output: 5  # 例如5类分割
    kernel_size: 1
  }
}
```

### 调整网络深度
可以增加或减少编码器/解码器的层数，但要确保：
- 每增加一层编码器，相应增加一层解码器
- 跳跃连接正确匹配对应层
- 裁剪偏移量正确计算

### 使用批归一化
在卷积层后添加 BatchNorm 层可以提高训练稳定性：

```
layer {
  name: "bn1_1"
  type: "BatchNorm"
  bottom: "conv1_1"
  top: "conv1_1"
}
```

## 性能优化

1. **数据增强**: 在训练时使用镜像、旋转、缩放等数据增强
2. **学习率调整**: 根据训练曲线调整学习率策略
3. **权重初始化**: 使用预训练模型初始化编码器部分
4. **损失函数**: 对于不平衡数据集，考虑使用加权损失

## 注意事项

1. U-Net 对内存要求较高，如果显存不足，可以：
   - 减小 batch_size
   - 减小输入图像尺寸
   - 减少通道数

2. 裁剪偏移量（crop offset）需要根据网络结构精确计算，否则会导致尺寸不匹配错误

3. 确保标签图像的尺寸与网络输出尺寸匹配（388x388）

## 参考

- U-Net 原论文: [U-Net: Convolutional Networks for Biomedical Image Segmentation](https://arxiv.org/abs/1505.04597)
- Caffe 官方文档: http://caffe.berkeleyvision.org/

## 常见问题

### Q: 维度不匹配错误
**A**: 检查裁剪层的偏移量设置，确保编码器特征图与解码器特征图尺寸匹配

### Q: 内存溢出
**A**: 减小 batch_size 或输入图像尺寸

### Q: 训练不收敛
**A**: 调整学习率，检查数据归一化，考虑使用批归一化层

### Q: 如何修改为RGB输入？
**A**: 在 unet_deploy.prototxt 的输入层中修改 `input_dim` 的第二个参数为3：
```
input_dim: 1    # batch size
input_dim: 3    # channels (RGB)
input_dim: 572  # height
input_dim: 572  # width
```

同时在 unet_train.prototxt 的数据层中确保数据是RGB格式。