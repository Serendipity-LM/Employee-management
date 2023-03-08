#pragma once
#include<iostream>
#include "worker.h"
using namespace std;
class Manager :public Worker {
public:
    Manager(int Id, string name, int deptId);
    virtual void showInfo();
    virtual string getDeptName();
};

