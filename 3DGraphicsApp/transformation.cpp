#include "transformation.h"
#include <QDebug>

Transformation::Transformation()
{
    this->Reset(t);
}

void Transformation::Reset(double m[4][4])
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(i==j)
                m[i][j]=1;
            else
                m[i][j]=0;
}

void Transformation::MatrixMultiplication(double m[4][4])
{
    double r[4][4];
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            r[i][j]=0;
            for(int k=0; k<4; k++)
                r[i][j]+=m[i][k]*t[k][j];
        }
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
           t[i][j]=r[i][j];

    //PrintMatrix(t);
}

void Transformation::ScaleOrigin(double sx, double sy, double sz)
{
    double m[4][4];
    Reset(m);

    m[0][0]=sx;
    m[1][1]=sy;
    m[2][2]=sz;

    MatrixMultiplication(m);
}

void Transformation::ScalePoint(double sx, double sy, double sz, Point3D point)
{
    Translate(point.x, point.y, point.z);
    ScaleOrigin(sx, sy, sz);
    Translate(-point.x, -point.y, -point.z);
}

void Transformation::Symmetry(double sx, double sy, double sz)
{
    this->ScaleOrigin(sx, sy, sz);
}

void Transformation::SymmetryPlane(double sx, double sy, double sz, double alfa, double beta, Point3D gravityPoint)
{
    this->Translate(sx, sy, sz);
    this->RotateOy(-alfa, Point3D(gravityPoint.x, 0, gravityPoint.z));
    this->RotateOz(beta, Point3D(gravityPoint.x, gravityPoint.y, 0));
    this->ScaleOrigin(0, 1.1, 1.1); // ?????
    this->RotateOz(-beta, Point3D(gravityPoint.x, gravityPoint.y, 0));
    this->RotateOy(alfa, Point3D(gravityPoint.x, 0, gravityPoint.z));
    this->Translate(-sx, -sy, -sz);
}

void Transformation::RotationAroundLine(double sx, double sy, double sz, double alfa, double beta, double gama, Point3D gravityPoint)
{
    this->Translate(sx, sy, sz);
    this->RotateOy(-gama, Point3D(gravityPoint.x, 0, gravityPoint.z));
    this->RotateOz(alfa, Point3D(gravityPoint.x, gravityPoint.y, 0));
    this->RotateOx(beta, Point3D(0, gravityPoint.y, gravityPoint.z));
    this->RotateOz(-alfa, Point3D(gravityPoint.x, gravityPoint.y, 0));
    this->RotateOy(gama, Point3D(gravityPoint.x, 0, gravityPoint.z));
    this->Translate(-sx, -sy, -sz);
}

void Transformation::Translate(double dx, double dy, double dz)
{
    double m[4][4];
    this->Reset(m);

    m[0][3] = dx;
    m[1][3] = dy;
    m[2][3] = dz;

    qDebug()<<"Translatie";
    MatrixMultiplication(m);
}

//xOy
void Transformation::RotateOz(double alfa, Point3D axis)
{
    qDebug()<<"Rotatie Oz";
    this->Translate(-axis.x, -axis.y, -axis.z);
    double m[4][4];
    Reset(m);
    m[0][0] = cos(alfa);
    m[0][1] = -sin(alfa);
    m[1][0] = sin(alfa);
    m[1][1] = cos(alfa);
    MatrixMultiplication(m);

    this->Translate(axis.x, axis.y, axis.z);
}

//yOz
void Transformation::RotateOx(double beta, Point3D axis)
{
    this->Translate(-axis.x, -axis.y, -axis.z);
    double m[4][4];
    Reset(m);
    m[1][1] = cos(beta);
    m[1][2] = -sin(beta);
    m[2][1] = sin(beta);
    m[2][2] = cos(beta);
    MatrixMultiplication(m);

    this->Translate(axis.x, axis.y, axis.z);
}

//zOx
void Transformation::RotateOy(double gama, Point3D axis)
{
    this->Translate(-axis.x, -axis.y, -axis.z);
    double m[4][4];
    Reset(m);
    m[0][0] = cos(gama);
    m[0][2] = -sin(gama);
    m[2][0] = sin(gama);
    m[2][2] = cos(gama);
    MatrixMultiplication(m);

    this->Translate(axis.x, axis.y, axis.z);
}

void Transformation::ApplyTransformation(double x, double y, double z, double& xp, double& yp, double& zp)
{
//    qDebug()<<"Inainte de aplicare";
//    PrintMatrix(t);
    xp = t[0][0] * x + t[0][1] * y + t[0][2] * z + t[0][3];
    yp = t[1][0] * x + t[1][1] * y + t[1][2] * z + t[1][3];
    zp = t[2][0] * x + t[2][1] * y + t[2][2] * z + t[2][3];
}

void Transformation::PrintMatrix(double m[4][4])
{
    QDebug deb = qDebug();
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            deb<<m[i][j]<<" ";
        deb<<endl;
    }
}
