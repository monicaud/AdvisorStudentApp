/*
Project 2
Due Date: 4/21/19
Group Members:
	Loiy Habhab					
	Monica Ulloa 
	Serena Rampersad
*/

#include "User.h"
#include "Advisor.h"
#include "Student.h"
#include "FileIO.h"

using namespace std;

//A function that calls the virtual function in User class. This is overridden.
bool getUserInfo(User &newUser) { //This is polymorphism and it does work. (: SR
	
	return newUser.login(); 
	//if user is a student, should use student login function
	//if user is an advisor, should use advisor login function
	  
}

int main() {

	FileIO file;

	if (file.file_is_open == false) {
	cout << "The files were unable to be located. Please locate the files and restart the application." << endl;
	return 0;
	}

	bool isOk = 1;
	string try_again = "Y";
	string StudentID;
	bool checkID = false;
	string yes_no = "y";

	while (isOk) { //Still participating in application. False when exiting.
		cout << "Hello! Welcome to OASIS!" << endl << endl;
		cout << "Please select an option: ";
		cout << "\nAdvisor (A) \nStudent (S)\nExit (E)\nOption? "; //Prompting user
		string option;
		cin >> option;

		cout << endl << endl;

		int notDone = 1;
		int numOption = 0;
		string id;
		if (option == "A" || option == "a") { //Advisor Route
			Advisor advisor;

			try_again = "y";

			while ((try_again == "Y")||(try_again == "y")) { //while loop for incorrect login for student and advisor

				try_again = "n";
				
				if (getUserInfo(advisor)) {//if advisor login worked, go into while loop
					while (notDone) { //Stil participating as an advisor.

						cout << "\n-----------------------------------" << endl;
						cout << "\nAdvisor Menu:" << endl << endl;
						cout << "Please select an option: " << endl;
						cout << "1. Display My Advisees" << endl
							<< "2. Search My Advisees" << endl
							<< "3. Search Non-Advisee" << endl
							<< "4. View My Notes" << endl
							<< "5. Add New Note" << endl
							<< "6. Add New Advisee" << endl
							<< "7. Transfer Advisees" << endl
							<< "8. Delete Advisee " << endl
							<< "9. See All Advisors" << endl
							<< "10. Exit" << endl
							<< "Option: ";
						cin >> numOption;

						while (cin.fail()) { //if not int
							cin.clear();
							cin.ignore();

							cout << "Try again. Select option from Advisor Menu: ";
							cin >> numOption;

						}

						switch (numOption) {
						case 1: 
							advisor.Display();
							break;
						case 2: 
							advisor.Search();
							break;
						case 3: 
							cout << "Student ID: ";
							cin >> id;
							advisor.Find(id);
							break;
						case 4: 
							advisor.ViewNotes();
							break;
						case 5: //Add New Note
							checkID = false; 
							yes_no = "y";
							while(checkID == false && (yes_no == "y" || yes_no == "Y")){
								cout << "Please enter student ID: ";
								cin >> StudentID;
								checkID = advisor.AddNotes(StudentID, file); //returns true if student is found and note is added

								if(checkID==false){ //student was not found
									cout << "Try again? (y/n): ";
									cin >> yes_no;
									cin.clear();
									cin.ignore();
								}
							}
							// writes into the files after adding a note
							file.WriteDataBack();
							break;
						case 6: 
							advisor.Add_Advisee();
							break;
						case 7: 
							advisor.Transfer_Advisees();
							break;
						case 8: 
							advisor.Delete_Student();
							break;
						case 9:
							advisor.AllAdvisors();
							break;
						case 10:
							notDone = 0;
							break;
						default:
							break;
						}
					}
				}
				else { //if advisor login didn't work
					cout << "Incorrect log in credentials." << endl
						<< "Try again? Y/N: ";
					cin >> try_again;
				}
			}
			
			
		}
		else if (option == "S" || option == "s") { //Student Route
			Student student;
			try_again = "Y";
			while ((try_again == "Y") || (try_again == "y")) {
				try_again = "n";
				if (getUserInfo(student)) {
					//--------------WHILE LOOP-------------------
					while (notDone) {
						cout << "\n-----------------------------------" << endl;
						cout << "\nStudent Menu:" << endl << endl;
						cout << "Please select an option: " << endl;
						cout << "1. View My Stats" << endl
							<< "2. Change GPA" << endl
							<< "3. Change Major " << endl
							<< "4. Change Total Hours" << endl
							<< "5. Exit " << endl
							<< "Option: ";
						cin >> numOption;

						while (cin.fail()) {
							cin.clear();
							cin.ignore();
							
							cout << "Try again: ";
							cin >> numOption;

						}


						switch (numOption) {
						case 1: 
							student.viewStats();
							student.viewAdvisor();
							break;
						case 2:
							student.change_gpa();
							break;
						case 3: 
							student.change_major();
							break;
						case 4: 
							student.change_hours();
							break;
						case 5:
							notDone = 0;
							break;
						default:
							cout << "That is not a valid option.";
							break;
						}
					}
					//--------------WHILE LOOP-------------------
				}
				else {
					//incorrect login for the student
					cout << "Incorrect log in credentials." << endl
						<< "Try again? Y/N: ";
					cin >> try_again;
				}
			}
		}
		else if (option == "E" || option == "e") { //Exit Route
			cout << "Have a great day!" << endl;
			isOk = false;
		}
	}

	return 0;
}