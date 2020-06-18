#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {

	if (q->size == MAX_QUEUE_SIZE) return;
	q->proc[q->size++]=proc;

}

struct pcb_t * dequeue(struct queue_t * q) {
	if (q->size<=0) return NULL;
	int maxPriority = 0, pos = -1;
	for (int i = 0 ; i < q->size ; i++)
		if (maxPriority < q->proc[i]->priority) {
			maxPriority = q->proc[i]->priority;
			pos = i;
		}
	if (pos == -1) 
		return NULL;
	struct pcb_t *temp = q->proc[pos];
	q->proc[pos]=q->proc[--q->size];
	return temp;
}