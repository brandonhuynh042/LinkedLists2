#include <iostream>
#include <cstring>
#include <iomanip>
#include "Node.h"
#include "Student.h"

void addStudent(Student* newStudent, Node* &head);
void printStudent(Node* current);
void averageGPA(Node* current, int index, float sum);
int main() {
  Node* head = NULL;
  bool quit = false;
    while (quit == false) {
    // Take in user input, show commands
      char input[9];
    cout << "You can: \'ADD\' \'AVERAGE\' \'PRINT\' \'DELETE\' \'QUIT\'" << endl;
    cin >> input;
    // See what they entered...
    if (strcmp(input, "ADD") == 0) {
      Student* newStudent = new Student();
      cout << "first name" << endl;
      char firstName[20];
      cin >> firstName;
      cout << "last name" << endl;
      char lastName[20];
      cin >> lastName;
      cout << "id" << endl;
      int id;
      cin >> id;
      cout << "gpa" << endl;
      float gpa;
      cin >> gpa;
      newStudent->setFName(firstName);
      newStudent->setLName(lastName);
      newStudent->setID(id);
      newStudent->setGpa(gpa);
      addStudent(newStudent, head);             // go to proccess of adding student
    }
    else if (strcmp(input, "AVERAGE") == 0) {
      averageGPA(head, 0, 0);
    }
    else if (strcmp(input, "PRINT") == 0) {
      printStudent(head);           // go to process of printing student list
    }
    else if (strcmp(input, "DELETE") == 0) {
      // Get the ID that wants to be deleted
      cout << "What is the ID of the student you'd like to delete?" << endl;
      int deleteInput;
      cin >> deleteInput;
    }
    else if (strcmp(input, "QUIT") == 0) {
      cout << "Quitting." << endl;
      quit = true;
    }
    else {
      cout << "Please enter a valid input!" << endl;
    }
  }
  return 0;
}

void addStudent(Student* newStudent, Node* &head) {
  if (head == NULL) {
    head = new Node(newStudent);
    return;
  }
  if (newStudent->getID() <= head->getValue()->getID()) {
     cout << "here" << endl;
        Node* newNode = new Node(newStudent);
        Node* tempHead = head;
        head = newNode;
        head->setNext(tempHead);
  }
  Node* next = head->getNext();
    if (next != NULL) {
      if (head->getValue()->getID() <= newStudent->getID() && newStudent->getID() <= next->getValue()->getID()) {
	Node* newNode = new Node(newStudent);
	head->setNext(newNode);
	head->getNext()->setNext(next);
	return;
      }
      addStudent(newStudent, next);
    }
    if (next == NULL) {
      if (head->getValue()->getID() < newStudent->getID()) {
	Node* newNode = new Node(newStudent);
	head->setNext(newNode);
	newNode->setNext(NULL);
	return;
      }
    }
}

void printStudent(Node* current) {
  if (current != NULL) {
    try {
       cout << current->getValue()->getID() << ", " << current->getValue()->getFName() << " " << current->getValue()->getLName() << " " << fixed << setprecision(2) << current->getValue()->getGpa() << endl;
       printStudent(current->getNext());
    }
    catch (...) {
      cout << "There were no students!" << endl;
    }
  }
}

void averageGPA(Node* current, int index, float sum) {
  if (current == NULL) {
    if (index == 0) {
      cout << "No students!" << endl;
      return;
    }
      float average = sum / index;
      cout << "Average GPA: " << fixed << setprecision(2) << average << endl;
   }
  else {
    sum += current->getValue()->getGpa();
    averageGPA(current->getNext(), ++index, sum);
  }
}
