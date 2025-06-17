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
	// ����������ӵ���һ�������


	Node* head;

private:

	friend bool isLinkHasMerge(Node* S, Node* T);
	friend void ccc(Node* S, Node* T, int val);
};

// �Ѻ������������һλ���ӵ�ǰ������ĵ�valλ
void ccc(Node* S, Node* T, int val)
{
	Node* p = S;
	Node* q = T;
	while (q->next != nullptr)
	{
		q = q->next;
	}
	while (val--)
	{
		p = p->next;
	}
	q->next = p;
	return;
}

bool isLinkHasMerge(Node* S, Node* T)
{
	Node* p = S;
	Node* q = T;
	int cnt1 = 0;
	int cnt2 = 0;
	while (p != nullptr)
	{
		cnt1++;
		p = p->next;
	}
	while (q != nullptr)
	{
		cnt2++;
		q = q->next;
	}
	p = S;
	q = T;
	if (cnt1 > cnt2)
	{
		while (cnt1-- > cnt2)
		{
			p = p->next;
		}
	}
	else
	{
		while (cnt1 < cnt2--)
		{
			q = q->next;
		}
	}
	while (p != nullptr)
	{
		if (p == q)
		{
			return true;
		}
		p = p->next;
		q = q->next;
	}
	return false;
};

int main()
{
	Clink S;
	S.inserttail(778);
	S.inserttail(1778);
	S.inserttail(2778);
	S.inserttail(3778);
	S.inserttail(4778);
	S.inserttail(5778);
	S.inserttail(6778);
	S.inserttail(7778);
	S.inserttail(8778);
	S.inserttail(9778);
	S.inserttail(10778);

	Clink T;
	T.inserttail(452);
	T.inserttail(2452);
	T.inserttail(12452);
	T.inserttail(22452);
	T.inserttail(32452);
	T.inserttail(42452);
	T.inserttail(52452);
	T.inserttail(62452);
	T.inserttail(72452);
	T.inserttail(72452);
	T.inserttail(92452);

	if (isLinkHasMerge(S.head, T.head))
		cout << "�ཻ��......" << endl;
	else
		cout << "û���ཻ......" << endl;

	// ���øú������������ཻ����ʱ����ע�͵��������������������......
	ccc(S.head, T.head, 5);

	if (isLinkHasMerge(S.head, T.head))
		cout << "�ཻ��......" << endl;
	else
		cout << "û���ཻ......" << endl;

	return 0;
}