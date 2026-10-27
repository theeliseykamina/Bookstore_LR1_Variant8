#include "Base.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

Base::Base() : price_(0.0) {
    std::cout << "[Constructor] Base: default\n";
}

Base::Base(double price) : price_(0.0) {
    setPrice(price);
    std::cout << "[Constructor] Base: with parameters\n";
}

Base::Base(const Base& other) : price_(other.price_) {
    std::cout << "[Constructor] Base: copy\n";
}

Base::~Base() {
    std::cout << "[Destructor] Base\n";
}

double Base::getPrice() const {
    return price_;
}

void Base::setPrice(double price) {
    if (!std::isfinite(price) || price < 0.0) {
        throw std::invalid_argument("Price cannot be negative or invalid.");
    }
    price_ = price;
}

std::ostream& operator<<(std::ostream& out, const Base& item) {
    item.print(out);
    return out;
}
