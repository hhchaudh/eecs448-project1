#include "Detail.h"

Detail::Detail() {
	m_hour = 0;
	m_minute = 0;
	m_text = "";
}

void Detail::setHours( int hour ) {
	m_hour = hour;
}

int Detail::getHours() const {
	return( m_minute );
}

void Detail::setMinutes( int minute ) {
	m_minute = minute;
}

int Detail::getMinutes() const {
	return( m_minute );
}

void Detail::setText( std::string text ) {
	m_text = text;
}

std::string Detail::getText() const {
	return( m_text );
}

bool Detail::compare( Detail a, Detail b )
{
	// The 99's should get displayed first, so make them the smallest.
	if( b.m_hour == 99 )
	{
		return false;
	}
	
	if( a.m_hour == 99 )
	{
		return true;
	}
	
	// neither is 99, so just lower hour wins.
	if( a.m_hour < b.m_hour )
	{
		return true;
	}
	
	if( a.m_hour == b.m_hour)
	{
		// hour is the same so lower minutes wins.
		if( a.m_minute < b.m_minute )
		{
			return true;
		}
	}
	
	// a wanted to win but b must be lower.
	// If they are equal b wins to prevent shuffling between uses.
	return false;
}
