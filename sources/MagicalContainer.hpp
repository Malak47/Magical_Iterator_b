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
        void addAndSortElements(int element);
        static bool isPrime(int number);

    public:
        MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        size_t size() const;
        const vector<int> &getElements () const;

        //********************************************************************************
        //********** I T E R A T O R   I N T E R F A C E *********************************
        //********************************************************************************

        enum class IteratorType { ASCENDING, SIDE_CROSS, PRIME };

        class Iterator {
        private:
            IteratorType iterType;
        public:
            Iterator(IteratorType iterType) : iterType(iterType){};

            virtual ~Iterator() = default;

            Iterator(const Iterator &other) = default;                      //Copy constructor
            Iterator(Iterator &&other) = default;                           //Move constructor
            Iterator &operator=(const Iterator &other) = default;           //Copy assignment operator
            Iterator& operator=(Iterator&& other) = default;                //Move assignment operator

            virtual bool operator==(const Iterator& other) const = 0;
            virtual bool operator!=(const Iterator& other) const = 0;
            virtual bool operator>(const Iterator& other) const = 0;
            virtual bool operator<(const Iterator& other) const = 0;

             IteratorType getIterType() const {return iterType;};
        };

        //********************************************************************************
        //********** A S C E N D I N G   I T E R A T O R *********************************
        //********************************************************************************

        class AscendingIterator : public Iterator{
        private:
            MagicalContainer &container;
            size_t index;
        public:
            AscendingIterator();
            AscendingIterator(MagicalContainer &container);
            AscendingIterator(MagicalContainer &container, size_t index);

            ~AscendingIterator() override;

            AscendingIterator(const AscendingIterator &other);                           //Copy constructor
            AscendingIterator(AscendingIterator &&) noexcept = delete;                   //Move constructor
            AscendingIterator &operator=(const AscendingIterator &other);                //Move assignment operator
            AscendingIterator &operator=(AscendingIterator &&) noexcept = delete;        //Copy assignment operator

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

            MagicalContainer &getContainer() const;
            size_t getIndex() const;

        };

        //********************************************************************************
        //********** S I D E - C R O S S   I T E R A T O R *******************************
        //********************************************************************************

        class SideCrossIterator : public Iterator {
        private:
            MagicalContainer &container;
            size_t frontIndex, backIndex;
            int increments = 0;

        public:
            SideCrossIterator();
            SideCrossIterator(MagicalContainer &container);
            SideCrossIterator(MagicalContainer &container, size_t frontIndex, size_t backIndex);

            ~SideCrossIterator() override;

            SideCrossIterator(const SideCrossIterator &other);                          //Copy constructor
            SideCrossIterator(SideCrossIterator &&) noexcept = delete;                  //Move constructor
            SideCrossIterator &operator=(const SideCrossIterator &other);               //Move assignment operator
            SideCrossIterator &operator=(SideCrossIterator &&) noexcept = delete;       //Copy assignment operator

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

            MagicalContainer &getContainer() const;
            size_t getFrontIndex() const;
            size_t getBackIndex() const;
        };

        //********************************************************************************
        //********** P R I M E   I T E R A T O R *****************************************
        //********************************************************************************

        class PrimeIterator : public Iterator{
        private:
            MagicalContainer &container;
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

            MagicalContainer &getContainer() const;
            size_t getIndex() const;
        };
    };
}
#endif //MAGICAL_ITERATORS_MAGICALCONTAINER_HPP
