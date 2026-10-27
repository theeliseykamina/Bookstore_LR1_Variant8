#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "Base.h"
#include <string>

class Textbook : public Base {
private:
    std::string title_;
    std::string author_;
    int year_;
    std::string institution_;
    int studyYear_;
    int pages_;

public:
    Textbook();
    Textbook(const std::string& title, const std::string& author, int year,
             const std::string& institution, int studyYear,
             int pages, double price);
    Textbook(const Textbook& other);
    ~Textbook() override;

    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    int getYear() const;
    const std::string& getInstitution() const;
    int getStudyYear() const;
    int getPages() const;

    void setTitle(const std::string& value);
    void setAuthor(const std::string& value);
    void setYear(int value);
    void setInstitution(const std::string& value);
    void setStudyYear(int value);
    void setPages(int value);

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
