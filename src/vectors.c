#include "global.h"
#include "vectors.h"
#include <math.h>




float TPoint3D__Norme1(const TPoint3D p) {
  return fabs(p.x) +  fabs(p.y) + fabs(p.z);    
}; 

float TPoint2D__Norme1(const TPoint2D p) {
  return fabs(p.x) +  fabs(p.y);    
}; 

void TPoint3D_Normer2(TPoint3D * p_ref) {
  const float norme2 = TPoint3D_Norme2(*p_ref); 
  TPoint3D_lambda_self(1.0f / norme2, *p_ref); 
};



#if 0 
TPoint2D operator- (TPoint2D p1, TPoint2D p2)
{
  TPoint2D r;
  r.x = p1.x - p2.x;
  r.y = p1.y - p2.y;
  return r;
}

TPoint2D operator+ (TPoint2D p1, TPoint2D p2)
{
  TPoint2D r;
  r.x = p1.x + p2.x;
  r.y = p1.y + p2.y;
  return r;
}




TPoint2D operator* (float lambda, TPoint2D p)
{
  TPoint2D r;
  r.x = lambda*p.x;
  r.y = lambda*p.y;
  return r;
}



TPoint3D operator- (TPoint3D p1, TPoint3D p2)
{
  TPoint3D r;
  r.x = p1.x - p2.x;
  r.y = p1.y - p2.y;
  r.z = p1.z - p2.z;
  return r;
}

TPoint3D operator+ (TPoint3D p1, TPoint3D p2) {
  TPoint3D r;
  r.x = p1.x + p2.x;
  r.y = p1.y + p2.y;
  r.z = p1.z + p2.z;
  return r;
}



TPoint3D operator* (float lambda, TPoint3D p)
{
  p.x = lambda*p.x;
  p.y = lambda*p.y;
  p.z = lambda*p.z;
  return p;
}

TPoint3D operator^ (TPoint3D p1, TPoint3D p2)
  /*produit vectoriel*/
{
  TPoint3D r;
  r.x = (p1).y * (p2).z - (p1).z * (p2).y;
  r.y = (p1).z * (p2).x - (p1).x * (p2).z;
  r.z = (p1).x * (p2).y - (p1).y * (p2).x;
  return r;
}

TPoint3D Point3D(float x, float y, float z)
{
  TPoint3D r;
  r.x = x;
  r.y = y;
  r.z = z;
  r.arf = 1.0f;
  return r;
}    





#endif 
