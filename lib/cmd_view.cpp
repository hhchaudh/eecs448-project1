#include "command.h"

namespace CMD_VIEW
{
static int getDayofweek(int y, int m, int d) {
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

static int getDayofweek( Node * day ) {
	return getDayofweek( day->getYear(), day->getMonth(), day->getDay() );
}

static int month_to_year[] = {
//  INVAL  JAN   FEB   MAR   APR   MAY   JUN   JUL   AUG   SEP   OCT   NOV   DEC
	2017, 2017, 2017, 2017, 2017, 2017, 2017, 2017, 2016, 2016, 2016, 2016, 2016
};

std::unordered_map<std::string, int> mon_to_int = {
        { "JAN", 1 }, { "FEB", 2 }, { "MAR", 3 }, { "APR", 4  }, { "MAY", 5  }, { "JUN", 6  }, 
        { "jan", 1 }, { "feb", 2 }, { "mar", 3 }, { "apr", 4  }, { "may", 5  }, { "jun", 6  }, 
		{ "JUL", 7 }, { "AUG", 8 }, { "SEP", 9 }, { "OCT", 10 }, { "NOV", 11 }, { "DEC", 12 },
		{ "jul", 7 }, { "aug", 8 }, { "sep", 9 }, { "oct", 10 }, { "nov", 11 }, { "dec", 12 }
};

static void printCalHead()
{
	std::cout << "| SUN | MON | TUE | WED | THU | FRI | SAT |\n";
	return;
}

static void printWeekHead()
{
	std::cout << "|-----------------------------------------|\n";
	return;
}

static int getMonNum( std::string monthName )
{
	auto month = mon_to_int.find( monthName );
	if( month == mon_to_int.end() ) {
		return 0;
	}
	
	return mon_to_int[ monthName ];
}

std::string months[] = {
	"ERR", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

static std::string getMonth( int m )
{
	if ( m < 1 || m > 12 )
	{ return "ERR"; }
	return months[m];
}

static Node * printWeek( Node * day, bool monthWrap, std::vector<int> currentDate )
{
	int dayOfWeek = getDayofweek( day );
	int origionalMonth = day->getMonth();
	
	// Step backward through this week until we get to Sunday or beginning of Calendar
	while (  (dayOfWeek > 0)  &&  (day->getPrev() != nullptr)  )
	{
		// If we don't want to wrap to the previous month, Then stop at the first.
		if(   !monthWrap   &&   ( day->getMonth() != origionalMonth )   )
		{
			day = day->getNext();
			dayOfWeek++;
			break;
		}
		
		day = day->getPrev();
		dayOfWeek--;
	}
	
	// we might not be on Sunday, so print blank spots until the day we are at.
	std::cout << "|";
	std::string blankDay = "     |";
	for ( int i = 0; i < dayOfWeek; i++ )
	{
		std::cout << blankDay;
	}
	
	// Print the days until the end of week, or the end of the calendar.
	while (   (dayOfWeek < 7)  &&  (day != nullptr)   )
	{
		// If we don't want to wrap around months, then stop here.
		if(   !monthWrap   &&   ( day->getMonth() != origionalMonth )   )
		{
			break;
		}
		
		char buff[3];
		sprintf( buff, "%2d", day->getDay() );
		std::cout << " " << buff;
		
		// print '*' if day has details.
		if( day->getDetails().size() != 0 )  { std::cout << "*";    }
		else                                 { std::cout << " ";    }
		
		// print '@' if this is the current selected day.
		if( day->getMonth() == currentDate[1] && day->getDay() == currentDate[2])
		     { std::cout << "@";  }
		else { std::cout << " ";  }
		
		std::cout << "|";
		
		dayOfWeek++;
		day = day->getNext();
	}
	
	// might not have printed a full week, so fill the rest with blanks.
	for( int i = dayOfWeek; i < 7; i++ )
	{
		std::cout << blankDay;
	}

	std::cout << "\n";	
	// return a pointer to the next day that we didn't print, or NULL if we are at end of Calendar.
	return day;
}


static std::vector<int> week(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	
	if( command_vec.size() != 2 )
	{
		std::cout << "Incorrect input: should be: view week month day\n\n";
		return( ret );
	}
	
	int monthNum = getMonNum( command_vec[0] );
	int dayNum = atoi(  command_vec[1].c_str()  );
	int year = month_to_year[ monthNum ];
	if( !monthNum  ||  !dayNum  ||  ( calendar->getNode( year, monthNum, dayNum ) == nullptr )   )
	{
		std::cout << "Incorrect input: Could not find the date:" << monthNum << "/" << dayNum << "/" << year << "\n\n";
		return( ret );
	}
	
	Node * day = calendar->getNode( year, monthNum, dayNum );
	
	printWeekHead();
	printCalHead();
	printWeekHead();
	printWeek( day, true, currentDate );
	printWeekHead();
	std::cout << "\n";
	
	return( ret );
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
		
		if( curDay->getMonth() == currentDate[1] && curDay->getDay() == currentDate[2])
		{	std::cout << "@";	}					// This month contains the current day so mark it.
		
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
		{ "year", &year },
		{ "week", &week }
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
}

}
