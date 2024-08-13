#ifndef GFL_TASKINFO_H
#define GFL_TASKINFO_H

#include <types.h>
#include <cstring> // for memcpy, memset

namespace gfl {  
    class Task;

    class TaskInfo {
    public:
        enum Flags : u8 {
            Inactive = 0,
            Active   = 1,
        };

        static TaskInfo* CurrentTask;
    public:
        TaskInfo();
        ~TaskInfo();
    public:
        char        mName[0x17];
        Flags       mFlags;
        TaskInfo*   mpParent;
        TaskInfo*   mpNext;
        TaskInfo*   mpChild;
        Task*       mpOwner;
    };

    constexpr int taskinfosize = sizeof(TaskInfo);

    static_assert(sizeof(TaskInfo) == 0x28, "gfl::TaskInfo size mismatch");
}

#endif