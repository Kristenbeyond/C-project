#pragma once
#include <iostream>
#include <string>
using namespace std;


class Patient
{
public:
	Patient(int id, string name, int dep, int day, int month, int year);

	void ShowInfo();

	string getDepName();

	int m_Id;
	string m_Name;
	int m_Dep;
	int m_Day;
	int m_Month;
	int m_Year;
};