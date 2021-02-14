#pragma once
#include "User.h"
#include "FileIO.h"

class Student : public User {
private:
	string id;
	string password;
	double gpa;
	string major;
	int totalHours;

	string advisorID;
	string advisorRoomNum;
	string advisorTeleNum;
public:
	Student();

	void viewAdvisor();

	template<typename T>
	void display(T value); //can print out all student info, which may be int, string, etc

	void viewStats();

	void set_totalHrs(int p); 
	void set_major(string maj);
	void set_gpa(double gpa);
	void set_id(string p);

	void set_advisorID(string id);
	void set_advisorRoomNum(string room);
	void set_advisorTeleNum(string number);

	string get_id();
	double get_gpa();
	string get_major();
	int get_totalHours();
	string get_advisor();

	bool login();
	void change_gpa();
	void change_major();
	void change_hours();
	void update_vector();
};