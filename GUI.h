#pragma once
#include "Service.h"
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qlistview.h>
#include <qstringlistmodel.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qtoolbar.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>

class GUI: public QMainWindow
{
	Q_OBJECT

protected slots:
	void onAdd();

private:
	Service& srv;
	QListView* pendingTasks = new QListView;
	QListView* completedTasks = new QListView;

	QWidget* main = new QWidget;
	QLabel* lbPending = new QLabel{ "Pending tasks" };
	QLabel* lbCompleted = new QLabel{ "Completed tasks" };

	QToolBar* toolbar = new QToolBar;
	QAction* addAct = new QAction;
	QLineEdit* taskName = new QLineEdit;
	QAction* markComplete = new QAction;
	QAction* markPending = new QAction;

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
	GUI(Service& srv) : srv{ srv } {
		initGui();
		connectSignals();
		setInitialState();
	}
};

