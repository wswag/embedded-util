#ifndef CHAINEDLIST_H
#define CHAINEDLIST_H

template<class T>
class ChainedList
{
    private:
        T *_head = nullptr;
    public:
        // add to tail, less efficient
        void add(T *elem);
        // add to head, more efficient
        void prepend(T *elem);
        void rem(T *elem, T *prevElem = nullptr);
        void replace(T *elem, T* newElem, T *prevElem = nullptr);
        T* head() const { return _head; }
        T* tail() const;
        T* prev(T* elem) const;
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
void ChainedList<T>::prepend(T* elem)
{
    elem->setNext(_head);
    _head = elem;
}

template<class T>
void ChainedList<T>::rem(T *elem, T *prevElem) 
{
    if (_head == nullptr) return;
    if (elem == _head) {
        _head = _head->next();
        return;
    }
    T* prevE = prevElem;
    if (prevE == nullptr || prev->next() != elem) {
        prevE = prev(elem);
    }
    if (prev)
        // remove the element
        prev->setNext(elem->next());
}

template<class T>
void ChainedList<T>::replace(T *elem, T* newElem, T *prevElem) 
{
    if (_head == nullptr) return;
    if (elem == _head) {
        newElem->setNext(_head);
        _head = newElem;
        return;
    }
    T* prevE = prevElem;
    if (prevE == nullptr || prev->next() != elem) {
        prevE = prev(elem);
    }
    if (prev) {
        // remove the element
        newElem->setNext(elem->next());
        prev->setNext(newElem);
    }
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
T* ChainedList<T>::prev(T* elem) const
{
    auto cursor = head();
    while (cursor) {
        if (cursor->next() == elem)
            return cursor;
        cursor = cursor->next();
    }
    return nullptr;
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
