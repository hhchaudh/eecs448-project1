 #include "ReadWrite.h"

 ReadWrite::ReadWrite(){
 	if(!(isFile())){
		std::ifstream info("user.txt");
 	}
 	m_curdate = {2016,8,1};
 }

 bool ReadWrite::isFile() const {
 	if(std::ifstream info("user.txt")){
 		return true;
 	}
 }

 int* ReadWrite::getDate(){
 	return m_curdate;
 }

 void ReadWrite::setDate(int curdate[]){
 	m_curdate = curdate;
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
 	char* t_char = itoa(m_curdate);
 	char* y_char;
 	char* m_char;
 	char* d_char;
 	std::string str;
 	str = string(t_char);
 	std::ofstream of; //open out file stream
 	of.open("user.txt", std::ofstream::out | std::ofstream::trunc);
 	of << str + "\n";
 	for(int i=0; i<dll->size(); i++){
 		temp = dll->getFront();
 		tempvec = temp->getDetails();
 		if(tempvec.size() != 0){
 			for(int j=0; j<tempvec.size(); j++){
 				y_char = temp->getYear();
 				m_char = temp->getMonth();
 				d_char = temp->getDay();
 				str = string(itoa(y_char)) + string(itoa(m_char)) + string(itoa(d_char)) + tempvec[j];
 				of << str + "\n";
 			}
 		}
 		temp = temp->getNext();
 	}
 	of.close();
 }