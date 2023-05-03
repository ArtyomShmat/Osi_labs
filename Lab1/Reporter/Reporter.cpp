#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "Employee.hpp"
#include "Windows.h"

using namespace std;

int main(int argc, char* argv[])
{
    Employee emp;
    ifstream in;
    ofstream out;
    vector<Employee> employees;
    string binFileName = argv[1];
    string reportFileName = argv[2];
    int payPerHour = stod(argv[3]);

    cout << "Reporter process has started" << endl;

    in.open(binFileName, ios::binary);
    if (in.is_open()) {
        do {
            in.read((char*)&emp, sizeof(Employee));
            employees.push_back(emp);
        } while (!in.eof());
        employees.pop_back();
    }
    in.close();

    out.open(reportFileName);
    if (out.is_open()) {
        out << setiosflags(ios::left);
        out << "-------------------Report according to " << reportFileName << "-------------------" << endl;
        cout << endl;
        out << setw(20) << "Num" << setw(20) << "Name" <<
            setw(20) << "Hours" << setw(20) << "Salary" << endl;
        cout << "Creating report";
        for (Employee e : employees) {
            out << setw(20) << e.num << setw(20) << e.name << setw(20) << e.hours << setw(20) <<
                e.hours * payPerHour << endl;
            cout << ".";
        }
    }
    out.close();
    cout << endl << "Reporter process is completed" << endl;
}
