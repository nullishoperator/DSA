#ifndef Queue_h
#define Queue_h

#include "Array.h"
using namespace std;

template <class T>
class Queue : public Array<T>
{
protected:
    int front = 0;

//INTERNAL GET
    virtual T &get(int index) override
    {
        
        front %= this->size;
        index = (index + front) % (this->size);
        return this->A[index];
    }

    T &get(int index) const
    {
        
        return this->A[(index + front) % (this->size)];
    }

public:
//CONSTRUCTORS AND DESTRUCTORS AND ASSIGNMENT OPERATORS
    Queue() : Array<T>() {}
    virtual ~Queue() override = default;
    Queue(initializer_list<T> list) : Array<T>(list.size())
    {
        this->initFromList(list);
    }
    Queue(int n) : Array<T>(n) {}
    
    Queue(const Queue &other) : Array<T>(other), front(other.front) {}
    Queue(Queue &&other) noexcept : Array<T>(move(other)), front(other.front) {}

    Queue &operator=(const Queue<T> &other)
    {
        if (this != &other)
            this->Array<T>::operator=(other);
        front = other.front;
        return *this;
    }

    Data<T> &operator=(const Data<T> &other) override
    {
        if (this != &other)
            this->Data<T>::operator=(other);

        return *this;
    }

    Queue &operator=(Queue<T> &&other) noexcept
    {
        if (this != &other)
        {
            this->Array<T>::operator=(move(other));
            front = other.front;
        }
        return *this;
    }
    
//PLUST OPERATORS
    Data<T> &operator+(Data<T> &other) override
    {
        return this->Array<T>::operator+(other);
    }

    Data<T> &operator+=(Data<T> &other) override
    {
        this->Array<T>::operator+=(other);
        return *this;
    }
//INDEX OPERTORS 


//INSERT AND REMOVE
    virtual Data<T> &insert(int index, T val) override
    {
        return insert(val);
    }
    virtual Data<T> &insert(Special special, T val) override
    {
        return insert(val);
    }
    virtual Data<T> &insert(T val) override
    {
        if (isFull())
            this->increase(10);

        get(this->length++) = val;

        return *this;
    }
    virtual Data<T> &remove(int index) override
    {
        return remove();
    }
    virtual Data<T> &remove(Special special) override
    {
        return remove();
    }
    virtual Data<T> &remove() override
    {
        if (!isEmpty())
        {
            front++;
            this->length--;
        }

        return *this;
    }

//POINTER
    virtual Data<T> *pointer(int n) override
    {
        Queue<T> *p = new Queue(n);
        return p;
    }


//UTIL
    bool isFull()
    {
        return this->length >= this->size;
    }

   bool isEmpty()
    {
        return this->length <= 0;
    }
};

#endif