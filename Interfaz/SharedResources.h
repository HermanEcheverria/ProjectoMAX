
#ifndef SHARED_RESOURCES_H
#define SHARED_RESOURCES_H

#include <vector>
#include <pthread.h>
#include "Task.h"  // Assuming Task.h is the header file for the Task class

// Global variables
extern std::vector<Task> taskList;
extern pthread_mutex_t taskMutex;
extern pthread_cond_t taskCond;

#endif // SHARED_RESOURCES_H

