#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <string>
#include "identity.h"
#include "patient.h"
#include "doctor.h"
#include "doctor_identity.h"
#include "globalFile.h"
#include <algorithm>


class The_Manager : public Identity
{
public:
	//默认构造
	The_Manager();

	//有参构造 管理员账号，密码
	The_Manager(string z_name, string z_pwd);

	//记录医生人数
	int m_DocNum;

	//医生数组之指针
	Doctor** m_DocArray;

	//记录患者人数
	int m_PatNum;

	//患者数组之指针
	Patient** m_PatArray;

	//判断医生文件是否为空的标志
	bool m_DFileIsEmpty;

	//判断病人文件是否为空标志
	bool m_PFileIsEmpty;

	//统计原文件中医生人数
	int get_DocNum();

	//初始化医生文件
	void init_Doc();

	//统计原文件中患者人数
	int get_PatNum();

	//初始化患者文件
	void init_Pat();

	//保存医生文件
	void D_save();

	//保存患者文件
	void P_save();

	//按照医生编号判断医生是否存在，若存在返回医生在数组中位置，不存在返回-1
	int DIsExist(int id);

	//按照患者编号判断患者是否存在，若存在返回患者在数组中位置，不存在返回-1
	int PIsExist(int id);

	//选择菜单  虚函数
	void opermenu();

	//展示医生查找操作菜单
	void showFindDoc();
	
	//展示统计病人数量操作菜单----第一级
	void showCalPatf();

	//展示统计病人数量操作菜单----第二级
	void showCalPats();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//医生信息基本操作菜单
	void showDocAct();

	//医生基本信息录入
	void add_Doc();

	//医生基本信息修改
	void Mod_Doc();

	//删除医生信息
	void Del_Doc();

	//患者挂号信息录入
	void add_Pat();

	//患者基本信息修改
	void Mod_Pat();

	//删除患者信息
	void Del_Pat();
	
	//患者挂号信息基本操作菜单
	void showPatAct();
	
	//医生信息查询
	void Find_Doc();

	//统计就诊病人数量
	void Cal_Pat();

	//初始化容器
	void initVector();

	//医生容器
	vector<Doctor_identity>vDoc;

	//检测添加医生账号重复 参数：（传入用户名name） 返回值（true代表有重复，false代表无重复）
	bool checkUsersRepeat(string name);

	//检测 添加/修改 医生用户时医生编号重复
	bool checkDoctorRepeat(int id);

	//检测 添加/修改 患者用户时患者编号重复
	bool checkPatientRepeat(int id);

	//析构函数
	~The_Manager();

};