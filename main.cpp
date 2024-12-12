#include <iostream>
#include <cstring>
#include <iomanip>
#include "Node.h"
#include "Student.h"

/* This program creates a student list using linked lists, and has commands to add, average, print, and delete students.
*  Brandon Huynh, last edited 12/12/2024 */

void addStudent(Student* newStudent, Node* &head);
void printStudent(Node* current);
void averageGPA(Node* current, int index, float sum);
void deleteStudent(int targetID, Node* &head);

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
      // take inputs for student info
      Student* newStudent = new Student();
      cout << "What is the student's first name?" << endl;
      char firstName[20];
      cin >> firstName;
      cout << "What is the student's last name?" << endl;
      char lastName[20];
      cin >> lastName;
      cout << "What is the student's ID?" << endl;
      int id;
      cin >> id;
      cout << "What is the student's GPA?" << endl;
      float gpa;
      cin >> gpa;
      newStudent->setFName(firstName);
      newStudent->setLName(lastName);
      newStudent->setID(id);
      newStudent->setGpa(gpa);
      addStudent(newStudent, head);             // go to proccess of adding student
    }
    else if (strcmp(input, "AVERAGE") == 0) {
      averageGPA(head, 0, 0);                   // go to process of averaging gpa
    }
    else if (strcmp(input, "PRINT") == 0) {
      printStudent(head);                       // go to process of printing student list
    }
    else if (strcmp(input, "DELETE") == 0) {
      // get the id that wants to be deleted
      cout << "What is the ID of the student you'd like to delete?" << endl;
      int deleteInput;
      cin >> deleteInput;
      deleteStudent(deleteInput, head);        // go to process of deleting student
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
  // if the list is empty, the student node is the new head
  if (head == NULL) {
    head = new Node(newStudent);
    return;
  }
  // the student node is also the new head if it's smaller than the current head
  if (newStudent->getID() <= head->getValue()->getID()) {
        Node* newNode = new Node(newStudent);
        newNode->setNext(head);
        head = newNode;
	return;
  }
  Node* next = head->getNext();
  // somewhere in the middle of the list
    if (next != NULL) {
      // is it in the right spot (id greater than last, less than next)
      if (head->getValue()->getID() <= newStudent->getID() && newStudent->getID() <= next->getValue()->getID()) {
	// put the new student in between
	Node* newNode = new Node(newStudent);
	head->setNext(newNode);
	head->getNext()->setNext(next);
	return;
      }
      // otherwise, move to the next node in the list
      addStudent(newStudent, next);
    }
    // it's reached the end, meaning it must be the largest.
    if (next == NULL) {
	Node* newNode = new Node(newStudent);
	head->setNext(newNode);
	newNode->setNext(NULL);
	return;
    }
}

void printStudent(Node* current) {
  // if still in the list, print and move to next student
  if (current != NULL) {
       cout << current->getValue()->getID() << ", " << current->getValue()->getFName() << " " << current->getValue()->getLName() << " " << fixed << setprecision(2) << current->getValue()->getGpa() << endl;
       printStudent(current->getNext());
  }
}

void averageGPA(Node* current, int index, float sum) {
  // reached the end of the list
  if (current == NULL) {
    // no students
    if (index == 0) {
      cout << "No students!" << endl;
      return; // to avoid dividing by zero
    }
    // take and print the average gpa
      float average = sum / index;
      cout << "Average GPA: " << fixed << setprecision(2) << average << endl;
   }
  // still in the list
  else {
    // add the student's gpa to the sum, move to the next student
    sum += current->getValue()->getGpa();
    averageGPA(current->getNext(), ++index, sum);
  }
}

void deleteStudent(int targetID, Node* &head) {
  if (head == NULL) {
    cout << "Student not found!" << endl;
  }
  Node* previous = head;
  Node* current = head->getNext();
  // for deleting head (current would see it first otherwise)
  if (previous->getValue()->getID() == targetID) {
    // if it's the only value there, the head is empty.
    if (current == NULL) {
      head = NULL;
      delete previous;
      return;
    }
    // otherwise, next node becomes the new head.
    else {
      head = current;
      delete previous;
      return;
    }
  }
  // main sequence
  if (current != NULL) {
    // is this the wanted node?
    if (current->getValue()->getID() == targetID) {
      // if it's the last one
      if (current->getNext() == NULL) {
	previous->setNext(NULL);
	delete current;
	return;
      }
      // if it's in the middle, skip it and delete it
      else {
	previous->setNext(current->getNext());
	delete current;
	return;
      }
    }
    // not the right student, move to the next
    deleteStudent(targetID, current);
  }
}
