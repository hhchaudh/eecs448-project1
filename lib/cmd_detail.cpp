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

static bool isValidTime( std::string timeString, int * retHours, int * retMins, int lastHours, int lastMins )
{
	int hours, mins;
	std::regex validTime( "^[0-9]{2}:[0-9]{2}$" );

	// see if user's input is in valid time format.
	if( !std::regex_match( timeString, validTime ) )
	{   // user's input was invalid.
		std::cout << "\nInvalid entry |" << timeString << "|. Please try again.\n";
		return false;
	}

	// was a valid format, get the hours.
	hours = getIntFrom2Digit( timeString.substr( 0, 2 ) );
	if( hours < 0 || hours > 23 )
	{
		std::cout << "\nInvalid entry |" << timeString.substr( 0, 2 ) << "|. Needs to be within 00 and 23.\n";
		return false;
	}

	// get the minutes.
	mins = getIntFrom2Digit( timeString.substr( 3, 2 ) );
	if( mins < 0 || mins > 59 )
	{
		std::cout << "\nInvalid entry |" << timeString.substr( 3, 2 ) << "|. Needs to be within 00 and 59.\n";
		return false;
	}

	// make sure this time comes after the last time.
	int curTime  = ( hours * 60 ) + mins;
	int lastTime = ( lastHours * 60 ) + lastMins;

	if( lastTime >= curTime)
	{
		std::cout << "\nInvalid entry |" << timeString << "|. Needs to happen after the start of the event.\n";
		return false;
	}

	// this time is fine.
	*retHours = hours;
	*retMins = mins;
	return true;
}

static bool getUserTime( Detail * det )
{
	int retries = 3;
	int hours, mins;
	std::string startTime, endTime;
	while ( true )
	{
		if( 0 == retries--){ return false; }

		std::cout << "\nPlease enter a start time, ex: 00:00, in military time. [q] to abort.\n";
		std::getline ( std::cin, startTime);

		// user wanted to quit, get otta here.
		if( startTime.size() > 0 && startTime.substr( 0, 1 ) == "q" ){ return false; }

		// check this time against a negative time, so it will win.
		if( ! isValidTime( startTime, &hours, &mins, 0, -1 ) )
		{
			continue;
		}

		break;
	}

	// well at least the start time was good.
	det->setStartHours( hours );
	det->setStartMinutes( mins );

	retries = 3;
	while ( true )
	{
		if( 0 == retries--){ return false; }

		std::cout << "\nPlease enter an end time, ex: 00:00, in military time. [q] to abort.\n";
		std::getline ( std::cin, endTime );

		// user wanted to quit, get otta here.
		if( endTime.size() > 0 && endTime.substr( 0, 1 ) == "q" ){ return false; }

		// check this time against the start time.
		if( ! isValidTime( 	endTime,
							&hours, &mins,
							det->getStartHours(), det->getStartMinutes() ) )
		{
			continue;
		}

		break;
	}

	// Now the end time was also good.
	det->setDoneHours( hours );
	det->setDoneMinutes( mins );

	return true;
}

static bool getRecurrence( int * recurrence, bool * repeatMonthly, bool * repeatBiWeekly, bool * repeatWeekly )
{
	std::string userTry;
	std::regex numReg( "^[1-9][0-9]{0,2}$" );
	int retries = 3;

	std::cout   << "\nHow many times should this event happen?\n"
				<< "[number]     => The next [number] of days\n"
				<< "\"weekly\"     => Weekly\n"
				<< "\"bi-weekly\"  => Bi-weekly\n"
				<< "\"monthly\"    => Monthly\n"
				<< "\"q\"          => Abort.\n";

	while ( true )
	{
		if( 0 == retries--){ return false; }

		std::getline ( std::cin, userTry );

		if( userTry == "weekly" ){ *recurrence = 999;  *repeatWeekly=true; return true;   }

		if( userTry == "bi-weekly" ){ *recurrence = 999; *repeatBiWeekly = true; return true;  }

		if( userTry == "monthly" ){ *recurrence = 999; *repeatMonthly = true; return true;  }

		if( userTry == "EOC" ){ *recurrence = 999;    return true;   }

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

static void getUserEvent( Detail * det )
{
	std::string userTry;
	std::cout << "Please enter the event:\n";
	std::getline ( std::cin, userTry );
	det->setText( userTry );
	return;
}

static bool setRepeatDays( bool * addToday, bool * repeatMonthly, bool * repeatBiWeekly, bool * repeatWeekly, std::unordered_map< int, bool> * repeatWeekDay, int recurrence, Node * selectedDate )
{
	/*
	forces repetition every week

	Node * currentDate = selectedDate;
	int timesToRecur = recurrence;
	int DOW = UTIL::getDayofweek( currentDate );

	while(timesToRecur > 0)
	{
		if(DOW == 7)
		{
			DOW = 0;
		}

		(*repeatWeekDay)[DOW] = true;
		timesToRecur--;
	}

	*repeatMonthly = false;
	*repeatWeekly = 9000;
	*addToday = false;
	return true;
	*/

	bool repeatEachWeek = *repeatWeekly;
	bool repeatEveryOtherWeek = *repeatBiWeekly;
	bool repeatEachMonth = *repeatMonthly;


	if(repeatEachMonth) //thought I might need this, so far i don't....
	{
		return true;
	}
	else if(repeatEachWeek || repeatEveryOtherWeek)
	{
		Node * currentDate = selectedDate;
		int DOW = UTIL::getDayofweek( currentDate );
		(*repeatWeekDay)[DOW] = true;

		return true;
	}
	else
	{
		Node * currentDate = selectedDate;
		int timesToRecur;

		if(recurrence > 7)
		{
			timesToRecur = 7;
		}
		else
		{
			timesToRecur = recurrence;
		}

		while(timesToRecur > 0)
		{
			int DOW = UTIL::getDayofweek( currentDate );

			(*repeatWeekDay)[DOW] = true;
			timesToRecur--;
			currentDate = currentDate->getNext();
		}

		return true;
	}

	return false; //Shouldn't get here
}

static void addEvents(
		Detail 	det, 			// The detail to add.
		int 	recurrence, 	// how many times to add it.
		Node * 	selectedDate,	// the currently selected date.
		bool 	addToday,		// Should the current day get added.
		bool 	repeatMonthly, 	// should we repeat every month on selectedDate's day.
		bool 	repeatBiWeekly, // repeat every other week
		bool 	repeatWeekly,	// add event every this many days.
		std::unordered_map< int, bool> * repeatWeekDay // add events on these weekdays.
)
{

	bool alternator = true; //used for bi-weekly alternating
	bool setDetailAtLastDayOfEveryMonth = false; //used to check if a detail repeated monthly falls on the 31st (which would make it fall on the end of every month with fewer than 31 days)
 	bool setDetailAtLastDayOfFeb = false;
	int monthlyDateToRepeat = 0;


	/*
	Okay so we can detect current date
	if that date is the 31st, then last date for all months = true
	if that date is the 30th, then last date for feb = true
	*/
	if(repeatMonthly)
	{
		monthlyDateToRepeat = selectedDate->getDay();
		if(monthlyDateToRepeat == 31)
		{
			setDetailAtLastDayOfEveryMonth = true;
			setDetailAtLastDayOfFeb = true;
		}
		else if(monthlyDateToRepeat == 30)
		{
			setDetailAtLastDayOfFeb = true;
		}
	}

	// step through every day left of the year, until we repeat as many times as we wanted.
	for ( Node * currentDate = selectedDate; currentDate != nullptr && recurrence != 0; currentDate = currentDate->getNext())
	{
		// If we are doing monthly, check if this day is the
		// day of the month that we want.
		if( repeatMonthly )
		{
			if(setDetailAtLastDayOfEveryMonth  && UTIL::lessThanThirtyOne(currentDate) && (currentDate->getDay() == 30) )
			{
				currentDate->addDetail( det );
				recurrence--;
				continue;
			}
			else if(setDetailAtLastDayOfFeb && (currentDate->getMonth() == 2) && (currentDate->getDay() == 28) )
			{
				currentDate->addDetail( det );
				recurrence--;
				continue;
			}
			else if (currentDate->getDay() == monthlyDateToRepeat)
			{
				currentDate->addDetail( det );
				recurrence--;
				continue;
			}
		}


		int DOW = UTIL::getDayofweek( currentDate );

		if(repeatBiWeekly && (*repeatWeekDay)[DOW])
		{
			if(alternator)
			{
				currentDate->addDetail( det );
				recurrence--;
			}
			alternator = !alternator;
			continue;
		}

		// used for adding days continuously or weekly.
		if( (*repeatWeekDay)[ DOW ] )
		{
			currentDate->addDetail( det );
			recurrence--;
			continue;
		}

		// Add to the current day if we want that. (does nothing...)
		if( addToday && currentDate == selectedDate )
		{
			currentDate->addDetail( det );
			recurrence--;
		}
	}
}

static std::vector<int> add(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate) {
	std::vector<int> ret = std::vector<int>();
	bool addToday = false;
	bool repeatMonthly = false;
	bool repeatWeekly  = false;
	bool repeatBiWeekly = false;

	// confirm correct number of arguments.
	if( command_vec.size() != 1 && command_vec[0] != "day" && command_vec[0] != "time" )
	{
		std::cout << "Incorrect input: should be: detail add [time|day]\n\n";
		return( ret );
	}

	Detail det; // automatically initialized to times of 99.

	// get the event
	getUserEvent( &det );

	if( command_vec[0] == "time" ) // try to get the time from the user.
	{
		if( !getUserTime( &det ) )
		{
			std::cout << "No detail added, did not get a time.\n\n";
			return( ret );
		}
	}

	// get the number of times the event should occur.
	int recurrence;
	if( ! getRecurrence( &recurrence, &repeatMonthly, &repeatBiWeekly, &repeatWeekly) )
	{
		std::cout << "No detail added, did not get a valid recurrence.\n\n";
		return( ret );
	}

	std::unordered_map< int, bool> repeatWeekDay = {
		{ 0, false }, { 1, false }, { 2, false }, { 3, false }, { 4, false }, { 5, false }, { 6, false }
	};

	Node * date = calendar->getNode(currentDate[0], currentDate[1], currentDate[2]);

	if( recurrence > 1   &&   !setRepeatDays( &addToday, &repeatMonthly, &repeatBiWeekly, &repeatWeekly, &repeatWeekDay, recurrence, date ) )
	{
		std::cout << "Don't know how to recur. Did not add any events.\n\n";
		return( ret );
	}

	addEvents( det, recurrence, date, addToday, repeatMonthly, repeatBiWeekly, repeatWeekly, &repeatWeekDay );

	std::cout << "detail was: " << det.getText() << "\n";
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
