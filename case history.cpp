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
	cout << "���������� " << this->m_Id
		<< "\t��������: " << this->m_Name
		<< "\t���߿��ң� " << this->getDepName() << endl;
	cout << "���߲��飺 " << this->m_Situation << endl;
	cout << "ҽ�����飺 " << this->m_Advice << endl;
}

//��ȡ�������߿�������
string Casehistory::getDepName()
{
	if (this->m_Dep == 1) return("�ڿ�");
	else if (this->m_Dep == 2) return("���");
	else if (this->m_Dep == 3) return("����");
	else return("����");
}
