#include "Keeper.h"
#include "Book.h"
#include "Stationery.h"
#include "Textbook.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

Keeper::Keeper() : items_(new Base*[2]), count_(0), capacity_(2) {
    std::cout << "[Constructor] Keeper: default\n";
}

Keeper::Keeper(int capacity) : items_(nullptr), count_(0), capacity_(capacity) {
    if (capacity < 1) throw std::invalid_argument("Capacity must be positive.");
    items_ = new Base*[capacity_];
    std::cout << "[Constructor] Keeper: with parameters\n";
}

Keeper::Keeper(const Keeper& other)
    : items_(new Base*[other.capacity_]), count_(0), capacity_(other.capacity_) {
    try {
        for (int i = 0; i < other.count_; ++i) {
            items_[count_++] = other.items_[i]->clone();
        }
    } catch (...) {
        clear();
        delete[] items_;
        throw;
    }
    std::cout << "[Constructor] Keeper: copy\n";
}

Keeper::~Keeper() {
    clear();
    delete[] items_;
    std::cout << "[Destructor] Keeper\n";
}

void Keeper::clear() {
    for (int i = 0; i < count_; ++i) {
        delete items_[i];
    }
    count_ = 0;
}

void Keeper::swapWith(Keeper& other) {
    Base** oldItems = items_;
    items_ = other.items_;
    other.items_ = oldItems;

    int oldCount = count_;
    count_ = other.count_;
    other.count_ = oldCount;

    int oldCapacity = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = oldCapacity;
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        Keeper copy(other);
        swapWith(copy);
    }
    return *this;
}

Keeper& Keeper::operator+=(Base* item) {
    add(item);
    return *this;
}

int Keeper::size() const { return count_; }

void Keeper::reserve(int newCapacity) {
    if (newCapacity <= capacity_) return;
    Base** newItems = new Base*[newCapacity];
    for (int i = 0; i < count_; ++i) {
        newItems[i] = items_[i];
    }
    delete[] items_;
    items_ = newItems;
    capacity_ = newCapacity;
}

void Keeper::add(Base* item) {
    if (item == nullptr) throw std::invalid_argument("Cannot add null object.");
    if (count_ == capacity_) {
        if (capacity_ > std::numeric_limits<int>::max() / 2) {
            throw std::runtime_error("Too many objects in Keeper.");
        }
        reserve(capacity_ * 2);
    }
    items_[count_++] = item; // Keeper owns the object from this point.
}

Base& Keeper::operator[](int index) {
    if (index < 0 || index >= count_) {
        throw std::out_of_range("There is no product with this number.");
    }
    return *items_[index];
}

const Base& Keeper::operator[](int index) const {
    if (index < 0 || index >= count_) {
        throw std::out_of_range("There is no product with this number.");
    }
    return *items_[index];
}

void Keeper::remove(int index) {
    if (index < 0 || index >= count_) {
        throw std::out_of_range("Cannot delete: invalid product number.");
    }
    delete items_[index];
    for (int i = index; i < count_ - 1; ++i) {
        items_[i] = items_[i + 1];
    }
    --count_;
}

void Keeper::showAll() const {
    if (count_ == 0) {
        std::cout << "The shop is empty.\n";
        return;
    }
    for (int i = 0; i < count_; ++i) {
        std::cout << "\n--- Product #" << (i + 1) << " ---\n"
                  << *items_[i];
    }
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream out(filename.c_str());
    if (!out) throw std::runtime_error("Cannot open file for writing.");
    out.precision(17);
    out << "BOOKSTORE_LAB1_V1\n" << count_ << '\n';
    for (int i = 0; i < count_; ++i) {
        out << items_[i]->typeId() << '\n';
        items_[i]->save(out);
    }
    out.flush();
    if (!out) throw std::runtime_error("Failed to write data to file.");
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream in(filename.c_str());
    if (!in) throw std::runtime_error("File not found or cannot be opened.");

    std::string header;
    std::getline(in, header);
    if (header != "BOOKSTORE_LAB1_V1") {
        throw std::runtime_error("This is not a valid bookstore data file.");
    }
    int amount;
    if (!(in >> amount) || amount < 0) {
        throw std::runtime_error("Invalid number of products in file.");
    }

    Keeper loaded;  // Keep old products untouched if reading fails.
    for (int i = 0; i < amount; ++i) {
        int type;
        if (!(in >> type)) throw std::runtime_error("Missing product type.");
        Base* item = nullptr;
        if (type == 1) item = new Book();
        else if (type == 2) item = new Textbook();
        else if (type == 3) item = new Stationery();
        else throw std::runtime_error("Unknown product type in file.");

        try {
            item->load(in);
            loaded.add(item);
        } catch (...) {
            delete item;
            throw;
        }
    }
    swapWith(loaded);
}
