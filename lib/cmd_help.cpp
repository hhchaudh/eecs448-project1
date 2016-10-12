/**
 * @file cmd_help.cpp A module that is used to display help menu.
 */

//! A module that is used to display help menu

#include "calendar_std.h"
#include "command.h"

namespace CMD_HELP
{

/*! 
 * \addtogroup CMD_HELP
 * @{ 
 */

/**
 * Prints out the help menu.
 * @param command_vec ignored, no args.
 * @param calendar The linked list of days which compose the calendar.
 * @param currentDate The currently selected day.
 * @return A date vector to change the current date, empty for success, and a single entry to exit the program.
 */

std::vector<int> func(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	std::cout << "help                           || Display this menu\n";
	std::cout << "view year                      || Display the year view\n";
	std::cout << "view month [month]             || Display the month with the specified [year] and [month]\n";
	std::cout << "view week  [month] [day]       || Display the week with the specified [year], [month], and [day]\n";
	std::cout << "view day   [month] [day]       || Display the day with the specified [year], [month], and [day] and change "
																							"it to the currently focused day\n";
	std::cout << "view current                   || Display the details of the current day\n";
	std::cout << "detail add                     || Add a detail to the currently checked out day displayed at the command entry\n";
	std::cout << "detail remove [index]          || Remove the detail at the index of the currently checked out day\n";
	std::cout << "exit                           || Exit the program\n";
	std::cout << "Valid months are all upper or lower case:\n";
	std::cout << "                                  AUG, SEP, OCT, NOV, DEC, JAN, FEB, MAR, APR, MAY\n";
	std::cout << "\n";
	
	return(ret);
}

/*! @} End of Doxygen Groups*/

}
