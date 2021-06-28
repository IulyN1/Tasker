#pragma once
#include "Repo.h"

class Service
{
private:
	Repo& repo;
public:
	//Constructor for the Service class
	//repo - object of type Repo
	Service(Repo& repo) :repo{ repo } {}

	//Default constructor for class Service
	Service() = default;

	//Copy constructor deleted for Service
	Service(const Service& ot) = delete;

	//Function that returns all the tasks
	const vector<Task>& get_all() const {
		return repo.get_all();
	}

	//Function that adds a new task based on the user input
	//name - string
	void add_task(const string& name);

	//Function that modifies the state of a task
	//t - object of type Task
	//state - string
	void modify_state(const Task& t,const string& state);
};

