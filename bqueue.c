#include <stdlib.h>
#include "bqueue.h"

#define MAX_SIZE 500

typedef struct qdata{
	long size; /*current max size of the queue*/
	long items; /*current size of the queue, nitems*/
	long head; /*index to remove from*/
	long tail;	/*index to from*/
	/*generic array of elements to act as the actual storage for the queue*/
	void** array;
} qdata;

/*function to remove item at tail, returns 1 on success and 0 on failures, may
be expanded to other return values for error raising*/
static int s_dequeue(const bqueue* bq, void** element){
	qdata* qd = (qdata*)bq->data;
	int status = 0;
	if( qd->items == 0 )
		return status;
	/*get element at tail*/
	*element = qd->array[qd->tail];
	qd->tail = ( qd->tail + 1 ) % qd->size;
	qd->items--;/*adjust pos of tail relative to size*/
	status = 1;
	return status;
}


/*function to add at head, currently returns 1 on success, 0 on failure, may be 
expanded to return other values to indicate different errors*/
static int s_enqueue(const bqueue* bq, void* element){
	qdata* qd = (qdata*)bq->data;
	int status = 0;
	/*check if bounded queue is at it max*/
	if( qd->size == qd->items )
		return status;
	/*insert at the head*/
	qd->array[qd->head] = element;
	qd->head = (qd->head + 1) % qd->size; /*increase head with respect to size*/
	qd->items++;
	status = 1;
	return status;
}

/*does a non destructive grab of the tail of the queue, returns 1 on success 0 toehrwise
can be expanded to return other values*/
static int s_peek(const bqueue* bq, void** element){
	qdata* qd = (qdata*)bq->data;
	int status = 0;
	if ( qd->items == 0)
		return status;
	*element = qd->array[qd->tail];
	status = 1;
	return status;
}

/*function used to free each element in the bounded queue, this is up to the caller as
as the items within the queue may need special frees*/
static void s_destroy(const bqueue* bq, void (*freefunc)(void* tofree)){
	qdata* qd = (qdata*)bq->data;
	int i=0;
	/*go from tail to head freeing each element*/
	for(; i < qd->size; i++){
		if( qd->array[i] ) /*shit style redo later*/
			freefunc(qd->array[i]);
	}
	free(qd->array);
	free(qd);
	free((void*)bq);
}

/*returns the current number of elements in the queue*/
static long s_size(const bqueue* bq){
	qdata* qd = (qdata*)bq->data;
	return qd->items;
}

/*boolean value to indicate if the selected queue is empty*/
static int s_is_empty(const bqueue* bq){
	qdata* qd = (qdata*)bq->data;
	if ( qd->items > 0)
		return 0;
	return 1;
}

static void s_purge(const bqueue* bq, void (*freefunc)(void* tofree)){
	qdata* qd = (qdata*)bq->data;
	int i=0;
	/*go from tail to head freeing each element*/
	for(; i < qd->size; i++){
		if( qd->array[i] ) /*shit style redo later*/
			freefunc(qd->array[i]);
	}
	qd->head = 0;
	qd->tail = 0;
	qd->items = 0;
}


const bqueue* create_bqueue(long size){

	bqueue* bq = (bqueue*)malloc(sizeof(bqueue));
	if ( bq != 
		NULL){
		/*check if size of bounded queue is within set bounds*/
		if(size > MAX_SIZE)
			size = MAX_SIZE;
		void** ar = (void**)malloc(size * sizeof(void*));
		if( ar != NULL){
			/*array has been malloc'd zero it out*/
			int i = 0;
			for(; i < size; i++){
				ar[i] = 0;
			}
			/*now set up the qdata*/
			qdata* qd = (qdata*)malloc(sizeof(qdata));

			if(qd != NULL){
				/*all error checks have cleared, now begin assigning thigns*/
				qd->size = size;
				qd->items = 0;
				qd->head = 0;
				qd->tail = 0;
				qd->array = ar;
				/*assign the qdata to the bounded queue*/
				bq->data = qd;
				/*now set up functions*/
				bq->enqueue = s_enqueue;
				bq->dequeue = s_dequeue;
				bq->destroy = s_destroy;
				bq->peek = s_peek;
				bq->size = s_size;
				bq->is_empty = s_is_empty;
				bq->purge = s_purge;
				return bq;
			} else {
				/*cleanup and NULL memory already allocted in event of failure*/
				free(ar);ar=NULL;
				free(bq);bq = NULL;
				return NULL;
			}
		/*failure on array memory allocation*/
		} else {
			free(bq);
			bq = NULL;
			return NULL;
		}
		/*failure on queue struct allocation*/
	} else {
		return bq;
	}



}