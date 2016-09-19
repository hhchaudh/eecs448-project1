#include "DoubleLinkedList.h"

DoubleLinkedList::DoubleLinkedList() {
	m_front = nullptr;
	m_back = nullptr;
	m_size = 0;
}

DoubleLinkedList::DoubleLinkedList(int startYear, int startMonth, int endYear, int endMonth) {
	m_front = nullptr;
	m_back = nullptr;
	m_size = 0;
	for (int year=startYear; year<=endYear; year++) { //Cycle through the years
		int l_startMonth = 1; //Starting month for the loop
		int l_endMonth = 12; //Ending month for the loop

		//Check when the month cycle should end and begin
		if (year == startYear) { l_startMonth = startMonth; }
		if (year == endYear) { l_endMonth = endMonth; }

		for (int month=l_startMonth; month <= l_endMonth; month++) { //Cycle through the months
			for (int day=1; day<=numDays(year,month); day++) { //Cycle through the days
				pushBack(year,month,day);
			}
		}
	}
}

DoubleLinkedList::~DoubleLinkedList() {
	while (m_size > 0) {
		removeFront();
	}
}

int DoubleLinkedList::size() const {
	return(m_size);
}

void DoubleLinkedList::pushFront(int year, int month, int day) {
	if (m_size == 0) { //If no Nodes have been added
		Node* temp = new Node();
		//Set values for the new Node
		temp->setYear(year);
		temp->setMonth(month);
		temp->setDay(day);
		//Point m_front and m_back
		m_front = temp;
		m_back = m_front;
	} else { //If one or more Nodes have been added already
		Node* temp = new Node();
		//Set values for the new Node
		temp->setYear(year);
		temp->setMonth(month);
		temp->setDay(day);
		//Point the new Node and previous m_front to each other
		temp->setNext(m_front);
		m_front->setPrev(temp);
		//Set m_front as the new Node
		m_front = temp;
	}
	m_size++; //Increment size
}

void DoubleLinkedList::removeFront() {
	if (m_size == 1) { //If only one Node in the DoubleLinkedList
		delete m_front;
		m_front = nullptr;
		m_back = nullptr;
	} else { //If there is more than one Node
		Node* temp = m_front->getNext(); //Get the second Node in the list
		temp->setPrev(nullptr); //Point that Node to nullptr
		delete m_front; //Delete the front Node
		m_front = temp; //Point m_front to the second Node
	}
	m_size--; //Decriment size
}

void DoubleLinkedList::pushBack(int year, int month, int day) {
	if (m_size == 0) { //If no Nodes have been added
		Node* temp = new Node();
		//Set values for the new Node
		temp->setYear(year);
		temp->setMonth(month);
		temp->setDay(day);
		//Point m_front and m_back
		m_front = temp;
		m_back = m_front;
	} else { //If one or more Nodes have been added already
		Node* temp = new Node();
		//Set values for the new Node
		temp->setYear(year);
		temp->setMonth(month);
		temp->setDay(day);
		//Point the new Node and previous m_back to each other
		temp->setPrev(m_back);
		m_back->setNext(temp);
		//Set m_back as the new Node
		m_back = temp;
	}
	m_size++; //Increment size
}

void DoubleLinkedList::removeBack() {
	if (m_size == 1) { //If only one Node in the DoubleLinkedList
		delete m_front;
		m_front = nullptr;
		m_back = nullptr;
	} else { //If there is more than one Node
		Node* temp = m_back->getPrev(); //Get the second to last Node in the list
		temp->setNext(nullptr); //Point that Node to nullptr
		delete m_back; //Delete the back Node
		m_back = temp; //Point m_back to the second to last Node
	}
	m_size--; //Decriment size
}

Node* DoubleLinkedList::getFront() const {
	return(m_front);
}

Node* DoubleLinkedList::getBack() const {
	return(m_back);
}

Node* DoubleLinkedList::getNode(int year, int month, int day) const {
	bool isFound = false;
	Node* temp = m_front;
	while(temp != nullptr && !isFound) {
		if (temp->getYear() == year && temp->getMonth() == month && temp->getDay() == day) {
			isFound = true;
		} else {
			temp = temp->getNext();
		}
	}
	return(temp);
}

bool DoubleLinkedList::checkYear(int year) const {
	bool isFound = false;
	Node* temp = m_front;
	while (temp != nullptr && !isFound) {
		if (temp->getYear() == year) {
			isFound = true;
		} else {
			temp = temp->getNext();
		}
	}
	return(isFound);
}

bool DoubleLinkedList::checkMonth(int year, int month) const {
	bool isFound = false;
	Node* temp = m_front;
	while (temp != nullptr && !isFound) {
		if (temp->getYear() == year && temp->getMonth() == month) {
			isFound = true;
		} else {
			temp = temp->getNext();
		}
	}
	return(isFound);
}

bool DoubleLinkedList::checkDay(int year, int month, int day) const {
	bool isFound = false;
	Node* temp = m_front;
	while (temp != nullptr && !isFound) {
		if (temp->getYear() == year && temp->getMonth() == month && temp->getDay() == day) {
			isFound = true;
		} else {
			temp = temp->getNext();
		}
	}
	return(isFound);
}

int DoubleLinkedList::numDays(int year, int month) {
	int val = 0; //Used to add extra day to February for leap year
	int daysInMonths[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (month == 2) { //If not checking for February
		if (year % 400 == 0) {
			val = 1;
		} else if (year % 4 == 0 && year % 100 != 0) {
			val = 1;
		}
	}
	return(daysInMonths[month-1] + val);
}

