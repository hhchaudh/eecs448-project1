/**	
 *	@file ReadWrite.cpp
 *	@author Jackson Schilmoeller
 *	@date Created: 9/15/2016
 *	@brief Generates file, user.txt, to keep user calendar data, and retrieve information from previous sessions
 **/

 #include "ReadWrite.h"

 ReadWrite::ReadWrite(){
 	if(!(isFile())){
		std::ofstream info("user.txt");
 	}
 	m_curdate = 0;
 }

 ReadWrite::~ReadWrite(){

 }

 bool ReadWrite::isFile(){
 	if(std::ifstream info("user.txt"))
 		return true;
 }

 int ReadWrite::getDate(){
 	return m_curdate;
 }

 void ReadWrite::setDate(int curdate){
 	m_curdate = curdate;
 }

 void ReadWrite::getFileInfo(DoubleLinkedList* dll){
 	
 }

 void ReadWrite::storeFileInfo(DoubleLinkedList* dll){

 }