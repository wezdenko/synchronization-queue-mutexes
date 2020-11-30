#ifndef MUTEX_H
#define MUTEX_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PAGE_SIZE   0x1000


union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *__buf;
};

int allocate_sem(key_t key, int sem_flags);

int deallocate_sem(int semid);

int init_sem(int semid, int* init_values);

int P(int sem_num, int semid);

int V(int sem_num, int semid);


#endif