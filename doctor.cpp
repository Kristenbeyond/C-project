#include "doctor.h"


//���캯��
Doctor::Doctor(int id, string name, int dep)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Dep = dep;
}

void Doctor::ShowInfo()
{
	cout << "ҽ����ţ� " << this->m_Id
		<< "\tҽ�������� " << this->m_Name
		<< "\tҽ�����ţ� " << this->getDepName() << endl;
}

//��ȡҽ����λ����
string Doctor::getDepName()
{
	if (this->m_Dep == 1) return("ҽ���");
	else if (this->m_Dep == 2) return("���¿�");
	else return("ҽ����");
}

