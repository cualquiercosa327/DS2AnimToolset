/*---------------------------------------------------------------------------------------*/
/*
 *  \file   common/XVector4.c
 *  \date   19-05-2008
 *  \brief  all functions that are common to the SSE and vanilla versions.
 */
/*---------------------------------------------------------------------------------------*/

#include "XM2/Vector4.h"
namespace XM2
{  
#if !XM2_NO_C_IO
//----------------------------------------------------------------------------------------------------------------------
void XVector4::fprint32(FILE* fp) const
{
  // ensure not NULL
  XM2_ASSERT(fp);
  XM2_ALIGN_ASSERT(this);

  ::fprintf(fp,"%f %f %f %f\n",(float)x,(float)y,(float)z,(float)w);
}

//----------------------------------------------------------------------------------------------------------------------
void XVector4::fprint64(FILE* fp) const
{
  // ensure not NULL
  XM2_ASSERT(fp);
  XM2_ALIGN_ASSERT(this);

  ::fprintf(fp,"%lf %lf %lf %lf\n",(double)x,(double)y,(double)z,(double)w);
}

//----------------------------------------------------------------------------------------------------------------------
void XVector4::fscan32(FILE* fp)
{
  // ensure not NULL
  XM2_ASSERT(fp);
  XM2_ALIGN_ASSERT(this);

  #if XM2_USE_FLOAT
  # if XM2_USE_SECURE_SCL
  ::fscanf_s(fp,"%f%f%f%f",&x,&y,&z,&w);
  # else
  ::fscanf(fp,"%f%f%f%f",&x,&y,&z,&w);
  # endif
  #else
  float x_,y_,z_,w_;
  # if XM2_USE_SECURE_SCL
  ::fscanf_s(fp,"%f%f%f%f",&x_,&y_,&z_,&w_);
  # else
  ::fscanf(fp,"%f%f%f%f",&x_,&y_,&z_,&w_);
  # endif
  x = (XReal)x_;
  y = (XReal)y_;
  z = (XReal)z_;
  w = (XReal)w_;
  #endif
}

//----------------------------------------------------------------------------------------------------------------------
void XVector4::fscan64(FILE* fp)
{
  // ensure not NULL
  XM2_ASSERT(fp);
  XM2_ALIGN_ASSERT(this);

  #if !XM2_USE_FLOAT
  # if XM2_USE_SECURE_SCL
  ::fscanf_s(fp,"%lf%lf%lf%lf",&x,&y,&z,&w);
  # else
  ::fscanf(fp,"%lf%lf%lf%lf",&x,&y,&z,&w);
  # endif
  #else
  double x_,y_,z_,w_;
  # if XM2_USE_SECURE_SCL
  ::fscanf_s(fp,"%lf%lf%lf%lf",&x_,&y_,&z_,&w_);
  # else
  ::fscanf(fp,"%lf%lf%lf%lf",&x_,&y_,&z_,&w_);
  # endif
  x = (XReal)x_;
  y = (XReal)y_;
  z = (XReal)z_;
  w = (XReal)w_;
  #endif
}

//----------------------------------------------------------------------------------------------------------------------
void XVector4::print32() const
{
  fprint32(stdout);
}

//----------------------------------------------------------------------------------------------------------------------
void XVector4::print64() const
{
  fprint64(stdout);
}

//----------------------------------------------------------------------------------------------------------------------
void XVector4::fwrite32(FILE* fp,bool flip_bytes) const
{
  // ensure not NULL
  XM2_ASSERT(fp);
  XM2_ALIGN_ASSERT(this);

  #if XM2_USE_FLOAT
  if (flip_bytes)
  {
    XVector4 temp=*this;
    XM2swap(temp.x);
    XM2swap(temp.y);
    XM2swap(temp.z);
    XM2swap(temp.w);
    ::fwrite(&temp,sizeof(XVector4),1,fp);
  }
  else
    ::fwrite(this,sizeof(XVector4),1,fp);
  #else
  float temp[4];
  temp[0] = (float)x;
  temp[1] = (float)y;
  temp[2] = (float)z;
  temp[3] = (float)w;
  if (flip_bytes)
  {
    XM2swap(temp[0]);
    XM2swap(temp[1]);
    XM2swap(temp[2]);
    XM2swap(temp[3]);
  }
  ::fwrite(this,sizeof(float),4,fp);
  #endif
}

//----------------------------------------------------------------------------------------------------------------------
void XVector4::fwrite64(FILE* fp,bool flip_bytes) const
{
  // ensure not NULL
  XM2_ASSERT(fp);
  XM2_ALIGN_ASSERT(this);

  #if !XM2_USE_FLOAT
  if (flip_bytes)
  {
    XVector4 temp=*this;
    XM2swap(temp.x);
    XM2swap(temp.y);
    XM2swap(temp.z);
    XM2swap(temp.w);
    ::fwrite(&temp,sizeof(XVector4),1,fp);
  }
  else
    ::fwrite(this,sizeof(XVector4),1,fp);
  #else
  double temp[4];
  temp[0] = (double)x;
  temp[1] = (double)y;
  temp[2] = (double)z;
  temp[3] = (double)w;
  if (flip_bytes)
  {
    XM2swap(temp[0]);
    XM2swap(temp[1]);
    XM2swap(temp[2]);
    XM2swap(temp[3]);
  }
  ::fwrite(&temp,sizeof(XVector4),1,fp);
  #endif
}

//----------------------------------------------------------------------------------------------------------------------
void XVector4::fread32(FILE* fp,bool flip_bytes)
{
  // ensure not NULL
  XM2_ASSERT(fp);
  XM2_ALIGN_ASSERT(this);

  #if XM2_USE_FLOAT
  ::fread(this,sizeof(XVector4),1,fp);
  if (flip_bytes)
  {
    XM2swap(x);
    XM2swap(y);
    XM2swap(z);
    XM2swap(w);
  }
  #else
  float temp[4];
  ::fread(temp,sizeof(float),1,fp);
  if (flip_bytes)
  {
    XM2swap(temp[0]);
    XM2swap(temp[1]);
    XM2swap(temp[2]);
    XM2swap(temp[3]);
  }
  x = (XReal)temp[0];
  y = (XReal)temp[1];
  z = (XReal)temp[2];
  w = (XReal)temp[3];
  #endif
}

//----------------------------------------------------------------------------------------------------------------------
void XVector4::fread64(FILE* fp,bool flip_bytes)
{
  // ensure not NULL
  XM2_ASSERT(fp);
  XM2_ALIGN_ASSERT(this);

  #if !XM2_USE_FLOAT
  ::fread(this,sizeof(XVector4),1,fp);
  if (flip_bytes)
  {
    XM2swap(x);
    XM2swap(y);
    XM2swap(z);
    XM2swap(w);
  }
  #else
  double temp[4];
  ::fread(temp,sizeof(double),1,fp);
  if (flip_bytes)
  {
    XM2swap(temp[0]);
    XM2swap(temp[1]);
    XM2swap(temp[2]);
    XM2swap(temp[3]);
  }
  x = (XReal)temp[0];
  y = (XReal)temp[1];
  z = (XReal)temp[2];
  w = (XReal)temp[3];
  #endif
}
#endif

#if !XM2_NO_STREAM_IO
//----------------------------------------------------------------------------------------------------------------------
XM2EXPORT std::ostream& operator<<(std::ostream& ofs,const XVector4& c)
{
  return ofs << c.x << " " << c.y << " " << c.z << " " << c.w;
}
//----------------------------------------------------------------------------------------------------------------------
XM2EXPORT std::istream& operator>>(std::istream& ifs,XVector4& c)
{
  c.w = 0.0f;
  return ifs >> c.x >> c.y >> c.z;
}
#endif

}