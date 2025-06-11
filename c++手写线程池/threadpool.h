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

	Any(const Any&) = delete;
	Any& operator = (const Any&) = delete;
	Any(Any&&) = default;
	Any& operator = (Any&&) = default;
	template<typename T>
	Any(T data) :base_(std::make_unique<Derive<T>>(data))
	{}


	//实现把Any对象里存储的数据提取出来
	template<typename T>
	T cast_()
	{
		// 从base_找到所指的Derive对象，从里面取出data成员变量
		Derive<T>* pd = dynamic_cast<Derive<T>*>(base_.get());
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
	std::unique_ptr<Base> base_; // 存储任意类型数据的基类指针
};

// 实现一个信号量类，用于控制资源的访问
class Semaphore
{
public:
	Semaphore(int limit = 0) : resLimit_(0)
	{}
	~Semaphore() = default;

	// 获取一个信号量资源
	void wait()
	{
		std::unique_lock<std::mutex>lock(mtx_); // 获取互斥锁
		// 等待条件变量，直到信号量计数器大于0
		cond_.wait(lock, [&]()->bool { return resLimit_ > 0; });
		resLimit_--; // 信号量计数器减1
	}

	// 增加一个信号量资源
	void post()
	{
		std::unique_lock<std::mutex>lock(mtx_); // 获取互斥锁
		resLimit_++; // 信号量计数器加1
		cond_.notify_all(); // 通知其他线程
	}

private:
	std::mutex mtx_; // 互斥锁
	std::condition_variable cond_; // 条件变量
	int resLimit_; // 信号量计数器
};

class Task; // 前向声明Task类
// 实现接收提交到线程池的任务，并返回结果的类
class Result
{
public:
	Result(std::shared_ptr<Task> task, bool isValid = true);


	void setVal(Any any);
	// 获取任务执行结果
	Any get();

	~Result() = default;
private:
	Any any_; // 存储任务执行结果的Any类型
	Semaphore sem_; // 信号量，用于控制结果的访问
	std::shared_ptr<Task> task_; // 任务指针，用于关联任务和结果
	std::atomic_bool isValid_; // 结果是否有效的标志位

};



// 任务抽象基类
class Task {
public:
	Task();
	~Task() = default;
	void exec();

	void setResult(Result* res);// 设置任务执行结果
	virtual Any run() = 0; // 任务执行方法
private:
	Result* result_; // 任务执行结果
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
	Result submitTask(std::shared_ptr<Task>sp);

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