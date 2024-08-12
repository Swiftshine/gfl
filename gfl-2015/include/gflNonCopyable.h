#ifndef GFL_NONCOPYABLE_H
#define GFL_NONCOPYABLE_H

namespace gfl {
    template <typename T>
    class NonCopyable {
    protected:
        NonCopyable();
        ~NonCopyable();
    private:
        NonCopyable(const NonCopyable&);
        NonCopyable& operator=(const NonCopyable&);
    };
}

#endif