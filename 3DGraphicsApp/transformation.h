#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include "point3d.h"
#include <math.h>

class Transformation
{
    double t[4][4];
    void matrixMultiplication(double a[4][4]);
public:
    Transformation();
    void Translate(double dx, double dy, double dz);

    void Scale(double sx, double sy, double sz);
    void ScaleOrigin(double sx, double sy, double sz);
    void ScalePoint(double sx, double sy, double sz, Point3D point);

    void RotateOz(double alfa, Point3D axis);
    void RotateOx(double beta, Point3D axis);
    void RotateOy(double gama, Point3D axis);
    void RotationAroundLine(double sx, double sy, double sz, double alfa, double gama, double beta, Point3D gravityPoint);

    void Symmetry(double sx, double sy, double sz);
    void SymmetryPlane(double sx, double sy, double sz, double alfa, double beta, Point3D gravityPoint);

    void ApplyTransformation(double x, double y, double z, double& xp, double& yp, double& zp);
    void Reset(double m[4][4]);
    void PrintMatrix(double m[4][4]);
};

#endif // TRANSFORMATION_H
