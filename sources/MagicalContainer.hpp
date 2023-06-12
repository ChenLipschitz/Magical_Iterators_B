#pragma once

#include <vector>
#include <iterator>
using namespace std;
namespace ariel{
    class MagicalContainer {
    private:
        vector<int> elements;
        vector<int*> prime_elements;

    public:
        MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        vector<int> getElements() const;
        size_t size() const;
        // Helper function to check if a number is prime
        bool isPrime(int number) const;

        class AscendingIterator {
        private:
            const MagicalContainer& container;
            size_t index;

        public:
            AscendingIterator(const MagicalContainer& container, size_t index);
            AscendingIterator(const AscendingIterator& other);
            AscendingIterator(const MagicalContainer& other);
            ~AscendingIterator();

            // overlaoding operators
            AscendingIterator& operator=(const AscendingIterator& other);
            bool operator==(const AscendingIterator& other) const;
            bool operator!=(const AscendingIterator& other) const;
            bool operator>(const AscendingIterator& other) const;
            bool operator<(const AscendingIterator& other) const;
            int operator*() const;
            AscendingIterator& operator++();

            // Get the iterator pointing to... element
            AscendingIterator begin() const;
            AscendingIterator end() const;
        };


        // SideCrossIterator class
        class SideCrossIterator {
        private:
            const MagicalContainer& container;
            size_t index;
            bool fromStart;

        public:
            SideCrossIterator(const MagicalContainer& container, size_t index, bool fromStart);
            SideCrossIterator(const SideCrossIterator& other);
            SideCrossIterator(const MagicalContainer& other);
            ~SideCrossIterator();

            // overloading operator
            SideCrossIterator& operator=(const SideCrossIterator& other);
            bool operator==(const SideCrossIterator& other) const;
            bool operator!=(const SideCrossIterator& other) const;
            bool operator>(const SideCrossIterator& other) const;
            bool operator<(const SideCrossIterator& other) const;
            int operator*() const;
            SideCrossIterator& operator++();
            void update_fromStart();

            // Get the iterator pointing to... element
            SideCrossIterator begin() const;
            SideCrossIterator end() const;
        };


        // PrimeIterator class
        class PrimeIterator {
        private:
            const MagicalContainer& container;
            size_t index;

        public:
            PrimeIterator(const MagicalContainer& container, size_t index);
            PrimeIterator(const PrimeIterator& other);
            PrimeIterator(const MagicalContainer& other);
            ~PrimeIterator();

            // overloading operator
            PrimeIterator& operator=(const PrimeIterator& other);
            bool operator==(const PrimeIterator& other) const;
            bool operator!=(const PrimeIterator& other) const;
            bool operator>(const PrimeIterator& other) const;
            bool operator<(const PrimeIterator& other) const;
            int &operator*() const;
            PrimeIterator& operator++();

            // Get the iterator pointing to... element
            PrimeIterator begin() const;
            PrimeIterator end() const;
        };
    };
};