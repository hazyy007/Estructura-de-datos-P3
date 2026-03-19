#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "types.h"


struct _Queue
{
    void *data[MAX_QUEUE];
    void **front;
    void **rear;
};




