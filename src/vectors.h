#ifndef VECTORS_H
#define VECTORS_H

struct TPoint2D {
  float x, y;
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TPoint2D);
DEFINE_NEW_OPERATOR_FOR_STRUCT(TPoint2D);

struct TPoint3D {
  float x, y, z, arf;
};
TYPEDEF_TYPENAME_WITHOUT_STRUCT(TPoint3D);
DEFINE_NEW_OPERATOR_FOR_STRUCT(TPoint3D);
#define TPoint3D_make_scalar(xx,yy,zz) ((struct TPoint3D) { xx, yy, zz, 1 })
#define TPoint3D_make_struct TPoint3D_make_scalar


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

#define TPoint3D_add(p1,p2) TPoint3D_make_struct((p1).x + (p2).x, (p1).y + (p2).y, (p1).z + (p2).z)
#define TPoint3D_sub(p1,p2) TPoint3D_make_struct((p1).x - (p2).x, (p1).y - (p2).y, (p1).z - (p2).z)
#define TPoint3D_scalar_mul(lambda,p1) TPoint3D_make_struct((lambda) * (p1).x, (lambda) * (p1).y, (lambda) * (p1).z)
#define TPoint3D_lambda TPoint3D_scalar_mul
#define TPoint3D_add_self(p1,p2) ((p1).x += (p2).x, (p1).y += (p2).y, (p1).z += (p2).z)
#define TPoint3D_add_self2(p1,xx,yy,zz) ((p1).x += (xx), (p1).y += (yy), (p1).z += (zz))
#define TPoint3D_sub_self(p1_,p2_) { TPoint3D p1 = (p1_), p2 = (p2_);  ((p1).x += (p2).x, (p1).y += (p2).y, (p1).z += (p2).z); }
#define TPoint3D_lambda_self(lambda_,p1_) { TPoint3D p1 = (p1_); float lambda = (lambda_); (p1).x *= (lambda);  (p1).y *= (lambda); (p1).z *= (lambda); } 
#define TPoint3D_assign(p1,xx,yy,zz) ((p1).x = (xx), (p1).y = (yy), (p1).z = (zz))
#define TPoint3D_normale(p1,p2) TPoint3D_make_struct((p1).y * (p2).z - (p1).z * (p2).y, (p1).z * (p2).x - (p1).x * (p2).z, (p1).x * (p2).y - (p1).y * (p2).x)


//void TPoint3D_add2(TPoint3D * p1, const float x, const float y, const float z);
//void TPoint3D_set(TPoint3D * p1, const float x, const float y, const float z);
#endif


#if 0
TPoint3D Point3D(float x, float y, float z);
#endif

#if 0
float Norme1(TPoint3D p);
float Norme1(TPoint2D p);
#elif 0 
float TPoint3D_Norme1(TPoint3D p);
float TPoint2D_Norme1(TPoint2D p);
#else 
#define TPoint2D_Norme1(p1) (fabs((p1).x) + fabs((p1).y)) 
#define TPoint3D_Norme1(p1) (fabs((p1).x) + fabs((p1).y) + fabs((p1).z)) 
#define TPoint3D_Norme2(p1) (sqrtf(((p1).x)*((p1).x) + ((p1).y)*((p1).y) + ((p1).z)*((p1).z))) 
#endif

//void Normer2(TPoint3D &p);
void TPoint3D_Normer2(TPoint3D * p_ref);

#endif /* VECTORS_H */
