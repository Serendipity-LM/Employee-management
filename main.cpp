#include<iostream>
#include<fstream>
#include "workerManager.h"
using namespace std;
//#include "worker.h"
//#include "employee.h"
//#include "manager.h"
//#include "boss.h"
int main() {
    //Worker* worker = NULL;
    //worker = new Employee(1, "张三", 1);
    //worker->showInfo();
    //delete worker;
    //worker = new Manager(2, "李四", 2);
    //worker->showInfo();
    //delete worker;
    //worker = new Boss(3, "王二", 3);
    //worker->showInfo();
    //delete worker;
    WorkerManager wm;
    int choice = 0;
    while (true) {
        wm.ShowMenu();
        cout << "请输入您的选择：  " << endl;
        cin >> choice;
        switch (choice)
        {
        case 0:
            wm.ExitSystem();
            break;
        case 1:
            wm.AddEmp();
            break;
        case 2:
            wm.show_Emp();
            break;
        case 3:
            wm.Del_Emp();
            break;
        case 4:
            wm.Modify_Emp();
            break;
        case 5:
            wm.Find_Emp();
            break;
        case 6:
            wm.Sort();
            break;
        case 7:
            wm.Clean();
            break;
        default:
            system("pause");
            system("cls");
            break;
        }
    }
    
    system("pause");
    return 0;
}
