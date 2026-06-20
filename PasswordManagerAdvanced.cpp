#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

//structure for the user profile
struct User{
    string user, password, account;
};
//output file stream to display all of the users
ostream &operator<<(ostream &out, const User &Data){
    out << "-----------------------" << endl;
    out << "Account: " << Data.account << endl;
    out << "Username: " << Data.user << endl;
    out << "Password: " << Data.password << endl;
    return out;
}
//check if the email is valid
/*^ — start of string
[a-zA-Z0-9_.+-]+ — one or more characters in the local part (before @)
includes letters, digits, _, ., +, - 
after @ sign
[a-zA-Z0-9-]+ — one or more letters, digits, or hyphens in the domain name
\. — literal dot
[a-zA-Z0-9-.]+ — one or more letters, digits, dots, or hyphens in the remainder of the domain
$ — end of string*/
bool validEmail(const string& email){
    const regex valid(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    return regex_match(email, valid);
}
//check the strength of the password to make sure it is strong
string passwordStrengthChecker(const string& password){
    bool hasLower = false;
    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    bool passwordLength = password.length() >= 8 ? 1:0;//make sure that the password is longer than 8 characters
    string specialChars = "!@#$%^&*()-+";//include special characters
    int totalConditions = 0;
    for (auto ch : password){
        if (islower(ch)){
            hasLower = true;
        }else if (isupper(ch)){
            hasUpper = true;
        }else if (isdigit(ch)){
            hasDigit = true;
        }else if (specialChars.find(ch) != string::npos){
            hasSpecial = true;
        }
    }
    totalConditions = hasLower + hasUpper + hasDigit + hasSpecial + passwordLength;
    if (totalConditions >= 5){//if it satisfies all conditions, then it is strong
        return "Strong";
    }else if (totalConditions >= 3){
        return "Medium";
    }else{
        return "Weak";
    }
}
class PasswordManager{
    private:
        string LoginUser;
        string LoginPassword;
        vector<User> listOfUsers;
    public:
        void saveToFile();
        void loadFromFile();
        void mainMenu();
        void addUser();
        void deleteUser();
        void updateUser();
        void displayUsers();
        void searchUser();
        void logout();
        void passwordCheck(const string&);
        void LoginMainMenu();
        void registerUser();
        void login();
        //void xorEncryptDecrypt(string &data, const char &key);
};
void PasswordManager::saveToFile(){//save the login credentials to the file
    ofstream file(LoginUser + ".txt");//open the login text file to write
    if (file.is_open()){//check if file is open
        file << LoginUser << "\n";//write the login user and password, then go through the list of users and write the details
        file << LoginPassword << "\n";
        for (const auto &user : listOfUsers){
            file << user.user << "\n";
            file << user.password << "\n";
            file << user.account << "\n";
        }
        file.close();
    }else{
        cout << "Cannot open the file for writing." << endl;
    }
}
void PasswordManager::loadFromFile(){//read from the file and get the user credentials
    listOfUsers.clear();//clear so that it does not duplicate users if not logged out
    ifstream file(LoginUser + ".txt");//open the file for reading
    if (file.is_open()){
        getline(file, LoginUser);//get login user and password, and for the profile get all of the sub profiles
        getline(file, LoginPassword);
        User user;
        while (getline(file, user.user) &&
               getline(file, user.password) &&
               getline(file, user.account)){
            listOfUsers.push_back(user);
        }
        file.close();
    }else{
        cout << "Cannot open the file for reading." << endl;
    }
}
void PasswordManager::addUser(){//add a new user once logged in, can add email account or non-email account but email has to be valid format
    User newUser;
    cout << "Enter account name: ";
    getline(cin, newUser.account);
    cout << "Enter username: ";
    getline(cin, newUser.user);
    cout << "Enter password: ";
    getline(cin, newUser.password);
    //passwordCheck(newUser.password);//check the password strength of the new user
    while (passwordStrengthChecker(newUser.password) == "Weak") {//if the password is weak, ask for a new password
        cout << "Password too weak. Enter again: ";
        getline(cin, newUser.password);
    }
    for (int x = 0; x < newUser.account.size(); x++){
        newUser.account[x] = tolower(newUser.account[x]);//convert account name to lower case to check if gmail or email exists
    }
    if (newUser.account == "gmail" || newUser.account == "email" || newUser.account == "yahoo"){//if it is an email account, then the username has to be a valid email format
        if (validEmail(newUser.user)){//check if the format of the email is valid
            listOfUsers.push_back(newUser);//put the user onto the vector array 
            cout << "User added." << endl;
        }else{
            cout << "Invalid email." << endl;
            addUser();
        }
    }else{
        listOfUsers.push_back(newUser);//push the new user onto the vector array of users for the logged in account
        cout << "User added." << endl;
    }
}
void PasswordManager::deleteUser(){//delete a user from a logged in account
    string userName;
    bool found = false;
    cout << "Deleting a user from the account." << endl;
    cout << "Enter username: ";
    getline(cin, userName);
    for (auto it = listOfUsers.begin(); it != listOfUsers.end(); ++it){
        if (it->user == userName){
            listOfUsers.erase(it);
            found = true;
            cout << "User deleted successfully!" << endl;
            return;//after deletion, stop the search
        }
    }
    if (!found){//if the boolean value does not change, that means the user was not found
        cout << "User does not exist." << endl;
    }
}
void PasswordManager::updateUser(){//update an account after logged in
    string userName;
    cout << "Updating a user..." << endl;
    cout << "Enter username: ";
    getline(cin, userName);
    bool found = false;
    for (auto &user : listOfUsers){//reference to get direct access to memory
        if (user.user == userName){//if the user is found, then update it
            found = true;
            cout << "Enter new password : ";
            getline(cin, user.password);
            cout << "User updated successfully!" << endl;
        }
    }
    if (!found){//if boolean value does not change, then the user does not exist
        cout << "User does not exist." << endl;
    }
}
void PasswordManager::displayUsers(){//display all of the usernames and passwords for a logged in account
    if (!listOfUsers.empty()){
        cout << "Displaying all users." << endl;
        for (auto &users : listOfUsers){
            //cout << "Username: " << users.user << " Account: " << users.account << " Password: " << users.password << endl;
            cout << users;//use output file stream instead
        }
    }else{
        cout << "The database is empty." << endl;
    }
}
void PasswordManager::searchUser(){//search for a user once logged in 
    string userName;
    bool found = false;
    cout << "Searching for user." << endl;
    cout << "Enter username: ";
    getline(cin, userName);
    for (auto &users : listOfUsers){//go through the vector array
        if (users.user == userName){
            found = true;
            cout << users;//use output file stream
        }
    }
    if (!found){
        cout << "User does not exist." << endl;
    }
}
void PasswordManager::logout(){//when logging out, set variables to empty
    cout << "Logging out..." << endl;
    saveToFile();
    LoginUser = "";
    LoginPassword = "";
    listOfUsers.clear();//clear the vector when logging out
    cout << "Logged out." << endl;
}
void PasswordManager::passwordCheck(const string& password){//checks the strength of the password
    string strength = passwordStrengthChecker(password);
    cout << "Password strength: " << strength << endl;//get the strength of the password from string passwordStrengthChecker
    if(!any_of(password.begin(), password.end(), ::isupper)){//any_of checks if at least one element in range satifies condition
        cout << "Password must have at least one uppercase letter." << endl;
    }else if(!any_of(password.begin(), password.end(), ::islower)){
        cout << "Password must have at least one lowercase letter." << endl;
    }else if(!any_of(password.begin(), password.end(), ::isdigit)){
        cout << "Password must have at least one digit." << endl;
    }else if(password.find_first_of("!@#$%^&*()-+") == string::npos){
        cout << "Password must have at least one special character." << endl;
    }else if(password.length() < 8){
        cout << "Password must be at least 8 characters long." << endl;
    }
}
void PasswordManager::LoginMainMenu(){//Initial main menu to log in a user
    int choice;
    do{
        cout << "Password Manager." << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();//ignore newline character left in the buffer
        //system("clear");
        switch (choice){
        case 1:
            registerUser();
            break;
        case 2:
            login();
            break;
        case 3:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Enter valid choice" << endl;
        }
    } while (choice != 3);
}

void PasswordManager::registerUser(){//register the user
    string inputUser;//inputs for registering
    string inputPassword;
    cout << "Registering a new user." << endl;
    cout << "Enter username: ";
    getline(cin, inputUser);
    cout << "Enter password: ";
    getline(cin, inputPassword);
    //if file exists already
    ifstream file(inputUser + ".txt");
    if (file.is_open()){//the user already exists
        cout << "The user already exists." << endl;
        file.close();
    }else{//the user does not exist yet
        LoginUser = inputUser;
        LoginPassword = inputPassword;
        saveToFile();
        cout << "User registered." << endl;
        file.close();
    }
}

void PasswordManager::login(){//Login the user
    string inputUser;
    string inputPassword;
    cout << "Logging in." << endl;
    cout << "Enter username: ";
    getline(cin, inputUser);//get the input username and check if it exists
    ifstream file(inputUser + ".txt");//open the file for reading
    if (file.is_open()){//if it is able to be opened, the user exists
        file.close();
        LoginUser = inputUser;//set the login username to the inputted username
        loadFromFile();
        cout << "Enter password : ";//get the password and check to see if it matches
        getline(cin, inputPassword);
        if (inputPassword == LoginPassword){//check if input password = loginPassword
            cout << "Login successful!" << endl;
            mainMenu();//take you to the main menu
        }else{
            cout << "Wrong Password." << endl;
        }
    }else{
        cout << "User does not exist." << endl;
    }
}

void PasswordManager::mainMenu(){
    int choice;//choice for what the user wants to do
    do{
        cout << "---------------------------" << endl;
        cout << "Password Manager Main Menu." << endl;
        cout << "1. Add User" << endl;
        cout << "2. Delete User" << endl;
        cout << "3. Update User" << endl;
        cout << "4. Display Users" << endl;
        cout << "5. Search User" << endl;
        cout << "6. Logout" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character left in the buffer
        //system("clear");
        switch(choice){
        case 1:
            addUser();
            break;
        case 2:
            deleteUser();
            break;
        case 3:
            updateUser();
            break;
        case 4:
            displayUsers();
            break;
        case 5:
            searchUser();
            break;
        case 6:
            logout();
            break;
        default:
            cout << "Enter a valid option." << endl;
        }
    } while (choice != 6);
}
int main(){
    PasswordManager loggingIn;//initiate object of PasswordManager class
    loggingIn.LoginMainMenu();
    cout << endl;
    return 0;
}