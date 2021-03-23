#include "doctor.h"


//构造函数
Doctor::Doctor(int id, string name, int dep)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Dep = dep;
}

void Doctor::ShowInfo()
{
	cout << "医生编号： " << this->m_Id
		<< "\t医生姓名： " << this->m_Name
		<< "\t医生部门： " << this->getDepName() << endl;
}

//获取医生岗位名称
string Doctor::getDepName()
{
	if (this->m_Dep == 1) return("医务科");
	else if (this->m_Dep == 2) return("人事科");
	else return("医保办");
}

