#pragma once

#include <vector>
#include <iterator>
using namespace std;
namespace ariel{

    enum class IteratorType {
        Ascending,
        SideCross,
        Prime
    };

    class MagicalContainer {
    private:
        vector<int> elements;
        vector<int*> prime_elements;

    public:
        MagicalContainer();
        MagicalContainer& operator=(const MagicalContainer& other);
        void addElement(int element);
        void removeElement(int element);
        vector<int> getElements() const;
        int size() const;
        bool isPrime(int number) const;     // Helper function to check if a number is prime

    class MyIterator{
        protected:
            size_t index;
            size_t index_current_location;
            enum IteratorType itr_type;
            MagicalContainer& container;

        public:

            MyIterator(MagicalContainer& container);
            MyIterator(const MyIterator& other);
            ~MyIterator();

            // overlaoding operators
            MagicalContainer& getContainer();
            MyIterator& operator=(const MyIterator& other);
            bool operator==(const MyIterator& other) const;
            bool operator!=(const MyIterator& other) const;
            bool operator>(const MyIterator& other) const;
            bool operator<(const MyIterator& other) const;
            int operator*() const;
    };

        class AscendingIterator : public MyIterator{
        public:
            AscendingIterator(MagicalContainer& container);
            AscendingIterator(const AscendingIterator& other);
            ~AscendingIterator();

            // overlaoding operators
            AscendingIterator& operator++();

            // Get the iterator pointing to... element
            AscendingIterator begin() const;
            AscendingIterator end() const;
        };


        // SideCrossIterator class
        class SideCrossIterator : public MyIterator{

        public:
            SideCrossIterator(MagicalContainer& container);
            SideCrossIterator(const SideCrossIterator& other);
            ~SideCrossIterator();

            // overloading operator
            SideCrossIterator& operator++();

            // Get the iterator pointing to... element
            SideCrossIterator begin() const;
            SideCrossIterator end() const;
        };


        // PrimeIterator class
        class PrimeIterator : public MyIterator{
        public:
            PrimeIterator(MagicalContainer& container);
            PrimeIterator(const PrimeIterator& other);
            ~PrimeIterator();

            // overloading operator
            PrimeIterator& operator++();

            // Get the iterator pointing to... element
            PrimeIterator begin() const;
            PrimeIterator end() const;
        };
    };
};