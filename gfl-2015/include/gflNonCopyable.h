#ifndef GFL_NONCOPYABLE_H
#define GFL_NONCOPYABLE_H

namespace gfl {
    template <typename T>
    class NonCopyable {
    protected:
        NonCopyable();
        ~NonCopyable();

        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

#endif