#include "MagicalContainer.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;
using namespace ariel;

//----------------------------- MagicalContainer class -----------------------------//
MagicalContainer::MagicalContainer() {}

// adds an element if is not already in the container
void MagicalContainer::addElement(int element)
{
    // Check if the element already exists in the container
    if (find(elements.begin(), elements.end(), element) != elements.end())
    {
        return;
    }

    /** Find the insertion position using
    lower_bound (=> returns an iterator pointing to the first
    element in a sorted range that is not less than a specified value)**/
    auto insertPos = lower_bound(elements.begin(), elements.end(), element);

    elements.insert(insertPos, element);
    update_prime_elemtnts();
}

// removes element if exists in the container
void MagicalContainer::removeElement(int element) {
    // Check if the element exists in the container
    auto erasePos = find(elements.begin(), elements.end(), element);
    if (erasePos == elements.end()) {
        throw runtime_error("Error - element doesnt exist in the container");
    }

    elements.erase(erasePos);

    if (isPrime(element)) {
        // if the given element is prime erase from prime_elements as well
        auto primePos = find(prime_elements.begin(), prime_elements.end(), &(*erasePos));
        if (primePos != prime_elements.end()){
            prime_elements.erase(primePos);
        }
    }
}

// returns the size of the elements in the container
size_t MagicalContainer::size() const {
    return elements.size();
}

// return the elements vector
std::vector<int> MagicalContainer::getElements() const {
    return elements;
}

// returns true if a number is prime, false else
bool MagicalContainer::isPrime(int number) const {
    if (number <= 1)
        return false;
    for (int i = 2; i * i <= number; ++i){
        if (number % i == 0)
            return false;
    }
    return true;
}

//updates the prime_elements vector after adding new element to the elements vector
void MagicalContainer::update_prime_elemtnts(){
    prime_elements.clear();
    for (size_t i = 0; i < size(); i++)
    {
        if (isPrime(elements[i]))
        {
            prime_elements.push_back(&elements[i]);
        }
    }
}




//----------------------------- AscendingIterator class -----------------------------//

MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &container_, size_t index_)
    : container(container_), index(index_) {}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
    : container(other.container), index(other.index) {}

MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &other)
    : container(other), index(0) {}

MagicalContainer::AscendingIterator::~AscendingIterator() {}


//--- Overlaoding Operators ---//
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
   if (&this->container != &other.container) {
        throw runtime_error("Error - cannot use operators on different containers");
    }
    this->index = other.index;
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
    return &container == &other.container && index == other.index;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
    return index > other.index;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
    return index < other.index;
}

int MagicalContainer::AscendingIterator::operator*() const {
    return container.elements[index];
}

//preincrement iterator according to the elements ascending order
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    if (index >= container.elements.size()) {
        throw runtime_error("Error - cannot increment, index out of range");
    }
    index++;
    return *this;
}

// return the first element according to the ascending order
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
    return AscendingIterator(container, 0);
}

// return the last element
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const {
    return AscendingIterator(container, container.size());
}




//----------------------------- SideCrossIterator class -----------------------------//

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container_, size_t index_, bool fromStart_)
    : container(container_), index(index_), fromStart(fromStart_) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
    : container(other.container), index(other.index), fromStart(other.fromStart) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &other)
    : container(other), index(0), fromStart(true) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}


//--- Overloading Operators ---//
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
    if (&this->container != &other.container) {
        throw runtime_error("Error - cannot use operators on different containers");
    }
    index = other.index;
    fromStart = other.fromStart;
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
    return index == other.index && fromStart == other.fromStart;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
    return !(*this == other);
}

// got the help of GPT
bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
    return (*this).operator*() > (other).operator*();
}

// got the help of GPT
bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
    return (*this).operator*() < (other).operator*();
}

int MagicalContainer::SideCrossIterator::operator*() const {
    if (!fromStart) {
        // if the returned element is from the right section
        size_t newIndex = container.size() - index - 1;
        return container.elements[newIndex];
    }
    return container.elements[index];
}

// preincrement iterator according to the sideCross order 
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    num_of_increments++;
    if (num_of_increments == container.size()+1) {
        throw runtime_error("Error - cannot increment, index out of bounds");
    }
    // increment only if the current element is from the right side of the container
    // the idea is to incremet the index evrey 2 elements, the operator* method calculates the value according to the index
    if (!fromStart) {
        ++index;
    }
    update_fromStart();
    return *this;
}

// returns the first element
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const {
    return SideCrossIterator(container, 0, true);
}

// returns the last element according to side cross order
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    // according to side cross order the last element will be the element in the middle of the vector
    if (container.elements.size() % 2 == 0) {
        return SideCrossIterator(container, container.elements.size() / 2, true);
    }
    return SideCrossIterator(container, container.elements.size() / 2, false);
}

// updates the fromStart attribute to be the opposite
void MagicalContainer::SideCrossIterator::update_fromStart() {
    this->fromStart = !fromStart;
}




//----------------------------- PrimeIterator class -----------------------------//
MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container_, size_t index_)
    : container(container_), index(index_) {}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
    : container(other.container), index(other.index) {}

MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &other)
    : container(other), index(0) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}


//--- Overlaoding Operators ---//
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
    if (&this->container != &other.container) {
        throw runtime_error("Error - cannot use operators on different containers");
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
    return &container == &other.container && index == other.index;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
    return index > other.index;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
    return index < other.index;
}

// returns the value of the prime number at the current index
int &MagicalContainer::PrimeIterator::operator*() const {
    return *container.prime_elements.at(index);
}

// increment index according to the index of the next prime element
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if (index >= container.prime_elements.size()) {
        throw runtime_error("Error - cannot increment, index out of range");
    }
    ++index;
    return *this;
}

// returns the first prime element
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
    return PrimeIterator(container, 0);
}

// returns the last prime element 
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
    return PrimeIterator(container, container.prime_elements.size());
}