#include "Advisor.h"

Advisor::Advisor()
{
	id = " ";
	password = " ";
	roomNum = " ";
	teleNum = " ";
	advisees = {};
}


void Advisor::Display()//we should have the option to sort based on id, major, total hrs -MD
{
	vector <string> sorted_id = {};
	vector <int> sorted_hours = {};
	vector <string> trial_string = {};
	bool flag = true;

	int size = 0;
	for (auto student : advisees) {
		size++;
	}

	if (size == 0) {
		cout << "Sorry, you have no advisees to display." << endl;
	}else {
		cout << "Sort by:\n";
		cout << "Student ID (I) "<<endl<< "Major (M)" << endl 
			<< "Range of Completed Hours (H)" << endl << "Exit (E)" << endl << "Option: ";
		char option;
		Student temp_stu;
		trial_string.clear();

		while (flag)
		{
			cin >> option; //read what they want to sort by

			switch (option) {
			case 'i':
			case 'I': //they chose to sort by ID

				for (int i = 0; i < size; i++) {
					trial_string.push_back(advisees[i].get_id()); //populating the string vector with all the ids
				}
				sort(trial_string.begin(), trial_string.end());
				for (auto str = trial_string.begin(); str != trial_string.end(); str++) {
					for (auto advisee = advisees.begin(); advisee != advisees.end(); advisee++) {
						if (advisee->get_id() == *str) {
							advisee->viewStats();
						}
					}
				}

				flag = false;
				break;
			case 'm':
			case 'M': //sorting by major
				for (int i = 0; i < size; i++) {
					trial_string.push_back(advisees[i].get_major()); //populating the string vector with all the ids
				}
				sort(trial_string.begin(), trial_string.end());
				for (auto str = trial_string.begin(); str != trial_string.end(); str++) {
					for (auto advisee = advisees.begin(); advisee != advisees.end(); advisee++) {
						if (advisee->get_major() == *str) {
							advisee->viewStats();
						}
					}
				}


				flag = false;
				break;
			case 'h':
			case 'H': //sorting by total hours
				for (int i = 0; i < size; i++) {
					sorted_hours.push_back(advisees[i].get_totalHours()); //populating the string vector with all the hours
				}
				sort(sorted_hours.begin(), sorted_hours.end());
				for (auto str = sorted_hours.begin(); str != sorted_hours.end(); str++) {
					for (auto advisee = advisees.begin(); advisee != advisees.end(); advisee++) {
						if (advisee->get_totalHours() == *str) {
							advisee->viewStats();
						}
					}
				}

				flag = false;
				break;
			case 'e':
			case 'E':
				flag = false;
				break;
			default:
				cout << "Wrong option. Try again: ";
				break;
			}
		}

	}


}

void Advisor::Search()
{
	cout << "Search by:" << endl;
	cout << "Student ID (I)" << endl << "Major (M)" << endl << "Range of Completed Hours (H)" << endl << "Major and Range of Completed Hours (C)" << endl << "Option: ";
	char option;
	bool flag = true;

	string studentID;
	int minimum = 0;
	int maximum = 0;
	string major;
	vector <double> studentGPAs;
	double count = 0.0;
	double avgGPA = 0.0;
	bool check = false;

	
	auto sameMajor = [&](Student s) -> bool { //lambda expression
		if (s.get_major() == major)
			return true;
		return false;
	};


	while (flag) {
		cin >> option;
		switch (option) {
		case 'I':
		case 'i':
			check = false;
			cout << "Please enter student ID: ";
			cin >> studentID;

			for (auto s : advisees) { //looking through vector of advisees
				if (s.get_id() == studentID) {
					s.viewStats();
					check = true;
				}
			}
			if (check == false) {
				cout << "Could not find student." << endl;
			}
			flag = false;
			break;

		case 'M':
		case 'm':
			cout << "Please enter major: ";
			cin >> major;

			for (auto s : advisees) { //looking through vector of advisees
				if (s.get_major() == major) {
					studentGPAs.push_back(s.get_gpa());
					s.viewStats();
				}
			}

			count = count_if(advisees.begin(), advisees.end(), sameMajor); //STL Algorithm

			avgGPA = accumulate(studentGPAs.begin(), studentGPAs.end(), 0.0) / count; //STL Algorithm

			cout << "You have " << studentGPAs.size() << " students with the major " << major << ". The average GPA is "
				<< avgGPA << ". " << endl << endl;
			flag = false;
			break;
		case 'H':
		case 'h':
			cout << "Please enter minimum amount of hours: ";
			cin >> minimum;

			cout << "Please enter maximum amount of hours: ";
			cin >> maximum;
			check = false;
			for (auto s : advisees) { //looking through vector of advisees
				if ((s.get_totalHours() >= minimum) && (s.get_totalHours() <= maximum)) {
					s.viewStats();
					check = true;
				}
			}
			if (check == false) {
				cout << "Could not find students with desired total hours." << endl;
			}
			flag = false;
			break;
		case 'C':
		case 'c':
			cout << "Please enter major: ";
			cin >> major;

			cout << "Please enter minimum amount of hours: ";
			cin >> minimum;

			cout << "Please enter maximum amount of hours: ";
			cin >> maximum;
			check = false;
			for (auto s : advisees) { //looking through vector of advisees
				if ((s.get_totalHours() >= minimum) && (s.get_totalHours() <= maximum) && (s.get_major() == major)) {
					s.viewStats();
					check = true;
				}
			}
			if (check == false) {
				cout << "Could not find students with desired info." << endl;
			}
			flag = false;
			break;
		case 'e':
		case 'E':
			flag = false;
			break;
		default:
			cout << "Wrong option. Try again: ";
			break;

		}
	}
	
}

void Advisor::ViewNotes()
{
	FileIO file;
	string StudentNotesId;
	cout << "Please enter student ID: ";
	cin >> StudentNotesId;

	bool check = false;
	bool check2 = false;

	//checks if the student is found as an advisee for that advisor
	for (auto iter = file.Advisees.begin(); iter != file.Advisees.end(); iter++) {
		if (iter->first == id) {

			for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++) {
				if (*iter2 == StudentNotesId) {
					check = true;
				}
			}
		}
	}

	//if student found
	if (check == true) {
		int size = 0;
		for (auto x : file.Notes) {
			size++;
		}
		for (int i = 0; i < size; i++) {
			if (i + 3 < size) {
				if (StudentNotesId == file.Notes[i + 2]) {//checks were the student is located in the notes vector
					cout << "Date: " << file.Notes[i + 1] << endl;
					cout << file.Notes[i + 2] << " " << file.Notes[i + 3] << endl; //i+2 is student ID
					check2 = true;

				}
			}
		}
	}
	else {
		cout << "Could not find student in your advisees list.\n" << endl;
	}

	if(check2==false){
		cout << "Student does not have any notes." << endl;
	}

	file.WriteDataBack();

}


bool Advisor::AddNotes(string StudentID, FileIO &file) { //for advisor menu, advisor writes in what they want

	string date, note;
	char date_char[10];
	stringstream str;

	bool check = false;
	bool checkValid = true;

	//checks if the student is an advisee of that advisor
	for (auto iter = file.Advisees.begin(); iter != file.Advisees.end(); iter++) {
		if (iter->first == id) {

			for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++) {
				if (*iter2 == StudentID) {
					check = true;
				}
			}
		}
	}

	if (check == true) {

		if (__DATE__[0] == 'J') {
			if (__DATE__[1] == 'a') {
				//it's january
				date_char[0] = '0';
				date_char[1] = '1';
			}

			if (__DATE__[2] == 'n') {
				//it's june
				date_char[0] = '0';
				date_char[1] = '6';
			}
			if (__DATE__[2] == 'l') {
				//it's july
				date_char[0] = '0';
				date_char[1] = '7';
			}

		}
		if (__DATE__[0] == 'F') {
			//it's feb
			date_char[0] = '0';
			date_char[1] = '2';
		}
		if (__DATE__[0] == 'M') {
			if (__DATE__[2] == 'y') {
				//it's may
				date_char[0] = '0';
				date_char[1] = '5';
			}
			if (__DATE__[2] == 'r') {
				//it's mar
				date_char[0] = '0';
				date_char[1] = '3';
			}
		}
		if (__DATE__[0] == 'A') {
			if (__DATE__[1] == 'p') {
				//it's apr
				date_char[0] = '0';
				date_char[1] = '4';
			}
			if (__DATE__[1] == 'u') {
				//it's aug
				date_char[0] = '0';
				date_char[1] = '8';
			}
		}
		if (__DATE__[0] == 'S') {
			//it's sep
			date_char[0] = '0';
			date_char[1] = '9';
		}
		if (__DATE__[0] == 'O') {
			//it's oct
			date_char[0] = '1';
			date_char[1] = '0';
		}
		if (__DATE__[0] == 'N') {
			//it's nov
			date_char[0] = '1';
			date_char[1] = '1';
		}
		if (__DATE__[0] == 'D') {
			//it's dec
			date_char[0] = '1';
			date_char[1] = '2';
		}
		//-------DAY VALIDATION-----------
		if (__DATE__[4] == ' ' || __DATE__[4] == '0') {
			date_char[3] = '0';
			//if the day is lower than 10
		}
		else {
			date_char[3] = __DATE__[4];
		}
		date_char[4] = __DATE__[5];

		date_char[2] = '/';
		date_char[5] = '/';

		//year is in __DATE__ 7,8,9,10, date_char 6,7,8,9

		date_char[6] = __DATE__[7];
		date_char[7] = __DATE__[8];
		date_char[8] = __DATE__[9];
		date_char[9] = __DATE__[10];


		for (int i = 0; i < 10; i++) {
			str << date_char[i]; //populates the string stream which is later turned into a string
		}

		cout << "Enter new note for " << StudentID << ": " << endl;;
		cin.ignore();
		getline(cin, note);

	}
	else {
		cout << "Could not find student in your advisees list.\n" << endl;
		return false;
	}

	if (note.size() != 0) {
		file.Notes.push_back(id);
		file.Notes.push_back(str.str());
		file.Notes.push_back(StudentID);
		file.Notes.push_back(note);
		file.Notes.push_back("\n");

		cout << "Note added successfully." << endl;
	}else{
		cout << "Note was not added successfully." << endl;
	}

	return true;
}

bool Advisor::AddNotes(string StudentID, string AdvisorID, string Note, FileIO &file) { //adding a transfer note and double advising

	string date, note;
	note = Note;
	char date_char[10];
	bool check1 = true;
	bool checkValid = true;
	//-------MONTH VALIDATION-----------
	if (__DATE__[0] == 'J') {
		if (__DATE__[1] == 'a') {
			//it's january
			date_char[0] = '0';
			date_char[1] = '1';
		}

		if (__DATE__[2] == 'n') {
			//it's june
			date_char[0] = '0';
			date_char[1] = '6';
		}
		if (__DATE__[2] == 'l') {
			//it's july
			date_char[0] = '0';
			date_char[1] = '7';
		}

	}
	if (__DATE__[0] == 'F') {
		//it's feb
		date_char[0] = '0';
		date_char[1] = '2';
	}
	if (__DATE__[0] == 'M') {
		if (__DATE__[2] == 'y') {
			//it's may
			date_char[0] = '0';
			date_char[1] = '5';
		}
		if (__DATE__[2] == 'r') {
			//it's mar
			date_char[0] = '0';
			date_char[1] = '3';
		}
	}
	if (__DATE__[0] == 'A') {
		if (__DATE__[1] == 'p') {
			//it's apr
			date_char[0] = '0';
			date_char[1] = '4';
		}
		if (__DATE__[1] == 'u') {
			//it's aug
			date_char[0] = '0';
			date_char[1] = '8';
		}
	}
	if (__DATE__[0] == 'S') {
		//it's sep
		date_char[0] = '0';
		date_char[1] = '9';
	}
	if (__DATE__[0] == 'O') {
		//it's oct
		date_char[0] = '1';
		date_char[1] = '0';
	}
	if (__DATE__[0] == 'N') {
		//it's nov
		date_char[0] = '1';
		date_char[1] = '1';
	}
	if (__DATE__[0] == 'D') {
		//it's dec
		date_char[0] = '1';
		date_char[1] = '2';
	}
	//-------DAY VALIDATION-----------
	if (__DATE__[4] == ' ' || __DATE__[4] == '0') {
		date_char[3] = '0';
		//if the day is lower than 10
	}
	else {
		date_char[3] = __DATE__[4];
	}
	date_char[4] = __DATE__[5];

	date_char[2] = '/';
	date_char[5] = '/';

	//year is in __DATE__ 7,8,9,10, date_char 6,7,8,9

	date_char[6] = __DATE__[7];
	date_char[7] = __DATE__[8];
	date_char[8] = __DATE__[9];
	date_char[9] = __DATE__[10];

	date = date_char;
	stringstream str;

	for (int i = 0; i < 10; i++) {
		str << date_char[i];
	}


	if (note.size() != 0) {

		file.Notes.push_back(AdvisorID);
		file.Notes.push_back(str.str());
		file.Notes.push_back(StudentID);
		file.Notes.push_back(note);
		file.Notes.push_back("\n");
		
	}

	return true;
}

//search non-advisee, advisor menu
void Advisor::Find(string id) {
	FileIO file;
	Student student;

	int size = file.StudentData.size() - 4;

	//populating student data
	for (int a = 0; a < size; a++) {
		if (file.StudentData.at(a) == id) {
			student.set_id(id);
		}
	}

	if (student.get_id() == "Unknown") {
		cout << "Student was not found.\n\n";
	}
	else {

		int length = file.Advisees.size();
		string advisor;
		//takes note of who advisor is and saves info to use later
		for (auto map_iter = file.Advisees.begin(); map_iter != file.Advisees.end(); map_iter++) {
			int length1 = map_iter->second.size();
			advisor = map_iter->first;
			for (int a = 0; a < length1; a++) {
				if (map_iter->second.at(a) == id) {
					student.set_advisorID(advisor);
				}
			}
		}

		int width = file.AdvisorData.size();

		for (int a = 0; a < width; a++) {
			if (file.AdvisorData.at(a) == student.get_advisor()) {
				student.set_advisorRoomNum(file.AdvisorData.at(a + 2));
				student.set_advisorTeleNum(file.AdvisorData.at(a + 3));
			}
		}

		student.viewAdvisor();
	}
}

void Advisor::Add_Advisee() //needs to be based on ID not just a student
{	//if student already has an advisor, a note will be added
	//if no student exists, 
	bool check = false;
	bool check2 = false;
	char choice = 'n';
	int size = 0;
	string current_advisor;

	FileIO file;

	while (check2 == false) {
		choice = 'n';
		cin.ignore();
		cout << "Please enter the student ID: ";
		string studentID;
		getline(cin, studentID, '\n');


		for (auto x : file.StudentData) {
			size++;
		}

		//looks for student if exists
		for (int i = 0; i < size; i++) {
			if (file.StudentData[i] == studentID) {
				check2 = true;
			}
		}
		if (check2 == true) {
			for (auto iter = file.Advisees.begin(); iter != file.Advisees.end(); iter++) {

				for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++) {

					if (*iter2 == studentID) {
						check = true; //if student does have an advisor
						current_advisor = iter->first;
					}
				}
			}
			if (check == true) {
				cout << "Student already has an advisor." << endl;
				file.WriteDataBack();
				AddNotes(studentID, current_advisor, "***DOUBLE ADVISING REJECTED", file);
			}
			else {
				//student doesn't have an advisor
				file.Advisees[id].pop_back(); //getting rid of newline in the file
				file.Advisees[id].push_back(studentID);
				file.Advisees[id].push_back("\n");

				cout << "Student is added to your advisees." << endl;
			}
		}
		else {
			cout << "Error. Student does not exist. Try again? (Y/N)";
			cin >> choice;

			if (choice == 'y' || choice == 'Y') {
				check2 = false;
			}
			else {
				check2 = true;
			}
		}
	}

	file.WriteDataBack();
}

void Advisor::Delete_Student()
{
	//if not advisor's advisee, can't delete

	FileIO file;
	bool found = false;
	int count = 0;

	int vect_size = 0; //number of advisees
	cout << "Please enter student ID: ";
	string sid;
	cin >> sid;
	//getting size of vector:
	for (auto student : advisees) {
		vect_size += 1;
	}
	char option;


	for (auto s : advisees) { //going thru all student objects
		if (s.get_id() == sid) { //if we get the desired student
			found = true;
			s.viewStats();
			cout << "Is this the student you would like to delete? (Y/N): ";
			cin >> option;

			switch (option) {
			case 'Y':
			case 'y':
				file.Advisees[id].clear(); //clearing vector inside the map

				//deleting student from Advisor object: advisee vector
				for (int a = 0; a < vect_size - 1; ) { //vect size -1 bc we only delete one student at a time
					if (advisees.at(a).get_id() == sid) {
						cout << "Deleted: " << advisees.at(a).get_id();
						advisees.erase(advisees.begin() + a);
					}
					else {
						file.Advisees[id].push_back((advisees.at(a).get_id()));
						a++;
					}
				}
				file.Advisees[id].push_back("\n");
				break;
			case 'N':
			case 'n':
				cout << "Would you like to delete a different student? (Y/N): ";
				cin >> option;

				switch (option) {
				case 'Y':
				case 'y':
					Delete_Student();
					break;

				case 'N':
				case 'n':
					break;

				default:
					break;
				}

				break;

			default:
				break;
			}
		}
	}

	if (!found) {
		cout << "Incorrect ID." << endl << endl;
	}

	file.WriteDataBack(); //updating actual file

}

void Advisor::Transfer_Advisees()
{
	string option;
	char try_again_bool = 'y';
	string receiving_id;
	string author_code = "ENB#342";
	bool code_correct = false;
	char tryAgain = 'y';
	string code_entered;
	bool found = false;
	bool adv_found = false;
	FileIO file;
	int size_vect = 0;
	while (tryAgain == 'y' || tryAgain == 'Y') {

		cin.ignore();
		cout << "Enter authorization code: ";
		getline(cin, code_entered, '\n');
		code_correct = false;

		if (code_entered == author_code) {
			code_correct = true;
			tryAgain = 'n';
		}

		while (!code_correct) {
			cout << "Authorization code is incorrect. Try again? (y/n): ";
			cin >> tryAgain;
			code_correct = true;
			if (tryAgain == 'n' || tryAgain == 'N') {
				return;
			}
		}
	}

	for (auto x : file.AdvisorData) {
		size_vect++;
	}
	while (!adv_found) {
		cout << "Enter the receiving advisor: ";
		cin >> receiving_id;
		// go thru all the advisors to make sure we got the right one

		for (int i = 0; i < size_vect; i++) {
			if (file.AdvisorData[i] == receiving_id) {
				adv_found = true;
			}
		}
		if (!adv_found) {
			cout << "Advisor ID was incorrect. Try again? (y/n) ";
			cin >> try_again_bool;
			if (try_again_bool == 'n' || try_again_bool == 'N') {
				return;
			}
		}
	}

	cout << "What major do you want to transfer? " << endl
		<< "Option: ";
	cin.ignore();
	getline(cin, option, '\n');

	vector <string> temp_vect;
	int count = 0;


	int size = advisees.size();
	int count2 = 0;
	
	for (int a = 0; a < size; a++) { //if the advisor has a student with that major
		if (advisees.at(a).get_major() == option) {
			found = true;
		}
	}

	if (found) { //if a student with major was found

		for (int a = 0; a < size - count2;) {
			if (advisees.at(a).get_major() == option) {
				temp_vect.push_back(advisees.at(a).get_id()); //add student ID to temp vector
				file.Advisees[id].erase(file.Advisees[id].begin() + a);
				advisees.erase(advisees.begin() + a); //erase student from current advisor
				count2++;
			}
			else {
				a++;
			}
		}

		int length = temp_vect.size();
		file.Advisees[receiving_id].pop_back(); //popping out newline character


		for (int a = 0; a < length; a++) { //adding transfer advisees to new advisor's vector in map
			file.Advisees[receiving_id].push_back(temp_vect.at(a));
		}

		file.WriteDataBack();
		file.Advisees[receiving_id].push_back("\n");
		//add note to student with receiving advisor in header
		for (auto stud : temp_vect) {
			AddNotes(stud, receiving_id, "***ADVISOR CHANGED FROM " + id + " TO " + receiving_id, file);
		}

	}
	else { //if a student with major was not found
		cout << "You have no advisees with that major." << endl << endl;
	}
	file.WriteDataBack();
}


bool Advisor::login() {
	//cout << "This is the login function in the Advisor class." << endl << endl;

	cout << "Please enter your advisor ID: ";
	string id;
	cin >> id;

	cout << "Please enter your password: ";
	string password;
	cin >> password;

	FileIO file;

	int size = file.AdvisorData.size() - 4;
	bool found = 0;

	//populating advisor data
	for (int a = 0; a < size; ) {
		if (file.AdvisorData.at(a) == id && file.AdvisorData.at(a + 1) == password) {
			this->id = id;
			this->password = password;
			roomNum = file.AdvisorData.at(a + 2);
			teleNum = file.AdvisorData.at(a + 3);
			found = 1;
		}
		a = a + 5;
	}

	if (!found) {
		return false;
	}

	create_advisees_vector();

	return true;

}



void Advisor::AllAdvisors() { //to see all other advisors' basic info

	FileIO file;
	int size = file.AdvisorData.size() - 4;

	cout << left << setw(6) << "\nID"
		<< right << setw(11) << "Room Number"
		<< right << setw(16) << "Phone Number" << endl;
	cout << "-----------------------------------" << endl;

	for (int a = 0; a < size; a++) {
		cout << left << setw(6) << file.AdvisorData.at(a) << right << setw(10) << file.AdvisorData.at(a + 2) << right << setw(16) << file.AdvisorData.at(a + 3) << endl;
		a = a + 4;
	}

}


void Advisor::create_advisees_vector() {

	FileIO file;

	for (auto iter = file.Advisees.begin(); iter != file.Advisees.end(); iter++) {
		if (iter->first == id) {

			for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++) {
				int size = 0;
				for (auto x : file.StudentData) {
					size++;
				}
				for (int i = 0; i < size; i++) {
					if (*iter2 != "\n") {
						if (*iter2 == file.StudentData[i]) {
							if ((i + 4) < size) {
								Student student;
								student.set_id(file.StudentData[i]);
								student.set_major(file.StudentData[i + 2]);
								student.set_totalHrs(stoi(file.StudentData[i + 3]));
								student.set_gpa(stod(file.StudentData[i + 4]));
								advisees.push_back(student);
							}
						}
					}
				}
			}
		}
	}

	file.WriteDataBack();
}


void Advisor::set_id(string p) {
	id = p;
}

void Advisor::set_room(string p) {
	roomNum = p;
}

void Advisor::set_number(string p) {
	teleNum = p;
}

void Advisor::viewStats() {
	cout << "\nAdvisor ID: " << id << endl;
	cout << "Advisor Room: " << roomNum << endl;
	cout << "Advisor Telephone Number: " << teleNum << endl << endl;
}