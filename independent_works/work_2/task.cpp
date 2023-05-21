// Work 2 (4)
// Practical task:
// This is a rectangular matrix. Determine the number of negatives
//elements in those rows that contain at least one zero element;

#include <vector>
#include <algorithm>
#include <iostream>
#include <map>


const std::vector<std::vector<int>> MTX = {
        {1, 2, 3, 5},
        {-1, 2, 0, -1},
        {0, -4, -4, -2},
        {1, 2, 1, 5},
};


std::vector<std::map<std::string, int>> negativeElementsSearch(const std::vector<std::vector<int>>& matrix, int num)
{
    std::vector<std::map<std::string, int>> result;
    std::map<std::string, int> report;
    int indexCounter = 0;

    for (const auto & elem : matrix)
    {
        int countNegative = 0;
        auto p = std::find(elem.begin(), elem.end(), num);
        if (p != elem.end())
        {
            for (int i = 0; i < matrix.size(); ++i)
            {
                int item = matrix[indexCounter][i];
                if (item < 0)
                {
                    ++countNegative;
                }
            }
            report= {{"index", indexCounter}, {"negative", countNegative}};
            result.push_back(report);
        }
        ++indexCounter;
    }

    return result;
}

void showReport(std::vector<std::map<std::string, int>>& elems)
{
    std::cout << "--- Report ---" << std::endl;
    std::cout << "[!] Warn: Row count starts from zero!" << std::endl;
    for (auto& item : elems)
    {
        std::cout << "In a matrix in a row:";
        std::cout << item["index"] << std::endl;
        std::cout << "Total negative numbers:";
        std::cout << item["negative"] << std::endl;
        std::cout << "---" << std::endl;
    }
}


int main()
{
    std::vector<std::map<std::string, int>> result = negativeElementsSearch(MTX, 0);
    showReport(result);
    return 0;
}