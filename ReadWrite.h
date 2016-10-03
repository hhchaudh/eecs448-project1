/**	
 *	Purpose: Generates file, user.txt, to keep user calendar data, and retrieve information from previous sessions
 */

#ifndef READ_WRITE_H
#define READ_WRITE_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include "DoubleLinkedList.h"
#include "Node.h"

/**
 * An object to read and write info from and to a file, to and from a list respectively.
 * @author Jackson Schilmoeller
 * @version 1.0, 18 Sep 2016
 */
class ReadWrite
{
public:
	/**
	 * A constructor for the ReadWrite object.
	 */
	ReadWrite();
	/* 
	 * A destructor for the ReadWrite object.
	 */
	~ReadWrite();
	/**
	 * Checks if user.txt has already been created.
	 * @return True if the file exists, false otherwise.
	 */
	bool isFile() const;
	/**
	 * Returns the date currently stored as the date in focus.
	 * @return The date currently stored as the date in focus.
	 */
	std::vector<int> getDate();
	/**
	 * Stores the date currently in focus.
	 * @param A vector of size three representive of the date in current focus.
	 */
	void setDate(std::vector<int> curdate);
	/**
	 * Reads in the information from the file and stores it into a DoubleLinkedList.
	 * @param The DoubleLinkedList object to be filled
	 */
	void getFileInfo(DoubleLinkedList* dll);
	/**
	 * Stores The information from the DoubleLinkedList object into the file.
	 * @param The DoubleLinkedList object to be read from.
	 */
	void storeFileInfo(DoubleLinkedList* dll);
private:
	std::vector<int> m_curdate; //Current date as focus
};

#endif
