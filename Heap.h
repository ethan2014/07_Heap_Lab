#include "Queue.h"
#include <utility>

//This should be the initial arrSize
#define START_SIZE 10

/*
 * This is a priority queue, which means that as items are removed in order
 * of decreasing priority.
 *
 * 
 */
template<class Pri, class T>
class Heap : public Queue<std::pair<Pri, T> > {
public:
	Heap();
	~Heap();

	//Add a new item
	virtual void add(std::pair<Pri, T> toAdd);

	//Remove the item with lowest priority, and return it
	//If the queue is empty, throw a string exception
	virtual std::pair<Pri, T> remove();

	//Return the number of items currently in the queue
	virtual unsigned long getNumItems();

private:
	int arrSize;
	int numItems;
	std::pair<Pri, T>* backingArray;

	//Grow the backingArray by making a new array of twice the size,
	// and copying over the data
	void grow();

	//Check the item at index, and make sure it is in the right place.
	// If not, swap it up the "tree" of the heap until you find the right
	// place
	void bubbleUp(unsigned long index);

	//Check the item at index, and make sure it is in the right place.
	// If not, swap it down the "tree" of the heap until you find the right
	// place
	void trickleDown(unsigned long index);

	unsigned long int left_child(unsigned long int index);
	unsigned long int right_child(unsigned long int index);
	unsigned long int parent(unsigned long int index);
};

#include <string>
#include <iostream>

template<class Pri, class T>
Heap<Pri, T>::Heap()
{
	numItems = 0;
	arrSize = 32;
	backingArray = new std::pair<Pri, T>[arrSize];
}

template<class Pri, class T>
Heap<Pri, T>::~Heap()
{
	delete[] backingArray;
}

template<class Pri, class T>
void Heap<Pri, T>::grow()
{
	int new_size = arrSize * 2;

	std::pair<Pri, T> *temp = new std::pair<Pri, T>[new_size];

	for (int i = 0; i < arrSize; i++) {
		temp[i] = backingArray[i];
	}

	delete[] backingArray;
	backingArray = temp;
	arrSize = new_size;
}

template<class Pri, class T>
void Heap<Pri, T>::add(std::pair<Pri, T> toAdd)
{
	// test if we need to grow before adding a new item
	if (numItems + 1 > arrSize) {
		grow();
	}

	// new elements are always put in the left most available space first
	// before they are bubbled up
	backingArray[numItems] = toAdd;

	// now we call bubbleUp on the node we just added
	bubbleUp(numItems);

	numItems++;
}

template<class Pri, class T>
void Heap<Pri, T>::bubbleUp(unsigned long index)
{
	unsigned long int p = parent(index);

	// continue to swap the node located at index with its parent while its parent is
	// greater than the node
	while (index > 0 && backingArray[p].first > backingArray[index].first) {
		swap(backingArray[p], backingArray[index]);
		index = p;
		p = parent(index);
	}
}

template<class Pri, class T>
void Heap<Pri, T>::trickleDown(unsigned long index)
{
	bool swapped;
	unsigned long int left;
	unsigned long int right;

	do {
		swapped = false;

		right = right_child(index);
		left = left_child(index);

		if (right < numItems && backingArray[right].first < backingArray[index].first) {
			// right child is a possible candidate for swapping

			if (backingArray[left].first < backingArray[right].first) {
				swap(backingArray[index], backingArray[left]);
				index = left;
				swapped = true;
			} else {
				swap(backingArray[index], backingArray[right]);
				index = right;
				swapped = true;
			}
		} else {
			if (left < numItems && backingArray[left].first < backingArray[index].first) {
				swap(backingArray[index], backingArray[left]);
				index = left;
				swapped = true;
			}
		}
	} while (swapped);
}

template<class Pri, class T>
std::pair<Pri, T> Heap<Pri, T>::remove()
{
	// get the element at the top of the tree
	std::pair<Pri, T> ret = backingArray[0];

	numItems--;

	// set the new root element to be the last element in the tree.  this
	// is only temporary, this value will be moved down the tree
	backingArray[0] = backingArray[numItems];

	// move the new root node down to its rightful place
	trickleDown(0);

	return ret;
}

template<class Pri, class T>
unsigned long Heap<Pri, T>::getNumItems()
{
	return numItems;
}

template<class Pri, class T>
unsigned long int Heap<Pri, T>::left_child(unsigned long int index)
{
	return 2 * index + 1;
}

template<class Pri, class T>
unsigned long int Heap<Pri, T>::right_child(unsigned long int index)
{
	return 2 * index + 2;
}

template<class Pri, class T>
unsigned long int Heap<Pri, T>::parent(unsigned long int index)
{
	return (index - 1) / 2;
}

