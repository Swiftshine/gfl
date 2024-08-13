#include <task/gflTask.h>
#include <task/gflTaskList.h>
#include <memory/gflMemoryUtil.h>

using namespace gfl;

TaskInfo* TaskList::GetNextAvailableTaskInfo() {
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

void TaskList::ResetTaskByIndex(u32 index) {
    mTaskInfo[index].mpNext = nullptr;
    mTaskInfo[index].mpChild = nullptr;
    mTaskInfo[index].mpParent = nullptr;
    mTaskInfo[index].mFlags = TaskInfo::Flags::Inactive;
    mTaskInfo[index].mpOwner = nullptr;
    memset(mTaskInfo[index].mName, 0, 0x17);
    mTaskEnabled[index] = false;
}

void TaskList::fn_02BD7CCC() { 
    // incomplete
}



void TaskList::MakeInstance() {
    TaskList::Instance = new (HeapID::LIB1) TaskList;
}

void TaskList::RemoveInstance() {
    delete TaskList::Instance;
    TaskList::Instance = nullptr;
    TaskInfo::CurrentTask = nullptr;
}