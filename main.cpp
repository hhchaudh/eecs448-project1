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
	int command = 0;
	//While loop will go here--------------------------------------------------------
	while(isRunning)
	{	
		command = 0;
		int y=currentDate[0];
		int m=currentDate[1];
		int d=currentDate[2];
		std::cout << "Current date is: " << y << "," << m << "," << d << std::endl;
		std::cout << "Enter Command " <<std::endl;
		std::cout << "1) Go to day" << std::endl;
		std::cout << "2) Add detail" << std::endl;
		std::cout << "3) Remove detail" << std::endl;
		std::cout << "4) View Details" << std::endl;
		std::cout << "5) Exit" << std::endl;
		std::cin >> command;
		if(command==1)
		{	
			int year = 0;
			int month = 0;
			int day = 0;
			std::cout << "Choose a year (2016/2017)" << std::endl;
			std::cin >> year;
			std::cout << "Choose a month (Aug-May)" << std::endl;
			std::cout << "8)August" << std::endl;
			std::cout << "9)September" << std::endl;
			std::cout << "10)October" << std::endl;
			std::cout << "11)November" << std::endl;
			std::cout << "12)December" << std::endl;
			std::cout << "1)January" << std::endl;
			std::cout << "2)February" << std::endl;
			std::cout << "3)March" << std::endl;
			std::cout << "4)April" << std::endl;
			std::cout << "5)May" << std::endl;
			std::cin >> month;
			std::cout << "Choose a day (correctly)" << std::endl;
			std::cin >> day;
			if(year==2016||year==2017
			{
			currentDate[0]=year;
			}
			if(month!=6 && month!=7)
			{
				currentDate[1]=month;
			}
			currentDate[2]=day;	
		}
		else if(command==2)
		{	
			std::string detail = "";
			std::cout << "Detail to add:" << std::endl;
			std::cin >> detail;
			Node* temp = calender->getNode(currentDate[0],currentDate[1],currentDate[2]);
			temp->addDetail(detail);	
		}
		else if(command==3)
		{	
			int index = 0;
			Node* temp = calender->getNode(currentDate[0],currentDate[1],currentDate[2]);
			std::vector<std::string> details = temp->getDetails();
			std::cout << "Which detail?" << std::endl;
			for(int i=0; i<details.size();i++)
			{
				std::cout << i+") "+ details[i] << std::endl;
			} 
			//Shows details for the day
			std::cin >> index;
			//Remove detail
			temp->removeDetail(index);
		}
		else if(command==4)
		{	
			std::cout << "Details for today" << std::endl;
			Node* temp = calender->getNode(currentDate[0],currentDate[1],currentDate[2]);
			std::vector<std::string> details = temp->getDetails();
			for(int i=0; i<details.size();i++)
			{
				std::cout << i+") "+ details[i] << std::endl;
			} 
		}
		else if(command==5)
		{
			isRunning=false;
		}
		else
		{
			std::cout << "Wrong Input" << std::endl;
		}
	}
	//Check for user exiting and save the data.
	writer.setDate(currentDate);
	writer.storeFileInfo(calender);
	//Delete linked list.
	delete calender;
	//Ok	
}

