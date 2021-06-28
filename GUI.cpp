#include "GUI.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qmessagebox.h>

void GUI::initGui() {
	QVBoxLayout* lyMain = new QVBoxLayout;
	main->setLayout(lyMain);

	QHBoxLayout* lyLabels = new QHBoxLayout;
	lyMain->addLayout(lyLabels);
	lyLabels->addWidget(lbPending);
	lyLabels->addWidget(lbCompleted);

	QHBoxLayout* lyList = new QHBoxLayout;
	lyMain->addLayout(lyList);
	lyList->addWidget(pendingTasks);
	lyList->addWidget(completedTasks);
}

void GUI::connectSignals() {
	pendingTasks->setModel(new QStringListModel);
	completedTasks->setModel(new QStringListModel);

	connect(addAct, &QAction::triggered, this, &GUI::onAdd);
	connect(markComplete, &QAction::triggered, this, [=]() {
		if (pendingTasks->selectionModel()->selectedIndexes().isEmpty()) {
			QMessageBox::information(this, "Info", "Please select a pending task first!");
			return;
		}
		auto ind = pendingTasks->selectionModel()->selectedIndexes().at(0);
		auto task = pendingTasks->model()->data(ind);
		Task t{ task.toString().toStdString() };
		srv.modify_state(t, "yes");
		loadTasks(srv.get_all());
		});
	connect(markPending, &QAction::triggered, this, [=]() {
		if (completedTasks->selectionModel()->selectedIndexes().isEmpty()) {
			QMessageBox::information(this, "Info", "Please select a completed task first!");
			return;
		}
		auto ind = completedTasks->selectionModel()->selectedIndexes().at(0);
		auto task = completedTasks->model()->data(ind);
		Task t{ task.toString().toStdString() };
		srv.modify_state(t, "no");
		loadTasks(srv.get_all());
		});
}

void GUI::setInitialState() {
	main->setStyleSheet("background-color: lightgrey");
	setCentralWidget(main);

	lbCompleted->setStyleSheet("font-size: 25px");
	lbPending->setStyleSheet("font-size: 25px");

	pendingTasks->setStyleSheet("QListView {font-size: 18px; font-weight: bold;}"
		"QListView::item { background-color: #C0392B; padding: 10%; border: 1px solid black;}"
		"QListView::item::hover { background-color: red; }");

	completedTasks->setStyleSheet("QListView {font-size: 18px; font-weight: bold;}"
		"QListView::item { background-color: green; padding: 10%; border: 1px solid black;}"
		"QListView::item::hover { background-color: lime; }");

	addToolBar(toolbar);
	addAct->setIcon(QIcon("add.png"));
	markPending->setIcon(QIcon("left.png"));
	markComplete->setIcon(QIcon("right.png"));
	toolbar->addAction(markComplete);
	toolbar->addAction(markPending);
	toolbar->addAction(addAct);
	toolbar->addWidget(taskName);
	loadTasks(srv.get_all());
}

void GUI::onAdd() {
	auto txt = taskName->text();
	if (txt == "") {
		QMessageBox::information(this, "Info", "Please enter a task name!");
		return;
	}
	srv.add_task(txt.toStdString());
	loadTasks(srv.get_all());
}

void GUI::loadTasks(const vector<Task>& tasks) {
	pendingTasks->model()->removeRows(0, pendingTasks->model()->rowCount());
	completedTasks->model()->removeRows(0, completedTasks->model()->rowCount());
	for (const auto& el : tasks) {
		if (el.get_completed() == "no") {
			pendingTasks->model()->insertRow(pendingTasks->model()->rowCount());
			QModelIndex ind = pendingTasks->model()->index(pendingTasks->model()->rowCount() - 1, 0);
			pendingTasks->model()->setData(ind, QString::fromStdString(el.get_name()));
		}
		else {
			completedTasks->model()->insertRow(completedTasks->model()->rowCount());
			QModelIndex ind = completedTasks->model()->index(completedTasks->model()->rowCount() - 1, 0);
			completedTasks->model()->setData(ind, QString::fromStdString(el.get_name()));
		}
	}
}