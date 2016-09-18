 #include "ReadWrite.h"

 ReadWrite::ReadWrite(){
 	if(!(isFile())){
		std::ifstream info("user.txt");
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
 	if(info.is_open()){
 		return true;
 	}
 	else
 		return false;
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
 	std::ifstream inf; //create infile stream
 	std::string str;
 	//temp ints for date
 	int t_year = 0;
 	int t_month = 0;
 	int t_day = 0;
 	std::string det; //temp string for details
 	std::string curdate;
 	inf.open("user.txt"); //read in from existing user.txt
 	getline(inf,str); //read in current date
 	curdate = str;
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
 	while(getline(inf,str)){ //read in, line by line, existing file
 		//populate dll with info
 		t_year = atoi((str.substr(0,4)).c_str());
 		t_month = atoi((str.substr(4,2)).c_str());
 		t_day = atoi((str.substr(6,2)).c_str());
 		det = str.substr(8); //create string with the rest of the line
 		//use parts of date and det to fill dll
 		temp = dll->getNode(t_year,t_month,t_day);
 		temp->addDetail(det);
 	}
 	inf.close();
 }

 void ReadWrite::storeFileInfo(DoubleLinkedList* dll){
 	Node* temp = nullptr;
 	std::vector<std::string> tempvec;
 	char y_char[4];
 	char m_char[2];
 	char d_char[2];
 	itoa(m_curdate[0],y_char,10);
 	itoa(m_curdate[1],m_char,10);
 	itoa(m_curdate[2],d_char,10);
 	int y_int;
 	int m_int;
 	int d_int;
 	std::string y_str(y_char);
 	std::string m_str(m_char);
 	std::string d_str(d_char);
 	std::ofstream of; //open out file stream
 	of.open("user.txt", std::ofstream::out | std::ofstream::trunc);
 	of << y_str + m_str + d_str + "\n";
 	for(int i=0; i<dll->size(); i++){
 		temp = dll->getFront();
 		tempvec = temp->getDetails();
 		if(tempvec.size() != 0){
 			for(int j=0; j<tempvec.size(); j++){
 				y_int = temp->getYear();
 				m_int = temp->getMonth();
 				d_int = temp->getDay();
 				itoa(y_int,y_char,10);
 				itoa(m_int,m_char,10);
 				itoa(d_int,d_char,10);
 				y_str = std::string(y_char);
 				m_str = std::string(m_char);
 				d_str = std::string(d_char);
 				of << y_str + m_str + d_str + tempvec[j] + "\n";
 			}
 		}
 		temp = temp->getNext();
 	}
 	of.close();
 }