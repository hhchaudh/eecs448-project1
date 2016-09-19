
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
 		inf >> curdate; //read in first line, current date
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
 			inf >> str;
 			while(!(inf.eof())){ //read in, line by line, existing file
 				//populate dll with info
 				t_year = atoi((str.substr(0,4)).c_str());
 				t_month = atoi((str.substr(4,2)).c_str());
 				t_day = atoi((str.substr(6,2)).c_str());
 				det = str.substr(8); //create string with the rest of the line
 				//use parts of date and det to fill dll
 				temp = dll->getNode(t_year,t_month,t_day);
 				temp->addDetail(det);
 				inf >> str;
 			}
 		}
 		else
 			std::cout<<"Error: user.txt not formatted correctly";
 	}
 	inf.close();
 }

 void ReadWrite::storeFileInfo(DoubleLinkedList* dll){
 	int sanity = 0;
 	Node* temp = nullptr;
 	std::vector<std::string> tempvec;
 	std::string tempdet = "";
 	char y_char[4];
 	char m_char[2];
 	char d_char[2];
 	itoa(m_curdate[0],y_char,10);
 	itoa(m_curdate[1],m_char,10);
 	itoa(m_curdate[2],d_char,10);
 	int y_int = 0;
 	int m_int = 0;
 	int d_int = 0;
 	std::string y_str(y_char);
 	std::string m_str(m_char);
 	//check for single digit month
 	if(m_curdate[1] == 1 || m_curdate[1] == 2 || m_curdate[1] == 3 || m_curdate[1] == 4 || m_curdate[1] == 5 
 		|| m_curdate[1] == 6 || m_curdate[1] == 7 || m_curdate[1] == 8 || m_curdate[1] == 9)
 	{
 		m_str = "0" + m_str;
 	}
 	std::string d_str(d_char);
 	//check for single digit day
 	if(m_curdate[2] == 1 || m_curdate[2] == 2 || m_curdate[2] == 3 || m_curdate[2] == 4 || m_curdate[2] == 5 
 		|| m_curdate[2] == 6 || m_curdate[2] == 7 || m_curdate[2] == 8 || m_curdate[2] == 9)
 	{
 		d_str = "0" + d_str;
 	}
 	std::ofstream of; 
 	//delete contents of text file
 	//----------------------------
 	of.open("user.txt", std::ofstream::out | std::ofstream::trunc); 
 	of.close();
 	//----------------------------
 	of.open("user.txt"); //open text file to store new info
 	of << y_str + m_str + d_str; //new current date
 	temp = dll->getFront(); //initialize node pointer
 	for(int i=0; i<dll->size(); i++){ //traverse dll
 		tempvec = temp->getDetails(); //get details for current day/node
 		if(tempvec.size() != 0){ //check if there are details
 			sanity = 0;
 			for(int j=0; j<tempvec.size(); j++){ //loop for number of details
 				if(j!=tempvec.size()){
 					//get date of current node
 					y_int = temp->getYear();
 					m_int = temp->getMonth();
 					d_int = temp->getDay();
 					//convert to char*
 					itoa(y_int,y_char,10);
 					itoa(m_int,m_char,10);
 					itoa(d_int,d_char,10);
 					//typecast to string
 					y_str = std::string(y_char);
 					m_str = std::string(m_char);
 					//check for single digit month
 					if(m_int == 1 || m_int == 2 || m_int == 3 || m_int == 4 || m_int == 5 
 						|| m_int == 6 || m_int == 7 || m_int == 8 || m_int == 9)
 					{
 						m_str = "0" + m_str;
 					}
 					d_str = std::string(d_char);
 					//check for single digit day
 					if(d_int == 1 || d_int == 2 || d_int == 3 || d_int == 4 || d_int == 5 
 						|| d_int == 6 || d_int == 7 || d_int == 8 || d_int == 9)
 					{
 						d_str = "0" + d_str;
 					}
 					//create new line in text file, concat ymd of node and then the string containing the detail
 					of << "\n" + y_str + m_str + d_str + tempvec[sanity];
 					sanity++;
 				}
 			}
 		}
 		if(temp->getNext()!=nullptr)
 			temp = temp->getNext(); //move to next node
 	}
 	of.close();
}