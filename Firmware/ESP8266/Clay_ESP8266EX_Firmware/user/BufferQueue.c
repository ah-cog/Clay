/*
 * BufferQueue.c
 *
 *  Created on: Mar 9, 2016
 *      Author: thebh_000
 */

#include "esp_common.h"
#include "string.h"
#include "BufferQueue.h"

void BufferQueue_Initialize(Buffer_Queue * queue)
{
	queue->back = 0;
	queue->front = 0;
	queue->count = 0;
}

bool BufferQueue_FlattenEnqueue(Buffer_Queue * queue, void * data, int length)
{
	bool rval = false;
	Buffer_Element newElt;

	newElt.length = length;
	newElt.data = zalloc(length);

	if (newElt.data != NULL)
	{
		memcpy(newElt.data, data, length);
		rval = BufferQueue_Enqueue(queue, &newElt);
	}

	return rval;
}

bool BufferQueue_Enqueue(Buffer_Queue * queue, Buffer_Element * newElement)
{
	bool rval = FALSE;

	if (queue->count < BUFFER_QUEUE_DEPTH)
	{
		queue->queue[queue->back] = *newElement;
		queue->back = (queue->back + 1) % BUFFER_QUEUE_DEPTH;
		queue->count++;
		rval = TRUE;
	}
	return rval;
}

bool BufferQueue_Dequeue(Buffer_Queue * queue, Buffer_Element * dequeuedElement)
{
	bool rval = false;

	if (queue->count > 0)
	{
		*dequeuedElement = queue->queue[queue->front];
		queue->front = (queue->front + 1) % BUFFER_QUEUE_DEPTH;
		--(queue->count);
		rval = true;
	}

	return rval;
}

Buffer_Element * BufferQueue_Peek(Buffer_Queue * queue)
{
	Buffer_Element * rval = NULL;

	if (queue->count > 0)
	{
		rval = queue->queue + (queue->front);
	}

	return rval;
}

bool Buffer_Test(Buffer_Queue * queue, int maxMessages)
{
	char testString[] = "testdatas";

	int enqueueCount = 0;

	Buffer_Element elementInput;
	elementInput.length = strlen(testString) + 1;
	elementInput.data = testString;

	Buffer_Element elementOutput;
	elementOutput.length = 0;
	elementOutput.data = NULL;

	bool rval = true;

	BufferQueue_Initialize(queue);
	while (enqueueCount < maxMessages
			&& BufferQueue_FlattenEnqueue(queue, testString,
					elementInput.length))
	{
		++enqueueCount;
		printf("nq %d\r\n", enqueueCount);
	}

	printf("enqueue count: %d\r\n", enqueueCount);

	if (enqueueCount < maxMessages && enqueueCount != BUFFER_QUEUE_DEPTH)
	{
		rval = false;
	}

	while (rval && BufferQueue_Dequeue(queue, &elementOutput))
	{
		printf("dq %d\r\n", enqueueCount);
		--enqueueCount;

		if (elementOutput.length != elementInput.length
				|| memcmp(elementOutput.data, elementInput.data,
						elementInput.length))
		{
			rval = false;
			printf("dq nfg\r\n");
		}

		if (elementOutput.data != NULL)
		{
			free(elementOutput.data);
		}

//		printf("dequeued i:%d o:%d\r\n, i:[%s] o:[%s]",
//				elementInput.length, elementOutput.length,
//				(char*) elementInput.data, (char*) elementOutput.data);
	}

	printf("dequeue count: %d\r\n", enqueueCount);

	if (enqueueCount != 0)
	{
		rval = false;
	}

	printf("returning\r\n");

	return rval;
}

void BufferTestTask()
{
	Buffer_Queue q;

	int successCount = 0;
	int totalCount = 0;
	int i;
	for (i = 0; i < 21; ++i)
	{
		printf("--------------------iteration:%d\r\n", i);
		++totalCount;
		if (Buffer_Test(&q, i))
		{
			++successCount;
		}
	}

	printf("total: %d success:%d", totalCount, successCount);

	vTaskDelete(NULL);
}

void StartBufferTestTask()
{
	xTaskCreate(BufferTestTask, "bufferTest", 256, NULL, 2, NULL);
}
