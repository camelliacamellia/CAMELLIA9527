#include<iostream>
using namespace std;

struct Node
{
	Node(int data_ = 0) :data(data_), next(nullptr) {};
	int data;
	Node* next;
};
class Clink
{
public:
	Clink()
	{
		head = new Node();
		head->next = nullptr;
	}
	~Clink()
	{
		//Node* q = head->next;
		//while (q != nullptr)
		//{
		//	delete head;
		//	head = q;
		//	q = q->next;
		//}
	}
	// 尾插法 O(n)
	void inserttail(int val)
	{
		// 找到尾结点
		Node* p = head;
		while (p->next != nullptr)
		{
			p = p->next;
		}
		Node* N = new Node(val);
		p->next = N;
		// 插入数据
		// 生成新结点
	}
	// 快慢指针
	bool kmzz()
	{
		Node* p = head;
		Node* q = head;
		while (p != nullptr && p->next != nullptr)
		{
			p = p->next->next;
			q = q->next;
			if (p == q)
			{
				return false;
			}
		}
		return true;
	}
	// 把最后结点链接到第一个结点上
	void ccc()
	{
		if (head == nullptr) return;
		Node* p = head;
		while (p->next != nullptr) {
			p = p->next;
		}
		p->next = head;  // 尾节点指向头节点（不是head->next！）
	}
private:
	Node* head;
};

int main()
{
	Clink S;
	S.inserttail(778);
	S.inserttail(778);
	S.inserttail(778);
	S.inserttail(778);
	S.inserttail(778);
	S.inserttail(778);
	S.inserttail(778);
	S.inserttail(778);
	S.inserttail(778);
	S.inserttail(778);
	S.inserttail(778);

	if (S.kmzz())
		cout << "这没有环" << endl;
	else
		cout << "这有环" << endl;

	// 调用这个链接环的函数时必须把析构函数的内容注释，不然会导致进程卡死
	S.ccc();

	if (S.kmzz())
		cout << "这没有环" << endl;
	else
		cout << "这有环" << endl;
	return 0;
}