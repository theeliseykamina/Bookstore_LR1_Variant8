#include "Stationery.h"
#include "Input.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

Stationery::Stationery() : Base() {
    std::cout << "[Constructor] Stationery: default\n";
}

Stationery::Stationery(const std::string& kind, const std::string& color,
                       const std::string& purpose, double price)
    : Base(price) {
    setKind(kind);
    setColor(color);
    setPurpose(purpose);
    std::cout << "[Constructor] Stationery: with parameters\n";
}

Stationery::Stationery(const Stationery& other)
    : Base(other), kind_(other.kind_), color_(other.color_),
      purpose_(other.purpose_) {
    std::cout << "[Constructor] Stationery: copy\n";
}

Stationery::~Stationery() {
    std::cout << "[Destructor] Stationery: " << kind_ << "\n";
}

const std::string& Stationery::getKind() const { return kind_; }
const std::string& Stationery::getColor() const { return color_; }
const std::string& Stationery::getPurpose() const { return purpose_; }

void Stationery::setKind(const std::string& value) {
    if (value.empty()) throw std::invalid_argument("Stationery type is empty.");
    kind_ = value;
}
void Stationery::setColor(const std::string& value) {
    if (value.empty()) throw std::invalid_argument("Color is empty.");
    color_ = value;
}
void Stationery::setPurpose(const std::string& value) {
    if (value.empty()) throw std::invalid_argument("Purpose is empty.");
    purpose_ = value;
}

int Stationery::typeId() const { return 3; }
const char* Stationery::typeName() const { return "Stationery"; }

void Stationery::input() {
    setKind(readText("Stationery type (pen, notebook, etc.): "));
    setColor(readText("Color: "));
    setPurpose(readText("Purpose: "));
    setPrice(readPrice("Price: "));
}

void Stationery::edit() {
    std::cout << "1 Type | 2 Color | 3 Purpose | 4 Price\n";
    int option = readInt("Field to change: ", 1, 4);
    switch (option) {
        case 1: setKind(readText("New type: ")); break;
        case 2: setColor(readText("New color: ")); break;
        case 3: setPurpose(readText("New purpose: ")); break;
        case 4: setPrice(readPrice("New price: ")); break;
    }
}

void Stationery::print(std::ostream& out) const {
    out << "Type: " << typeName() << "\n"
        << "Stationery: " << kind_ << "\n"
        << "Color: " << color_ << "\n"
        << "Purpose: " << purpose_ << "\n"
        << "Price: " << getPrice() << "\n";
}

void Stationery::save(std::ostream& out) const {
    out << std::quoted(kind_) << '\n'
        << std::quoted(color_) << '\n'
        << std::quoted(purpose_) << '\n'
        << getPrice() << '\n';
}

void Stationery::load(std::istream& in) {
    std::string kind, color, purpose;
    double price;
    if (!(in >> std::quoted(kind) >> std::quoted(color)
          >> std::quoted(purpose) >> price)) {
        throw std::runtime_error("Cannot read stationery data from file.");
    }
    setKind(kind);
    setColor(color);
    setPurpose(purpose);
    setPrice(price);
}

Base* Stationery::clone() const {
    return new Stationery(*this);
}
