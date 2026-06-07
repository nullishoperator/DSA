#ifndef SortedArray_h
#define SortedArray_h

#include "ArrayInterface.h"
using namespace std;
template <class T>
class SortedArray : public ArrayInterface<T>
{
protected:
    

//MID SEARCH
    virtual int midSearch(T &&key) const
    {
        int l, mid = -1, h;
        l = 0;
        h = this->length - 1;

        while (l <= h)
        {
            mid = (l + h) / 2;
            if (key == get(mid))
                return mid;
            else if (key < get(mid))
                h = mid - 1;
            else
                l = mid + 1;
        }
        return mid;
    }

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
    T *dummy = nullptr;
//CONSTRUCTORS AND DESTRUCTORS AND ASSIGNMENT OPERATORS
    virtual ~SortedArray() override {
        delete dummy;
    }
    SortedArray() : ArrayInterface<T>() {}
    SortedArray(initializer_list<T> list) : ArrayInterface<T>()
    {
        this->initFromList(list);
    }
    SortedArray(int n) : ArrayInterface<T>(n) {}
    SortedArray(const SortedArray &other) : ArrayInterface<T>(other){}
    SortedArray(SortedArray &&other) noexcept : ArrayInterface<T>(move(other)){}
    SortedArray &operator=(const SortedArray &other)
    {
        if (this == &other)
            return *this;

        ArrayInterface<T>::operator=(other);
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
    SortedArray<T> operator+(SortedArray<T> &arr2)
    {
        int i, j, k;
        i = j = k = 0;

        SortedArray arr3(this->length + arr2.length);

        while (i < this->length && j < arr2.length)
        {
            if (get(i) < arr2.get(j))
                arr3.get(k++) = get(i++);
            else
                arr3.get(k++) = arr2.get(j++);
        }
        for (; i < this->length; i++)
            arr3.get(k++) = get(i);
        for (; j < arr2.length; j++)
            arr3.get(k++) = arr2.get(j);
        arr3.length = this->length + arr2.length;

        return arr3;
    }
    SortedArray<T> &operator+=(SortedArray<T> &arr2)
    {
        int i, j, k;
        i = j = k = 0;

        SortedArray arr3(this->length + arr2.length);

        while (i < this->length && j < arr2.length)
        {
            if (get(i) < arr2.get(j))
                arr3.get(k++) = get(i++);
            else
                arr3.get(k++) = arr2.get(j++);
        }
        for (; i < this->length; i++)
            arr3.get(k++) = get(i);
        for (; j < arr2.length; j++)
            arr3.get(k++) = arr2.get(j);
        arr3.length = this->length + arr2.length;
        *this = move(arr3);
        return *this;
    }



//INDEX OPERATORS

    virtual T &operator[](int index) override {
        dummy = new T{};
        *dummy = this->Data<T>::operator[](index);
        return *dummy;
    }
    virtual T &operator[](Special special)override {
        dummy = new T{};
        *dummy=this->Data<T>::operator[](special);
        return *dummy;
    }
    virtual T &operator[](int index) const override{
        return this->Data<T>::operator[](index);
    }
    virtual T &operator[](Special special) const override{
        return this->Data<T>::operator[](special);
    }

//INSERT 
    virtual Data<T> &insert(T val) override
    {

        int i = this->length - 1;
        if (this->length == this->size)
            this->increase(10);

        while (i >= 0 && get(i) > val)
        {
            get(i + 1) = get(i);
            i--;
        }

        get(i + 1) = val;
        (this->length)++;
        return (*this);
    }

    virtual Data<T> &insert(int index, T val) override
    {
        return insert(val);
    }
    virtual Data<T> &insert(Special special, T val) override
    {
        return insert(val);
    }

//MIX MAX
    T min() const override
    {
        return get(0);
    }
    T max() const override
    {
        return get(this->length - 1);
    }

//POINTER
    virtual Data<T> *pointer(int n) override
    {
        SortedArray<T> *p = new SortedArray(n);
        return p;
    }

//UITL
    bool isSorted() override
    {
        return true;
    }
    virtual Data<T> &reverse() override
    {
        return (*this);
    }


    virtual int search(T &&key) const override
    {
        int mid = midSearch(forward<T>(key));

        if (mid != -1 && get(mid) == key)
            return mid;
        else
            return -1;
    }
    virtual int search(T &key) const override
    {
        return search(forward<T>(key));
    }




};

#endif