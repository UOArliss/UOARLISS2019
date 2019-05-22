#ifndef _BQUEUE_H
#define _BQUEUE_H

typedef struct bqueue bqueue;

/*create a bounded queue of a certain size*/
const bqueue* create_bqueue(long size);

struct bqueue {
	
	/*pointer to the bounded q's data*/
	void* data;

	/*adds an item to the queue at the head, returns 1 if add is successfull
	0 otherwise*/
	int (*enqueue)(const bqueue* bq, void* element);

	/*removes item at the head, returns 1 on success 0 on failure*/
	int (*dequeue)(const bqueue* bq, void** element);

	/*grabs item at the tail, but does not destroy*/
	int (*peek)(const bqueue* bq, void** element);

	/*removes all memory associated with the bounded queue, user passes function used
	to free elements*/
	void (*destroy)(const bqueue* bq, void (*freefunc)(void* tofree));

	/*returns size of the bounded queue*/
	long (*size)(const bqueue* bq);

	/*bool indicating if the current queue is empty*/
	int (*is_empty)(const bqueue* bq);

	/*empties the queue without destroying it*/
	void (*purge)(const bqueue* bq, void (*freefunc)(void* tofree));
};



#endif