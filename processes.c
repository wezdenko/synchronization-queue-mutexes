#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "headers/processes.h"

#define SLEEP_TIME 100000

int num_A1_waiting = 0;
int num_A2_waiting = 0;
int num_B1_waiting = 0;
int num_B2_waiting = 0;


int proc_A1(Buffer* buff, int mutex_set)
{
    clock_t time;
    time = clock();

    while ((clock() - time) < (5 * CLOCKS_PER_SEC))
    {
        P(mutex_set, GLOBAL);

        if (buff->even >= 10)
        {
            num_A1_waiting++;
            V(mutex_set, GLOBAL);
            P(mutex_set, A1);
        }

        put(buff, 2);
        printf("Put: 2\n");

        if (num_A2_waiting > 0 && buff->even > (buff->length - buff->even))
        {
            num_A2_waiting--;
            V(mutex_set, A2);
        }
        else if (num_B1_waiting > 0 && buff->length >= 3 && buff->head->value % 2 == 0)
        {
            num_B1_waiting--;
            V(mutex_set, B1);
        }
        else if (num_B2_waiting > 0 && buff->length >= 7 && buff->head->value % 2 != 0)
        {
            num_B2_waiting--;
            V(mutex_set, B2);
        }
        else
        {
            V(mutex_set, GLOBAL);
        }
        usleep(SLEEP_TIME);
    }

    printf("End of A1 proc\n");
    return 0;
}

int proc_A2(Buffer* buff, int mutex_set)
{
    clock_t time;
    time = clock();

    while ((clock() - time) < (5 * CLOCKS_PER_SEC))
    {
        P(mutex_set, GLOBAL);

        if (buff->even <= (buff->length - buff->even))
        {
            num_A2_waiting++;
            V(mutex_set, GLOBAL);
            P(mutex_set, A2);
        }

        put(buff, 3);
        printf("Put: 3\n");

        if (num_A1_waiting > 0 && buff->even < 10)
        {
            num_A1_waiting--;
            V(mutex_set, A1);
        }
        else if (num_B1_waiting > 0 && buff->length >= 3 && buff->head->value % 2 == 0)
        {
            num_B1_waiting--;
            V(mutex_set, B1);
        }
        else if (num_B2_waiting > 0 && buff->length >= 7 && buff->head->value % 2 != 0)
        {
            num_B2_waiting--;
            V(mutex_set, B2);
        }
        else
        {
            V(mutex_set, GLOBAL);
        }
        usleep(SLEEP_TIME);
    }

    printf("End of A2 proc\n");
    return 0;
}

int proc_B1(Buffer* buff, int mutex_set)
{
    clock_t time;
    time = clock();

    while ((clock() - time) < (5 * CLOCKS_PER_SEC))
    {
        P(mutex_set, GLOBAL);

        if (buff->length < 3 || buff->head->value % 2 != 0)
        {
            num_B1_waiting++;
            V(mutex_set, GLOBAL);
            P(mutex_set, B1);
        }

        Element elm = get(buff);
        printf("Get: %d\n", elm.value);

        if (num_A1_waiting > 0 && buff->even < 10)
        {
            num_A1_waiting--;
            V(mutex_set, A1);
        }
        else if (num_A2_waiting > 0 && buff->even > (buff->length - buff->even))
        {
            num_A2_waiting--;
            V(mutex_set, A2);
        }
        else if (num_B2_waiting > 0 && buff->length >= 7 && buff->head->value % 2 != 0)
        {
            num_B2_waiting--;
            V(mutex_set, B2);
        }
        else
        {
            V(mutex_set, GLOBAL);
        }
        usleep(SLEEP_TIME);
    }

    printf("End of B1 proc\n");
    return 0;
}

int proc_B2(Buffer* buff, int mutex_set)
{
    clock_t time;
    time = clock();

    while ((clock() - time) < (5 * CLOCKS_PER_SEC))
    {
        P(mutex_set, GLOBAL);

        if (buff->length < 7 || buff->head->value % 2 == 0)
        {
            num_B2_waiting++;
            V(mutex_set, GLOBAL);
            P(mutex_set, B2);
        }

        Element elm = get(buff);
        printf("Get: %d\n", elm.value);

        if (num_A1_waiting > 0 && buff->even < 10)
        {
            num_A1_waiting--;
            V(mutex_set, A1);
        }
        else if (num_A2_waiting > 0 && buff->even > (buff->length - buff->even))
        {
            num_A2_waiting--;
            V(mutex_set, A2);
        }
        else if (num_B1_waiting > 0 && buff->length >= 3 && buff->head->value % 2 == 0)
        {
            num_B1_waiting--;
            V(mutex_set, B1);
        }
        else
        {
            V(mutex_set, GLOBAL);
        }
        usleep(SLEEP_TIME);
    }

    printf("End of B2 proc\n");
    return 0;
}