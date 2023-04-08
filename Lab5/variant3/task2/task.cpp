#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctime>


using namespace std;

struct Report {
    string date;
    unordered_map<int, int> items;
};

struct Result {
    int code;
    int amt;
    vector<int> same;
};

vector<Report> generateReports()
{
    vector<Report> reports;
    vector<int> code = {111, 222, 333, 444, 555};
    srand(time(nullptr));
    for (int i = 0; i < code.size(); i++)
    {
        Report report;
        report.date = "1" + to_string(i) + ".11.2012";
        for (int j = 0; j < code.size(); j++)
        {
            report.items[code[j]] = rand() % 51;
        }
        reports.push_back(report);
    }
    return reports;
}

Result reportAnalysis(const vector<Report>& reports)
{
    vector<int> code;
    Result res = {0, 0, vector<int>()};

    for (const auto& rept : reports)
    {
        for (const auto& item : rept.items)
        {
            code.push_back(item.first);
        }
        break;
    }

    unordered_map<int, int> count;
    for (const auto& crtCode : code)
    {
        for (const auto& rept : reports)
        {
            auto iter = rept.items.find(crtCode);
            if (iter != rept.items.end())
            {
                count[crtCode] += iter->second;
            }
        }
    }

    for (const auto& items : count)
    {
        int crtKey = items.first;
        int crtValue = items.second;
        if (res.code == 0)
        {
            res.code = crtKey;
            res.amt = crtValue;
        }
        else
        {
            if (res.amt < crtValue)
            {
                res.code = crtKey;
                res.amt = crtValue;
                res.same.clear();
            } else if (res.amt == crtValue)
            {
                res.same.push_back(crtKey);
            }
        }
    }
    return res;
}

void outReport(const vector<Report>& reports, const Result& result)
{
    vector<string> date;
    cout << "=== List of goods and their quantity ===" << endl;
    for (const auto& crtRepo : reports)
    {
        date.push_back(crtRepo.date);
        cout << "Date: " << crtRepo.date << endl;
        for (const auto& items : crtRepo.items)
        {
            cout << "Item: " << items.first << " Quantity: " << items.second << endl;
        }
        cout << "------------------------------" << endl;
    }

    cout << "For the period from " << date.front() << " to " << date.back() << endl;
    cout << "The most common prohibited items:" << endl;
    cout << "Item: " << result.code << " Quantity: " << result.amt << endl;
    if (!result.same.empty())
    {
        cout << "There were also items:" << endl;
        for (const auto& code : result.same)
        {
            cout << "Item: " << code << " Quantity: " << result.amt << endl;
        }
    }
}

int main()
{
    vector<Report> reports = generateReports();
    Result freq = reportAnalysis(reports);
    outReport(reports, freq);
    return 0;
}