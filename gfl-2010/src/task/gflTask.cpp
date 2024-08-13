#include <task/gflTask.h>
#include <task/gflTaskList.h>
#include <memory/gflMemoryUtil.h>

using namespace gfl;

void Task::Init(const char* newName) {
    TaskInfo* info = TaskList::Instance->GetNextAvailableTaskInfo();
    mpTaskInfo = info;

    if (!newName) {
        mem::Memcpy(info->mName, 0x17, (void*)("NONAME"));
    } else {
        mem::Memcpy(info->mName, 0x17, (void*)(newName));
    }

    info->mpOwner   = this;
    info->mFlags    = 0xF1;
    info->mpParent  = nullptr;
    info->mpNext    = nullptr;
    info->mpChild   = nullptr;
} 


Task::~Task() { }

s32 Task::PollTask() {
    TaskInfo* myTaskInfo = mpTaskInfo;
    Task* childTask;

    // If the task is about to execute and it has the means to do so, it will
    if (!(m_10 & ~m_14) && mpFunctorFunc) {
        TaskInfo::SetCurrentTask(this);
        // mFunctorFunc->operator()();
        TaskInfo::ClearCurrentTask();


        // After executing, check the task's information to see if the task still exists
        if (!myTaskInfo->mpOwner) {
            // If it doesn't, it was destroyed and is done with its task
            return Status::Executed;
        }

        // If it does, there are child tasks that must be executed
    }

    childTask = TaskInfo::GetNextChild(mpTaskInfo);

    while (childTask) {
        TaskInfo* childTaskInfo = childTask->mpTaskInfo;
        u32 x = childTask->PollTask();

        if (!myTaskInfo->mpOwner) {
            return Status::ChildrenExecuted;
        }

        if (x - 1 > 1) {
            if (x == Status::Processing) {
                childTask = TaskInfo::GetNextNext(childTask->mpTaskInfo->mpNext);
            }
        } else {
            childTask = TaskInfo::GetNextNext(childTaskInfo->mpNext);
        }
    }

    return Status::Processing;
}

Task* Task::GetParent() {
    return TaskInfo::GetParent(mpTaskInfo);
}

Task* Task::GetNextChild() {
    return TaskInfo::GetNextChild(mpTaskInfo);
}

Task* Task::GetNextNext() {
    return TaskInfo::GetNextNext(mpTaskInfo->mpNext);
}

void Task::MakeChild(Task* newChild) {
    // incomplete
}

void Task::Replace(Task* other) {
    TaskInfo* inf;
    TaskInfo* theirTaskInfo;
    TaskInfo* myChildTaskInfo;

    inf = mpTaskInfo;
    theirTaskInfo = other->mpTaskInfo;
    myChildTaskInfo = inf->mpChild;

    if (myChildTaskInfo == theirTaskInfo) {
        theirTaskInfo->mpParent = nullptr;
        inf->mpChild = theirTaskInfo->mpNext;
        theirTaskInfo->mpNext = nullptr;
        return;
    }

    for (inf = myChildTaskInfo->mpNext; myChildTaskInfo; inf = inf->mpNext) {
        if (inf == theirTaskInfo) {
            theirTaskInfo->mpParent = nullptr;
            myChildTaskInfo->mpNext = theirTaskInfo->mpNext;
            theirTaskInfo->mpNext = nullptr;
            return;
        }

        myChildTaskInfo = inf;
    }
}

void Task::SetFlags(u8 newFlags) {
    mpTaskInfo->mFlags = newFlags;
}

u8 Task::GetFlags() {
    return mpTaskInfo->mFlags;
}

void Task::SetTaskName(const char* newName) {
    if (newName) {
        mem::Memcpy(mpTaskInfo->mName, 0x17, const_cast<char*>(newName));
    } else {
        mem::Memcpy(mpTaskInfo->mName, 0x17, (void*)("NONAME"));
    }
}

void Task::CreateSubtask(u8 groupID) {
    // incomplete
}