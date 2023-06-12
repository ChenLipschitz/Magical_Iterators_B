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
        vector<int*> getPrimeElements() const;
        size_t size() const;
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
            void setIndex(size_t newIndex);
            void setCurrLocation(size_t newLocation);
            MyIterator& operator=(const MyIterator& other);
            bool operator==(const MyIterator& other) const;
            bool operator!=(const MyIterator& other) const;
            bool operator>(const MyIterator& other) const;
            bool operator<(const MyIterator& other) const;
            virtual int operator*() const;
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

        private:
        size_t forwardIndex;    // Index for iterating in forward direction
        size_t backwardIndex;   // Index for iterating in backward direction
        bool isForward;         // Flag to indicate the current direction of iteration

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
            int operator*() const override;

            // Get the iterator pointing to... element
            PrimeIterator begin() const;
            PrimeIterator end() const;
        };
    };
};