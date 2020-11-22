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
    void ApplyTransformation(Transformation transf);

    void Translate(double dx, double dy, double dz);

    void ScaleOrigin(double sx, double sy, double sz);
    void ScalePoint(double sx, double sy, double sz, Point3D point);

    void RotateOz(double alfa);
    void RotateOx(double beta);
    void RotateOy(double gama);

    void Symmetry(double sx, double sy, double sz);
    void SymmetryPlane(double sx, double sy, double sz, double alfa, double beta);

    void setWindowCoordinates(int width, int height);

    QVector<Object3D> GetObjects3D()
    {
        return this->m_objects3D;
    }

    void SetObjects3D(QVector<Object3D> objects3D)
    {
        this->m_objects3D = objects3D;
    }
};

#endif // SCENE3D_H
