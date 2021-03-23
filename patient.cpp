#include "patient.h"


//构造函数
Patient::Patient(int id, string name, int year, int month, int day, int dep)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Dep = dep;
	this->m_Year = year;
	this->m_Month = month;
	this->m_Day = day;
}

void Patient::ShowInfo()
{
	cout << "患者编号： " << this->m_Id
		<< "\t患者姓名： " << this->m_Name << endl;
	cout << "就诊时间： " << this->m_Year << "年" << this->m_Month << "月" << this->m_Day << "日"
		<< "\t患者科室： " << this->getDepName() << endl;
	cout << endl;
}



//获取患者科室名称
string Patient::getDepName()
{
	if (this->m_Dep == 1) return("内科");
	else if (this->m_Dep == 2) return("外科");
	else if (this->m_Dep == 3) return("妇科");
	else return("儿科");
}

