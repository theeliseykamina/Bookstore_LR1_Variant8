#include "Base.h"
#include "Book.h"
#include "Input.h"
#include "Keeper.h"
#include "Stationery.h"
#include "Textbook.h"

#include <climits>
#include <exception>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

void printMenu() {
    std::cout << "\n========== BOOKSTORE (VARIANT 8) ==========\n"
              << "1. Add book\n"
              << "2. Add textbook\n"
              << "3. Add stationery\n"
              << "4. Show all products\n"
              << "5. Show one product\n"
              << "6. Edit product field\n"
              << "7. Delete product\n"
              << "8. Save all to file\n"
              << "9. Load all from file\n"
              << "10. Demonstrate copying\n"
              << "0. Exit\n";
}

int getProductIndex(const Keeper& keeper) {
    if (keeper.size() == 0) {
        std::cout << "The shop is empty.\n";
        return -1;
    }
    return readInt("Product number: ", 1, keeper.size()) - 1;
}

void addProduct(Keeper& keeper, int type) {
    Base* item = nullptr;
    if (type == 1) item = new Book();
    if (type == 2) item = new Textbook();
    if (type == 3) item = new Stationery();
    try {
        item->input();
        keeper += item;
        item = nullptr; // Keeper now owns this pointer.
        std::cout << "Product added.\n";
    } catch (...) {
        delete item;
        throw;
    }
}

void demonstrateCopy(const Keeper& keeper) {
    std::cout << "Making independent copy of Keeper...\n";
    Keeper copied(keeper);  // Copy constructor, deep copy via clone().
    std::cout << "Copied objects: " << copied.size() << "\n";
    std::cout << "Making another Keeper and assigning the copy...\n";
    Keeper second(1);       // Constructor with parameters.
    second = copied;        // Overloaded assignment operator.
    std::cout << "Assigned objects: " << second.size() << "\n";
    std::cout << "Copies are now destroyed at end of function.\n";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    Keeper keeper;
    try {
        while (true) {
            printMenu();
            int choice = readInt("Your choice: ", 0, 10);
            try {
                if (choice == 0) break;
                if (choice >= 1 && choice <= 3) {
                    addProduct(keeper, choice);
                } else if (choice == 4) {
                    keeper.showAll();
                } else if (choice == 5) {
                    int index = getProductIndex(keeper);
                    if (index >= 0) std::cout << keeper[index];
                } else if (choice == 6) {
                    int index = getProductIndex(keeper);
                    if (index >= 0) {
                        keeper[index].edit();
                        std::cout << "Field updated.\n";
                    }
                } else if (choice == 7) {
                    int index = getProductIndex(keeper);
                    if (index >= 0) {
                        keeper.remove(index);
                        std::cout << "Product deleted.\n";
                    }
                } else if (choice == 8) {
                    keeper.saveToFile(readText("File path for saving: "));
                    std::cout << "All products saved.\n";
                } else if (choice == 9) {
                    keeper.loadFromFile(readText("File path for loading: "));
                    std::cout << "All products loaded.\n";
                } else if (choice == 10) {
                    demonstrateCopy(keeper);
                }
            } catch (const std::exception& error) {
                std::cout << "Error: " << error.what() << '\n';
            }
        }
    } catch (const std::exception& error) {
        std::cerr << "Input ended or critical error: " << error.what() << '\n';
        return 1;
    }
    std::cout << "Goodbye!\n";
    return 0;
}
