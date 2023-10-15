#ifndef CAPSULE_H
#define CAPSULE_H

// object lifetime service
template<class T>
class Capsule : public ChainedUnidirectionalElement<Capsule<T>> {
    private:
        T* _obj;
    public:
        Capsule(T* obj) : _obj(obj) { _obj->incrRef(); }
        Capsule(Capsule& m) : _obj(m._obj) { _obj->incrRef(); };
        virtual ~Capsule() { _obj->decrRef(); }

        const T& getObject() const { return *_obj; }
};

class ManagedObject {
    private:
        int _refCounter = 0;
    public:
        virtual ~ManagedObject() {}
        
        int incrRef() {
            _refCounter++;
            return _refCounter;
        }

        int decrRef() {
            _refCounter--;
            if (_refCounter == 0) {
                delete this;
                return 0;
            }
            return _refCounter;
        }
};

#endif /* CAPSULE_H */
