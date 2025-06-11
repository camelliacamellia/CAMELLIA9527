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

	Any(const Any&) = delete;
	Any& operator = (const Any&) = delete;
	Any(Any&&) = default;
	Any& operator = (Any&&) = default;
	template<typename T>
	Any(T data) :base_(std::make_unique<Derive<T>>(data))
	{}


	//ʵ�ְ�Any������洢��������ȡ����
	template<typename T>
	T cast_()
	{
		// ��base_�ҵ���ָ��Derive���󣬴�����ȡ��data��Ա����
		Derive<T>* pd = dynamic_cast<Derive<T>*>(base_.get());
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
	std::unique_ptr<Base> base_; // �洢�����������ݵĻ���ָ��
};

// ʵ��һ���ź����࣬���ڿ�����Դ�ķ���
class Semaphore
{
public:
	Semaphore(int limit = 0) : resLimit_(0)
	{}
	~Semaphore() = default;

	// ��ȡһ���ź�����Դ
	void wait()
	{
		std::unique_lock<std::mutex>lock(mtx_); // ��ȡ������
		// �ȴ�����������ֱ���ź�������������0
		cond_.wait(lock, [&]()->bool { return resLimit_ > 0; });
		resLimit_--; // �ź�����������1
	}

	// ����һ���ź�����Դ
	void post()
	{
		std::unique_lock<std::mutex>lock(mtx_); // ��ȡ������
		resLimit_++; // �ź�����������1
		cond_.notify_all(); // ֪ͨ�����߳�
	}

private:
	std::mutex mtx_; // ������
	std::condition_variable cond_; // ��������
	int resLimit_; // �ź���������
};

class Task; // ǰ������Task��
// ʵ�ֽ����ύ���̳߳ص����񣬲����ؽ������
class Result
{
public:
	Result(std::shared_ptr<Task> task, bool isValid = true);


	void setVal(Any any);
	// ��ȡ����ִ�н��
	Any get();

	~Result() = default;
private:
	Any any_; // �洢����ִ�н����Any����
	Semaphore sem_; // �ź��������ڿ��ƽ���ķ���
	std::shared_ptr<Task> task_; // ����ָ�룬���ڹ�������ͽ��
	std::atomic_bool isValid_; // ����Ƿ���Ч�ı�־λ

};



// ����������
class Task {
public:
	Task();
	~Task() = default;
	void exec();

	void setResult(Result* res);// ��������ִ�н��
	virtual Any run() = 0; // ����ִ�з���
private:
	Result* result_; // ����ִ�н��
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
	Result submitTask(std::shared_ptr<Task>sp);

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