#include <QtWidgets/QApplication>
#include "UI.h"
#include "Repo.h"
#include "Service.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo{ "tasks.txt" };
    Service srv{ repo };
    //UI* w = new UI{ srv };
    GUI* w = new GUI{ srv };
    w->show();
    return a.exec();
}
