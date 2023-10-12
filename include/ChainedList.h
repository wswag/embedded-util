#ifndef CHAINEDLIST_H
#define CHAINEDLIST_H

template<class T>
class ChainedList
{
    private:
        T *_head = nullptr;
    public:
        void add(T *elem);
        void rem(T *elem);
        T* head() const { return _head; }
        T* tail() const;
        bool contains(T *elem) const;
        int count() const;
        void reset() { _head = nullptr; }
};

template<class T>
class ChainedUnidirectionalElement
{
    protected:
        T* _next = nullptr;
    public:
        void setNext(T* next) { _next = next; }
        T* next() const { return _next; }
};

template<class T>
void ChainedList<T>::add(T* elem)
{
    if (_head == 0)
        _head = elem;
    else
    {
        T* cursor = tail();
        cursor->setNext(elem);
    }
}

template<class T>
void ChainedList<T>::rem(T *elem) 
{
    T* cursor = head();
    T* prev = nullptr;
    while (cursor) {
        if (cursor == elem)
            break;
        prev = cursor;
        cursor = cursor->next();
    }
    if (cursor == elem)
        // remove the element
        prev->setNext(elem->next());
}

template<class T>
T* ChainedList<T>::tail() const
{
    if (_head == 0)
        return 0;
    else
    {
        T* cursor = _head;
        while (cursor->next())
            cursor = cursor->next();
        return cursor;
    }
}

template<class T>
bool ChainedList<T>::contains(T *elem) const
{
    T* cursor = _head;
    while (cursor) {
        if (cursor == elem)
            return true;   
        cursor = cursor->next();
    }
    return false;
}

template<class T>
int ChainedList<T>::count() const
{
    int n = 0;
    T* cursor = _head;
    while (cursor)
    {
        n++;
        cursor = cursor->next();
    }
    return n;
}

#endif /* CHAINEDLIST_H */
