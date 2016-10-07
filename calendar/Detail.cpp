#include "Detail.h"

Detail::Detail() {
	m_StartHours = 99;
	m_StartMinutes = 99;
	m_DoneHours = 99;
	m_DoneMinutes = 99;
	d_booked = false;
	m_text = "";
}

void Detail::setStartHours( int startHours ) {
	m_StartHours = startHours;
}

int Detail::getStartHours() const {
	return( m_StartHours );
}

void Detail::setStartMinutes( int startMinutes ) {
	m_StartMinutes = startMinutes;
}

int Detail::getStartMinutes() const {
	return( m_StartMinutes );
}

void Detail::setDoneHours( int doneHours ) {
	m_DoneHours = doneHours;
}

int Detail::getDoneHours() const {
	return( m_DoneHours );
}

void Detail::setDoneMinutes( int doneMinutes ) {
	m_DoneMinutes = doneMinutes;
}

int Detail::getDoneMinutes() const {
	return( m_DoneMinutes );
}

void Detail::setDoubleBooked( bool doubleBooked ) {
	d_booked = doubleBooked;
}

bool Detail::getDoubleBooked() const {
	return( d_booked );
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
	if( b.m_StartHours == 99 )
	{
		return false;
	}
	
	if( a.m_StartHours == 99 )
	{
		return true;
	}
	
	// neither is 99, so just lower hour wins.
	if( a.m_StartHours < b.m_StartHours )
	{
		return true;
	}
	
	if( a.m_StartHours == b.m_StartHours)
	{
		// hour is the same so lower minutes wins.
		if( a.m_StartMinutes < b.m_StartMinutes )
		{
			return true;
		}
	}
	
	// a wanted to win but b must be lower.
	// If they are equal b wins to prevent shuffling between uses.
	return false;
}
