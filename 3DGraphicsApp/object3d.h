#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <QPoint>
#include <QVector>
#include <QPainter>
#include "point3d.h"
#include "transformation.h"


class Object3D
{
    double zp = 1000;
    int wWidth, wHeight;

    QVector<Point3D> m_points3D;
    QVector<QPoint> m_points2D;

    QVector<QVector<int>> m_polygonIndices;
    QVector<int> m_colors;

    Transformation transformation3D;

    QPoint PerspectiveProjection(Point3D p3D);
public:
    Object3D();
    void setWindowCoordinates(int width, int height);

    // specific
    void AddPoint3D(Point3D p3D);
    void AddPolygon(QVector<int> polygonIndices, int color);
    void Translate(double dx, double dy, double dz);
    void Scale(double sx, double sy, double sz);
    void RotateOz(double alfa);
    void RotateOy(double beta);
    void RotateOx(double gama);
    // scalari, simetrii, rotatii etc.

    void SetTransformation(Transformation transf)
    {
        this->transformation3D = transf;
    }

    // basic
    void ApplyTransformation();
    void Display(QPainter& painter);
    void Reset();

    Point3D GetGravityCenterPoint();
};

#endif // OBJECT3D_H
