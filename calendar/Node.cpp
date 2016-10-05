#include "Node.h"

Node::Node() {
	m_year = 0;
	m_month = 0;
	m_day = 0;
	m_details = std::vector<Detail>();
	m_next = nullptr;
	m_prev = nullptr;
}

void Node::setYear(int year) {
	m_year = year;
}

int Node::getYear() const {
	return(m_year);
}

void Node::setMonth(int month) {
	m_month = month;
}

int Node::getMonth() const {
	return(m_month);
}

void Node::setDay(int day) {
	m_day = day;
}

int Node::getDay() const {
	return(m_day);
}

void Node::setDetails(std::vector<Detail> details) {
	m_details = details;
}

void Node::addDetail(Detail detail) {
	
	if( m_details.empty() )
	{
		m_details.push_back( detail );
		return;
	}
	
	auto current = m_details.begin();
	auto done = m_details.end();
	while ( current != done)
	{
		if( Detail::compare( detail, *current ) )
		{
			m_details.insert( current, detail );
			return;
		}
		
		current++;
	}
	
	m_details.push_back( detail );
}

std::vector<Detail> Node::getDetails() const {
	return(m_details);
}

void Node::removeDetail(int index) {
	m_details.erase(m_details.begin() + index);
}

void Node::setNext(Node* next) {
	m_next = next;
}

Node* Node::getNext() const {
	return(m_next);
}

void Node::setPrev(Node* prev) {
	m_prev = prev;
}

Node* Node::getPrev() const {
	return(m_prev);
}
