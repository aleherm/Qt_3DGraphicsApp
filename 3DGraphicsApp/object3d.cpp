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

// true -> afiseaza, false -> nu afiseaza
bool Object3D::IsVisiblePolygon(Point3D A0, Point3D A1, Point3D A2)
{
    Point3D PA0(A0.x, A0.y, A0.z - zp);
    Point3D N = GetPolygonNormal(A0, A1, A2);

    double visibility = CrossProduct(PA0, N);
    if(visibility > 0)
        return true; // se afiseaza
    return false;
}

bool Object3D::IsIlluminated(Point3D A0, Point3D A1, Point3D A2)
{
    Point3D N = GetPolygonNormal(A0, A1, A2);

    double lightSource = CrossProduct(lightVector, N);

    if(lightSource < 0)
        return true;
    return false; // se coloreaza negru
}

double Object3D::GetIlluminatingFactor(Point3D A0, Point3D A1, Point3D A2)
{
    Point3D N = GetPolygonNormal(A0, A1, A2);

    double normCross = VectorNorm(lightVector) * VectorNorm(N);
    double cosVector = CrossProduct(lightVector, N) / normCross;

    if(cosVector < 0)
        cosVector *= -1;

    double result = ambientLight + (1.0 - ambientLight) * cosVector; // k + (1 - k) * |cos(v1, N)|^alfa
    return result;
}

QColor Object3D::GetAmbientalColor(QColor color, double illuminatingFactor)
{
    int R = color.red() * illuminatingFactor;
    int G = color.green() * illuminatingFactor;
    int B = color.green() *  illuminatingFactor;
    return QColor(R, G, B);
}

void Object3D::Display(QPainter &painter)
{
    int index;
    Point3D P0, P1, P2;
    for (int i = 0; i < m_polygonIndices.size(); i++)
    {
        bool isPolygon = false;
        if(m_polygonIndices[i].size() >= 3)
            isPolygon = true;

        QVector<QPoint> points;
        for (int j = 0; j < m_polygonIndices[i].size(); j++)
        {
            index = m_polygonIndices[i][j];
            points.push_back(m_points2D[index]);
        }

        QColor newColor, color = this->m_colors[i];
        if(isPolygon)
        {
            P0 = Point3D(m_points3D[m_polygonIndices[i][0]]);
            P1 = Point3D(m_points3D[m_polygonIndices[i][1]]);
            P2 = Point3D(m_points3D[m_polygonIndices[i][2]]);

            bool isVisible = this->IsVisiblePolygon(P0, P1, P2);
            if(!isVisible)
                continue;

            bool isIlluminated = this->IsIlluminated(P0, P1, P2);
            if (isIlluminated)
            {
                double illuminatingFactor = GetIlluminatingFactor(P0, P1, P2);
                newColor = GetAmbientalColor(color, illuminatingFactor);
            }
            else
            {
                newColor = GetAmbientalColor(color, ambientLight);
            }
        }

        painter.setPen(QColor(newColor));
        painter.setBrush(QBrush(newColor));
        painter.drawPolygon(QPolygon(points));
    }
}

void Object3D::AddPoint3D(Point3D p3D)
{
    m_points3D.push_back(p3D);
    m_points2D.push_back(PerspectiveProjection(p3D));
}

void Object3D::AddPolygon(QVector<int> polygonIndices, QColor color)
{
    m_polygonIndices.push_back(polygonIndices);
    m_colors.push_back(color);
}

void Object3D::Translate(double dx, double dy, double dz)
{
    transformation3D.Translate(dx, dy, dz);
    this->ApplyTransformation();
}

void Object3D::ScaleOrigin(double sx, double sy, double sz)
{
    transformation3D.ScaleOrigin(sx, sy, sz);
    this->ApplyTransformation();
}

void Object3D::ScalePoint(double sx, double sy, double sz, Point3D point)
{
    transformation3D.ScalePoint(sx, sy, sz, point);
    this->ApplyTransformation();
}

void Object3D::RotateOz(double alfa) // Oz
{
    Point3D gravityPoint = GetGravityCenterPoint();
    transformation3D.RotateOz(alfa, Point3D(gravityPoint.x, gravityPoint.y, 0));
    this->ApplyTransformation();
}

void Object3D::RotateOx(double beta) // Ox
{
    Point3D gravityPoint = GetGravityCenterPoint();
    transformation3D.RotateOx(beta, Point3D(0, gravityPoint.y, gravityPoint.z));
    this->ApplyTransformation();
}

void Object3D::RotateOy(double gama) // Oy
{
    Point3D gravityPoint = GetGravityCenterPoint();
    transformation3D.RotateOy(gama, Point3D(gravityPoint.x, 0, gravityPoint.z));
    this->ApplyTransformation();
}

void Object3D::Symmetry(double sx, double sy, double sz)
{
    transformation3D.Symmetry(sx, sy, sz);
    this->ApplyTransformation();
}

void Object3D::SymmetryPlane(double sx, double sy, double sz, double alfa, double beta)
{
    Point3D gravityPoint = GetGravityCenterPoint();
    transformation3D.SymmetryPlane(sx, sy, sz, alfa, beta, gravityPoint);
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
        deb<<"Old: "<<m_points3D[i].x<< " " << m_points3D[i].y<< " "<< m_points3D[i].z << "|";
        deb<<"New: "<<newX<< " " << newY<< " "<< newZ;
        deb<<endl;
        Point3D newPoint(newX, newY, newZ);
        m_points3D[i] = newPoint;
        m_points2D[i] = QPoint(PerspectiveProjection(newPoint));
    }
}

Point3D Object3D::VectorialProduct(Point3D v1, Point3D v2)
{
    double x, y, z;
    x = v1.y * v2.z - v2.y * v1.z;
    y = v1.x * v2.z - v2.x * v1.z;
    z = v1.x * v2.y - v2.x * v1.y;

    return Point3D(x, -y, z);
}

double Object3D::CrossProduct(Point3D v1, Point3D v2)
{
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Point3D Object3D::GetPolygonNormal(Point3D A0, Point3D A1, Point3D A2)
{
    Point3D PA0(A0.x, A0.y, A0.z - zp);
    Point3D A0A1(A1.x - A0.x, A1.y - A0.y, A1.z - A0.z);
    Point3D A0A2(A2.x - A0.x, A2.y - A0.y, A2.z - A0.z);

    Point3D N = VectorialProduct(A0A2, A0A1); // cross product

    return N;
}

double Object3D::VectorNorm(Point3D v)
{
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
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

void Object3D::ZBufferingDisplay(QPainter& painter)
{
    int zBuffs[m_polygonIndices.size()];
    for (int i = 0; i < m_polygonIndices.size(); i++)
    {
        double gravityZ = 0;
        for (int j = 0; j < m_polygonIndices[i].size(); j++)
        {
            int index = m_polygonIndices[i][j];
            gravityZ += m_points3D[index].z;
        }
        zBuffs[i] = gravityZ / m_polygonIndices[i].size();
    }

    QVector<QVector<int>> newPolygonIndices = m_polygonIndices;

    //sort
    QVector<int> temp;
    for(int i = 0; i < newPolygonIndices.size(); i++)
    {
        for(int j = 0; j < newPolygonIndices.size()-i-1; j++)
        {
            if(zBuffs[j] > zBuffs[j+1])
            {
                // swap the elements
                temp = newPolygonIndices[j];
                newPolygonIndices[j] = newPolygonIndices[j+1];
                newPolygonIndices[j+1] = temp;
            }
        }
    }

    int index;
    for (int i = 0; i < newPolygonIndices.size(); i++)
    {
        Point3D P0(m_points3D[newPolygonIndices[i][0]]);
        Point3D P1(m_points3D[newPolygonIndices[i][1]]);
        Point3D P2(m_points3D[newPolygonIndices[i][2]]);
        bool isVisible = this->IsVisiblePolygon(P0, P1, P2);

        if(!isVisible)
            continue;

        QPoint points[4];
        int  j;
        for (j = 0; j < newPolygonIndices[i].size(); j++)
        {
            index = newPolygonIndices[i][j];
            points[j] = m_points2D[index];
        }

        QColor color = this->m_colors[i];
        painter.setBrush(QBrush(color));
        painter.drawPolygon(points, newPolygonIndices[i].size());
    }
}

void Object3D::CutObject()
{
//    bool canBeCut = false;
//    for(int i = 0; i < m_points3D.size() - 1; i++)
//    {
//        Point3D currentPoint = m_points3D[i];
//        Point3D nextPoint = m_points3D[i+1];
//        if(currentPoint.z * nextPoint.z < 0)
//            canBeCut = true;

//        if(canBeCut)
//        {
//            double Ix = currentPoint.x - currentPoint.z * ((nextPoint.x - currentPoint.x) / (nextPoint.z - currentPoint.z));
//            double Iy = currentPoint.y - currentPoint.z * ((nextPoint.y - currentPoint.y) / (nextPoint.z - currentPoint.z));
//            Point3D pointOfIncidence;

//        }
//    }
}

void Object3D::setWindowCoordinates(int width, int height)
{
    this->wWidth = width;
    this->wHeight = height;
}
