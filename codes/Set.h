#ifndef Set_h
#define Set_h

#include "SortedArray.h"
using namespace std;

template <class T>
class Set : public SortedArray<T>
{
protected:
//INTERNAL GET
    virtual T &get(int index) override
    {
        return this->A[index];
    }

    T &get(int index) const
    {
        return this->A[index];
    }

public:
//CONSTRUCTORS AND DESTRUCTORS AND ASSIGNMENT OPERATORS
    Set() : SortedArray<T>() {}
    virtual ~Set() override = default;
    Set(initializer_list<T> list) : SortedArray<T>()
    {
        this->initFromList(list);
    }
    Set(int n) : SortedArray<T>(n) {}
    Set(const Set &other) : SortedArray<T>(other) {}
    Set(Set &&other) noexcept : SortedArray<T>(move(other)) {}
    Set &operator=(const Set &other)
    {
        if (this == &other)
            return *this;

        SortedArray<T>::operator=(other);
        return *this;
    }
    Data<T> &operator=(const Data<T> &other)
    {
        if (this != &other)
            this->Data<T>::operator=(other);
        return *this;
    }
    ArrayInterface<T> &operator=(ArrayInterface<T> &&other) noexcept
    {
        if (this == &other)
            return *this;
        this->ArrayInterface<T>::operator=(other);
        return *this;
    }

//PLUS OPERATORS
    Data<T> &operator+(Data<T> &other) override
    {
        return this->Data<T>::operator+(other);
    }
    Data<T> &operator+=(Data<T> &other) override
    {
        this->Data<T>::operator+=(other);
        return *this;
    }

    Set<T> operator+(Set<T> &arr2)
    {

        int i, j, k;
        i = j = k = 0;

        Set<T> *arr3 = new Set<T>(this->length + arr2.length);

        while (i < this->length && j < arr2.length)
        {
            if (get(i) < get(j))
                arr3->get(k++) = get(i++);
            else if (arr2.get(j) < get(i))
                arr3->get(k++) = arr2.get(j++);
            else
            {
                arr3->get(k++) = get(i++);
                j++;
            }
        }
        for (; i < this->length; i++)
            arr3->get(k++) = get(i);
        for (; j < arr2.length; j++)
            arr3->get(k++) = arr2.get(j);

        arr3->length = k;

        return *arr3;
    }
    Set<T> &operator+=(Set<T> &arr2)
    {

        int i, j, k;
        i = j = k = 0;

        Set<T> *arr3 = new Set<T>(this->length + arr2.length);

        while (i < this->length && j < arr2.length)
        {
            if (get(i) < arr2.get(j))
                arr3->get(k++) = get(i++);
            else if (arr2.get(j) < get(i))
                arr3->get(k++) = arr2.get(j++);
            else
            {
                arr3->get(k++) = get(i++);
                j++;
            }
        }
        for (; i < this->length; i++)
            arr3->get(k++) = get(i);
        for (; j < arr2.length; j++)
            arr3->get(k++) = arr2.get(j);

        arr3->length = k;
        *this = move(*arr3);

        return *this;
    }
//INDEX OPERATOR 

//DIFFERENCE OPERATORS
    Set<T> &operator-(Set<T> &arr2)
    {

        int i, j, k;
        i = j = k = 0;

        Set<T> *arr3 = new Set<T>(this->length);

        while (i < this->length && j < arr2.length)
        {
            if (get(i) < arr2.get(j))
                arr3->get(k++) = get(i++);
            else if (arr2.get(j) < get(i))
                j++;
            else
            {
                i++;
                j++;
            }
        }
        for (; i < this->length; i++)
            arr3->get(k++) = get(i);

        arr3->length = k;

        return *arr3;
    }
    Set<T> &operator-=(Set<T> &arr2)
    {
        int i, j, k;
        i = j = k = 0;

        Set<T> *arr3 = new Set<T>(this->length);

        while (i < this->length && j < arr2.length)
        {
            if (get(i) < arr2.get(j))
                arr3->get(k++) = get(i++);
            else if (arr2.get(j) < get(i))
                j++;
            else
            {
                i++;
                j++;
            }
        }
        for (; i < this->length; i++)
            arr3->get(k++) = get(i);

        arr3->length = k;
        *this = move(*arr3);

        return *this;
    }

//INTERSECTION OPERATORS
    Set<T>& operator&(Set<T> &other)
    {
        int i, j, k;
        i = j = k = 0;

        Set<T> *arr3 = new Set<T>(this->length);

        while (i < this->length && j < other.length)
        {
            if (get(i) < other.get(j))
                i++;
            else if (other.get(j) < get(i))
                j++;
            else if (get(i) == other.get(j))
            {
                arr3->get(k++) = get(i++);
                j++;
            }
        }

        arr3->length = k;

        return *arr3;
    }
    Set<T> & operator&=(Set<T> &other)
    {
        int i, j, k;
        i = j = k = 0;

        Set<T> *arr3 = new Set<T>(this->length);

        while (i < this->length && j < other.length)
        {
            if (get(i) < other.get(j))
                i++;
            else if (other.get(j) < get(i))
                j++;
            else if (get(i) == other.get(j))
            {
                arr3->get(k++) = get(i++);
                j++;
            }
        }

        arr3->length = k;
        *this = move(*arr3);

        return *this;
    }
//INSERT
    virtual Data<T> &insert(T val) override
    {
        int index = this->midSearch(forward<T>(val));

        if (index == -1 || get(index) != val)
            this->SortedArray<T>::insert(val);
        return *this;
    }
    virtual Data<T> &insert(int index, T val) override
    {
        return this->insert(val);
    }
    virtual Data<T> &insert(Special special, T val) override
    {
        return this->insert(val);
    }
//POINTER
    virtual Data<T> *pointer(int n) override
    {
        Set<T> *p = new Set<T>(n);
        return p;
    }

//UTILITY
    Set<Set<T>> subsets()
    {

        int total_subsets = 1 << this->length;
        Set<Set<T>> result;
        for (int i = 0; i < total_subsets; i++)
        {
            Set<T> subset;
            for (int j = 0; j < this->length; j++)
                if (i & (1 << j))
                    subset.insert(get(j));

            result.insert(subset); // Use insert to add the subset
        }
        return result; // Return the result by value
    }
};

#endif