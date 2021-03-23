//病历类头文件
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Casehistory
{
public:
	Casehistory(int id, string name, int dep, char situation[64], char advice[64]);

	void c_ShowInfo();

	string getDepName();

	int m_Id;
	string m_Name;
	int m_Dep;
	char m_Situation[64];
	char m_Advice[64];
};