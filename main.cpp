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
	//Setup on startup
	bool isRunning=true;
	std::vector<int> currentDate = std::vector<int>();
	DoubleLinkedList* calender = new DoubleLinkedList(2016,8,2017,5);
	ReadWrite writer = ReadWrite();
	//
	writer.getFileInfo(calender);
	currentDate=writer.getDate();
	//Program interacting with user now
	std::cout << "Current date is: "+currentDate[1]+","+currentDate[2]+","+currentDate[3] << std:endl;
	std::cout << "Choose a year (2015/2016)" << std::endl;
	std::cout << "Choose a month (Aug-May)" << std::endl;
	std::cout << "Choose a day (correctly)" << std::endl;
	//Check for user exiting and save the data.
	writer.setDate(currentDate);
	writer.storeFileInfo(calender);
	//Delete linked list.
	delete calender;


	
}
