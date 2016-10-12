/**
 * @file main.cpp The main functions for running the Calendar program.
 */


#include "calendar_std.h"
#include "command.h"

/**
 * Finds the number of days in the month of the given year
 * @param year 	The year of the month
 * @param month The month to be checked
 * @return The number of days in the month for the given year
 */
int findNumDaysMonth(int year, int month) {
	int val = 0; //Used to add extra day to February for leap year
	int daysInMonths[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (month == 2) { //If not checking for February
		if (year % 400 == 0) {
			val = 1;
		} else if (year % 4 == 0 && year % 100 != 0) {
			val = 1;
		}
	}
	return(daysInMonths[month-1] + val);
}


/**
 * Takes a command as a string and parses it into the seperate parts.
 * @param command_str 	The string to be broken apart.
 * @return A vector of strings that are the different parts of the command.
 */
std::vector<std::string> parseCommand(std::string command_str) {
	std::vector<std::string> command_vec = std::vector<std::string>();
	unsigned int index = 0;
	std::string temp = "";
	while (index < command_str.length()) {
		if (command_str.at(index) != ' ' && command_str.at(index) != '\t') {
			temp.append(1,command_str.at(index));
		} else {
			if( temp != "" ) {
				command_vec.push_back(temp);
			}
			temp = "";
		}
		index++;
	}
	command_vec.push_back(temp);
	return(command_vec);
}

std::vector<int> cmd_exit(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	ret.push_back(0);
	
	return(ret);
}

/**
 * Checks what command should be ran.
 * @param comand_vec 	The seperated command.
 * @param calendar 		The DoubleLinkedList object that is the calendar.
 * @param currentDate 	The current date of focus for the program.
 * @return A vector of ints that are either the new current day, or a command to close the program.
 */
std::vector<int> checkCommand(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	// map the command names to command functions.
	std::unordered_map<std::string, commandfunc *> commands = {
		{ "help",   &CMD_HELP::func   },
		{ "view",   &CMD_VIEW::func   },
		{ "detail", &CMD_DETAIL::func },
		{ "exit",   &cmd_exit         }
	};
	
	// see if the user's command was in the map.
	auto cmd_func = commands.find( command_vec[0] );
	if( cmd_func != commands.end() ) {
		// it was, so call that function but without the name of the command since it knows that.
		command_vec.erase(command_vec.begin());
		ret = cmd_func->second( command_vec, calendar, currentDate );
	} else if (command_vec[0] == "detail") {
		Node* temp = calendar->getNode(currentDate[0], currentDate[1], currentDate[2]);
		if (command_vec[1] == "add") {
			std::string tmp_str = "";
			std::cout << currentDate[2] << "-" << currentDate[1] << "-" << currentDate[0] << " Input Detail> ";
			getline(std::cin, tmp_str);
			Detail myDetail;
			myDetail.setStartHours( 99 );
			myDetail.setStartMinutes( 99 );
			myDetail.setDoneHours( 99 );
			myDetail.setDoneMinutes( 99 );
			myDetail.setText( tmp_str );
			temp->addDetail( myDetail );
		}
	} else {
		std::cout << "incorrect input |" << command_vec[0] << "| is not a valid command.\n";
		std::cout << "Try typing 'help' for a list of commands.\n\n";
	}
	
	return(ret);
}

/**
 * The main method of the program.
 * @author Rony Singh
 * @author Jackson Schilmoeller
 * @author Chris Porras
 * @author Brad Gibbons
 * @version 1.0, 18 Sep 2016
 * @return The return message of the program.
 */
int main() {
	//Setup on startup
	std::string command_str = std::string(); // string to catch user input
	// user's command string broken into tokens, starts as help to display help.
	std::vector<std::string> command_vec { "help" };
	bool isRunning=true;
	
	// default the current date. We are just going to blindly write over this though.
	std::vector<int> currentDate = {2016,8,1};
	
	// create our calendar which is a linked list of days.
	DoubleLinkedList* calendar = new DoubleLinkedList(2016,8,2017,5);
	
	// create the database with current date 2016,8,1 if it does not exist
	// also set internal current date of writer to 2016,8,1 no matter what.
	ReadWrite writer = ReadWrite();
	
	// get the current date and all events stored in the file.
	writer.getFileInfo(calendar);
	
	// use the current date that was in the file.
	currentDate = writer.getDate();
	std::vector<int> ret = std::vector<int>();
	
	// welcome message + help menu.
	std::cout << "\n\n---- Welcome to the Calendar Program ----\n\n";
	std::cout << "Valid commands are:\n";
	checkCommand(command_vec, calendar, currentDate);

	//Run program
	while(isRunning) {
		// prompt user for a command.
		std::cout << currentDate[2] << "-" << currentDate[1] << "-" << currentDate[0] << " Enter Command> ";
		getline(std::cin, command_str);
		
		// break the command up by spaces and tabs. Multiple spaces allowed. 
		// Garunteed vecotr[0] is at least "" even if the user didn't enter anything.
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

	//Store Calendar info to file and delete linked list.
	writer.setDate(currentDate);
	writer.storeFileInfo(calendar);
	delete calendar;
	return(0);
}
