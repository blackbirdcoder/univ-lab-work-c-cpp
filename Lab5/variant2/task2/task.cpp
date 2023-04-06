//  *************************
//  * Laboratory work 5     *
//  * Variant 2             *
//  * Task 2                *
//  *************************

//Create a document that stores information on the assortment
//grocery items in the store: store name, product code, quantity of this product, price per
//kilogram. Sort stores for wholesale purchase of a given product according to its price

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int numProducts = 5;
const int numShops = 4;
const int initProductCode = 1000;
const int optionsScreen = 1;
const int optionsFind = 2;
const int optionsOut = 3;

string productNames[numProducts] = {"apple", "pear", "grape", "peach", "plum"};
string shopNames[numShops] = {"mastershop", "lastshop", "firstshop", "doshop"};

struct Product {
    string name;
    int code;
    int quantity;
    int price;
};

struct Shop {
    string name;
    Product products[numProducts];
};

struct ProductData {
    string name;
    Shop store;
    int low;
    int quantity;
};

struct Option {
    int screen;
    int find;
    int out;
};

Option options = {optionsScreen, optionsFind, optionsOut};

void buildFoodPackages(Product* products, int numProducts, int srd) {
    srand(srd);
    for (int i = 0; i < numProducts; i++) {
        products[i].name = productNames[i];
        products[i].code = initProductCode + i;
        products[i].quantity = rand() % 91 + 10;
        products[i].price = rand() % 200 + 1;
    }
}

void buildShops(Shop* shops, int num_shops, Product* products, int numProducts)
{
    for (int i = 0; i < num_shops; i++) {
        shops[i].name = shopNames[i];
        int tme = time(nullptr) + i;
        buildFoodPackages(shops[i].products, numProducts ,tme);
    }
}

void screenShop(Shop* shops, int numShops, int numProducts) {
    for (int i = 0; i < numShops; i++) {
        cout << "--------------------" << endl;
        cout << "Shop: " << shops[i].name << endl;
        cout << "Products:" << endl;
        cout << "Name\t\t | Code\t\t | Quantity\t\t\t | Price (kilo) $\t\t\t |" << endl;
        for (int j = 0; j < numProducts; j++) {
            cout << shops[i].products[j].name << "\t\t | "
                 << shops[i].products[j].code << "\t\t | "
                 << shops[i].products[j].quantity << "\t\t\t\t | "
                 << shops[i].products[j].price << "\t\t\t\t\t |" << endl;
        }
    }
}


void interactionStore(Shop* shops, int numShops, vector<string> prodNames) {
    cout << "****************************************" << endl;
    while (true) {
        cout << "Welcome to Shops" << endl;
        cout << "Menu:" << endl;
        cout << options.screen << ") Shops on screen" << endl;
        cout << options.find << ") Find the cheapest item" << endl;
        cout << options.out << ") Exit shops" << endl;

        int answer;
        while (true) {
            cout << "Select menu item: ";
            if (!(cin >> answer)) {
                cin.clear();
//                cin.ignore(numeric_limits<streamsize>::max(), 'endl');
                cout << "No such menu item available" << endl;
                continue;
            }
            if (answer == options.screen || answer == options.find || answer == options.out) {
                break;
            }
            cout << "No such menu item available" << endl;
        }

        if (answer == options.screen) {
            screenShop(shops, numShops, numProducts);
        } else if (answer == options.find) {
            cout << "Available items in stock: ";
            for (auto name: prodNames) {
                cout << name << "; ";
            }
            cout << endl;

            string itemName;
            while (true) {
                cout << "Please enter an item in stock: ";
                cin >> itemName;
                if (find(prodNames.begin(), prodNames.end(), itemName) != prodNames.end()) {
                    break;
                }
                cout << "This item is out of stock" << endl;
            }

            ProductData pdtData;
            pdtData.name = itemName;
            int low = 0;
            for (int i = 0; i < numShops; i++)
            {
                for (int j = 0; j < numProducts; j++)
                {
                    if (shops[i].products[j].name == itemName)
                    {
                        if (low == 0)
                        {
                            low = shops[i].products[j].price;
                            pdtData.quantity = shops[i].products[j].quantity;
                            pdtData.store = shops[i];
                        }
                        else if (shops[i].products[j].price < low)
                        {
                            low = shops[i].products[j].price;
                            pdtData.quantity = shops[i].products[j].quantity;
                            pdtData.store = shops[i];
                        }
                    }
                }
            }
            pdtData.low = low;

            cout << "The cheapest " << pdtData.name << " in the store: "
                 << pdtData.store.name << ", price: " << pdtData.low
                 << ", quantity: " << pdtData.quantity << endl;
        } else {
            cout << "Goodbye!" << endl;
            break;
        }
    }
}

int main() {
    Shop shops[numShops];
    Product products[numProducts];
    buildShops(shops, numShops, products, numProducts);
    vector<string> prod_names(productNames, productNames + numProducts);
    interactionStore(shops, numShops, prod_names);
    return 0;
}

