#include "object3d.h"
#include <QDebug>

Object3D::Object3D()
{

}

QPoint Object3D::PerspectiveProjection(Point3D p3D)
{
    double x = wWidth / 2 + p3D.x * zp / (zp - p3D.z);
    double y = wHeight / 2 + p3D.y * zp / (zp - p3D.z);
    return QPoint(x, y);
}

void Object3D::Display(QPainter &painter)
{
    int index1, index2;
    for (int i = 0; i < m_polygonIndices.size(); i++)
    {
        int  j;
        for (j = 0; j < m_polygonIndices[i].size() - 1; j++)
        {
            index1 = m_polygonIndices[i][j];
            index2 = m_polygonIndices[i][j+1];
            if (index1 < m_points2D.size() && index2 < m_points2D.size())
            {
                painter.drawLine(m_points2D[index1].x(), m_points2D[index1].y(), m_points2D[index2].x(), m_points2D[index2].y());
            }
        }
        index1 = m_polygonIndices[i][j];
        index2 = m_polygonIndices[i][0];
        painter.drawLine(m_points2D[index1].x(), m_points2D[index1].y(), m_points2D[index2].x(), m_points2D[index2].y());
    }
}

void Object3D::AddPoint3D(Point3D p3D)
{
    m_points3D.push_back(p3D);
    m_points2D.push_back(PerspectiveProjection(p3D));
}

//Object3D = mai multe poligoane (de culori diferite?)
void Object3D::AddPolygon(QVector<int> polygonIndices, int color)
{
    m_polygonIndices.push_back(polygonIndices);
    m_colors.push_back(color);
}

void Object3D::Translate(double dx, double dy, double dz)
{
    transformation3D.Translate(dx, dy, dz);
    this->ApplyTransformation();
}

void Object3D::Scale(double sx, double sy, double sz)
{
    transformation3D.Scale(sx, sy, sz);
    this->ApplyTransformation();
}

void Object3D::RotateOz(double alfa) // Oz
{
    Point3D gravityPoint = GetGravityCenterPoint();
    transformation3D.RotateOz(alfa, Point3D(gravityPoint.x, gravityPoint.y, 0));
    this->ApplyTransformation();
}

void Object3D::RotateOy(double beta) // Oz
{
    Point3D gravityPoint = GetGravityCenterPoint();
    transformation3D.RotateOy(beta, Point3D(gravityPoint.x, gravityPoint.y, 0));
    this->ApplyTransformation();
}

void Object3D::RotateOx(double gama) // Oz
{
    Point3D gravityPoint = GetGravityCenterPoint();
    transformation3D.RotateOx(gama, Point3D(gravityPoint.x, gravityPoint.y, 0));
    this->ApplyTransformation();
}

void Object3D::Reset()
{
    m_polygonIndices.resize(0);
    m_points3D.resize(0);
    m_colors.resize(0);
}

void Object3D::ApplyTransformation()
{
    QDebug deb = qDebug();
    for (int i = 0; i < m_points3D.size(); i++)
    {
        double newX, newY, newZ;
        transformation3D.ApplyTransformation(m_points3D[i].x, m_points3D[i].y, m_points3D[i].z, newX, newY, newZ);
        deb<<"Old: "<<m_points3D[i].x<< " " << m_points3D[i].y<< " "<< m_points3D[i].z;
        deb<<"New: "<<newX<< " " << newY<< " "<< newZ;
        deb<<endl;
        Point3D newPoint(newX, newY, newZ);
        m_points3D[i] = newPoint;
        m_points2D[i] = QPoint(PerspectiveProjection(newPoint));
    }
}

Point3D Object3D::GetGravityCenterPoint()
{
    double centruX = 0, centruY = 0, centruZ = 0;

    for (int i = 0; i < this->m_points3D.size(); i++)
    {
        centruX += this->m_points3D[i].x;
        centruY += this->m_points3D[i].y;
        centruZ += this->m_points3D[i].z;
    }

    centruX = (double)centruX / this->m_points3D.size();
    centruY = (double)centruY / this->m_points3D.size();
    centruZ = (double)centruZ / this->m_points3D.size();

    Point3D gravityPoint(centruX, centruY, centruZ);

    return gravityPoint;
}

void Object3D::setWindowCoordinates(int width, int height)
{
    this->wWidth = width;
    this->wHeight = height;
}
