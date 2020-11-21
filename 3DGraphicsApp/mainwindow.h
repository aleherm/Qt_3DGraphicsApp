#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QVector3D>
#include <QPainter>
#include <QKeyEvent>
#include "point3d.h"
#include "object3d.h"
#include "transformation.h"
#include "scene3d.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Transformation transf;
    Scene3D scene3D;
    bool start;

    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *event);
    void addCoordinates();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
