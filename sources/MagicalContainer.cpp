#include "MagicalContainer.hpp"
#include "MyIterator.hpp"
#include <vector>
#include <algorithm>
using namespace std;
using namespace ariel;


//----------------------------- MagicalContainer class -----------------------------//
MagicalContainer::MagicalContainer() {

}

void MagicalContainer::addElement(int element) {

}

void MagicalContainer::removeElement(int element) {

}

size_t MagicalContainer::size() const {
    return elements.size();
}

std::vector<int> MagicalContainer::getElements() const{
    return elements;
}




//----------------------------- AscendingIterator class -----------------------------//

MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& container_, int index_)
    : container(container_), index(index_) {}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : container(other.container), index(other.index) {}

MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& other)
    : container(other), index(0) {}

MagicalContainer::AscendingIterator::~AscendingIterator() {}

//--- Overlaoding Operators ---//
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
    if (&container != &other.container) {
        throw std::runtime_error("Error- Cannot use operators on different containers");
    }
    index = other.index;
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const MyIterator& other) const {
    const AscendingIterator* castedOther = dynamic_cast<const AscendingIterator*>(&other);
    if (castedOther == nullptr) {
        throw std::runtime_error("Error- Cannot use operators on different iterators type");
    }
    if (&container != &castedOther->container){
        throw std:: runtime_error("Error- Cannot use operators on different containers");
    }
    return index == castedOther->index;
}

bool MagicalContainer::AscendingIterator::operator!=(const MyIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const MyIterator& other) const {
    const AscendingIterator* castedOther = dynamic_cast<const AscendingIterator*>(&other);
    if (castedOther == nullptr) {
        throw std::runtime_error("Error- Cannot use operators on different iterators type");
    }
    if (&container != &castedOther->container){
        throw std:: runtime_error("Error- Cannot use operators on different containers");
    }
    return index > castedOther->index;
}

bool MagicalContainer::AscendingIterator::operator<(const MyIterator& other) const {
    const AscendingIterator* castedOther = dynamic_cast<const AscendingIterator*>(&other);
    return (index != castedOther->index) && !(index > castedOther->index);
}

int MagicalContainer::AscendingIterator::operator*() const {
    return container.getElements().at(index);
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    ++index;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
    return AscendingIterator(container, 0);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const{
    return AscendingIterator(container, container.elements.size());
}




//----------------------------- SideCrossIterator class -----------------------------//

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& container_, int index_, bool fromStart_)
    : container(container_), index(0), fromStart(false) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    : container(other.container), index(other.index), fromStart(other.fromStart) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& other)
    : container(other), index(0), fromStart(true) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}


//--- Overloading Operators ---//
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
    if (&container != &other.container) {
        throw std::runtime_error("Error- Cannot use operators on different containers");
    }
    index = other.index;
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const MyIterator& other) const {
    const SideCrossIterator* castedOther = dynamic_cast<const SideCrossIterator*>(&other);
    if (castedOther == nullptr) {
        throw std::runtime_error("Error- Cannot use operators on different iterators type");
    }
    if (&container != &castedOther->container){
        throw std:: runtime_error("Error- Cannot use operators on different containers");
    }
    return index == castedOther->index;
}

bool MagicalContainer::SideCrossIterator::operator!=(const MyIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const MyIterator& other) const {
    const SideCrossIterator* castedOther = dynamic_cast<const SideCrossIterator*>(&other);
    if (castedOther == nullptr) {
        throw std::runtime_error("Error- Cannot use operators on different iterators type");
    }
    if (&container != &castedOther->container){
        throw std:: runtime_error("Error- Cannot use operators on different containers");
    }
    return index > castedOther->index;
}

bool MagicalContainer::SideCrossIterator::operator<(const MyIterator& other) const {
    const SideCrossIterator* castedOther = dynamic_cast<const SideCrossIterator*>(&other);
    return (index != castedOther->index) && !(index > castedOther->index);
}

int MagicalContainer::SideCrossIterator::operator*() const {
    return 0;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const{
    return SideCrossIterator(container, 0, false);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const{
    int index = container.size();
    bool fromStart = (index % 2 == 0);
    return SideCrossIterator(container, index, fromStart);
}




//----------------------------- PrimeIterator class -----------------------------//
MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& container_, int index_)
    : container(container_), index(index_) {}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
    : container(other.container), index(other.index) {}

MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& other)
    : container(other), index(0) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}


//--- Overlaoding Operators ---//
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const MyIterator& other) const {
    const PrimeIterator* castedOther = dynamic_cast<const PrimeIterator*>(&other);
    if (castedOther == nullptr) {
        throw std::runtime_error("Error- Cannot use operators on different iterators type");
    }
    if (&container != &castedOther->container){
        throw std:: runtime_error("Error- Cannot use operators on different containers");
    }
    return index == castedOther->index;
}

bool MagicalContainer::PrimeIterator::operator!=(const MyIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const MyIterator& other) const {
    const PrimeIterator* castedOther = dynamic_cast<const PrimeIterator*>(&other);
    if (castedOther == nullptr) {
        throw std::runtime_error("Error- Cannot use operators on different iterators type");
    }
    if (&container != &castedOther->container){
        throw std:: runtime_error("Error- Cannot use operators on different containers");
    }
    return index > castedOther->index;
}

bool MagicalContainer::PrimeIterator::operator<(const MyIterator& other) const {
    const PrimeIterator* castedOther = dynamic_cast<const PrimeIterator*>(&other);
    return (index != castedOther->index) && !(index > castedOther->index);
}

int MagicalContainer::PrimeIterator::operator*() const {
    return 0;
}

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

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const{
    return PrimeIterator(container, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const{
    return PrimeIterator(container, container.elements.size());
}
