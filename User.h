#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <exception>
#include <iomanip>
#include <sstream>

using namespace std;

//Superclass

class User {
private:
	string id;
	string password;
public:
	User();
	string get_id();
	void set_password(string password);
	virtual bool login();
};

