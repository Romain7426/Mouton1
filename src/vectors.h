#ifndef VECTORS_H
#define VECTORS_H

struct TPoint2D {
  float x, y;
};
DEFINE_NEW_OPERATOR_FOR_STRUCT(TPoint2D);
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TPoint2D);

struct TPoint3D {
  float x, y, z, arf;
};
DEFINE_NEW_OPERATOR_FOR_STRUCT(TPoint3D);
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TPoint3D);


#if 0
TPoint2D operator- (TPoint2D p1, TPoint2D p2);
TPoint2D operator+ (TPoint2D p1, TPoint2D p2);
TPoint2D operator* (float lambda, TPoint2D p);

TPoint3D operator- (TPoint3D p1, TPoint3D p2);
TPoint3D operator+ (TPoint3D p1, TPoint3D p2);
TPoint3D operator* (float lambda, TPoint3D p);
TPoint3D operator^ (TPoint3D p1, TPoint3D p2);
#else
void TPoint2D_operator_sub(const TPoint2D p1, const TPoint2D p2, TPoint2D * p3);
void TPoint2D_operator_add(const TPoint2D p1, const TPoint2D p2, TPoint2D * p3);
void TPoint2D_operator_scalar_mul(const float lambda, const TPoint2D p1, TPoint2D * p3);

void TPoint3D_operator_sub(const TPoint3D p1, const TPoint3D p2, TPoint3D * p3);
void TPoint3D_operator_add(const TPoint3D p1, const TPoint3D p2, TPoint3D * p3);
void TPoint3D_operator_scalar_mul(const float lambda, const TPoint3D p1, TPoint3D * p3);
void TPoint3D_operator_hat(const TPoint3D p1, const TPoint3D p2, TPoint3D * p3);
#endif

#if 0
TPoint3D Point3D(float x, float y, float z);
#endif

#if 0
float Norme1(TPoint3D p);
float Norme1(TPoint2D p);
#else
float TPoint3D_Norme1(TPoint3D p);
float TPoint2D_Norme1(TPoint2D p);
#endif

//void Normer2(TPoint3D &p);

#endif /* VECTORS_H */
