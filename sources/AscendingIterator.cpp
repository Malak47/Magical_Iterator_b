//
// Created by malaklinux on 5/27/23.
//

#include "MagicalContainer.hpp"

using namespace ariel;

MagicalContainer::AscendingIterator::AscendingIterator() : Iterator(IteratorType::ASCENDING), index(0),
                                                           container(*new MagicalContainer()) {}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) : Iterator(IteratorType::ASCENDING),
                                                                                      index(0), container(container) {}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t index) : Iterator(
        IteratorType::ASCENDING),
                                                                                                    index(index),
                                                                                                    container(
                                                                                                            container) {
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : Iterator(
        IteratorType::ASCENDING), index(other.index), container(other.container) {}

MagicalContainer::AscendingIterator::~AscendingIterator() = default;

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
    if (this != &other) {
        if (&container != &other.container) {
            throw runtime_error("Error with operator=(): Iterators belong to different containers.");
        }
        index = other.index;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator==(): Iterators belong to different containers.");
    }
    return index == other.index;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator>(): Iterators belong to different containers.");
    }
    return index > other.index;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {

    return !(*this > other || *this == other);
}

int MagicalContainer::AscendingIterator::operator*() const {
    if (index < 0 || index >= container.size()) {
        throw runtime_error("Error with operator*(): Iterator out of range.");
    }
    return container.vecElements[index];
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    if (++index > container.size()) {
        throw runtime_error("Error with operator++(): Iterator incremented beyond end of container.");
    }
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    return AscendingIterator(container, 0);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    return AscendingIterator(container, container.size());
}

MagicalContainer &MagicalContainer::AscendingIterator::getContainer() const {
    return container;
}

size_t MagicalContainer::AscendingIterator::getIndex() const {
    return index;
}

bool MagicalContainer::AscendingIterator::operator==(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator==(): Iterators belong to different containers.");
    }
    const auto &otherAscendingIterator = dynamic_cast<const AscendingIterator &>(other);
    return *this == otherAscendingIterator;
}

bool MagicalContainer::AscendingIterator::operator!=(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator!=(): Iterators belong to different containers.");
    }
    const auto &otherAscendingIterator = dynamic_cast<const AscendingIterator &>(other);
    return *this != otherAscendingIterator;
}

bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator>(): Iterators belong to different containers.");
    }
    const auto &otherAscendingIterator = dynamic_cast<const AscendingIterator &>(other);
    return *this > otherAscendingIterator;
}

bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator<(): Iterators belong to different containers.");
    }
    const auto &otherAscendingIterator = dynamic_cast<const AscendingIterator &>(other);
    return *this < otherAscendingIterator;
}





