#ifndef THREADPOOL_H
#define THREADPOOL_H

#include<vector>
#include<queue>
#include<memory>
#include<atomic>
#include<mutex>
#include<condition_variable>
#include<functional>


// Any���ͣ�
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


	//ʵ�ְ�Any������洢��������ȡ����
	template<typename T>
	T cast_()
	{
		// ��base_�ҵ���ָ��Derive���󣬴�����ȡ��data��Ա����
		Derive<T>* pd = dynamic_cast<Derive<T>>(base_.get());
		if (pd == nullptr)
		{
			throw "type is unmatch";
		}
		return pd->data_;
	}

private:
	// ��������
	class Base
	{
	public:
		virtual ~Base() = default;		//ʹ��Ĭ����������
	};

	// ������ģ�壬���ڴ洢�������͵�����
	template<typename T>
	class Derive : public Base
	{
	public:
		Derive(T data) :data_(data)
		{}
		T data_;
	};
};


// ����������
class Task {
public:
	virtual Any run() = 0; // ����ִ�з���
};


enum class PoolMode		// �̳߳�֧�ֵ�ģʽ
{
	MOD_FIXED,		// �̶��̳߳�
	MODE_CACHED,	// �߳�������̬����
};


class Thread {
public:
	using ThreadFunc = std::function<void()>;


	// �̹߳��캯��
	Thread(ThreadFunc func);
	// �߳���������
	~Thread();
	// �����߳�
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
		void run() override {			// ��д����ִ�з���
		// ����ִ���߼�
		std::cout << "Task is running." << std::endl;
	}
}

pool.submitTask(std::make_shated<MyTask>());

*/

class ThreadPool {
public:

	// �̳߳ع���
	ThreadPool();
	// �̳߳�����
	~ThreadPool();

	void setMode(PoolMode mode); // �����̳߳�ģʽ

	// ����task����������ֵ
	void setTaskQueMaxThreshHold(int threshhold);

	// ���̳߳��ύ����
	void submitTask(std::shared_ptr<Task>sp);

	// �����̳߳�
	void start(int initThreadSize = 4);

	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator = (const ThreadPool&) = delete;
private:
	std::vector<std::unique_ptr<Thread>>threads_;		// �߳��б�
	int initThreadSize_;	// ��ʼ�߳�����

	std::queue<std::shared_ptr<Task>>taskQue_;
	std::atomic_int taskSize_; //��������� 
	int taskQueMaxThreshhold_; //�����������������ֵ

	std::mutex taskQueMtx_; // ������л����� ���������̰߳�ȫ

	std::condition_variable notFull_; // ������в���
	std::condition_variable notEmpty_; // ������в���


	PoolMode poolMode_; // �̳߳�ģʽ

	void threadFunc(); // �̴߳�����
};


#endif // !THREADPOOL_H