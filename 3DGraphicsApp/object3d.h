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
    Point3D lightVector = Point3D(-150, 150, 150);

    QVector<Point3D> m_points3D;
    QVector<QPoint> m_points2D;

    QVector<QVector<int>> m_polygonIndices;
    QVector<QColor> m_colors;

    Transformation transformation3D;

    // centrul de greutate
    Point3D GetGravityCenterPoint();

    // transforma un punct 3D intr-unul 2D
    QPoint PerspectiveProjection(Point3D p3D);
    bool IsVisiblePolygon(Point3D A0, Point3D A1, Point3D A2); // verifica daca poligonul este in fata/spate
    bool IsIlluminated(Point3D A0, Point3D A1, Point3D A2); // verifica daca poligonul este iluminat
    double GetIlluminatingFactor(Point3D A0, Point3D A1, Point3D A2); // factorul de iluminare cu care urmeaza sa se faca schimbarea culorii
    QColor GetAmbientalColor(QColor color, double lightFactor); // da culoarea finala dupa iluminare

    // vector operations
    double VectorNorm(Point3D v); // norma unui vector
    Point3D VectorialProduct(Point3D v1, Point3D v2); // produs vectorial
    double CrossProduct(Point3D v1, Point3D v2); // produs scalar
    Point3D GetPolygonNormal(Point3D A0, Point3D A1, Point3D A2); // normala unui plan dat de 3 puncte
public:
    Object3D();
    void setWindowCoordinates(int width, int height);

    // basic
    void AddPoint3D(Point3D p3D);
    void AddPolygon(QVector<int> polygonIndices, QColor color);
    void ApplyTransformation();
    void Display(QPainter& painter);
    void Reset();

    // transformari
    void Translate(double dx, double dy, double dz);

    void ScaleOrigin(double sx, double sy, double sz);
    void ScalePoint(double sx, double sy, double sz, Point3D point);

    void RotateOz(double alfa);
    void RotateOx(double beta);
    void RotateOy(double gama);

    void Symmetry(double sx, double sy, double sz);
    void SymmetryPlane(double sx, double sy, double sz, double alfa, double beta);

    void ZBufferingDisplay(QPainter& painter);
    void CutObject();

    void SetTransformation(Transformation& transf) // paseaza obiectul de transformare din mainwindow.cpp
    {
        this->transformation3D = transf;
    }
};

#endif // OBJECT3D_H
