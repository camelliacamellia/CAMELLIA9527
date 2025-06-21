/*
��׺->��׺
��������ֱ���������result
�������ţ�
	1.ջΪ�գ�ֱ����ջ
	2.�����'('��ֱ����ջ
	3.�õ�ǰ������ջ�����Ž������ȼ��Ƚ�
		��ǰ���� > ջ������ ����ǰ������ջ break
		��ǰ���� <= ջ������ �� ջ�����ų�ջ������� result ��Ȼ������Ƚ���һ��ջ���������ȼ�
			3.1��ջΪ�ս���
			3.2������')' ��ʼһֱ��ջ��ֱ������'('����
*/


// �ж��ڸó��Ƿ���Ҫ��ջ
bool Priority(char ch, char topch)
{
	if ((ch == '*' || ch == '/') && (topch == '+' || topch == '-'))
		return true;
	if (topch == ')')
		return false;
	if (topch == '(' && ch != ')')
		return true;

	return false;
}


string MiddleToEndExpr(string expr)
{
	string result;
	stack<char>s;
	for (char ch : expr)
	{
		if (ch >= '0' && ch <= '9')
			result.push_back(ch);
		else
		{
			while (true)
			{
				if (s.empty() || ch == '(')
				{
					s.push(ch);
					break;
				}
				char topch = s.top();
				if (Priority(ch, topch))
				{
					s.push(ch);
					break;
				}
				else
				{
					s.pop();
					if (topch == '(')
						break;
					result.push_back(topch);
				}
			}
		}
	}
	while (!s.empty())
	{
		result.push_back(s.top());
		s.pop();
	}
	return result;
}