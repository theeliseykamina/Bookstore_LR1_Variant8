#include "Textbook.h"
#include "Input.h"

#include <climits>
#include <iomanip>
#include <iostream>
#include <stdexcept>

Textbook::Textbook() : Base(), year_(1), studyYear_(1), pages_(1) {
    std::cout << "[Constructor] Textbook: default\n";
}

Textbook::Textbook(const std::string& title, const std::string& author,
                   int year, const std::string& institution, int studyYear,
                   int pages, double price)
    : Base(price), year_(1), studyYear_(1), pages_(1) {
    setTitle(title);
    setAuthor(author);
    setYear(year);
    setInstitution(institution);
    setStudyYear(studyYear);
    setPages(pages);
    std::cout << "[Constructor] Textbook: with parameters\n";
}

Textbook::Textbook(const Textbook& other)
    : Base(other), title_(other.title_), author_(other.author_),
      year_(other.year_), institution_(other.institution_),
      studyYear_(other.studyYear_), pages_(other.pages_) {
    std::cout << "[Constructor] Textbook: copy\n";
}

Textbook::~Textbook() {
    std::cout << "[Destructor] Textbook: " << title_ << "\n";
}

const std::string& Textbook::getTitle() const { return title_; }
const std::string& Textbook::getAuthor() const { return author_; }
int Textbook::getYear() const { return year_; }
const std::string& Textbook::getInstitution() const { return institution_; }
int Textbook::getStudyYear() const { return studyYear_; }
int Textbook::getPages() const { return pages_; }

void Textbook::setTitle(const std::string& value) {
    if (value.empty()) throw std::invalid_argument("Textbook title is empty.");
    title_ = value;
}
void Textbook::setAuthor(const std::string& value) {
    if (value.empty()) throw std::invalid_argument("Textbook author is empty.");
    author_ = value;
}
void Textbook::setYear(int value) {
    if (value < 1) throw std::invalid_argument("Year must be positive.");
    year_ = value;
}
void Textbook::setInstitution(const std::string& value) {
    if (value.empty()) throw std::invalid_argument("Institution is empty.");
    institution_ = value;
}
void Textbook::setStudyYear(int value) {
    if (value < 1) throw std::invalid_argument("Study year must be positive.");
    studyYear_ = value;
}
void Textbook::setPages(int value) {
    if (value < 1) throw std::invalid_argument("Pages must be positive.");
    pages_ = value;
}

int Textbook::typeId() const { return 2; }
const char* Textbook::typeName() const { return "Textbook"; }

void Textbook::input() {
    setTitle(readText("Title: "));
    setAuthor(readText("Author: "));
    setYear(readInt("Publication year: ", 1, INT_MAX));
    setInstitution(readText("Educational institution: "));
    setStudyYear(readInt("Study year / course: ", 1, INT_MAX));
    setPages(readInt("Page count: ", 1, INT_MAX));
    setPrice(readPrice("Price: "));
}

void Textbook::edit() {
    std::cout << "1 Title | 2 Author | 3 Year | 4 Institution | "
                 "5 Study year | 6 Pages | 7 Price\n";
    int option = readInt("Field to change: ", 1, 7);
    switch (option) {
        case 1: setTitle(readText("New title: ")); break;
        case 2: setAuthor(readText("New author: ")); break;
        case 3: setYear(readInt("New publication year: ", 1, INT_MAX)); break;
        case 4: setInstitution(readText("New institution: ")); break;
        case 5: setStudyYear(readInt("New study year: ", 1, INT_MAX)); break;
        case 6: setPages(readInt("New page count: ", 1, INT_MAX)); break;
        case 7: setPrice(readPrice("New price: ")); break;
    }
}

void Textbook::print(std::ostream& out) const {
    out << "Type: " << typeName() << "\n"
        << "Title: " << title_ << "\n"
        << "Author: " << author_ << "\n"
        << "Year: " << year_ << "\n"
        << "Institution: " << institution_ << "\n"
        << "Study year: " << studyYear_ << "\n"
        << "Pages: " << pages_ << "\n"
        << "Price: " << getPrice() << "\n";
}

void Textbook::save(std::ostream& out) const {
    out << std::quoted(title_) << '\n'
        << std::quoted(author_) << '\n'
        << year_ << '\n'
        << std::quoted(institution_) << '\n'
        << studyYear_ << '\n'
        << pages_ << '\n'
        << getPrice() << '\n';
}

void Textbook::load(std::istream& in) {
    std::string title, author, institution;
    int year, studyYear, pages;
    double price;
    if (!(in >> std::quoted(title) >> std::quoted(author) >> year
          >> std::quoted(institution) >> studyYear >> pages >> price)) {
        throw std::runtime_error("Cannot read textbook data from file.");
    }
    setTitle(title);
    setAuthor(author);
    setYear(year);
    setInstitution(institution);
    setStudyYear(studyYear);
    setPages(pages);
    setPrice(price);
}

Base* Textbook::clone() const {
    return new Textbook(*this);
}
