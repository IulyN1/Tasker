#pragma once
#include <string>
using std::string;
#include <iostream>

class Task {
private:
	string name;
	string completed;
public:
	//Constructor for Task class
	//name - string
	//completed - string (yes or no)
	Task(const string& name,const string& completed) :name{ name }, completed{ completed }{}

	//Constructor for Task class
	//name - string
	Task(const string& name) :name{ name }, completed{ "no" }{}

	//Default constructor for class Task
	Task() = default;

	//Function that returns the name of a task
	const string& get_name() const {
		return name;
	}

	//Function that returns the completion state of a task
	const string& get_completed() const {
		return completed;
	}

	//Function that sets the completion state of a task
	//compl - string (yes or no))
	void set_completed(const string& compl) {
		completed = compl;
	}

	//Copy constructor for class Task
	//ot - object of type Task
	Task(const Task& ot) :name{ ot.name }, completed{ ot.completed }{}
};