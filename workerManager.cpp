#include "workerManager.h"
WorkerManager::WorkerManager() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if (!ifs.is_open()) {
        cout << "文件不存在" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        cout << "文件为空" << endl;
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    int num = this->get_EmpNum();
    cout << "员工人数：" << num << endl;
    this->m_EmpNum = num;
    this->m_EmpArray = new Worker * [this->m_EmpNum];   //new Worker * [this->m_EmpNum] 返回的是Worker 类型的指针的指针，数量有this->m_EmpNum个
    //将文件中的数据存放在数组中。
    this->init_Emp();
    //for (int i = 0; i < this->m_EmpNum;i++) {
    //    cout << "职工编号：" << this->m_EmpArray[i]->m_ID
    //        << "\t职工姓名：" << this->m_EmpArray[i]->name
    //        << "\t部门编号： " << this->m_EmpArray[i]->m_deptID << endl;
    //}
}
void WorkerManager::save() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (int i = 0; i < this->m_EmpNum;i++) {
        ofs << this->m_EmpArray[i]->m_ID << " "
            << this->m_EmpArray[i]->name << " "
            << this->m_EmpArray[i]->m_deptID << endl;
    }
    ofs.close();
}
void WorkerManager::show_Emp() {
    if (this->m_FileIsEmpty) {
        cout << "文件不存在或者记录为空." << endl;
    }
    else {
        for (int i = 0; i < this->m_EmpNum;i++) {
            this->m_EmpArray[i]->showInfo();
        }
    }
    system("pause");
    system("cls");
}
int WorkerManager::get_EmpNum() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int ID;
    string name;
    int deptID;
    int num = 0;
    while (ifs >> ID && ifs >> name && ifs >> deptID) {
        num++;
    }
    return num;
}
void WorkerManager::AddEmp() {
    cout << "请输入添加的员工数量：" << endl;
    int addNum = 0;
    cin >> addNum;
    if (addNum>0) {
        int newSize = this->m_EmpNum + addNum;
        Worker** newSpace= new Worker* [newSize];
        if (this->m_EmpArray!=NULL) {
            for (int i = 0; i < this->m_EmpNum;i++) {
                newSpace[i] = this->m_EmpArray[i];        //数组元素是Worker * ， 即Worker指针
            }
        }
        for (int i = 0; i < addNum; i++) {
            int id;
            string name;
            int answer;
            int deptSelect;
            cout << "请输入第  " << i + 1 << " 个新员工编号: " << endl;
            cin >> id;
            answer = this->isExist(id);
            while (answer!= -1) {
                cout << "编号已有，请重新输入第  " << i + 1 << " 个新员工编号: " << endl;
                cin >> id;
                answer = this->isExist(id);
            }
            cout << "请输入第  " << i + 1 << " 个新员工姓名: " << endl;
            cin >> name;
            cout << "请选择该员工岗位： " << endl;
            cout << "1 ,  普通职工" << endl;
            cout << "2 ,  经理" << endl;
            cout << "3 ,  老板" << endl;
            cin >> deptSelect;
            Worker* worker = NULL;
            switch (deptSelect)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            default:
                break;
            }
            newSpace[this->m_EmpNum + i] = worker;
        }
        delete[] this->m_EmpArray;    // m_EmpArray是指针的指针,前面要加[]
        this->m_EmpArray = newSpace;
        this->m_EmpNum = newSize;
        this->m_FileIsEmpty = false;
        cout << "添加成功了" << addNum << "名职工。" << endl;
        this->save();
    }
    else {
        cout << "输入有误" << endl;
    }
    system("pause");
    system("cls");
}
void WorkerManager::ShowMenu() {
    cout << "*******************************************" << endl;
    cout << "*******   欢迎使用员工管理系统    *********" << endl;
    cout << "*******    0.     退出管理程序    *********" << endl;
    cout << "*******    1.     增加员工信息    *********" << endl;
    cout << "*******    2.     显示员工信息    *********" << endl;
    cout << "*******    3.     删除离职员工    *********" << endl;
    cout << "*******    4.     修改员工信息    *********" << endl;
    cout << "*******    5.     查找员工信息    *********" << endl;
    cout << "*******    6.     按照编号排序    *********" << endl;
    cout << "*******    7.     清空所有文档    *********" << endl;
    cout << "*******************************************" << endl;
    cout << endl;
}
void WorkerManager::ExitSystem() {
    cout << "欢迎下次使用！" << endl;
    system("pause");
    exit(0);
}
void WorkerManager::init_Emp() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int ID;
    string name;
    int deptID;
    int index = 0;
    while (ifs >> ID && ifs >> name && ifs >> deptID) {
        Worker* worker = NULL;
        if (deptID==1) {
            worker = new Employee(ID, name, 1);
        }
        else if (deptID == 2) {
            worker = new Manager(ID, name, 2);
        }
        else {
            worker = new Boss(ID, name, 3);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    ifs.close();
}
int WorkerManager::isExist(int id) {
    int index = -1;
    for (int i = 0; i < this->m_EmpNum;i++) {
        if (this->m_EmpArray[i]->m_ID==id) {
            index = i;
            break;
        }
    }
    return index;
}
void WorkerManager::Del_Emp() {
    if (this->m_FileIsEmpty) {
        cout << "文件不存在或者记录为空." << endl;
    }
    else {
        cout << "请输入你要删除的员工编号：" << endl;
        int id = 0;
        cin >> id;
        int index= this->isExist(id);
        if (index!=-1) {
            for (int i = index; i < this->m_EmpNum - 1;i++) {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--;
            this->save();
            cout << "删除成功！" << endl;
        }
        else {
            cout << "不存在此编号员工" << endl;
        }
    }
    system("pause");
    system("cls");
}
void WorkerManager::Modify_Emp() {
    if (this->m_FileIsEmpty) {
        cout << "文件不存在或者记录为空." << endl;
    }
    else {
        cout << "请输入你要修改的员工编号：" << endl;
        int id = 0;
        cin >> id;
        int index = this->isExist(id);
        if (index != -1) {
            delete this->m_EmpArray[index];
            int newID = 0;
            string newName = "";
            int newDeptID = 0;
            cout << "查到： " << id << " 号职工，请输入新员工工号：" << endl;
            cin >> newID;
            cout << "请输入新的姓名：" << endl;
            cin >> newName;
            cout << "请选择该员工岗位： " << endl;
            cout << "1 ,  普通职工" << endl;
            cout << "2 ,  经理" << endl;
            cout << "3 ,  老板" << endl;
            cin >> newDeptID;
            Worker* worker = NULL;
            switch (newDeptID)
            {
            case 1:
                worker = new Employee(newID, newName, 1);
                break;
            case 2:
                worker = new Manager(newID, newName, 2);
                break;
            case 3:
                worker = new Boss(newID, newName, 3);
                break;
            default:
                break;
            }
            this->m_EmpArray[index] = worker;
            cout << "修改成功!" << endl;
            this->save();
        }
        else {
            cout << "不存在此编号员工" << endl;
        }
    }
    system("pause");
    system("cls");
}
void WorkerManager::Find_Emp() {
    if (this->m_FileIsEmpty) {
        cout << "文件不存在或者记录为空." << endl;
    }
    else {
        cout << "请输入查找的方式： " << endl;
        cout << "1：按照员工编号查找" << endl;
        cout << "2：按照员工姓名查找" << endl;
        int select;
        cin >> select;
        if (select==1) {
            cout << "请输入你要查找的职工编号：" << endl;
            int id = 0;
            cin >> id;
            int index = this->isExist(id);
            if (index != -1) {
                cout << "查找成功！该职工的信息如下：" << endl;
                this->m_EmpArray[index]->showInfo();
            }
            else {
                cout << "不存在此编号员工" << endl;
            }
        }
        else  {
            cout << "请输入你要查找的职工姓名：" << endl;
            string s;
            cin >> s;
            bool flag=false;
            for (int i = 0; i < this->m_EmpNum;i++) {
                if (this->m_EmpArray[i]->name==s) {
                    cout << "查找成功，职工编号为：" << this->m_EmpArray[i]->m_ID<<"，信息如下：" << endl;
                    this->m_EmpArray[i]->showInfo();
                    flag = true;
                }
            }
            if (flag==false) {
                cout << "不存在此名称员工" << endl;
            }
        }
    }
    system("pause");
    system("cls");
}
void WorkerManager::Sort() {
    if (this->m_FileIsEmpty) {
        cout << "文件不存在或者记录为空." << endl;
        system("pause");
        system("cls");
    }
    else {
        cout << "请选择排序方式：" << endl;
        cout << "1，          按照职工号进行升序。" << endl;
        cout << "其他字符数字，按照职工号进行降序。" << endl;
        int select;
        cin >> select;
        if (select==1) {
            for (int i = 1; i < this->m_EmpNum; i++) {
                for (int j = this->m_EmpNum - 1; j >= i; j--) {
                    if (this->m_EmpArray[j]->m_ID < this->m_EmpArray[j - 1]->m_ID) {
                        int temp = this->m_EmpArray[j - 1]->m_ID;
                        this->m_EmpArray[j - 1]->m_ID = this->m_EmpArray[j]->m_ID;
                        this->m_EmpArray[j]->m_ID = temp;
                    }
                }
            }
        }
        else {
            for (int i = 1; i < this->m_EmpNum; i++) {
                for (int j = this->m_EmpNum - 1; j >= i; j--) {
                    if (this->m_EmpArray[j]->m_ID > this->m_EmpArray[j - 1]->m_ID) {
                        int temp = this->m_EmpArray[j - 1]->m_ID;
                        this->m_EmpArray[j - 1]->m_ID = this->m_EmpArray[j]->m_ID;
                        this->m_EmpArray[j]->m_ID = temp;
                    }
                }
            }
        }
        cout << "排序成功！排序结果为：" << endl;
        this->save();
        this->show_Emp();
    }
}
void WorkerManager::Clean() {
    cout << "确定清空? " << endl;
    cout << "1，确认" << endl;
    cout << "2，返回" << endl;
    int select = 0;
    cin >> select;
    if (select==1) {
        ofstream ofs(FILENAME, ios::trunc);   //删除文件后再重新创建
        ofs.close();
        if (this->m_EmpArray != NULL) {
            for (int i = 0; i < this->m_EmpNum; i++) {
                if (this->m_EmpArray[i] != NULL) {
                    delete this->m_EmpArray[i];
                    this->m_EmpArray[i] = NULL;
                }
            }
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty=true;
        }
        cout << "清空成功！" << endl;
    }
    system("pause");
    system("cls");
}
WorkerManager::~WorkerManager() {
    if (this->m_EmpArray!=NULL) {
        for (int i = 0; i < this->m_EmpNum; i++) {
            if (this->m_EmpArray[i] != NULL) {
                delete this->m_EmpArray[i];
            }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}

