#include "Repo.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

void Repo::load() {
	string name,complete;
	ifstream in(filename);
	while (!in.eof()) {
		std::getline(in, name);
		if (in.eof())break;
		std::getline(in, complete);
		const Task t{ name,complete };
		tasks.push_back(t);
	}
	in.close();
}

void Repo::save() {
	ofstream out(filename);
	for (const auto& el : tasks) {
		out << el.get_name() << '\n';
		out << el.get_completed() << '\n';
	}
	out.close();
}

void Repo::add(const Task& t) {
	tasks.push_back(t);
	save();
}

void Repo::modify(const Task& t, const string& state) {
	auto it = std::find_if(tasks.begin(), tasks.end(), [t](const Task& task) {
		if (t.get_name() == task.get_name()) {
			return true;
		}
		return false;
		});
	if (it != tasks.end()) {
		Task& t = *it;
		t.set_completed(state);
	}
	save();
}