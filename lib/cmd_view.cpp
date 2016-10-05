#include "command.h"

namespace CMD_VIEW
{

std::string months[13] = {
	"ERR", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

static std::string getMonth( int m )
{
	if ( m < 1 || m > 12 )
	{ return "ERR"; }
	return months[m];
}

static std::vector<int> year(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	std::unordered_map<std::string, int> printed_months;
	
	for ( 	Node * curDay = calendar->getFront(); // iterate through all days of the calendar
			curDay != nullptr; 
			curDay = curDay->getNext() 	)
	{
		int month_num         = curDay->getMonth();
		int events_found      = 0;
		std::string month_str = getMonth( month_num ); // get this day's 3 letter month code.
		
		auto printed = printed_months.find( month_str ); 
		if( printed == printed_months.end() ) {       // is this a new month?
			std::cout << " | " << month_str;          // yep print it
			printed_months.insert( { month_str, 0 } );// mark it as printed
		}
		else
		{                                             // nope it is old, see if we printed the star yet.
			events_found = printed_months[ month_str ];
		}
		
		if( events_found > 0 ){ continue; }         // we already printed the star, keep going.
		
		if( curDay->getDetails().size() > 0 )       // we have not found an event yet
		{
			std::cout << "*";                      // now we have so print the start
			printed_months[ month_str ]++;         // mark it so we only print 1 star.
		}
	}
	
	std::cout << " |\n\n";
	return( ret );
}


std::vector<int> func(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	if( command_vec.size() == 0 )
	{
		std::cout << "Incorrect input: view command requires arguments. type 'help' for more details.\n\n";
		return( ret );
	}
	
	// map the command names to command functions.
	std::unordered_map<std::string, commandfunc *> commands = {
		{ "year", &year }
	};
	
	// see if the user's command was in the map.
	auto cmd_func = commands.find( command_vec[0] );
	if( cmd_func != commands.end() ) {
		// it was, so call that function but without the name of the command since it knows that.
		command_vec.erase(command_vec.begin());
		ret = cmd_func->second( command_vec, calendar, currentDate );
	}
	
	return( ret );
}

}
