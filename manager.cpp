#include "manager.h"
using namespace std;

Manager::Manager(int Id, string name, int deptId) {
    this->m_ID = Id;
    this->name = name;
    this->m_deptID = deptId;
}
void Manager::showInfo() {
    cout << "职工编号：" << this->m_ID
        << "\t职工姓名：" << this->name
        << "\t\t岗位： " << this->getDeptName()
        << "\t岗位职责：完成老板交代的任务。" << endl;
}
string Manager::getDeptName() {
    return string("经理");
}
