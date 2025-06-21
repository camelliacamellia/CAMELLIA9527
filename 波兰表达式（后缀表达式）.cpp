/*
中缀->后缀
遇到数字直接输出，到result
遇到符号：
	1.栈为空，直接入栈
	2.如果是'('，直接入栈
	3.让当前符号与栈顶符号进行优先级比较
		当前符号 > 栈顶符号 ，当前符号入栈 break
		当前符号 <= 栈顶符号 ， 栈顶符号出栈并输出到 result ，然后继续比较下一个栈顶符号优先级
			3.1、栈为空结束
			3.2、遇到')' 开始一直出栈，直到遇到'('结束
*/


// 判断在该出是否需要出栈
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