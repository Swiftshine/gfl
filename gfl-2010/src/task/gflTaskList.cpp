#include <task/gflTask.h>
#include <task/gflTaskList.h>
#include <memory/gflMemoryUtil.h>
using namespace gfl;

void TaskList::MakeInstance() {
    TaskList::Instance = new (HeapID::LIB1) TaskList;
}

void TaskList::RemoveInstance() {
    delete TaskList::Instance;
    TaskList::Instance = nullptr;
    TaskInfo::CurrentTask = nullptr;
}