#ifndef THREADPOOL_H
#define THREADPOOL_H

#include<vector>
#include<queue>
#include<memory>
#include<atomic>
#include<mutex>
#include<condition_variable>
#include<functional>


// Any类型：
class Any
{
public:
	Any() = default;
	~Any() = default;

	Any(const Any&) = default;
	Any& operator = (const Any&) = delete;
	Any(Any&&) = default;
	Any& operator = (Any&&) = delete;
	template<typename T>
	Any(T data) :base_(std::make_unique<Derive<T>>(data))
	{}


	//实现把Any对象里存储的数据提取出来
	template<typename T>
	T cast_()
	{
		// 从base_找到所指的Derive对象，从里面取出data成员变量
		Derive<T>* pd = dynamic_cast<Derive<T>>(base_.get());
		if (pd == nullptr)
		{
			throw "type is unmatch";
		}
		return pd->data_;
	}

private:
	// 基类类型
	class Base
	{
	public:
		virtual ~Base() = default;		//使用默认析构函数
	};

	// 派生类模板，用于存储任意类型的数据
	template<typename T>
	class Derive : public Base
	{
	public:
		Derive(T data) :data_(data)
		{}
		T data_;
	};
};


// 任务抽象基类
class Task {
public:
	virtual Any run() = 0; // 任务执行方法
};


enum class PoolMode		// 线程池支持的模式
{
	MOD_FIXED,		// 固定线程池
	MODE_CACHED,	// 线程数量动态增长
};


class Thread {
public:
	using ThreadFunc = std::function<void()>;


	// 线程构造函数
	Thread(ThreadFunc func);
	// 线程析构函数
	~Thread();
	// 启动线程
	void start();
private:
	ThreadFunc func_;
};

/*
example usage:
ThreadPool pool;
pool.start(4);

class MyTask : public Task
{
	public:
		void run() override {			// 重写任务执行方法
		// 任务执行逻辑
		std::cout << "Task is running." << std::endl;
	}
}

pool.submitTask(std::make_shated<MyTask>());

*/

class ThreadPool {
public:

	// 线程池构造
	ThreadPool();
	// 线程池析构
	~ThreadPool();

	void setMode(PoolMode mode); // 设置线程池模式

	// 设置task任务上限阈值
	void setTaskQueMaxThreshHold(int threshhold);

	// 给线程池提交任务
	void submitTask(std::shared_ptr<Task>sp);

	// 开启线程池
	void start(int initThreadSize = 4);

	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator = (const ThreadPool&) = delete;
private:
	std::vector<std::unique_ptr<Thread>>threads_;		// 线程列表
	int initThreadSize_;	// 初始线程数量

	std::queue<std::shared_ptr<Task>>taskQue_;
	std::atomic_int taskSize_; //任务的数量 
	int taskQueMaxThreshhold_; //任务队列数量上限阈值

	std::mutex taskQueMtx_; // 任务队列互斥锁 保护队列线程安全

	std::condition_variable notFull_; // 任务队列不满
	std::condition_variable notEmpty_; // 任务队列不空


	PoolMode poolMode_; // 线程池模式

	void threadFunc(); // 线程处理方法
};


#endif // !THREADPOOL_H