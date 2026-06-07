#ifndef Array_h
#define Array_h

#include "ArrayInterface.h"
using namespace std;

template <class T>
class Array : public ArrayInterface<T>
{

protected:
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
    virtual ~Array() override = default;
    Array() : ArrayInterface<T>() {}
    Array(initializer_list<T> list) : ArrayInterface<T>()
    {
        this->initFromList(list);
    }
    Array(int n) : ArrayInterface<T>(n) {}
    
    Array(const Array &other) : ArrayInterface<T>(other) {}
    Array(Array &&other) noexcept : ArrayInterface<T>(move(other)) {}
    Array &operator=(const Array<T> &other)
    {
        if (this != &other)
            this->ArrayInterface<T>::operator=(other);
        return *this;
    }
    Data<T> &operator=(const Data<T> &other) override
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

//INDEX OPERATORS
    

    
//POINTER
    virtual Data<T> *pointer(int n) override
    {
        Array<T> *p = new Array(n);
        return p;
    };
};

#endif