#include "TheManager.h"

//Ĭ�Ϲ���
The_Manager::The_Manager()
{
	//��ʵ��
}

//�вι��� ����Ա�˺ţ�����
The_Manager::The_Manager(string z_name, string z_pwd)
{
	this->i_Name = z_name;
	this->i_Pwd = z_pwd;

	//�����������дҽ�����캯��
	//1��ҽ���ļ�������
	ifstream dfs;
	dfs.open(D_FILENAME, ios::in); //���ļ�

	if (!dfs.is_open())
	{
		//cout << "�ļ������ڣ�" << endl;
		//��ʼ������
		this->m_DocNum = 0;   //��ʼ����¼������Ϊ0
		this->m_DocArray = NULL;  //��ʼ�������ָ��Ϊ��
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_DFileIsEmpty = true;
		dfs.close();
		return;
	}

	//2��ҽ���ļ����� ��������Ϊ��
	char dh;
	dfs >> dh;    //��һ���ַ�
	if (dfs.eof())
	{
		this->m_DocNum = 0;   //��ʼ����¼������Ϊ0
		this->m_DocArray = NULL;  //��ʼ�������ָ��Ϊ��
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_DFileIsEmpty = true;
		dfs.close();
		return;
	}

	//�ļ����� ���Ҽ�¼������
	int d_num = this->get_DocNum();
	this->m_DocNum = d_num;

	//���ٿռ�
	//����ҽ��������������
	this->m_DocArray = new Doctor * [this->m_DocNum];
	//���ļ��е����ݣ��浽������
	//��ʼ��ҽ��
	this->init_Doc();


	//�����������д���߹��캯��
	//1�������ļ�������
	ifstream pfs;
	pfs.open(P_FILENAME, ios::in); //���ļ�


	if (!pfs.is_open())
	{
		//cout << "�ļ������ڣ�" << endl;
		//��ʼ������
		this->m_PatNum = 0;   //��ʼ����¼������Ϊ0
		this->m_PatArray = NULL;  //��ʼ�������ָ��Ϊ��
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_PFileIsEmpty = true;
		pfs.close();
		return;
	}

	//2�������ļ����� ��������Ϊ��
	char th;
	pfs >> th;    //��һ���ַ�
	if (pfs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->m_PatNum = 0;   //��ʼ����¼������Ϊ0
		this->m_PatArray = NULL;  //��ʼ�������ָ��Ϊ��
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_PFileIsEmpty = true;
		pfs.close();
		return;
	}

	//�ļ����� ���Ҽ�¼������
	int p_num = this->get_PatNum();
	this->m_PatNum = p_num;

	//���ٿռ�
	//���ݻ���������������
	this->m_PatArray = new Patient * [this->m_PatNum];
	//���ļ��е����ݣ��浽������
	//��ʼ������
	this->init_Pat();


	//��ʼ������ ��ȡ���ļ���ҽ����Ϣ
	this->initVector();
}

//ѡ��˵�
void The_Manager::opermenu()
{
	cout << "=================   ��ӭʹ��ҽԺ������Ϣ����ϵͳ    =================" << endl;
	cout << "��ӭ����Ա��" << this -> i_Name << "��¼��" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 1�����ҽ���˺�                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 2���鿴ҽ���˺�                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 3��ҽ��������Ϣ����             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 4�����߹Һ���Ϣ����             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 5��ͳ�ƾ��ﲡ������             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 6��ע����¼                     |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "����������ѡ��";
}



//����ҽ������ж�ҽ���Ƿ���ڣ������ڷ���ҽ����������λ�ã������ڷ���-1
int The_Manager::DIsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_DocNum; i++)
	{
		//�ҵ�ְ��
		if (this->m_DocArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//���ջ��߱���жϻ����Ƿ���ڣ������ڷ��ػ�����������λ�ã������ڷ���-1
int The_Manager::PIsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_PatNum; i++)
	{
		//�ҵ�ְ��
		if (this->m_PatArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//����˺�
void The_Manager::addPerson()
{
	string fileName;  //�����ļ���
	ofstream ofs;     //�ļ���������

	ofs.open(FDOCTOR_FILE, ios::out | ios::app);   //ios::app   ��׷�ӵķ�ʽд��
	string name;
	string pwd;

	cout << "�������û�����" << endl;
	while (true)
	{
		cin >> name;
		bool ret = this->checkUsersRepeat(name);

		if (ret) //���ظ�
		{
			cout << "�û����ظ������������룡" << endl;
			cout << "�������û�����" << endl;
		}
		else
		{
			break;
		}
	}

	cout << "���������룺" << endl;
	cin >> pwd;
	
	ofs << name << "  " << pwd << " " << endl;
	cout << "��ӳɹ���" << endl;

	//��Ȼ���Լ���ظ����˺ţ����Ǹ���ӵ��˺�����û�и��µ������У���˲��������
	//���¸ռ�����û������ٴ����ʱ��Ȼ�����ظ���������������䣬
	
	//���ó�ʼ�������ӿڣ����»�ȡ�ļ��е�����
	this->initVector();

	system("pause");
	system("cls");

	ofs.close();
}

void printDoctor(Doctor_identity &s)
{
	cout << "ҽ���û�����" << s.i_Name << "\t\t\t���룺 " << s.i_Pwd << endl;
}

//�鿴�˺�
void The_Manager::showPerson()
{
	this->initVector();
	system("cls");
	cout << "����ҽ�����˺���Ϣ���£�" << endl;
	for_each(vDoc.begin(), vDoc.end(), printDoctor);
	system("pause");
	system("cls");
}


//ҽ����Ϣ���������˵�
void The_Manager::showDocAct()
{
	cout << "=======================   ҽ��������Ϣ����    =======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 1�����ҽ����Ϣ                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 2���޸�ҽ����Ϣ                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 3��ɾ��ҽ����Ϣ                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 4����ѯҽ����Ϣ                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 5��ҽ����Ϣ�����ļ�             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 6��������һ���˵�               |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "����������ѡ��";
}

//ҽ��������Ϣ¼��
void The_Manager::add_Doc()
{
	system("cls");

	int addNum = 0; //�����û�����������

	while (true)
	{
		cout << "������¼��ҽ����������" << endl;
		cin >> addNum;

		if (addNum > 0)
		{
			//���
			//��������¿ռ��С
			int newSize = this->m_DocNum + addNum; //�¿ռ����� = ԭ����¼����+��������

			//�����¿ռ�(��̬��չ��
			Doctor** newSpace = new Doctor * [newSize];


			//��ԭ���ռ������ݣ��������¿ռ���
			if (this->m_DocArray != NULL) //���ԭ���Ŀռ䲻Ϊ��
			{
				for (int i = 0; i < this->m_DocNum; i++)
				{
					newSpace[i] = this->m_DocArray[i];
				}
			}


			//�������������
			for (int i = 0; i < addNum; i++)
			{
				system("cls");
				int id; //ҽ�����
				string name; //ҽ������
				int dSelect; //����ѡ��


				cout << "������� " << i + 1 << " ��ҽ�����" << endl;
				while (true)
				{
					cin >> id;
					bool flag = this->checkDoctorRepeat(id);

					if (flag) //���ظ�
					{
						cout << "�����ҽ������ظ������������룡" << endl;
						cout << "������� " << i + 1 << " ��ҽ�����" << endl;
					}
					else
					{
						break;
					}
				}

				cout << "������� " << i + 1 << " ��ҽ������" << endl;
				cin >> name;

				cout << "��ѡ���ҽ������:" << endl;
				cout << "1��ҽ���" << endl;
				cout << "2�����¿�" << endl;
				cout << "3��ҽ����" << endl;

				while (true)
				{
					cin >> dSelect;
					if (dSelect == 1 || dSelect == 2 || dSelect == 3)
					{
						break;
					}
					else
					{
						cout << "ѡ���ҽ����������������ѡ��" << endl;
						cout << "��ѡ���ҽ������:" << endl;
					}
				}


				Doctor* doctor = NULL;

				switch (dSelect)
				{
				case 1:
					doctor = new Doctor(id, name, dSelect);
					break;
				case 2:
					doctor = new Doctor(id, name, dSelect);
					break;
				case 3:
					doctor = new Doctor(id, name, dSelect);
					break;
				default:
					break;
				}


				//��������ҽ��ָ�룬���浽������
				newSpace[this->m_DocNum + i] = doctor;
			}

			//�ͷ�ԭ�еĿռ�
			delete[] this->m_DocArray;

			//�����¿ռ��ָ��
			this->m_DocArray = newSpace;

			//�����µ�ҽ������
			this->m_DocNum = newSize;

			//����ְ����Ϊ�ձ�־
			this->m_DFileIsEmpty = false;

			//��ʾ��ӳɹ�
			cout << "�ɹ���� " << addNum << " ��ҽ����" << endl;
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

//ҽ��������Ϣ�޸�
void The_Manager::Mod_Doc()
{
	system("cls");
	if (this->m_DFileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸�ҽ���ı�ţ�" << endl;
		int id;
		cin >> id;

		int ret = this->DIsExist(id);
		if (ret != -1)
		{
			//ɾ�����ҵ���ŵ�ҽ��
			delete this->m_DocArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽��" << id << "��ҽ������������ҽ����ţ�" << endl;

			while (true)
			{
				cin >> newId;
				bool flag = this->checkDoctorRepeat(newId);

				if (flag) //���ظ�
				{
					cout << "�������ҽ������ظ������������룡" << endl;
					cout << "�鵽��" << id << "��ҽ������������ҽ����ţ�" << endl;
				}
				else
				{
					break;
				}
			}

			cout << "��������ҽ��������" << endl;
			cin >> newName;

			cout << "��ѡ���ҽ�����Ų��ţ�" << endl;
			cout << "1��ҽ���" << endl;
			cout << "2�����¿�" << endl;
			cout << "3��ҽ����" << endl;
			
			while (true)
			{
				cin >> dSelect;
				if (dSelect == 1 || dSelect == 2 || dSelect == 3)
				{
					break;
				}
				else
				{
					cout << "ѡ���ҽ����������������ѡ��" << endl;
					cout << "��ѡ���ҽ������:" << endl;
				}
			}

			Doctor* doctor = NULL;
			switch (dSelect)
			{
			case 1:
				doctor = new Doctor(newId, newName, dSelect);
				break;

			case 2:
				doctor = new Doctor(newId, newName, dSelect);
				break;

			case 3:
				doctor = new Doctor(newId, newName, dSelect);
				break;

			default:
				break;
			}

			//�������� ��������
			this->m_DocArray[ret] = doctor;

			cout << "�޸ĳɹ���" << endl;
		}
		else
		{
			cout << "�޸�ʧ�ܣ�δ�ҵ���ҽ����" << endl;
		}
	}

	system("pause");
	system("cls");
}

//ɾ��ҽ����Ϣ
void The_Manager::Del_Doc()
{
	system("cls");
	if (this->m_DFileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//����ҽ�����ɾ��
		cout << "��������Ҫɾ��ҽ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->DIsExist(id);
		if (index != -1) //˵��ҽ�����ڣ�����Ҫɾ��indexλ���ϵ�ҽ��
		{
			//����ǰ��
			for (int i = index; i < this->m_DocNum - 1; i++)
			{
				this->m_DocArray[i] = this->m_DocArray[i + 1];
			}
			this->m_DocNum--;  //���������������м�¼����Ա����

			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ҽ����" << endl;
		}
	}

	system("pause");
	system("cls");
}


//���߹Һ���Ϣ���������˵�
void The_Manager::showPatAct()
{
	cout << "=======================   ���߹Һ���Ϣ����    =======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 1����ӻ��߹Һ���Ϣ             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 2���޸Ļ��߹Һ���Ϣ             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 3��ɾ�����߹Һ���Ϣ             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 4�����߹Һ���Ϣ�����ļ�         |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 5��������һ���˵�               |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "����������ѡ��";
}


//���߹Һ���Ϣ¼��
void The_Manager::add_Pat()
{
	system("cls");

	int addNum = 0; //�����û�����������
	while (true)
	{
		cout << "������¼�뻼�ߵ�������" << endl;
		cin >> addNum;
		if (addNum > 0)
		{
			//���
			//��������¿ռ��С
			int newSize = this->m_PatNum + addNum; //�¿ռ����� = ԭ����¼����+��������

			//�����¿ռ�(��̬��չ��
			Patient** newSpace = new Patient * [newSize];


			//��ԭ���ռ������ݣ��������¿ռ���
			if (this->m_PatArray != NULL) //���ԭ���Ŀռ䲻Ϊ��
			{
				for (int i = 0; i < this->m_PatNum; i++)
				{
					newSpace[i] = this->m_PatArray[i];
				}
			}


			//�������������
			for (int i = 0; i < addNum; i++)
			{
				system("cls");
				int id; //���߱��
				string name; //ҽ������
				int dSelect; //�ҺŲ���
				int day;
				int month;
				int year;
				int flag = 0;

				cout << "������� " << i + 1 << " �����߱��" << endl;

				while (true)
				{
					cin >> id;
					bool flag = this->checkPatientRepeat(id);

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

				while (true)
				{
					//	flag = 0;
					cout << "������� " << i + 1 << " �����߾������ڣ���ʽ���� �� �գ��ֽ�֧��2010~2020�꣩" << endl;
					cin >> year >> month >> day;
					if (year < 2010 || year >2020)
					{
						cout << "�Һ�����������󣬿����뷶ΧΪ2010~2020�꣬��������������" << endl;
						flag++;
					}
					if (month < 1 || month > 12)
					{
						cout << "�Һ��·��������󣬿����뷶ΧΪ1~12�£���������������" << endl;
						flag++;
					}
					if (day < 1 || day > 31)
					{
						cout << "�Һ�����������󣬿����뷶ΧΪ1~31�գ���������������" << endl;
						flag++;
					}
					if (month == 2 && day > 29)
					{
						cout << "2�����Ϊ29�죬��������������" << endl;
						flag++;
					}
					if (flag == 0) break;
					flag = 0;

				}
				cout << "��ѡ���߹Һſ���:" << endl;
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

				Patient* patient = NULL;
				switch (dSelect)
				{
				case 1:
					patient = new Patient(id, name, year, month, day, dSelect);
					break;
				case 2:
					patient = new Patient(id, name, year, month, day, dSelect);
					break;
				case 3:
					patient = new Patient(id, name, year, month, day, dSelect);
					break;
				case 4:
					patient = new Patient(id, name, year, month, day, dSelect);
					break;
				default:
					break;
				}


				//�������Ļ���ָ�룬���浽������
				newSpace[this->m_PatNum + i] = patient;
			}

			//�ͷ�ԭ�еĿռ�
			delete[] this->m_PatArray;

			//�����¿ռ��ָ��
			this->m_PatArray = newSpace;

			//�����µ�ҽ������
			this->m_PatNum = newSize;

			//����ְ����Ϊ�ձ�־
			this->m_PFileIsEmpty = false;

			//��ʾ��ӳɹ�
			cout << "�ɹ���� " << addNum << " �����ߣ�" << endl;
			system("pause");
			system("cls");
			break;

		}
		else
		{
			cout << "��������,���������룡" << endl;
		}
	}
}


//���߻�����Ϣ�޸�
void The_Manager::Mod_Pat()
{
	system("cls");
	if (this->m_PFileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸Ļ��ߵı�ţ�" << endl;
		int id;
		cin >> id;

		int ret = this->PIsExist(id);
		if (ret != -1)
		{
			//ɾ�����ҵ���ŵĻ���
			delete this->m_PatArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;
			int newDay;
			int newMonth;
			int newYear;
			int flag = 0;


			cout << "�鵽��" << id << "�Ż��ߣ��������»��߱�ţ�" << endl;
			
			while (true)
			{
				cin >> newId;
				bool flag = this->checkPatientRepeat(newId);

				if (flag) //���ظ�
				{
					cout << "������»��߱���ظ������������룡" << endl;
					cout << "�鵽��" << id << "�Ż��ߣ��������»��߱�ţ�" << endl;
				}
				else
				{
					break;
				}
			}

			cout << "�������»���������" << endl;
			cin >> newName;

			while (true)
			{
				cout << "�����뻼���¾������ڣ���ʽ���� �� �գ��ֽ�֧��2010~2020�꣩" << endl;
				cin >> newYear >> newMonth >> newDay;
				if (newYear < 2010 || newYear >2020)
				{
					cout << "�Һ�����������󣬿����뷶ΧΪ2010~2020�꣬��������������" << endl;
					flag++;
				}
				if (newMonth < 1 || newMonth > 12)
				{
					cout << "�Һ��·��������󣬿����뷶ΧΪ1~12�£���������������" << endl;
					flag++;
				}
				if (newDay < 1 || newDay > 31)
				{
					cout << "�Һ�����������󣬿����뷶ΧΪ1~31�գ���������������" << endl;
					flag++;
				}
				if (newMonth == 2 && newDay > 29)
				{
					cout << "2�����Ϊ29�죬��������������" << endl;
					flag++;
				}
				if (flag == 0) break;
				flag = 0;
			}

			cout << "��ѡ���߿��ң�" << endl;
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

			Patient* patient = NULL;
			switch (dSelect)
			{
			case 1:
				patient = new Patient(newId, newName, newYear, newMonth, newDay, dSelect);
				break;

			case 2:
				patient = new Patient(newId, newName, newYear, newMonth, newDay, dSelect);
				break;

			case 3:
				patient = new Patient(newId, newName, newYear, newMonth, newDay, dSelect);
				break;

			case 4:
				patient = new Patient(newId, newName, newYear, newMonth, newDay, dSelect);
				break;

			default:
				break;
			}

			//�������� ��������
			this->m_PatArray[ret] = patient;

			cout << "�޸ĳɹ���" << endl;

		}
		else
		{
			cout << "�޸�ʧ�ܣ�δ�ҵ��û��ߣ�" << endl;
		}
	}

	system("pause");
	system("cls");
}

//ɾ��������Ϣ
void The_Manager::Del_Pat()
{
	system("cls");
	if (this->m_PFileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//���ջ��߱��ɾ��
		cout << "��������Ҫɾ�����߱�ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->PIsExist(id);
		if (index != -1) //˵�����ߴ��ڣ�����Ҫɾ��indexλ���ϵĻ���
		{
			//����ǰ��
			for (int i = index; i < this->m_PatNum - 1; i++)
			{
				this->m_PatArray[i] = this->m_PatArray[i + 1];
			}
			this->m_PatNum--;  //���������������м�¼����Ա����
			//ͬ�����µ��ļ���
			//this->P_save();

			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ��û��ߣ�" << endl;
		}
	}

	system("pause");
	system("cls");
}



//ҽ����Ϣ��ѯ
void The_Manager::Find_Doc()
{
	system("cls");
	if (this->m_DFileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		showFindDoc();

		int select = 0;
		while (true)
		{
			cin >> select;

			if (select == 1) //��ҽ����Ų���
			{
				system("cls");
				int id;
				cout << "��������ҵ�ҽ����ţ�" << endl;
				cin >> id;

				int ret = DIsExist(id);
				if (ret != -1)
				{
					cout << "���ҳɹ������Ϊ" << id << "��ҽ����Ϣ����:" << endl;
					this->m_DocArray[ret]->ShowInfo();

				}
				else
				{
					cout << "���޴��ˣ�" << endl;
				}
				system("pause");
				system("cls");
				showFindDoc();
			}
			else if (select == 2)
			{
				system("cls");
				string name;
				cout << "��������ҵ�ҽ������ ��" << endl;
				cin >> name;

				bool flag = false; //���ҵ��ı�־
				for (int i = 0; i < m_DocNum; i++)
				{
					if (m_DocArray[i]->m_Name == name)
					{
						cout << "���ҳɹ���ҽ������Ϊ: "
							<< m_DocArray[i]->m_Name
							<< " �ŵ���Ϣ����" << endl;

						flag = true;

						this->m_DocArray[i]->ShowInfo();
					}
				}
				if (flag == false)
				{
					cout << "����ʧ�ܣ����޴��ˣ�" << endl;
				}
				system("pause");
				system("cls");
				showFindDoc();

			}
			else if (select == 3)
			{
				system("cls");
				break;
			}
			else
			{
				system("cls");
				cout << "ѡ������������ѡ��" << endl;
				showFindDoc();
			}
		}
	}
}

//ͳ�ƾ��ﲡ������
void The_Manager::Cal_Pat()
{
	if (this->m_PFileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		system("cls");
		showCalPatf();

		int dSelect = 0;
		while (true)
		{
			cin >> dSelect;

			system("cls");
			if (dSelect == 1)
			{
				showCalPats();

				int select = 0;
				while (true)
				{
					cin >> select;

					if (select == 1)   //����ͳ�ƻ�������
					{
						system("cls");
						int year1[] = { 2010,2011,2012,2013,2014,2015,2016,2017,2018,2019,2020 };
						int year2[11] = { 0 };
						int month1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
						int month2[12] = { 0 };
						int day1[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,29,21,22,23,24,25,26,27,28,29,30,31 };

						for (int i = 0; i < 11; i++)
						{
							for (int j = 0; j < 12; j++)
							{
								int day2[31] = { 0 };
								for (int k = 0; k < m_PatNum; k++)
								{
									if (this->m_PatArray[k]->m_Year == year1[i] && this->m_PatArray[k]->m_Month == month1[j])
									{
										year2[i]++;
										month2[j]++;
										for (int w = 0; w < 31; w++)
										{
											if (this->m_PatArray[k]->m_Day == day1[w])
											{
												day2[w]++;
											}
										}
									}
								}
								for (int g = 0; g < 31; g++)
								{
									if (year2[i] != 0 && month2[j] != 0 && day2[g] != 0)
									{
										cout << year1[i] << "��" << month1[j] << "��" << day1[g] << "�գ���������Ϊ��" << day2[g] << endl;
									}
								}
							}
						}
						system("pause");
						system("cls");
						showCalPats();
					}
					else if (select == 2)  //����ͳ�ƻ�������
					{
						system("cls");
						int year1[] = { 2010,2011,2012,2013,2014,2015,2016,2017,2018,2019,2020 };
						int year2[11] = { 0 };
						int month1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };

						for (int i = 0; i < 11; i++)
						{
							int month2[12] = { 0 };
							for (int j = 0; j < m_PatNum; j++)
							{

								if (this->m_PatArray[j]->m_Year == year1[i])
								{
									year2[i]++;
									for (int k = 0; k < 12; k++)
									{
										if (this->m_PatArray[j]->m_Month == month1[k])
											month2[k]++;
									}
								}
							}
							for (int l = 0; l < 12; l++)
							{
								if (year2[i] != 0 && month2[l] != 0)
								{
									cout << year1[i] << "��" << month1[l] << "�£���������Ϊ�� " << month2[l] << "��" << endl;
								}
							}
						}
						system("pause");
						system("cls");
						showCalPats();
					}
					else if (select == 3)  //������ͳ�Ʋ�������
					{
						system("cls");
						int year1[] = { 2010,2011,2012,2013,2014,2015,2016,2017,2018,2019,2020 };
						int year2[11] = { 0 };
						int month1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
						int season1[] = { 1,2,3,4 };

						int month2[12] = { 0 };
						for (int i = 0; i < 11; i++)
						{
							int season2[4] = { 0 };
							for (int j = 0; j < m_PatNum; j++)
							{
								if (this->m_PatArray[j]->m_Year == year1[i])
								{

									year2[i]++;
									for (int k = 0; k < 12; k++)
									{
										if (this->m_PatArray[j]->m_Month == month1[k])
											month2[k]++;
									}
									if (this->m_PatArray[j]->m_Month == 1 || this->m_PatArray[j]->m_Month == 2 || this->m_PatArray[j]->m_Month == 3)
										season2[0]++;
									else if (this->m_PatArray[j]->m_Month == 4 || this->m_PatArray[j]->m_Month == 5 || this->m_PatArray[j]->m_Month == 6)
										season2[1]++;
									else if (this->m_PatArray[j]->m_Month == 8 || this->m_PatArray[j]->m_Month == 9 || this->m_PatArray[j]->m_Month == 10)
										season2[2]++;
									else
										season2[3]++;
								}
							}
							for (int q = 0; q < 4; q++)
							{
								if (year2[i] != 0 && season2[q] != 0)
									cout << year1[i] << "���" << season1[q] << "����,��������Ϊ��" << season2[q] << "��" << endl;
							}
						}
						system("pause");
						system("cls");
						showCalPats();
					}
					else if (select == 4)  //����ͳ�ƻ�������
					{
						system("cls");
						int year1[] = { 2010,2011,2012,2013,2014,2015,2016,2017,2018,2019,2020 };
						int year2[11] = { 0 };
						for (int i = 0; i <= 10; i++)
						{
							for (int j = 0; j < this->m_PatNum; j++)
							{
								if (this->m_PatArray[j]->m_Year == year1[i])
									year2[i]++;
							}
						}
						for (int i = 0; i <= 10; i++)
						{
							if (year2[i] != 0)
							{
								cout << year1[i] << "�꣬" << "��������Ϊ��" << year2[i] << "��" << endl;
							}
						}
						system("pause");
						system("cls");
						showCalPats();
					}
					else if(select == 5)
					{
						system("cls");
						showCalPatf();
						break;
					}
					else
					{
					system("cls");
					cout << "ѡ������������ѡ��" << endl;
					showCalPats();
					}
				}
			}

			else if (dSelect == 2)  //������ͳ��
			{
				system("cls");
				int did1[] = { 1,2,3,4 };
				int did2[4] = { 0 };
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < this->m_PatNum; j++)
					{
						if (this->m_PatArray[j]->m_Dep == did1[i])
							did2[i]++;
					}
				}
				for (int i = 0; i < 4; i++)
				{
					if (did2[i] != 0)
					{
						string dId = " ";
						if (did1[i] == 1)
						{
							dId = "�ڿ�";
							cout << dId << "��������Ϊ��" << did2[i] << "��" << endl;
						}
						else if (did1[i] == 2)
						{
							dId = "���";
							cout << dId << "��������Ϊ��" << did2[i] << "��" << endl;
						}
						else if (did1[i] == 3)
						{
							dId = "����";
							cout << dId << "��������Ϊ��" << did2[i] << "��" << endl;
						}
						else
						{
							dId = "����";
							cout << dId << "��������Ϊ��" << did2[i] << "��" << endl;
						}
					}
				}
				system("pause");
				system("cls");
				showCalPatf();
			}
			else if (dSelect == 3)
			{
				system("cls");
				break;
			}
			else
			{
				system("cls");
				cout << "ѡ������������ѡ��" << endl;
				showCalPatf();
			}
		}
	}
}

//ͳ��ԭ�ļ���ҽ������
int The_Manager::get_DocNum()
{
	ifstream ifs;
	ifs.open(D_FILENAME, ios::in);  //���ļ� ��

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//ͳ������
		num++;
	}

	return num;
}

//��ʼ��ҽ���ļ�
void The_Manager::init_Doc()
{
	ifstream ifs;
	ifs.open(D_FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Doctor* doctor = NULL;
		//���ݲ�ͬ�Ĳ��ű�Ŵ�����ͬ�Ķ���
		if (dId == 1)   //1��ҽ���
		{
			doctor = new Doctor(id, name, dId);
		}
		else if (dId == 2)   //2�����¿�
		{
			doctor = new Doctor(id, name, dId);
		}
		else  //ҽ����
		{
			doctor = new Doctor(id, name, dId);
		}

		//�����������
		this->m_DocArray[index] = doctor;
		index++;
	}

	//�ر��ļ�
	ifs.close();
}

//ͳ��ԭ�ļ��л�������
int The_Manager::get_PatNum()
{
	ifstream ifs;
	ifs.open(P_FILENAME, ios::in);  //���ļ� ��

	int id;
	string name;
	int dId;
	int day;
	int month;
	int year;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> year && ifs >> month && ifs >> day && ifs >> dId)
	{
		//ͳ������
		num++;
	}

	return num;
}

//��ʼ�������ļ�
void The_Manager::init_Pat()
{
	ifstream ifs;
	ifs.open(P_FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int day;
	int month;
	int year;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> year && ifs >> month && ifs >> day && ifs >> dId)
	{
		Patient* patient = NULL;
		//���ݲ�ͬ�Ĳ��ű�Ŵ�����ͬ�Ķ���
		if (dId == 1)        //1���ڿ�
		{
			patient = new Patient(id, name, year, month, day, dId);
		}
		else if (dId == 2)   //2�����
		{
			patient = new Patient(id, name, year, month, day, dId);
		}
		else if (dId == 3)   //3������
		{
			patient = new Patient(id, name, year, month, day, dId);
		}
		else                 //4������
		{
			patient = new Patient(id, name, year, month, day, dId);
		}

		//�����������
		this->m_PatArray[index] = patient;
		index++;
	}

	//�ر��ļ�
	ifs.close();
}


//����ҽ���ļ�
void The_Manager::D_save()
{
	ofstream ofs;
	ofs.open(D_FILENAME, ios::out);  //�������ʽ���ļ� -- д�ļ�

	//��ÿ���˵�����д���ļ���
	for (int i = 0; i < this->m_DocNum; i++)
	{
		ofs << this->m_DocArray[i]->m_Id << " "
			<< this->m_DocArray[i]->m_Name << " "
			<< this->m_DocArray[i]->m_Dep << endl;
	}

	//�ر��ļ�
	ofs.close();
	cout << "ҽ���ļ�����ɹ���" << endl;
}

//��ʼ������
void The_Manager::initVector()
{
	vDoc.clear();   //ȷ���������״̬
	//��ȡ��Ϣ ҽ��
	ifstream ifs;
	ifs.open(FDOCTOR_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}

	Doctor_identity s;
	while (ifs >> s.i_Name && ifs >> s.i_Pwd)
	{
		vDoc.push_back(s);  //�Ѵ��ļ��ж�ȡ��������Ϣ���浽������
	}

	ifs.close();
}

//���滼���ļ�
void The_Manager::P_save()
{
	ofstream ofs;
	ofs.open(P_FILENAME, ios::out);  //�������ʽ���ļ� -- д�ļ�

	//��ÿ���˵�����д���ļ���
	for (int i = 0; i < this->m_PatNum; i++)
	{
		ofs << this->m_PatArray[i]->m_Id << " "
			<< this->m_PatArray[i]->m_Name << " "
			<< this->m_PatArray[i]->m_Year << " "
			<< this->m_PatArray[i]->m_Month << " "
			<< this->m_PatArray[i]->m_Day << " "
			<< this->m_PatArray[i]->m_Dep << endl;
	}

	//�ر��ļ�
	ofs.close();
	cout << "�ɹ��������ļ���" << endl;
}

//������ҽ���ظ� �������������û���name�� ����ֵ��true�������ظ���false�������ظ���
bool The_Manager::checkUsersRepeat(string name)
{
	for (vector<Doctor_identity>::iterator it = vDoc.begin(); it != vDoc.end(); it++)
	{
		if (name == it->i_Name)
		{
			return true;
		}
	}
	return false;
}

//��� ���/�޸� ҽ���û��ظ�
bool The_Manager::checkDoctorRepeat(int id)
{
	for (int i = 0; i < m_DocNum; i++)
	{
		if (m_DocArray[i]->m_Id == id)
		{
			return true;
		}
	}
	return false;
}

//��� ���/�޸� �����û�ʱ���߱���ظ�
bool The_Manager::checkPatientRepeat(int id)
{
	for (int i = 0; i < m_PatNum; i++)
	{
		if (m_PatArray[i]->m_Id == id)
		{
			return true;
		}
	}
	return false;
}




//չʾҽ�����Ҳ����˵�
void The_Manager::showFindDoc()
{
	cout << "=======================   ҽ��������Ϣ����   =======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 1����ҽ����Ų���               |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 2����ҽ����������               |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 3��������һ���˵�               |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "����������ѡ��";
}

//չʾͳ�Ʋ������������˵�----��һ��
void The_Manager::showCalPatf()
{
	cout << "=======================   ͳ�ƾ��ﲡ������   =======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                1����ʱ��ͳ�Ʋ�������            |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                2��������ͳ�Ʋ�������            |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                3��������һ���˵�                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "����������ѡ��";
}

//չʾͳ�Ʋ������������˵�----�ڶ���
void The_Manager::showCalPats()
{
	cout << "=======================   ͳ�ƾ��ﲡ������   =======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                1������ͳ�Ʋ�������              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                2������ͳ�Ʋ�������              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                3��������ͳ�Ʋ�������            |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                4������ͳ�Ʋ�������              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                5��������һ���˵�                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "����������ѡ��";
}

//��������
The_Manager::~The_Manager()    //�ֶ��ͷŶ�������
{
	//�ͷ�ҽ���ռ�
	if (this->m_DocArray != NULL)
	{
		delete[] this->m_DocArray;
		this->m_DocArray = NULL;
	}

	//�ͷŻ��߿ռ�
	if (this->m_PatArray != NULL)
	{
		delete[] this->m_PatArray;
		this->m_PatArray = NULL;
	}

}