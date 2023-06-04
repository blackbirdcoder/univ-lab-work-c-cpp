//  *************************
//  * Laboratory work 9     *
//  * Variant 2             *
//  *************************
//
// Task: The application system for production of products

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

const std::string FILE_OUT = "invoice.txt";
const std::string FILE_RESOURCE = "product.txt";
const int QUANTITY_PRODUCT = 2;
const int COLOR_SWATCHES = 2;

struct Color {
    std::string swatches[COLOR_SWATCHES];
};

struct Furniture {
    std::string name;
    std::string size;
    Color colors;
};

struct Order {
    Furniture furniture;
    std::string color;
};

class Manager {
private:
    Furniture furniture[QUANTITY_PRODUCT];
    int productSize;
public:
    bool makeProduct() {
        bool status = false;
        int counterRec = 0;
        std::ifstream resourceFile(FILE_RESOURCE);
        if (!resourceFile) {
            return status;
        } else {
            while (resourceFile
            >> furniture[counterRec].name
            >> furniture[counterRec].size
            >> furniture[counterRec].colors.swatches[0]
            >> furniture[counterRec].colors.swatches[1]) {
                counterRec++;
            }
            resourceFile.close();
            if (furniture[0].name.length()) {
                status = true;
                productSize = counterRec;
            }
        }
        return status;
    }
    void showProduct() {
        for (int i = 0; i < productSize; ++i) {
            std::cout
            << "---- Furniture " << i + 1 << " ----\n"
            << "Type: " << furniture[i].name << "\n"
            << "Size: " << furniture[i].size << "\n"
            << "Color: " << furniture[i].colors.swatches[0]
            << " " << furniture[i].colors.swatches[1] << "\n"
            << "-------------------"
            << std::endl;
        }
    }

    Furniture getProduct(int position) {
        return furniture[position - 1];
    }

    int getQuantityProducts() {
        return productSize;
    }

    void showColors(Furniture& refFurniture) {
        std::string* colorsPointer = refFurniture.colors.swatches;
        for (int i = 0; i < COLOR_SWATCHES; ++i) {
            std::cout << i + 1 << ")" << *colorsPointer++ << std::endl;
        }
    }

    void payOut(std::vector<std::map<std::string, std::string>>& refBlanks) {
        for (auto& blank : refBlanks) {
            blank["price"] = std::to_string(stoi(blank["making"]) + stoi(blank["ready"]) * 10);
        }
    }
};

class Manufactory {
private:
    std::vector<std::map<std::string, std::string>> blanks;
public:
    Manufactory(std::vector<Order>& refOrders)
    {
        std::map<std::string, std::string> blank;
        srand(time(0));
        for (auto& order : refOrders)
        {
            int numRand = rand() % (1 - 20 + 1) + 1;
            blank["type"] = order.furniture.name;
            blank["size"] = order.furniture.size;
            blank["color"] = order.color;
            blank["making"] = std::to_string(numRand);
            blank["ready"] = std::to_string(numRand + 1);
            blanks.push_back(blank);
        }
    }

    std::vector<std::map<std::string, std::string>> getBlanks() {
        return blanks;
    }
};

class Invoice {
public:
    Invoice(std::vector<std::map<std::string, std::string>>& refBlanks) {
        std::ofstream outData;
        outData.open(FILE_OUT);
        for (auto& blank : refBlanks) {
            outData
            << "=============== Blank ===============\n"
            << "Product name: " << blank["type"] << "\n"
            << "Size and color: " << blank["size"] << " "
            << blank["color"] << "\n"
            << "Time to manufacture: " << blank["making"] << "\n"
            << "Shop day: " << blank["ready"] << "\n"
            << "PRICE: " << blank["price"] << " $" << "\n"
            << "=============== ***** ===============\n";
        }
        outData.close();
    }
};

int main() {
    char answer;
    int userResponse;
    int quantityProducts;
    std::vector<Order> orders;
    Manager manager;
    bool statusMake = manager.makeProduct();
    if (!statusMake) {
        std::cout << "Unable to create products. Check the file!\n";
        return 1;
    }
    std::cout << "**** Welcome to the world of furniture ****\n";
    while (true) {
        std::cout << "Would you like to order furniture? [Y/N]>";
        std::cin >> answer;
        if (toupper(answer) == 'Y') {
            manager.showProduct();
            while(true) {
                std::cout
                    << "Enter [0] to exit\n"
                    << "Choose furniture number> ";
                std::cin >> userResponse;
                if (userResponse == 0) {
                    break;
                }
                quantityProducts = manager.getQuantityProducts();
                if (userResponse <= quantityProducts) {
                    Furniture selectFurniture = manager.getProduct(userResponse);
                    manager.showColors(selectFurniture);
                    std::cout
                    << "Enter [0] to exit\n"
                    << "Choose a color by entering its number> ";
                    std::cin >> userResponse;
                    if (userResponse == 0) {
                        break;
                    }
                    Order order;
                    order.furniture = selectFurniture;
                    order.color = selectFurniture.colors.swatches[userResponse - 1];
                    orders.push_back(order);
                    break;
                } else {
                    std::cout << "[!] There is no such furniture number\n";
                }
            }
        } else if (toupper(answer) == 'N')  {
            break;
        }
    }
    if (!orders.empty()) {
        Manufactory mainManufactory(orders);
        std::vector<std::map<std::string, std::string>> blanks = mainManufactory.getBlanks();
        manager.payOut(blanks);
        Invoice invoice(blanks);
        std::cout
        << "Thank you!\n"
        << "Receipt issued see file " << FILE_OUT
        << std::endl;
    } else {
        std::cout << "Goodbye\n";
    }

    return 0;
};




