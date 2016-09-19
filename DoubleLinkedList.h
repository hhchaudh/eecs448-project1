/**
 * Purpose: To handle the creation and interaction of Nodes- specifically for a Calender
 */

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <string>
#include <vector>
#include "Node.h"

/**
 * A list to store Node objects.
 * @author Brad Gibbons
 * @version 1.0, 15 Sep 2016
 */
class DoubleLinkedList {
public:
	/**
	 * A constructor for the DoubleLinkedList object.
	 */
	DoubleLinkedList();
	/**
	 * An overload constructor for the DoubleLinkedList object to populate the list with Node objects.
	 * @param startYear 	The starting year for the linked list.
	 * @param startMonth 	The starting month for the linked list.
	 * @param endYear 		The ending year for the linked list.
	 * @param endMonth 		The ending month for the linked list.
	 */
	DoubleLinkedList(int startYear, int startMonth, int endYear, int endMonth);
	/**
	 * A deconstructor to delete the Node objects stored in the list.
	 */
	~DoubleLinkedList();
	/**
	 * Method to get the size of the list.
	 * @return The number of Node objects in the linked list.
	 */
	int size() const;
	/**
	 * Adds a Node to the front of the list with set values.
	 * @param year 	Year to be stored in the added Node object.
	 * @param month Month to be stored in the added Node object.
	 * @param day 	Day to be stored in the added Node object.
	 */
	void pushFront(int year, int month, int day);
	/**
	 * Removes the front Node in the list.
	 */
	void removeFront();
	/**
	 * Adds a Node to the back of the list with set values.
	 * @param year 	Year to be stored in the added Node object.
	 * @param month Month to be stored in the added Node object.
	 * @param day 	Day to be stored in the added Node object.
	 */
	void pushBack(int year, int month, int day);
	/**
	 * Removes the back Node in the list.
	 */
	void removeBack();
	/**
	 * Method to get the front Node in the list.
	 * @return The Node currently at the front of the list.
	 */
	Node* getFront() const;
	/**
	 * Method to return the back Node in the list.
	 * @return The Node currently at the back of the list.
	 */
	Node* getBack() const;
	/**
	 * Method to get the Node with the set date.
	 * @param year 	Year to be searched for.
	 * @param month Month to be searched for.
	 * @param day 	Day to be searched for.
	 * @return A node with the specified values.
	 */
	Node* getNode(int year, int month, int day) const;
	/**
	 * Checks if the year requested exists.
	 * @return True if the year is part of the list, false otherwise.
	 */
	bool checkYear(int year) const;
	/**
	 * Checks if the month exists in the calender for the given year.
	 * @return True if the month exists for the year, false otherwise.
	 */
	bool checkMonth(int year, int month) const;
	/**
	 * Checks if the given day exists in the list
	 * @return True if the day exists in the list, false otherwise.
	 */
	bool checkDay(int year, int month, int day) const;
private:
	Node* m_front; //Pointer to the first Node
	Node* m_back; //Pointer to the last Node
	int m_size; //Size of the DoubleLinkedList
	int numDays(int year, int month); //Gets the number of days in the month for that year
};

#endif
