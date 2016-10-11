#ifndef CALENDAR_STD_H
#define CALENDAR_STD_H

// standard includes for the project.
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "ReadWrite.h"
#include "DoubleLinkedList.h"
#include "Node.h"
#include "Detail.h"

typedef std::vector<int> commandfunc(std::vector<std::string> command_vec, DoubleLinkedList* calendar, std::vector<int> currentDate);

#endif
