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
	
	//While loop will go here--------------------------------------------------------
	//Check for user exiting and save the data.
//writer.setDate(currentDate);
//writer.storeFileInfo(calender);
	//Delete linked list.
	delete calender;


	
}
while(isRunning)
{	
	int command = 0;
	std::cout << "Current date is: "+currentDate[1]+","+currentDate[2]+","+currentDate[3] << std:endl;
	std::cout << "Enter Command " <<std::endl;
	std::cout << "1) Go to day" << std::endl;
	std::cout << "2) Add detatil" << std::endl;
	std::cout << "3) Remove detial" << std::endl;
	std::cout << "4) View Details" << std::endl;
	std::cout << "5) Exit" << std::endl;
	std::cin >> command;
	if(command==1)
	{	
		int year = 0;
		int month = 0;
		int day = 0;
		std::cout << "Choose a year (2015/2016)" << std::endl;
		std::cin >> year;
		std::cout << "Choose a month (Aug-May)" << std::endl;
		std::cin >> month;
		std::cout << "Choose a day (correctly)" + calender.numDays(year,month) << std::endl;
		std::cin >> day;
		calender.getNode(year,month,day)		
	}
	if(command==2)
	{	
		string detail = "";
		std::cout << "Detail to add:" << std::endl;
		std::cin >> year;
		
	}
	if(command==2)
	{	
		string detail = "";
		std::cout << "Detail to add:" << std::endl;
		std::cin >> detail;
		//Add detail	
	}
	if(command==3)
	{	
		int index = 0;
		std::cout << "Which detail?" << std::endl;
		//Shows details for the day
		std::cin >> index;
		//Remove detail
	}
	if(command==4)
	{	
		std::cout << "Details for today" << std::endl;
		//Shows details	
	}
	if(command==5)
	{
		isRunning=false;
	}
}
