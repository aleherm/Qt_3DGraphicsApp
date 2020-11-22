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
    scene3D.AddPointToObject(Point3D(-50, 30, 140)); // 4
    scene3D.AddPointToObject(Point3D(-200, 30, 140)); // 5
    scene3D.AddPointToObject(Point3D(-200, 170, 140)); // 6
    scene3D.AddPointToObject(Point3D(-50, 170, 140)); // 7

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
    }
    else
    {
        scene3D.ApplyTransformation(transf);
        scene3D.Display(painter);
        painter.drawText(rect(), Qt::AlignCenter, message);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // translatii
    if(event->key() == Qt::Key_W)
    {
        scene3D.Translate(0, -10, 0);
    }
    if(event->key() == Qt::Key_S)
    {
        scene3D.Translate(0, 10, 0);
    }
    if(event->key() == Qt::Key_D)
    {
        scene3D.Translate(10, 0, 0);
    }
    if(event->key() == Qt::Key_A)
    {
        scene3D.Translate(-10, 0, 0);
    }

    // scalari
    if(event->key() == Qt::Key_Plus)
    {
        scene3D.ScaleOrigin(1.1, 1.1, 1.1);
    }
    if(event->key() == Qt::Key_Minus)
    {
        scene3D.ScaleOrigin(0.9, 0.9, 0.9);
    }

    if(event->key() == Qt::Key_O)
    {
        scene3D.ScalePoint(0.9, 0.9, 0.9, Point3D(100, 100, 100));
    }

    if(event->key() == Qt::Key_P)
    {
        scene3D.ScalePoint(1.1, 1.1, 1.1, Point3D(100, 100, 100));
    }

    // rotatii
    if(event->key() == Qt::Key_Right)
    {
        scene3D.RotateOz(0.1);
    }
    if(event->key() == Qt::Key_Left)
    {
        scene3D.RotateOz(-0.1);
    }
    if(event->key() == Qt::Key_Up)
    {
        scene3D.RotateOx(0.1);
    }
    if(event->key() == Qt::Key_Down)
    {
        scene3D.RotateOx(-0.1);
    }
    if(event->key() == Qt::Key_Comma)
    {
        scene3D.RotateOy(0.1);
    }
    if(event->key() == Qt::Key_Period)
    {
        scene3D.RotateOy(-0.1);
    }

    // simetrii
    if(event->key() == Qt::Key_1)
    {
        this->message = "xOy symmetry";
        scene3D.Symmetry(1, 1, -1);
    }
    if(event->key() == Qt::Key_2)
    {
        this->message = "yOz symmetry";
        scene3D.Symmetry(-1, 1, 1);
    }
    if(event->key() == Qt::Key_3)
    {
        this->message = "zOx symmetry";
        scene3D.Symmetry(1, -1, 1);
    }

    if(event->key() == Qt::Key_4)
    {
        this->message = "Ox symmetry";
        scene3D.Symmetry(1, -1, -1);
    }
    if(event->key() == Qt::Key_5)
    {
        this->message = "Oy symmetry";
        scene3D.Symmetry(-1, 1, -1);
    }
    if(event->key() == Qt::Key_6)
    {
        this->message = "Oz symmetry";
        scene3D.Symmetry(-1, -1, 1);
    }
    if(event->key() == Qt::Key_7)
    {
        this->message = "O symmetry";
        scene3D.Symmetry(-1, -1, -1);
    }

    if(event->key() == Qt::Key_Z)
    {
        this->message = "plane symmetry";
        scene3D.SymmetryPlane(10, 10, 0, 0.1, 0.1);
    }

    repaint();
}
