/*
[20 points] Write a C++ Program to design an efficient way for the following scenario:

Ross is grading papers this quarter. Each student can have either one or multiple answer sheets. So Ross records the following :

X and Y, which indicates that the marks Y is to be added to the student whose name is X. 

X is a string representing name of the student followed by the first initial of their last name. Y is an integer representing the score. (See example below) 

Each X and Y pair is taken as input from user. For simplicity you can assume the number of entries to be any value greater than 2. 

Finally after all the records have been entered, Ross wants to view the scores and the student names sorted \textbf{lowest to highest by score}. [Assume that two students can have the same score]. 

For Example: 

Input Record list:

SmitaG
20
SamJ
10
SmitaG
10
SamJ
15
ShivA
30

Output:

25 SamJ 
30 ShivA 
30 SmitaG 
*/
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    map<string, int> studentScores;  // Maps student name to total score
    int numEntries;
    cout << "Enter the number of entries: ";
    cin >> numEntries;
    cout << "Input Record list:" << endl;
    for (int i = 0; i < numEntries; i++) {
        string name;
        int score;
        cin >> name >> score;  // Read student name and score
        studentScores[name] += score;  // Add score to the student's total
    }
    
    cout << "Output:" << endl;
    // Create a multimap to sort by score
    multimap<int, string> sortedScores;  // Maps score to student name，const auto& entry的意思是传入引用
    // for (const auto& entry : studentScores) {//传入studentScores中的每个条目，entry.first是学生的名字，entry.second是学生的总分数
    //     sortedScores.insert({entry.second, entry.first});  // Insert score and name into multimap
    // }
    // for (const auto& entry : sortedScores) {
    //     cout << entry.first << " " << entry.second << endl;
    // }
    map<string, int>::iterator it;
    for (it = studentScores.begin(); it != studentScores.end(); ++it) {
        sortedScores.insert({it->second, it->first});  // Insert score and name into multimap
    }
    multimap<int, string>::iterator itr;
    for (itr = sortedScores.begin(); itr != sortedScores.end(); ++itr) {
        cout << itr->first << " " << itr->second << endl;
    }
    return 0;
}