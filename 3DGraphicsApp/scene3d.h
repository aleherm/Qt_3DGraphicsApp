#ifndef SCENE3D_H
#define SCENE3D_H
#include <QVector>
#include <QPainter>
#include "point3d.h"
#include "object3d.h"

class Scene3D
{
    QVector<Object3D> m_objects3D; // vectorul de obiecte
    Object3D m_currentObject; // obiectul curent
public:
    Scene3D();

    void StartObject();
    void AddPointToObject(Point3D p3D);
    void AddPolygonToObject(QVector<int> indices, QColor color);
    void FinishObject();
    void Display(QPainter& painter);

    void SetWindowCoordinates(int width, int height);
    void ApplyTransformation(Transformation transf);

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
};

#endif // SCENE3D_H
