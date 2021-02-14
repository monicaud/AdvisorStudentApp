#include "User.h"

User::User() {}

bool User::login() {
	cout << "This is the login function in the User class." << endl;
	return true;
}

string User::get_id()
{
	return id;
}

void User::set_password(string password)
{
	this->password = password;
}
