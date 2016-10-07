#include "calendar_std.h"
#include "command.h"

namespace CMD_DETAIL
{

static std::vector<int> remove(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	// confirm correct number of arguments.
	if( command_vec.size() != 1 )
	{
		std::cout << "Incorrect input: should be: detail remove [index]\n\n";
		return( ret );
	}
	
	Node * date = calendar->getNode(currentDate[0], currentDate[1], currentDate[2]);
	std::vector<Detail> dets =  date->getDetails();
	int index = atoi(command_vec[0].c_str());
	
	if (index < 0 || (unsigned)index >= dets.size() ) {
		std::cout << "Incorrect input: could not find index |" << index << "| on current date.\n\n";
		return( ret );
	}
	
	date->removeDetail(index);
	std::cout << "Removed detail.\n\n";
	
	return( ret );
}


std::vector<int> func(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	if( command_vec.size() == 0 )
	{
		std::cout << "Incorrect input: detail command requires arguments. type 'help' for more details.\n\n";
		return( ret );
	}
	
	// map the command names to command functions.
	std::unordered_map<std::string, commandfunc *> commands = {
		{ "remove", &remove }
	};
	
	// see if the user's command was in the map.
	auto cmd_func = commands.find( command_vec[0] );
	if( cmd_func != commands.end() ) {
		// it was, so call that function but without the name of the command since it knows that.
		command_vec.erase(command_vec.begin());
		ret = cmd_func->second( command_vec, calendar, currentDate );
	}
	else
	{
		std::cout << "incorrect input |" << command_vec[0] << "| is not a valid first arg for the command detail.\n";
		std::cout << "Try typing 'help' for a list of commands.\n\n";
	}
	
	return( ret );
}

}
