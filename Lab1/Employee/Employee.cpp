#include "Employee.hpp"

Employee::Employee() {
    this->num = 0;
    this->hours = 0.;
}

Employee::Employee(int _num, const char* _name, double _hours) {
    this->num = _num;
    for (int i = 0; i < 10; i++)
        this->name[i] = _name[i];
    this->hours = _hours;
}
