#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->start=true;
    this->isZBuffering = false;
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

    // puncte fata
    scene3D.AddPointToObject(Point3D(-100, -100, -700));
    scene3D.AddPointToObject(Point3D(100, -100, -700));
    scene3D.AddPointToObject(Point3D(-100, 100, -700));
    scene3D.AddPointToObject(Point3D(100, 100, -700));

    // puncte spate
    scene3D.AddPointToObject(Point3D(-100, -100, -900));
    scene3D.AddPointToObject(Point3D(100, -100, -900));
    scene3D.AddPointToObject(Point3D(-100, 100, -900));
    scene3D.AddPointToObject(Point3D(100, 100, -900));

    scene3D.AddPolygonToObject({ 0, 1, 3, 2}, 255);
    scene3D.AddPolygonToObject({ 1, 5, 7, 3}, 255);
    scene3D.AddPolygonToObject({ 4, 6, 7, 5}, 255);
    scene3D.AddPolygonToObject({ 0, 2, 6, 4}, 255);
    scene3D.AddPolygonToObject({ 0, 4, 5, 1}, 255);
    scene3D.AddPolygonToObject({ 2, 3, 7, 6}, 255);

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
        QFont bold("Verdana", 20);
        bold.setBold(true);
        painter.setFont(bold);
        painter.drawText(rect(), Qt::AlignHCenter, message);
        if(isZBuffering)
        {
            scene3D.ZBufferingDisplay(painter);
            return;
        }
        scene3D.ApplyTransformation(transf);
        scene3D.Display(painter);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // translatii
    if(event->key() == Qt::Key_W)
    {
        this->message = "Move UP";
        scene3D.Translate(0, -10, 0);
    }
    if(event->key() == Qt::Key_S)
    {
        this->message = "Move DOWN";
        scene3D.Translate(0, 10, 0);
    }
    if(event->key() == Qt::Key_D)
    {
        this->message = "Move RIGHT";
        scene3D.Translate(10, 0, 0);
    }
    if(event->key() == Qt::Key_A)
    {
        this->message = "Move LEFT";
        scene3D.Translate(-10, 0, 0);
    }

    // scalari
    if(event->key() == Qt::Key_Plus)
    {
        this->message = "Zoom In";
        scene3D.ScaleOrigin(1.1, 1.1, 1.1);
    }
    if(event->key() == Qt::Key_Minus)
    {
        this->message = "Zoom Out";
        scene3D.ScaleOrigin(0.9, 0.9, 0.9);
    }

    if(event->key() == Qt::Key_O)
    {
        this->message = "Zoom Out - POINT";
        scene3D.ScalePoint(0.9, 0.9, 0.9, Point3D(100, 100, 100));
    }

    if(event->key() == Qt::Key_P)
    {
        this->message = "Zoom In - POINT";
        scene3D.ScalePoint(1.1, 1.1, 1.1, Point3D(100, 100, 100));
    }

    // rotatii
    if(event->key() == Qt::Key_Period)
    {
        this->message = "OZ Rotation - RIGHT";
        scene3D.RotateOz(0.1);
    }
    if(event->key() == Qt::Key_Comma)
    {
        this->message = "OZ Rotation - LEFT";
        scene3D.RotateOz(-0.1);
    }
    if(event->key() == Qt::Key_Up)
    {
        this->message = "OX Rotation - UP";
        scene3D.RotateOx(0.1);
    }
    if(event->key() == Qt::Key_Down)
    {
        this->message = "OX Rotation - DOWN";
        scene3D.RotateOx(-0.1);
    }
    if(event->key() == Qt::Key_Left)
    {
        this->message = "OY Rotation - LEFT";
        scene3D.RotateOy(0.1);
    }
    if(event->key() == Qt::Key_Right)
    {
        this->message = "OY Rotation - RIGHT";
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
        this->message = "OX symmetry";
        scene3D.Symmetry(1, -1, -1);
    }
    if(event->key() == Qt::Key_5)
    {
        this->message = "OY symmetry";
        scene3D.Symmetry(-1, 1, -1);
    }
    if(event->key() == Qt::Key_6)
    {
        this->message = "OZ symmetry";
        scene3D.Symmetry(-1, -1, 1);
    }
    if(event->key() == Qt::Key_7)
    {
        this->message = "O symmetry";
        scene3D.Symmetry(-1, -1, -1);
    }

    if(event->key() == Qt::Key_Q)
    {
        this->message = "Plane symmetry";
        scene3D.SymmetryPlane(10, 10, 0, 0.1, 0.1);
    }

    if(event->key() == Qt::Key_Z)
    {
        this->message = "Z-Buffering";
        if(this->isZBuffering == true)
            this->isZBuffering = false;
        else
            this->isZBuffering = true;
    }

    repaint();
}
