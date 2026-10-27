#ifndef BASE_H
#define BASE_H

#include <iosfwd>

// Abstract parent for all products of the shop.
class Base {
private:
    double price_;

public:
    Base();
    explicit Base(double price);
    Base(const Base& other);
    virtual ~Base();

    double getPrice() const;
    void setPrice(double price);

    virtual int typeId() const = 0;
    virtual const char* typeName() const = 0;
    virtual void input() = 0;
    virtual void edit() = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;
    virtual Base* clone() const = 0;
};

std::ostream& operator<<(std::ostream& out, const Base& item);

#endif
