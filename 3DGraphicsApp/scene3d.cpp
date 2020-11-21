#include "scene3d.h"

Scene3D::Scene3D()
{

}

void Scene3D::Display(QPainter& painter)
{
    for (Object3D& ob : m_objects3D)
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

void Scene3D::AddPolygonToObject(QVector<int> indices, int color)
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

void Scene3D::setWindowCoordinates(int width, int height)
{
    m_currentObject.setWindowCoordinates(width, height);
}
