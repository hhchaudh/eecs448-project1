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

void printDayHead()
{
	std::cout << "---|-------|------------|----------|---------------------------------------------------|\n";
	return;
}

void printDayBlankBegin()
{
	std::cout << "   |       |            |          |";
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

static void markEventsDoubleBooked( std::vector<Detail> * dets )
{
	// step through the details and mark the overlaps.
	auto current = dets->begin();
	auto done = dets->end();
	Detail * latestEnding = nullptr;
	for ( ; current != done; current++ )
	{
		current->setDoubleBooked( false );  // assume it is false and only set if it is double booked.
		if( current->getStartHours() == 99 ){ continue; } // ignore day events.
		
		if( latestEnding == nullptr ) // no event to compare it to so no overlap yet
		{
			latestEnding = &(*current); // and detail has the latest ending.
			continue;
		}
		
		if(  (  current->getStartHours() < latestEnding->getDoneHours()  )
			 || (
				     current->getStartHours()   ==  latestEnding->getDoneHours()
				  && current->getStartMinutes() <   latestEnding->getDoneMinutes() 	
				)
		)
		{
			// overlapping events
			current->setDoubleBooked( true );
			latestEnding->setDoubleBooked( true );
		}
		
		if(  ( current->getDoneHours() > latestEnding->getDoneHours() )
		     || (
					current->getDoneHours()   == latestEnding->getDoneHours()
			     && current->getDoneMinutes() >  latestEnding->getDoneMinutes()	
				)
		)
		{
			latestEnding = &(*current);
		}	
	}
}

void printDay( Node * day )
{
	// print the day header.
	std::cout << "Day: "<< day->getDay() << " - " << day->getMonth() << " - " << day->getYear() << std::endl;
	printDayHead();
	std::cout << "   | DBook | Start Time | End Time |      Event                                        |" << std::endl;
	printDayHead();
	
	std::vector<Detail> dets = day->getDetails();
	markEventsDoubleBooked( &dets );
	
	// Step through events and print.
	auto current = dets.begin();
	auto done = dets.end();
	int i = 0;
	for ( ; current != done; current++, i++ )
	{
		int buf_size = 64;
		char buffer[ buf_size ];
		std::cout << i << ") |";
		if( current->getDoubleBooked() ){  std::cout << "   X   |";  }
		else						    {  std::cout << "       |";  }
		if( current->getStartHours() == 99 ){  std::cout << "    -----   |   -----  |";  }
		else
		{
			snprintf( buffer, buf_size,
					 "    %02d:%02d   |   %02d:%02d  |", 
					 current->getStartHours(), current->getStartMinutes(), 
					 current->getDoneHours(),  current->getDoneMinutes() 
			);
			buffer[ buf_size - 1 ]  = '\0';
			std::cout << buffer;
		}
		
		std::string leftToPrint = current->getText();
		while( leftToPrint.size() > 50 )
		{
			std::cout << " " << leftToPrint.substr( 0, 50 ) << "|\n";
			printDayBlankBegin();
			leftToPrint = leftToPrint.substr( 50 );
		}
		
		int extraPrint = 50 - leftToPrint.size();
		std::cout << " " << leftToPrint << std::string( extraPrint, ' ') << "|\n";
		printDayHead();
	}
	
	std::cout << "\n";
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
