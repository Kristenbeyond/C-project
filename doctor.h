#pragma once
#include <iostream>
#include <string>
using namespace std;

class Doctor
{
public:
	Doctor(int id, string name, int dep);

	void ShowInfo();

	string getDepName();

	int m_Id;
	string m_Name;
	int m_Dep;
};