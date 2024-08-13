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

        static Task* CurrentTask;

    public:
        TaskInfo();
        ~TaskInfo();

        static inline void SetCurrentTask(Task* src) {
            TaskInfo::CurrentTask = src;
        }

        static inline void ClearCurrentTask() {
            TaskInfo::CurrentTask = nullptr;
        }

        static inline Task* GetNextNext(TaskInfo* taskInfo) {
            while (taskInfo) {
                Task* task = taskInfo->mpOwner;
                if (task) {
                    return task;
                }
                taskInfo = taskInfo->mpNext;
            }

            return nullptr;
        }

        static inline Task* GetParent(TaskInfo* taskInfo) {
            TaskInfo* parentInfo = taskInfo->mpParent;
            if (parentInfo) {
                return parentInfo->mpOwner;
            }

            return nullptr;
        }

        static inline Task* GetNextChild(TaskInfo* taskInfo) {
            if (taskInfo) {
                taskInfo = taskInfo->mpChild;
                Task* task;
                while (taskInfo) {
                    task = taskInfo->mpOwner;
                    if (task) {
                        return task;
                    }
                    taskInfo = taskInfo->mpNext;
                }
            }

            return nullptr;
        }


    public:
        char        mName[0x17];
        u8          mFlags;
        TaskInfo*   mpParent;
        TaskInfo*   mpNext;
        TaskInfo*   mpChild;
        Task*       mpOwner;
    };

    constexpr int taskinfosize = sizeof(TaskInfo);

    static_assert(sizeof(TaskInfo) == 0x28, "gfl::TaskInfo size mismatch");
}

#endif