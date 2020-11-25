#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QColor>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->start=true;
    this->isZBuffering = false;
    //this->MakeCube();
    this->MakeSphere();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MakeCube()
{
    scene3D.SetWindowCoordinates(width(), height());
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

    scene3D.AddPolygonToObject({ 0, 1, 3, 2}, QColor(34,139,34));
    scene3D.AddPolygonToObject({ 1, 5, 7, 3}, QColor(34,139,34));
    scene3D.AddPolygonToObject({ 4, 6, 7, 5}, QColor(34,139,34));
    scene3D.AddPolygonToObject({ 0, 2, 6, 4}, QColor(34,139,34));
    scene3D.AddPolygonToObject({ 0, 4, 5, 1}, QColor(34,139,34));
    scene3D.AddPolygonToObject({ 2, 3, 7, 6}, QColor(34,139,34));

    scene3D.FinishObject();
}

void MainWindow::MakeSphere()
{
    scene3D.SetWindowCoordinates(width(), height());
    scene3D.StartObject();

    uint rows = 10;
    uint cols = 10;
    uint northPolePos = (rows - 1) * cols;
    uint southPolePos = northPolePos + 1;

    float radius = 200;

    float alphaStart = 0;
    float alphaEnd = M_PI;
    float alphaStep = (alphaEnd - alphaStart) / rows;

    float betaStart = 0;
    float betaEnd = 2 * M_PI;
    float betaStep = (betaEnd - betaStart) / cols;

    // body
    for (int i = 1; i < rows; ++i)
    {
        float alpha = alphaStart + alphaStep * i;
        float cosAlpha = cos(alpha);
        float sinAlpha = sin(alpha);

        for (int j = 0; j < cols; ++j)
        {
            float beta = betaStart + betaStep * j;

            float sinBeta = sin(beta);
            float cosBeta = cos(beta);

            Point3D point;
            point.x = radius * cosBeta * sinAlpha;
            point.y = radius * cosAlpha;
            point.z = radius * sinBeta * sinAlpha;

            scene3D.AddPointToObject(point);
        }
    }

    //north pole
    scene3D.AddPointToObject(Point3D(0, radius, 0));
    //south pole
    scene3D.AddPointToObject(Point3D(0, -radius, 0));

    QVector<int> polygon;
    // body
    for (int i = 0; i < rows - 1 - 1; ++i)
    {
        for (int j = 0; j < cols - 1; ++j)
        {
            polygon.clear();
            polygon.push_back(i*cols + j + 1);
            polygon.push_back((i + 1)*cols + j + 1);
            polygon.push_back((i + 1)*cols + j);
            polygon.push_back(i*cols + j);
            scene3D.AddPolygonToObject(polygon, QColor(200, 0, 0));
        }

        polygon.clear();
        polygon.push_back(i *cols);
        polygon.push_back((i + 1)*cols);
        polygon.push_back((i + 2)*cols - 1);
        polygon.push_back((i + 1)*cols - 1);
        scene3D.AddPolygonToObject(polygon, QColor(200, 0, 0));
    }

    // north pole triangles
    for (int j = 0; j < cols - 1; ++j)
    {
        polygon.clear();
        polygon.push_back(northPolePos);
        polygon.push_back(j + 1);
        polygon.push_back(j);
        scene3D.AddPolygonToObject(polygon, QColor(200, 0, 0));
    }
    polygon.clear();
    polygon.push_back(northPolePos);
    polygon.push_back(0);
    polygon.push_back(cols-1);
    scene3D.AddPolygonToObject(polygon, QColor(200, 0, 0));

    // south pole triangles
    for (int j = 0; j < cols - 1; ++j)
    {
        polygon.clear();
        polygon.push_back(southPolePos);
        polygon.push_back((rows - 2)*cols + j);
        polygon.push_back((rows - 2)*cols + j + 1);
        scene3D.AddPolygonToObject(polygon, QColor(200, 0, 0));
    }
    polygon.clear();
    polygon.push_back(southPolePos);
    polygon.push_back((rows - 1) * cols - 1);
    polygon.push_back((rows - 2) * cols);
    scene3D.AddPolygonToObject(polygon, QColor(200, 0, 0));

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
        this->message = "Zoom In - ORIGIN";
        scene3D.ScaleOrigin(1.1, 1.1, 1.1);
    }
    if(event->key() == Qt::Key_Minus)
    {
        this->message = "Zoom Out - ORIGIN";
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
        this->message = "ORIGIN symmetry";
        scene3D.Symmetry(-1, -1, -1);
    }

    if(event->key() == Qt::Key_Q)
    {
        this->message = "PLANE symmetry";
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
