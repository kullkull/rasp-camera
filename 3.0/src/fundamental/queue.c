#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"

queue_t* queue_create(void)
{

queue_t* new_queue = (queue_t*)malloc(sizeof(queue_t));
new_queue ->front 	= NULL;
new_queue ->back	= NULL;	
new_queue -> size	= 0;

	return new_queue;

}

void queue_enqueue(queue_t *queue ,queue_element data){
	queue_element* new_element = (queue_element*)malloc(sizeof(queue_element));
//allocate memory to new element
	memcpy((void*)new_element,(void*)&data,sizeof(data));

//allocate memory to new node
	queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));
	new_node -> data = new_element;

//case when queue is empty;
	if(queue -> size == 0){
		queue -> front = queue -> back = new_node;
		new_node -> lnode =NULL;
		new_node -> rnode =NULL;
		queue -> size ++;
	}
//where there are at least one node;
	else
	{		
		new_node -> lnode = queue ->back;
		new_node -> rnode = NULL;
		queue -> back -> rnode = new_node;
		queue -> back = new_node ;
		queue -> size ++;
	}
}

void queue_print(queue_t* queue)
{
printf("Queue List : ");
	queue_node *cur_node = queue -> front;
	
	for(int i = 0 ;  i < queue -> size; i++){		
	printf("%d  ", cur_node -> data -> pid);
	cur_node = cur_node -> rnode;
	}
printf("\n");
}


queue_node* queue_dequeue(queue_t* queue){

	if(queue -> size == 0)
		return NULL;
	else if( queue -> size ==1 )
	{
	queue_node *tmp = queue -> front;
	queue -> front = queue -> back =NULL;
	queue -> size --;
	return tmp;
	}
	else
	{
	queue_node *tmp = queue -> front;
	tmp-> rnode -> lnode = NULL;	
	queue -> front = tmp -> rnode;	
	queue -> size --;
	return tmp;
	}
}


void queue_free(queue_node* node){
if(node != NULL)
	{
	free(node -> data);
	free(node);
}
}

