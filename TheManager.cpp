#include "TheManager.h"

//默认构造
The_Manager::The_Manager()
{
	//空实现
}

//有参构造 管理员账号，密码
The_Manager::The_Manager(string z_name, string z_pwd)
{
	this->i_Name = z_name;
	this->i_Pwd = z_pwd;

	//根据三种情况写医生构造函数
	//1、医生文件不存在
	ifstream dfs;
	dfs.open(D_FILENAME, ios::in); //读文件

	if (!dfs.is_open())
	{
		//cout << "文件不存在！" << endl;
		//初始化属性
		this->m_DocNum = 0;   //初始化记录的人数为0
		this->m_DocArray = NULL;  //初始化数组的指针为空
		//初始化文件是否为空
		this->m_DFileIsEmpty = true;
		dfs.close();
		return;
	}

	//2、医生文件存在 但是数据为空
	char dh;
	dfs >> dh;    //读一个字符
	if (dfs.eof())
	{
		this->m_DocNum = 0;   //初始化记录的人数为0
		this->m_DocArray = NULL;  //初始化数组的指针为空
		//初始化文件是否为空
		this->m_DFileIsEmpty = true;
		dfs.close();
		return;
	}

	//文件存在 并且记录了数据
	int d_num = this->get_DocNum();
	this->m_DocNum = d_num;

	//开辟空间
	//根据医生人数创建数组
	this->m_DocArray = new Doctor * [this->m_DocNum];
	//将文件中的数据，存到数组中
	//初始化医生
	this->init_Doc();


	//根据三种情况写患者构造函数
	//1、患者文件不存在
	ifstream pfs;
	pfs.open(P_FILENAME, ios::in); //读文件


	if (!pfs.is_open())
	{
		//cout << "文件不存在！" << endl;
		//初始化属性
		this->m_PatNum = 0;   //初始化记录的人数为0
		this->m_PatArray = NULL;  //初始化数组的指针为空
		//初始化文件是否为空
		this->m_PFileIsEmpty = true;
		pfs.close();
		return;
	}

	//2、患者文件存在 但是数据为空
	char th;
	pfs >> th;    //读一个字符
	if (pfs.eof())
	{
		//cout << "文件为空" << endl;
		this->m_PatNum = 0;   //初始化记录的人数为0
		this->m_PatArray = NULL;  //初始化数组的指针为空
		//初始化文件是否为空
		this->m_PFileIsEmpty = true;
		pfs.close();
		return;
	}

	//文件存在 并且记录了数据
	int p_num = this->get_PatNum();
	this->m_PatNum = p_num;

	//开辟空间
	//根据患者人数创建数组
	this->m_PatArray = new Patient * [this->m_PatNum];
	//将文件中的数据，存到数组中
	//初始化患者
	this->init_Pat();


	//初始化容器 获取到文件中医生信息
	this->initVector();
}

//选择菜单
void The_Manager::opermenu()
{
	cout << "=================   欢迎使用医院门诊信息管理系统    =================" << endl;
	cout << "欢迎管理员：" << this -> i_Name << "登录！" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 1、添加医生账号                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 2、查看医生账号                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 3、医生基本信息操作             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 4、患者挂号信息操作             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 5、统计就诊病人数量             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 6、注销登录                     |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "请输入您的选择：";
}



//按照医生编号判断医生是否存在，若存在返回医生在数组中位置，不存在返回-1
int The_Manager::DIsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_DocNum; i++)
	{
		//找到职工
		if (this->m_DocArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//按照患者编号判断患者是否存在，若存在返回患者在数组中位置，不存在返回-1
int The_Manager::PIsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_PatNum; i++)
	{
		//找到职工
		if (this->m_PatArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//添加账号
void The_Manager::addPerson()
{
	string fileName;  //操作文件名
	ofstream ofs;     //文件操作对象

	ofs.open(FDOCTOR_FILE, ios::out | ios::app);   //ios::app   以追加的方式写入
	string name;
	string pwd;

	cout << "请输入用户名：" << endl;
	while (true)
	{
		cin >> name;
		bool ret = this->checkUsersRepeat(name);

		if (ret) //有重复
		{
			cout << "用户名重复，请重新输入！" << endl;
			cout << "请输入用户名：" << endl;
		}
		else
		{
			break;
		}
	}

	cout << "请输入密码：" << endl;
	cin >> pwd;
	
	ofs << name << "  " << pwd << " " << endl;
	cout << "添加成功！" << endl;

	//虽然可以检测重复的账号，但是刚添加的账号由于没有更新到容器中，因此不会作检测
	//导致刚加入的用户名，再次添加时依然可以重复，故增加以下语句，
	
	//调用初始化容器接口，重新获取文件中的数据
	this->initVector();

	system("pause");
	system("cls");

	ofs.close();
}

void printDoctor(Doctor_identity &s)
{
	cout << "医生用户名：" << s.i_Name << "\t\t\t密码： " << s.i_Pwd << endl;
}

//查看账号
void The_Manager::showPerson()
{
	this->initVector();
	system("cls");
	cout << "所有医生的账号信息如下：" << endl;
	for_each(vDoc.begin(), vDoc.end(), printDoctor);
	system("pause");
	system("cls");
}


//医生信息基本操作菜单
void The_Manager::showDocAct()
{
	cout << "=======================   医生基本信息操作    =======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 1、添加医生信息                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 2、修改医生信息                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 3、删除医生信息                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 4、查询医生信息                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 5、医生信息保存文件             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 6、返回上一级菜单               |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "请输入您的选择：";
}

//医生基本信息录入
void The_Manager::add_Doc()
{
	system("cls");

	int addNum = 0; //保存用户的输入数量

	while (true)
	{
		cout << "请输入录入医生的数量：" << endl;
		cin >> addNum;

		if (addNum > 0)
		{
			//添加
			//计算添加新空间大小
			int newSize = this->m_DocNum + addNum; //新空间人数 = 原来记录人数+新增人数

			//开辟新空间(动态扩展）
			Doctor** newSpace = new Doctor * [newSize];


			//将原来空间下数据，拷贝到新空间下
			if (this->m_DocArray != NULL) //如果原来的空间不为空
			{
				for (int i = 0; i < this->m_DocNum; i++)
				{
					newSpace[i] = this->m_DocArray[i];
				}
			}


			//批量添加新数据
			for (int i = 0; i < addNum; i++)
			{
				system("cls");
				int id; //医生编号
				string name; //医生姓名
				int dSelect; //部门选择


				cout << "请输入第 " << i + 1 << " 个医生编号" << endl;
				while (true)
				{
					cin >> id;
					bool flag = this->checkDoctorRepeat(id);

					if (flag) //有重复
					{
						cout << "输入的医生编号重复，请重新输入！" << endl;
						cout << "请输入第 " << i + 1 << " 个医生编号" << endl;
					}
					else
					{
						break;
					}
				}

				cout << "请输入第 " << i + 1 << " 个医生姓名" << endl;
				cin >> name;

				cout << "请选择该医生部门:" << endl;
				cout << "1、医务科" << endl;
				cout << "2、人事科" << endl;
				cout << "3、医保办" << endl;

				while (true)
				{
					cin >> dSelect;
					if (dSelect == 1 || dSelect == 2 || dSelect == 3)
					{
						break;
					}
					else
					{
						cout << "选择的医生部门有误，请重新选择！" << endl;
						cout << "请选择该医生部门:" << endl;
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


				//将创建的医生指针，保存到数组中
				newSpace[this->m_DocNum + i] = doctor;
			}

			//释放原有的空间
			delete[] this->m_DocArray;

			//更改新空间的指向
			this->m_DocArray = newSpace;

			//更新新的医生人数
			this->m_DocNum = newSize;

			//更新职工不为空标志
			this->m_DFileIsEmpty = false;

			//提示添加成功
			cout << "成功添加 " << addNum << " 名医生！" << endl;
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

//医生基本信息修改
void The_Manager::Mod_Doc()
{
	system("cls");
	if (this->m_DFileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改医生的编号：" << endl;
		int id;
		cin >> id;

		int ret = this->DIsExist(id);
		if (ret != -1)
		{
			//删除查找到编号的医生
			delete this->m_DocArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到：" << id << "号医生，请输入新医生编号：" << endl;

			while (true)
			{
				cin >> newId;
				bool flag = this->checkDoctorRepeat(newId);

				if (flag) //有重复
				{
					cout << "输入的新医生编号重复，请重新输入！" << endl;
					cout << "查到：" << id << "号医生，请输入新医生编号：" << endl;
				}
				else
				{
					break;
				}
			}

			cout << "请输入新医生姓名：" << endl;
			cin >> newName;

			cout << "请选择该医生部门部门：" << endl;
			cout << "1、医务科" << endl;
			cout << "2、人事科" << endl;
			cout << "3、医保办" << endl;
			
			while (true)
			{
				cin >> dSelect;
				if (dSelect == 1 || dSelect == 2 || dSelect == 3)
				{
					break;
				}
				else
				{
					cout << "选择的医生部门有误，请重新选择！" << endl;
					cout << "请选择该医生部门:" << endl;
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

			//更新数据 到数组中
			this->m_DocArray[ret] = doctor;

			cout << "修改成功！" << endl;
		}
		else
		{
			cout << "修改失败，未找到该医生！" << endl;
		}
	}

	system("pause");
	system("cls");
}

//删除医生信息
void The_Manager::Del_Doc()
{
	system("cls");
	if (this->m_DFileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按照医生编号删除
		cout << "请输入想要删除医生编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->DIsExist(id);
		if (index != -1) //说明医生存在，并且要删除index位置上的医生
		{
			//数据前移
			for (int i = index; i < this->m_DocNum - 1; i++)
			{
				this->m_DocArray[i] = this->m_DocArray[i + 1];
			}
			this->m_DocNum--;  //个更新以下数组中记录的人员个数

			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败！未找到该医生！" << endl;
		}
	}

	system("pause");
	system("cls");
}


//患者挂号信息基本操作菜单
void The_Manager::showPatAct()
{
	cout << "=======================   患者挂号信息操作    =======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 1、添加患者挂号信息             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 2、修改患者挂号信息             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 3、删除患者挂号信息             |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 4、患者挂号信息保存文件         |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 5、返回上一级菜单               |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "请输入您的选择：";
}


//患者挂号信息录入
void The_Manager::add_Pat()
{
	system("cls");

	int addNum = 0; //保存用户的输入数量
	while (true)
	{
		cout << "请输入录入患者的数量：" << endl;
		cin >> addNum;
		if (addNum > 0)
		{
			//添加
			//计算添加新空间大小
			int newSize = this->m_PatNum + addNum; //新空间人数 = 原来记录人数+新增人数

			//开辟新空间(动态扩展）
			Patient** newSpace = new Patient * [newSize];


			//将原来空间下数据，拷贝到新空间下
			if (this->m_PatArray != NULL) //如果原来的空间不为空
			{
				for (int i = 0; i < this->m_PatNum; i++)
				{
					newSpace[i] = this->m_PatArray[i];
				}
			}


			//批量添加新数据
			for (int i = 0; i < addNum; i++)
			{
				system("cls");
				int id; //患者编号
				string name; //医生姓名
				int dSelect; //挂号部门
				int day;
				int month;
				int year;
				int flag = 0;

				cout << "请输入第 " << i + 1 << " 个患者编号" << endl;

				while (true)
				{
					cin >> id;
					bool flag = this->checkPatientRepeat(id);

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

				while (true)
				{
					//	flag = 0;
					cout << "请输入第 " << i + 1 << " 个患者就诊日期（格式：年 月 日，现仅支持2010~2020年）" << endl;
					cin >> year >> month >> day;
					if (year < 2010 || year >2020)
					{
						cout << "挂号年份输入有误，可输入范围为2010~2020年，请重新输入日期" << endl;
						flag++;
					}
					if (month < 1 || month > 12)
					{
						cout << "挂号月份输入有误，可输入范围为1~12月，请重新输入日期" << endl;
						flag++;
					}
					if (day < 1 || day > 31)
					{
						cout << "挂号天份输入有误，可输入范围为1~31日，请重新输入日期" << endl;
						flag++;
					}
					if (month == 2 && day > 29)
					{
						cout << "2月最多为29天，请重新输入日期" << endl;
						flag++;
					}
					if (flag == 0) break;
					flag = 0;

				}
				cout << "请选择患者挂号科室:" << endl;
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


				//将创建的患者指针，保存到数组中
				newSpace[this->m_PatNum + i] = patient;
			}

			//释放原有的空间
			delete[] this->m_PatArray;

			//更改新空间的指向
			this->m_PatArray = newSpace;

			//更新新的医生人数
			this->m_PatNum = newSize;

			//更新职工不为空标志
			this->m_PFileIsEmpty = false;

			//提示添加成功
			cout << "成功添加 " << addNum << " 名患者！" << endl;
			system("pause");
			system("cls");
			break;

		}
		else
		{
			cout << "输入有误,请重新输入！" << endl;
		}
	}
}


//患者基本信息修改
void The_Manager::Mod_Pat()
{
	system("cls");
	if (this->m_PFileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改患者的编号：" << endl;
		int id;
		cin >> id;

		int ret = this->PIsExist(id);
		if (ret != -1)
		{
			//删除查找到编号的患者
			delete this->m_PatArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;
			int newDay;
			int newMonth;
			int newYear;
			int flag = 0;


			cout << "查到：" << id << "号患者，请输入新患者编号：" << endl;
			
			while (true)
			{
				cin >> newId;
				bool flag = this->checkPatientRepeat(newId);

				if (flag) //有重复
				{
					cout << "输入的新患者编号重复，请重新输入！" << endl;
					cout << "查到：" << id << "号患者，请输入新患者编号：" << endl;
				}
				else
				{
					break;
				}
			}

			cout << "请输入新患者姓名：" << endl;
			cin >> newName;

			while (true)
			{
				cout << "请输入患者新就诊日期（格式：年 月 日，现仅支持2010~2020年）" << endl;
				cin >> newYear >> newMonth >> newDay;
				if (newYear < 2010 || newYear >2020)
				{
					cout << "挂号年份输入有误，可输入范围为2010~2020年，请重新输入日期" << endl;
					flag++;
				}
				if (newMonth < 1 || newMonth > 12)
				{
					cout << "挂号月份输入有误，可输入范围为1~12月，请重新输入日期" << endl;
					flag++;
				}
				if (newDay < 1 || newDay > 31)
				{
					cout << "挂号天份输入有误，可输入范围为1~31日，请重新输入日期" << endl;
					flag++;
				}
				if (newMonth == 2 && newDay > 29)
				{
					cout << "2月最多为29天，请重新输入日期" << endl;
					flag++;
				}
				if (flag == 0) break;
				flag = 0;
			}

			cout << "请选择患者科室：" << endl;
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

			//更新数据 到数组中
			this->m_PatArray[ret] = patient;

			cout << "修改成功！" << endl;

		}
		else
		{
			cout << "修改失败，未找到该患者！" << endl;
		}
	}

	system("pause");
	system("cls");
}

//删除患者信息
void The_Manager::Del_Pat()
{
	system("cls");
	if (this->m_PFileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按照患者编号删除
		cout << "请输入想要删除患者编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->PIsExist(id);
		if (index != -1) //说明患者存在，并且要删除index位置上的患者
		{
			//数据前移
			for (int i = index; i < this->m_PatNum - 1; i++)
			{
				this->m_PatArray[i] = this->m_PatArray[i + 1];
			}
			this->m_PatNum--;  //个更新以下数组中记录的人员个数
			//同步更新到文件中
			//this->P_save();

			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败！未找到该患者！" << endl;
		}
	}

	system("pause");
	system("cls");
}



//医生信息查询
void The_Manager::Find_Doc()
{
	system("cls");
	if (this->m_DFileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		showFindDoc();

		int select = 0;
		while (true)
		{
			cin >> select;

			if (select == 1) //按医生编号查找
			{
				system("cls");
				int id;
				cout << "请输入查找的医生编号：" << endl;
				cin >> id;

				int ret = DIsExist(id);
				if (ret != -1)
				{
					cout << "查找成功，编号为" << id << "的医生信息如下:" << endl;
					this->m_DocArray[ret]->ShowInfo();

				}
				else
				{
					cout << "查无此人！" << endl;
				}
				system("pause");
				system("cls");
				showFindDoc();
			}
			else if (select == 2)
			{
				system("cls");
				string name;
				cout << "请输入查找的医生姓名 ：" << endl;
				cin >> name;

				bool flag = false; //查找到的标志
				for (int i = 0; i < m_DocNum; i++)
				{
					if (m_DocArray[i]->m_Name == name)
					{
						cout << "查找成功，医生姓名为: "
							<< m_DocArray[i]->m_Name
							<< " 号的信息如下" << endl;

						flag = true;

						this->m_DocArray[i]->ShowInfo();
					}
				}
				if (flag == false)
				{
					cout << "查找失败，查无此人！" << endl;
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
				cout << "选择有误，请重新选择！" << endl;
				showFindDoc();
			}
		}
	}
}

//统计就诊病人数量
void The_Manager::Cal_Pat()
{
	if (this->m_PFileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
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

					if (select == 1)   //按日统计患者数量
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
										cout << year1[i] << "年" << month1[j] << "月" << day1[g] << "日，病人数量为：" << day2[g] << endl;
									}
								}
							}
						}
						system("pause");
						system("cls");
						showCalPats();
					}
					else if (select == 2)  //按月统计患者数量
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
									cout << year1[i] << "年" << month1[l] << "月，病人数量为： " << month2[l] << "人" << endl;
								}
							}
						}
						system("pause");
						system("cls");
						showCalPats();
					}
					else if (select == 3)  //按季度统计病人数量
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
									cout << year1[i] << "年第" << season1[q] << "季度,病人数量为：" << season2[q] << "人" << endl;
							}
						}
						system("pause");
						system("cls");
						showCalPats();
					}
					else if (select == 4)  //按年统计患者数量
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
								cout << year1[i] << "年，" << "患者数量为：" << year2[i] << "人" << endl;
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
					cout << "选择有误，请重新选择！" << endl;
					showCalPats();
					}
				}
			}

			else if (dSelect == 2)  //按科室统计
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
							dId = "内科";
							cout << dId << "病人数量为：" << did2[i] << "人" << endl;
						}
						else if (did1[i] == 2)
						{
							dId = "外科";
							cout << dId << "病人数量为：" << did2[i] << "人" << endl;
						}
						else if (did1[i] == 3)
						{
							dId = "儿科";
							cout << dId << "病人数量为：" << did2[i] << "人" << endl;
						}
						else
						{
							dId = "妇科";
							cout << dId << "病人数量为：" << did2[i] << "人" << endl;
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
				cout << "选择有误，请重新选择！" << endl;
				showCalPatf();
			}
		}
	}
}

//统计原文件中医生人数
int The_Manager::get_DocNum()
{
	ifstream ifs;
	ifs.open(D_FILENAME, ios::in);  //打开文件 读

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数
		num++;
	}

	return num;
}

//初始化医生文件
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
		//根据不同的部门编号创建不同的对象
		if (dId == 1)   //1、医务科
		{
			doctor = new Doctor(id, name, dId);
		}
		else if (dId == 2)   //2、人事科
		{
			doctor = new Doctor(id, name, dId);
		}
		else  //医保办
		{
			doctor = new Doctor(id, name, dId);
		}

		//存放在数组中
		this->m_DocArray[index] = doctor;
		index++;
	}

	//关闭文件
	ifs.close();
}

//统计原文件中患者人数
int The_Manager::get_PatNum()
{
	ifstream ifs;
	ifs.open(P_FILENAME, ios::in);  //打开文件 读

	int id;
	string name;
	int dId;
	int day;
	int month;
	int year;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> year && ifs >> month && ifs >> day && ifs >> dId)
	{
		//统计人数
		num++;
	}

	return num;
}

//初始化患者文件
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
		//根据不同的部门编号创建不同的对象
		if (dId == 1)        //1、内科
		{
			patient = new Patient(id, name, year, month, day, dId);
		}
		else if (dId == 2)   //2、外科
		{
			patient = new Patient(id, name, year, month, day, dId);
		}
		else if (dId == 3)   //3、妇科
		{
			patient = new Patient(id, name, year, month, day, dId);
		}
		else                 //4、儿科
		{
			patient = new Patient(id, name, year, month, day, dId);
		}

		//存放在数组中
		this->m_PatArray[index] = patient;
		index++;
	}

	//关闭文件
	ifs.close();
}


//保存医生文件
void The_Manager::D_save()
{
	ofstream ofs;
	ofs.open(D_FILENAME, ios::out);  //用输出方式打开文件 -- 写文件

	//将每个人的数据写入文件中
	for (int i = 0; i < this->m_DocNum; i++)
	{
		ofs << this->m_DocArray[i]->m_Id << " "
			<< this->m_DocArray[i]->m_Name << " "
			<< this->m_DocArray[i]->m_Dep << endl;
	}

	//关闭文件
	ofs.close();
	cout << "医生文件保存成功！" << endl;
}

//初始化容器
void The_Manager::initVector()
{
	vDoc.clear();   //确保容器清空状态
	//读取信息 医生
	ifstream ifs;
	ifs.open(FDOCTOR_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
		return;
	}

	Doctor_identity s;
	while (ifs >> s.i_Name && ifs >> s.i_Pwd)
	{
		vDoc.push_back(s);  //把从文件中读取出来的信息储存到容器中
	}

	ifs.close();
}

//保存患者文件
void The_Manager::P_save()
{
	ofstream ofs;
	ofs.open(P_FILENAME, ios::out);  //用输出方式打开文件 -- 写文件

	//将每个人的数据写入文件中
	for (int i = 0; i < this->m_PatNum; i++)
	{
		ofs << this->m_PatArray[i]->m_Id << " "
			<< this->m_PatArray[i]->m_Name << " "
			<< this->m_PatArray[i]->m_Year << " "
			<< this->m_PatArray[i]->m_Month << " "
			<< this->m_PatArray[i]->m_Day << " "
			<< this->m_PatArray[i]->m_Dep << endl;
	}

	//关闭文件
	ofs.close();
	cout << "成功保存入文件！" << endl;
}

//检测添加医生重复 参数：（传入用户名name） 返回值（true代表有重复，false代表无重复）
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

//检测 添加/修改 医生用户重复
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

//检测 添加/修改 患者用户时患者编号重复
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




//展示医生查找操作菜单
void The_Manager::showFindDoc()
{
	cout << "=======================   医生基本信息查找   =======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 1、按医生编号查找               |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 2、按医生姓名查找               |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                 3、返回上一级菜单               |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "请输入您的选择：";
}

//展示统计病人数量操作菜单----第一级
void The_Manager::showCalPatf()
{
	cout << "=======================   统计就诊病人数量   =======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                1、按时间统计病人数量            |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                2、按科室统计病人数量            |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                3、返回上一级菜单                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "请输入您的选择：";
}

//展示统计病人数量操作菜单----第二级
void The_Manager::showCalPats()
{
	cout << "=======================   统计就诊病人数量   =======================" << endl;
	cout << "\t -------------------------------------------------\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                1、按日统计病人数量              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                2、按月统计病人数量              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                3、按季度统计病人数量            |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                4、按年统计病人数量              |\n";
	cout << "\t|                                                 |\n";
	cout << "\t|                5、返回上一级菜单                |\n";
	cout << "\t|                                                 |\n";
	cout << "\t -------------------------------------------------\n";
	cout << "请输入您的选择：";
}

//析构函数
The_Manager::~The_Manager()    //手动释放堆区数据
{
	//释放医生空间
	if (this->m_DocArray != NULL)
	{
		delete[] this->m_DocArray;
		this->m_DocArray = NULL;
	}

	//释放患者空间
	if (this->m_PatArray != NULL)
	{
		delete[] this->m_PatArray;
		this->m_PatArray = NULL;
	}

}