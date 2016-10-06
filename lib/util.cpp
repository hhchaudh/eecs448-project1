#include "calendar_std.h"
#include "command.h"

namespace UTIL
{

/**
 * Returns the day of the week (sun=0 through sat=6).
 * @param y     The year of the day
 * @param m     The month of the day
 * @param d     The day
 * @return The day of the week as an int (sun=0 through sat=6).
 */
int getDayofweek(int y, int m, int d) {
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

int getDayofweek( Node * day ) {
	return getDayofweek( day->getYear(), day->getMonth(), day->getDay() );
}

int month_to_year[] = {
//  INVAL  JAN   FEB   MAR   APR   MAY   JUN   JUL   AUG   SEP   OCT   NOV   DEC
	2017, 2017, 2017, 2017, 2017, 2017, 2017, 2017, 2016, 2016, 2016, 2016, 2016
};

std::unordered_map<std::string, int> mon_to_int = {
        { "JAN", 1 }, { "FEB", 2 }, { "MAR", 3 }, { "APR", 4  }, { "MAY", 5  }, { "JUN", 6  }, 
        { "jan", 1 }, { "feb", 2 }, { "mar", 3 }, { "apr", 4  }, { "may", 5  }, { "jun", 6  }, 
		{ "JUL", 7 }, { "AUG", 8 }, { "SEP", 9 }, { "OCT", 10 }, { "NOV", 11 }, { "DEC", 12 },
		{ "jul", 7 }, { "aug", 8 }, { "sep", 9 }, { "oct", 10 }, { "nov", 11 }, { "dec", 12 }
};

void printCalHead()
{
	std::cout << "| SUN | MON | TUE | WED | THU | FRI | SAT |\n";
	return;
}

void printWeekHead()
{
	std::cout << "|-----------------------------------------|\n";
	return;
}

int getMonNum( std::string monthName )
{
	auto month = mon_to_int.find( monthName );
	if( month == mon_to_int.end() ) {
		return 0;
	}
	
	return mon_to_int[ monthName ];
}

const std::string months[] = {
	"ERR", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

std::string getMonth( int m )
{
	if ( m < 1 || m > 12 )
	{ return "ERR"; }
	return months[m];
}

Node * printWeek( Node * day, bool monthWrap, std::vector<int> currentDate )
{
	int dayOfWeek = getDayofweek( day );
	int origionalMonth = day->getMonth();
	
	// Step backward through this week until we get to Sunday or beginning of Calendar
	while (  (dayOfWeek > 0)  &&  (day->getPrev() != nullptr)  )
	{
		day = day->getPrev();
		dayOfWeek--;
		
		// If we don't want to wrap to the previous month, Then stop at the first.
		if(   !monthWrap   &&   ( day->getMonth() != origionalMonth )   )
		{
			day = day->getNext();
			dayOfWeek++;
			break;
		}
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

}
