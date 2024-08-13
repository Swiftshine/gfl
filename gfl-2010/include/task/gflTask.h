#ifndef GFL_TASK_H
#define GFL_TASK_H

#include <types.h>
#include <task/gflTaskInfo.h>

namespace gfl {
    // incomplete

    class Task {
    public:
        inline Task() { }

        virtual ~Task();
        virtual void PollTask();
    public:
        TaskInfo*   mpTaskInfo;
        void*       mpFunctor;
        void*       mpFunctorFunc;
        Task*       mp_10;
        u32         m_14;
    };


}

#endif