#ifndef ENABLE_SHARED_FROM_THIS
#define ENABLE_SHARED_FROM_THIS

#include <memory>

template<class T>
class Enable_shared_from_this 
{
    private:
        std::weak_ptr<T> weak_this;
    public:
        std::shared_ptr<T> shared_from_this()
        {
            std::shared_ptr<T> p(weak_this);
            return p;
        }
};

#endif
