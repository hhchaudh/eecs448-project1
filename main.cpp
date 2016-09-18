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
	int currentDate []={};
	bool isRunning=true;
	//Create Linked list object
	DoubleLinkedList* calender = new DoubleLinkedList(2016,8,2017,5);
	//Create read/write object
	ReadWrite writer = ReadWrite();
	//Get File info
	writer.getFileInfo(calender);
	//Setting current date
	currentDate=writer.getDate();
	//Create a while loop for when the program is running.
	//While holder
	while(isRunning==true)
	{
		//Needs to follow the changing days
		//Needs to go to the right index in the double linked list user dll method.
		//Needs to write/delete in that section
		//Sets details using node method
		//Needs to check for user exit.
		//User input and program is running
		bool isRunning=false;
	}
	//Check for user exiting and save the data.
	writer.setDate(currentDate);
	writer.storeFileInfo(calender);
	//Delete linked list.
	delete calender;
}
