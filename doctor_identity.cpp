#include "doctor_identity.h"

//���캯��
Doctor_identity::Doctor_identity()
{
	
}

//�вι��캯����ҽ���˺ţ����룩
Doctor_identity::Doctor_identity(string i_Dname, string i_Dpwd)
{
	this->i_Name = i_Dname;
	this->i_Pwd = i_Dpwd;

	//�����������д�������캯��
	//1�������ļ�������
	ifstream cfs;
	cfs.open(C_FILENAME, ios::in); //���ļ�

	if (!cfs.is_open())
	{
		//cout << "�ļ������ڣ�" << endl;
		//��ʼ������
		this->m_CaseNum = 0;   //��ʼ����¼������Ϊ0
		this->m_CaseArray = NULL;  //��ʼ�������ָ��Ϊ��
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_CFileIsEmpty = true;
		cfs.close();
		return;
	}

	//2�������ļ����� ��������Ϊ��
	char ch;
	cfs >> ch;    //��һ���ַ�
	if (cfs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->m_CaseNum = 0;   //��ʼ����¼������Ϊ0
		this->m_CaseArray = NULL;  //��ʼ�������ָ��Ϊ��
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_CFileIsEmpty = true;
		cfs.close();
		return;
	}

	//�ļ����� ���Ҽ�¼������
	int c_num = this->get_CaseNum();
	this->m_CaseNum = c_num;

	//���ٿռ�
	//���ݻ���������������
	this->m_CaseArray = new Casehistory * [this->m_CaseNum];
	//���ļ��е����ݣ��浽������
	//��ʼ��ְ��
	this->init_Case();
}


//ѡ��˵�
void Doctor_identity::opermenu()
{
	cout << "=================   ��ӭʹ��ҽԺ������Ϣ����ϵͳ    =================" << endl;
	cout << "��ӭҽ��" << this->i_Name << "��¼!"<< endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 1�����߲�����Ϣ����             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 2��ע����¼                     |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "����������ѡ��";
}

//������Ϣ���������˵�
void Doctor_identity::showHCaseAct()
{
	cout << "=======================   ���߲�����Ϣ����    ======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                1����ӻ��߲�����Ϣ              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                2����ѯ���߲�����Ϣ              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                3��ɾ�����߲�����Ϣ              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                4��������Ϣ�����ļ�              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                5��������һ���˵�                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "����������ѡ��";
}

//ͳ��ԭ�ļ��в�������
int Doctor_identity::get_CaseNum()
{
	ifstream ifs;
	ifs.open(C_FILENAME, ios::in);  //���ļ� ��

	int id;
	string name;
	int dId;
	char situation[64];
	char advice[64];

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId && ifs >> situation && ifs >> advice)
	{
		//ͳ������
		num++;
	}

	return num;
}

//��ʼ�������ļ�
void Doctor_identity::init_Case()
{
	ifstream ifs;
	ifs.open(C_FILENAME, ios::in);

	int id;
	string name;
	int dId;
	char situation[64];
	char advice[64];

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId && ifs >> situation && ifs >> advice)
	{
		Casehistory* casehistory = NULL;
		//���ݲ�ͬ�Ĳ��ű�Ŵ�����ͬ�Ķ���
		if (dId == 1)   //1���ڿ�
		{
			casehistory = new Casehistory(id, name, dId, situation, advice);
		}
		else if (dId == 2)   //2�����
		{
			casehistory = new Casehistory(id, name, dId, situation, advice);
		}
		else if (dId == 3)   //3������
		{
			casehistory = new Casehistory(id, name, dId, situation, advice);
		}
		else  //4������
		{
			casehistory = new Casehistory(id, name, dId, situation, advice);
		}

		//�����������
		this->m_CaseArray[index] = casehistory;
		index++;
	}

	//�ر��ļ�
	ifs.close();
}

//���߲�����Ϣ��д
void Doctor_identity::add_Case()
{
	system("cls");
	int addNum = 0; //�����û�����������
	while (true)
	{
		cout << "��������д������������" << endl;
		cin >> addNum;
		
		if (addNum > 0)
		{
			//���
			//��������¿ռ��С
			int newSize = this->m_CaseNum + addNum; //�¿ռ����� = ԭ����¼����+��������

			//�����¿ռ�(��̬��չ��
			Casehistory** newSpace = new Casehistory * [newSize];


			//��ԭ���ռ������ݣ��������¿ռ���
			if (this->m_CaseArray != NULL) //���ԭ���Ŀռ䲻Ϊ��
			{
				for (int i = 0; i < this->m_CaseNum; i++)
				{
					newSpace[i] = this->m_CaseArray[i];
				}
			}

			//�������������
			for (int i = 0; i < addNum; i++)
			{
				system("cls");
				int id; //���߱��
				string name; //��������
				int dSelect; //���߿���
				char situation[64]; //���߲���
				char advice[64];  //ҽ������

				cout << "������� " << i + 1 << " �����߱��" << endl;
				while (true)
				{
					cin >> id;
					bool flag = this->checkCHistoryRepeat(id);

					if (flag) //���ظ�
					{
						cout << "����Ļ��߱���ظ������������룡" << endl;
						cout << "������� " << i + 1 << " �����߱��" << endl;
					}
					else
					{
						break;
					}
				}

				cout << "������� " << i + 1 << " ����������" << endl;
				cin >> name;

				cout << "��ѡ���߿���: " << endl;
				cout << "1���ڿ�" << endl;
				cout << "2�����" << endl;
				cout << "3������" << endl;
				cout << "4������" << endl;

				while (true)
				{
					cin >> dSelect;
					if (dSelect == 1 || dSelect == 2 || dSelect == 3 || dSelect == 4)
					{
						break;
					}
					else
					{
						cout << "ѡ��Ļ��߿�������������ѡ��" << endl;
						cout << "��ѡ���߿���:" << endl;
					}
				}

				cout << "�����뻼�߲��飺 " << endl;
				cin >> situation;
				cout << "������ҽ�����飺 " << endl;
				cin >> advice;

				Casehistory* casehistory = NULL;
				switch (dSelect)
				{
				case 1:
					casehistory = new Casehistory(id, name, dSelect, situation, advice);
					break;
				case 2:
					casehistory = new Casehistory(id, name, dSelect, situation, advice);
					break;
				case 3:
					casehistory = new Casehistory(id, name, dSelect, situation, advice);
					break;
				case 4:
					casehistory = new Casehistory(id, name, dSelect, situation, advice);
					break;
				default:
					break;
				}

			//	system("cls");

				//�������Ĳ���ָ�룬���浽������
				newSpace[this->m_CaseNum + i] = casehistory;
			}

			//�ͷ�ԭ�еĿռ�
			delete[] this->m_CaseArray;

			//�����¿ռ��ָ��
			this->m_CaseArray = newSpace;

			//�����µĲ�����
			this->m_CaseNum = newSize;

			//����ְ����Ϊ�ձ�־
			this->m_CFileIsEmpty = false;

			//��ʾ��ӳɹ�
			cout << "�ɹ���� " << addNum << " �ݲ�����" << endl;
			system("pause");
			system("cls");
			break;

		}
		else
		{
			cout << "�����������������룡" << endl;
		}
	}
}

//���߲�����Ϣ��ѯ
void Doctor_identity::Find_Case()
{
	system("cls");
	if (this->m_CFileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		showHCaseActSecond();

		int select = 0;
		while (true)
		{
			cin >> select;

			if (select == 1) //��������Ų���
			{
				system("cls");
				int id;
				cout << "��������ҵĲ�����ţ�" << endl;
				cin >> id;

				int ret = CIsExist(id);
				if (ret != -1)
				{
					cout << "���ҳɹ������Ϊ" << id << "�Ĳ�����Ϣ����:" << endl;
					this->m_CaseArray[ret]->c_ShowInfo();
				}
				else
				{
					cout << "����ʧ�ܣ��޴˲�����" << endl;
				}
				system("pause");
				system("cls");
				showHCaseActSecond();
			}
			else if (select == 2)
			{
				system("cls");
				string name;
				cout << "��������ҵĲ����������� ��" << endl;
				cin >> name;

				bool flag = false; //���ҵ��ı�־
				for (int i = 0; i < m_CaseNum; i++)
				{
					if (m_CaseArray[i]->m_Name == name)
					{
						cout << "���ҳɹ���������������Ϊ: "
							<< m_CaseArray[i]->m_Name
							<< " �ŵ���Ϣ����" << endl;

						flag = true;

						this->m_CaseArray[i]->c_ShowInfo();
					}
				}
				if (flag == false)
				{
					cout << "����ʧ�ܣ��޴˲�����" << endl;
				}
				system("pause");
				system("cls");
				showHCaseActSecond();
			}
			else if (select == 3)
			{
				system("cls");
				//showHCaseAct();
				break;
			}
			else
			{
				system("cls");
				cout << "ѡ������������ѡ��" << endl;
				showHCaseActSecond();
			}
		}
	}
}

//���߲�����Ϣɾ��
void Doctor_identity::Del_Case()
{
	system("cls");
	if (this->m_CFileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//���ղ������ɾ��
		cout << "��������Ҫɾ��������ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->CIsExist(id);
		if (index != -1) //˵���������ڣ�����Ҫɾ��indexλ���ϵĲ���
		{
			//����ǰ��
			for (int i = index; i < this->m_CaseNum - 1; i++)
			{
				this->m_CaseArray[i] = this->m_CaseArray[i + 1];
			}
			this->m_CaseNum--;  //���������������м�¼�Ĳ�������


			cout << "����ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ��ò�����" << endl;
		}
	}
	system("pause");
	system("cls");
}

//���ջ��߲�������жϻ��߲����Ƿ���ڣ������ڷ��ػ��߲�����������λ�ã������ڷ���-1
int Doctor_identity::CIsExist(int id)
{
	{
		int index = -1;
		for (int i = 0; i < this->m_CaseNum; i++)
		{
			//�ҵ�ְ��
			if (this->m_CaseArray[i]->m_Id == id)
			{
				index = i;
				break;
			}
		}
		return index;
	}
}

//���没���ļ�
void Doctor_identity::C_save()
{
	ofstream ofs;
	ofs.open(C_FILENAME, ios::out);  //�������ʽ���ļ� -- д�ļ�

	//��ÿ���˵�����д���ļ���
	for (int i = 0; i < this->m_CaseNum; i++)
	{
		ofs << this->m_CaseArray[i]->m_Id << " "
			<< this->m_CaseArray[i]->m_Name << " "
			<< this->m_CaseArray[i]->m_Dep << " "
			<< this->m_CaseArray[i]->m_Situation << " "
			<< this->m_CaseArray[i]->m_Advice << endl;
	}

	//�ر��ļ�
	ofs.close();
	cout << "�����ļ�����ɹ���" << endl;
}

//չʾ���߲������Ҳ˵�
void Doctor_identity::showHCaseActSecond()
{
	cout << "========================   ���߲�������   =========================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                1����������Ų���                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                2����������������                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                3��������һ���˵�                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "����������ѡ��";
}

//��� ��� �����ļ�ʱ��������ظ�
bool Doctor_identity::checkCHistoryRepeat(int id)
{
	for (int i = 0; i < m_CaseNum; i++)
	{
		if (m_CaseArray[i]->m_Id == id)
		{
			return true;
		}
	}
	return false;
}


//��������
Doctor_identity::~Doctor_identity()
{
	//�ͷŲ����ռ�
	if (this->m_CaseArray != NULL)
	{
		delete[] this->m_CaseArray;
		this->m_CaseArray = NULL;
	}
}
