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
	//writer.setDate(currentDate);
	//writer.storeFileInfo(calender);
	//Delete linked list.
	delete calender;


	
}
while(isRunning)
{	
	int command = 0;
	std::cout<<"Enter Command"<<std::endl;
	std::cout << "1) Year View" << std::endl;
	std::cout << "2) Month View" << std::endl;
	std::cout << "3) Week View" << std::endl;
	std::cout << "4) Day View" << std::endl;
	std::cout << "5) " << std::endl;
	std::cout << "6) " << std::endl;
	std::cout << "7) " << std::endl;
	std::cout << "8) " << std::endl;
	if(command==1)
	{

	}
	if(command==10)
	{
		isRunning=false;
	}
}
