#ifndef GFL_FIXEDMEMORYSTREAM_H
#define GFL_FIXEDMEMORYSTREAM_H

#include <memory/gflStream.h>
#include <types.h>
#include <cstring> // for memcpy

namespace gfl {
    class FixedMemoryStream : Stream {
    private:
        inline bool RangeValid() {
            return mStreamPos < mSize;
        }
    public:
        enum SeekType : int {
            Begin   = 0,
            Current = 1,
            End     = 2,
        };

    public:
        FixedMemoryStream(char* addr, u32 newSize);

        // Returns the number of bytes read.
        virtual u32 Read(char* dst, u32 count);
        // Returns the number of bytes written.
        virtual u32 Write(char* src, u32 count);
        // Returns if the file seeking operation was sucessful.
        virtual bool Seek(u32 pos, int seekType);
        virtual u32 GetStreamPos();
        virtual void Reset();
        virtual ~FixedMemoryStream();
    private:
        char* mpData;
        u32 mSize;
        u32 mStreamPos;
    };

    static_assert(sizeof(FixedMemoryStream) == 0x10, "gfl::FixedMemoryStream size mismatch");
}
#endif