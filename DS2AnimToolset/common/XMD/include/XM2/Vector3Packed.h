//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "XM2/MathCommon.h"
//----------------------------------------------------------------------------------------------------------------------
namespace XM2
{
//----------------------------------------------------------------------------------------------------------------------
// forward declarations
//----------------------------------------------------------------------------------------------------------------------

class XM2EXPORT XVector3;
class XM2EXPORT XVector4;

//----------------------------------------------------------------------------------------------------------------------
/// \class   XMD::XVector3Packed
/// \brief   A 3D vector or point type. This class is not SSE optimised! It's intended for
///          use in arrays of Vector3 data, where the additional w component of the XVector3
///          class would cause the data size to increase by 33%, and slows down processing
///          of vector3 data. The XVector3PackedArray processes 4 of these types at a time, 
///          and is considerably quicker.
/// \ingroup XM2MathsTypes
//----------------------------------------------------------------------------------------------------------------------
class XM2EXPORT XVector3Packed
{
public:

  //--------------------------------------------------------------------------------------------------------------------
  // XVector3 Constructors
  //--------------------------------------------------------------------------------------------------------------------

  /// \name  construction

  /// \brief  ctor 
  XM2_INLINE XVector3Packed();
  XM2_INLINE XVector3Packed(const XVector3Packed& rhs);
  XM2_INLINE XVector3Packed(const XVector3& rhs);
  XM2_INLINE XVector3Packed(XReal _x, XReal _y, XReal _z);

  //--------------------------------------------------------------------------------------------------------------------
  // XVector3 Initialisation funcs
  //--------------------------------------------------------------------------------------------------------------------

  /// \name  initialisation

  /// \brief  initialises this vector to 0,0,0
  XM2_INLINE void zero();

  /// \brief  sets the values
  /// \param  x - the x component
  /// \param  y - the y component
  /// \param  z - the z component
  XM2_INLINE void set(XReal x, XReal y, XReal z);
  
  /// \brief  sets the values 
  /// \param  ptr - the data to read from
  XM2_INLINE void set(const XReal* ptr);

  //--------------------------------------------------------------------------------------------------------------------
  // XVector3 Logical Comparisons
  //--------------------------------------------------------------------------------------------------------------------

  /// \name  equality

  /// \brief  this == b
  /// \param  b - second XVector3 to test
  /// \param  eps - floating point error tolerance
  /// \return true if this and b are the same, false otherwise
  XM2_INLINE bool equal(const XVector3Packed& b, XReal eps=XM2_FLOAT_ZERO) const;
  
  /// \brief  this != b
  /// \param  b - second XVector3 to test
  /// \param  eps - floating point error tolerance
  /// \return true if this and b are NOT the same, false otherwise
  XM2_INLINE bool notEqual(const XVector3Packed& b, XReal eps=XM2_FLOAT_ZERO) const;

  //--------------------------------------------------------------------------------------------------------------------
  // XVector3 Arithmetic
  //--------------------------------------------------------------------------------------------------------------------

  /// \name  maths

  /// \brief  adds an XVector3 to an XVector3. i.e.
  /// \code
  ///         this = a + b
  /// \endcode
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  XM2_INLINE void add(const XVector3Packed& a, const XVector3Packed& b);

  /// \brief  subtracts an XVector3 from an XVector3. i.e.
  /// \code
  ///         this = a - b
  /// \endcode
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  XM2_INLINE void sub(const XVector3Packed& a, const XVector3Packed& b);

  /// \brief  adds an XVector3 to this XVector3. i.e.
  /// \code
  ///         this += b
  /// \endcode
  /// \param  b - input arg 1
  XM2_INLINE void add(const XVector3Packed& b);

  /// \brief  subtracts an XVector3 from this XVector3. i.e.
  /// \code
  ///         this -= b
  /// \endcode
  /// \param  b - input arg 1
  ///
  XM2_INLINE void sub(const XVector3Packed& b);

  /// \brief  multiplies an XVector3 with an XVector3. i.e.
  /// \code
  ///         this = a * b
  /// \endcode
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  XM2_INLINE void mul(const XVector3Packed& a, const XVector3Packed& b);

  /// \brief  divides an XVector3 with an XVector3. i.e.
  /// \code
  ///         this = a * b
  /// \endcode
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  XM2_INLINE void div(const XVector3Packed& a, const XVector3Packed& b);

  /// \brief  multiplies this XVector3 with an XVector3. i.e.
  /// \code
  ///         this *= b
  /// \endcode
  /// \param  b - input arg 1
  XM2_INLINE void mul(const XVector3Packed& b);

  /// \brief  divides this XVector3 by an XVector3. i.e.
  /// \code
  ///         this /= b
  /// \endcode
  /// \param  b - input arg 1
  XM2_INLINE void div(const XVector3Packed& b);

  //--------------------------------------------------------------------------------------------------------------------
  // XVector3 / Float arithmetic
  //--------------------------------------------------------------------------------------------------------------------

  /// \brief  adds a float to an XVector3. i.e.
  /// \code
  ///         this = a + b
  /// \endcode
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  XM2_INLINE void add(const XVector3Packed& a, XReal b);

  /// \brief  subtracts a float from an XVector3. i.e.
  /// \code
  ///         this = a - b
  /// \endcode
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  XM2_INLINE void sub(const XVector3Packed& a, XReal b);

  /// \brief  divides an XVector3 with a float. i.e.
  /// \code
  ///         this = a * b
  /// \endcode
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  XM2_INLINE void div(const XVector3Packed& a, XReal b);

  /// \brief  multiplies an XVector3 with a float. i.e.
  /// \code
  ///         this = a * b
  /// \endcode
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  XM2_INLINE void mul(const XVector3Packed& a, XReal b);

  /// \brief  adds a float to this XVector3. i.e.
  /// \code
  ///         this += b
  /// \endcode
  /// \param  b - input arg 1
  XM2_INLINE void add(XReal b);

  /// \brief  subtracts a float from this XVector3. i.e.
  /// \code
  ///         this -= b
  /// \endcode
  /// \param  b - input arg 1
  XM2_INLINE void sub(XReal b);
  
  /// \brief  divides this XVector3 by a float. i.e.
  /// \code
  ///         this /= b
  /// \endcode
  /// \param  b - input arg 1
  XM2_INLINE void div(XReal b);

  /// \brief  multiplies this XVector3 with a float. i.e.
  /// \code
  ///         this *= b
  /// \endcode
  /// \param  b - input arg 1
  XM2_INLINE void mul(XReal b);

  //--------------------------------------------------------------------------------------------------------------------
  // dot & cross products
  //--------------------------------------------------------------------------------------------------------------------

  /// \brief  performs a dot product between this and b
  /// \param  b - second vec3
  /// \return the dot product of this and b
  XM2_INLINE XReal dot(const XVector3Packed& b) const;
  
  /// \brief  performs a cross product between this and b
  /// \param  a - first vec3
  /// \param  b - second vec3
  /// \return the dot product of a and b
  XM2_INLINE void cross(const XVector3Packed& a, const XVector3Packed& b);

  //--------------------------------------------------------------------------------------------------------------------
  // XVector3 Length & Normalisation routines
  //--------------------------------------------------------------------------------------------------------------------

  /// \brief  computes the length^2 of this vector3
  /// \return the square length of this vector
  XM2_INLINE XReal lengthSquared() const;

  /// \brief  calculate the length of this vector 
  /// \return return the vector's length
  XM2_INLINE XReal length() const;

  /// \brief  normalises this vector so it's of unit length
  XM2_INLINE void normalise();

  /// \brief  normalises this vector so it's of unit length
  XM2_INLINE void normalise(const XVector3Packed& q);

  //--------------------------------------------------------------------------------------------------------------------
  // XVector3 Lerps and Slerps
  //--------------------------------------------------------------------------------------------------------------------

  /// \name  lerp/slerp

  /// \brief  linearly interpolates (LERPS) between XVector3 a and b and stores in this
  /// \param  a - the first value
  /// \param  b - the 2nd value
  /// \param  t - the 0 to 1 interpolation control value
  XM2_INLINE void lerp(const XVector3Packed& a, const XVector3Packed& b, XReal t);

  /// \brief  interpolates using a bezier function between a,b,c and d. 
  /// \param  a - the first value
  /// \param  b - the 2nd value
  /// \param  c - the 3rd value
  /// \param  d - the 4th value
  /// \param  t - the 0 to 1 interpolation control value
  XM2_INLINE void bezier(const XVector3Packed& a, const XVector3Packed& b, const XVector3Packed& c, const XVector3Packed& d, XReal t);

  //--------------------------------------------------------------------------------------------------------------------
  // XVector3 Negation
  //--------------------------------------------------------------------------------------------------------------------

  /// \name  negation

  /// \brief  negates this XVector3 
  XM2_INLINE void negate();

  /// \brief  negates an XVector3 
  /// \param  v - the XVector3 to negate
  XM2_INLINE void negate(const XVector3Packed& v);

  //--------------------------------------------------------------------------------------------------------------------
  // XVector3 stdio
  //--------------------------------------------------------------------------------------------------------------------

  /// \name  file IO

  #if !XM2_NO_C_IO

  /// \brief  prints this XVector3  the specified text file
  /// \param  fp - the file to write to 
  void fprint32(FILE* fp) const;

  /// \brief  prints this XVector3  to the specified text file
  /// \param  fp - the file to write to 
  void fprint64(FILE* fp) const;

  /// \brief  reads a XVector3  from the specified text file
  /// \param  fp - the file to read from
  void fscan32(FILE* fp);

  /// \brief  reads a XVector3  from the specified text file
  /// \param  fp - the file to read from
  void fscan64(FILE* fp);

  /// \brief  prints this XVector3  to stdout
  void print32() const;

  /// \brief  prints this XVector3  to stdout
  void print64() const;

  /// \brief  writes this XVector3  to the specified binary file
  /// \param  fp - the file to write to 
  /// \param  flip_bytes - flag to indicate file byte order is different to the systems
  ///         byte order, in which case the bytes being read/written need to be swapped
  void fwrite32(FILE* fp, bool flip_bytes = false) const;

  /// \brief  writes this XVector3  to the specified binary file
  /// \param  fp - the file to write to 
  /// \param  flip_bytes - flag to indicate file byte order is different to the systems
  ///         byte order, in which case the bytes being read/written need to be swapped
  void fwrite64(FILE* fp, bool flip_bytes = false) const;

  /// \brief  reads a XVector3  from the specified binary file
  /// \param  fp - the file to read from
  /// \param  flip_bytes - flag to indicate file byte order is different to the systems
  ///         byte order, in which case the bytes being read/written need to be swapped
  void fread32(FILE* fp, bool flip_bytes = false);

  /// \brief  reads a XVector3  from the specified binary file
  /// \param  fp - the file to read from
  /// \param  flip_bytes - flag to indicate file byte order is different to the systems
  ///         byte order, in which case the bytes being read/written need to be swapped
  void fread64(FILE* fp, bool flip_bytes = false); 
  
  #endif

  //--------------------------------------------------------------------------------------------------------------------
  // C++ operators
  //--------------------------------------------------------------------------------------------------------------------

  /// \name  operators

  XM2_INLINE XVector3Packed operator-() const;

  XM2_INLINE bool operator == (const XVector3Packed& c) const;
  XM2_INLINE bool operator != (const XVector3Packed& c) const;

  XM2_INLINE const XVector3Packed& operator = (const XVector3Packed& c);
  XM2_INLINE const XVector3Packed& operator = (const XVector3& c);
  XM2_INLINE const XVector3Packed& operator = (const XVector4& c);

  XM2_INLINE const XVector3Packed& operator *= (const XVector3Packed& c);
  XM2_INLINE const XVector3Packed& operator /= (const XVector3Packed& c);
  XM2_INLINE const XVector3Packed& operator += (const XVector3Packed& c);
  XM2_INLINE const XVector3Packed& operator -= (const XVector3Packed& c);

  XM2_INLINE const XVector3Packed& operator += (XReal c);
  XM2_INLINE const XVector3Packed& operator -= (XReal c);
  XM2_INLINE const XVector3Packed& operator /= (XReal c);
  XM2_INLINE const XVector3Packed& operator *= (XReal c);

  XM2_INLINE XVector3Packed operator + (const XVector3Packed& c) const;
  XM2_INLINE XVector3Packed operator - (const XVector3Packed& c) const;
  XM2_INLINE XVector3Packed operator * (const XVector3Packed& c) const;
  XM2_INLINE XVector3Packed operator / (const XVector3Packed& c) const;

  XM2_INLINE XVector3Packed operator + (XReal c) const;
  XM2_INLINE XVector3Packed operator - (XReal c) const;
  XM2_INLINE XVector3Packed operator / (XReal c) const;
  XM2_INLINE XVector3Packed operator * (XReal c) const;

  friend XM2_INLINE XVector3Packed operator * (XReal f, const XVector3Packed& p);

  //--------------------------------------------------------------------------------------------------------------------
  // 16 Byte Aligned new / delete operators
  //--------------------------------------------------------------------------------------------------------------------

  XM2_MEMORY_OPERATORS

  /// \name  data

  //--------------------------------------------------------------------------------------------------------------------
  // Member variables
  //--------------------------------------------------------------------------------------------------------------------
  union 
  {
    struct 
    {
      /// x component 
      XReal x; 
      /// y component 
      XReal y;
      /// z component 
      XReal z;
    };
    XReal data[3];
  };


  /// \name  static array methods

  /// \brief  initialises this vector to 0,0,0
  /// \param  ptr - the array of XVector3s to zero
  /// \param  num - the number of XVector3s in the array
  static void arrayZero(XVector3Packed* ptr, int num);

  //--------------------------------------------------------------------------------------------------------------------
  // XVector3 Array Arithmetic
  //--------------------------------------------------------------------------------------------------------------------

  /// \brief  adds 2 XVector3 arrays together. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b[i];
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayAdd(XVector3Packed* output, const XVector3Packed* a, const XVector3Packed* b, int num);

  /// \brief  adds an XVector3 to each element in an XVector3 array. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayAdd(XVector3Packed* output, const XVector3Packed* a, const XVector3Packed& b, int num);

  /// \brief  adds 2 XVector3 arrays together. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b[i];
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayAdd(XVector3Packed* output, const XVector3Packed* a, const XVector3* b, int num);

  /// \brief  adds an XVector3 to each element in an XVector3 array. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayAdd(XVector3Packed* output, const XVector3Packed* a, const XVector3& b, int num);

  /// \brief  adds a float to each element in an XVector3 array. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayAdd(XVector3Packed* output, const XVector3Packed* a, XReal b, int num);

  /// \brief  subtracts an XVector3 array from another XVector3 array. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b[i];
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arraySub(XVector3Packed* output, const XVector3Packed* a, const XVector3Packed* b, int num);

  /// \brief  subtracts an XVector3 from an XVector3 array. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arraySub(XVector3Packed* output, const XVector3Packed* a, const XVector3Packed& b, int num);

  /// \brief  subtracts an XVector3 array from another XVector3 array. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b[i];
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arraySub(XVector3Packed* output, const XVector3Packed* a, const XVector3* b, int num);

  /// \brief  subtracts an XVector3 from an XVector3 array. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arraySub(XVector3Packed* output, const XVector3Packed* a, const XVector3& b, int num);

  /// \brief  subtracts a float from an XVector3 array. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  ///
  static void arraySub(XVector3Packed* output, const XVector3Packed* a, XReal b, int num);

  /// \brief  multiplies an array of XVector3s with an array of XVector3s. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b[i];
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayMul(XVector3Packed* output, const XVector3Packed* a, const XVector3Packed* b, int num);

  /// \brief  multiplies an array of XVector3s with an XVector3. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayMul(XVector3Packed* output, const XVector3Packed* a, const XVector3Packed& b, int num);

  /// \brief  multiplies an array of XVector3s with an array of XVector3s. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b[i];
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayMul(XVector3Packed* output, const XVector3Packed* a, const XVector3* b, int num);

  /// \brief  multiplies an array of XVector3s with an XVector3. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayMul(XVector3Packed* output, const XVector3Packed* a, const XVector3& b, int num);


  /// \brief  multiplies an array of XVector3s with a float. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayMul(XVector3Packed* output, const XVector3Packed* a, XReal b, int num);

  /// \brief  divides an array of XVector3s by an array of XVector3s. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b[i];
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayDiv(XVector3Packed* output, const XVector3Packed* a, const XVector3Packed* b, int num);

  /// \brief  divides an array of XVector3s by an XVector3. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayDiv(XVector3Packed* output, const XVector3Packed* a, const XVector3Packed& b, int num);

  /// \brief  divides an array of XVector3s by an array of XVector3s. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b[i];
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayDiv(XVector3Packed* output, const XVector3Packed* a, const XVector3* b, int num);

  /// \brief  divides an array of XVector3s by an XVector3. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayDiv(XVector3Packed* output, const XVector3Packed* a, const XVector3& b, int num);

  /// \brief  divides an array of XVector3s by a float. i.e.
  /// \code
  ///          for(i=0;i<num;++i)
  ///          {
  ///            output[i] = a[i] + b;
  ///          }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - input arg 0
  /// \param  b - input arg 1
  /// \param  num - the number of XVector3s in the arrays
  static void arrayDiv(XVector3Packed* output, const XVector3Packed* a, XReal b, int num);

  
  //--------------------------------------------------------------------------------------------------------------------
  // dot & cross products
  //--------------------------------------------------------------------------------------------------------------------

  /// \brief  performs the dot product on an array of XVector3
  /// \code
  ///         for(i=0;i<num;++i)
  ///         {
  ///           output[i] = dot( a[i], b[i] );
  ///         }
  /// \endcode
  /// \param  output - the dot product of a and b
  /// \param  a - first arg
  /// \param  b - second arg
  /// \param  num - the number of elements in the arrays
  static void arrayDot(XReal* product, const XVector3Packed* a, const XVector3Packed* b, int num);

  /// \brief  performs the dot product on an array of XVector3
  /// \code
  ///         for(i=0;i<num;++i)
  ///         {
  ///           output[i] = dot( a[i], b );
  ///         }
  /// \endcode
  /// \param  output - the dot product of a and b
  /// \param  a - first arg
  /// \param  b - second arg
  /// \param  num - the number of elements in the arrays
  static void arrayDot(XReal* product, const XVector3Packed* a, const XVector3Packed& b, int num);

  /// \brief  performs the cross product on an array of XVector3
  /// \code
  ///         for(i=0;i<num;++i)
  ///         {
  ///           output[i] = cross( a[i], b[i] );
  ///         }
  /// \endcode
  /// \param  output - the cross product of a and b
  /// \param  a - first arg
  /// \param  b - second arg
  /// \param  num - the number of elements in the arrays
  static void arrayCross(XVector3Packed* output, const XVector3Packed* a, const XVector3Packed* b, int num);

  /// \brief  performs the cross product on an array of XVector3
  /// \code
  ///         for(i=0;i<num;++i)
  ///         {
  ///           output[i] = cross( a[i], b );
  ///         }
  /// \endcode
  /// \param  output - the cross product of a and b
  /// \param  a - first arg
  /// \param  b - second arg
  /// \param  num - the number of elements in the arrays
  static void arrayCross(XVector3Packed* output, const XVector3Packed* a, const XVector3Packed& b, int num);


  /// \brief  normalises an array of XVector3
  /// \code
  ///         for(i=0;i<num;++i)
  ///         {
  ///           output[i] = normalise( a[i] );
  ///         }
  /// \endcode
  /// \param  output - the array to normalise
  /// \param  num - the number of elements in the array
  static XM2_INLINE void arrayNormalise(XVector3Packed* output, int num);

  /// \brief  normalises an array of XVector3
  /// \code
  ///         for(i=0;i<num;++i)
  ///         {
  ///           output[i] = normalise( a[i] );
  ///         }
  /// \endcode
  /// \param  output - the array to normalise
  /// \param  num - the number of elements in the array
  static void arrayNormalise(XVector3Packed* output, const XVector3Packed* input, int num);

  /// \brief  normalises an array of XVector3
  /// \code
  ///         for(i=0;i<num;++i)
  ///         {
  ///           output[i] = normalise( a[i] );
  ///         }
  /// \endcode
  /// \param  output - the array to normalise
  /// \param  num - the number of elements in the array
  static XM2_INLINE void arrayNegate(XVector3Packed* output, int num);

  /// \brief  normalises an array of XVector3
  /// \code
  ///         for(i=0;i<num;++i)
  ///         {
  ///           output[i] = normalise( a[i] );
  ///         }
  /// \endcode
  /// \param  output - the array to normalise
  /// \param  num - the number of elements in the array
  static void arrayNegate(XVector3Packed* output, const XVector3Packed* input, int num);

  //--------------------------------------------------------------------------------------------------------------------
  // XVector3SOA Lerps and Slerps
  //--------------------------------------------------------------------------------------------------------------------

  /// \name  lerp / slerp

  /// \brief  linearly interpolates (LERPS) between the XVector3 arrays a and b and 
  ///         stores the result in the output array.
  /// \code
  ///         for(i=0;i<num;++i)
  ///         {
  ///           output[i] = lerp( a[i], b[i], t );
  ///         }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - the first array
  /// \param  b - the 2nd array
  /// \param  t - the 0 to 1 interpolation control value
  /// \param  num - the number of elements in the arrays
  static void arrayLerp(XVector3Packed* output,
                        const XVector3Packed* a, const XVector3Packed* b,
                        XReal t, int num);

  /// \brief  interpolates using a bezier function between a,b,c and d. 
  /// \code
  ///         for(i=0;i<num;++i)
  ///         {
  ///           output[i] = bezier( a[i], b[i], c[i], d[i], t );
  ///         }
  /// \endcode
  /// \param  output - the output array
  /// \param  a - the first array
  /// \param  b - the 2nd array
  /// \param  c - the 3rd array
  /// \param  d - the 4th array
  /// \param  t - the 0 to 1 interpolation control value
  /// \param  num - the number of elements in the arrays
  static void arrayBezier(XVector3Packed* output,
                          const XVector3Packed* a, const XVector3Packed* b,
                          const XVector3Packed* c, const XVector3Packed* d,
                          XReal t, int num);
}
XM2_ALIGN_SUFFIX(16);

#if !XM2_NO_STREAM_IO
XM2EXPORT std::ostream& operator<<(std::ostream& ofs, const XVector3Packed& c);
XM2EXPORT std::istream& operator>>(std::istream& ofs ,XVector3Packed& c);
#endif
}
//----------------------------------------------------------------------------------------------------------------------
#include "XM2/Vector3.h"
#include "XM2/Vector4.h"
#include "XM2/inl/Vector3Packed.inl"
//----------------------------------------------------------------------------------------------------------------------
