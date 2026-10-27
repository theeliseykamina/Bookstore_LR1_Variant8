#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include <string>

// Owns a manually allocated, growing array of Base* (no STL containers).
class Keeper {
private:
    Base** items_;
    int count_;
    int capacity_;

    void reserve(int newCapacity);
    void swapWith(Keeper& other);

public:
    Keeper();
    explicit Keeper(int capacity);
    Keeper(const Keeper& other);
    ~Keeper();

    Keeper& operator=(const Keeper& other);
    Keeper& operator+=(Base* item);
    Base& operator[](int index);
    const Base& operator[](int index) const;

    int size() const;
    void add(Base* item);
    void remove(int index);
    void clear();
    void showAll() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif
