#ifndef CHAINEDLIST_H
#define CHAINEDLIST_H

template<class T>
class ChainedList
{
    public:
        T *_head = nullptr;
        void add(T *elem);
        void rem(T *elem);
        T* head() { return _head; }
        T* tail();
        bool contains(T *elem);
        int count();
        void reset() { _head = nullptr; }
};

template<class T>
class ChainedUnidirectionalElement
{
    public:
        T* _next = nullptr;
        void setNext(T* next) { _next = next; }
        T* next() { return _next; }
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
T* ChainedList<T>::tail()
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
bool ChainedList<T>::contains(T *elem) 
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
int ChainedList<T>::count()
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
