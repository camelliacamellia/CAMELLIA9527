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
	// β�巨 O(n)
	void inserttail(int val)
	{
		// �ҵ�β���
		Node* p = head;
		while (p->next != nullptr)
		{
			p = p->next;
		}
		Node* N = new Node(val);
		p->next = N;
		// ��������
		// �����½��
	}
	// ����ָ��
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
	// ����������ӵ���һ�������
	void ccc()
	{
		if (head == nullptr) return;
		Node* p = head;
		while (p->next != nullptr) {
			p = p->next;
		}
		p->next = head;  // β�ڵ�ָ��ͷ�ڵ㣨����head->next����
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
		cout << "��û�л�" << endl;
	else
		cout << "���л�" << endl;

	// ����������ӻ��ĺ���ʱ�������������������ע�ͣ���Ȼ�ᵼ�½��̿���
	S.ccc();

	if (S.kmzz())
		cout << "��û�л�" << endl;
	else
		cout << "���л�" << endl;
	return 0;
}