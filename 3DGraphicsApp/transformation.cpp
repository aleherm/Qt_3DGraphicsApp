#include "transformation.h"

void Transformation::matrixMultiplication(double a[4][4])
{
    double b[4][4];
    for (int i = 0; i < 4 ; i++)
        for (int j = 0; j < 4;j ++)
        {
            b[i][j] = 0;
            for (int k = 0;k < 4;k++)
                b[i][j] += a[i][k] * t[k][j];
        }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            t[i][j] = b[i][j];
}

Transformation::Transformation()
{
    this->Reset(t);
}

void Transformation::Reset(double m[4][4])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i == j)
                m[i][j] = 1;
            else
                m[i][j] = 0;
}

void Transformation::Translate(double dx, double dy, double dz)
{
    double m[4][4];

    m[1][3] = dx;
    m[2][3] = dy;
    m[3][3] = dz;

    matrixMultiplication(m);
}

//xOy
void Transformation::RotateOz(double alfa, Point3D axis)
{
    this->Translate(-axis.x, -axis.y, -axis.z);
    double m[4][4];
    Reset(m);
    m[0][0] = cos(alfa);
    m[0][1] = -sin(alfa);
    m[1][0] = sin(alfa);
    m[1][1] = cos(alfa);
    matrixMultiplication(m);

    this->Translate(axis.x, axis.y, axis.z);
}
//zOx
void Transformation::RotateOy(double beta, Point3D axis)
{
    this->Translate(-axis.x, -axis.y, -axis.z);
    double m[4][4];
    Reset(m);
    m[0][0] = cos(beta);
    m[0][2] = -sin(beta);
    m[2][0] = sin(beta);
    m[2][2] = cos(beta);
    matrixMultiplication(m);

    this->Translate(axis.x, axis.y, axis.z);
}
//yOz
void Transformation::RotateOx(double gama, Point3D axis)
{
    this->Translate(-axis.x, -axis.y, -axis.z);
    double m[4][4];
    Reset(m);
    m[1][1] = cos(gama);
    m[1][2] = -sin(gama);
    m[2][1] = sin(gama);
    m[2][2] = cos(gama);
    matrixMultiplication(m);

    this->Translate(axis.x, axis.y, axis.z);
}

void Transformation::ApplyTransformation(double x, double y, double z, double& xp, double& yp, double& zp)
{
    xp = t[0][0] * x + t[0][1] * y + t[0][2] * z + t[0][3];
    yp = t[1][0] * x + t[1][1] * y + t[1][2] * z + t[1][3];
    zp = t[2][0] * x + t[2][1] * y + t[2][2] * z + t[2][3];
}
