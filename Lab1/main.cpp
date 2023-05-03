#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include "Employee.hpp"

using namespace std;

void displayTxtFile(string fileName) {

    ifstream in;
    string line;
    in.open(fileName, ios::binary);
    if (in.is_open()) {
        while (!in.eof()) {
            getline(in, line);
            cout << line << endl;
        }
    }
}

void displayBinFile(string fileName) {
    Employee emp;
    vector<Employee> employees;
    ifstream in;

    in.open(fileName, ios::binary);
    if (in.is_open()) {
        do {
            in.read((char*)&emp, sizeof(Employee));
            employees.push_back(emp);
        } while (!in.eof());
        employees.pop_back();
    }
    for (Employee e : employees)
        cout << "num: " << e.num <<
        "; name: " << e.name <<
        "; hours:" << e.hours << endl;
}



int main()
{
    STARTUPINFO si = { 0 };                // задает параметры окна, созданного новым процессом
    PROCESS_INFORMATION pi = { 0 };                // содержит информацию о созданом процессе и его первичном потоке
    DWORD excode;                    // код при выходе из процесса
    string binFileName;               // имя бинарного файла, куда будут сериализоваться рабочие
    string txtFileName;               // имя файла, где содержится отчет по сотрудникам
    string numOfEntries;              // число записей в бинарник
    string payPerHour;                // оплата за час


    cout << "Main process has been started" << endl;
    cout << "Input filename: "; cin >> binFileName;
    cout << "Input number of entiries: "; cin >> numOfEntries;


    string cmdCreatorRequest = string("Creator.exe") + " " + binFileName + " " + numOfEntries;
    wstring creatorCmdLine(cmdCreatorRequest.begin(), cmdCreatorRequest.end());
    LPWSTR lpwCreatorCmdLine = &creatorCmdLine[0];
    BOOL creatorHasCreated = CreateProcess(NULL,
        lpwCreatorCmdLine,
        NULL,
        NULL,
        TRUE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi);
    if (!creatorHasCreated)
        cout << "Unable to create creator proccess" << endl;
    WaitForSingleObject(pi.hProcess, INFINITE);


    displayBinFile(binFileName);


    cout << "Enter report filename: "; cin >> txtFileName;
    cout << "Enter pay per hour: "; cin >> payPerHour;


    string cmdReporterRequest = string("Reporter.exe") + " " + binFileName + " " + txtFileName + " " + payPerHour;
    wstring reporterCmdLine(cmdReporterRequest.begin(), cmdReporterRequest.end());
    LPWSTR lpwReporterCmdLine = &reporterCmdLine[0];
    BOOL reporterHasCreated = CreateProcess(NULL,
        lpwReporterCmdLine,
        NULL,
        NULL,
        TRUE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi);
    if (!reporterHasCreated)
        cout << "Unable to create reporter process" << endl;
    WaitForSingleObject(pi.hProcess, INFINITE);
    cout << "Reporter process has been terminated" << endl;

    displayTxtFile("report.txt");


    _getch();
    GetExitCodeProcess(pi.hProcess, &excode);

    if (excode != STILL_ACTIVE) {
        cout << "Done" << endl;
    }
    else {
        cout << "Process still running" << endl;
    }

    cout << "Main process has been terminated" << endl;
    _getch();

}

