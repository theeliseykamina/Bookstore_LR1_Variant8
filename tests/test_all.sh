#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
mkdir -p build
g++ -std=c++17 -Wall -Wextra -pedantic src/*.cpp -o build/bookstore_lab1
./build/bookstore_lab1 < tests/demo_input.txt > build/demo_output.txt
grep -q "Product added." build/demo_output.txt
grep -q "Product deleted." build/demo_output.txt
grep -q "All products loaded." build/demo_output.txt
grep -q "Color: Black" build/demo_output.txt
grep -q "Copied objects: 3" build/demo_output.txt
grep -q "Assigned objects: 3" build/demo_output.txt
./build/bookstore_lab1 < tests/invalid_input.txt > build/invalid_output.txt
grep -q "All products" build/demo_output.txt
grep -q "File not found or cannot be opened." build/invalid_output.txt
printf '9\ntests/bad_data.dat\n4\n0\n' | ./build/bookstore_lab1 > build/bad_data_output.txt
grep -q "Price cannot be negative or invalid." build/bad_data_output.txt
grep -q "The shop is empty." build/bad_data_output.txt
g++ -std=c++17 -Wall -Wextra -pedantic -Isrc tests/test_classes.cpp \
  src/Base.cpp src/Book.cpp src/Textbook.cpp src/Stationery.cpp \
  src/Keeper.cpp src/Input.cpp -o build/test_classes
./build/test_classes > build/class_output.txt
grep -q "CLASS_TESTS_PASSED" build/class_output.txt
printf 'All checks passed.\n'
