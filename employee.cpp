#include "employee.h"
using namespace std;

Employee::Employee(int Id, string name, int deptId) {
    this->m_ID = Id;
    this->name = name;
    this->m_deptID = deptId;
}
void Employee::  showInfo() {
    cout << "职工编号：" << this->m_ID
        << "\t职工姓名：" << this->name
        << "\t\t岗位： " << this->getDeptName()
        << "\t岗位职责：完成经理交代的任务。" << endl;
}
string Employee::  getDeptName() {
    return string("员工");
}
