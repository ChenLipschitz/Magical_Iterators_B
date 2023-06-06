// #pragma once

// #include <vector>
// #include <iterator>
// #include "MyIterator.hpp"

// using namespace std;

// namespace ariel{
//     class MagicalContainer {
//     private:
//         vector<int> elements;

//     public:
//         MagicalContainer();
//         void addElement(int element);
//         void removeElement(int element);
//         vector<int> getElements() const;
//         size_t size() const;


//         class AscendingIterator : public MyIterator {
//         private:
//             const MagicalContainer& container;
//             int index;

//         public:
//             AscendingIterator(const MagicalContainer& container, int index);
//             AscendingIterator(const AscendingIterator& other);
//             AscendingIterator(const MagicalContainer& other);
//             ~AscendingIterator() override = default;

//             // overlaoding operators
//             AscendingIterator& operator=(const AscendingIterator& other);
//             bool operator==(const MyIterator& other) const override;
//             bool operator!=(const MyIterator& other) const override;
//             bool operator>(const MyIterator& other) const override;
//             bool operator<(const MyIterator& other) const override;

//             bool operator==(const AscendingIterator& other) const;
//             bool operator!=(const AscendingIterator& other) const;
//             bool operator>(const AscendingIterator& other) const;
//             bool operator<(const AscendingIterator& other) const;

//             int operator*() const;
//             AscendingIterator& operator++() override;

//             // Get the iterator pointing to... element
//             AscendingIterator begin() const;
//             AscendingIterator end() const;
//         };


//         // SideCrossIterator class
//         class SideCrossIterator : public MyIterator {
//         private:
//             const MagicalContainer& container;
//             int index;
//             bool fromStart;

//         public:
//             SideCrossIterator(const MagicalContainer& container, int index, bool fromStart);
//             SideCrossIterator(const SideCrossIterator& other);
//             SideCrossIterator(const MagicalContainer& other);
//             ~SideCrossIterator();

//             // overloading operator
//             SideCrossIterator& operator=(const SideCrossIterator& other);
//             bool operator==(const MyIterator& other) const override;
//             bool operator!=(const MyIterator& other) const override;
//             bool operator>(const MyIterator& other) const override;
//             bool operator<(const MyIterator& other) const override;

//             bool operator==(const SideCrossIterator& other) const;
//             bool operator!=(const SideCrossIterator& other) const;
//             bool operator>(const SideCrossIterator& other) const;
//             bool operator<(const SideCrossIterator& other) const;

//             int operator*() const;
//             SideCrossIterator& operator++() override;

//             // Get the iterator pointing to... element
//             SideCrossIterator begin() const;
//             SideCrossIterator end() const;
//         };


//         // PrimeIterator class
//         class PrimeIterator : public MyIterator {
//         private:
//             const MagicalContainer& container;
//             int index;

//         public:
//             PrimeIterator(const MagicalContainer& container, int index);
//             PrimeIterator(const PrimeIterator& other);
//             PrimeIterator(const MagicalContainer& other);
//             ~PrimeIterator();

//             // overloading operator
//             PrimeIterator& operator=(const PrimeIterator& other);
//             bool operator==(const MyIterator& other) const override;
//             bool operator!=(const MyIterator& other) const override;
//             bool operator>(const MyIterator& other) const override;
//             bool operator<(const MyIterator& other) const override;

//             bool operator==(const PrimeIterator& other) const;
//             bool operator!=(const PrimeIterator& other) const;
//             bool operator>(const PrimeIterator& other) const;
//             bool operator<(const PrimeIterator& other) const;

//             int operator*() const;
//             PrimeIterator& operator++() override;

//             // Get the iterator pointing to... element
//             PrimeIterator begin() const;
//             PrimeIterator end() const;

//             // Helper function to check if a number is prime
//             bool isPrime(int number) const;
//         };
//     };
// };

#pragma once

#include <vector>
#include <iterator>
using namespace std;
namespace ariel{
    class MagicalContainer {
    private:
        vector<int> elements;

    public:
        MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        vector<int> getElements() const;
        int size() const;


        class AscendingIterator {
        private:
            const MagicalContainer& container;
            int index;

        public:
            AscendingIterator(const MagicalContainer& container, int index);
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
            int index;
            bool fromStart;

        public:
            SideCrossIterator(const MagicalContainer& container, int index, bool fromStart);
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

            // Get the iterator pointing to... element
            SideCrossIterator begin() const;
            SideCrossIterator end() const;
        };


        // PrimeIterator class
        class PrimeIterator {
        private:
            const MagicalContainer& container;
            int index;

        public:
            PrimeIterator(const MagicalContainer& container, int index);
            PrimeIterator(const PrimeIterator& other);
            PrimeIterator(const MagicalContainer& other);
            ~PrimeIterator();

            // overloading operator
            PrimeIterator& operator=(const PrimeIterator& other);
            bool operator==(const PrimeIterator& other) const;
            bool operator!=(const PrimeIterator& other) const;
            bool operator>(const PrimeIterator& other) const;
            bool operator<(const PrimeIterator& other) const;
            int operator*() const;
            PrimeIterator& operator++();

            // Get the iterator pointing to... element
            PrimeIterator begin() const;
            PrimeIterator end() const;

            // Helper function to check if a number is prime
            bool isPrime(int number) const;
        };
    };
};