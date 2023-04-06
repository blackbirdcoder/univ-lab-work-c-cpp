#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Company {
    string name;
    int profit;
    int salary;
};

Company* createCompanies(string names[], int size) {
    Company* companies = new Company[size];
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        int profit = rand() % 9001 + 1000;
        companies[i] = { names[i], profit, profit / 2 };
    }
    return companies;
}

void report(Company comps[], int size) {

    // sorted
    for (int initIdx = 0; initIdx < size - 1; initIdx++) {
        int rememIdx = initIdx;
        for (int resIdx = initIdx + 1; resIdx < size; resIdx++) {
            if (comps[resIdx].profit > comps[rememIdx].profit) {
                rememIdx = resIdx;
            }
        }
        Company tmp = comps[initIdx];
        comps[initIdx] = comps[rememIdx];
        comps[rememIdx] = tmp;
    }

    cout << "List of companies under audit:" << endl;
    for (int idx = 0; idx < size; idx++)
    {
        cout << idx + 1 << ") Name: " << comps[idx].name << " Profit: "
        << comps[idx].profit << " Salary: " << comps[idx].salary << endl;
    }
    cout << endl << "*** The most successful three companies ***" << endl;
    for (int idx = 0; idx < 3; idx++)
    {
        cout << string(50, '-') << endl;
        cout << idx + 1 << ") Name: " << comps[idx].name << " Profit: "
        << comps[idx].profit << " Salary: " << comps[idx].salary << endl;
    }
    cout << string(50, '-') << endl;
}


int main() {
    string company_names[] = {  "NexaCorp", "Synthetix", "Cybrospace",
                                "NeoCypher", "OmegaTech", "Dynamics" };
    int size = sizeof(company_names) / sizeof(company_names[0]);
    Company* companies_set = createCompanies(company_names, size);
    report(companies_set, size);
    delete[] companies_set;
    return 0;
}