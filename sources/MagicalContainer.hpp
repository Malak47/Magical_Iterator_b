//
// Created by malaklinux on 5/24/23.
//

#ifndef MAGICAL_ITERATORS_MAGICALCONTAINER_HPP
#define MAGICAL_ITERATORS_MAGICALCONTAINER_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include "cmath"

using namespace std;
namespace ariel {

    class MagicalContainer {
    private:
        vector<int> vecElements;
        vector<int> vecPrime;

    public:
        MagicalContainer();

        void addElement(int element);
        void removeElement(int element);
        size_t size() const;
        vector<int> getElements();

        void addAndSortElements(int element);
        static bool isPrime(int number);

        //********************************************************************************
        //********** I T E R A T O R   I N T E R F A C E *********************************
        //********************************************************************************
        enum class IteratorType { ASCENDING, SIDE_CROSS, PRIME, UNDEFINED };

        class Iterator {
        protected:
            IteratorType iterType;
        public:
            Iterator() : iterType(IteratorType::UNDEFINED){};
            Iterator( IteratorType iterType) : iterType(iterType){};

            virtual ~Iterator() = default;

            Iterator(const Iterator &other) = default;
            Iterator(Iterator &&other) = default;

            Iterator &operator=(const Iterator &other) = default;
            Iterator& operator=(Iterator&& other) = default;

            virtual bool operator==(const Iterator& other) const = 0;
            virtual bool operator!=(const Iterator& other) const = 0;
            virtual bool operator>(const Iterator& other) const = 0;
            virtual bool operator<(const Iterator& other) const = 0;

            virtual IteratorType getType() const = 0; // pure virtual function

        };

        //********************************************************************************
        //********** A S C E N D I N G   I T E R A T O R *********************************
        //********************************************************************************

        class AscendingIterator : public Iterator{
        private:
            MagicalContainer *container;
            size_t index;
        public:
            AscendingIterator();
            AscendingIterator(MagicalContainer &container);
            AscendingIterator(MagicalContainer &container, size_t index);
            AscendingIterator(const AscendingIterator &other);
            ~AscendingIterator() override;
            AscendingIterator(AscendingIterator &&) noexcept = delete;

            AscendingIterator &operator=(AscendingIterator &&) noexcept = delete;
            AscendingIterator &operator=(const AscendingIterator &other);

            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;

            bool operator==(const Iterator &other) const override;
            bool operator!=(const Iterator &other) const override;
            bool operator>(const Iterator &other) const override;
            bool operator<(const Iterator &other) const override;

            int operator*() const;

            AscendingIterator &operator++();

            AscendingIterator begin();
            AscendingIterator end();

            MagicalContainer getContainer() const;
            size_t getIndex() const;
            IteratorType getType() const override { return IteratorType::ASCENDING; }


        };

        //********************************************************************************
        //********** S I D E - C R O S S   I T E R A T O R *******************************
        //********************************************************************************

        class SideCrossIterator : public Iterator {
        private:
            MagicalContainer *container;
            size_t frontIndex, backIndex;
            int increments = 0; // Number of times the iterator has been incremented.

        public:
            SideCrossIterator();
            SideCrossIterator(MagicalContainer &container);
            SideCrossIterator(MagicalContainer &container, size_t fronIndex, size_t backIndex);

            SideCrossIterator(const SideCrossIterator &other);
            ~SideCrossIterator() override;
            SideCrossIterator(SideCrossIterator &&) noexcept = delete;

            SideCrossIterator &operator=(SideCrossIterator &&) noexcept = delete;
            SideCrossIterator &operator=(const SideCrossIterator &other);

            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;

            bool operator==(const Iterator &other) const override;
            bool operator!=(const Iterator &other) const override;
            bool operator>(const Iterator &other) const override;
            bool operator<(const Iterator &other) const override;

            int operator*() const;

            SideCrossIterator &operator++();

            SideCrossIterator begin();
            SideCrossIterator end();

            MagicalContainer getContainer() const;
            size_t getFrontIndex() const;
            size_t getBackIndex() const;
            IteratorType getType() const override { return IteratorType::SIDE_CROSS; }


        };

        //********************************************************************************
        //********** P R I M E   I T E R A T O R *****************************************
        //********************************************************************************

        class PrimeIterator : public Iterator{
        private:
            MagicalContainer *container;
            size_t index;

        public:
            PrimeIterator();
            PrimeIterator(MagicalContainer &container);
            PrimeIterator(MagicalContainer &container, size_t index);
            PrimeIterator(const PrimeIterator &other);
            ~PrimeIterator() override;
            PrimeIterator(PrimeIterator &&) noexcept = delete;

            PrimeIterator &operator=(PrimeIterator &&) noexcept = delete;
            PrimeIterator &operator=(const PrimeIterator &other);

            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            bool operator>(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;

            bool operator==(const Iterator &other) const override;
            bool operator!=(const Iterator &other) const override;
            bool operator>(const Iterator &other) const override;
            bool operator<(const Iterator &other) const override;

            int operator*() const;

            PrimeIterator &operator++();

            PrimeIterator begin();
            PrimeIterator end();

            MagicalContainer getContainer() const;
            size_t getIndex() const;
            IteratorType getType() const override { return IteratorType::PRIME; }

        };
    };
}
#endif //MAGICAL_ITERATORS_MAGICALCONTAINER_HPP
