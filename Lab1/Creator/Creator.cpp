#include <iostream>
#include <fstream>
#include <string>
#include "Employee.hpp"
#include "Windows.h"

using namespace std;

int main(int argc, char* argv[])
{
    Employee emp;
    ofstream out;
    string binFileName = argv[1];
    int NumOfEntries = stoi(argv[2]);

    cout << "Creator process has started" << endl;
    out.open(binFileName, std::ios::app | std::ios::binary);
    if (out.is_open()) {
        for (int i = 0; i < NumOfEntries; i++) {
            cout << "Enter employee " << i + 1 << " info: " << endl;
            cout << "Enter num: "; cin >> emp.num;
            cout << "Enter name: "; cin >> emp.name;
            cout << "Enter hours: "; cin >> emp.hours;
            out.write((char*)&emp, sizeof(Employee));
        }
    }
    out.close();
    cout << "Creator process is completed" << endl;
}