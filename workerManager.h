#pragma once
#include<iostream>
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
#include<fstream>
#define FILENAME "empFile.txt"
using namespace std;
class WorkerManager {
public:
    WorkerManager();
    void ShowMenu();
    void ExitSystem();
    void AddEmp();
    void save();
    int get_EmpNum();
    void show_Emp();
    void init_Emp();
    void Del_Emp();
    void Modify_Emp();
    void Find_Emp();
    void Sort();
    void Clean();
    int isExist(int id);
    ~WorkerManager();
    bool m_FileIsEmpty;
    int m_EmpNum;
    Worker** m_EmpArray;
};
