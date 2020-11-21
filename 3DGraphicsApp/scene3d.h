#ifndef SCENE3D_H
#define SCENE3D_H
#include <QVector>
#include <QPainter>
#include "point3d.h"
#include "object3d.h"

class Scene3D
{
    QVector<Object3D> m_objects3D;
    Object3D m_currentObject;
public:
    Scene3D();
    Scene3D(int w, int h);
    void Display(QPainter& painter);
    void StartObject();
    void AddPointToObject(Point3D p3D);
    void AddPolygonToObject(QVector<int> indices, int color);
    void FinishObject();

    void Translate(double dx, double dy, double dz);
    void RotateOz(double alfa);
    // scalari, simetrii, rotatii etc. scena

    void setWindowCoordinates(int width, int height);
};

#endif // SCENE3D_H
