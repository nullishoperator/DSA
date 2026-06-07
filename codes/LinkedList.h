#ifndef LinkList_h
#define LinkList_h
using namespace std;
template <typename T>
class LinkedList : public Data<T>
{
protected:
//INTERNAL GET
    virtual T &get(int index) override
    {

        int n = index - current.index;
        for (int i = 0; i < abs(n); i++)
        {
            if (n > 0)
                current++;
            else
                current--;
        }

        return current.p->data;
    }

    T &get(int index) const
    {

        int n = index - current.index;

        for (int i = 0; i < abs(n); i++)
        {
            if (n > 0)
                (current)++;
            else
                (current)--;
        }

        return current.p->data;
    }
//INNER CLASS NODE
    class Node
    {
    public:
        T data{};
        Node *next;
        Node *prev;
        Node(T data, Node *prev = nullptr, Node *next = nullptr)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };
//INNER CLASS CURRENTNODE
    class currentNode
    {
    public:
        int index;
        Node *p{};
        currentNode() : index(-1), p(nullptr) {}
        currentNode operator++(int)
        {
            currentNode temp = *this;
            if (p && p->next)
            {
                p = p->next;
                index++;
            }
            return temp;
        }
        currentNode operator--(int)
        {
            currentNode temp = *this;

            if (p && p->prev)
            {
                p = p->prev;
                index--;
            }
            return temp;
        }
    };
    
//INTERNAL UTIL
    void cut(currentNode lastOfUs)
    {
        if (lastOfUs.p->next)
        {
            LinkedList<T> result;
            result.head = lastOfUs.p->next;
            this->length = lastOfUs.index;
            lastOfUs.p->next = nullptr;
        }
    }

    Node *head = nullptr;
    Node *tail = nullptr;
    mutable currentNode current; 

public:

//CONSTRUCTOR AND DESTRUCTOR AND ASSIGNMENT OPERATORS
    LinkedList() : Data<T>()
    {
        T val{};
        current.p = head = tail = new Node(val);
    }
    LinkedList(initializer_list<T> list) : LinkedList<T>()
    {

        this->initFromList(list);
    }
    ~LinkedList()
    {
        current.p = head;
        current.index = 0;
        while (head)
        {
            head = head->next;
            delete current.p;
            current.p = head;
        }
    }
    LinkedList(const LinkedList &other) : Data<T>(other)
    {
        for (int i = 0; i < other.length; i++)
            this->insert(other.get(i));
        current.p = head;
        current.index = 0;
    }
    LinkedList(LinkedList &&other) noexcept : Data<T>(std::move(other)), head(other.head), tail(other.tail)
    {
        current.p = other.current.p;
        current.index = other.current.index;
        this->length = other.length;
        other.head = nullptr;
        other.tail = nullptr;
        other.current.p = nullptr;
        other.current.index = 0;
        other.length = 0;
    }
    virtual Data<T> &operator=(const Data<T> &other) override
    {
        if (this != &other)
            this->Data<T>::operator=(other);
        return *this;
    }

    LinkedList &operator=(const LinkedList &other)
    {
        if (this == &other)
            return *this;
        int i = 0;

        for (; i < min(this->length, other.length); i++)
            this->get(i) = other.get(i);

        if (this->length > other.length)
            cut(current);
        else
            for (; i < other.length; i++)
                this->insert(other.get(i));
        return *this;
    }

    LinkedList &operator=(LinkedList<T> &&other) noexcept
    {
        if (this == &other)
            return *this;

        this->Data<T>::operator=(std::move(other));
        this->head = other.head;
        this->tail = other.tail;
        this->current.p = other.current.p;
        this->current.index = other.current.index;
        other.head = nullptr;
        other.tail = nullptr;
        other.current.p = nullptr;
        other.current.index = 0;
        return *this;
    }



//PLUST OPERATOR
    Data<T> &operator+(Data<T> &data) override
    {
        return this->Data<T>::operator+(data);
    }
    Data<T> &operator+=(Data<T> &data) override
    {
        this->Data<T>::operator+=(data);
        return *this;
    }
//INDEX OPERATOR


//INSERT AND REMOVE
    virtual Data<T> &insert(int index, T val) override
    {

        index = this->toInt(index);
        if (index < 0 || index > this->length)
            throw out_of_range("Index out of range");

        get(index);

        if (index == this->length)
            current.p = tail = tail->next = new Node(val, tail, nullptr);
        else
            current.p->prev = current.p->prev->next = new Node(val, current.p->prev, current.p);
        current.index++;

        this->length++;
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
        get(index);

        if (index == this->length - 1)
        {
            tail->prev->next = nullptr;
            current.p = tail = tail->prev;
            current.index--;
        }
        else
        {
            current.p->prev->next = current.p->next;
            current.p = current.p->next->prev = current.p->prev;
            current.index--;
        }

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
//POINTER 
    virtual Data<T> *pointer(int n)
    {
        LinkedList<T> *p = new LinkedList<T>();
        return p;
    }


};
#endif 