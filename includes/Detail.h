/**
 * Purpose: To hold info on a specific detal.
 */

#ifndef DETAIL_H
#define DETAIL_H

#include <string>

/**
 * Detail class to hold info on a detail. 
 * @author Jacob Fustos
 * @version 1.0, 11 Oct 2016
 */
class Detail {
public:
	/**
	 * Constructor for a Detail object.
	 */
    Detail();
	/**
	 * Sets the hour the event will start.
	 * @param StartHour The hour the event will start.
	 */
    void setStartHours( int StartHour );
	/**
	 * Gets the hour the event will start.
	 * @return The hour the event will start.
	 */
    int  getStartHours() const;
	/**
	 * Sets the minutes the event will start.
	 * @param StartMinute The minutes the event will start.
	 */
    void setStartMinutes( int StartMinute );
	/**
	 * Gets the Minutes the event will start.
	 * @return The minutes the event will start.
	 */
    int  getStartMinutes() const;
	/**
	 * Sets the hour the event will end.
	 * @param DoneHour The hour the event will end.
	 */
    void setDoneHours( int DoneHour );
	/**
	 * Gets the hour the event will end.
	 * @return The hour the event will end.
	 */
    int  getDoneHours() const;
	/**
	 * Sets the minutes the event will end.
	 * @param DoneMinute The minutes the event will end.
	 */
    void setDoneMinutes( int DoneMinute );
	/**
	 * Gets the minutes the event will end.
	 * @return The minutes the event will end.
	 */
    int  getDoneMinutes() const;
	/**
	 * Sets if the event overlaps with another event..
	 * @param doubleBooked true if event is overlapping, false otherwise.
	 */
    void setDoubleBooked( bool doubleBooked );
	/**
	 * Gets if the detail overlaps another detail.
	 * @return true if does overlap, false otherwise.
	 */
    bool  getDoubleBooked() const;
	/**
	 * Sets the text describing the event.
	 * @param text The text describing the event.
	 */
    void setText( std::string text );
	/**
	 * Gets the text describing the event.
	 * @return The text describing the event.
	 */
    std::string getText() const;
	/**
	 * Compare a to b. 
	 * @param a An event to compare.
	 * @param b The other event to compare.
	 * @return True if a should come before b, else false.
	 */
	static bool compare( Detail a, Detail b );
private:
    int m_StartHours;	// The hours the event starts.
    int m_StartMinutes;	// The minutes the event starts at.
    int m_DoneHours;	// The hours the event ends at.
    int m_DoneMinutes;	// The minutes the event ends at.
	bool d_booked;		// If the event overlaps another event.
    std::string m_text; // The text descibing the event.
};

#endif
