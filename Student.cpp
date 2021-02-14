#include "Student.h"

//works
Student::Student()
{
	id = "Unknown";
	password = "Unknown";
	gpa = 0.0;
	major = "Unknown";
	totalHours = 0;

	advisorID = "Not Assigned";
	advisorRoomNum = "N/A";
	advisorTeleNum = "N/A";
}

bool Student::login() {
	bool found = false;
	cout << "Please enter your student ID: ";
	string id;
	cin >> id;

	cout << "Please enter your password: ";
	string password;
	cin >> password;

	FileIO file;

	//-4 so that the for loop doesn't go out of bounds
	int size = file.StudentData.size() - 5;

	//populating student data
	for (int a = 0; a < size;) {
		if (file.StudentData.at(a) == id && file.StudentData.at(a + 1) == password) {
			this->id = id;
			this->password = password;
			major = file.StudentData.at(a + 2);
			totalHours = stoi(file.StudentData.at(a + 3));
			gpa = stod(file.StudentData.at(a + 4));
			found = true;
		}
		a = a + 6;
	}
	if (!found) {
		return false;
	}

	int length = file.Advisees.size();
	string advisor;

	for (auto map_iter = file.Advisees.begin(); map_iter != file.Advisees.end(); map_iter++) {
		int size1 = map_iter->second.size();
		advisor = map_iter->first;
		for(int a = 0; a < size1; a++){
			if(map_iter->second.at(a) == id){
				advisorID = advisor; //populating data members in student object
			}
		}
	}

	int width = file.AdvisorData.size();

	for (int a = 0; a < width; a++) {
		if (file.AdvisorData.at(a) == advisorID) {
			advisorRoomNum = file.AdvisorData.at(a + 2);
			advisorTeleNum = file.AdvisorData.at(a + 3);
		}
	}

	return true;

}

void Student::change_gpa()
{

	double newGPA = 0.0;

	cout << "Current GPA: " << gpa << endl;
	cout << "Enter new GPA: ";
	cin >> newGPA;
	while (cin.fail()) {
		cin.clear();
		cin.ignore();

		cout << "Try again: ";
		cin >> newGPA;

	}
	set_gpa(newGPA);
	cout << "New GPA: " << gpa;
	update_vector();

}

void Student::change_major()
{

	string newMajor;

	cout << "Current major: " << major << endl;
	cout << "Enter new major: ";
	cin.ignore();
	getline(cin, newMajor, '\n');
	//cin >> newMajor;

	set_major(newMajor);
	cout << "New Major: " << major;

	
	update_vector();
}

void Student::change_hours()
{	
	double newHours;
	int int_hours = 0;
	cout << "Current total hours: " << totalHours << endl;
	cout << "Enter new total hours: ";
	cin >> newHours;
	while (cin.fail()) {
		cin.clear();
		cin.ignore();

		cout << "Try again: ";
		cin >> newHours;
	}
	try{
		if(newHours != (int)newHours){
			throw -1;
		}else{
			set_totalHrs(newHours);
			cout << "New Hours: " << totalHours;
		}
	}
	catch (int) { 
		cout << "Total Hours must be a whole number.\n";
	}
	update_vector();

}



//works
void Student::viewAdvisor()
{
	cout << "Advisor ID: " << advisorID << endl;
	cout << "Advisor Room: " << advisorRoomNum << endl;
	cout << "Advisor Telephone Number: " << advisorTeleNum << endl;
}

template<typename T>
void Student::display(T value){ //function template
	cout << value;
}


void Student::viewStats()
{
	cout << "\nStudent ID: ";
	display(id);
	cout << endl;

	cout << "Student Major: ";
	display(major);
	cout << endl;

	cout << "Student Total Hours: ";
	display(totalHours);
	cout << endl;

	cout << "Student GPA: ";
	display(gpa);
	cout << endl;

}

void Student::update_vector(){

	FileIO file;
	//change the student_Data file
	stringstream str2;
	int size1 = 0;
	for (auto x : file.StudentData) {
		size1++;
	}
	for(int i = 0; i<size1 ; i++ ){
		if(file.StudentData[i]==id){
			
			str2 << setprecision(3) << gpa;
			file.StudentData[i + 2] = major;
			file.StudentData[i + 3] = to_string(totalHours);
			file.StudentData[i + 4] = str2.str();
		}
	}

	file.WriteDataBack();
}

void Student::set_id(string p)
{
	id = p;
}

string Student::get_id()
{
	return id;
}

string Student::get_major()
{
	return major;
}


int Student::get_totalHours()
{
	return totalHours;
}


void Student::set_totalHrs(int p)
{
	totalHours = p;
}

string Student::get_advisor(){
	return advisorID;
}

void Student::set_advisorID(string id) {
	advisorID = id;
}

void Student::set_advisorRoomNum(string num) {
	advisorRoomNum = num;
}

void Student::set_advisorTeleNum(string num) {
	advisorTeleNum = num;
}

void Student::set_gpa(double gpa) {
	this->gpa = gpa;
}

double Student::get_gpa() {
	return gpa;
}

void Student::set_major(string maj)
{
	major = maj;
}
