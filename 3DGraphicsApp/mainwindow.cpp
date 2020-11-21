#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->start=true;
    this->addCoordinates();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addCoordinates()
{
    scene3D.setWindowCoordinates(width(), height());
    scene3D.StartObject();

    // puncte spate
    scene3D.AddPointToObject(Point3D(-50, 30, 0)); // 0
    scene3D.AddPointToObject(Point3D(-200, 30, 0)); // 1
    scene3D.AddPointToObject(Point3D(-200, 170, 0)); // 2
    scene3D.AddPointToObject(Point3D(-50, 170, 0)); // 3

    // puncte fata
    scene3D.AddPointToObject(Point3D(-50, 30, 300)); // 4
    scene3D.AddPointToObject(Point3D(-200, 30, 300)); // 5
    scene3D.AddPointToObject(Point3D(-200, 170, 300)); // 6
    scene3D.AddPointToObject(Point3D(-50, 170, 300)); // 7

    // perete spate
    scene3D.AddPolygonToObject({ 0, 1, 2, 3 }, 255);
    // perete fata
    scene3D.AddPolygonToObject({ 4, 5, 6, 7 }, 255);
    // perete sus
    scene3D.AddPolygonToObject({ 0, 1, 5, 4 }, 255);
    // perete jos
    scene3D.AddPolygonToObject({ 3, 2, 6, 7 }, 255);

    scene3D.FinishObject();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if(start)
    {
        scene3D.Display(painter);
        this->start=false;
        qDebug()<<start;
    }
    else
    {


    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        this->transf.Translate(0, -10, 0);
    }
    if(event->key() == Qt::Key_S)
    {
        this->transf.Translate(0, 10, 0);
    }
    if(event->key() == Qt::Key_D)
    {
        this->transf.Translate(-10, 0, 0);
    }
    if(event->key() == Qt::Key_A)
    {
        this->transf.Translate(10, 0, 0);
    }
    repaint();
}
