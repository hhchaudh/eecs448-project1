/**
 * @file cmd_view.cpp A module that is used to display content to the user.
 */

//! A module that is used to display content to the user.

#include "calendar_std.h"
#include "command.h"

namespace CMD_VIEW
{

/*! 
 * \addtogroup CMD_VIEW 
 * @{ 
 */

/**
 * Prints out events and info for the selected date.
 * @param command_vec Contains the Month and Day to be printed.
 * @param calendar The linked list of days which compose the calendar.
 * @param currentDate The currently selected day.
 * @return A date vector to change the current date, empty for success, and a single entry to exit the program.
 */
static std::vector<int> day(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	// confirm correct number of arguments.
	if( command_vec.size() != 2 )
	{
		std::cout << "Incorrect input: should be: view day [month] [day]\n\n";
		return( ret );
	}
	
	// make sure the date they entered is a valid date.
	int day   = atoi(  command_vec[1].c_str()  );
	int month = UTIL::getMonNum( command_vec[0] );
	int year = UTIL::month_to_year[ month ];
	if( !month  ||  !day  ||  ( calendar->getNode( year, month, day ) == nullptr )   )
	{
		std::cout << "Incorrect input: Could not find the date:" << month << "/" << day << "/" << year << "\n\n";
		return( ret );
	}
	
	Node* date = calendar->getNode(year, month, day);
	
	UTIL::printDay( date );
	
	currentDate[0] = date->getYear();
	currentDate[1] = date->getMonth();
	currentDate[2] = date->getDay();
	
	return( currentDate );
}

/**
 * Prints out events and info for the currently selected day.
 * @param command_vec ignored
 * @param calendar The linked list of days which compose the calendar.
 * @param currentDate The currently selected day.
 * @return A date vector to change the current date, empty for success, and a single entry to exit the program.
 */
static std::vector<int> current(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	// convert the current day to the form of the view day command and use that.
	std::vector<std::string> date = {
			UTIL::getMonth( currentDate[1] ), 
			std::to_string( currentDate[2])
	};
	
	ret = day( date, calendar, currentDate );
	
	return( ret );
}

/**
 * Prints out a Calendar resembling a month. Days with events are morked with '*' the current date is marked with '@'
 * @param command_vec Contains the Month to be printed.
 * @param calendar The linked list of days which compose the calendar.
 * @param currentDate The currently selected day.
 * @return A date vector to change the current date, empty for success, and a single entry to exit the program.
 */
static std::vector<int> month(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	// check the command got the right amount of arguments.
	if( command_vec.size() != 1 )
	{
		std::cout << "Incorrect input: should be: view month [month]\n\n";
		return( ret );
	}
	
	// Check that that argument was a month that is in the Calendar
	Node * day = calendar->getFront();
	int desiredMonthNum = UTIL::getMonNum( command_vec[0] );
	while ( day != nullptr && day->getMonth() != desiredMonthNum )
	{
		day = day->getNext();
	}
	
	if( day == nullptr )
	{
		std::cout << "Incorrect input: Could not find the month: " << command_vec[0] << "\n\n";
		return( ret );
	}
	
	// not only is the month in the Calendar, we also have a pointer to the first day of that month.
	UTIL::printWeekHead();
	UTIL::printCalHead();
	UTIL::printWeekHead();
	while( day != nullptr && day->getMonth() == desiredMonthNum )
	{
		// print all the weeks of the month.
		day = UTIL::printWeek( day, false, currentDate );
		UTIL::printWeekHead();
	}
	
	std::cout << "\n";
	
	return( ret );
}

/**
 * Prints out a Calendar resembling a week. Days with events are morked with '*' the current date is marked with '@'
 * @param command_vec Contains the Month and day of the week to be printed.
 * @param calendar The linked list of days which compose the calendar.
 * @param currentDate The currently selected day.
 * @return A date vector to change the current date, empty for success, and a single entry to exit the program.
 */
static std::vector<int> week(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	if( command_vec.size() != 2 )
	{
		std::cout << "Incorrect input: should be: view week [month] [day]\n\n";
		return( ret );
	}
	
	int monthNum = UTIL::getMonNum( command_vec[0] );
	int dayNum = atoi(  command_vec[1].c_str()  );
	int year = UTIL::month_to_year[ monthNum ];
	if( !monthNum  ||  !dayNum  ||  ( calendar->getNode( year, monthNum, dayNum ) == nullptr )   )
	{
		std::cout << "Incorrect input: Could not find the date:" << monthNum << "/" << dayNum << "/" << year << "\n\n";
		return( ret );
	}
	
	Node * day = calendar->getNode( year, monthNum, dayNum );
	
	UTIL::printWeekHead();
	UTIL::printCalHead();
	UTIL::printWeekHead();
	UTIL::printWeek( day, true, currentDate );
	UTIL::printWeekHead();
	std::cout << "\n";
	
	return( ret );
}

/**
 * Prints out a Calendar resembling a year. Months with events are morked with '*' the current date is marked with '@'
 * @param command_vec ignored.
 * @param calendar The linked list of days which compose the calendar.
 * @param currentDate The currently selected day.
 * @return A date vector to change the current date, empty for success, and a single entry to exit the program.
 */
static std::vector<int> year(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	std::unordered_map<std::string, int> printed_months;
	
	for ( 	Node * curDay = calendar->getFront(); // iterate through all days of the calendar
			curDay != nullptr; 
			curDay = curDay->getNext() 	)
	{
		int month_num         = curDay->getMonth();
		int events_found      = 0;
		std::string month_str = UTIL::getMonth( month_num ); // get this day's 3 letter month code.
		
		auto printed = printed_months.find( month_str ); 
		if( printed == printed_months.end() ) {       // is this a new month?
			std::cout << "| " << month_str << " ";    // yep print it
			printed_months.insert( { month_str, 0 } );// mark it as printed
		}
		else
		{                                             // nope it is old, see if we printed the star yet.
			events_found = printed_months[ month_str ];
		}
		
		if( curDay->getMonth() == currentDate[1] && curDay->getDay() == currentDate[2])
		{	std::cout << "@";	}					// This month contains the current day so mark it.
		
		if( events_found > 0 ){ continue; }         // we already printed the star, keep going.
		
		if( curDay->getDetails().size() > 0 )       // we have not found an event yet
		{
			std::cout << "*";                      // now we have so print the start
			printed_months[ month_str ]++;         // mark it so we only print 1 star.
		}
	}
	
	std::cout << "|\n\n";
	return( ret );
}


/**
 * Takes care to call all of the view commands.
 * @param command_vec Contains the command name plus arguments.
 * @param calendar The linked list of days which compose the calendar.
 * @param currentDate The currently selected day.
 * @return A date vector to change the current date, empty for success, and a single entry to exit the program.
 */
std::vector<int> func(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	if( command_vec.size() == 0 )
	{
		std::cout << "Incorrect input: view command requires arguments. type 'help' for more details.\n\n";
		return( ret );
	}
	
	// map the command names to command functions.
	std::unordered_map<std::string, commandfunc *> commands = {
		{ "year",    &year    },
		{ "month",   &month   },
		{ "week",    &week    },
		{ "day",     &day     },
		{ "current", &current }
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
		std::cout << "incorrect input |" << command_vec[0] << "| is not a valid first arg for the command view.\n";
		std::cout << "Try typing 'help' for a list of commands.\n\n";
	}
	
	return( ret );

/*! @} End of Doxygen Groups*/

}

}
