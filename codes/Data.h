#ifndef Data_h
#define Data_h
#include <iostream>
#include <string>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <cstring>
using namespace std;

enum Special
{
    NONE,
    FIRST,
    MIDDLE,
    LAST,
    RECURSIVE,
    NON_RECURSIVE,
    NEXT,
    PREVIOUS,
    FIXED,
    DYNAMIC,
    PUSH,
    CURRENT
};

template <class T>
class Data
{
protected:
    int length;
//DEFAULT CONSTRUCTOR
    Data() : length(0) {}
//INTERNAL GET
    virtual T &get(int index) = 0;
    virtual T &get(int index) const=0;

public:
//INIT
    void initFromList(initializer_list<T> list)
    {
        for (const auto &element : list)
            this->insert(element);
    }
        
    

//CONSTRUCTORS AND DESTRUCTORS AND ASSIGNMENT OPERATORS
    virtual ~Data() = default;
    Data(const Data &) = default;
    Data(Data &&) = default;
    virtual Data<T> &operator=(const Data<T> &data)
    {
        this->length = 0;
        for (int i = 0; i < data.getLength(); i++)
            this->insert(data[i]);
        return (*this);
    }
    virtual Data<T> &operator=(Data<T> &&data) = default;

//PLUS OPERATORS
    virtual Data<T> &operator+(Data<T> &data)
    {
        Data<T> *result = this->pointer(this->length + data.getLength());
        *result = *this;
        for (int i = 0; i < data.getLength(); i++)
            result->insert(data[i]);
        return (*result);
    }
    virtual Data<T> &operator+=(Data<T> &data)
    {
        for (int i = 0; i < data.getLength(); i++)
            this->insert(data[i]);
        return (*this);
    }

//LOGICAL OPERATORS
    bool operator==(const Data &data) const
    {
        if (length != data.length)
            return false;
        for (int i = 0; i < length; i++)
            if ((*this)[i] != data[i])
                return false;
        return true;
    }

    bool operator!=(const Data &data) const
    {
        return !((*this) == data);
    }

    bool operator>(const Data &data) const
    {
        return (sum() > data.sum());
    }

    bool operator<(const Data &data) const
    {
        return (sum() < data.sum());
    }

    bool operator>=(const Data &data) const
    {
        return (sum() >= data.sum());
    }

    bool operator<=(const Data &data) const
    {
        return (sum() <= data.sum());
    }
//INDEX OPERATORS

    virtual T &operator[](int index) const 
    {
        index = this->toInt(index);
        if (index < 0 || index >= this->length)
            throw out_of_range("Index out of range");
        return get(index);
    }
    virtual T &operator[](Special special) const 
    {
        return (*this)[this->toInt(special)];
    }
    virtual T &operator[](int index)  
    {
        index = this->toInt(index);
        if (index < 0 || index >= this->length)
            throw out_of_range("Index out of range");
        return this->get(index);
    }
    virtual T &operator[](Special special)  
    {
        return (*this)[this->toInt(special)];
    }

//MAX MIN SUM
    T sum() const
    {
        T total{};
        for (int i = 0; i < length; i++)
        {
            total += (*this)[i];
        }
        return total;
    }

    virtual T max() const
    {
        if (length == 0)
            throw out_of_range("Array is empty");
        T result = (*this)[0];
        for (int i = 1; i < length; i++)
            if ((*this)[i] > result)
                result = (*this)[i];
        return result;
    }

    virtual T min() const
    {
        if (length == 0)
            throw out_of_range("Array is empty");
        T result = (*this)[0];
        for (int i = 1; i < length; i++)
            if ((*this)[i] < result)
                result = (*this)[i];
        return result;
    }




//POINTER
virtual Data<T> *pointer(int n) = 0;

//INSERT AND REMOVE
    virtual Data<T> &insert(int index, T val) = 0;
    virtual Data<T> &insert(Special special, T val) = 0;
    virtual Data<T> &insert(T val) = 0;
    virtual Data<T> &remove(int index) = 0;
    virtual Data<T> &remove(Special special) = 0;
    virtual Data<T> &remove() = 0;



    



//UTIL : SEARCH , is Sorted , REVERSE , TO INT , GET LENGTH , setLENGTH
    virtual int search(T &value) const
    {
        return search(forward<T>(value));
    }
    virtual int search(T &&value) const
    {
        for (int i = 0; i < length; i++)
            if ((*this)[i] == value)
                return i;
        return -1;
    }
    virtual bool isSorted()
    {
        for (int i = 0; i < length - 1; i++)
            if ((*this)[i] > (*this)[i + 1])
                return false;
        return true;
    }
    virtual Data<T> &reverse()
    {

        int i = 0, j = this->length - 1;
        while (i < j)
            swap(get(i++), get(j--));
        return (*this);
    };

    virtual int toInt(int index) const
    {
        return (index < 0) ? this->length + index : index;
    }
    virtual int toInt(Special special) const
    {
        switch (special)
        {
        case FIRST:
            return 0;
        case LAST:
            return this->length - 1;
        case MIDDLE:
            return (this->length - 1) / 2;
        case PUSH:
            return this->length;
        default:
            throw invalid_argument("Invalid Special argument");
        }
    }
    int getLength() const
    {
        return length;
    }
    
    virtual Data<T> &setLength(int n){
        T zero{};
        cout<<zero<<endl;
        int l=length;
        if(n<0)
            return(*this);
        if(n>l)
            for(int i=0;i<n-l;i++)
                this->insert(zero);
        else
            for(int i=0;i<l-n;i++)
                this->remove();
        
        return (*this);
    }
 

//F.R.I.E.N.D.S
    template <class U>
    friend ostream &operator<<(ostream &os, const Data<U> &data);

};

template <class T>
ostream &operator<<(ostream &os, const Data<T> &data)
{
    os << "[";
    for (int i = 0; i < data.length; i++)
    {
        os << data[i];
        if (i < data.length - 1)
            os << ",";
    }
    os << "]";
    return os;
}
#endif 