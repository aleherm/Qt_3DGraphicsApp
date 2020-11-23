#include "scene3d.h"

Scene3D::Scene3D()
{

}

void Scene3D::Display(QPainter& painter)
{
    for (Object3D ob : m_objects3D)
        ob.Display(painter);
}

void Scene3D::StartObject()
{
    m_currentObject.Reset();
}

void Scene3D::AddPointToObject(Point3D p3D)
{
    m_currentObject.AddPoint3D(p3D);
}

void Scene3D::AddPolygonToObject(QVector<int> indices, QColor color)
{
    m_currentObject.AddPolygon(indices, color);
}

void Scene3D::FinishObject()
{
    m_objects3D.push_back(m_currentObject);
}

void Scene3D::Translate(double dx, double dy, double dz)
{
    for (Object3D& ob : m_objects3D)
        ob.Translate(dx, dy, dz);
}

void Scene3D::RotateOz(double alfa)
{
    for (Object3D& ob : m_objects3D)
        ob.RotateOz(alfa);
}

void Scene3D::RotateOx(double beta)
{
    for (Object3D& ob : m_objects3D)
        ob.RotateOx(beta);
}

void Scene3D::RotateOy(double gama)
{
    for (Object3D& ob : m_objects3D)
        ob.RotateOy(gama);
}

void Scene3D::ScaleOrigin(double sx, double sy, double sz)
{
    for (Object3D& ob : m_objects3D)
        ob.ScaleOrigin(sx, sy, sz);
}

void Scene3D::ScalePoint(double sx, double sy, double sz, Point3D point)
{
    for (Object3D& ob : m_objects3D)
        ob.ScalePoint(sx, sy, sz, point);
}

void Scene3D::Symmetry(double sx, double sy, double sz)
{
    for (Object3D& ob : m_objects3D)
        ob.Symmetry(sx, sy, sz);
}

void Scene3D::SymmetryPlane(double sx, double sy, double sz, double alfa, double beta)
{
    for (Object3D& ob : m_objects3D)
        ob.SymmetryPlane(sx, sy, sz, alfa, beta);
}

void Scene3D::setWindowCoordinates(int width, int height)
{
    m_currentObject.setWindowCoordinates(width, height);
}

void Scene3D::ZBufferingDisplay(QPainter& painter)
{
    for (Object3D& ob : m_objects3D)
        ob.ZBufferingDisplay(painter);
}

void Scene3D::ApplyTransformation(Transformation transf)
{
    for (Object3D& ob : m_objects3D)
    {
        ob.SetTransformation(transf);
        ob.ApplyTransformation();
    }
}
