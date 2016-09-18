/**	
 *	@file ReadWrite.h
 *	@author Jackson Schilmoeller
 *	@date Created: 9/8/2016
 *	@brief Generates file, user.txt, to keep user calendar data, and retrieve information from previous sessions
 **/

	#ifndef READ_WRITE_H
	#define READ_WRITE_H

	#include <iostream>
	#include <vector>
 	#include <fstream>
 	#include "DoubleLinkedList.h"
 	#include "Node.h"

	class ReadWrite
	{
	public:
		ReadWrite();
		~ReadWrite();
		bool isFile() const;
		int* getDate();
		void setDate(int curdate[]);
		void getFileInfo(DoubleLinkedList* dll);
		void storeFileInfo(DoubleLinkedList* dll);
	private:
		int m_curdate[];
	};

	#endif