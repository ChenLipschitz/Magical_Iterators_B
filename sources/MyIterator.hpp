#pragma once

#include <vector>
#include <iterator>
using namespace std;

namespace ariel {
    class MyIterator{
    public:

            // Default constructor and destructor
            MyIterator() = default;
            virtual ~MyIterator() = default;

            // Overlaoding operators
            MyIterator& operator=(const MyIterator& other);
            bool operator==(const MyIterator& other) const;
            bool operator!=(const MyIterator& other) const;
            bool operator>(const MyIterator& other) const;
            bool operator<(const MyIterator& other) const;
            int operator*() const;
            virtual MyIterator& operator++() = 0;
    };
}
