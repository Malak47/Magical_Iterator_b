//
// Created by malaklinux on 5/27/23.
//


#include "MagicalContainer.hpp"

using namespace ariel;

MagicalContainer::MagicalContainer() : vecElements(), vecPrime() {}

void MagicalContainer::addElement(int element) {
    addAndSortElements(element);
}

void MagicalContainer::removeElement(int element) {
    if (isPrime(element)) {
        auto it = lower_bound(vecPrime.begin(), vecPrime.end(), element); // element <= ...
        if (it != vecPrime.end() && *it == element) {
            vecPrime.erase(it);
        }
    }

    auto it = std::lower_bound(vecElements.begin(), vecElements.end(), element); // element <= ...
    if (it != vecElements.end() && *it == element) {
        vecElements.erase(it);
        return;
    }
    throw runtime_error("Error: No Element To Remove.");
}

size_t MagicalContainer::size() const { return vecElements.size(); }

void MagicalContainer::addAndSortElements(int element) {
    if (isPrime(element)) {
        auto it = lower_bound(vecPrime.begin(), vecPrime.end(), element); // element <= ...
        if (it == vecPrime.end() || *it != element) {
            vecPrime.insert(it, element);
        }
    }
    auto it = lower_bound(vecElements.begin(), vecElements.end(), element); // element <= ...
    if (it == vecElements.end() || *it != element) {
        vecElements.insert(it, element);
    }
}

bool MagicalContainer::isPrime(int number) {
    if (number <= 1) {
        return false;
    }

    if (number == 2) {
        return true;
    }

    if (number % 2 == 0) {
        return false;
    }

    for (int i = 3; i <= sqrt(number); i += 2) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

const vector<int> &MagicalContainer::getElements() const {
    return vecElements;
}
