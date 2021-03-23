#include "patient.h"


//���캯��
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
	cout << "���߱�ţ� " << this->m_Id
		<< "\t���������� " << this->m_Name << endl;
	cout << "����ʱ�䣺 " << this->m_Year << "��" << this->m_Month << "��" << this->m_Day << "��"
		<< "\t���߿��ң� " << this->getDepName() << endl;
	cout << endl;
}



//��ȡ���߿�������
string Patient::getDepName()
{
	if (this->m_Dep == 1) return("�ڿ�");
	else if (this->m_Dep == 2) return("���");
	else if (this->m_Dep == 3) return("����");
	else return("����");
}

