/**
*	@file : main.cpp
*	@author: Brad Gibbons, Rony Singh, Jackson Schilmoeller, Chris Porras
*	@date: 2016.09.09
*	Purpose: Implementation of the program
*/
#include <string>
#include <iostream>
#include "Node.h"
#include "DoubleLinkedList.h"
#include "ReadWrite.h"
int main() 
{
	int currentDate=0;
	//Create Linked list object
	DoubleLinkedList* calender = new DoubleLinkedList();
	//Create read/write object
	ReadWrite writer = new ReadWrite();
	//Get File info
	writer.getFileInfo(calender);
	//Setting current date
	currentDate=writer.getCurrentDate();
	//Create a while loop for when the program is running.
	//While holder
	while(1)
	{
		//User input and program is running
	}
	//Check for user exiting and save the data.
	saveData();
	//Delete linked list.
	delete calender;
	//Delete read write.
	delete writer;
	
}
//Method to be called when program is exiting.
saveData()
{
	writer.setCurrentDate(currentDate);
	writer.storeFileInfo(calender);
}
