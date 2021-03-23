#include "doctor_identity.h"

//构造函数
Doctor_identity::Doctor_identity()
{
	
}

//有参构造函数（医生账号，密码）
Doctor_identity::Doctor_identity(string i_Dname, string i_Dpwd)
{
	this->i_Name = i_Dname;
	this->i_Pwd = i_Dpwd;

	//根据三种情况写病历构造函数
	//1、病历文件不存在
	ifstream cfs;
	cfs.open(C_FILENAME, ios::in); //读文件

	if (!cfs.is_open())
	{
		//cout << "文件不存在！" << endl;
		//初始化属性
		this->m_CaseNum = 0;   //初始化记录的人数为0
		this->m_CaseArray = NULL;  //初始化数组的指针为空
		//初始化文件是否为空
		this->m_CFileIsEmpty = true;
		cfs.close();
		return;
	}

	//2、患者文件存在 但是数据为空
	char ch;
	cfs >> ch;    //读一个字符
	if (cfs.eof())
	{
		//cout << "文件为空" << endl;
		this->m_CaseNum = 0;   //初始化记录的人数为0
		this->m_CaseArray = NULL;  //初始化数组的指针为空
		//初始化文件是否为空
		this->m_CFileIsEmpty = true;
		cfs.close();
		return;
	}

	//文件存在 并且记录了数据
	int c_num = this->get_CaseNum();
	this->m_CaseNum = c_num;

	//开辟空间
	//根据患者人数创建数组
	this->m_CaseArray = new Casehistory * [this->m_CaseNum];
	//将文件中的数据，存到数组中
	//初始化职工
	this->init_Case();
}


//选择菜单
void Doctor_identity::opermenu()
{
	cout << "=================   欢迎使用医院门诊信息管理系统    =================" << endl;
	cout << "欢迎医生" << this->i_Name << "登录!"<< endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 1、患者病历信息操作             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 2、注销登录                     |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "请输入您的选择：";
}

//病历信息基本操作菜单
void Doctor_identity::showHCaseAct()
{
	cout << "=======================   患者病历信息操作    ======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                1、添加患者病历信息              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                2、查询患者病历信息              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                3、删除患者病历信息              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                4、病历信息保存文件              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                5、返回上一级菜单                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "请输入您的选择：";
}

//统计原文件中病历个数
int Doctor_identity::get_CaseNum()
{
	ifstream ifs;
	ifs.open(C_FILENAME, ios::in);  //打开文件 读

	int id;
	string name;
	int dId;
	char situation[64];
	char advice[64];

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId && ifs >> situation && ifs >> advice)
	{
		//统计人数
		num++;
	}

	return num;
}

//初始化病历文件
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
		//根据不同的部门编号创建不同的对象
		if (dId == 1)   //1、内科
		{
			casehistory = new Casehistory(id, name, dId, situation, advice);
		}
		else if (dId == 2)   //2、外科
		{
			casehistory = new Casehistory(id, name, dId, situation, advice);
		}
		else if (dId == 3)   //3、妇科
		{
			casehistory = new Casehistory(id, name, dId, situation, advice);
		}
		else  //4、儿科
		{
			casehistory = new Casehistory(id, name, dId, situation, advice);
		}

		//存放在数组中
		this->m_CaseArray[index] = casehistory;
		index++;
	}

	//关闭文件
	ifs.close();
}

//患者病历信息填写
void Doctor_identity::add_Case()
{
	system("cls");
	int addNum = 0; //保存用户的输入数量
	while (true)
	{
		cout << "请输入填写病历的数量：" << endl;
		cin >> addNum;
		
		if (addNum > 0)
		{
			//添加
			//计算添加新空间大小
			int newSize = this->m_CaseNum + addNum; //新空间人数 = 原来记录人数+新增人数

			//开辟新空间(动态扩展）
			Casehistory** newSpace = new Casehistory * [newSize];


			//将原来空间下数据，拷贝到新空间下
			if (this->m_CaseArray != NULL) //如果原来的空间不为空
			{
				for (int i = 0; i < this->m_CaseNum; i++)
				{
					newSpace[i] = this->m_CaseArray[i];
				}
			}

			//批量添加新数据
			for (int i = 0; i < addNum; i++)
			{
				system("cls");
				int id; //患者编号
				string name; //患者姓名
				int dSelect; //患者科室
				char situation[64]; //患者病情
				char advice[64];  //医生建议

				cout << "请输入第 " << i + 1 << " 个患者编号" << endl;
				while (true)
				{
					cin >> id;
					bool flag = this->checkCHistoryRepeat(id);

					if (flag) //有重复
					{
						cout << "输入的患者编号重复，请重新输入！" << endl;
						cout << "请输入第 " << i + 1 << " 个患者编号" << endl;
					}
					else
					{
						break;
					}
				}

				cout << "请输入第 " << i + 1 << " 个患者姓名" << endl;
				cin >> name;

				cout << "请选择患者科室: " << endl;
				cout << "1、内科" << endl;
				cout << "2、外科" << endl;
				cout << "3、妇科" << endl;
				cout << "4、儿科" << endl;

				while (true)
				{
					cin >> dSelect;
					if (dSelect == 1 || dSelect == 2 || dSelect == 3 || dSelect == 4)
					{
						break;
					}
					else
					{
						cout << "选择的患者科室有误，请重新选择！" << endl;
						cout << "请选择患者科室:" << endl;
					}
				}

				cout << "请输入患者病情： " << endl;
				cin >> situation;
				cout << "请输入医生建议： " << endl;
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

				//将创建的病历指针，保存到数组中
				newSpace[this->m_CaseNum + i] = casehistory;
			}

			//释放原有的空间
			delete[] this->m_CaseArray;

			//更改新空间的指向
			this->m_CaseArray = newSpace;

			//更新新的病历数
			this->m_CaseNum = newSize;

			//更新职工不为空标志
			this->m_CFileIsEmpty = false;

			//提示添加成功
			cout << "成功添加 " << addNum << " 份病历！" << endl;
			system("pause");
			system("cls");
			break;

		}
		else
		{
			cout << "输入有误，请重新输入！" << endl;
		}
	}
}

//患者病历信息查询
void Doctor_identity::Find_Case()
{
	system("cls");
	if (this->m_CFileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		showHCaseActSecond();

		int select = 0;
		while (true)
		{
			cin >> select;

			if (select == 1) //按病历编号查找
			{
				system("cls");
				int id;
				cout << "请输入查找的病历编号：" << endl;
				cin >> id;

				int ret = CIsExist(id);
				if (ret != -1)
				{
					cout << "查找成功，编号为" << id << "的病历信息如下:" << endl;
					this->m_CaseArray[ret]->c_ShowInfo();
				}
				else
				{
					cout << "查找失败，无此病历！" << endl;
				}
				system("pause");
				system("cls");
				showHCaseActSecond();
			}
			else if (select == 2)
			{
				system("cls");
				string name;
				cout << "请输入查找的病历患者姓名 ：" << endl;
				cin >> name;

				bool flag = false; //查找到的标志
				for (int i = 0; i < m_CaseNum; i++)
				{
					if (m_CaseArray[i]->m_Name == name)
					{
						cout << "查找成功，病历患者姓名为: "
							<< m_CaseArray[i]->m_Name
							<< " 号的信息如下" << endl;

						flag = true;

						this->m_CaseArray[i]->c_ShowInfo();
					}
				}
				if (flag == false)
				{
					cout << "查找失败，无此病历！" << endl;
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
				cout << "选择有误，请重新选择！" << endl;
				showHCaseActSecond();
			}
		}
	}
}

//患者病历信息删除
void Doctor_identity::Del_Case()
{
	system("cls");
	if (this->m_CFileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按照病历编号删除
		cout << "请输入想要删除病历编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->CIsExist(id);
		if (index != -1) //说明病历存在，并且要删除index位置上的病历
		{
			//数据前移
			for (int i = index; i < this->m_CaseNum - 1; i++)
			{
				this->m_CaseArray[i] = this->m_CaseArray[i + 1];
			}
			this->m_CaseNum--;  //个更新以下数组中记录的病历个数


			cout << "病历删除成功！" << endl;
		}
		else
		{
			cout << "删除失败！未找到该病历！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//按照患者病历编号判断患者病历是否存在，若存在返回患者病历在数组中位置，不存在返回-1
int Doctor_identity::CIsExist(int id)
{
	{
		int index = -1;
		for (int i = 0; i < this->m_CaseNum; i++)
		{
			//找到职工
			if (this->m_CaseArray[i]->m_Id == id)
			{
				index = i;
				break;
			}
		}
		return index;
	}
}

//保存病历文件
void Doctor_identity::C_save()
{
	ofstream ofs;
	ofs.open(C_FILENAME, ios::out);  //用输出方式打开文件 -- 写文件

	//将每个人的数据写入文件中
	for (int i = 0; i < this->m_CaseNum; i++)
	{
		ofs << this->m_CaseArray[i]->m_Id << " "
			<< this->m_CaseArray[i]->m_Name << " "
			<< this->m_CaseArray[i]->m_Dep << " "
			<< this->m_CaseArray[i]->m_Situation << " "
			<< this->m_CaseArray[i]->m_Advice << endl;
	}

	//关闭文件
	ofs.close();
	cout << "病历文件保存成功！" << endl;
}

//展示患者病历查找菜单
void Doctor_identity::showHCaseActSecond()
{
	cout << "========================   患者病历查找   =========================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                1、按病历编号查找                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                2、按病历姓名查找                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                3、返回上一级菜单                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "请输入您的选择：";
}

//检测 添加 病历文件时病历编号重复
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


//析构函数
Doctor_identity::~Doctor_identity()
{
	//释放病历空间
	if (this->m_CaseArray != NULL)
	{
		delete[] this->m_CaseArray;
		this->m_CaseArray = NULL;
	}
}
