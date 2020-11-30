#include "headers/queue.h"

void init_buff(Buffer* buff)
{
    int i;
    for (i = 0; i < MAXSIZE; i++)
    {
        buff->queue[i].value = 0;
        buff->queue[i].is_valid = NOT_VALID;
        buff->queue[i].next_elm = 0;
    }
    buff->head = 0;
    buff->tail = 0;
    buff->length = 0;
    buff->even = 0;
}

Element get(Buffer* buff)
{
    Element ret_elm;
    ret_elm = *buff->head;

    buff->head->is_valid = NOT_VALID;
    buff->head = buff->head->next_elm;
    buff->length--;

    if (ret_elm.value % 2 == 0)
        buff->even--;

    return ret_elm;
}

void put(Buffer* buff, int value)
{
    int free_index, i;

    for (i = 0; i < MAXSIZE; i++)
    {
        if (buff->queue[i].is_valid == NOT_VALID)
        {
            free_index = i;
            break;
        }
    }

    buff->queue[free_index].value = value;
    buff->queue[free_index].is_valid = VALID;
    buff->queue[free_index].next_elm = 0;

    if (value % 2 == 0)
        buff->even++;
    buff->length++;
}

Element check(Buffer* buff)
{
    Element elm = *buff->head;
    return elm;
}