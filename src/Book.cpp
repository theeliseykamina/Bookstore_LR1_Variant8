#include "Book.h"
#include "Input.h"

#include <climits>
#include <iomanip>
#include <iostream>
#include <stdexcept>

Book::Book() : Base(), year_(1), pages_(1) {
    std::cout << "[Constructor] Book: default\n";
}

Book::Book(const std::string& title, const std::string& author, int year,
           const std::string& annotation, const std::string& genre,
           int pages, double price)
    : Base(price), year_(1), pages_(1) {
    setTitle(title);
    setAuthor(author);
    setYear(year);
    setAnnotation(annotation);
    setGenre(genre);
    setPages(pages);
    std::cout << "[Constructor] Book: with parameters\n";
}

Book::Book(const Book& other)
    : Base(other), title_(other.title_), author_(other.author_),
      year_(other.year_), annotation_(other.annotation_),
      genre_(other.genre_), pages_(other.pages_) {
    std::cout << "[Constructor] Book: copy\n";
}

Book::~Book() {
    std::cout << "[Destructor] Book: " << title_ << "\n";
}

const std::string& Book::getTitle() const { return title_; }
const std::string& Book::getAuthor() const { return author_; }
int Book::getYear() const { return year_; }
const std::string& Book::getAnnotation() const { return annotation_; }
const std::string& Book::getGenre() const { return genre_; }
int Book::getPages() const { return pages_; }

void Book::setTitle(const std::string& value) {
    if (value.empty()) throw std::invalid_argument("Book title is empty.");
    title_ = value;
}
void Book::setAuthor(const std::string& value) {
    if (value.empty()) throw std::invalid_argument("Book author is empty.");
    author_ = value;
}
void Book::setYear(int value) {
    if (value < 1) throw std::invalid_argument("Year must be positive.");
    year_ = value;
}
void Book::setAnnotation(const std::string& value) {
    if (value.empty()) throw std::invalid_argument("Annotation is empty.");
    annotation_ = value;
}
void Book::setGenre(const std::string& value) {
    if (value.empty()) throw std::invalid_argument("Genre is empty.");
    genre_ = value;
}
void Book::setPages(int value) {
    if (value < 1) throw std::invalid_argument("Pages must be positive.");
    pages_ = value;
}

int Book::typeId() const { return 1; }
const char* Book::typeName() const { return "Book"; }

void Book::input() {
    setTitle(readText("Title: "));
    setAuthor(readText("Author: "));
    setYear(readInt("Publication year: ", 1, INT_MAX));
    setAnnotation(readText("Annotation: "));
    setGenre(readText("Genre: "));
    setPages(readInt("Page count: ", 1, INT_MAX));
    setPrice(readPrice("Price: "));
}

void Book::edit() {
    std::cout << "1 Title | 2 Author | 3 Year | 4 Annotation | "
                 "5 Genre | 6 Pages | 7 Price\n";
    int option = readInt("Field to change: ", 1, 7);
    switch (option) {
        case 1: setTitle(readText("New title: ")); break;
        case 2: setAuthor(readText("New author: ")); break;
        case 3: setYear(readInt("New year: ", 1, INT_MAX)); break;
        case 4: setAnnotation(readText("New annotation: ")); break;
        case 5: setGenre(readText("New genre: ")); break;
        case 6: setPages(readInt("New page count: ", 1, INT_MAX)); break;
        case 7: setPrice(readPrice("New price: ")); break;
    }
}

void Book::print(std::ostream& out) const {
    out << "Type: " << typeName() << "\n"
        << "Title: " << title_ << "\n"
        << "Author: " << author_ << "\n"
        << "Year: " << year_ << "\n"
        << "Annotation: " << annotation_ << "\n"
        << "Genre: " << genre_ << "\n"
        << "Pages: " << pages_ << "\n"
        << "Price: " << getPrice() << "\n";
}

void Book::save(std::ostream& out) const {
    out << std::quoted(title_) << '\n'
        << std::quoted(author_) << '\n'
        << year_ << '\n'
        << std::quoted(annotation_) << '\n'
        << std::quoted(genre_) << '\n'
        << pages_ << '\n'
        << getPrice() << '\n';
}

void Book::load(std::istream& in) {
    std::string title, author, annotation, genre;
    int year, pages;
    double price;
    if (!(in >> std::quoted(title) >> std::quoted(author) >> year
          >> std::quoted(annotation) >> std::quoted(genre) >> pages >> price)) {
        throw std::runtime_error("Cannot read book data from file.");
    }
    setTitle(title);
    setAuthor(author);
    setYear(year);
    setAnnotation(annotation);
    setGenre(genre);
    setPages(pages);
    setPrice(price);
}

Base* Book::clone() const {
    return new Book(*this);
}
