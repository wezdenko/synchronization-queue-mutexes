#include "headers/mutex.h"

int allocate_sem(key_t key, int sem_flags)
{
    return semget(key, 1, sem_flags);
}

int deallocate_sem(int semid)
{
    union semun ignored_argument;
    return semctl (semid, 5, IPC_RMID, ignored_argument);
}

int init_sem(int semid, int* init_values)
{
    union semun argument;
    unsigned short values[5];

    for (int i = 0; i < 5; i++)
    {
        values[i] = init_values[i];
    }
    
    argument.array = values;
    return semctl (semid, 0, SETALL, argument);
}

int P(int semid, int sem_num)
{
    struct sembuf operations[1];
    operations[0].sem_num = sem_num;
    operations[0].sem_op = -1;
    operations[0].sem_flg = SEM_UNDO;

    return semop(semid, operations, 1);
}

int V(int semid, int sem_num)
{
    struct sembuf operations[1];
    operations[0].sem_num = sem_num;
    operations[0].sem_op = 1;
    operations[0].sem_flg = SEM_UNDO;

    return semop(semid, operations, 1);
}