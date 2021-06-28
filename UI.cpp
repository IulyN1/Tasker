#include "UI.h"
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qmessagebox.h>

void UI::initGui() {
	QVBoxLayout* ly = new QVBoxLayout;
	ly->addWidget(title);
	setLayout(ly);
	QHBoxLayout* lyAdd = new QHBoxLayout;
	lyAdd->addWidget(btnAdd);
	lyAdd->addWidget(taskName);
	ly->addLayout(lyAdd);
	ly->addLayout(lyTasks);
	ly->addStretch();
}

void UI::connectSignals() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, [=]() {
		auto txt = taskName->text();
		if (!txt.isEmpty()) {
			srv.add_task(txt.toStdString());
			int i{ 0 };
			for (int i = 0; i < (int)srv.get_all().size(); i++) {
				auto el = lyTasks->itemAt(0);
				lyTasks->removeItem(el);
			}
			loadTasks(srv.get_all());
		}
		else {
			QMessageBox::information(this, "Info", "Please give a name for the task!");
		}
		});
}

void UI::setInitialState() {
	loadTasks(srv.get_all());
	title->setAlignment(Qt::AlignHCenter);
}

void UI::loadTasks(const vector<Task>& tasks) {
	for (auto& el : tasks) {
		auto btn = new QCheckBox;
		auto txt = new QLabel{ QString::fromStdString(el.get_name()) };
		QHBoxLayout* lyBtn = new QHBoxLayout;
		lyBtn->addWidget(btn);
		lyBtn->addWidget(txt);
		lyTasks->addLayout(lyBtn);
		if (el.get_completed() == "yes") {
			btn->setChecked(true);
		}
		QObject::connect(btn, &QCheckBox::clicked, this, [=]() {
			if (el.get_completed() == "no") {
				srv.modify_state(el, "yes");
			}
			else {
				srv.modify_state(el, "no");
			}
			});
	}
}