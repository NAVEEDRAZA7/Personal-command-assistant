#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
void speak(const string &text) {
    string command = "espeak \"" + text + "\"";
    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Error: Failed to execute 'espeak'. Please check installation." << endl;
    }
}

	string getGreeting() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int hour = ltm->tm_hour;

    if (hour >= 5 && hour < 12) {
        return "Good Morning";
    } else if (hour >= 12 && hour < 18) {
        return "Good Afternoon";
    } else if (hour >= 18 && hour < 22) {
        return "Good Evening";
    } else {
        return "Hello";
    }
}

string login(const string &username, const string &password) {
    string stored_username, stored_password;

    ifstream readfile("login_info.txt");
    if (!readfile.is_open()) {
        return "Error: Unable to open login file.";
    }

    getline(readfile, stored_username);
    getline(readfile, stored_password);

    readfile.close();

    if (username == stored_username && password == stored_password) {
        return "Login successful";
    } else {
    	speak("Invalid username or password");
    	return ("Invalid username or password");
    }
}

void changeCredentials() {
    cout << "What would you like to change?\n";
    cout << "1. Change Username\n";
    cout << "2. Change Password\n";
    cout << "Enter your choice (1 or 2): ";

    string choice;
    getline(cin, choice);

    string stored_username, stored_password;

  
    ifstream readfile("login_info.txt");
    if (!readfile.is_open()) {
        cout << "Error: Unable to read the login file." << endl;
        speak("Error: Unable to read the login file");
        return;
    }

    getline(readfile, stored_username);
    getline(readfile, stored_password);
    readfile.close();

    if (choice == "1") {
        string new_username;
        cout << "Enter new username: ";
        getline(cin, new_username);

        ofstream writefile("login_info.txt");
        if (writefile.is_open()) {
            writefile << new_username << endl;
            writefile << stored_password << endl;
            writefile.close();
            cout << "Username updated successfully!" << endl;
            speak("Username updated successfully");
        }
		else 
		{
        	speak("Error: Unable to update the username");
            cout << "Error: Unable to update the username." << endl;
          
        }

    } 
	else if (choice == "2") {
        string new_password;
        cout << "Enter new password: ";
        getline(cin, new_password);
   
        ofstream writefile("login_info.txt");
        if (writefile.is_open()) {
            writefile << stored_username << endl;
            writefile << new_password << endl;
            writefile.close();
            cout << "Password updated successfully!" << endl;
            speak("Password updated successfully");
        } else {
            cout << "Error: Unable to update the password." << endl;
            speak("Error: Unable to update the password");
        }

    } else {
        cout << "Invalid choice! Please select 1 or 2." << endl;
        speak("Invalid choice. Please select 1 or 2.");
    }
}
void executecommand(const string &command) {
    cout << "You said: " << command << endl;
    speak("You said " + command);

    if (command == "notepad") {
        cout << "Opening Notepad..." << endl;
        speak("Opening Notepad");
        system("start notepad");
    }
		else if (command == "chrome") {
        cout << "Opening Google chrome..." << endl;
        speak("Opening Google Chrome");
        system("start Chrome");
    } 
   
	else if (command == "note") {
    cout << "What note do you want to save? ";
    speak("What note do you want to save?");
    string note;
    getline(cin, note);

    ofstream note_file("note.txt", ios::app);
    note_file << note << endl;
    note_file.close();

    cout << "Note saved successfully!" << endl;
    speak("Note saved successfully");
}
		else if (command == "tell time") {
        time_t now = time(0);
        tm *ltm = localtime(&now);
       
		stringstream hours_stream;
		hours_stream << ltm->tm_hour;
		string hours = hours_stream.str();
		
		stringstream minutes_stream;
		minutes_stream << ltm->tm_min;
		string minutes = minutes_stream.str();

        string current_time = "Time is " + hours + ":" + minutes;
        cout << current_time << endl;
        speak(current_time);
    } 
		else if (command == "shutdown") {
    cout << "Shutting down the computer..." << endl;
    speak("Shutting down the computer");
    system("shutdown /s /t 0");
} 
		else if (command == "restart") {
    cout << "Restarting the computer..." << endl;
    speak("Restarting the computer");
    system("shutdown /r /t 0");
}
		else if (command == "how are you") {
    cout << "I am fine, and how are you?" << endl;
    speak("I am fine, and how are you?");
    
    string user_response;
    cout << "Your response: ";
    getline(cin, user_response);
    
    cout << "Great!" << endl;
    speak("Great!");
}
		else if (command == "weather") {
    cout << "Showing current weather..." << endl;
    speak("Showing current weather");
    system("start https://www.weather.com");
}
		else if (command == "search") {
    cout << "What do you want to search for on Google? ";
    speak("What do you want to search for on Google?");
    string query;
    getline(cin, query);
    replace(query.begin(), query.end(), ' ', '+');
    string google_search = "start https://www.google.com/search?q=" + query;
    system(google_search.c_str());
}
		else if (command == "ms word") {
    cout << "Opening Microsoft Word..." << endl;
    speak("Opening Microsoft Word");
    system("start winword");
}
		else if (command == "calculator") {
    cout << "Opening Calculator..." << endl;
    speak("Opening Calculator");
    system("calc");
}

    else if (command == "system info") {
    cout << "Fetching system information..." << endl;
    speak("Fetching system information");
    system("systeminfo");
}

		else if (command == "play music") {
    cout << "Opening default music application..." << endl;
    speak("Opening default music application");
    system("start wmplayer");
}
		else if (command == "bye") {
        cout << "Allah Hafiz!" << endl;
        speak("Allah Hafiz");
        exit(0);
    } 	else {
        cout << "Command not recognized!" << endl;
        speak("Command not recognized");
    }
}

bool askToContinue() {
    string response;
    cout << "Do you want to continue? Say 'yes' to continue or 'no' to exit: ";
    getline(cin, response);
    transform(response.begin(), response.end(), response.begin(), ::tolower);

    if (response == "yes") {
        return true;
    } else {
        return false;
    }
}

int main() {
    string u_name, pass;

    cout << "Enter Your Username: ";
    speak("Enter Your Username");
    getline(cin, u_name);

    cout << "Enter Your Password: ";
    speak("Enter Your Password");
    getline(cin, pass);

    string result = login(u_name, pass);

    if (result == "Login successful") {
        string dynamic_greeting = getGreeting();
        cout << "===============================================\n";
        cout << "      Welcome to Your Personal Assistant!      \n";
        cout << "===============================================\n";
        cout << " - Open applications like Notepad, Calculator, or MS Word.\n";
        cout << " - Tell you the current time and date.\n";
        cout << " - Search the web or check the weather.\n";
        cout << " - Play music or fetch system information.\n";
        cout << " - Create and save notes.\n";
        cout << " - Shut down or restart the computer.\n";
        cout << " - And much more!\n";

        cout << "-----------------------------------------------" << endl;
        cout << "Type your command below, and I will assist you:" << endl;
        cout << "-----------------------------------------------" << endl;

        speak(dynamic_greeting + ", " + u_name +  
        ". Welcome to Your Personal Assistant! I am here to make your life easier. You can ask me to: "
        "open applications like Notepad, Calculator, or Microsoft Word; "
        "tell you the current time and date; "
        "search the web or check the weather; "
        "play music or fetch system information; "
        "create and save notes; "
        "shut down or restart the computer; "
        "and much more! "
        "Type your command below, and I will assist you.");
        
        string command;
        while (true) {
            cout << "Enter command: ";
            getline(cin, command);

            transform(command.begin(), command.end(), command.begin(), ::tolower);

            if (command == "change credentials") {
                changeCredentials();
            } else if (command == "bye") {
                cout << "Exiting the assistant. Goodbye!" << endl;
                speak("Goodbye!");
                break;
            } else {
                executecommand(command);
            }

            if (!askToContinue()) {
                cout << "Exiting program..." << endl;
                speak("Exiting program");
                break;
            }
        }
    } else {
        cout << result << endl;
    }

    return 0;
}

