//
// Created by malaklinux on 5/27/23.
//


#include "MagicalContainer.hpp"

using namespace ariel;

MagicalContainer::PrimeIterator::PrimeIterator() : Iterator(IteratorType::PRIME) ,index(0), container(*new MagicalContainer()) {}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) : Iterator(IteratorType::PRIME), index(0), container(container) {
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, size_t index) : Iterator(IteratorType::PRIME), index(index),
                                                                                            container(container) {}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : Iterator(IteratorType::PRIME), index(other.index),
                                                                             container(other.container) {}

MagicalContainer::PrimeIterator::~PrimeIterator() = default;

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
    if (*this != other) {
        if (&container != &other.container) {
            throw runtime_error("Error with operator=(): Iterators belong to different containers.");
        }
        index = other.index;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator==(): Iterators belong to different containers.");
    }
    return index == other.index;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator>(): Iterators belong to different containers.");
    }
    return index > other.index;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {

    return !(*this > other || *this == other);
}

int MagicalContainer::PrimeIterator::operator*() const {
    if (index < 0 || index >= container.vecPrime.size()) {
        throw runtime_error("Error with operator*(): Iterator out of range.");
    }
    return container.vecPrime[index];
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if (++index > container.vecPrime.size()) {
        throw runtime_error("Error with operator++(): Iterator incremented beyond end of container.");
    }
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    return PrimeIterator(container, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    return PrimeIterator(container, container.vecPrime.size());
}

MagicalContainer &MagicalContainer::PrimeIterator::getContainer() const {
    return container;
}

size_t MagicalContainer::PrimeIterator::getIndex() const {
    return index;
}


bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator==(): Iterators belong to different containers.");
    }
    const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
    return *this == otherPrimeIterator;
}

bool MagicalContainer::PrimeIterator::operator!=(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator!=(): Iterators belong to different containers.");
    }
    const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
    return *this != otherPrimeIterator;
}

bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator>(): Iterators belong to different containers.");
    }
    const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
    return *this > otherPrimeIterator;
}

bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator<(): Iterators belong to different containers.");
    }
    const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
    return *this < otherPrimeIterator;
}


