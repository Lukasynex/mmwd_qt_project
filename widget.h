#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qcustomplot.h"
#include "Algorytm.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    //QProcess *myProcess;
    Algorytm * problem;
    explicit Widget(QWidget *parent = 0);
    void setupLineStyleDemo(QCustomPlot *customPlot);
    void rysujFunkcje();

    ~Widget();

private slots:
    void on_distance_matrix_load_3_clicked();

    void on_price_matrix_load_3_clicked();

    void on_distance_matrix_save_3_clicked();

    void on_price_matrix_save_3_clicked();

    void on_primary_vector_load_3_clicked();

    void on_primary_vector_save_3_clicked();

    void on_pushButton_3_clicked();

    void on_Podglad_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
