
 #include "ReadWrite.h"

 ReadWrite::ReadWrite(){
 	if(!(isFile())){
		std::ofstream of("user.txt");
		of << "20160801";
 	}
 	m_curdate.resize(3);
 	m_curdate[0] = 2016;
 	m_curdate[1] = 8;
 	m_curdate[2] = 1;
 }

 ReadWrite::~ReadWrite(){

 }

 bool ReadWrite::isFile() const {
 	std::ifstream info("user.txt");
 	return info.good();
 }

 std::vector<int> ReadWrite::getDate(){
 	return m_curdate;
 }

 void ReadWrite::setDate(std::vector<int> curdate){
 	m_curdate[0] = curdate[0];
 	m_curdate[1] = curdate[1];
 	m_curdate[2] = curdate[2];
 }

 void ReadWrite::getFileInfo(DoubleLinkedList* dll){
 	Node* temp = nullptr;
 	std::string str = "";
 	//temp ints for date
 	int t_year = 0;
 	int t_month = 0;
 	int t_day = 0;
 	std::string det = ""; //temp string for details
 	std::string curdate = ""; //temp string for current date
 	std::ifstream inf; //create infile stream
 	inf.open("user.txt"); //read in from existing user.txt
 	if(inf.is_open()){
 		getline(inf,curdate); //read in first line, current date
 		if(curdate.size() == 8){
 			//lengthy type conversion process
 			std::string curYstr = curdate.substr(0,4);
 			const char* curYchar = curYstr.c_str();
 			std::string curMstr = curdate.substr(4,2);
 			const char* curMchar = curMstr.c_str();
 			std::string curDstr = curdate.substr(6,2);
 			const char* curDchar = curDstr.c_str();
 			m_curdate[0] = atoi(curYchar); //parse year
 			m_curdate[1] = atoi(curMchar); //parse month
 			m_curdate[2] = atoi(curDchar); //parse day
 			while(!(inf.eof())){ //read in, line by line, existing file
				Detail myDet;
 				getline(inf,str);
 				//populate dll with info
 				t_year = atoi((str.substr(0,4)).c_str());
 				t_month = atoi((str.substr(4,2)).c_str());
 				t_day = atoi((str.substr(6,2)).c_str());
				myDet.setHours  (   atoi((str.substr(8,2)).c_str())   );
				myDet.setMinutes(   atoi((str.substr(10,2)).c_str())   );
				myDet.setText   (   str.substr(12)   );
				
 				//use parts of date and det to fill dll
 				temp = dll->getNode(t_year,t_month,t_day);
 				temp->addDetail( myDet );
 			}
 		}
 		else
		{
 			std::cout<<"Error: user.txt not formatted correctly";
		}
 	}
	else
	{
		std::cout<<"Error: Could not open user.txt for reading.";
	}
	
 	inf.close();
 }

 void ReadWrite::storeFileInfo(DoubleLinkedList* dll){
	// convert the current date to a string.
	char buffer[13];
	sprintf( buffer,     "%04d", m_curdate[0]);
	sprintf( buffer + 4, "%02d", m_curdate[1]);
	sprintf( buffer + 6, "%02d", m_curdate[2]);
	std::string curDay( buffer );
	
 	std::ofstream of; 
 	//delete contents of text file
 	//----------------------------
 	of.open("user.txt", std::ofstream::out | std::ofstream::trunc); 
 	of.close();
 	//----------------------------
 	of.open("user.txt"); //open text file to store new info
	
	// write out the current date.
 	of << curDay; //new current date
	
	for(	Node * curNode = dll->getFront(); 
			curNode != nullptr; 
			curNode = curNode->getNext()	)
	{
		std::vector<Detail> curVec = curNode->getDetails();
		while ( curVec.size() != 0 )
		{
			auto start = curVec.begin();
			sprintf( buffer,      "%04d",  curNode->getYear()     );
			sprintf( buffer + 4,  "%02d",  curNode->getMonth()    );
			sprintf( buffer + 6,  "%02d",  curNode->getDay()      );
			sprintf( buffer + 8,  "%02d",  start->getHours()        );
			sprintf( buffer + 10, "%02d",  start->getMinutes()      );
			
			std::string codedDate( buffer );
			
			of << "\n" + codedDate + start->getText();
			curVec.erase( start );
		}	
 	}
	
 	of.close();
}
