
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
			cout << "图鉴连接�?....." << endl;
		}
		else
		{
			cout << "MYSQL connection is error!!!" << endl;
		};
		mysql_query(&mysql, "set names gbk");
		system("cls");
	}

	bool seek(const char* sql, int n)		//查找函数
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
			cout << "查找错误！！�? << endl;
		}
		if (ok)
		{
			cout << "未找到英雄，请核对后查找......" << endl;
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
			cout << "插入成功" << endl;
			return true;
		}
		else
		{
			cout << "错误！！�? << mysql_error(&mysql) << endl;
			return false;
		}
	}

	bool ALTER(const char* sql)
	{
		int res = mysql_query(&mysql, sql);
		if (!res)
		{
			cout << "修改成功......" << endl;
			return true;
		}
		else
		{
			cout << "修改错误......" << mysql_error(&mysql) << endl;
			return false;
		}
	}


	bool CANCLE(const char* sql)
	{
		int res = mysql_query(&mysql, sql);
		if (!res)
		{
			cout << "删除成功......" << endl;
			return true;
		}
		else
		{
			cout << "删除错误: " << mysql_error(&mysql) << endl;  // 输出具体错误信息
			return false;
		}
	}

	int FROM()
	{
		cout << left << setw(10) << " 编号 ";
		cout << left << setw(10) << " 姓名 ";
		cout << left << setw(10) << " 种族 ";
		cout << left << setw(10) << " 身高 ";
		cout << left << setw(10) << " 能量 ";
		cout << left << setw(10) << " 城市 ";
		cout << left << setw(10) << " 势力 ";
		cout << left << setw(10) << " 身份 ";
		cout << left << setw(10) << " 介绍 ";
		return 0;
	}


	void base_seek()			// 查找基本信息
	{
		system("cls");
		string STR;
		string s;
		const char* sql;
		int num = 0;
		STR = "SELECT * FROM character_table WHERE number > 0 ";
		cout << "选择按什么查�?....." << endl;
		cout << "�?角色 ---------> 1" << endl;
		cout << "�?种族 ---------> 2" << endl;
		cout << "�?能量 ---------> 3" << endl;
		cout << "�?城市 ---------> 4" << endl;
		cout << "�?势力 ---------> 5" << endl;
		cout << "�?身份 ---------> 6" << endl;
		cout << "合并 查找 -------> 7" << endl;
		cin >> num;
		Sleep(1000);
		system("cls");
		switch (num)
		{
		case 1:
			cout << "输入你要查找�?名字 :" << endl;
			cin >> s;
			STR += "and name like '%" + s + "%' ";
			break;
		case 2:
			cout << "输入你要查找�?种族 :" << endl;
			cin >> s;
			STR += "and race like '%" + s + "%' ";
			break;
		case 3:
			cout << "输入你要查找�?能量 :" << endl;
			cin >> s;
			STR += "and energy like '%" + s + "%' ";
			break;
		case 4:
			cout << "输入你要查找�?城市 :" << endl;
			cin >> s;
			STR += "and city like '%" + s + "%' ";
			break;
		case 5:
			cout << "输入你要查找�?势力 :" << endl;
			cin >> s;
			STR += "and force like '%" + s + "%' ";
			break;
		case 6:
			cout << "输入你要查找�?身份 :" << endl;
			cin >> s;
			STR += "and rank like '%" + s + "%' ";
		case 7:
		{
			cout << "合并查找中，输入你需要的类型......" << endl;
			cout << "输入你要查找�?种族 或输�?NULL 代表无关:" << endl;
			cin >> s;
			if (s != "NULL")
				STR += "and race like '%" + s + "%' ";

			cout << "输入你要查找�?能量 或输�?NULL 代表无关:" << endl;
			cin >> s;
			if (s != "NULL")
				STR += "and energy like '%" + s + "%' ";

			cout << "输入你要查找�?城市 或输�?NULL 代表无关:" << endl;
			cin >> s;
			if (s != "NULL")
				STR += "and city like '%" + s + "%' ";

			cout << "输入你要查找�?势力 或输�?NULL 代表无关:" << endl;
			cin >> s;
			if (s != "NULL")
				STR += "and `force` like '%" + s + "%' ";

			cout << "输入你要查找�?身份 或输�?NULL 代表无关:" << endl;
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

	void base_insert()			// 插入基本信息
	{
		system("cls");
		string STR;
		string s;
		const char* sql;
		string name, race, energy, city, force, rank, introduce;
		string height;
		cout << "输入名字:" << endl;
		cin >> name;
		if (name == "NULL")
		{
			cout << "无效�? << endl;
			cout << "退出插�?....." << endl;
			Sleep(2000);
			system("cls");
			return;
		}
		cout << "输入种族 �?NULL:" << endl;
		cin >> race;
		cout << "输入身高 �?0:" << endl;
		cin >> height;
		cout << "输入能量 �?NULL:" << endl;
		cin >> energy;
		cout << "输入城市 �?NULL:" << endl;
		cin >> city;
		cout << "输入势力 �?NULL:" << endl;
		cin >> force;
		cout << "输入身份 �?NULL:" << endl;
		cin >> rank;
		cout << "输入角色简�?�?NULL:" << endl;
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
	string escapeSQL(const string& input) {			// 防止 SQL注入 进行 简单加�?
		string output;
		output.reserve(input.length() * 2);  // 预分配空间提高效�?

		for (char c : input) {
			switch (c) {
			case '\'': output += "''"; break;  // 转义单引�?
			case '\\': output += "\\\\"; break; // 转义反斜�?
			case '\"': output += "\\\""; break; // 转义双引�?
			case '\0': output += "\\0"; break;  // 转义NULL字符
			case '\b': output += "\\b"; break;  // 转义退�?
			case '\n': output += "\\n"; break;  // 转义换行
			case '\r': output += "\\r"; break;  // 转义回车
			case '\t': output += "\\t"; break;  // 转义制表�?
			default: output += c;
			}
		}
		return output;
	}

	void RELATIONSHIP_SEEK()			// 查找关系
	{
		system("cls");
		string STR;
		const char* sql;
		string name;
		cout << "输入要查找的人物:" << endl;
		cin >> name;
		STR = "SELECT * FROM relationship_table WHERE character_name like '%"
			+ escapeSQL(name) + "%' or related_character_name like '%" + escapeSQL(name) + "%';";
		sql = STR.c_str();
		cout << left << setw(10) << " 编号 ";
		cout << left << setw(10) << " 姓名 ";
		cout << left << setw(10) << " 姓名 ";
		cout << left << setw(10) << " 关系 ";
		cout << left << setw(10) << " 介绍 ";
		seek(sql, 4);

		CLS();
	}

	void RELATIONSHIP_INSERT()			//插入关系
	{
		system("cls");
		string STR;
		string name1, name2, rela, s;
		const char* sql;
		cout << "输入 姓名:" << endl;
		cin >> name1;
		cout << "输入 姓名:" << endl;
		cin >> name2;
		cout << "输入 关系:" << endl;
		cin >> rela;
		cout << "输入 一段描�?" << endl;
		cin >> s;

		STR = "INSERT INTO relationship_table (character_name,related_character_name,relationship_type, description)\
				VALUES('" + escapeSQL(name1) + "', '" + escapeSQL(name2) + "', '" + escapeSQL(rela) + "', '" + escapeSQL(s) + "'); ";
		sql = STR.c_str();
		INSERT(sql);
		CLS();
	}

	void SKILLS_SEEK()					// 查找 技�?
	{
		system("cls");
		string STR;
		const char* sql;
		string name;
		cout << "输入要查找技能的角色:" << endl;
		cin >> name;
		STR = "SELECT * FROM skills_table WHERE character_name like '%" + escapeSQL(name) + "%'";
		sql = STR.c_str();
		seek(sql, 5);
		CLS();
	}

	void SKILLS_INSERT()				// 插入 技�?
	{
		system("cls");
		string STR;
		string name, caaracter_name;
		const char* sql;
		int n;
		cout << "输入需要加入的技能数:";
		cin >> n;
		cout << "输入要插入技能的角色:" << endl;
		cin >> name;
		string skill, skill_type, skill_introduction, mana;
		for (int i = 0; i < n; i++)
		{
			cout << "输入 技能名:";
			cin >> skill;
			cout << "输入 技能类�?";
			cin >> skill_type;
			cout << "输入 技能介�?";
			cin >> skill_introduction;
			cout << "输入 技能蓝�?";
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
				cout << "插入错误 ，角色不存在或数据库未连�?....." << endl;
				cout << "强制结束......" << endl;
				CLS();
				return;
			}
			else
			{
				cout << "修改保存�?....." << endl;
				CLS();
			}
		}
		CLS();

	}

	bool BASE_ALTER()							// 修改英雄
	{
		system("cls");
		string STR;
		string name, race, height, energy, city, force, rank, introduce;
		const char* sql;
		cout << "输入需要修改的英雄" << endl;
		cin >> name;
		cout << "输入种族 �?NULL:" << endl;
		cin >> race;
		cout << "输入身高 �?0:" << endl;
		cin >> height;
		cout << "输入能量 �?NULL:" << endl;
		cin >> energy;
		cout << "输入城市 �?NULL:" << endl;
		cin >> city;
		cout << "输入势力 �?NULL:" << endl;
		cin >> force;
		cout << "输入身份 �?NULL:" << endl;
		cin >> rank;
		cout << "输入角色简�?�?NULL:" << endl;
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

	void SKILLS_DELETE()					// 删除英雄技�?
	{
		system("cls");
		string STR;
		string name, name_skills;
		const char* sql;
		const char* sqll;
		cout << "输入要删�?技�?�?英雄:" << endl;
		cin >> name;
		STR = "SELECT * FROM skills_table WHERE character_name = '" + escapeSQL(name) + "'";
		sqll = STR.c_str();
		if (!seek(sqll, 5))
		{
			cout << "强制结束......" << endl;
			Sleep(3000);
			system("cls");
			return;
		}
		cout << "输入需要删除的技�?";
		cin >> name_skills;
		STR = "DELETE FROM skills_table WHERE character_name = '" + escapeSQL(name)
			+ "'and skill_name = '" + escapeSQL(name_skills) + "'; ";
		sql = STR.c_str();
		CANCLE(sql);
	}

	void RELATIONSHIP_DELETE()				// 删除英雄关系
	{
		system("cls");
		string STR;
		string character_name, related_character_name, YES;
		const char* sql;
		cout << "输入要删除关系的英雄:" << endl;
		cin >> character_name;
		cout << "输入被删除关系的英雄:" << endl;
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
			cout << "将要删除以上关系（Y/N�? << endl;
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
				cout << "已取消删除，退出删除中......" << endl;
				return;
			}
		}
	}

	void CHARACTER_DELETE()					// 删除英雄
	{
		system("cls");
		int num;

		string STR;
		string character_name, YES;
		const char* sql;
		cout << "输入要删除的英雄:" << endl;
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
			cout << "关于该英雄的所有信�?包括技能和关系�?都会被删除，你确定要这么操作�?Y/N)?" << endl;
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


bool SetConsoleFontSize(int fontSize = 30)			// 用于修改窗口字体大小
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
		cout << " 请选择以下 功能 中的一个或�?-1 退�? << endl;
		cout << "  所�?英雄 介绍 -------> 1" << endl;
		cout << "  英雄 介绍 ------------> 2" << endl;
		cout << "  英雄 关系�?----------> 3" << endl;
		cout << "  英雄 技能介�?--------> 4" << endl;
		cout << "  修改 英雄 信息--------> 5" << endl;
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
			cout << "修改英雄需要管理员权限，请输入密码验证身份(123456)" << endl;
			cin >> num;
			if (num != 123456)
			{
				cout << "验证错误，禁止删除角�?....." << endl;
				cout << "退出中......" << endl;
				Sleep(3000);
				system("cls");
				break;
			}
			else
			{
				M.CLS();
			}
			int num2;
			cout << "选择需要修改的信息" << endl;
			cout << " 添加 英雄  ----------------> 1" << endl;
			cout << " 添加 英雄 关系 ------------> 2" << endl;
			cout << " 添加 英雄 技�?------------> 3" << endl;
			cout << " 修改 英雄  ----------------> 4" << endl;
			cout << " 删除 英雄 技�?------------> 5" << endl;
			cout << " 删除 英雄 关系 ------------> 6" << endl;
			cout << " 删除 英雄 -----------------> 7" << endl;
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
					cout << "修改保存�?....." << endl;
					Sleep(3000);

					break;
				}
			}
		}
		break;
		default:
			cout << "图鉴关闭�?....." << endl;
			Sleep(3000);
			return 0;
		}
	}
	M.~MYSQL_WZRY();
	return 0;
}
