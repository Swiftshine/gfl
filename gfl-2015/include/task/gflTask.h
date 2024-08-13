#ifndef GFL_TASK_H
#define GFL_TASK_H

#include <types.h>
#include <task/gflTaskInfo.h>

namespace gfl {
    // incomplete

    class Task {
    public:
        enum Status : u32 {
            Processing = 0,
            Executed = 1,
            ChildrenExecuted = 2,
        };

    public:
        inline Task() { }
        
        void Init(const char* newName);

        virtual ~Task();
        virtual s32 PollTask();

        Task* GetParent();
        Task* GetNextChild();
        Task* GetNextNext();
        void  MakeChild(Task* newChild);
        void  Replace(Task* other);
        void  SetFlags(u8 newFlags);
        u8    GetFlags();
        void  SetTaskName(const char* newName);
        void  CreateSubtask(u8 groupID);
    public:
        TaskInfo*   mpTaskInfo;
        void*       mpFunctor;
        void*       mpFunctorFunc;
        u32         m_10;
        u32         m_14;
        u32         m_18;
    };


}

#endif