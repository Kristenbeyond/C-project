#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <string>
#include "identity.h"
#include "patient.h"
#include "doctor.h"
#include "doctor_identity.h"
#include "globalFile.h"
#include <algorithm>


class The_Manager : public Identity
{
public:
	//Ĭ�Ϲ���
	The_Manager();

	//�вι��� ����Ա�˺ţ�����
	The_Manager(string z_name, string z_pwd);

	//��¼ҽ������
	int m_DocNum;

	//ҽ������ָ֮��
	Doctor** m_DocArray;

	//��¼��������
	int m_PatNum;

	//��������ָ֮��
	Patient** m_PatArray;

	//�ж�ҽ���ļ��Ƿ�Ϊ�յı�־
	bool m_DFileIsEmpty;

	//�жϲ����ļ��Ƿ�Ϊ�ձ�־
	bool m_PFileIsEmpty;

	//ͳ��ԭ�ļ���ҽ������
	int get_DocNum();

	//��ʼ��ҽ���ļ�
	void init_Doc();

	//ͳ��ԭ�ļ��л�������
	int get_PatNum();

	//��ʼ�������ļ�
	void init_Pat();

	//����ҽ���ļ�
	void D_save();

	//���滼���ļ�
	void P_save();

	//����ҽ������ж�ҽ���Ƿ���ڣ������ڷ���ҽ����������λ�ã������ڷ���-1
	int DIsExist(int id);

	//���ջ��߱���жϻ����Ƿ���ڣ������ڷ��ػ�����������λ�ã������ڷ���-1
	int PIsExist(int id);

	//ѡ��˵�  �麯��
	void opermenu();

	//չʾҽ�����Ҳ����˵�
	void showFindDoc();
	
	//չʾͳ�Ʋ������������˵�----��һ��
	void showCalPatf();

	//չʾͳ�Ʋ������������˵�----�ڶ���
	void showCalPats();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//ҽ����Ϣ���������˵�
	void showDocAct();

	//ҽ��������Ϣ¼��
	void add_Doc();

	//ҽ��������Ϣ�޸�
	void Mod_Doc();

	//ɾ��ҽ����Ϣ
	void Del_Doc();

	//���߹Һ���Ϣ¼��
	void add_Pat();

	//���߻�����Ϣ�޸�
	void Mod_Pat();

	//ɾ��������Ϣ
	void Del_Pat();
	
	//���߹Һ���Ϣ���������˵�
	void showPatAct();
	
	//ҽ����Ϣ��ѯ
	void Find_Doc();

	//ͳ�ƾ��ﲡ������
	void Cal_Pat();

	//��ʼ������
	void initVector();

	//ҽ������
	vector<Doctor_identity>vDoc;

	//������ҽ���˺��ظ� �������������û���name�� ����ֵ��true�������ظ���false�������ظ���
	bool checkUsersRepeat(string name);

	//��� ���/�޸� ҽ���û�ʱҽ������ظ�
	bool checkDoctorRepeat(int id);

	//��� ���/�޸� �����û�ʱ���߱���ظ�
	bool checkPatientRepeat(int id);

	//��������
	~The_Manager();

};