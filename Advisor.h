#pragma once
#include "User.h"
#include "Student.h"


//for the advisor class constructor we can 
//make the vector where we can put the id in it (to help for searching through data) LH

class Advisor : public User {
private:
	string id;
	string password;
	string roomNum;
	string teleNum;
	vector <Student> advisees = {};
public:
	Advisor();

	void Display();
	void Search();
	void Find(string id);
	void AllAdvisors();
	void ViewNotes();
	bool AddNotes(string StudentID, FileIO &file);
	bool AddNotes(string StudentID, string Note, string AdvisorID , FileIO &file);
	void Add_Advisee();
	void Delete_Student();
	void Transfer_Advisees();

	bool login();

	void set_id(string p);
	void set_room(string room);
	void set_number(string num);

	void viewStats();

	void create_advisees_vector();

};
