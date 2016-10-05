#ifndef DETAIL_H
#define DETAIL_H

#include <string>

class Detail {
public:
    Detail();
    void setHours( int hour );
    int getHours() const;
    void setMinutes( int minute );
    int getMinutes() const;
    void setText( std::string text );
    std::string getText() const;
	static bool compare( Detail a, Detail b );
private:
    int m_hour;
    int m_minute;
    std::string m_text;
};

#endif
