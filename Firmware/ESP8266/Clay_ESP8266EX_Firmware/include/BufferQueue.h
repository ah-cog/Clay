/*
 * BufferQueue.h
 *
 *  Created on: Mar 9, 2016
 *      Author: thebh_000
 */

//A queue of buffer objects.
#ifndef INCLUDE_BUFFERQUEUE_H_
#define INCLUDE_BUFFERQUEUE_H_

#define BUFFER_QUEUE_DEPTH		20

typedef struct
{
	void * data;
	uint32 length;
} Buffer_Element;

typedef struct
{
	Buffer_Element queue[BUFFER_QUEUE_DEPTH];
	int front;
	int back;
	int count;
} Buffer_Queue;

extern void BufferQueue_Initialize(Buffer_Queue * queue);

extern bool BufferQueue_FlattenEnqueue(Buffer_Queue * queue, void * data,
		int length);

extern bool BufferQueue_Enqueue(Buffer_Queue* queue,
		Buffer_Element * newElement);

bool BufferQueue_Dequeue(Buffer_Queue * queue,
		Buffer_Element * dequeuedElement);

extern Buffer_Element * BufferQueue_Peek(Buffer_Queue * queue);

extern void StartBufferTestTask();

#endif /* INCLUDE_BUFFERQUEUE_H_ */
