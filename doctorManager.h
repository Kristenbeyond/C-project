#pragma once             //��ֹͷ�ļ��ظ�����
#include <iostream>
using namespace std;
#include "doctor.h"
#include "case_history.h"
#include <fstream>
#include <cstdlib>
#include <string>
#define D_FILENAME "doctor.txt"
#define C_FILENAME "case_history.txt"

class DoctorManager
{
public:
	//���캯��
	DoctorManager();

	//չʾ�˵�
	void D_Show_Menu();

	//�˳�����
	void D_ExitSystem();

	//��¼������
	int m_CaseNum;

	//��������ָ֮��
	Casehistory ** m_CaseArray;

	//�жϲ����ļ��Ƿ�Ϊ�ձ�־
	bool m_CFileIsEmpty;

	//���ջ��߲�������жϻ��߲����Ƿ���ڣ������ڷ��ػ��߲�����������λ�ã������ڷ���-1
	int CIsExist(int id);

	//ͳ��ԭ�ļ��в�������
	int get_CaseNum();

	//��ʼ�������ļ�
	void init_Case();

	//���没���ļ�
	void C_save();

	//������Ϣ��ѯ
	void Find_Case();

	//������Ϣɾ��
	void Del_Case();

	//���߲�����Ϣ��д
	void add_Case();

	//ͳ�ƾ��ﲡ������
	void cal_Pat();

	//��������
	~DoctorManager();
};