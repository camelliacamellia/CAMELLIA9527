#include "threadpool.h"
#include<functional>
#include<thread>
#include<iostream>

const int TASK_MAX_THRESHHOLD = 1024; // 任务队列数量上限阈值

ThreadPool::ThreadPool()
	: initThreadSize_(0),
	taskSize_(0),
	taskQueMaxThreshhold_(TASK_MAX_THRESHHOLD),
	poolMode_(PoolMode::MOD_FIXED) {

}

// 线程池析构
ThreadPool::~ThreadPool()
{}

// 设置线程池模式
void ThreadPool::setMode(PoolMode mode)
{
	poolMode_ = mode;
}

// 设置task任务上限阈值
void ThreadPool::setTaskQueMaxThreshHold(int threshhold)
{
	taskQueMaxThreshhold_ = threshhold;
}



// 给线程池提交任务
Result ThreadPool::submitTask(std::shared_ptr<Task> sp)
{
	// 获取任务队列锁
	std::unique_lock<std::mutex> lock(taskQueMtx_);

	// 线程的通信  等待可以进入任务队列 lock是锁，第二个是等待时间，第三个是lambda表达式，表示等待条件
	if (!notFull_.wait_for(lock, std::chrono::seconds(1), [&]()->bool {return taskQue_.size() < (size_t)taskQueMaxThreshhold_; }))
	{
		// wait_for有返回值，如果返回true，表示条件满足，任务队列有空余空间，可以放入任务
		// 表示条件还是没有满足，任务队列已满
		std::cerr << "Task queue is full, task submission failed." << std::endl;
		return Result(sp, false);
	}
	// 如果有空余，就把任务放入任务队列
	taskQue_.emplace(sp);
	taskSize_++; // 任务数量加1

	// 因为放入了一个任务，所以任务队列不问空，在notEmpty上进行通知 让空闲线程去处理任务
	notEmpty_.notify_all();
	return Result(sp);
}

// 开启线程池
void ThreadPool::start(int initThreadSize)
{
	// 记录初始线程数量
	initThreadSize_ = initThreadSize;

	// 根据线程池模式创建线程
	for (int i = 0; i < initThreadSize_; i++)
	{
		auto ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this));
		threads_.emplace_back(std::move(ptr));		// 把左值转化为右值，使用左值报错
	}

	// 启动线程池中的线程
	for (int i = 0; i < initThreadSize_; i++)
	{
		threads_[i]->start();
	}
}

void ThreadPool::threadFunc()
{
	//std::cout << "Thread started:" << std::this_thread::get_id() << std::endl;
	//std::cout << "Thread end:" << std::this_thread::get_id() << std::endl;

	for (;;)
	{
		std::shared_ptr<Task> task; // 定义一个任务指针
		{
			// 获取任务队列锁
			std::unique_lock<std::mutex>lock(taskQueMtx_);

			std::cout << "tid:" << std::this_thread::get_id() << " 尝试获取任务..." << std::endl;

			// 等待notEmpty条件
			notEmpty_.wait(lock, [&]()->bool { return taskQue_.size() > 0; });

			std::cout << "tid:" << std::this_thread::get_id() << " 获取任务成功..." << std::endl;

			// 从任务队列中取出一个任务
			task = taskQue_.front(); // 获取任务队列的第一个任务
			taskQue_.pop(); // 从任务队列中移除这个任务
			taskSize_--; // 任务数量减1
			// 通知notFull条件，表示任务队列不满
			if (taskQue_.size() > 0)
			{
				notEmpty_.notify_all(); // 通知任务队列不空
			}
			notFull_.notify_all(); // 通知任务队列不满
		}


		// 当前线程负责执行这个任务
		if (task != nullptr)
		{
			// task->run(); // 执行任务
			task->exec();
		}

	}

}
// 线程构造函数
Thread::Thread(ThreadFunc func) :func_(func)
{}
// 线程析构函数
Thread::~Thread()
{}
// 线程方法实现
void Thread::start()
{
	// 创建一个线程来执行一个线程函数
	std::thread t(func_);
	t.detach(); // 分离线程，允许线程在后台运行
}

Task::Task() : result_(nullptr) // 初始化结果为nullptr
{}

void Task::exec()
{
	if (result_ != nullptr) // 如果结果不为空，说明任务已经执行过了，不需要重复执行
	{
		result_->setVal(run()); // 执行任务
	}
}
void Task::setResult(Result* res)
{
	result_ = res;
}

// Result方法的实现
Result::Result(std::shared_ptr<Task> task, bool isValid) :isValid_(isValid), task_(task)
{
	task_->setResult(this); // 设置任务的结果为当前Result对象
}

Any Result::get()
{
	if (!isValid_)
	{
		return "";
	}
	sem_.wait(); // 等待信号量，确保结果可以访问,task如果没有执行完，调用get会阻塞等待
	return std::move(any_);
}
void Result::setVal(Any any)
{
	// 存储task的返回值
	this->any_ = Any(std::move(any));
	sem_.post(); // 释放信号量，表示结果可以访问
}