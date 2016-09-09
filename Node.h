/**
*       @file Node.h
*       @author Brad Gibbons
*       @date 2016.09.09
*       Purpose: To hold the details of a specific day of the year
*/

#ifndef NODE_H
#define NODE_H

class Node {
public:
    /**
    *   @pre none
    *   @post Creates and initializes a Node instance
    *   @return none
    */
    Node();
    /**
    *   @pre none
    *   @post Sets the year of the Node
    *   @return none
    */
    void setYear(int year);
    /**
    *   @pre A stored year in the Node
    *   @post none
    *   @return The value of the year of the Node
    */
    int getYear() const;
    /**
    *   @pre none
    *   @post Sets the month of the Node
    *   @return none
    */
    void setMonth(int month);
    /**
    *   @pre A stored month in the Node
    *   @post none
    *   @return The value of the month of the Node
    */
    int getMonth() const;
    /**
    *   @pre none
    *   @post Sets the day of the Node
    *   @return none
    */
    void setDay(int year);
    /**
    *   @pre A stored day in the Node
    *   @post none
    *   @return The value of the day of the Node
    */
    int getDay() const;
private:
    int m_year; //Year of the Node
    int m_month; //Mont of the Node
    int m_day; //Day of the Node
};

#endif
