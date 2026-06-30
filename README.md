# PasswordManagerAdvanced
A more advanced version of the beginner password manager.
Password management system using C++ using file handling, data structures, object-oriented design, and user input validation. It manages account credentials and implements CRUD (Create, Read, Update, Delete) operations.
Console-based Password Manager written in C++ that allows users to securely organize login credentials for multiple accounts under a master account.
 - Main Features
    - User Registration and Login
        - Users can create a master account with a username and password.
        - Registered users can log in using their credentials.
        - Account data is stored in a text file named after the username.
    - Credential Management
        - After logging in, users can:
        - Add new account credentials
        - Delete existing credentials
        - Update passwords
        - Search for specific accounts
        - Display all stored accounts
        - Log out
    - Password Strength Validation
        - Passwords are evaluated as Weak, Medium, or Strong.
        - Strength is determined by the presence of: Uppercase letters, Lowercase letters, Numbers, Special characters, Minimum length of 8 characters
        - Weak passwords are rejected when adding new accounts.
  - Email Validation
        - Uses regular expressions to verify that email addresses follow a valid format.
        - Applied when adding email-based accounts such as Gmail.
  - File Persistence
        - User data is saved to and loaded from text files.
        - Stored information includes:
        - Master username
        - Master password
        - Saved account usernames
        - Saved account passwords
        - Account names

Object-Oriented Programming (classes and methods), Structures (struct User), File Input/Output (ifstream, ofstream), Data Structures (vectors), Operator overloading, Regular expressions (regex), Input validation, String manipulation, Menu-driven program design
