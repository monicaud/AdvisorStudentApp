#include "FileIO.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>

using namespace std;


//constructor that calles all four function to read from the data files
FileIO::FileIO() {
	file_is_open = true;
	ReadAdvisorData();
	ReadStudentData();
	ReadNotes();
	ReadAdvisees();
	WriteDataBack();
	
}

void FileIO::ReadAdvisorData() {
	int size = 0;

	

	string name = "C:\\3331\\Project2\\Data_advisors.txt";
	ifstream read_file(name);
	
	if (read_file.fail()) {
		file_is_open = false;
		return;
	}
	//reading the file
	//read_file.open(name);
	
	if (read_file) {
		string line;
		stringstream ss;
		while (getline(read_file, line)) {

			//read each line into a vector of characters
			vector <char> ar(line.begin(), line.end());

			//go through the vector 
			for (char x : ar) {
				//data is separated by commas
				if (x != ',') { 
					ss << x;
				}
				else {
					AdvisorData.push_back(ss.str());
					ss.clear();
					ss.str("");
				}
			}
			AdvisorData.push_back(ss.str());
			ss.clear();
			//emptying to add new line of data
			ss.str("");
			AdvisorData.push_back("\n");
		}
	}
	else {
		//cout << "Unable to open file: " << name << endl;
		file_is_open = false;

	}
	//printing the data if needed
	/*
	for (string y : AdvisorData) {
		if (y == "\n") {
			cout << endl;
		}
		else {
			cout << y << " ";

		}
	}
	*/
	read_file.close();
}

void FileIO::ReadStudentData() {

	string name = "C:\\3331\\Project2\\Data_students.txt";

	ifstream read_file(name);

	if (read_file.fail()) {
		file_is_open = false;
		return;
	}
	//reading the file
	//read_file.open(name);
	
	if (read_file) {
		string line;
		stringstream ss;
		while (getline(read_file, line)) {
			if(line.empty()){
				file_is_open = false;
				return;
			}
			vector <char> ar(line.begin(), line.end());

			for (char x : ar) {

				if (x != ',') {
					ss << x;
				}
				else {
					StudentData.push_back(ss.str());
					ss.clear();
					ss.str("");
				}

			}
			StudentData.push_back(ss.str());
			ss.clear();
			ss.str("");
			StudentData.push_back("\n");

		}

	}
	else {
		file_is_open = false;
	}

	//printing the data if needed
	/*
	for (string y : StudentData) {
		if (y == "\n") {
			cout << endl;
		}
		else {
			cout << y << " ";

		}
	}
	*/
	read_file.close();
}

void FileIO::ReadNotes() {

	string name = "C:\\3331\\Project2\\Data_advisingNotes.txt";

	ifstream read_file(name);

	if (read_file.fail()) {
		file_is_open = false;
		return;
	}

	
	if (read_file) {
		string line;
		stringstream ss;
		int count = 1; //count is the number of lines 
		while (getline(read_file, line)) {
			if (line.empty()) {
				file_is_open = false;
				return;
			}
			ss.str(line);
			string word;
			for (int i = (1 * count); i < (3 + (1 * count)); i++) {
				word = "";
				ss >> word;
				if (i == count) {
					//Erases the "(" from the first element
					word.erase(0, 1);
					Notes.push_back(word); //pushes back advisor ID

				}
				else if (i == (3 + count) - 2) { //reading the date
					int size = word.size();
					word.erase(size - 1, 1); //Erases the ")"
					Notes.push_back(word);

				}
				else {
					Notes.push_back(word); //pushes the student ID
				}
			}
			word = "";
			stringstream nn;
			while (ss >> word) { //putting the actual note into the string stream
				nn << word << " ";
			}
			Notes.push_back(nn.str()); //push back the note into the vector
			Notes.push_back("\n");
			ss.clear();
			ss.str("");
			count++;
		}
	}
	else {
		file_is_open = false;
		//cout << "couldn't open file" << endl;

	}

	//printing data if needed
	/*
	for (int i = 0; i < Notes.size(); i++) {
		cout << "Advisor ID: " << Notes[i] << endl;
		i++;
		cout << "Date: " << Notes[i] << endl;
		i++;
		cout << "Student ID: " << Notes[i] << endl;
		i++;
		cout << "Notes: " << Notes[i] << endl;
		i++;
		cout << Notes[i];
	}
	*/

	read_file.close();
}

void FileIO::ReadAdvisees() {

	vector<string> AdviseesVector;  // temp vector of IDs

	string name = "C:\\3331\\Project2\\Data_advisees.txt";
	ifstream read_file(name);
	if (read_file.fail()) {
		file_is_open = false;
		return;
	}

	//reading the file
	//read_file.open(name);
	
	if (read_file) {
		string line;
		stringstream ss;
		while (getline(read_file, line)) {
			if (line.empty()) {
				file_is_open = false;
				return;
			}
			vector <char> ar(line.begin(), line.end());

			for (char x : ar) {
				if (x != ',') {
					ss << x;
				}
				else {
					AdviseesVector.push_back(ss.str());
					ss.clear();
					ss.str("");

				}



			}
			AdviseesVector.push_back(ss.str());
			ss.clear();
			ss.str("");
			AdviseesVector.push_back("\n");


		}

	}
	else {
		file_is_open = false;
		//cout << "couldn't open file" << endl;

	}

	int size1 = 0;
	for (auto student : AdviseesVector) {
		size1++;
	}

	//reading the Advisors IDs to use later in creating the full map
	vector <string> ID;
	for (int i = 0; i < size1; i++) {
		if (i == 0) {
			ID.push_back(AdviseesVector[i]);
		}
		else {
			if (AdviseesVector[i] == "\n") {
				if ((i + 1) < size1) {
					ID.push_back(AdviseesVector[i + 1]);
				}

			}
		}
	}

	int size2 = 0; // number of advisors with advisees
	for (auto student : ID) {
		size2++;
	}
	//putting data into the map
	for (int s = 0; s < size2; s++) { //'s' goes thru advisors who have advisees
		for (int i = 0; i < size1; i++) {
			if (i == 0) {
				//Advisees1[ID[s]];
				while (AdviseesVector[i] != "\n") {
					Advisees[ID[s]].push_back(AdviseesVector[i + 1]);
					i++;

				}
			}
			else if (AdviseesVector[i] == "\n") {
				i++;
				s++;
				//Advisees1[ID[s]];
				if (i < size1) {
					while (AdviseesVector[i] != "\n") {
						if ((i + 1) < size1) {
							Advisees[ID[s]].push_back(AdviseesVector[i + 1]);
							i++;
						}
					}
				}
			}
			if (i < size1) {
				if (AdviseesVector[i] == "\n") {
					i--;
				}
			}
		}
	}


	//printing the map if needed

	/*
	for (auto iter = Advisees.begin(); iter != Advisees.end();iter++) {
		cout << iter->first<< ": ";
		for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++) {
			if (iter2 == iter->second.end()) {
				cout << *iter2;
			}
			else {
				cout << *iter2 << " ";
			}
		}
		cout << endl;
	}
	*/
	read_file.close();
}

void FileIO::WriteDataBack() {
	ofstream write_file_advisor;

	//write advisor data back into file
	//...
	//...
	//...
	string name_advisor = "C:\\3331\\Project2\\Data_advisors.txt";

	write_file_advisor.open(name_advisor);


	if (write_file_advisor) {
		int count1 = 0;
		for (auto s : AdvisorData) {
			count1++;
		}

		for (int i = 0; i < count1; i++) {
			if (AdvisorData[i] == "\n") {
				write_file_advisor << AdvisorData[i];
			}
			else {
				write_file_advisor << AdvisorData[i];
				if (AdvisorData[i + 1] != "\n") {
					write_file_advisor << ",";
				}
			}
		}
	}
	else {
		cout << "File did not work!" << endl;
	}
	write_file_advisor.close();
	//write student data back into file
	//...
	//...
	//...
	ofstream write_file_student;

	string name_student = "C:\\3331\\Project2\\Data_students.txt";

	write_file_student.open(name_student);

	if (write_file_student) {
		int count2 = 0;
		for (auto s : StudentData) {
			count2++;
		}

		for (int i = 0; i < count2; i++) {
			if (StudentData[i] == "\n") {
				write_file_student << StudentData[i];
			}
			else {
				write_file_student << StudentData[i];
				if (StudentData[i + 1] != "\n") {
					write_file_student << ",";
				}
			}
		}
	}
	else {
		cout << "File did not work!" << endl;
	}
	write_file_student.close();
	//write notes back into file
	//...
	//...
	//...

	ofstream write_file_notes;


	string name_notes = "C:\\3331\\Project2\\Data_advisingNotes.txt";

	write_file_notes.open(name_notes);

	if (write_file_notes) {
		int count3 = 0; // size of notes vector
		for (auto s : Notes) {
			count3++;
		}

		for (int i = 0; i < count3; i++) {

			write_file_notes << "(" << Notes[i] << " ";
			i++;
			write_file_notes << Notes[i] << ") ";
			i++;
			write_file_notes << Notes[i] << " ";
			i++;
			write_file_notes << Notes[i];
			i++;
			write_file_notes << Notes[i];

		}
	}
	else {
		cout << "File did not work!" << endl;
	}
	write_file_notes.close();
	//write advisees data back into file
	//...
	//...
	//...

	ofstream write_file_advisees;

	string name_advisees = "C:\\3331\\Project2\\Data_advisees.txt";

	write_file_advisees.open(name_advisees);

	if (write_file_advisees) {

		for (auto iter = Advisees.begin(); iter != Advisees.end(); iter++) { //going elements of map
			write_file_advisees << iter->first;
			for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++) { //going thru the elements of the vectors within map
				if (iter2 == iter->second.end()) {
					write_file_advisees << *iter2;
				}
				else {
					if (*iter2 != "\n") {
						write_file_advisees << "," << *iter2;
					}
					else {
						write_file_advisees << *iter2;
					}
				}
			}
		}
	}
	else {
		cout << "could not open file!." << endl;
	}
	write_file_advisees.close();
}