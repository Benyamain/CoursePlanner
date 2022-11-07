/* Andre Price & Benyamain Yacoob
04-06-2022
Intro to Programming II
Dr. Mina Maleki
"Project #3-2" Exercise */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Global variables
const int MAX_NUM_OF_COURSES = 100;	// Global variable to show the maximum number of courses

struct CourseInfo
{
    int courseID;
    string courseName;
    string courseCode;
    string Term;
    int courseSections[3];
};

// greetingText: Posts instructions to the user on how the program functions
// INPUT: N/A
// Function called to display user greeting
// OUTPUT: N/A
void greetingText()
{
    for (int i = 0; i < 120; i++)
        cout << "-";

  	//Prints the greeting to the user.
    cout << endl << "Hello! Welcome to Price & Yacoob University. You have entered the course creation screen." << endl;
    cout << "As the new Dean of Classes, you can add any course that you want.";
    cout << " However, there are a set of rules you must follow." << endl;
    cout << "The first step is to add a course name (for example 'Calculus I') and";
    cout << " then add a course code (MATH-1410).\n";
    cout << "Then, add a term! The term MUST start with a capital letter after which you must add a year (S2022).\n";
    cout << "Finally, you must add course sections. There is a maximum of 3. Any sections";
    cout << " not listed will be marked with a 0." << endl;

    for (int i = 0; i < 120; i++)
        cout << "-";

    cout << endl << endl;
}

// inputValidation: Asks user to confirm the menu choice they made
// INPUT: A character ( inputConfirm ) that is 'Y' or 'N'
// Function called when menu choice needs to be confirmed
// OUTPUT: N/A
char inputValidation(int choiceFromUser, char inputConfirm)
{
    inputConfirm = toupper(inputConfirm); // Uppercases the letter

    while (true)
    {
        if (inputConfirm == 'Y')
            break;
        else if (inputConfirm == 'N')
            break;
        else if (inputConfirm != 'Y' && inputConfirm != 'N')
        {
            cout << "ERROR: Invalid input.\n";
            cout << "Please type (Y/N): ";
            cin >> inputConfirm;

            inputConfirm = toupper(inputConfirm);
        }
    }

    return inputConfirm;
}

// validationForExit: Asks user to confirm if they want to save course data
// INPUT: A character that is 'Y' or 'N'
// Function called when save course data question needs to be answered
// OUTPUT: N/A
char validationForExit(char exitConfirm)
{
    exitConfirm = toupper(exitConfirm); // Uppercases the letter

    while (true)
    {
        if (exitConfirm == 'Y')
            break;
        else if (exitConfirm == 'N')
            break;
        else if (exitConfirm != 'Y' && exitConfirm != 'N')
        {
            cout << "ERROR: Invalid input.\n";
            cout << "Please type (Y/N): ";
            cin >> exitConfirm;

            exitConfirm = toupper(exitConfirm);
        }
    }

    return exitConfirm;
}

// menuOptions: Show menu options for user to interact with
// INPUT: N/A
// Function is called in the main
// OUTPUT: Displays the program menu for the user
int menuOptions()
{
    int choiceFromUser;
    char inputConfirm;    // Echoing the input when appropriate

    do
    {
        // Displays the menu options
        cout << endl << "Course Management System" << endl;
        cout << "------------------------" << endl;
        cout << "1. Add a new course" << endl;
        cout << "2. Update a course" << endl;
        cout << "3. Delete a course" << endl;
        cout << "4. Search for a course" << endl;
        cout << "5. Display course information" << endl;
        cout << "6. Save course information" << endl;
        cout << "7. Exit" << endl;
        cout << "Please enter a selection: ";
        cin >> choiceFromUser;
        cout << "Did you mean to press " << choiceFromUser << " (Y/N)?: ";
        cin >> inputConfirm;

        inputConfirm = inputValidation(choiceFromUser, inputConfirm);   // Calling function

    } while (inputConfirm != 'Y');

    return choiceFromUser;
}

// loadCourseInfo: Format and store them in an array of CourseInfo structures. 
// INPUT: Read-in the "inputFile" from the main as well as the struct variable "arr"
// Function called to read all data from the input file (courseInfo.txt)
// OUTPUT: Returns number of courses
int loadCourseInfo(fstream& inputFile, CourseInfo arr[])
{
    // Declaration of variables
    char delimList[] = ",", * tokenPtr;
    string readFile, tempForArr, tempForTerm;
    int currentPosOfTok = 0, currentPosOfLine = 1;    // Sets current position = 1 b/c will be used as a counter for courseID

    // Checking to see if the inputFile can be opened
    if (!inputFile)
    {
        cout << "Unable to open the file!\n";
    }
    else
    {
        while (!inputFile.eof())    // Read file until the end
        {
            getline(inputFile, readFile);    // Get the content of inputFile into string "readFile"

            int length = readFile.size();

            char* g = new char[length + 1];  // Dynamically allocate to the array to use for tokenizing
            copy(readFile.begin(), readFile.end(), g);
            g[length] = '\0';    // Last index of array will be a null terminator

            // Separating the words in the inputFile
            tokenPtr = strtok(g, delimList);      // Assign the number of tokens to tokenPtr

            arr[currentPosOfLine].courseID = currentPosOfLine; // Current position being used to track courseID

            while (tokenPtr != NULL)
            {
                if (tokenPtr != "deleted") {
                    currentPosOfTok++;	// Using this variable to track where tokenPtr is

                    switch (currentPosOfTok)
                    {
                    case 1:	arr[currentPosOfLine].courseName = tokenPtr;
                        break;

                    case 2:	tempForArr = tokenPtr;
                        tempForArr += "-";
                        break;

                    case 3:	tempForArr += tokenPtr; // String concatenation
                        arr[currentPosOfLine].courseCode = tempForArr;
                        break;

                    case 4:	arr[currentPosOfLine].courseSections[0] = atoi(tokenPtr);   // Converts the char* to an int
                        break;

                    case 5:	arr[currentPosOfLine].courseSections[1] = atoi(tokenPtr);
                        break;

                    case 6:	arr[currentPosOfLine].courseSections[2] = atoi(tokenPtr);
                        break;

                    case 7:	tempForTerm = tokenPtr;
                        break;

                    case 8:	tempForTerm += tokenPtr;
                        arr[currentPosOfLine].Term = tempForTerm; // Store temp into the struct
                        break;

                    default:	for (int i = 0; i < 20; i++)
                        cout << "-";
                        cout << endl << "ERROR OCCURRED!\n";
                        break;
                    }
                    tokenPtr = strtok(NULL, delimList);
                }
            }

            delete[] g;

            currentPosOfTok = 0;    // Resets the current position to go thru the other lines

            currentPosOfLine++;	// Keep track of line to later store into struct
        }
    }

    return currentPosOfLine;
}

// displayCourseInfo: To print a table indicating the course information
// INPUT: User enters ('5') on menu interface
// Function called to display the current courses
// OUTPUT: Courses graphic
void displayCourseInfo(CourseInfo arr[], int currentCourseAmnt)
{
    cout << endl << "ID" << setw(8) << "Name" << setw(16) << "Code" << setw(12) << "Term" << setw(17) << "Sections" << endl;
    for (int a = 0; a < 55; a++)
        cout << "-";

    for (int i = 1; i < currentCourseAmnt; i++)
    {
        cout << endl << arr[i].courseID << "   " << arr[i].courseName << setw(12) << arr[i].courseCode << setw(10) << arr[i].Term;
        cout << setw(9) << arr[i].courseSections[0];
        cout << ',' << arr[i].courseSections[1] << ',' << arr[i].courseSections[2];
    }

    cout << endl << endl;
}

// addCourseInfo: To add a new course 
// INPUT: User enters ('1') on menu interface
// Function called for user to add a new course to the CourseInfo struct
// OUTPUT: Increment the currentCourseAmnt to signify a course was added
int addCourseInfo(fstream& inputFile, CourseInfo arr[], int currentCourseAmnt)
{
    string tempCourseCode, tempCourseTerm;
    bool repeatedCourse = false;
    int numOfSections;

  	//User enters the name of course
    cin.ignore();
    cout << "Enter course name: ";
    getline(cin, arr[currentCourseAmnt].courseName);

    arr[currentCourseAmnt].courseName[0] = toupper(arr[currentCourseAmnt].courseName[0]);   // Make the first letter of newCourseName uppercase
    while (true)
    {
        cout << endl << "Enter subject code (format xxxx): ";
        getline(cin, arr[currentCourseAmnt].courseCode);

        if ((arr[currentCourseAmnt].courseCode).length() == 4){  // Checking if format of courseCode is being followed
            for (int i = 0; i < 4; i++)
                arr[currentCourseAmnt].courseCode[i] = toupper(arr[currentCourseAmnt].courseCode[i]);
            
            break;
        }
        else
            cout << "INVALID SUBJECT CODE INPUT!\n";
    }

    tempCourseCode = arr[currentCourseAmnt].courseCode;
    tempCourseCode += "-";

    while (true)
    {
        cout << endl << "Enter course number (format xxxx): ";
        getline(cin, arr[currentCourseAmnt].courseCode);

        if ((arr[currentCourseAmnt].courseCode).length() == 4)
            break;
        else
            cout << "INVALID COURSE NUMBER INPUT!\n";
    }

    tempCourseCode += arr[currentCourseAmnt].courseCode;

    arr[currentCourseAmnt].courseCode = tempCourseCode; // Putting courseCode into struct

    while (true)
    {
        cout << endl << "Enter semester (S, F or W): ";
        getline(cin, arr[currentCourseAmnt].Term);

        arr[currentCourseAmnt].Term[0] = toupper(arr[currentCourseAmnt].Term[0]);

        if (arr[currentCourseAmnt].Term == "S" || arr[currentCourseAmnt].Term == "F" || arr[currentCourseAmnt].Term == "W")
            break;
        else
            cout << "INVALID COURSE TERM INPUT!\n";
    }

    tempCourseTerm = arr[currentCourseAmnt].Term;

    while (true)
    {
        cout << endl << "Enter year (format yyyy): ";
        getline(cin, arr[currentCourseAmnt].Term);

        if (arr[currentCourseAmnt].Term.length() == 4)
            break;
        else
            cout << "INVALID YEAR INPUT!\n";
    }

    tempCourseTerm += arr[currentCourseAmnt].Term;

    arr[currentCourseAmnt].Term = tempCourseTerm;

    for (int e = 1; e < currentCourseAmnt; e++) // Evaluates if there is a repeated course being added
    {
        if (arr[currentCourseAmnt].Term == arr[e].Term && arr[currentCourseAmnt].courseCode == arr[e].courseCode)
        {
            repeatedCourse = true;
            cout << "INVALID: Repeated course information (" << arr[e].courseCode << " in " << arr[e].Term << ")!\n";
        }
    }

    while (true)
    {
        cout << endl << "Enter number of sections: ";
        cin >> numOfSections;

        if (numOfSections < 1 || numOfSections > 3)
        {
            cout << "----------------------------------------------------" << endl;
            cout << "YOU MUST HAVE AT LEAST 1 TO 3 COURSE SECTIONS!\n";
        }
        else
        {
            // Evaluating if any of entered courseSections are repeated
            for (int i = 0; i < numOfSections; i++)
            {
                cout << endl << "Enter section code " << i + 1 << ": ";
                cin >> arr[currentCourseAmnt].courseSections[i];

                if (numOfSections == 1)
                {
                }
                else
                {
                    for (int c = 0; c < i; c++)
                    {
                        if (arr[currentCourseAmnt].courseSections[i] == arr[currentCourseAmnt].courseSections[c])
                        {
                            cout << "INVALID: Repeated section code!\n";
                            
                            --i;
                        }
                    }
                }
                
            }

            arr[currentCourseAmnt].courseID = currentCourseAmnt;    // Set courseID to be displayed later

            // Displaying the format
            cout << endl << endl;
            cout << "The following course was added:" << endl;

            cout << "ID" << setw(8) << "Name" << setw(16) << "Code" << setw(12) << "Term" << setw(17) << "Sections" << endl;
            for (int a = 0; a < 55; a++)
                cout << "-";

            cout << endl << arr[currentCourseAmnt].courseID << "   " << arr[currentCourseAmnt].courseName << setw(12);
            cout << arr[currentCourseAmnt].courseCode << setw(10) << arr[currentCourseAmnt].Term;
            cout << setw(9) << arr[currentCourseAmnt].courseSections[0];
            cout << ',' << arr[currentCourseAmnt].courseSections[1] << ',' << arr[currentCourseAmnt].courseSections[2];

            cout << endl << endl;

            currentCourseAmnt++;

            break;
        }
    }

    return currentCourseAmnt;
}

// updateCourseInfo: To update existing course information
// INPUT: User enters ('2') on menu interface
// Function called for user to update some course already available
// OUTPUT: Updated course(s)
void updateCourseInfo(CourseInfo arr[], fstream& inputFile, int currentCourseAmnt)
{
    int inputForID, inputMethod, inputForSections;
    string tempCourseForSwitch, tempTermForSwitch;

    cout << "Enter course ID: ";
    cin >> inputForID;

    cout << endl << "ID" << setw(8) << "Name" << setw(16) << "Code" << setw(12) << "Term" << setw(17) << "Sections" << endl;
    for (int a = 0; a < 55; a++)
        cout << "-";

    for (int i = 0; i < currentCourseAmnt; i++)
    {
        // Algorithm to see if such courseID exists
        if (inputForID == i) {
            cout << endl << arr[inputForID].courseID << "   " << arr[inputForID].courseName << setw(12);
            cout << arr[inputForID].courseCode << setw(10) << arr[inputForID].Term;
            cout << setw(9) << arr[inputForID].courseSections[0];
            cout << ',' << arr[inputForID].courseSections[1] << ',' << arr[inputForID].courseSections[2];

            cout << endl << endl << "Enter the code to update the course name (1), course code (2), term (3), or sections (6): ";
            cin >> inputMethod;

            switch (inputMethod)
            {
            case 1: cin.ignore();
                cout << "Enter the new course name: ";
                getline(cin, arr[inputForID].courseName);

                arr[inputForID].courseName[0] = toupper(arr[inputForID].courseName[0]);

                cout << "The course information was updated:" << endl;
                cout << endl << "ID" << setw(8) << "Name" << setw(16) << "Code" << setw(12) << "Term" << setw(17) << "Sections" << endl;

                for (int a = 0; a < 55; a++)
                    cout << "-";

                cout << endl << arr[inputForID].courseID << "   " << arr[inputForID].courseName << setw(12);
                cout << arr[inputForID].courseCode << setw(10) << arr[inputForID].Term;
                cout << setw(9) << arr[inputForID].courseSections[0];
                cout << ',' << arr[inputForID].courseSections[1] << ',' << arr[inputForID].courseSections[2];
                break;

            case 2: cin.ignore();
                while (true)
                {
                    cout << endl << "Enter the new subject code (format xxxx): ";
                    getline(cin, arr[inputForID].courseCode);

                    if ((arr[inputForID].courseCode).length() == 4){
                        for (int i = 0; i < 4; i++)
                            arr[inputForID].courseCode[i] = toupper(arr[inputForID].courseCode[i]);
                        
                        break;
                    }
                    else
                        cout << "INVALID SUBJECT CODE INPUT!\n";
                }

                tempCourseForSwitch = arr[inputForID].courseCode;
                tempCourseForSwitch += "-";

                while (true)
                {
                    cout << endl << "Enter the new course number (format xxxx): ";
                    getline(cin, arr[inputForID].courseCode);

                    if ((arr[inputForID].courseCode).length() == 4)
                        break;
                    else
                        cout << "INVALID COURSE NUMBER INPUT!\n";
                }

                tempCourseForSwitch += arr[inputForID].courseCode;

                arr[inputForID].courseCode = tempCourseForSwitch;

                cout << "The course information was updated:" << endl;
                cout << endl << "ID" << setw(8) << "Name" << setw(16) << "Code" << setw(12) << "Term" << setw(17) << "Sections" << endl;

                for (int a = 0; a < 55; a++)
                    cout << "-";

                cout << endl << arr[inputForID].courseID << "   " << arr[inputForID].courseName << setw(12);
                cout << arr[inputForID].courseCode << setw(10) << arr[inputForID].Term;
                cout << setw(9) << arr[inputForID].courseSections[0];
                cout << ',' << arr[inputForID].courseSections[1] << ',' << arr[inputForID].courseSections[2];
                break;

            case 3: cin.ignore();
                while (true)
                {
                    cout << endl << "Enter the new semester (S, F or W): ";
                    getline(cin, arr[inputForID].Term);

                    arr[inputForID].Term[0] = toupper(arr[inputForID].Term[0]);

                    if (arr[inputForID].Term == "S" || arr[inputForID].Term == "F" || arr[inputForID].Term == "W")
                        break;
                    else
                        cout << "INVALID COURSE TERM INPUT!\n";
                }

                tempTermForSwitch = arr[inputForID].Term;

                while (true)
                {
                    cout << endl << "Enter the new year (format yyyy): ";
                    getline(cin, arr[inputForID].Term);

                    if (arr[inputForID].Term.length() == 4)
                        break;
                    else
                        cout << "INVALID YEAR INPUT!\n";
                }

                tempTermForSwitch += arr[inputForID].Term;

                arr[inputForID].Term = tempTermForSwitch;

                cout << "The course information was updated:" << endl;
                cout << endl << "ID" << setw(8) << "Name" << setw(16) << "Code" << setw(12) << "Term" << setw(17) << "Sections" << endl;

                for (int a = 0; a < 55; a++)
                    cout << "-";

                cout << endl << arr[inputForID].courseID << "   " << arr[inputForID].courseName << setw(12);
                cout << arr[inputForID].courseCode << setw(10) << arr[inputForID].Term;
                cout << setw(9) << arr[inputForID].courseSections[0];
                cout << ',' << arr[inputForID].courseSections[1] << ',' << arr[inputForID].courseSections[2];
                break;

            case 6: cin.ignore();
                while (true)
                {
                    cout << endl << "Enter number of sections: ";
                    cin >> inputForSections;

                    if (inputForSections < 1 || inputForSections > 3)
                    {
                        cout << "----------------------------------------------------" << endl;
                        cout << "YOU MUST HAVE AT LEAST 1 TO 3 COURSE SECTIONS!\n";
                    }
                    else
                    {
                        // Evaluating if any of entered courseSections are repeated
                        for (int i = 0; i < inputForSections; i++)
                        {
                            cout << endl << "Enter section code " << i + 1 << ": ";
                            cin >> arr[inputForID].courseSections[i];
                            
                            if (inputForSections == 1)
                            {
                            }
                            else
                            {
                                for (int c = 0; c < i; c++)
                                {
                                    if (arr[inputForID].courseSections[i] == arr[inputForID].courseSections[c])
                                    {
                                        cout << "INVALID: Repeated section code!\n";
                                        
                                        --i;
                                    }
                                }
                            }
                        }

                        cout << "The course information was updated:" << endl;

                        cout << "ID" << setw(8) << "Name" << setw(16) << "Code" << setw(12) << "Term" << setw(17) << "Sections" << endl;
                        for (int a = 0; a < 55; a++)
                            cout << "-";

                        cout << endl << arr[inputForID].courseID << "   " << arr[inputForID].courseName << setw(12);
                        cout << arr[inputForID].courseCode << setw(10) << arr[inputForID].Term;
                        cout << setw(9) << arr[inputForID].courseSections[0];
                        cout << ',' << arr[inputForID].courseSections[1] << ',' << arr[inputForID].courseSections[2];

                        cout << endl << endl;

                        break;
                    }
                }
                break;

            default:    for (int a = 0; a < 20; a++)
                cout << "-";
                cout << "INVALID INPUT!\n";
            }
        }
    }
    cout << endl << endl;
}

// saveCourseInfo: To save course information from the array of structures to a text file
// INPUT: User enters ('6') on menu interface
// Function called to save the updated "CourseInfo" struct into the inputFile
// OUTPUT: N/A
void saveCourseInfo(CourseInfo arr[], int currentCourseAmnt)
{
    ofstream inputFile("courseInfo.txt", ios::in | ios::out); //Makes file input and output.

    for (int i = 1; i < currentCourseAmnt; i++)
    {
        if (arr[i].courseID != 0) {
            inputFile << arr[i].courseName << ",";

            for (int b = 0; b < 4; b++)
                inputFile << arr[i].courseCode[b];

            inputFile << ",";
            for (int c = 5; c < 9; c++)
                inputFile << arr[i].courseCode[c];


            inputFile << "," << arr[i].courseSections[0] << "," << arr[i].courseSections[1] << "," << arr[i].courseSections[2];
            inputFile << ",";

            for (int d = 0; d < 1; d++)
                inputFile << arr[i].Term[d];

            inputFile << ",";

            for (int f = 1; f < 5; f++)
                inputFile << arr[i].Term[f];

            if (i != currentCourseAmnt - 1) // Does not create a new line at the end
                inputFile << endl;
        }
        else {
                inputFile << "deleted, " ;
            for (int i = 0; i < sizeof(arr[i]); i++) {
                inputFile << " ";
            }
            inputFile << endl;
        }
    }

    inputFile.close();
}

// deleteCourseInfo: To delete existing course information
// INPUT: User enters ('3') on menu interface
// Function called to delete a course from available ones listed
// OUTPUT: Some course is now deleted
int deleteCourseInfo(CourseInfo arr[], fstream& inputFile, int currentCourseAmnt)
{
    int currentCourseID = 1, userInputForID;
    char deleteConfirmation, inputConfirmation;
    CourseInfo arrTemp[100];

    // Setting the original value to the copy
    for (int i = 1; i < currentCourseAmnt; i++)
    {
        arrTemp[i].courseID = arr[i].courseID;
        arrTemp[i].courseName = arr[i].courseName;
        arrTemp[i].courseCode = arr[i].courseCode;
        arrTemp[i].courseSections[0] = arr[i].courseSections[0];
        arrTemp[i].courseSections[1] = arr[i].courseSections[1];
        arrTemp[i].courseSections[2] = arr[i].courseSections[2];
        arrTemp[i].Term = arr[i].Term;
    }

    cout << "Enter the course ID: ";
    cin >> userInputForID;

    cout << endl << "ID" << setw(8) << "Name" << setw(16) << "Code" << setw(12) << "Term" << setw(17) << "Sections" << endl;
    for (int a = 0; a < 55; a++)
        cout << "-";

    cout << endl << arr[userInputForID].courseID << "   " << arr[userInputForID].courseName << setw(12);
    cout << arr[userInputForID].courseCode << setw(10) << arr[userInputForID].Term;
    cout << setw(9) << arr[userInputForID].courseSections[0];
    cout << ',' << arr[userInputForID].courseSections[1] << ',' << arr[userInputForID].courseSections[2];
    cout << endl << endl;

    do
    {
        cout << endl << endl << "Are you sure you want to delete the course (Y/N)?: ";
        cin >> deleteConfirmation;
        cout << "Did you mean to press " << deleteConfirmation << " (Y/N)?: ";
        cin >> inputConfirmation;

        inputConfirmation = inputValidation(deleteConfirmation, inputConfirmation);

    } while (inputConfirmation != 'Y');

    for (int i = 1; i < currentCourseAmnt; i++)
    {
        // Matches with the courseID
        if (userInputForID == i) {
            arr[i].courseName = "Deleted course";
            arr[i].courseCode = "";
            arr[i].Term = "";
            arr[i].courseID = 0;
            arr[i].courseSections[0] = 0;
            arr[i].courseSections[1] = 0;
            arr[i].courseSections[2] = 0;
        }
        else
        {
            arr[i].courseID = currentCourseID;
            arr[i].courseID = arrTemp[i].courseID;
            arr[i].courseName = arrTemp[i].courseName;
            arr[i].courseCode = arrTemp[i].courseCode;
            arr[i].courseSections[0] = arrTemp[i].courseSections[0];
            arr[i].courseSections[1] = arrTemp[i].courseSections[1];
            arr[i].courseSections[2] = arrTemp[i].courseSections[2];
            arr[i].Term = arrTemp[i].Term;
            currentCourseID++;
        }
    }

    cout << endl << endl;
    saveCourseInfo(arr, currentCourseAmnt);
    loadCourseInfo(inputFile, arr);

    return currentCourseAmnt;
}

// searchCourseInfo: To search for course information using either courseName, courseCode, or Term
// INPUT: User enters ('4') on menu interface
// Function called to give user ability to search for a desired course
// OUTPUT: Print the list of course information if it exists
void searchCourseInfo(CourseInfo arr[], int currentCourseAmnt)
{
    char userChoice;
    string name, code, semester, year, term, courseNum;
    bool courseExists = false, termExists = false, subjectExists = false;

    cout << "Welcome to the course search interface!" << endl;
    cout << "Please select how you want to search for the course. (A) for course name, (B) for course code, or (C) for the term: ";
    cin >> userChoice;

    userChoice = toupper(userChoice);   // Making the input uppercase

    while (userChoice != 'A' && userChoice != 'B' && userChoice != 'C') {
        cout << "The character you have entered is incorrect. Please try again: ";
        cin >> userChoice;
        
        userChoice = toupper(userChoice);
    }

    cin.ignore();

  	// Code for if the user chooses to search for the course by using the course name.
    if (userChoice == 'A') {
        cout << "Please state the name of the course that you want to search for: ";
        getline(cin, name);

        name[0] = toupper(name[0]);

        cout << endl << "ID" << setw(8) << "Name" << setw(16) << "Code" << setw(12) << "Term" << setw(17) << "Sections" << endl;
        for (int a = 0; a < 55; a++)
            cout << "-";

        for (int i = 0; i < currentCourseAmnt; i++)
        {
            // Matching input to the struct
            if (name == arr[i].courseName) {
                courseExists = true;
                cout << endl << arr[i].courseID << "   " << arr[i].courseName << setw(12) << arr[i].courseCode << setw(10) << arr[i].Term;
                cout << setw(9) << arr[i].courseSections[0];
                cout << ',' << arr[i].courseSections[1] << ',' << arr[i].courseSections[2];
            }
        }
        cout << endl << endl;

        if (!courseExists)
        {
            cout << "-------------------------------" << endl;
            cout << "THAT COURSE NAME DOES NOT EXIST!\n";
        }
    }
  	// Code for if the user is using course subject and course number.
    else if (userChoice == 'B') {

        while (true)
        {
            cout << "Please state the course subject: ";
            getline(cin, code);

            if (code.length() == 4){
                for (int i = 0; i < 4; i++)
                    code[i] = toupper(code[i]);
                
                break;
            }
            else
                cout << "INVALID SUBJECT CODE INPUT!\n";
        }

        code += "-";

        while (true)
        {
            cout << "Please state the course number: ";
            getline(cin, courseNum);

            if (courseNum.length() == 4)
                break;
            else
                cout << "INVALID COURSE NUMBER INPUT!\n";
        }

        code += courseNum;

        courseNum = code;

        cout << endl << "ID" << setw(8) << "Name" << setw(16) << "Code" << setw(12) << "Term" << setw(17) << "Sections" << endl;
        for (int a = 0; a < 55; a++)
            cout << "-";

        for (int i = 0; i < currentCourseAmnt; i++)
        {
            if (courseNum == arr[i].courseCode)
            {
                subjectExists = true;
                cout << endl << arr[i].courseID << "   " << arr[i].courseName << setw(12) << arr[i].courseCode << setw(10) << arr[i].Term;
                cout << setw(9) << arr[i].courseSections[0];
                cout << ',' << arr[i].courseSections[1] << ',' << arr[i].courseSections[2];
            }
        }
        cout << endl << endl;

        if (!subjectExists)
        {
            cout << "-------------------------------" << endl;
            cout << "THAT COURSE CODE DOES NOT EXIST!\n";
        }
    }
		// Code for the Term and year
    else if (userChoice == 'C') {

        while (true)
        {
            cout << "Please state the term letter: ";
            getline(cin, semester);

            semester[0] = toupper(semester[0]);

            if (semester == "S" || semester == "F" || semester == "W")
                break;
            else
                cout << "INVALID COURSE TERM INPUT!\n";
        }
        while (true)
        {
            cout << "Now enter the year: ";
            getline(cin, year);

            if (year.length() == 4)
                break;
            else
                cout << "INVALID YEAR INPUT!\n";
        }

        term = semester + year;

        cout << endl << "ID" << setw(8) << "Name" << setw(16) << "Code" << setw(12) << "Term" << setw(17) << "Sections" << endl;
        for (int a = 0; a < 55; a++)
            cout << "-";

        for (int i = 0; i < currentCourseAmnt; i++)
        {
            if (term == arr[i].Term)
            {
                termExists = true;
                cout << endl << arr[i].courseID << "   " << arr[i].courseName << setw(12) << arr[i].courseCode << setw(10) << arr[i].Term;
                cout << setw(9) << arr[i].courseSections[0];
                cout << ',' << arr[i].courseSections[1] << ',' << arr[i].courseSections[2];
            }
        }
        cout << endl << endl;

        if (!termExists)
        {
            cout << "-------------------------------" << endl;
            cout << "THAT TERM DOES NOT EXIST!\n";
        }
    }
}

int main()
{
    // Declaring the variables
    fstream inputFile;    // Declares the inputfile
    CourseInfo arr[MAX_NUM_OF_COURSES];    // Declares the variable 'member' with struct CourseInfo
    char saveDataInput, exitConfirm;
    int currentCourseAmnt;

    greetingText();  // Calls the introText function

    // Opening the inputFile
    inputFile.open("courseInfo.txt");

    currentCourseAmnt = loadCourseInfo(inputFile, arr);   // Assign number of courses to a variable for other functions to access

    // Exits the menu interface by pressing 7
    bool runningCode = true;    // Terminates program if false

    do
    {
        // Function is called to show menu interface
        int choiceFromUser = menuOptions();

        switch (choiceFromUser)
        {
        case 1: if (currentCourseAmnt <= MAX_NUM_OF_COURSES)
        {
            currentCourseAmnt = addCourseInfo(inputFile, arr, currentCourseAmnt);
        }
              else
        {
            for (int i = 0; i < 40; i++)
                cout << "-";
            cout << "\nYOU HAVE REACHED THE MAXIMUM AMOUNT OF COURSES. PLEASE DELETE A COURSE AND TRY AGAIN!\n";
        }
              break;

        case 2: displayCourseInfo(arr, currentCourseAmnt);  // Show user what course(s) they want to update

            updateCourseInfo(arr, inputFile, currentCourseAmnt);
            break;

        case 3: deleteCourseInfo(arr, inputFile, currentCourseAmnt);
            break;

        case 4: searchCourseInfo(arr, currentCourseAmnt);
            break;

        case 5: displayCourseInfo(arr, currentCourseAmnt);
            break;

        case 6: saveCourseInfo(arr, currentCourseAmnt);
            break;

        case 7: do
        {
            cout << "Do you want to save course data (Y/N)?: ";
            cin >> saveDataInput;
            cout << "Did you mean to press " << saveDataInput << " (Y/N)?: ";
            cin >> exitConfirm;

            exitConfirm = validationForExit(exitConfirm);   // Calling function

        } while (exitConfirm != 'Y');

        saveDataInput = toupper(saveDataInput);

        if (saveDataInput == 'Y')
            saveCourseInfo(arr, currentCourseAmnt); // Calling the function to save data

        for (int i = 0; i < 40; i++)
            cout << "-";

        cout << "\nGOODBYE!\n";

        runningCode = false;
        break;

        default:    for (int i = 0; i < 20; i++)
            cout << "-";
            cout << "\nINVALID INPUT!\n";
            break;
        }
    } while (runningCode);

    inputFile.close();    // Closing the file

    return 0;
}