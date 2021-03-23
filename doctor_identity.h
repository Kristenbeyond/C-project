#pragma once
using namespace std;
#include <fstream>
#include "identity.h"
#include "case_history.h"
#define C_FILENAME "case_history.txt"

class Doctor_identity : public Identity
{
public:
	//Ĭ�Ϲ��캯��
	Doctor_identity();

	//�вι��캯����ҽ���˺ţ����������룩
	Doctor_identity(string i_Dname, string i_Dpwd);

	//�˵�����  �麯��
	void opermenu();

	//������Ϣ���������˵�
	void showHCaseAct();
	
	//���߲�����Ϣ��д
	void add_Case();

	//������Ϣ��ѯ
	void Find_Case();

	//������Ϣɾ��
	void Del_Case();

	//���没���ļ�
	void C_save();

	//��¼������
	int m_CaseNum;

	//��������ָ֮��
	Casehistory** m_CaseArray;

	//ͳ��ԭ�ļ��в�������
	int get_CaseNum();

	//���ջ��߲�������жϻ��߲����Ƿ���ڣ������ڷ��ػ��߲�����������λ�ã������ڷ���-1
	int CIsExist(int id);

	//��ʼ�������ļ�
	void init_Case();

	//�жϲ����ļ��Ƿ�Ϊ�ձ�־
	bool m_CFileIsEmpty;

	//չʾ���߲������Ҳ˵�
	void showHCaseActSecond();

	//��� ��� �����ļ�ʱ��������ظ�
	bool checkCHistoryRepeat(int id);

	//��������
	~Doctor_identity();
};