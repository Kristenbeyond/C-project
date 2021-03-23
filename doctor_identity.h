#pragma once
using namespace std;
#include <fstream>
#include "identity.h"
#include "case_history.h"
#define C_FILENAME "case_history.txt"

class Doctor_identity : public Identity
{
public:
	//默认构造函数
	Doctor_identity();

	//有参构造函数（医生账号，姓名，密码）
	Doctor_identity(string i_Dname, string i_Dpwd);

	//菜单界面  虚函数
	void opermenu();

	//病历信息基本操作菜单
	void showHCaseAct();
	
	//患者病历信息填写
	void add_Case();

	//病历信息查询
	void Find_Case();

	//病历信息删除
	void Del_Case();

	//保存病历文件
	void C_save();

	//记录病历数
	int m_CaseNum;

	//病历数组之指针
	Casehistory** m_CaseArray;

	//统计原文件中病历个数
	int get_CaseNum();

	//按照患者病历编号判断患者病历是否存在，若存在返回患者病历在数组中位置，不存在返回-1
	int CIsExist(int id);

	//初始化病历文件
	void init_Case();

	//判断病历文件是否为空标志
	bool m_CFileIsEmpty;

	//展示患者病历查找菜单
	void showHCaseActSecond();

	//检测 添加 病历文件时病历编号重复
	bool checkCHistoryRepeat(int id);

	//析构函数
	~Doctor_identity();
};