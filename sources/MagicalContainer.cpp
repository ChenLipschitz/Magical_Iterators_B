#include "MagicalContainer.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;
using namespace ariel;


//----------------------------- MagicalContainer class -----------------------------//
MagicalContainer::MagicalContainer() {}

bool MagicalContainer::isPrime(int number) const{
    if (number <= 1)
        return false;
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0)
            return false;
    }
    return true;
}

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

size_t MagicalContainer::size() const {
    return elements.size();
}

vector<int> MagicalContainer::getElements() const{
    return elements;
}

vector<int*> MagicalContainer::getPrimeElements() const{
    return this->prime_elements;
}

MagicalContainer& MagicalContainer::operator=(const MagicalContainer& other) {
    if (this != &other) {
        elements = other.elements;
        prime_elements.clear();
        
        // Copy prime elements by address
        for (const int* prime : other.prime_elements) {
            size_t index = static_cast<size_t>(prime - &(other.elements[0]));
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

void MagicalContainer::MyIterator::setIndex(size_t newIndex){
    index = newIndex;
}

void MagicalContainer::MyIterator::setCurrLocation(size_t newLocation){
    index_current_location = newLocation;
}

// overloading operators
MagicalContainer::MyIterator& MagicalContainer::MyIterator::operator=(const MyIterator& other) {
    if (this != &other){
        throw runtime_error("Error - cannot operate on different containers");
    }
    else {
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
//--- Initialization ---//
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container)
    : MyIterator(container) {
    this->itr_type = IteratorType::Ascending;
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : MyIterator(other) {}

MagicalContainer::AscendingIterator::~AscendingIterator() {}

//--- Overloading Operators ---//
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    ++index;
    ++index_current_location;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
    AscendingIterator beginIterator(container);
    return beginIterator;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const {
    AscendingIterator endIterator(container);
    endIterator.setIndex(container.size());
    endIterator.setCurrLocation(container.size());
    return endIterator;
}



//----------------------------- SideCrossIterator class -----------------------------//

//--- Initialization ---//
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
    : MyIterator(container) {
    this->itr_type = IteratorType::SideCross;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    : MyIterator(other) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

//--- Overloading Operators ---//
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if (index_current_location == 0) {
            setIndex(1);
    } else {
        if (index_current_location % 2 == 1) {
            setCurrLocation(index_current_location + index_current_location);
        } else {
            setCurrLocation(index_current_location - index_current_location -2 );
        }
    }
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const {
    SideCrossIterator beginIterator(container);
    beginIterator.index_current_location = 0;
    return beginIterator;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    SideCrossIterator endIterator(container);
    endIterator.index_current_location = container.size()/2;
    endIterator.index = container.size()/2;
    return endIterator;
}


//----------------------------- PrimeIterator class -----------------------------//
//--- Initialization ---//
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
    : MyIterator(container) {
    this->itr_type = IteratorType::Prime;
}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
    : MyIterator(other) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

//--- Overloading Operators ---//
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
     if (index_current_location == container.getPrimeElements().size() - 1) {
        throw runtime_error("Error - index out of range");
    }
    index++;
    index_current_location++;   // represents the location in the prime_elements container

    return *this;
}

int MagicalContainer::PrimeIterator::operator*() const {
    return *container.getPrimeElements()[index_current_location];
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
    PrimeIterator beginIterator(container);
    beginIterator.index = 0;
    beginIterator.index_current_location = 0;
    return beginIterator;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
    PrimeIterator endIterator(container);
    endIterator.setIndex(container.getPrimeElements().size());
    endIterator.setCurrLocation(container.getPrimeElements().size());
    return endIterator;
}
