#ifndef GFL_TASKLIST_H
#define GFL_TASKLIST_H

#include <task/gflTaskInfo.h>

#define GFL_TASKLIST_MAX_TASK_COUNT 5000

namespace gfl {
    class TaskList {
    public:
        static TaskList* Instance;
    public:
        TaskInfo* GetNextAvailableTaskInfo();
        void ResetTaskByIndex(u32 index);
        void fn_02BD7CCC();

        void MakeInstance();
        void RemoveInstance();
    private:
        TaskList() { }
        ~TaskList() { }
    public:
        u32         mTaskCount;
        bool        mTaskEnabled[GFL_TASKLIST_MAX_TASK_COUNT];
        TaskInfo    mTaskInfo[GFL_TASKLIST_MAX_TASK_COUNT];
    };

    static_assert(sizeof(TaskList) == 0x320CC, "gfl::TaskList size mismatch");

}
#endif