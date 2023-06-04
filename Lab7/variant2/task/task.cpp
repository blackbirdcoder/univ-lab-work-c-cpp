//  *************************
//  * Laboratory work 7     *
//  * Variant 2             *
//  *************************
//
// Task:
// Create a list of department employees: surname, first name and
// patronymic, number, month of birth. Display information about
// employees who were born in the given months.

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const char* FILE_STORAGE = "Worker.bin";

struct Date {
    int year;
    short month;
    short day;
};

struct Worker {
    char firstName[50];
    char lastName[50];
    char middleName[50];
    Date date;
};

void showWorkers(Worker[], const int);

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Select
void sortWorkers(Worker wrk[], const int sizeWrk)
{
    for (int i = 0; i < sizeWrk - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < sizeWrk; j++)
        {
            if (strcmp(wrk[j].firstName, wrk[minIdx].firstName) == 0)
            {
                minIdx = j;
            }
        }
        swap(wrk[i], wrk[minIdx]);
    }
}


void addWorkerToBinaryFile()
{
    ofstream outFile(FILE_STORAGE, ios::binary | ios::out | ios::app);
    Worker newWorker;

    cin.ignore();
    cout << "FirstName:" << endl;
    cin.getline(newWorker.firstName, 50);
    cout << "LastName:" << endl;
    cin.getline(newWorker.lastName, 50);
    cout << "MiddleName:" << endl;
    cin.getline(newWorker.middleName, 50);
    cout << "Enter year:" << endl;
    cin >> newWorker.date.year;
    cout << "Enter month:" << endl;
    cin >> newWorker.date.month;
    cout << "Enter day:" << endl;
    cin >> newWorker.date.day;

    outFile.write((char*)&newWorker, sizeof(newWorker));
    outFile.close();
}

int readWorkersFromBinaryFile(Worker wrk[])
{
    ifstream inFile(FILE_STORAGE, ios::binary | ios::in);
    if (!inFile)
    {
        cout << "Error no data! First, enter the data of workers!" << endl;
        return 0;
    }
    int num = 0;
    while (inFile.read((char*)&wrk[num], sizeof(Worker)))
    {
        ++num;
    }
    inFile.close();
    showWorkers(wrk, num);
    return num;
}

void showWorkers(Worker wrk[], const int sizeWrk)
{
    for (int i = 0; i < sizeWrk; ++i)
    {
        cout << wrk[i].firstName << " ";
        cout << wrk[i].lastName << " ";
        cout << wrk[i].middleName << " ";
        cout << wrk[i].date.year << "/";
        cout << wrk[i].date.month << "/";
        cout << wrk[i].date.month << "/";
        cout << wrk[i].date.day << endl;
        cout << "---------------" << endl;
    }
}

void saveFilterWorkersIntoTextFile(Worker wrk[], const int sizeWrk)
{
    const char* resultFile = "Worker.txt";
    int numMonth;

    do
    {
        cin.ignore();
        cout << "Enter month [1-12]:" << endl;
        cin >> numMonth;
    }
    while(!(numMonth >= 1 && numMonth <= 12));

    cin.ignore();
    ofstream outFile(resultFile);
    sortWorkers(wrk, sizeWrk);

    for (int i = 0; i < sizeWrk; ++i)
    {
        if ( wrk[i].date.month == numMonth)
        {
            outFile << wrk[i].firstName << " ";
            outFile << wrk[i].lastName << " ";
            outFile << wrk[i].middleName << " ";
            outFile << wrk[i].date.year << " ";
            outFile << wrk[i].date.month << " ";
            outFile << wrk[i].date.day << endl;

            cout << wrk[i].firstName << " ";
            cout << wrk[i].lastName << " ";
            cout << wrk[i].middleName << " ";
            cout << wrk[i].date.year << " ";
            cout << wrk[i].date.month << " ";
            cout << wrk[i].date.day << endl;
        }
    }

    outFile.close();
}

bool presenceCheckFile()
{
    ifstream fileStorage(FILE_STORAGE);
    if (fileStorage.good())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    Worker workers[100];
    int wrkSize = readWorkersFromBinaryFile(workers);;
    int menuWork;
    bool status;
    do
    {
        clearConsole();
        int option;
        cout << "Select function to run:" << endl;
        cout << "[1] Add Worker To Binary File:" << endl;
        cout << "[2] Read Workers From Binary File:" << endl;
        cout << "[3] Save Sorted Workers Into Text File:" << endl;
        cin >> option;
        switch(option)
        {
            case 1:
                addWorkerToBinaryFile();
                break;
            case 2:
                wrkSize = readWorkersFromBinaryFile(workers);
                break;
            case 3:
                status = presenceCheckFile();
                if (status)
                {
                    saveFilterWorkersIntoTextFile(workers , wrkSize);
                }
                else
                {
                    cout << "There is no file with workers. Write to the workers file!" << endl;
                }
                break;
            default:
                cout << "The number is not correct" << endl;
        }
        cout << "Press [0] to exit or any number to continue" << endl;
        cin >> menuWork;
    }
    while (menuWork);
    cout << "Program is finished" << endl;
    return 0;
}
