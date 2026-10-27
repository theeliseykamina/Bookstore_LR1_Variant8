#include "Base.h"
#include "Book.h"
#include "Keeper.h"
#include "Stationery.h"
#include "Textbook.h"

#include <cassert>
#include <exception>
#include <iostream>

int main() {
    Book b("Test", "Author", 2020, "Short info", "Fiction", 120, 200.5);
    Book copiedBook(b);
    assert(copiedBook.getTitle() == "Test");

    Textbook t("Geometry", "Teacher", 2015, "School", 7, 240, 325.0);
    Textbook copiedTextbook(t);
    assert(copiedTextbook.getStudyYear() == 7);

    Stationery s("Pencil", "Gray", "Drawing", 15.5);
    Stationery copiedStationery(s);
    assert(copiedStationery.getColor() == "Gray");

    Keeper first(1);
    first.add(new Book(b));
    first.add(new Textbook(t));
    first.add(new Stationery(s));
    Keeper second(first);
    dynamic_cast<Book&>(second[0]).setTitle("Different title");
    assert(dynamic_cast<Book&>(first[0]).getTitle() == "Test");

    Keeper assigned;
    assigned = second;
    assert(assigned.size() == 3);
    assert(dynamic_cast<Book&>(assigned[0]).getTitle() == "Different title");

    first.saveToFile("build/test_classes.dat");
    Keeper loaded;
    loaded.loadFromFile("build/test_classes.dat");
    assert(loaded.size() == 3);
    assert(dynamic_cast<Textbook&>(loaded[1]).getPages() == 240);

    try {
        loaded.loadFromFile("tests/bad_data.dat");
        assert(false);
    } catch (const std::exception&) {
        assert(loaded.size() == 3); // Corrupt file cannot erase existing data.
    }

    loaded.remove(1);
    assert(loaded.size() == 2);
    std::cout << "CLASS_TESTS_PASSED\n";
}
