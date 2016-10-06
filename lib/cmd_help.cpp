#include "calendar_std.h"
#include "command.h"

namespace CMD_HELP
{

std::vector<int> func(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	std::cout << "help                           || Display this menu\n";
	std::cout << "view year                      || Display the year view\n";
	std::cout << "view month [year] [month]      || Display the month with the specified [year] and [month]\n";
	std::cout << "view week [year] [month] [day] || Display the week with the specified [year], [month], and [day]\n";
	std::cout << "view day [year] [month] [day]  || Display the day with the specified [year], [month], and [day] and change "
																							"it to the currently focused day\n";
	std::cout << "detail add                     || Add a detail to the currently checked out day displayed at the command entry\n";
	std::cout << "detail remove [index]          || Remove the detail at the index of the currently checked out day\n";
	std::cout << "details                        || Display the details of the current day\n";
	std::cout << "exit                           || Exit the program\n";
	std::cout << "\n";
	
	return(ret);
}

}
