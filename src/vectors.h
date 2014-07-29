#ifndef VECTORS_HPP
#define VECTORS_HPP

struct TPoint2D {
  float x, y;
};

struct TPoint3D {
  float x, y, z, arf;
};

TPoint2D operator- (TPoint2D p1, TPoint2D p2);
TPoint2D operator+ (TPoint2D p1, TPoint2D p2);
TPoint2D operator* (float lambda, TPoint2D p);

TPoint3D operator- (TPoint3D p1, TPoint3D p2);
TPoint3D operator+ (TPoint3D p1, TPoint3D p2);
TPoint3D operator* (float lambda, TPoint3D p);
TPoint3D operator^ (TPoint3D p1, TPoint3D p2);

TPoint3D Point3D(float x, float y, float z);

float Norme1(TPoint3D p);
float Norme1(TPoint2D p);

void Normer2(TPoint3D &p);

#endif /* VECTORS_HPP */
