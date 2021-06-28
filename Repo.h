#pragma once
#include "Task.h"
#include <vector>
using std::vector;

class Repo
{
private:
	string filename;
	vector<Task> tasks;

	//Private function that loads the tasks from the file
	void load();

	//Private function that saves the tasks to the file
	void save();
public:
	//Constructor for Repository
	//filename - string
	Repo(const string& filename) :filename{ filename } {
		load();
	}

	//Default constructor for Repo class
	Repo() = default;

	//Copy constructor for Repo class deleted
	Repo(const Repo& ot) = delete;

	//Function that returns all the tasks
	const vector<Task>& get_all() const {
		return tasks;
	}

	//Function that adds a new task
	//t - object of type Task
	void add(const Task& t);

	//Function that modifies the state of a task
	//t - object of type Task
	//state - string
	void modify(const Task& t, const string& state);
};

