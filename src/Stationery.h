#ifndef STATIONERY_H
#define STATIONERY_H

#include "Base.h"
#include <string>

class Stationery : public Base {
private:
    std::string kind_;
    std::string color_;
    std::string purpose_;

public:
    Stationery();
    Stationery(const std::string& kind, const std::string& color,
               const std::string& purpose, double price);
    Stationery(const Stationery& other);
    ~Stationery() override;

    const std::string& getKind() const;
    const std::string& getColor() const;
    const std::string& getPurpose() const;
    void setKind(const std::string& value);
    void setColor(const std::string& value);
    void setPurpose(const std::string& value);

    int typeId() const override;
    const char* typeName() const override;
    void input() override;
    void edit() override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
    Base* clone() const override;
};

#endif
