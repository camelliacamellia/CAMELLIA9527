#include "threadpool.h"
#include<functional>
#include<thread>
#include<iostream>

const int TASK_MAX_THRESHHOLD = 1024; // �����������������ֵ

ThreadPool::ThreadPool()
	: initThreadSize_(0),
	taskSize_(0),
	taskQueMaxThreshhold_(TASK_MAX_THRESHHOLD),
	poolMode_(PoolMode::MOD_FIXED) {

}

// �̳߳�����
ThreadPool::~ThreadPool()
{}

// �����̳߳�ģʽ
void ThreadPool::setMode(PoolMode mode)
{
	poolMode_ = mode;
}

// ����task����������ֵ
void ThreadPool::setTaskQueMaxThreshHold(int threshhold)
{
	taskQueMaxThreshhold_ = threshhold;
}



// ���̳߳��ύ����
Result ThreadPool::submitTask(std::shared_ptr<Task> sp)
{
	// ��ȡ���������
	std::unique_lock<std::mutex> lock(taskQueMtx_);

	// �̵߳�ͨ��  �ȴ����Խ���������� lock�������ڶ����ǵȴ�ʱ�䣬��������lambda���ʽ����ʾ�ȴ�����
	if (!notFull_.wait_for(lock, std::chrono::seconds(1), [&]()->bool {return taskQue_.size() < (size_t)taskQueMaxThreshhold_; }))
	{
		// wait_for�з���ֵ���������true����ʾ�������㣬��������п���ռ䣬���Է�������
		// ��ʾ��������û�����㣬�����������
		std::cerr << "Task queue is full, task submission failed." << std::endl;
		return Result(sp, false);
	}
	// ����п��࣬�Ͱ���������������
	taskQue_.emplace(sp);
	taskSize_++; // ����������1

	// ��Ϊ������һ����������������в��ʿգ���notEmpty�Ͻ���֪ͨ �ÿ����߳�ȥ��������
	notEmpty_.notify_all();
	return Result(sp);
}

// �����̳߳�
void ThreadPool::start(int initThreadSize)
{
	// ��¼��ʼ�߳�����
	initThreadSize_ = initThreadSize;

	// �����̳߳�ģʽ�����߳�
	for (int i = 0; i < initThreadSize_; i++)
	{
		auto ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this));
		threads_.emplace_back(std::move(ptr));		// ����ֵת��Ϊ��ֵ��ʹ����ֵ����
	}

	// �����̳߳��е��߳�
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
		std::shared_ptr<Task> task; // ����һ������ָ��
		{
			// ��ȡ���������
			std::unique_lock<std::mutex>lock(taskQueMtx_);

			std::cout << "tid:" << std::this_thread::get_id() << " ���Ի�ȡ����..." << std::endl;

			// �ȴ�notEmpty����
			notEmpty_.wait(lock, [&]()->bool { return taskQue_.size() > 0; });

			std::cout << "tid:" << std::this_thread::get_id() << " ��ȡ����ɹ�..." << std::endl;

			// �����������ȡ��һ������
			task = taskQue_.front(); // ��ȡ������еĵ�һ������
			taskQue_.pop(); // ������������Ƴ��������
			taskSize_--; // ����������1
			// ֪ͨnotFull��������ʾ������в���
			if (taskQue_.size() > 0)
			{
				notEmpty_.notify_all(); // ֪ͨ������в���
			}
			notFull_.notify_all(); // ֪ͨ������в���
		}


		// ��ǰ�̸߳���ִ���������
		if (task != nullptr)
		{
			// task->run(); // ִ������
			task->exec();
		}

	}

}
// �̹߳��캯��
Thread::Thread(ThreadFunc func) :func_(func)
{}
// �߳���������
Thread::~Thread()
{}
// �̷߳���ʵ��
void Thread::start()
{
	// ����һ���߳���ִ��һ���̺߳���
	std::thread t(func_);
	t.detach(); // �����̣߳������߳��ں�̨����
}

Task::Task() : result_(nullptr) // ��ʼ�����Ϊnullptr
{}

void Task::exec()
{
	if (result_ != nullptr) // ��������Ϊ�գ�˵�������Ѿ�ִ�й��ˣ�����Ҫ�ظ�ִ��
	{
		result_->setVal(run()); // ִ������
	}
}
void Task::setResult(Result* res)
{
	result_ = res;
}

// Result������ʵ��
Result::Result(std::shared_ptr<Task> task, bool isValid) :isValid_(isValid), task_(task)
{
	task_->setResult(this); // ��������Ľ��Ϊ��ǰResult����
}

Any Result::get()
{
	if (!isValid_)
	{
		return "";
	}
	sem_.wait(); // �ȴ��ź�����ȷ��������Է���,task���û��ִ���꣬����get�������ȴ�
	return std::move(any_);
}
void Result::setVal(Any any)
{
	// �洢task�ķ���ֵ
	this->any_ = Any(std::move(any));
	sem_.post(); // �ͷ��ź�������ʾ������Է���
}