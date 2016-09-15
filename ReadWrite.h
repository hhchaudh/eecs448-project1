/*	
	@file ReadWrite.h
	@author Jackson Schilmoeller
	@date Created: 9/8/2016
	@brief Generates file, user.txt, to keep user calendar data, and retrieve information from previous sessions
*/

	#ifndef READ_WRITE_H
	#define READ_WRITE_H

	#include <iostream>
	#include <vector>

	class ReadWrite
	{
	public:
		ReadWrite();
		~ReadWrite();
		bool isFile() const;
		int fileSize() const;
		int* getCalInfo();
		std::vector<string> getCalDetails();
		void storeFileInfo();
	private:
		std::vector<string> rw_v;
	};

	#endif