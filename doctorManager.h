#pragma once             //防止头文件重复包含
#include <iostream>
using namespace std;
#include "doctor.h"
#include "case_history.h"
#include <fstream>
#include <cstdlib>
#include <string>
#define D_FILENAME "doctor.txt"
#define C_FILENAME "case_history.txt"

class DoctorManager
{
public:
	//构造函数
	DoctorManager();

	//展示菜单
	void D_Show_Menu();

	//退出功能
	void D_ExitSystem();

	//记录病历数
	int m_CaseNum;

	//病历数组之指针
	Casehistory ** m_CaseArray;

	//判断病历文件是否为空标志
	bool m_CFileIsEmpty;

	//按照患者病历编号判断患者病历是否存在，若存在返回患者病历在数组中位置，不存在返回-1
	int CIsExist(int id);

	//统计原文件中病历个数
	int get_CaseNum();

	//初始化病历文件
	void init_Case();

	//保存病历文件
	void C_save();

	//病历信息查询
	void Find_Case();

	//病历信息删除
	void Del_Case();

	//患者病历信息填写
	void add_Case();

	//统计就诊病人数量
	void cal_Pat();

	//析构函数
	~DoctorManager();
};