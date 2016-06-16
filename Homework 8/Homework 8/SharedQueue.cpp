#ifndef __Lab14__SharedQueue__
#define __Lab14__SharedQueue__

#include <mutex>
#include <iostream>

template <typename T>
class SharedQueue {
public:
	SharedQueue();
	~SharedQueue();

	//Return true if the queue is empty
	bool IsEmpty() const;

	//Enqueue the next item at the tail of the queue.
	void Add(T value);

	//Dequeue the next queue element and store it in "item" variable.  The function returns false if the queue is empty and no item can be retrieved.
	bool Remove(T &item);
	void Print();
private:
	struct QueueItem{
		T item;
		QueueItem *next;
	};

	QueueItem* head;
	QueueItem* tail;
	std::mutex* lock;

	//Fill in the The private data members.
};

template <typename T>

SharedQueue<T>::SharedQueue()
{
	head = NULL;
	lock = new std::mutex;
}

template <typename T>
SharedQueue<T>::~SharedQueue()
{
	QueueItem* temp = head;
	while (head != NULL)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
	delete lock;
}

template <typename T>
bool SharedQueue<T>::IsEmpty() const
{
	if (head == NULL)
	{
		return true;

	}
	return false;
}

template <typename T>
void SharedQueue<T>::Add(T value)
{
	//add to tail
	//leave from head
	//check if empty
	QueueItem* otherItem = new QueueItem();
	lock->lock();
	otherItem->item = value;
	otherItem->next = NULL;
	if (head != NULL)
	{
		tail->next = otherItem;
		tail = otherItem;
	}
	else
	{
		head = otherItem;
		tail = otherItem;
	}
	lock->unlock();


}

template <typename T>
//passing by reference so can modify it
bool SharedQueue<T>::Remove(T &item)
{
	lock->lock();
	if (head == NULL)
	{
		lock->unlock();
		return false;
	}
	if (head == tail)
	{
		tail = NULL;
	}
	QueueItem* temp = head->next;
	item = head->item;
	delete head;
	head = temp;
	lock->unlock();
	return true;

}

template <typename T>
void SharedQueue<T>::Print()
{
	lock->lock();
	QueueItem* temp = head;
	while (temp != NULL)
	{
		std::cout << temp->item;
		temp = temp->next;
	}
	lock->unlock();
}

//Fill in the function definitions

#endif
