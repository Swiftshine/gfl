#ifndef GFL_TASKLIST_H
#define GFL_TASKLIST_H

#include <task/gflTaskInfo.h>

#define GFL_TASKLIST_MAX_TASK_COUNT 1400

namespace gfl {
    class TaskList {
    public:
        static TaskList* Instance;
    public:
        inline TaskInfo* GetNextAvailableTaskInfo() {
            // This function is inline in GFL 2010, but not in GFL 2015

            for (int i = 0; i < GFL_TASKLIST_MAX_TASK_COUNT; i++) {
                if (!mTaskEnabled[i]) {
                    TaskInfo* info = &mTaskInfo[i];
                    mTaskInfo[i].mpParent = nullptr;
                    mTaskInfo[i].mpNext = nullptr;
                    mTaskInfo[i].mpChild = nullptr;
                    mTaskInfo[i].mpOwner = nullptr;
                    mTaskInfo[i].mFlags = TaskInfo::Flags::Inactive;
                    memset(info->mName, 0, 0x17);
                    mTaskEnabled[i] = true;
                    return info;
                }
            }

            return nullptr;
        }

        void MakeInstance();
        void RemoveInstance();
    private:
        TaskList() { }
        ~TaskList() { }
    public:
        bool        mTaskEnabled[GFL_TASKLIST_MAX_TASK_COUNT];
        TaskInfo    mTaskInfo[GFL_TASKLIST_MAX_TASK_COUNT];
    };

    static_assert(sizeof(TaskList) == 0xE038, "gfl::TaskList size mismatch");

}
#endif