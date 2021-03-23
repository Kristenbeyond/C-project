#include "case_history.h"

Casehistory::Casehistory(int id, string name, int dep, char situation[64], char advice[64])
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Dep = dep;
	strcpy_s(this->m_Situation, situation);
	strcpy_s(this->m_Advice, advice);
}

void Casehistory::c_ShowInfo()
{
	cout << "患者姓名： " << this->m_Id
		<< "\t患者姓名: " << this->m_Name
		<< "\t患者科室： " << this->getDepName() << endl;
	cout << "患者病情： " << this->m_Situation << endl;
	cout << "医生建议： " << this->m_Advice << endl;
}

//获取病历患者科室名称
string Casehistory::getDepName()
{
	if (this->m_Dep == 1) return("内科");
	else if (this->m_Dep == 2) return("外科");
	else if (this->m_Dep == 3) return("妇科");
	else return("儿科");
}
