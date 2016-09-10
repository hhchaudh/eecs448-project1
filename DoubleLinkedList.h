/**
*       @file DoubleLinkedList.h
*       @author Brad Gibbons
*       @date 2016.09.09
*       Purpose: To handle the creation and interaction of Nodes- specifically for a Calender
*/

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <string>
#include <vector>
#include "Node.h"

class LinkedList {
public:
	/**
	*  @pre none
	*  @post An instantiated DoubleLinkedList object
	*  @return none
	*/
	DoubleLinkedList();
	/**
	*  @pre none
	*  @post An instantiated DoubleLinkedList object that contains the dates specified
	*  @return none
	*/
	DoubleLinkedList(int startYear, int startMonth, int endYear, int endMonth);
	/**
	*  @pre A LinkedList object
	*  @post Deletes the Nodes contained by the DoubleLinkedList
	*  @return none
	*/
	~DoubleLinkedList();
	/**
	*  @pre none
	*  @post none
	*  @return The number of Nodes in the DoubleLinkedList
	*/
	int size() const;
	/**
	*  @pre none
	*  @post Adds a Node to the front of the DoubleLinkedList
	*  @return none
	*/
	void pushFront();
	/**
	*  @pre At least one Node in the DoubleLinkedList
	*  @post Removes the front Node from the DoubleLinkedList
	*  @return none
	*/
	void removeFront();
	/**
	*  @pre none
	*  @post Adds a Node to the back of the DoubleLinkedList
	*  @return none
	*/
	void pushBack();
	/**
	*  @pre At least one Node in the DoubleLinkedList
	*  @post Deletes the last Node in the DoubleLinkedList
	*  @return none
	*/
	void removeBack();
	/**
	*  @pre At least one Node in the DoubleLinkedList
	*  @post none
	*  @return A pointer to the Node that represents the day requested
	*/
	Node* getNode(int year, int month, int day) const;
private:
	Node* m_front; //Pointer to the first Node
	Node* m_back; //Pointer to the last Node
	int m_size; //Size of the DoubleLinkedList
};

#endif