#ifndef GFL_MEMORYUTIL_H
#define GFL_MEMORYUTIL_H

#include <types.h>

void* operator new(size_t size, u8 heapID);

namespace gfl {
    enum HeapID : u8 {
        None = 0,
        LIB1 = 1,
        LIB2 = 2,
        String = 3,
        ETC = 4,
        Sound = 5,

        Work = 10,
        Resource = 11,
    };
}
#endif