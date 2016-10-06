#ifndef DETAIL_H
#define DETAIL_H

#include <string>

class Detail {
public:
    Detail();
    void setStartHours( int StartHour );
    int  getStartHours() const;
    void setStartMinutes( int StartMinute );
    int  getStartMinutes() const;
    void setDoneHours( int DoneHour );
    int  getDoneHours() const;
    void setDoneMinutes( int DoneMinute );
    int  getDoneMinutes() const;
    void setDoubleBooked( bool doubleBooked );
    bool  getDoubleBooked() const;
    void setText( std::string text );
    std::string getText() const;
	static bool compare( Detail a, Detail b );
private:
    int m_StartHours;
    int m_StartMinutes;
    int m_DoneHours;
    int m_DoneMinutes;
	bool d_booked;
    std::string m_text;
};

#endif
