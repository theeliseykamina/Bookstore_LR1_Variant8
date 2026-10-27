#ifndef BOOK_H
#define BOOK_H

#include "Base.h"
#include <string>

class Book : public Base {
private:
    std::string title_;
    std::string author_;
    int year_;
    std::string annotation_;
    std::string genre_;
    int pages_;

public:
    Book();
    Book(const std::string& title, const std::string& author, int year,
         const std::string& annotation, const std::string& genre,
         int pages, double price);
    Book(const Book& other);
    ~Book() override;

    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    int getYear() const;
    const std::string& getAnnotation() const;
    const std::string& getGenre() const;
    int getPages() const;

    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setYear(int year);
    void setAnnotation(const std::string& annotation);
    void setGenre(const std::string& genre);
    void setPages(int pages);

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
