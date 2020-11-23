#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <QPoint>
#include <QVector>
#include <QPainter>
#include <QColor>
#include "point3d.h"
#include "transformation.h"
#include "math.h"


class Object3D
{
    double zp = 1000, alfa = 2;
    float ambientLight = 0.2;
    int wWidth, wHeight;
    Point3D lightVector = Point3D(-250, 250, 250);

    QVector<Point3D> m_points3D;
    QVector<QPoint> m_points2D;

    QVector<QVector<int>> m_polygonIndices;
    QVector<QColor> m_colors;

    Transformation transformation3D;

    QPoint PerspectiveProjection(Point3D p3D);
    bool IsVisiblePolygon(Point3D A0, Point3D A1, Point3D A2);
    bool IsIlluminated(Point3D A0, Point3D A1, Point3D A2);
    Point3D VectorMutiplication(Point3D v1, Point3D v2);
    double GetIlluminatingFactor(Point3D A0, Point3D A1, Point3D A2);
    double VectorNorm(Point3D v);
    double ScalarMultiplication(Point3D v1, Point3D v2);
    Point3D GetPolygonNormal(Point3D A0, Point3D A1, Point3D A2);
    QColor GetAmbientalColor(QColor color, double lightFactor);
public:
    Object3D();
    void setWindowCoordinates(int width, int height);

    // specific
    void AddPoint3D(Point3D p3D);
    void AddPolygon(QVector<int> polygonIndices, QColor color);

    void Translate(double dx, double dy, double dz);

    void ScaleOrigin(double sx, double sy, double sz);
    void ScalePoint(double sx, double sy, double sz, Point3D point);

    void RotateOz(double alfa);
    void RotateOx(double beta);
    void RotateOy(double gama);

    void Symmetry(double sx, double sy, double sz);
    void SymmetryPlane(double sx, double sy, double sz, double alfa, double beta);

    void SetTransformation(Transformation transf)
    {
        this->transformation3D = transf;
    }

    // basic
    void ApplyTransformation();
    void Display(QPainter& painter);
    void Reset();

    Point3D GetGravityCenterPoint();
    void ZBufferingDisplay(QPainter& painter);
};

#endif // OBJECT3D_H
