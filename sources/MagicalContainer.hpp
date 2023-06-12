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
        bool isPrime(int number) const;
        void update_prime_elemtnts();

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
            int num_of_increments = 0; 
            /* NOTE - The reason we need num_of_increments is that index alone does not
                provide enough information to determine the side-cross pattern of iteration.
                The num_of_increments variable allows the iterator to alternate between the left and right sides of the container as it progresses,
                regardless of the current index value.
                By incrementing num_of_increments and using it as a condition in the operator++ method,
                the iterator knows when it has completed iterating through all the elements
                in the container according to the side-cross pattern.*/

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