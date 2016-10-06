#ifndef COMMAND_H
#define COMMAND_H

namespace CMD_HELP
{
	extern commandfunc func;
}

namespace CMD_VIEW
{
	extern commandfunc func;
}

namespace UTIL
{
	extern int month_to_year[ 13 ];
	extern std::unordered_map<std::string, int> mon_to_int;
	
	extern int getDayofweek(int y, int m, int d);
	extern int getDayofweek( Node * day );
	extern void printCalHead();
	extern void printWeekHead();
	extern int getMonNum( std::string monthName );
	extern std::string getMonth( int m );
	extern Node * printWeek( Node * day, bool monthWrap, std::vector<int> currentDate );
	extern void printDay( Node * day );
}

#endif
