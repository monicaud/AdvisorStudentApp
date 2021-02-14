#pragma once
#include "User.h"
#include <map>
class FileIO {

public:

	FileIO();
	//the key is the advisor ID and the vector of strings is the IDs of student advisees
	map <string, vector<string> > Advisees;
	vector <string> AdvisorData;
	vector <string> StudentData;
	vector <string> Notes;
	bool file_is_open;

	void ReadAdvisorData();
	void ReadStudentData();
	void ReadNotes();
	void ReadAdvisees();
	void WriteDataBack();

};