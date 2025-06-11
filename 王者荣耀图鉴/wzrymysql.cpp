
#include<iostream>
#include<iomanip>
#include<winsock.h>
#include<mysql.h>
#include<cstring>
#include<stdlib.h>
using namespace std; 



class MYSQL_WZRY
{
private:
	MYSQL mysql;
	MYSQL_RES* result;
	MYSQL_ROW sql_row;
public:
	MYSQL_WZRY() :result(nullptr), sql_row(nullptr)
	{
		mysql_init(&mysql);
		if (mysql_real_connect(&mysql, "127.0.0.1", "root", "123456", "wzry", 3306, NULL, 0))
		{
			cout << "ͼ��������......" << endl;
		}
		else
		{
			cout << "MYSQL connection is error!!!" << endl;
		};
		mysql_query(&mysql, "set names gbk");
		system("cls");
	}

	bool seek(const char* sql, int n)		//���Һ���
	{
		int res = mysql_query(&mysql, sql);
		bool ok = true;
		if (!res)
		{
			result = mysql_store_result(&mysql);
			while (sql_row = mysql_fetch_row(result))
			{
				if (ok && n == 8)
					FROM();
				if (sql_row)
				{
					cout << endl;
					for (int i = 0; i <= n; i++)
					{
						ok = false;
						cout << left << setw(10) << sql_row[i];
					}
				}
			}
		}
		else
		{
			cout << "���Ҵ��󣡣���" << endl;
		}
		if (ok)
		{
			cout << "δ�ҵ�Ӣ�ۣ���˶Ժ����......" << endl;
			return false;
		}
		cout << endl;
		return true;
	}

	bool INSERT(const char* sql)
	{
		int res = mysql_query(&mysql, sql);
		if (!res)
		{
			cout << "����ɹ�" << endl;
			return true;
		}
		else
		{
			cout << "���󣡣���" << mysql_error(&mysql) << endl;
			return false;
		}
	}

	bool ALTER(const char* sql)
	{
		int res = mysql_query(&mysql, sql);
		if (!res)
		{
			cout << "�޸ĳɹ�......" << endl;
			return true;
		}
		else
		{
			cout << "�޸Ĵ���......" << mysql_error(&mysql) << endl;
			return false;
		}
	}


	bool CANCLE(const char* sql)
	{
		int res = mysql_query(&mysql, sql);
		if (!res)
		{
			cout << "ɾ���ɹ�......" << endl;
			return true;
		}
		else
		{
			cout << "ɾ������: " << mysql_error(&mysql) << endl;  // ������������Ϣ
			return false;
		}
	}

	int FROM()
	{
		cout << left << setw(10) << " ��� ";
		cout << left << setw(10) << " ���� ";
		cout << left << setw(10) << " ���� ";
		cout << left << setw(10) << " ��� ";
		cout << left << setw(10) << " ���� ";
		cout << left << setw(10) << " ���� ";
		cout << left << setw(10) << " ���� ";
		cout << left << setw(10) << " ��� ";
		cout << left << setw(10) << " ���� ";
		return 0;
	}


	void base_seek()			// ���һ�����Ϣ
	{
		system("cls");
		string STR;
		string s;
		const char* sql;
		int num = 0;
		STR = "SELECT * FROM character_table WHERE number > 0 ";
		cout << "ѡ��ʲô����......" << endl;
		cout << "�� ��ɫ ---------> 1" << endl;
		cout << "�� ���� ---------> 2" << endl;
		cout << "�� ���� ---------> 3" << endl;
		cout << "�� ���� ---------> 4" << endl;
		cout << "�� ���� ---------> 5" << endl;
		cout << "�� ��� ---------> 6" << endl;
		cout << "�ϲ� ���� -------> 7" << endl;
		cin >> num;
		Sleep(1000);
		system("cls");
		switch (num)
		{
		case 1:
			cout << "������Ҫ���ҵ� ���� :" << endl;
			cin >> s;
			STR += "and name like '%" + s + "%' ";
			break;
		case 2:
			cout << "������Ҫ���ҵ� ���� :" << endl;
			cin >> s;
			STR += "and race like '%" + s + "%' ";
			break;
		case 3:
			cout << "������Ҫ���ҵ� ���� :" << endl;
			cin >> s;
			STR += "and energy like '%" + s + "%' ";
			break;
		case 4:
			cout << "������Ҫ���ҵ� ���� :" << endl;
			cin >> s;
			STR += "and city like '%" + s + "%' ";
			break;
		case 5:
			cout << "������Ҫ���ҵ� ���� :" << endl;
			cin >> s;
			STR += "and force like '%" + s + "%' ";
			break;
		case 6:
			cout << "������Ҫ���ҵ� ��� :" << endl;
			cin >> s;
			STR += "and rank like '%" + s + "%' ";
		case 7:
		{
			cout << "�ϲ������У���������Ҫ������......" << endl;
			cout << "������Ҫ���ҵ� ���� ������ NULL �����޹�:" << endl;
			cin >> s;
			if (s != "NULL")
				STR += "and race like '%" + s + "%' ";

			cout << "������Ҫ���ҵ� ���� ������ NULL �����޹�:" << endl;
			cin >> s;
			if (s != "NULL")
				STR += "and energy like '%" + s + "%' ";

			cout << "������Ҫ���ҵ� ���� ������ NULL �����޹�:" << endl;
			cin >> s;
			if (s != "NULL")
				STR += "and city like '%" + s + "%' ";

			cout << "������Ҫ���ҵ� ���� ������ NULL �����޹�:" << endl;
			cin >> s;
			if (s != "NULL")
				STR += "and `force` like '%" + s + "%' ";

			cout << "������Ҫ���ҵ� ��� ������ NULL �����޹�:" << endl;
			cin >> s;
			if (s != "NULL")
				STR += "and `rank` like '%" + s + "%' ";
		}
		default:
			break;
		}
		sql = STR.c_str();
		seek(sql, 8);
		CLS();
	}

	void base_insert()			// ���������Ϣ
	{
		system("cls");
		string STR;
		string s;
		const char* sql;
		string name, race, energy, city, force, rank, introduce;
		string height;
		cout << "��������:" << endl;
		cin >> name;
		if (name == "NULL")
		{
			cout << "��Ч��" << endl;
			cout << "�˳�����......" << endl;
			Sleep(2000);
			system("cls");
			return;
		}
		cout << "�������� �� NULL:" << endl;
		cin >> race;
		cout << "������� �� 0:" << endl;
		cin >> height;
		cout << "�������� �� NULL:" << endl;
		cin >> energy;
		cout << "������� �� NULL:" << endl;
		cin >> city;
		cout << "�������� �� NULL:" << endl;
		cin >> force;
		cout << "������� �� NULL:" << endl;
		cin >> rank;
		cout << "�����ɫ��� �� NULL:" << endl;
		cin >> introduce;
		STR = "INSERT INTO character_table (name, race, height, energy, city, `force`, `rank`, introduce) "
			"VALUES('" + escapeSQL(name) + "', "
			"'" + escapeSQL(race) + "', "
			"'" + escapeSQL(height) + "', "
			"'" + escapeSQL(energy) + "', "
			"'" + escapeSQL(city) + "', "
			"'" + escapeSQL(force) + "', "
			"'" + escapeSQL(rank) + "', "
			"'" + escapeSQL(introduce) + "');";
		sql = STR.c_str();
		INSERT(sql);
		CLS();
	};
	string escapeSQL(const string& input) {			// ��ֹ SQLע�� ���� �򵥼���
		string output;
		output.reserve(input.length() * 2);  // Ԥ����ռ����Ч��

		for (char c : input) {
			switch (c) {
			case '\'': output += "''"; break;  // ת�嵥����
			case '\\': output += "\\\\"; break; // ת�巴б��
			case '\"': output += "\\\""; break; // ת��˫����
			case '\0': output += "\\0"; break;  // ת��NULL�ַ�
			case '\b': output += "\\b"; break;  // ת���˸�
			case '\n': output += "\\n"; break;  // ת�廻��
			case '\r': output += "\\r"; break;  // ת��س�
			case '\t': output += "\\t"; break;  // ת���Ʊ��
			default: output += c;
			}
		}
		return output;
	}

	void RELATIONSHIP_SEEK()			// ���ҹ�ϵ
	{
		system("cls");
		string STR;
		const char* sql;
		string name;
		cout << "����Ҫ���ҵ�����:" << endl;
		cin >> name;
		STR = "SELECT * FROM relationship_table WHERE character_name like '%"
			+ escapeSQL(name) + "%' or related_character_name like '%" + escapeSQL(name) + "%';";
		sql = STR.c_str();
		cout << left << setw(10) << " ��� ";
		cout << left << setw(10) << " ���� ";
		cout << left << setw(10) << " ���� ";
		cout << left << setw(10) << " ��ϵ ";
		cout << left << setw(10) << " ���� ";
		seek(sql, 4);

		CLS();
	}

	void RELATIONSHIP_INSERT()			//�����ϵ
	{
		system("cls");
		string STR;
		string name1, name2, rela, s;
		const char* sql;
		cout << "���� ����:" << endl;
		cin >> name1;
		cout << "���� ����:" << endl;
		cin >> name2;
		cout << "���� ��ϵ:" << endl;
		cin >> rela;
		cout << "���� һ������:" << endl;
		cin >> s;

		STR = "INSERT INTO relationship_table (character_name,related_character_name,relationship_type, description)\
				VALUES('" + escapeSQL(name1) + "', '" + escapeSQL(name2) + "', '" + escapeSQL(rela) + "', '" + escapeSQL(s) + "'); ";
		sql = STR.c_str();
		INSERT(sql);
		CLS();
	}

	void SKILLS_SEEK()					// ���� ����
	{
		system("cls");
		string STR;
		const char* sql;
		string name;
		cout << "����Ҫ���Ҽ��ܵĽ�ɫ:" << endl;
		cin >> name;
		STR = "SELECT * FROM skills_table WHERE character_name like '%" + escapeSQL(name) + "%'";
		sql = STR.c_str();
		seek(sql, 5);
		CLS();
	}

	void SKILLS_INSERT()				// ���� ����
	{
		system("cls");
		string STR;
		string name, caaracter_name;
		const char* sql;
		int n;
		cout << "������Ҫ����ļ�����:";
		cin >> n;
		cout << "����Ҫ���뼼�ܵĽ�ɫ:" << endl;
		cin >> name;
		string skill, skill_type, skill_introduction, mana;
		for (int i = 0; i < n; i++)
		{
			cout << "���� ������:";
			cin >> skill;
			cout << "���� ��������:";
			cin >> skill_type;
			cout << "���� ���ܽ���:";
			cin >> skill_introduction;
			cout << "���� ��������:";
			cin >> mana;
			STR = "INSERT INTO skills_table (character_name, skill_name, skill_type, skill_description, power_level)VALUES\
					('" + escapeSQL(name)
				+ "', '" + escapeSQL(skill)
				+ "', '" + escapeSQL(skill_type)
				+ "', '" + escapeSQL(skill_introduction)
				+ "', '" + escapeSQL(mana) + "')";
			sql = STR.c_str();
			if (!INSERT(sql))
			{
				cout << "������� ����ɫ�����ڻ����ݿ�δ����......" << endl;
				cout << "ǿ�ƽ���......" << endl;
				CLS();
				return;
			}
			else
			{
				cout << "�޸ı�����......" << endl;
				CLS();
			}
		}
		CLS();

	}

	bool BASE_ALTER()							// �޸�Ӣ��
	{
		system("cls");
		string STR;
		string name, race, height, energy, city, force, rank, introduce;
		const char* sql;
		cout << "������Ҫ�޸ĵ�Ӣ��" << endl;
		cin >> name;
		cout << "�������� �� NULL:" << endl;
		cin >> race;
		cout << "������� �� 0:" << endl;
		cin >> height;
		cout << "�������� �� NULL:" << endl;
		cin >> energy;
		cout << "������� �� NULL:" << endl;
		cin >> city;
		cout << "�������� �� NULL:" << endl;
		cin >> force;
		cout << "������� �� NULL:" << endl;
		cin >> rank;
		cout << "�����ɫ��� �� NULL:" << endl;
		cin >> introduce;
		STR = "UPDATE character_table SET race = '" + escapeSQL(race)
			+ "',height = '" + escapeSQL(height)
			+ "',energy = '" + escapeSQL(energy)
			+ "',city = '" + escapeSQL(city)
			+ "',`force` = '" + escapeSQL(force)
			+ "',`rank` = '" + escapeSQL(rank)
			+ "',introduce = '" + escapeSQL(introduce)
			+ "'  WHERE name = '" + escapeSQL(name) + "'; ";
		sql = STR.c_str();
		ALTER(sql);
		CLS();
		return true;
	}

	void SKILLS_DELETE()					// ɾ��Ӣ�ۼ���
	{
		system("cls");
		string STR;
		string name, name_skills;
		const char* sql;
		const char* sqll;
		cout << "����Ҫɾ�� ���� �� Ӣ��:" << endl;
		cin >> name;
		STR = "SELECT * FROM skills_table WHERE character_name = '" + escapeSQL(name) + "'";
		sqll = STR.c_str();
		if (!seek(sqll, 5))
		{
			cout << "ǿ�ƽ���......" << endl;
			Sleep(3000);
			system("cls");
			return;
		}
		cout << "������Ҫɾ���ļ���:";
		cin >> name_skills;
		STR = "DELETE FROM skills_table WHERE character_name = '" + escapeSQL(name)
			+ "'and skill_name = '" + escapeSQL(name_skills) + "'; ";
		sql = STR.c_str();
		CANCLE(sql);
	}

	void RELATIONSHIP_DELETE()				// ɾ��Ӣ�۹�ϵ
	{
		system("cls");
		string STR;
		string character_name, related_character_name, YES;
		const char* sql;
		cout << "����Ҫɾ����ϵ��Ӣ��:" << endl;
		cin >> character_name;
		cout << "���뱻ɾ����ϵ��Ӣ��:" << endl;
		cin >> related_character_name;

		STR = "SELECT * FROM relationship_table WHERE character_name = '"
			+ escapeSQL(character_name) + "' and related_character_name = '"
			+ escapeSQL(related_character_name) + "';";
		sql = STR.c_str();
		if (!seek(sql, 4))
		{
			Sleep(3000);
			system("cls");
			return;
		}
		else
		{
			cout << "��Ҫɾ�����Ϲ�ϵ��Y/N��" << endl;
			cin >> YES;
			if (YES == "Y" || YES == "y")
			{
				STR = "DELETE FROM relationship_table WHERE  character_name = '"
					+ escapeSQL(character_name) + "' and related_character_name = '"
					+ escapeSQL(related_character_name) + "';";
				sql = STR.c_str();
				CANCLE(sql);
			}
			else
			{
				cout << "��ȡ��ɾ�����˳�ɾ����......" << endl;
				return;
			}
		}
	}

	void CHARACTER_DELETE()					// ɾ��Ӣ��
	{
		system("cls");
		int num;

		string STR;
		string character_name, YES;
		const char* sql;
		cout << "����Ҫɾ����Ӣ��:" << endl;
		cin >> character_name;
		STR = "SELECT * FROM character_table WHERE name = '" + character_name + "'";
		sql = STR.c_str();
		if (!seek(sql, 8))
		{
			Sleep(2000);
			system("cls");
			return;
		}
		else
		{
			cout << "���ڸ�Ӣ�۵�������Ϣ(�������ܺ͹�ϵ��)���ᱻɾ������ȷ��Ҫ��ô������(Y/N)?" << endl;
			cin >> YES;
			if (YES == "Y" || YES == "y")
			{
				STR = "DELETE FROM relationship_table WHERE character_name = '"
					+ character_name + "' OR related_character_name = '"
					+ character_name + "'";
				sql = STR.c_str();
				CANCLE(sql);
				STR = "DELETE FROM skills_table WHERE character_name = '" + character_name + "'";
				sql = STR.c_str();
				CANCLE(sql);

				STR = "DELETE FROM character_table WHERE name = '" + character_name + "';";
				sql = STR.c_str();
				CANCLE(sql);
				Sleep(1000);
				CLS();
			}
		}
	}


	void CLS()
	{
		system("pause");
		system("cls");
	}


	~MYSQL_WZRY() {
		if (result != nullptr) {
			mysql_free_result(result);
			result = nullptr;
		}
		mysql_close(&mysql);
	}

};


bool SetConsoleFontSize(int fontSize = 30)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) return false;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return false;
	COORD originalBufferSize = csbi.dwSize;
	SMALL_RECT originalWindowSize = csbi.srWindow;

	CONSOLE_FONT_INFOEX fontInfo = { 0 };
	fontInfo.cbSize = sizeof(fontInfo);
	if (!GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) return false;
	fontInfo.dwFontSize.Y = fontSize;
	fontInfo.FontWeight = FW_NORMAL;
	if (!SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) return false;

	SetConsoleWindowInfo(hConsole, TRUE, &originalWindowSize);

	return true;
}
int main()
{
	SetConsoleFontSize(20);
	MYSQL_WZRY M;

	int num = 1;
	while (num)
	{
		cout << " ��ѡ������ ���� �е�һ���� -1 �˳�" << endl;
		cout << "  ���� Ӣ�� ���� -------> 1" << endl;
		cout << "  Ӣ�� ���� ------------> 2" << endl;
		cout << "  Ӣ�� ��ϵ�� ----------> 3" << endl;
		cout << "  Ӣ�� ���ܽ��� --------> 4" << endl;
		cout << "  �޸� Ӣ�� ��Ϣ--------> 5" << endl;
		cin >> num;
		Sleep(300);
		system("cls");
		switch (num)
		{
		case 1:
			M.seek("select * from character_table", 8);
			M.CLS();
			break;
		case 2:
			M.base_seek();
			break;
		case 3:
			M.RELATIONSHIP_SEEK();
			break;
		case 4:
			M.SKILLS_SEEK();
			break;
		case 5:
		{
			int num;
			cout << "�޸�Ӣ����Ҫ����ԱȨ�ޣ�������������֤���(123456)" << endl;
			cin >> num;
			if (num != 123456)
			{
				cout << "��֤���󣬽�ֹɾ����ɫ......" << endl;
				cout << "�˳���......" << endl;
				Sleep(3000);
				system("cls");
				break;
			}
			else
			{
				M.CLS();
			}
			int num2;
			cout << "ѡ����Ҫ�޸ĵ���Ϣ" << endl;
			cout << " ��� Ӣ��  ----------------> 1" << endl;
			cout << " ��� Ӣ�� ��ϵ ------------> 2" << endl;
			cout << " ��� Ӣ�� ���� ------------> 3" << endl;
			cout << " �޸� Ӣ��  ----------------> 4" << endl;
			cout << " ɾ�� Ӣ�� ���� ------------> 5" << endl;
			cout << " ɾ�� Ӣ�� ��ϵ ------------> 6" << endl;
			cout << " ɾ�� Ӣ�� -----------------> 7" << endl;
			cin >> num2;
			{
				switch (num2)
				{
				case 1:
					M.base_insert();
					break;
				case 2:
					M.RELATIONSHIP_INSERT();
					break;
				case 3:
					M.SKILLS_INSERT();
					break;
				case 4:
					M.BASE_ALTER();
					break;
				case 5:
					M.SKILLS_DELETE();
					break;
				case 6:
					M.RELATIONSHIP_DELETE();
					break;
				case 7:
					M.CHARACTER_DELETE();
					break;
				default:
					cout << "�޸ı�����......" << endl;
					Sleep(3000);

					break;
				}
			}
		}
		break;
		default:
			cout << "ͼ���ر���......" << endl;
			Sleep(3000);
			return 0;
		}
	}
	M.~MYSQL_WZRY();
	return 0;
}