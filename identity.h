#pragma once
#include <iostream>
using namespace std;

//身份抽象类
class Identity
{
public:
	//操作菜单
	virtual void opermenu() = 0;

	string i_Name;
	string i_Pwd;
};