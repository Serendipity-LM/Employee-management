#include "boss.h"
using namespace std;

Boss::Boss(int Id, string name, int deptId) {
    this->m_ID = Id;
    this->name = name;
    this->m_deptID = deptId;
}
void Boss::showInfo() {
    cout << "职工编号：" << this->m_ID
        << "\t职工姓名：" << this->name
        << "\t\t岗位： " << this->getDeptName()
        << "\t岗位职责：监督所有人工作。" << endl;
}
string Boss::getDeptName() {
    return string("老板");
}
