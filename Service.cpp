#include "Service.h"
#include <algorithm>

void Service::add_task(const string& name) {
	Task t{ name };
	repo.add(t);
}

void Service::modify_state(const Task& t, const string& state) {
	repo.modify(t, state);
}