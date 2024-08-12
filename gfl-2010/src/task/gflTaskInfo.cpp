#include <task/gflTaskInfo.h>
#include <cstring> // for memset

using namespace gfl;

TaskInfo::TaskInfo()
    : mFlags(Flags::Inactive)
    , mpParent(nullptr)
    , mpNext(nullptr)
    , mpChild(nullptr)
    , mpOwner(nullptr)
{
    memset(mName, 0, 0x17);
}

TaskInfo::~TaskInfo() { }
