#include "widget.h"
#include <QApplication>


#include <fstream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

//    Algorytm problem;
//    problem.Start();

//    cout << "Koniec programu " << endl;
    return a.exec();
}
