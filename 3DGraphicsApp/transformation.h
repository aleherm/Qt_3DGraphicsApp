#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include "point3d.h"
#include <math.h>

class Transformation
{
    double t[4][4];
    void MatrixMultiplication(double a[4][4]);
public:
    Transformation();
    void Translate(double dx, double dy, double dz);

    void ScaleOrigin(double sx, double sy, double sz); // scalare fata de origine
    void ScalePoint(double sx, double sy, double sz, Point3D point); // scalae fata de un punct

    void RotateOz(double alfa, Point3D axis);
    void RotateOx(double beta, Point3D axis);
    void RotateOy(double gama, Point3D axis);
    void RotationAroundLine(double sx, double sy, double sz, double alfa, double gama, double beta, Point3D gravityPoint); // rotatie in jurul unei linii oarecare (not working)

    void Symmetry(double sx, double sy, double sz);
    void SymmetryPlane(double sx, double sy, double sz, double alfa, double beta, Point3D gravityPoint); // simetria fata de un plan (not working)

    void ApplyTransformation(double x, double y, double z, double& xp, double& yp, double& zp); // aplica matricea de transformare unui punct

    void Reset(double m[4][4]); // reseteaza la matricea identitate
    void PrintMatrix(double m[4][4]); // afiseaza matricea
};

#endif // TRANSFORMATION_H
