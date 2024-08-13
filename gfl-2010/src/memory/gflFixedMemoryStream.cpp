#include <memory/gflFixedMemoryStream.h>

using namespace gfl;

FixedMemoryStream::FixedMemoryStream(char* addr, u32 newSize) {
    mpData = addr;
    mSize = newSize;
    mStreamPos = 0;
}

FixedMemoryStream::~FixedMemoryStream() { }

u32 FixedMemoryStream::Read(char* dst, u32 count) {
    u32 remain;
    u8* offs;
    
    if (this->mStreamPos == this->mSize) {
        return 0;
    }
        
    offs = (u8*)this->mpData + this->mStreamPos;
    remain = this->mSize - this->mStreamPos;
    count = (remain < count) ? remain : count;

    memcpy(dst, offs, count);
    this->mStreamPos += count;
    return count;
}


u32 FixedMemoryStream::Write(char* src, u32 count) {
    u32 remain;
    u8* offs;
    
    if (this->mStreamPos >= this->mSize) {
        return 0;
    }
        
    offs = (u8*)this->mpData + this->mStreamPos;
    remain = this->mSize - this->mStreamPos;
    count = (remain < count) ? remain : count;

    memcpy(offs, src, count);
    this->mStreamPos += count;
    return count;
}

bool FixedMemoryStream::Seek(u32 pos, int seekType) {
    s32 finalPos = 0;

    switch (seekType) {
        case SeekType::Begin: {
            finalPos = pos;
            break;
        }

        case SeekType::Current: {
            finalPos = pos + this->mStreamPos;
            break;
        }

        case SeekType::End: {
            finalPos = (pos + this->mSize) - 1;
            break;
        }
    }

    if (finalPos < 0) {
        return false;
    }

    this->mStreamPos = finalPos;
    return true;
}

u32 FixedMemoryStream::GetStreamPos() {
    return mStreamPos;
}

void FixedMemoryStream::Reset() {
    mpData = nullptr;
    mSize = 0;
    mStreamPos = 0;
}