#pragma once
#include<iostream>
#include "worker.h"
using namespace std;
class Employee :public Worker {
public:
    Employee(int Id, string name, int deptId);
    virtual void showInfo();
    virtual string getDeptName();
};
