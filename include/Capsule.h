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
        ManagedObject() {
            log_v("obj constructor for %x", (int)this);
        }
        virtual ~ManagedObject() {}

        // release shared resources within dispose() method instead of destructor
        virtual void dispose() {}
        
        int incrRef() {
            _refCounter++;
            return _refCounter;
        }

        int decrRef() {
            log_v("decr ref of obj %x from %d", (int)this, _refCounter);
            if (_refCounter > 0) {
                _refCounter--;
                if (_refCounter == 0) {
                    log_d("dispose obj %x", (int)this);
                    dispose();
                    delete this;
                    return 0;
                }
            } else {
                throw std::domain_error("ref counter already 0!");
            }
            return _refCounter;
        }
};

#endif /* CAPSULE_H */
