#include "MagicalContainer.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;
using namespace ariel;

//----------------------------- MagicalContainer class -----------------------------//
MagicalContainer::MagicalContainer() {}

void MagicalContainer::addElement(int element)
{
    // Check if the element already exists in the container
    if (find(elements.begin(), elements.end(), element) != elements.end())
    {
        return;
    }

    // Find the insertion position using lower_bound
    auto insertPos = lower_bound(elements.begin(), elements.end(), element);

    // Insert the element at the determined position
    elements.insert(insertPos, element);

    // if (isPrime(element))
    // {
    //     auto insertPos = lower_bound(prime_elements.begin(), prime_elements.end(), element);
    //     prime_elements.insert(insertPos, &element);
    // }

    prime_elements.clear();
    for (size_t i = 0; i < size(); i++)
    {
        if (isPrime(elements[i]))
        {
            prime_elements.push_back(&elements[i]);
        }
    }
}

void MagicalContainer::removeElement(int element)
{
    // Check if the element exists in the container
    auto erasePos = find(elements.begin(), elements.end(), element);
    if (erasePos == elements.end())
    {
        throw runtime_error("Error - element doesnt exists in the container");
    }

    elements.erase(erasePos);

    if (isPrime(element))
    {
        // if the given element is prime erase from prime_elements as well
        auto primePos = find(prime_elements.begin(), prime_elements.end(), &(*erasePos));
        if (primePos != prime_elements.end())
        {
            prime_elements.erase(primePos);
        }
    }
}

size_t MagicalContainer::size() const
{
    return elements.size();
}

std::vector<int> MagicalContainer::getElements() const
{
    return elements;
}

bool MagicalContainer::isPrime(int number) const
{
    if (number <= 1)
        return false;
    for (int i = 2; i * i <= number; ++i)
    {
        if (number % i == 0)
            return false;
    }
    return true;
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

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    if (index >= container.elements.size()) {
        throw runtime_error("Error - cannot increment, index out of range");
    }
    index++;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
    return AscendingIterator(container, 0);
}

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

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
    return (*this).operator*() > (other).operator*();
    // return container.getElements()[index] > other.container.getElements()[index];
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
    // return container.getElements()[index] < other.container.getElements()[index];
    return (*this).operator*() < (other).operator*();
}

int MagicalContainer::SideCrossIterator::operator*() const {
    // size_t new_index = 0;
    if (!fromStart) {
        return container.elements[container.size() - index - 1];
    }
    return container.elements[index];
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    st++;
    if (st == container.size()+1) {
        throw runtime_error("Error - cannot increment, index out of bounds");
    }
    if (!fromStart) {
        ++index;
    }
    update_fromStart();
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const {
    return SideCrossIterator(container, 0, true);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    if (container.elements.size() % 2 == 0) {
        return SideCrossIterator(container, container.elements.size() / 2, true);
    }
    return SideCrossIterator(container, container.elements.size() / 2, false);
}

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

int &MagicalContainer::PrimeIterator::operator*() const {
    return *container.prime_elements.at(index);
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if (index >= container.prime_elements.size()) {
        throw runtime_error("Error - cannot increment, index out of range");
    }
    ++index;
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
    return PrimeIterator(container, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
    return PrimeIterator(container, container.prime_elements.size());
}