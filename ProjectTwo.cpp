//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Nicole Swanson
// Description : Project 2
//============================================================================


#include <iostream>
#include <fstream>
#include "ProjectTwo.hpp"
#include <vector>
#include <string>

using namespace std;

/*definea structure to hold bid information*/
struct Course {
	string courseNum;
	string courseName;
	string prereq;
	Course(){}
};

/*Internal structure for tree node*/
struct Node {
	Course course;
	Node* left;
	Node* right;

	/*default constructor*/
	Node() {
		left = nullptr;
		right = nullptr;
	}

	/*initialize with a course*/
	Node(Course aCourse) : Node() {
		course = aCourse;
	}
};

/*define a class containing data to impliment a search tree*/
class BinarySearchTree {

private:
	Node* root;
	void addNode(Node* node, Course course);
	void printSchedule(Node* node);
	void printCourseInfo(Node* node, string couseNum);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void Remove(Node* node);
	void Insert(Course course);
	int numPrereqCourse(Course course);
	void printSchedule();
	void printCourseInfo(string courseNum);
};

/*default constructor*/
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

/*deconstructer to remove nodes*/
BinarySearchTree::~BinarySearchTree() {
	Remove(root);
}

/*removes node from tree*/
void BinarySearchTree::Remove(Node* node) {
	if (node) {
		Remove(node->left);
		Remove(node->right);
		delete node;
	}
}

/*insert node into tree*/
void BinarySearchTree::Insert(Course course) {
	if (root == nullptr) {
		root = new Node(course);
	}
	/*if cannot insert add node*/
	else {
		addNode(root, course);
	}
}

/*returns number of course prerequisites*/
int BinarySearchTree::numPrereqCourse(Course course) {
	int count = 0;
	for (unsigned int i = 0; i < course.prereq.size(); i++) {
		if (prereq.at(i).length() > 0)
			count++;
	}
		return count;
}

/*utilize private method of tree*/
void BinarySearchTree::printSchedule() {
	this->printSchedule(root);
}

/*sends to search the tree*/
void BinarySearchTree::printCourseInfo(Node* node, string courseNum) {
	this->printCourseInfo(root, courseNum);
}

/*determines and sets alphanumeric location by searching*/
void BinarySearchTree::addNode(Node* node, Course course) {
	if (node->course.courseNum.compare(course.courseNum) > 0) {
		if (node->left == nullptr) {
			node->left = new Node(course);
		}
		else {
			addNode(node->left, course);
		}
	}
	else if (node->right == nullptr) {
			node->right = new Node(course);
		}
		else {
			addNode(node->right, course);
		}
	}

/*prints the courses in order*/
void BinarySearchTree::printSchedule(Node* node) {
	if (node != nullptr) {
		printSchedule(node->left);
		cout << node->course.courseNum << ", " << node->course.courseName << endl;
		printSchedule(node->right);
	}
	return;
}

/*prints courses and prerequisites*/
void BinarySearchTree::printCourseInfo(Node* current, string courseNum) {
	while (current != nullptr) {
		if (current->course.courseNum.compare(courseNum) == 0) {
			cout << endl << current->course.courseNum << ", " << current->course.courseName << endl;
			unsigned int size = numPrereqCourse(current->course);
			cout << "Prerequesites: ";
			unsigned int i = 0;
			for (unsigned int i = 0; i < size; ++i) {
				cout << current->course.prereq.at(i);
				if (i != size - 1) {
					cout << ", ";
				}
				if (i == 0) {
					cout << "No prerequsites required." << endl;
					return;
				}
				else if (courseNum.compare(current->course.courseNum) < 0) {
					current = current->left;
				}
				else {
					current = current->right;
				}
				cout << "Course " << courseNum << "not found." << endl;
			}
		}

/*load courses from choice*/
bool loadCourse(string csvPath, BinarySearchTree * BinarySearchTree);{
/*open file and insert into tree by way of vector strings*/
		ifstream courseFile (csvPath);
		if (courseFile.is_open()) {
			while (!courseFile.eof()) {
				vector<string>printCourseInfo;
				string courseData;
				getline(courseFile, courseData);
				while (courseData.length() > 0) {
					unsigned int comma = courseData.find(',');
					if (comma < 100) {
						printCourseInfo.push_back(courseData.substr(0, comma));
						courseData.erase(0, comma + 1);
					}
					else {
						printCourseInfo.push_back(courseData.substr(0, courseData.length()));
						courseData = "";
					}
				}
				Course course;
				course.courseNum = printCourseInfo[0];
				course.courseName = printCourseInfo[1];
				for (unsigned int i = 2; i < printCourseInfo.size(); i++) {
					course.prereq.push_back(printCourseInfo[i]);
				}
				BinarySearchTree->Insert(Course course);
			}
			/*close file after inserting course values into tree*/
			courseFile.close();
			return;
		}
	}
	
/*create display menu*/
void displayMenu(BinarySearchTree);
	cout << "Welcome to the course planner." << endl;
	int choice = 0;
	while (choice != 9) {
		cout << endl;
		cout << "1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit" << endl;
		cout << endl;
		cout << "What would you like to do? ";
		/*get input from user*/
		cin >> choice;

		/*respond to user input*/
		switch (choice) {
		case 1:
			loadCourse();
			break;
		case 2:
			printSchedule();
			break;
		case 3:
			printCourseInfo();
			break;
		case 9:
			cout << "Thank you for using the course planner!" << endl;
			break;
		default:
			cout << choice << " is not a valid option." << endl;
			break;
		}
	}

return;
}