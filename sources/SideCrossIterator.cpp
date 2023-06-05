//
// Created by malaklinux on 5/27/23.
//


#include "MagicalContainer.hpp"

using namespace ariel;

MagicalContainer::SideCrossIterator::SideCrossIterator() : Iterator(IteratorType::SIDE_CROSS), frontIndex(0),
                                                           backIndex(container.size() - 1),
                                                           container(*new MagicalContainer()) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) : Iterator(
        IteratorType::SIDE_CROSS), frontIndex(0), backIndex(container.size() - 1), container(container) {
    if (container.size() == 0) {
        backIndex = 0;
    }
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t frontIndex, size_t backIndex)
        : Iterator(IteratorType::SIDE_CROSS), frontIndex(frontIndex), backIndex(backIndex), container(container) {
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : Iterator(
        IteratorType::SIDE_CROSS), frontIndex(other.frontIndex), backIndex(other.backIndex),
                                                                                         container(other.container) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() = default;

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
    if (this != &other) {
        if (&container != &other.container) {
            throw runtime_error("Error with operator=(): Iterators belong to different containers.");
        }
        frontIndex = other.frontIndex;
        backIndex = other.backIndex;
    }
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator==(): Iterators belong to different containers.");
    }
    return (frontIndex == other.frontIndex && backIndex == other.backIndex);
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator>(): Iterators belong to different containers.");
    }
    // The iterator closer to the middle is considered "greater"
    return (min(frontIndex, backIndex) > min(other.frontIndex, other.backIndex));
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator<(): Iterators belong to different containers.");
    }
    // The iterator closer to the start/end is considered "lesser"
    return (max(frontIndex, backIndex) < max(other.frontIndex, other.backIndex));
}


MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    if (frontIndex > backIndex) {
        throw runtime_error("Error with operator++(): Iterator has reached its end.");
    }
    // If we are at an even count of increments, we increment the front index.
    // Otherwise, we decrement the back index.
    if (increments % 2 == 0) {
        frontIndex++;
    } else {
        backIndex--;
    }
    increments++;
    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() const {
    if (frontIndex > backIndex) {
        throw runtime_error("Error with operator*(): Iterator has reached its end.");
    }
    // If we are at an even count of increments, we return from the front.
    // Otherwise, we return from the back.
    if (increments % 2 == 0) {
        return container.vecElements[frontIndex];
    } else {
        return container.vecElements[backIndex];
    }
}


MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return {container, 0, container.size() - 1};
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    size_t mid = (container.size() + 1) / 2;
    if (mid == 0) {
        return {container, mid, mid};
    }
    return {container, mid, mid - 1};
}


MagicalContainer &MagicalContainer::SideCrossIterator::getContainer() const {
    return container;
}

size_t MagicalContainer::SideCrossIterator::getFrontIndex() const {
    return frontIndex;
}

size_t MagicalContainer::SideCrossIterator::getBackIndex() const {
    return backIndex;
}

bool MagicalContainer::SideCrossIterator::operator==(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator==(): Iterators belong to different containers.");
    }
    const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
    return *this == otherSideCrossIterator;
}

bool MagicalContainer::SideCrossIterator::operator!=(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator!=(): Iterators belong to different containers.");
    }
    const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
    return *this != otherSideCrossIterator;
}

bool MagicalContainer::SideCrossIterator::operator>(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator>(): Iterators belong to different containers.");
    }
    const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
    return *this > otherSideCrossIterator;
}

bool MagicalContainer::SideCrossIterator::operator<(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator<(): Iterators belong to different containers.");
    }
    const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
    return *this < otherSideCrossIterator;
}



