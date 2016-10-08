#include "calendar_std.h"
#include "command.h"
#include <regex>

namespace CMD_DETAIL
{

static int getIntGarunteed( std::string digits )
{
	return atoi( digits.c_str() );
}

static int getIntFrom2Digit( std::string digits)
{
	// If there is a leading 0, then drop it.
	if( digits.substr( 0, 1 ) == "0" )
	{
		digits = digits.substr( 1, 1 );
	}
	
	// after that we should just be able to use atoi to convert.
	return atoi( digits.c_str() );
}

static bool getUserTime( Detail * det )
{
	int retries = 3;
	std::string startTime, endTime;
	std::regex reg( "^[0-9]{2}:[0-9]{2}$" );
	while ( true )
	{
		if( 0 == retries--){ return false; }
		
		std::cout << "Please enter a start time, ex: 00:00, in military time. [q] to abort.\n";
		std::cin >> startTime;
		
		// user wanted to quit, get otta here.
		if( startTime.size() > 0 && startTime.substr( 0, 1 ) == "q" ){ return false; }
		
		if( !std::regex_match( startTime, reg) )
		{   // user's input was invalid.
			std::cout << "\nInvalid entry |" << startTime << "|. Please try again.\n\n";
			continue;
		}
		
		break;
	}
		
	// well at least the start time was good.	
	det->setStartHours( 
			getIntFrom2Digit( 
				startTime.substr( 0, 2 )
			) 
	);
	det->setStartMinutes( 
			getIntFrom2Digit( 
				startTime.substr( 3, 2 )
			) 
	);
		
	retries = 3;
	while ( true )
	{
		if( 0 == retries--){ return false; }
		
		std::cout << "Please enter an end time, ex: 00:00, in military time. [q] to abort.\n";
		std::cin >> endTime;
		
		// user wanted to quit, get otta here.
		if( endTime.size() > 0 && endTime.substr( 0, 1 ) == "q" ){ return false; }
		
		if( !std::regex_match( endTime, reg) )
		{   // user's input was invalid.
			std::cout << "\nInvalid entry |" << endTime << "|. Please try again.\n\n";
			continue;
		}
		
		break;
	}
		
	// Now the end time was also good.
	det->setDoneHours( 
			getIntFrom2Digit( 
				endTime.substr( 0, 2 )
			) 
	);
	det->setDoneMinutes( 
			getIntFrom2Digit( 
				endTime.substr( 3, 2 )
			) 
	);
	
	return true;
}

static bool getRecurrence( int * recurrence )
{
	std::string userTry;
	std::regex numReg( "^[1-9][0-9]{0,2}$" );
	int retries = 3;
	
	std::cout   << "How many times should this event happen?\n"
				<< "1 - 999   => 1 - 999\n" 
				<< "EOC       => to end of Calendar.\n" 
				<< "[q]       => abort.\n";
	
	while ( true )
	{
		if( 0 == retries--){ return false; }
		
		std::cin >> userTry;
		
		if( userTry == "EOC" ){ *recurrence = 0;    return true;   }
		
		if( userTry == "q" ){  return false;  }
		
		if( std::regex_match( userTry, numReg) )
		{
			*recurrence = getIntGarunteed( userTry );
			return true;
		}
		
		std::cout   << "The value |" << userTry << "| is not a valid number of retries.\n"
					<< "Please try again:\n";
	}
	
	// should not get here.
	return false;
}

static std::vector<int> add(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	// confirm correct number of arguments.
	if( command_vec.size() != 1 && command_vec[0] != "day" && command_vec[0] != "time" )
	{
		std::cout << "Incorrect input: should be: detail add [time|day]\n\n";
		return( ret );
	}
	
	Detail det; // automatically initialized to times of 99.
	if( command_vec[0] == "time" ) // try to get the time from the user.
	{
		if( !getUserTime( &det ) )
		{
			std::cout << "No detail added, did not get a time.\n\n";
			return( ret );
		}
	}
	
	int recurrence;
	if( ! getRecurrence( &recurrence) )
	{
		std::cout << "No detail added, did not get a valid recurrence.\n\n";
		return( ret );
	}
	
	std::cout << "rec = |" << recurrence <<"| Got sTime = |" << det.getStartHours() << ":" << det.getStartMinutes() << "| endTime = |" 
								<< det.getDoneHours() << ":" << det.getDoneMinutes() << "|\n\n";
	
	return( ret );
}

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
		{ "add",    &add    },
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
