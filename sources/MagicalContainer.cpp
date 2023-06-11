#include "MagicalContainer.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;
using namespace ariel;


//----------------------------- MagicalContainer class -----------------------------//
MagicalContainer::MagicalContainer() {}

//got the help of chatGPT in this method
void MagicalContainer::addElement(int element) {
    // Check if the element already exists in the container
    if (find(elements.begin(), elements.end(), element) != elements.end()) {
        return;
    }

    // Find the insertion position using lower_bound
    auto insertPos = lower_bound(elements.begin(), elements.end(), element);

    // Insert the element at the determined position
    elements.insert(insertPos, element);

    if (isPrime(element)) {
        prime_elements.push_back(&(*insertPos));
    }
}

void MagicalContainer::removeElement(int element) {
    // Check if the element exists in the container
    auto erasePos = find(elements.begin(), elements.end(), element);
    if (erasePos == elements.end()) {
        return;
    }

    elements.erase(erasePos);

    if (isPrime(element)) { //if the given element is prime erase from prime_elements as well
        auto primePos = find(prime_elements.begin(), prime_elements.end(), &(*erasePos));
        if (primePos != prime_elements.end()) {
            prime_elements.erase(primePos);
        }
    }
}

int MagicalContainer::size() const {
    return elements.size();
}

std::vector<int> MagicalContainer::getElements() const{
    return elements;
}

MagicalContainer& MagicalContainer::operator=(const MagicalContainer& other) {
    if (this != &other) {
        elements = other.elements;
        prime_elements.clear();
        
        // Copy prime elements by address
        for (const int* prime : other.prime_elements) {
            size_t index = prime - &(other.elements[0]);
            prime_elements.push_back(&elements[index]);
        }
    }
    return *this;
}



//----------------------------- MyIterator class -----------------------------//

// Constructors
MagicalContainer::MyIterator::MyIterator(MagicalContainer& container)
 : index(0), index_current_location(0), itr_type(IteratorType::Ascending), container(container) {}

MagicalContainer::MyIterator::MyIterator(const MyIterator& other)
 : index(other.index), index_current_location(other.index_current_location), itr_type(other.itr_type), container(other.container) {}

MagicalContainer::MyIterator::~MyIterator() {}

// overloading operators
MagicalContainer::MyIterator& MagicalContainer::MyIterator::operator=(const MyIterator& other) {
    if (this != &other) {
        index = other.index;
        index_current_location = other.index_current_location;
        itr_type = other.itr_type;
        container = other.container;
    }
    return *this;
}

bool MagicalContainer::MyIterator::operator==(const MyIterator& other) const {
    return (index == other.index) && (index_current_location == other.index_current_location) && (itr_type == other.itr_type) && (&container == &other.container);
}

bool MagicalContainer::MyIterator::operator!=(const MyIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::MyIterator::operator>(const MyIterator& other) const {
    return index > other.index;
}

bool MagicalContainer::MyIterator::operator<(const MyIterator& other) const {
    return index < other.index;
}

int MagicalContainer::MyIterator::operator*() const {
    // Return the appropriate value based on the iterator type
    switch (itr_type) {
        case IteratorType::Ascending:
            return container.getElements()[index];
        case IteratorType::SideCross:
            return container.getElements()[index_current_location];
        case IteratorType::Prime:
            return *container.prime_elements[index];
        default:
            return 0; // or some other default value
    }
}

//----------------------------- AscendingIterator class -----------------------------//

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container)
    : MyIterator(container) {}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : MyIterator(other.container) {}

MagicalContainer::AscendingIterator::~AscendingIterator() {}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    ++index;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
    return AscendingIterator(container);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const {
    AscendingIterator endIterator(container);
    endIterator.index = container.size() - 1;
    return endIterator;
}


//----------------------------- SideCrossIterator class -----------------------------//


MagicalContainer::SideCrossIterator::~SideCrossIterator() {}


//--- Overloading Operators ---//




//----------------------------- PrimeIterator class -----------------------------//

MagicalContainer::PrimeIterator::~PrimeIterator() {}


//--- Overlaoding Operators ---//
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    return *this;
}

bool isPrime(int number) {
    if (number <= 1)
        return false;
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0)
            return false;
    }
    return true;
}