/**
 * Purpose: To hold the details of a specific day of the year.
 */

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

/**
 * Node object used to store a year, month, day, and details.
 * @author Brad Gibbons
 * @version 1.0, 15 Sep 2016
 */
class Node {
public:
    /**
     * Constructor for a Node object.
     */
    Node();
    /**
     * Sets the year stored in the node.
     * @param year 	The year to be stored in the node.
     */
    void setYear(int year);
    /**
     * Method to get the year currently stored in the node.
     * @return The year currently stored in the node.
     */
    int getYear() const;
    /**
     * Sets the month stored in the node.
     * @param month	The month to be stored in the node.
     */
    void setMonth(int month);
    /**
     * Method to get the month currently stored in the node.
     * @return The month currently stored in the node.
     */
    int getMonth() const;
    /**
     * Sets the day stored in the node.
	 * @param day 	The day to be stored in the node.
	 */
    void setDay(int day);
    /**
     * Method to get the day currently stored in the node.
     * @return The day currently stored in the node.
     */
    int getDay() const;
    /**
     * Sets the details stored in the node.
     * @param details 	A vector of strings that are the details.
     */
    void setDetails(std::vector<std::string> details);
    /**
     * Adds a details to the current list of details.
     * @param detail 	A string to be pushed onto the current details.
     */
    void addDetail(std::string detail);
    /**
     * Returns the vector of details stored in the node.
     * @return A vector of strings that are the details in the node.
     */
    std::vector<std::string> getDetails() const;
    /**
     * Removes the detail at the given index.
     * @param index     The index of the detail to be removed.
     */
    void removeDetail(int index);
    /**
     * A pointer to another node.
     * @param next 	The node to point the current node to.
     */
    void setNext(Node* next);
    /**
     * Returns a pointer to the next node.
     * @return The node the current node is pointing to.
     */
    Node* getNext() const;
    /**
     * A pointer to another node.
     * @param prev 	The node to point the current node to.
     */
    void setPrev(Node* prev);
    /**
     * Returns a pointer to the next node.
     * @return The node the current node is pointing to.
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
