#pragma once
#include "Service.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>

class UI: public QWidget
{
private:
	Service& srv;
	QLabel* title = new QLabel{ "My tasks" };
	QVBoxLayout* lyTasks = new QVBoxLayout;
	QLineEdit* taskName = new QLineEdit;
	QPushButton* btnAdd = new QPushButton{"+"};

	//Function that initializes the GUI
	void initGui();

	//Function that connects the signals of the widgets
	void connectSignals();

	//Function that sets the initial state of the app
	void setInitialState();

	//Function that loads the tasks
	//tasks - vector of objects of type Task
	void loadTasks(const vector<Task>& tasks);
public:
	//Constructor for the UI class
	//srv - object of type Service
	UI(Service& srv) :srv{ srv } {
		initGui();
		connectSignals();
		setInitialState();
	}
};

