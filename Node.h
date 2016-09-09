/**
*       @file Node.h
*       @author Brad Gibbons
*       @date 2016.09.09
*       Purpose: To hold the details of a specific day of the year
*/

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

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
    /**
    *   @pre none
    *   @post Sets the vector of details for that Node
    *   @return none
    */
    void setDetails(std::vector<std::string> details);
    /**
    *   @pre none
    *   @post Pushes a details onto the vector of details in the Node
    *   @return none
    */
    void addDetail(std::string detail);
    /**
    *   @pre A vector of details for the Node
    *   @post none
    *   @return A vector of strings that are the details for that Node
    */
    std::vector<std::string> getDetails() const;
    /**
    *  @pre none
    *  @post Set the pointer to the next Node
    *  @return none
    */
    void setNext(Node* next);
    /**
    *  @pre A Node after the current Node
    *  @post none
    *  @return The next Node
    */
    Node* getNext() const;
    /**
    *  @pre none
    *  @post Set the pointer to the previous Node
    *  @return none
    */
    void setPrev(Node* prev);
    /**
    *  @pre A Node before the current Node
    *  @post none
    *  @return The previous Node
    */
    Node* getPrev() const;
private:
    int m_year; //Year of the Node
    int m_month; //Month of the Node
    int m_day; //Day of the Node
    std::vector<std::string> m_details; //Vector of details for the Node
    Node* m_next; //Pointer to the next Node
    Node* m_prev; //Pointer to the previous Node
};

#endif
