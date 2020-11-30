#ifndef PROCESSES_H
#define PROCESSES_H

#include "mutex.h"
#include "queue.h"

#define GLOBAL  0
#define A1  1
#define A2  2
#define B1  3
#define B2  4


int proc_A1(Buffer* buff, int mutex_set);

int proc_A2(Buffer* buff, int mutex_set);

int proc_B1(Buffer* buff, int mutex_set);

int proc_B2(Buffer* buff, int mutex_set);


#endif