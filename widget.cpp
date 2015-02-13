#include "widget.h"
#include "ui_widget.h"
#include "qcustomplot.h"
#include <QProcess>
#include <iostream>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <fstream>
#include "Algorytm.h"
#include<Vector>
#include <cstdlib>


using std::vector;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->warning->setText("");
}


void Widget::setupLineStyleDemo(QCustomPlot *customPlot){

    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    QPen pen;

      QVector<double> x(101), y(101); // initialize with entries 0..100
      for (int i=0; i<101; ++i)
      {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i];  // let's plot a quadratic function
      }
      // create graph and assign data to it:
      customPlot->addGraph();
      customPlot->graph(0)->setData(x, y);
      // give the axes some labels:
      customPlot->xAxis->setLabel("x");
      customPlot->yAxis->setLabel("y");
      // set axes ranges, so we see all data:
      customPlot->xAxis->setRange(-1, 1);
      customPlot->yAxis->setRange(0, 1);
      pen.setColor(QColor(0,0,255));
      customPlot->graph()->setPen(pen);
      customPlot->graph()->setName("Wartosc funkcji celu");
      customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
      customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
      // generate data:
      ///////////////////////////////////////////////////////////////////////////////////////


      customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
      customPlot->xAxis->scaleRange(1.1, customPlot->xAxis->range().center());

      // set blank axis lines:
      customPlot->xAxis->setTicks(true);
      customPlot->yAxis->setTicks(true);
      customPlot->xAxis->setTickLabels(true);
      customPlot->yAxis->setTickLabels(true);
      // make top right axes clones of bottom left axes:
      customPlot->axisRect()->setupFullAxesBox();
      //make dragable and zoomable
      customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_distance_matrix_load_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                 tr("Wczytaj macierz odległości"), "",
                 tr("Pliki tekstowe (*.txt);;All Files (*)"));
        if (fileName.isEmpty())
                 return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadWrite))
                QMessageBox::information(this, tr("Nie można otworzyć pliku."), file.errorString());
            QTextStream in(&file);
            ui->EditDistanceMatrix_3->setText(in.readAll());
        }
}


void Widget::on_price_matrix_load_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                 tr("Wczytaj macierz cen"), "",
                 tr("Pliki tekstowe (*.txt);;All Files (*)"));
        if (fileName.isEmpty())
                 return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadWrite))
                QMessageBox::information(this, tr("Nie można otworzyć pliku."), file.errorString());
            QTextStream in(&file);
            ui->EditPriceMatrix_3->setText(in.readAll());
        }
}

void Widget::on_distance_matrix_save_3_clicked()
{
    QFile outfile;
    if (ui->matrix_name->text().length() == 0)
        outfile.setFileName("macierz_odleglosci.txt");
    else{
        QString fileName = ui->matrix_name->text();
        fileName.append(".txt");
        outfile.setFileName(fileName);
    }
    outfile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&outfile);
    out << ui->EditDistanceMatrix_3->toPlainText() << endl;
}


void Widget::on_price_matrix_save_3_clicked()
{
    QFile outfile;
    if (ui->price_name->text().length() == 0)
        outfile.setFileName("macierz_cen.txt");
    else{
        QString fileName = ui->price_name->text();
        fileName.append(".txt");
        outfile.setFileName(fileName);
    }
     outfile.open(QIODevice::WriteOnly | QIODevice::Text);
     QTextStream out(&outfile);
     out << ui->EditPriceMatrix_3->toPlainText() << endl;
}


void Widget::on_primary_vector_load_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                tr("Wczytaj wektor początkowy"), "",
                tr("Pliki tekstowe (*.txt);;All Files (*)"));
       if (fileName.isEmpty())
                return;
       else {
           QFile file(fileName);
           if (!file.open(QIODevice::ReadWrite))
               QMessageBox::information(this, tr("Nie można otworzyć pliku."), file.errorString());
           QTextStream in(&file);
           ui->EditPrimaryVector_3->setText(in.readAll());
       }
}

void Widget::on_primary_vector_save_3_clicked()
{
    QFile outfile;
    if (ui->matrix_name->text().length() == 0)
        outfile.setFileName("wektor_poczatkowy.txt");
    else{
        QString fileName = ui->vector_name->text();
        fileName.append(".txt");
        outfile.setFileName(fileName);
    }
    outfile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&outfile);
    out << ui->EditPrimaryVector_3->toPlainText() << endl;
}

void Widget::on_Podglad_clicked(){
    QString fileName = ui->matrix_name->text();
    fileName.append(".txt");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite))
        QMessageBox::information(this, tr("Nie można otworzyć pliku."), file.errorString());
    QTextStream in(&file);
    ui->EditDistanceMatrix_3->setText(in.readAll());

    fileName = ui->price_name->text();
    fileName.append(".txt");
    QFile file1(fileName);
    if (!file1.open(QIODevice::ReadWrite))
        QMessageBox::information(this, tr("Nie można otworzyć pliku."), file1.errorString());
    QTextStream in1(&file1);
    ui->EditPriceMatrix_3->setText(in1.readAll());

    fileName = ui->vector_name->text();
    fileName.append(".txt");
    QFile file2(fileName);
    if (!file2.open(QIODevice::ReadWrite))
        QMessageBox::information(this, tr("Nie można otworzyć pliku."), file2.errorString());
    QTextStream in2(&file2);
    ui->EditPrimaryVector_3->setText(in2.readAll());
}

void Widget::on_pushButton_3_clicked(){
        ui->wektorOptymalny->setText("");
        ui->FCValue->setText("");
        ui->progressBar->setValue(0);
        ui->pushButton->setEnabled(false);
        bool ok, ko, oo, kk;
        int sklepy = ui->lineEdit_sklepy->text().toInt(&ok, 10);
        int iteracje = ui->lineEdit_iteracje->text().toInt(&oo, 10);
        int produkty = ui->lineEdit_produkty->text().toInt(&ko, 10);
        int tabu = ui->lineEdit_tabu->text().toInt(&kk, 10);
        if(ui->nazwa_pliku->text().length()==0){
            ui->warning->setText("Podaj nazwę pliku wyjściowego!");
            return;
        }
        if(ok && kk && ko && oo)
            problem = new Algorytm(sklepy, produkty, tabu, iteracje);
        else
            problem = new Algorytm(20,10,100,10000);
        cout << "\niteracje " << iteracje << "\ntabu " << tabu;
        problem->setBar(ui->progressBar);
        QString string1 = ui->nazwa_pliku->text();
        QString string2 = ui->vector_name->text();
        QString string3 = ui->matrix_name->text();
        QString string4 = ui->price_name->text();
        if(string2.length()==0 || string3.length()==0|| string4.length()==0){
           string2 = "droga_startowa";
           string3 = "macierz_drog_high";
           string4 = "macierz_cen_high";
        }

        string1.append(".txt");
        string2.append(".txt");
        string3.append(".txt");
        string4.append(".txt");

        problem->setOutputName(string1);
        problem->setInputName(string2);
        problem->setDistanceName(string3);
        problem->setPricesName(string4);


        problem->Start();

    //    for(int i=0;i<iteracje;i++)
    //        ui->progressBar->setValue(100*i/(iteracje-1));

        //connect(problem, SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)));

        cout << "\niteracje " << iteracje << "\ntabu " << tabu;

        ui->FCValue->setText(QString::number(problem->najlepsza_wartosc_f_celu));

        for(int i = 0; i < problem->dane->MAX_ILOSC_SKLEPOW; i++)
            ui->wektorOptymalny->append(QString::number(problem->droga_najlepsza[i].id_sklepu) + " " + QString::number(problem->droga_najlepsza[i].id_prod));

        ui->pushButton->setEnabled(true);
         rysujFunkcje();
        //setupLineStyleDemo(ui->customPlot);
        ui->customPlot_3->repaint();

        ui->warning->setText("");

}

void Widget::rysujFunkcje(){\
    QCustomPlot* customPlot = ui->customPlot_3;
    customPlot->clearItems();
        customPlot->clearGraphs();
        customPlot->clearPlottables();

        customPlot->legend->setVisible(true);
        customPlot->legend->setFont(QFont("Helvetica", 9));
        QPen pen(QColor(0,0,255));
        customPlot->addGraph();
     //   pen.setColor(QColor(0,0,255));
        customPlot->graph()->setPen(pen);
        customPlot->graph()->setName("Wartosc funkcji celu");
        customPlot->graph()->setLineStyle((QCPGraph::LineStyle)1);
        customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));

          int iter = problem->ilosc_iteracji_arg;
          QVector<double> x(iter), y(iter);
          QString string1 = ui->nazwa_pliku->text();
          string1.append(".txt");
          QFile file(string1);

          if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
              std::cerr << "tu sie zepsulo!" << std::endl;
          QTextStream in(&file);


          int index=0;
          while (!in.atEnd()){
            if(in.readLine().at(0)=='0'){
                in>> x[index]>> y[index];
                for(int i=1; i < iter; i++){
                    in >> x[i] >> y[i];
                    std::cout << x[i] << ", "<< y[i] << std::endl;
                  }
              }
          }

          /*QVector<double> xx(iter), yy(iter);
          for(int i=0;i<iter;i++){
              xx[i] = (double)x[i];
              yy[i] = (double)y[i];
          }*/
          customPlot->graph()->setData(x,y);
          customPlot->graph()->rescaleAxes(true);

          customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
          customPlot->xAxis->scaleRange(1.1, customPlot->xAxis->range().center());

          // set blank axis lines:
          customPlot->xAxis->setTicks(true);
          customPlot->yAxis->setTicks(true);
          customPlot->xAxis->setTickLabels(true);
          customPlot->yAxis->setTickLabels(true);
          // make top right axes clones of bottom left axes:
          customPlot->axisRect()->setupFullAxesBox();
          //make dragable and zoomable
          customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void Widget::on_pushButton_clicked()
{
    QFile plikWyj;
    QString str = ui->lineEditPlik->displayText();
    str.append(".txt");
    plikWyj.setFileName(str);
    plikWyj.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream tekst(&plikWyj);
    if(!ui->czyWektor->isChecked()){
    for(int i = 0; i < ui->lineEditWiersze->text().toInt(); i++){
        for(int j = 0; j < ui->lineEditKolumny->text().toInt(); j++){
            if(i == j && ui->checkBoxPrzekatna->isChecked()) tekst << "-1 ";
            else tekst << rand()%(ui->lineEditMax->text().toInt() - ui->lineEditMin->text().toInt()) +
                          ui->lineEditMin->text().toInt() << " ";
        }
        tekst << endl;
    }
    }
    else{

        bool ok;
        int row = ui->lineEditWiersze->text().toInt(&ok,10);
        int col = ui->lineEditKolumny->text().toInt(&ok,10);
        vector<int> sklepy;
        vector<int> produkty;
        sklepy.reserve(row);
        produkty.reserve(row);

        for(int i = 1; i <= row; i++){
           sklepy[i-1] = i;
           if(i < col)
              produkty[i-1] = i;
           else
               produkty[i-1] = 0;
        }
        int tmp, los1, los2;
        int i = 0;
        while(i < 100){
            los1 = rand()%row;
            los2 = rand()%row;
            if (los1 != los2){
                tmp = sklepy[los1];
                sklepy[los1] = sklepy[los2];
                sklepy[los2] = tmp;

                tmp = produkty[los1];
                produkty[los1] = produkty[los2];
                produkty[los2] = tmp;

                i++;
            }

        }

        for(int j = 0; j < row; j++){
           tekst << sklepy[j] << " " << produkty[j] << endl;
        }
    }



    plikWyj.close();
}
