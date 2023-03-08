#pragma once
#include<iostream>
#include "worker.h"
using namespace std;
class Boss :public Worker {
public:
    Boss(int Id, string name, int deptId);
    virtual void showInfo();
    virtual string getDeptName();
};
