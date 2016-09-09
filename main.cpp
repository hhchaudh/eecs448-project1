/**
*	@file : main.cpp
*	@author: Brad Gibbons
*	@date: 2016.09.09
*	Purpose: Implementation of the program
*/

#include <string>
#include <iostream>
#include "Node.h"

int main() {
	Node* test = new Node();
	test->setYear(2016);
	std::cout << test->getYear() << std::endl;
	delete test;
	return(0);
}