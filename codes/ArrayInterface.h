#ifndef ArrayInterface_h
#define ArrayInterface_h

#include "Data.h"
using namespace std;

template <class T>
class ArrayInterface : public Data<T>
{

protected:
    int size;
    T *A;
//INTERNAL GET
    virtual T &get(int index) override
    {
        return this->A[index];
    }

    T &get(int index) const override
    {
        return this->A[index];
    }

//INTERNAL CONSTRUCTORS
    ArrayInterface() : Data<T>(), size(0), A(nullptr) {}
    ArrayInterface(initializer_list<T> list) : Data<T>(), size(list.size()), A(new T[list.size()])
    {
        this->initFromList(list);
    }
    ArrayInterface(int n) : Data<T>(), size(n), A(new T[n]())
    {
        this->length = 0;
    }
  



public:


//CONSTRUCTORS AND DESTRUCTORS AND ASSIGNMENT OPERATOR
    virtual ~ArrayInterface() override
    {
        delete[] A;
    }

    ArrayInterface(const ArrayInterface &other) : Data<T>(other), size(other.size), A(new T[other.size])
    {
        this->length = other.length;
        for (int i = 0; i < this->length; i++)
            get(i) = other.get(i);
    }

    ArrayInterface(ArrayInterface &&other) noexcept : Data<T>(std::move(other)), size(other.size), A(other.A)
    {
        this->length = other.length;
        other.A = nullptr;
        other.size = 0;
        other.length = 0;
    }

    virtual Data<T> &operator=(const Data<T> &other) override
    {
        if (this != &other)
            this->Data<T>::operator=(other);
        return *this;
    }
    ArrayInterface &operator=(const ArrayInterface &other)
    {
        if (this == &other)
            return *this;

        delete[] A;

        size = other.size;
        this->length = other.length;
        A = new T[size];
        for (int i = 0; i < this->length; i++)
            get(i) = other.get(i);

        return *this;
    }
    ArrayInterface &operator=(ArrayInterface &&other) noexcept
    {
        if (this == &other)
            return *this;

        Data<T>::operator=(std::move(other));
        delete[] A;

        size = other.size;
        this->length = other.length;
        A = other.A;

        other.A = nullptr;
        other.size = 0;
        other.length = 0;

        return *this;
    }

//PLUST OPERATORS
    Data<T> &operator+(Data<T> &data) override
    {
        return this->Data<T>::operator+(data);
    }
    Data<T> &operator+=(Data<T> &data) override
    {
        this->Data<T>::operator+=(data);
        return *this;
    }

//INDEX OPERATORS
    

//INSERT AND REMOVE
    virtual Data<T> &insert(int index, T val) override
    {

        index = this->toInt(index);
        if (this->length == size)
            increase(10);
        for (int i = this->length; i > index; i--)
            get(i) = get(i - 1);
        get(index) = val;
        (this->length)++;
        return (*this);
    }

    virtual Data<T> &insert(Special special, T val) override
    {
        if (special == FIRST)
            return this->insert(this->toInt(special), val);
        else
            return this->insert(this->toInt(special) + 1, val);
    }
    virtual Data<T> &insert(T val) override
    {
        return this->insert(this->toInt(LAST) + 1, val);
    }

    virtual Data<T> &remove(int index) override
    {
        index = this->toInt(index);
        if (index < 0 || index >= this->length)
            throw out_of_range("Index out of range");
        for (int i = index; i < (this->length) - 1; i++)
            get(i) = get(i + 1);
        (this->length)--;
        return (*this);
    }
    virtual Data<T> &remove(Special special) override
    {
        return this->remove(this->toInt(special));
    }
    virtual Data<T> &remove() override
    {
        return this->remove(LAST);
    }


//RESIZE
    Data<T> &resize(int val)
    {
        T *B = new T[val];
        for (int i = 0; i < this->length; i++)
            B[i] = get(i);
        delete[] A;
        A = B;
        size = val;
        return (*this);
    }

    Data<T> &increase(int val)
    {
        return resize(size + val);
    }

//UTILITY
    int getSize() const
    {
        return this->size;
    }
};

#endif