#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

#include "headers/queue.h"
#include "headers/mutex.h"
#include "headers/processes.h"


int fork_process(int proc_num, Buffer* buff, int mutex_id);

int main(int argc, char const *argv[])
{
    int segment_id, mutex_set;
    int flags = (IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    Buffer* buff;

    // allocate shared memory segment
    segment_id = shmget(IPC_PRIVATE, PAGE_SIZE, flags);

    // attach memory segment and init buffer
    buff = (Buffer*) shmat(segment_id, 0, 0);
    init_buff(buff);

    // alocate semathores
    mutex_set = allocate_sem(IPC_PRIVATE, flags);

    // init semathores
    int init_values[] = {1, 0, 0, 0, 0};
    init_sem(mutex_set, init_values);

    // forking processes
    fork_process(A1, buff, mutex_set);
    fork_process(A2, buff, mutex_set);
    fork_process(B1, buff, mutex_set);
    fork_process(B2, buff, mutex_set);

    // waiting for child processes
    int stat_lock = 0;
    while (wait(&stat_lock) > 0);

    printf("End of main proc\n");

    // deallocating semathores
    deallocate_sem(mutex_set);

    // detach shared memory segment
    shmdt(buff);

    // deallocating shared memory segment
    shmctl(segment_id, IPC_RMID, 0);
    
    return 0;
}

int fork_process(int proc_num, Buffer* buff, int mutex_set)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == 0)
    {
        // child process executes new program
        if (proc_num == A1)
            proc_A1(buff, mutex_set);
        else if (proc_num == A2)
            proc_A2(buff, mutex_set);
        else if (proc_num == B1)
            proc_B1(buff, mutex_set);
        else if (proc_num == B2)
            proc_B2(buff, mutex_set);
        exit(0);
    }
    // parent process returns
    return child_pid;
}
