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
extern void TPoint3D_sub   (const TPoint3D  p1, const TPoint3D p2, TPoint3D * p3_ref); 
extern void TPoint3D_add   (const TPoint3D  p1, const TPoint3D p2, TPoint3D * p3_ref); 
extern void TPoint3D_normal(const TPoint3D  p1, const TPoint3D p2, TPoint3D * p3_ref); // RL: ux ^ uy = uz 
extern void TPoint3D_scale (const float lambda, const TPoint3D p1, TPoint3D * p3_ref); 
#define TPoint3D_hat    TPoint3D_normal 
#define TPoint3D_lambda TPoint3D_scale 

// RL: A nice way to implement these macros would be to implement a TPoint3D stack. 
//     However, it would not be thread-safe (cooperative and/or preemptive), 
//     and it would imply extra complexity for management. 
//     So does it worth it, considering the extra bugs it would make, and the not-that-great gain (the syntax would still be awkward, and not thought-free). 
#define TPoint3D_add__macro(__p1__,__p2__) TPoint3D_make_struct((__p1__).x + (__p2__).x, (__p1__).y + (__p2__).y, (__p1__).z + (__p2__).z) 
#define TPoint3D_sub__macro(__p1__,__p2__) TPoint3D_make_struct((__p1__).x - (__p2__).x, (__p1__).y - (__p2__).y, (__p1__).z - (__p2__).z) 
#define TPoint3D_scale__macro(__lambda__,__p1__) TPoint3D_make_struct((__lambda__) * (__p1__).x, (__lambda__) * (__p1__).y, (__lambda__) * (__p1__).z) 
#define TPoint3D_lambda__macro TPoint3D_scale__macro 
#define TPoint3D_normal__macro(__p1__,__p2__) TPoint3D_make_struct((__p1__).y * (__p2__).z - (__p1__).z * (__p2__).y, (__p1__).z * (__p2__).x - (__p1__).x * (__p2__).z, (__p1__).x * (__p2__).y - (__p1__).y * (__p2__).x)
#define TPoint3D_assign__macro(__p1__,__xx__,__yy__,__zz__) { TPoint3D * __p1_ref__ = &(__p1__); __p1_ref__ -> x = (__xx__); __p1_ref__ -> y = (__yy__); __p1_ref__ -> z = (__zz__); }; 
//#define TPoint3D_add_self(____p1____,____p2____) { TPoint3D __p1__ = ((__p1__).x += (__p2__).x, (__p1__).y += (__p2__).y, (__p1__).z += (__p2__).z) }; 
//#define TPoint3D_add_self3(__p1__,__p2__) ((__p1__).x += (__p2__).x, (__p1__).y += (__p2__).y, (__p1__).z += (__p2__).z)
//#define TPoint3D_add_self2(__p1__,xx,yy,zz) ((__p1__).x += (xx), (__p1__).y += (yy), (__p1__).z += (zz)) 
#define TPoint3D_add_self__macro(__p1__,__p2__) { TPoint3D * __p1_ref__ = &(__p1__); const TPoint3D __p2_v__ = (__p2__); __p1_ref__ -> x += __p2_v__.x; __p1_ref__ -> y += __p2_v__.y; __p1_ref__ -> z += __p2_v__.z; }; 
#define TPoint3D_sub_self__macro(__p1__,__p2__) { TPoint3D * __p1_ref__ = &(__p1__); const TPoint3D __p2_v__ = (__p2__); __p1_ref__ -> x -= __p2_v__.x; __p1_ref__ -> y -= __p2_v__.y; __p1_ref__ -> z -= __p2_v__.z; }; 
#define TPoint3D_scale_self__macro(__lambda__,__p1__) { TPoint3D * __p1_ref__ = &(__p1__); const float __lambda_v__ = (__lambda__); __p1_ref__ -> x *= __lambda_v__; __p1_ref__ -> y *= __lambda_v__; __p1_ref__ -> z *= __lambda_v__; }; 
#define TPoint3D_lambda_self__macro TPoint3D_scale_self__macro 
#define TPoint3D_add_self_expanded__macro(__p1__,__x2__,__y2__,__z2__) { TPoint3D * __p1_ref__ = &(__p1__); __p1_ref__ -> x += (__x2__); __p1_ref__ -> y += (__y2__); __p1_ref__ -> z += (__z2__); }; 

extern void TPoint3D_add_self(TPoint3D * p1_ref, const TPoint3D p2); 
extern void TPoint3D_sub_self(TPoint3D * p1_ref, const TPoint3D p2); 
extern void TPoint3D_scale_self(const float lambda, TPoint3D * p1_ref); 
#define TPoint3D_lambda_self TPoint3D_scale_self 

extern void TPoint3D_add_self_expanded(TPoint3D * p1_ref, const float x, const float y, const float z); 

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
#define TPoint2D_Norme1(__p1__) (fabs((__p1__).x) + fabs((__p1__).y)) 
#define TPoint3D_Norme1(__p1__) (fabs((__p1__).x) + fabs((__p1__).y) + fabs((__p1__).z)) 
#define TPoint3D_Norme2(__p1__) (sqrtf(((__p1__).x)*((__p1__).x) + ((__p1__).y)*((__p1__).y) + ((__p1__).z)*((__p1__).z))) 
#endif

//void Normer2(TPoint3D &p); 
void TPoint3D_Normer2(TPoint3D * p_ref);

#endif /* VECTORS_H */
