#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct _queue_element{
int pid;
} queue_element;

typedef struct _queue_node{

queue_element *data;
struct _queue_node *lnode;
struct _queue_node *rnode;
} queue_node;

typedef struct _queue_t{
queue_node* front;
queue_node* back;
int size;
} queue_t;


queue_t* queue_create(void);
void queue_enqueue(queue_t *queue ,queue_element data);
queue_node* queue_dequeue(queue_t* queue);
void queue_print(queue_t* queue);
void queue_free(queue_node* node);

#endif
