#ifndef GFL_SINGLETON_H
#define GFL_SINGLETON_H

namespace gfl {
    template <typename T>
    class Singleton {
    protected:
        Singleton();
        ~Singleton();
    public:
        static T& Instance() {
            static T instance;
            return instance;
        }
    };
}

#endif // GFL_SINGLETON_H
