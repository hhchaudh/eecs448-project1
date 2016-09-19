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

int dayofweek(int y, int m, int d) {
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

void printYear(int year) {
	if (year == 2016) {
		std::cout << "AUGUST 2016 | SEPTEMBER 2016 | OCTOBER 2016 | NOVEMBER 2016 | DECEMBER 2016" << std::endl;
	}
	else if (year == 2017) {
		std::cout << "JANUARY 2017 | FEBRUARY 2017 | MARCH 2017 | APRIL 2017 | MAY 2017" << std::endl;
	}

	return;
}

void printMonth(int year, int month) {
	int monthStartDay = 0;
	int weekStartDay = 0;
	bool monthStart = false;
	if (month == 1) {
		monthStartDay = 0;
	}
	else if (month == 5 || month == 8) {
		monthStartDay = 1;
	}
	else if (month == 11) {
		monthStartDay = 2;
	}
	else if (month == 2 || month == 3) {
		monthStartDay = 3;
	}
	else if (month == 9 || month == 12) {
		monthStartDay = 4;
	}
	else if (month == 4 || month == 10) {
		monthStartDay = 6;
	}

	std::cout << "SUN|MON|TUE|WED|THU|FRI|SAT" << std::endl;

	if (month == 1 || month == 3 || month == 5 || month == 8 || month == 10 || month == 12) {

		for (int i = 1; i < 32; i++) {
			if (!monthStart) {
				for (int k = 0; k < monthStartDay; k++) {
					std::cout << "    ";
				}
				weekStartDay = monthStartDay;
				monthStart = true;
			}
			std::cout << i;

			if (i < 10) {
				std::cout << "   ";
			}
			else {
				std::cout << "  ";
			}
			weekStartDay++;
			if (weekStartDay == 7) {
				std::cout<<std::endl;
				weekStartDay = 0;
			}
		}
	}
	else if (month == 4 || month == 9 || month == 11) {
		for (int i = 1; i < 31; i++) {
			if (!monthStart) {
				for (int k = 0; k < monthStartDay; k++) {
					std::cout << "    ";
				}
				weekStartDay = monthStartDay;
				monthStart = true;
			}
			std::cout << i;

			if (i < 10) {
				std::cout << "   ";
			}
			else {
				std::cout << "  ";
			}
			weekStartDay++;
			if (weekStartDay == 7) {
				std::cout << std::endl;
				weekStartDay = 0;
			}
		}
	}
	else if (month == 2) {
		for (int i = 1; i < 28; i++) {
			if (!monthStart) {
				for (int k = 0; k < monthStartDay; k++) {
					std::cout << "    ";
				}
				weekStartDay = monthStartDay;
				monthStart = true;
			}
			std::cout << i;

			if (i < 10) {
				std::cout << "   ";
			}
			else {
				std::cout << "  ";
			}
			weekStartDay++;
			if (weekStartDay == 7) {
				std::cout << std::endl;
				weekStartDay = 0;
			}
		}
	}
	std::cout << std::endl;
}

int findNumDaysMonth(int month) {
	int numOfDaysInMonth = 0;
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		numOfDaysInMonth = 31;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		numOfDaysInMonth = 30;
	}
	else if (month == 2) {
		numOfDaysInMonth = 28;
	}
	return(numOfDaysInMonth);
}

void printWeek(int year, int month, int day) {
	int weekDay = dayofweek(year, month, day);

	int date = day;
	int daysDrawn = 0;

	int currentMonthDays = findNumDaysMonth(month);

	std::cout << "SUN|MON|TUE|WED|THU|FRI|SAT" << std::endl;
	if (weekDay == 0) {
		for (int i = 0; i < 7; i++) {
			if (date > currentMonthDays) {
				date = 1;
			}
			if (date < 10) {
				std::cout << date << "   ";
			}
			else {
				std::cout << date << "  ";
			}
			date++;

		}
	}
	else if (weekDay == 1) {
		if (day - 1 < 1) {
			date = findNumDaysMonth(month - 1) - (1 - (day - 1));
			currentMonthDays = findNumDaysMonth(month - 1);
		}
		else {
			date = day - 1;
		}
		for (int i = 0; i < 7; i++) {
			if (date > currentMonthDays) {
				date = 1;
			}
			if (date < 10) {
				std::cout << date << "   ";
			}
			else {
				std::cout << date << "  ";
			}
			date++;

		}
	}
	else if (weekDay == 2) {
		if (day - 2 < 1) {
			date = findNumDaysMonth(month - 1) - (1 - (day - 2));
			currentMonthDays = findNumDaysMonth(month - 1);
		}
		else {
			date = day - 2;
		}

		for (int i = 0; i < 7; i++) {
			if (date > currentMonthDays) {
				date = 1;
			}
			if (date < 10) {
				std::cout << date << "   ";
			}
			else {
				std::cout << date << "  ";
			}
			date++;

		}
	}
	else if (weekDay == 3) {
		if (day - 3 < 1) {
			date = findNumDaysMonth(month - 1) - (1 - (day - 3));
			currentMonthDays = findNumDaysMonth(month - 1);
		}
		else {
			date = day - 3;
		}
		for (int i = 0; i < 7; i++) {
			if (date > currentMonthDays) {
				date = 1;
			}
			if (date < 10) {
				std::cout << date << "   ";
			}
			else {
				std::cout << date << "  ";
			}
			date++;

		}
	}
	else if (weekDay == 4) {
		if (day - 4 < 1) {
			date = findNumDaysMonth(month - 1) - (1 - (day - 4));
			currentMonthDays = findNumDaysMonth(month - 1);
		}

		else {
			date = day - 4;
		}
		for (int i = 0; i < 7; i++) {
			if (date > currentMonthDays) {
				date = 1;
			}
			if (date < 10) {
				std::cout << date << "   ";
			}
			else {
				std::cout << date << "  ";
			}
			date++;

		}
	}
	else if (weekDay == 5) {
		if (day - 5 < 1) {
			date = findNumDaysMonth(month - 1) - (1 - (day - 5));
			currentMonthDays = findNumDaysMonth(month - 1);
		}
		else {
			date = day - 5;
		}
		for (int i = 0; i < 7; i++) {
			if (date > currentMonthDays) {
				date = 1;
			}
			if (date < 10) {
				std::cout << date << "   ";
			}
			else {
				std::cout << date << "  ";
			}
			date++;

		}
	}
	else if (weekDay == 6) {
		if (day - 6 < 1) {
			date = findNumDaysMonth(month - 1) - (1 - (day - 6));
			currentMonthDays = findNumDaysMonth(month - 1);
		}
		else {
			date = day - 6;
		}
		for (int i = 0; i < 7; i++) {
			if (date > currentMonthDays) {
				date = 1;
			}
			if (date < 10) {
				std::cout << date << "   ";
			}
			else {
				std::cout << date << "  ";
			}
			date++;

		}
	}
	std::cout << std::endl;
}

void printDay(int year, int month, int day, DoubleLinkedList* calendar) {
	std::cout << "Day: "<< day << " - " << month << " - " << year << std::endl;
	Node* temp = calendar->getNode(year, month, day);
	std::vector<std::string> details = temp->getDetails();
	for (int i = 0; i < details.size(); i++) {
		std::cout << i << ") " <<details[i] << std::endl;
	}
	return;
}

std::vector<std::string> parseCommand(std::string command_str) {
	std::vector<std::string> command_vec = std::vector<std::string>();
	int index = 0;
	std::string temp = "";
	while (index < command_str.length()) {
		if (command_str.at(index) != ' ') {
			temp.append(1,command_str.at(index));
		} else {
			command_vec.push_back(temp);
			temp = "";
		}
		index++;
	}
	command_vec.push_back(temp);
	return(command_vec);
}

std::vector<int> checkCommand(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	if (command_vec[0] == "help") { //If first command is help
		std::cout << "help                           || Display this menu\n";
		std::cout << "goto year [year]               || Display the year with the specified [year]\n";
		std::cout << "goto month [year] [month]      || Display the month with the specified [year] and [month]\n";
		std::cout << "goto week [year] [month] [day] || Display the week with the specified [year], [month], and [day]\n";
		std::cout << "goto day [year] [month] [day]  || Display the day with the specified [year], [month], and [day] and change it to the currently focused day\n";
		std::cout << "detail add                     || Add a detail to the currently checked out day displayed at the command entry\n";
		std::cout << "detail remove [index]          || Remove the detail at the index of the currently checked out day\n";
		std::cout << "details                        || Display the details of the current day\n";
		std::cout << "exit                           || Exit the program\n";
	} else if (command_vec[0] == "exit") { //If first command is exit
		ret.push_back(0);
	} else if (command_vec[0] == "goto") { //If first command is goto
		if (command_vec[1] == "year") {
			printYear(atoi(command_vec[2].c_str()));
		} else if (command_vec[1] == "month") {
			printMonth(atoi(command_vec[2].c_str()), atoi(command_vec[3].c_str()));
		} else if (command_vec[1] == "week") {
			//printWeek(atoi(command_vec[2].c_str()), atoi(command_vec[3].c_str()), atoi(command_vec[4].c_str()));
		} else if (command_vec[1] == "day") {
			printDay(atoi(command_vec[2].c_str()), atoi(command_vec[3].c_str()), atoi(command_vec[4].c_str()), calendar);
			ret.push_back(atoi(command_vec[2].c_str()));
			ret.push_back(atoi(command_vec[3].c_str()));
			ret.push_back(atoi(command_vec[4].c_str()));
		} else {
			std::cout << "Incorrect input: type 'help' for more help\n";
		}
	} else if (command_vec[0] == "detail") {
		Node* temp = calendar->getNode(currentDate[0], currentDate[1], currentDate[2]);
		if (command_vec[1] == "add") {
			std::string tmp_str = "";
			std::cout << currentDate[2] << "-" << currentDate[1] << "-" << currentDate[0] << " Input Detail> ";
			getline(std::cin, tmp_str);
			temp->addDetail(tmp_str);
		} else if (command_vec[1] == "remove") {
			temp->removeDetail(atoi(command_vec[2].c_str()));
		} else {
			std::cout << "Incorrect input: type 'help' for more help\n";
		}
	} else if (command_vec[0] == "details") {
		printDay(currentDate[0], currentDate[1], currentDate[2], calendar);
	} else {
		std::cout << "incorrect input: type 'help' for more help\n";
	}
	return(ret);
}

int main() {
	//Setup on startup
	std::string command_str = std::string();
	std::vector<std::string> command_vec = std::vector<std::string>();
	bool isRunning=true;
	std::vector<int> currentDate = {2016,8,1};
	DoubleLinkedList* calendar = new DoubleLinkedList(2016,8,2017,5);
	ReadWrite writer = ReadWrite();
	writer.getFileInfo(calendar);
	currentDate = writer.getDate();
	std::vector<int> ret = std::vector<int>();

	//Run program
	while(isRunning) {
		std::cout << currentDate[2] << "-" << currentDate[1] << "-" << currentDate[0] << " Enter Command> ";
		getline(std::cin, command_str);
		command_vec = parseCommand(command_str);
		ret = checkCommand(command_vec, calendar, currentDate);
		if (ret.size() == 1) {
			isRunning = false;
		} else if (ret.size() == 3) {
			for (int i=0;i<3;i++) {
				currentDate[i] = ret[i];
			}
		}
	}

	//Delete linked list.
	writer.setDate(currentDate);
	writer.storeFileInfo(calendar);
	delete calendar;
	return(0);
}