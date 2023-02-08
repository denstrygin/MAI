#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QStyle>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    h = 0.00001, axic = 5;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString aQstr = ui->lineA->text();
    QString bQstr = ui->lineB->text();
    if (aQstr.isEmpty() || bQstr.isEmpty()) {
        ui->label->setText("Enter all values for variables A and B");
        ui->label->setStyleSheet("QLabel {; color : red;}");
    } else {
        double a = aQstr.toDouble();
        double b = bQstr.toDouble();
        //Проверяем условие a,b > 0
        if (a <= 0 || b <= 0) {
            ui->label->setText("Incorrect input");
            ui->label->setStyleSheet("QLabel {; color: red;}");
        } else {
            //Подбираем масштаб графика
            if (a > b)
                axic = a + 2;
            else
                axic = b + 2;

            //Выводем текст об успехе
            ui->label->setText("Success");
            ui->label->setStyleSheet("QLabel {; color : green;}");

            //Настраиваем оси графика
            ui->widget->xAxis->setRange(-axic, axic);
            ui->widget->yAxis->setRange(-axic, axic);

            //Заполняем вектор точками графика верхнего полушария
            for (X = -a; X <= a; X += h) {
                x.push_back(X);
                y.push_back(qSqrt((1 - qPow(X, 2)/qPow(a, 2)) * qPow(b, 2)));
                y1.push_back(-qSqrt((1 - qPow(X, 2)/qPow(a, 2)) * qPow(b, 2)));
            }

            //Передаём график на виджет и передаём в график точки вектора
            ui->widget->addGraph();
            ui->widget->graph(0)->setData(x, y);

            ui->widget->addGraph();
            ui->widget->graph(1)->setData(x, y1);

            //Рисуем график
            ui->widget->replot();

            //Подключаем методы масштаба и перемещени по графику
            ui->widget->setInteraction(QCP::iRangeZoom, true);
            ui->widget->setInteraction(QCP::iRangeDrag, true);

            //Освобождаем вектор для повторного использования
            x.clear();
            y.clear();
            y1.clear();

            //Выводим формулу на label
            ui->label2->setText("x^2/" + QString("%1").arg(a) + "^2 + y^2/" + QString("%1").arg(b) + "^2 = 1");
        }
    }
}

