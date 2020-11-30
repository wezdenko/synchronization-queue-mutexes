#ifndef QUEUE_H
#define QUEUE_H

#define VALID       1
#define NOT_VALID   -1

#define MAXSIZE     20


typedef struct Element Element;
struct Element
{
    int value;
    int is_valid;
    Element* next_elm;
};


typedef struct Buffer Buffer;
struct Buffer
{
    Element queue[MAXSIZE];
    Element* head;
    Element* tail;
    int length;
    int even;
};


void init_buff(Buffer* buff);

Element get(Buffer* buff);

void put(Buffer* buff, int value);

Element check(Buffer* buff);


#endif