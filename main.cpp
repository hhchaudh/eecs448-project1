/**
*	@file : main.cpp
*	@author: Brad Gibbons, Rony Singh, Jackson Schilmoeller, Chris Porras
*	@date: 2016.09.09
*	Purpose: Implementation of the program
*/
#include <string>
#include <iostream>
#include <vector>
#include "Node.h"
#include "DoubleLinkedList.h"
#include "ReadWrite.h"
int main() 
{
	std::cout << "ping: Initialize currentDate" << std::endl;
	std::vector<int> currentDate = std::vector<int>();
	std::cout << "ping: Initialize isRunning" << std::endl;
	bool isRunning=true;
	//Create Linked list object
	std::cout << "ping: Initialize calender" << std::endl;
	DoubleLinkedList* calender = new DoubleLinkedList(2016,8,2017,5);
	//Create read/write object
	std::cout << "ping: Initialize writer" << std::endl;
	ReadWrite writer = ReadWrite();
	//Get File info
	std::cout << "ping: Call getFileInfo()" << std::endl;
	writer.getFileInfo(calender);
	//Setting current date
	std::cout << "ping: Call getDate()" << std::endl;
	currentDate=writer.getDate();
	//Create a while loop for when the program is running.
	//While holder
	std::cout << "ping: While loop" << std::endl;
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
	std::cout << "ping: Call setDate()" << std::endl;
	writer.setDate(currentDate);
	std::cout << "ping Call storeFileInfo()" << std::endl;
	writer.storeFileInfo(calender);
	//Delete linked list.
	delete calender;
}
