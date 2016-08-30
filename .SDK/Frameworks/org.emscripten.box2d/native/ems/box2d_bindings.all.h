//// box2d.clean.h
#line 1 "root.h"
#line 1 "root.h"
#line 1 "<built-in>"
#line 1 "<built-in>"
#line 144 "<built-in>"
#line 1 "<command line>"
#line 1 "<built-in>"
#line 1 "root.h"
#line 20 "root.h"
#line 1 "Box2D_v2.2.1\\Box2D/Box2D.h"
#line 34 "Box2D_v2.2.1\\Box2D/Box2D.h"
#line 1 "Box2D_v2.2.1\\Box2D/Common/b2Settings.h"
#line 23 "Box2D_v2.2.1\\Box2D/Common/b2Settings.h"
#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\assert.h"
#line 14 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\assert.h"
#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
#line 56 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\sal.h"
#line 160 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\sal.h"
#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include/codeanalysis\\sourceannotations.h"
#line 160 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\sal.h"
#line 56 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"





#pragma pack(push,_CRT_PACKING)


#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\vadefs.h"
#line 29 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\vadefs.h"
#pragma pack(push,_CRT_PACKING)
#line 48 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\vadefs.h"
typedef __w64 unsigned int uintptr_t;
#line 57 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\vadefs.h"
typedef char * va_list;
#line 146 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\vadefs.h"
#pragma pack(pop)
#line 63 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
#line 402 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
typedef __w64 unsigned int size_t;






typedef size_t rsize_t;
#line 418 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
typedef __w64 int intptr_t;
#line 436 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
typedef __w64 int ptrdiff_t;





typedef unsigned short wchar_t;




typedef unsigned short wint_t;
typedef unsigned short wctype_t;
#line 469 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
typedef int errno_t;



typedef __w64 long __time32_t;




typedef __int64 __time64_t;







typedef __time64_t time_t;
#line 545 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
         void __cdecl _invalid_parameter_noinfo(void);
         __declspec(noreturn) void __cdecl _invalid_parameter_noinfo_noreturn(void);


        __declspec(noreturn)
void __cdecl _invoke_watson( const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t);
#line 1953 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct * pthreadlocinfo;
typedef struct threadmbcinfostruct * pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct
{
    pthreadlocinfo locinfo;
    pthreadmbcinfo mbcinfo;
} _locale_tstruct, *_locale_t;


typedef struct tagLC_ID {
        unsigned short wLanguage;
        unsigned short wCountry;
        unsigned short wCodePage;
} LC_ID, *LPLC_ID;




typedef struct threadlocaleinfostruct {
        int refcount;
        unsigned int lc_codepage;
        unsigned int lc_collate_cp;
        size_t lc_handle[6];
        LC_ID lc_id[6];
        struct {
            char *locale;
            wchar_t *wlocale;
            int *refcount;
            int *wrefcount;
        } lc_category[6];
        int lc_clike;
        int mb_cur_max;
        int * lconv_intl_refcount;
        int * lconv_num_refcount;
        int * lconv_mon_refcount;
        struct lconv * lconv;
        int * ctype1_refcount;
        unsigned short * ctype1;
        const unsigned short * pctype;
        const unsigned char * pclmap;
        const unsigned char * pcumap;
        struct __lc_time_data * lc_time_curr;
} threadlocinfo;
#line 2036 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
#pragma pack(pop)
#line 14 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\assert.h"
#line 23 "Box2D_v2.2.1\\Box2D/Common/b2Settings.h"

#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\math.h"
#line 18 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\math.h"
#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
#line 18 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\math.h"






#pragma pack(push,_CRT_PACKING)
#line 37 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\math.h"
struct _exception {
        int type;
        char *name;
        double arg1;
        double arg2;
        double retval;
        } ;
#line 54 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\math.h"
struct _complex {
        double x,y;
        } ;
#line 88 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\math.h"
        extern double _HUGE;
#line 101 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\math.h"
        int __cdecl abs( int _X);
        long __cdecl labs( long _X);
        long long __cdecl llabs( long long _X);


        double __cdecl acos( double _X);
        double __cdecl asin( double _X);
        double __cdecl atan( double _X);
        double __cdecl atan2( double _Y, double _X);

                       double __cdecl _copysign ( double _Number, double _Sign);
                       double __cdecl _chgsign ( double _X);


        double __cdecl cos( double _X);
        double __cdecl cosh( double _X);
        double __cdecl exp( double _X);
                   double __cdecl fabs( double _X);
        double __cdecl fmod( double _X, double _Y);
        double __cdecl log( double _X);
        double __cdecl log10( double _X);
        double __cdecl pow( double _X, double _Y);
        double __cdecl sin( double _X);
        double __cdecl sinh( double _X);
        double __cdecl tan( double _X);
        double __cdecl tanh( double _X);
        double __cdecl sqrt( double _X);


                       double __cdecl atof( const char *_String);
                       double __cdecl _atof_l( const char *_String, _locale_t _Locale);


        double __cdecl _cabs( struct _complex _Complex_value);
        double __cdecl ceil( double _X);
        double __cdecl floor( double _X);
        double __cdecl frexp( double _X, int * _Y);
        double __cdecl _hypot( double _X, double _Y);
        float __cdecl _hypotf( float _X, float _Y);
        double __cdecl _j0( double _X );
        double __cdecl _j1( double _X );
        double __cdecl _jn(int _X, double _Y);
        double __cdecl ldexp( double _X, int _Y);





        int __cdecl _matherr( struct _exception * _Except);


        double __cdecl modf( double _X, double * _Y);

        double __cdecl _y0( double _X);
        double __cdecl _y1( double _X);
        double __cdecl _yn( int _X, double _Y);




static __inline double __cdecl hypot( double _X, double _Y)
{
    return _hypot(_X, _Y);
}

static __inline float __cdecl hypotf( float _X, float _Y)
{
    return _hypotf(_X, _Y);
}





        int __cdecl _set_SSE2_enable( int _Flag);
#line 460 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\math.h"
        extern double HUGE;




__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_cabs" ". See online help for details.")) double __cdecl cabs( struct _complex _X);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_j0" ". See online help for details.")) double __cdecl j0( double _X);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_j1" ". See online help for details.")) double __cdecl j1( double _X);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_jn" ". See online help for details.")) double __cdecl jn( int _X, double _Y);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_y0" ". See online help for details.")) double __cdecl y0( double _X);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_y1" ". See online help for details.")) double __cdecl y1( double _X);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_yn" ". See online help for details.")) double __cdecl yn( int _X, double _Y);
#line 599 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\math.h"
#pragma pack(pop)
#line 24 "Box2D_v2.2.1\\Box2D/Common/b2Settings.h"
#line 33 "Box2D_v2.2.1\\Box2D/Common/b2Settings.h"
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef float float32;
typedef double float64;
#line 135 "Box2D_v2.2.1\\Box2D/Common/b2Settings.h"
void* b2Alloc(int32 size);


void b2Free(void* mem);


void b2Log(const char* string, ...);



struct b2Version
{
 int32 major;
 int32 minor;
 int32 revision;
};


extern b2Version b2_version;
#line 34 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Common/b2Draw.h"
#line 19 "Box2D_v2.2.1\\Box2D/Common/b2Draw.h"
#line 1 "Box2D_v2.2.1\\Box2D/Common/b2Math.h"
#line 25 "Box2D_v2.2.1\\Box2D/Common/b2Math.h"
#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\math.h"
#line 25 "Box2D_v2.2.1\\Box2D/Common/b2Math.h"

#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\float.h"
#line 21 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\float.h"
#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
#line 21 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\float.h"

#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtwrn.h"
#line 17 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtwrn.h"
#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
#line 17 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtwrn.h"
#line 22 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\float.h"
#line 83 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\float.h"
                                  unsigned int __cdecl _clearfp(void);
#pragma warning(push)
#pragma warning(disable: 4141)
 __declspec(deprecated("This function or variable may be unsafe. Consider using " "_controlfp_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.")) unsigned int __cdecl _controlfp( unsigned int _NewValue, unsigned int _Mask);
#pragma warning(pop)
 void __cdecl _set_controlfp( unsigned int _NewValue, unsigned int _Mask);
                                  errno_t __cdecl _controlfp_s( unsigned int *_CurrentState, unsigned int _NewValue, unsigned int _Mask);
                                  unsigned int __cdecl _statusfp(void);
                                  void __cdecl _fpreset(void);


                                  void __cdecl _statusfp2( unsigned int *_X86_status, unsigned int *_SSE2_status);
#line 172 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\float.h"
                                  unsigned int __cdecl _control87( unsigned int _NewValue, unsigned int _Mask);

                                  int __cdecl __control87_2( unsigned int _NewValue, unsigned int _Mask,
                                            unsigned int* _X86_cw, unsigned int* _Sse2_cw);




                       extern int * __cdecl __fpecode(void);
#line 216 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\float.h"
                       double __cdecl _scalb( double _X, long _Y);
                       double __cdecl _logb( double _X);
                       double __cdecl _nextafter( double _X, double _Y);
                       int __cdecl _finite( double _X);
                       int __cdecl _isnan( double _X);
                       int __cdecl _fpclass( double _X);
#line 247 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\float.h"
                                  void __cdecl fpreset(void);
#line 26 "Box2D_v2.2.1\\Box2D/Common/b2Math.h"

#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\stddef.h"
#line 20 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\stddef.h"
#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
#line 20 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\stddef.h"
#line 47 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\stddef.h"
        extern int * __cdecl _errno(void);


errno_t __cdecl _set_errno( int _Value);
errno_t __cdecl _get_errno( int * _Value);
#line 73 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\stddef.h"
        extern size_t __cdecl __threadid(void);

        extern uintptr_t __cdecl __threadhandle(void);
#line 27 "Box2D_v2.2.1\\Box2D/Common/b2Math.h"

#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\limits.h"
#line 17 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\limits.h"
#line 1 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\crtdefs.h"
#line 17 "C:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\include\\limits.h"
#line 28 "Box2D_v2.2.1\\Box2D/Common/b2Math.h"
#line 38 "Box2D_v2.2.1\\Box2D/Common/b2Math.h"
inline bool b2IsValid(float32 x)
{
 if (x != x)
 {

  return false;
 }

 float32 infinity = std::numeric_limits<float32>::infinity();
 return -infinity < x && x < infinity;
}


inline float32 b2InvSqrt(float32 x)
{
 union
 {
  float32 x;
  int32 i;
 } convert;

 convert.x = x;
 float32 xhalf = 0.5f * x;
 convert.i = 0x5f3759df - (convert.i >> 1);
 x = convert.x;
 x = x * (1.5f - xhalf * x * x);
 return x;
}





struct b2Vec2
{

 b2Vec2() {}


 b2Vec2(float32 x, float32 y) : x(x), y(y) {}


 void SetZero() { x = 0.0f; y = 0.0f; }


 void Set(float32 x_, float32 y_) { x = x_; y = y_; }


 b2Vec2 operator -() const { b2Vec2 v; v.Set(-x, -y); return v; }


 float32 operator () (int32 i) const
 {
  return (&x)[i];
 }


 float32& operator () (int32 i)
 {
  return (&x)[i];
 }


 void operator += (const b2Vec2& v)
 {
  x += v.x; y += v.y;
 }


 void operator -= (const b2Vec2& v)
 {
  x -= v.x; y -= v.y;
 }


 void operator *= (float32 a)
 {
  x *= a; y *= a;
 }


 float32 Length() const
 {
  return std::sqrt(x * x + y * y);
 }



 float32 LengthSquared() const
 {
  return x * x + y * y;
 }


 float32 Normalize()
 {
  float32 length = Length();
  if (length < 1.192092896e-07F)
  {
   return 0.0f;
  }
  float32 invLength = 1.0f / length;
  x *= invLength;
  y *= invLength;

  return length;
 }


 bool IsValid() const
 {
  return b2IsValid(x) && b2IsValid(y);
 }


 b2Vec2 Skew() const
 {
  return b2Vec2(-y, x);
 }

 float32 x;
 float32 y;
};


struct b2Vec3
{

 b2Vec3() {}


 b2Vec3(float32 x, float32 y, float32 z) : x(x), y(y), z(z) {}


 void SetZero() { x = 0.0f; y = 0.0f; z = 0.0f; }


 void Set(float32 x_, float32 y_, float32 z_) { x = x_; y = y_; z = z_; }


 b2Vec3 operator -() const { b2Vec3 v; v.Set(-x, -y, -z); return v; }


 void operator += (const b2Vec3& v)
 {
  x += v.x; y += v.y; z += v.z;
 }


 void operator -= (const b2Vec3& v)
 {
  x -= v.x; y -= v.y; z -= v.z;
 }


 void operator *= (float32 s)
 {
  x *= s; y *= s; z *= s;
 }

 float32 x, y, z;
};


struct b2Mat22
{

 b2Mat22() {}


 b2Mat22(const b2Vec2& c1, const b2Vec2& c2)
 {
  ex = c1;
  ey = c2;
 }


 b2Mat22(float32 a11, float32 a12, float32 a21, float32 a22)
 {
  ex.x = a11; ex.y = a21;
  ey.x = a12; ey.y = a22;
 }


 void Set(const b2Vec2& c1, const b2Vec2& c2)
 {
  ex = c1;
  ey = c2;
 }


 void SetIdentity()
 {
  ex.x = 1.0f; ey.x = 0.0f;
  ex.y = 0.0f; ey.y = 1.0f;
 }


 void SetZero()
 {
  ex.x = 0.0f; ey.x = 0.0f;
  ex.y = 0.0f; ey.y = 0.0f;
 }

 b2Mat22 GetInverse() const
 {
  float32 a = ex.x, b = ey.x, c = ex.y, d = ey.y;
  b2Mat22 B;
  float32 det = a * d - b * c;
  if (det != 0.0f)
  {
   det = 1.0f / det;
  }
  B.ex.x = det * d; B.ey.x = -det * b;
  B.ex.y = -det * c; B.ey.y = det * a;
  return B;
 }



 b2Vec2 Solve(const b2Vec2& b) const
 {
  float32 a11 = ex.x, a12 = ey.x, a21 = ex.y, a22 = ey.y;
  float32 det = a11 * a22 - a12 * a21;
  if (det != 0.0f)
  {
   det = 1.0f / det;
  }
  b2Vec2 x;
  x.x = det * (a22 * b.x - a12 * b.y);
  x.y = det * (a11 * b.y - a21 * b.x);
  return x;
 }

 b2Vec2 ex, ey;
};


struct b2Mat33
{

 b2Mat33() {}


 b2Mat33(const b2Vec3& c1, const b2Vec3& c2, const b2Vec3& c3)
 {
  ex = c1;
  ey = c2;
  ez = c3;
 }


 void SetZero()
 {
  ex.SetZero();
  ey.SetZero();
  ez.SetZero();
 }



 b2Vec3 Solve33(const b2Vec3& b) const;




 b2Vec2 Solve22(const b2Vec2& b) const;



 void GetInverse22(b2Mat33* M) const;



 void GetSymInverse33(b2Mat33* M) const;

 b2Vec3 ex, ey, ez;
};


struct b2Rot
{
 b2Rot() {}


 explicit b2Rot(float32 angle)
 {

  s = ((float)sin((double)(angle)));
  c = ((float)cos((double)(angle)));
 }


 void Set(float32 angle)
 {

  s = ((float)sin((double)(angle)));
  c = ((float)cos((double)(angle)));
 }


 void SetIdentity()
 {
  s = 0.0f;
  c = 1.0f;
 }


 float32 GetAngle() const
 {
  return std::atan2(s, c);
 }


 b2Vec2 GetXAxis() const
 {
  return b2Vec2(c, s);
 }


 b2Vec2 GetYAxis() const
 {
  return b2Vec2(-s, c);
 }


 float32 s, c;
};



struct b2Transform
{

 b2Transform() {}


 b2Transform(const b2Vec2& position, const b2Rot& rotation) : p(position), q(rotation) {}


 void SetIdentity()
 {
  p.SetZero();
  q.SetIdentity();
 }


 void Set(const b2Vec2& position, float32 angle)
 {
  p = position;
  q.Set(angle);
 }

 b2Vec2 p;
 b2Rot q;
};





struct b2Sweep
{


 void GetTransform(b2Transform* xfb, float32 beta) const;



 void Advance(float32 alpha);


 void Normalize();

 b2Vec2 localCenter;
 b2Vec2 c0, c;
 float32 a0, a;



 float32 alpha0;
};


extern const b2Vec2 b2Vec2_zero;


inline float32 b2Dot(const b2Vec2& a, const b2Vec2& b)
{
 return a.x * b.x + a.y * b.y;
}


inline float32 b2Cross(const b2Vec2& a, const b2Vec2& b)
{
 return a.x * b.y - a.y * b.x;
}



inline b2Vec2 b2Cross(const b2Vec2& a, float32 s)
{
 return b2Vec2(s * a.y, -s * a.x);
}



inline b2Vec2 b2Cross(float32 s, const b2Vec2& a)
{
 return b2Vec2(-s * a.y, s * a.x);
}



inline b2Vec2 b2Mul(const b2Mat22& A, const b2Vec2& v)
{
 return b2Vec2(A.ex.x * v.x + A.ey.x * v.y, A.ex.y * v.x + A.ey.y * v.y);
}



inline b2Vec2 b2MulT(const b2Mat22& A, const b2Vec2& v)
{
 return b2Vec2(b2Dot(v, A.ex), b2Dot(v, A.ey));
}


inline b2Vec2 operator + (const b2Vec2& a, const b2Vec2& b)
{
 return b2Vec2(a.x + b.x, a.y + b.y);
}


inline b2Vec2 operator - (const b2Vec2& a, const b2Vec2& b)
{
 return b2Vec2(a.x - b.x, a.y - b.y);
}

inline b2Vec2 operator * (float32 s, const b2Vec2& a)
{
 return b2Vec2(s * a.x, s * a.y);
}

inline bool operator == (const b2Vec2& a, const b2Vec2& b)
{
 return a.x == b.x && a.y == b.y;
}

inline float32 b2Distance(const b2Vec2& a, const b2Vec2& b)
{
 b2Vec2 c = a - b;
 return c.Length();
}

inline float32 b2DistanceSquared(const b2Vec2& a, const b2Vec2& b)
{
 b2Vec2 c = a - b;
 return b2Dot(c, c);
}

inline b2Vec3 operator * (float32 s, const b2Vec3& a)
{
 return b2Vec3(s * a.x, s * a.y, s * a.z);
}


inline b2Vec3 operator + (const b2Vec3& a, const b2Vec3& b)
{
 return b2Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}


inline b2Vec3 operator - (const b2Vec3& a, const b2Vec3& b)
{
 return b2Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}


inline float32 b2Dot(const b2Vec3& a, const b2Vec3& b)
{
 return a.x * b.x + a.y * b.y + a.z * b.z;
}


inline b2Vec3 b2Cross(const b2Vec3& a, const b2Vec3& b)
{
 return b2Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline b2Mat22 operator + (const b2Mat22& A, const b2Mat22& B)
{
 return b2Mat22(A.ex + B.ex, A.ey + B.ey);
}


inline b2Mat22 b2Mul(const b2Mat22& A, const b2Mat22& B)
{
 return b2Mat22(b2Mul(A, B.ex), b2Mul(A, B.ey));
}


inline b2Mat22 b2MulT(const b2Mat22& A, const b2Mat22& B)
{
 b2Vec2 c1(b2Dot(A.ex, B.ex), b2Dot(A.ey, B.ex));
 b2Vec2 c2(b2Dot(A.ex, B.ey), b2Dot(A.ey, B.ey));
 return b2Mat22(c1, c2);
}


inline b2Vec3 b2Mul(const b2Mat33& A, const b2Vec3& v)
{
 return v.x * A.ex + v.y * A.ey + v.z * A.ez;
}


inline b2Vec2 b2Mul22(const b2Mat33& A, const b2Vec2& v)
{
 return b2Vec2(A.ex.x * v.x + A.ey.x * v.y, A.ex.y * v.x + A.ey.y * v.y);
}


inline b2Rot b2Mul(const b2Rot& q, const b2Rot& r)
{




 b2Rot qr;
 qr.s = q.s * r.c + q.c * r.s;
 qr.c = q.c * r.c - q.s * r.s;
 return qr;
}


inline b2Rot b2MulT(const b2Rot& q, const b2Rot& r)
{




 b2Rot qr;
 qr.s = q.c * r.s - q.s * r.c;
 qr.c = q.c * r.c + q.s * r.s;
 return qr;
}


inline b2Vec2 b2Mul(const b2Rot& q, const b2Vec2& v)
{
 return b2Vec2(q.c * v.x - q.s * v.y, q.s * v.x + q.c * v.y);
}


inline b2Vec2 b2MulT(const b2Rot& q, const b2Vec2& v)
{
 return b2Vec2(q.c * v.x + q.s * v.y, -q.s * v.x + q.c * v.y);
}

inline b2Vec2 b2Mul(const b2Transform& T, const b2Vec2& v)
{
 float32 x = (T.q.c * v.x - T.q.s * v.y) + T.p.x;
 float32 y = (T.q.s * v.x + T.q.c * v.y) + T.p.y;

 return b2Vec2(x, y);
}

inline b2Vec2 b2MulT(const b2Transform& T, const b2Vec2& v)
{
 float32 px = v.x - T.p.x;
 float32 py = v.y - T.p.y;
 float32 x = (T.q.c * px + T.q.s * py);
 float32 y = (-T.q.s * px + T.q.c * py);

 return b2Vec2(x, y);
}



inline b2Transform b2Mul(const b2Transform& A, const b2Transform& B)
{
 b2Transform C;
 C.q = b2Mul(A.q, B.q);
 C.p = b2Mul(A.q, B.p) + A.p;
 return C;
}



inline b2Transform b2MulT(const b2Transform& A, const b2Transform& B)
{
 b2Transform C;
 C.q = b2MulT(A.q, B.q);
 C.p = b2MulT(A.q, B.p - A.p);
 return C;
}

template <typename T>
inline T b2Abs(T a)
{
 return a > T(0) ? a : -a;
}

inline b2Vec2 b2Abs(const b2Vec2& a)
{
 return b2Vec2(b2Abs(a.x), b2Abs(a.y));
}

inline b2Mat22 b2Abs(const b2Mat22& A)
{
 return b2Mat22(b2Abs(A.ex), b2Abs(A.ey));
}

template <typename T>
inline T b2Min(T a, T b)
{
 return a < b ? a : b;
}

inline b2Vec2 b2Min(const b2Vec2& a, const b2Vec2& b)
{
 return b2Vec2(b2Min(a.x, b.x), b2Min(a.y, b.y));
}

template <typename T>
inline T b2Max(T a, T b)
{
 return a > b ? a : b;
}

inline b2Vec2 b2Max(const b2Vec2& a, const b2Vec2& b)
{
 return b2Vec2(b2Max(a.x, b.x), b2Max(a.y, b.y));
}

template <typename T>
inline T b2Clamp(T a, T low, T high)
{
 return b2Max(low, b2Min(a, high));
}

inline b2Vec2 b2Clamp(const b2Vec2& a, const b2Vec2& low, const b2Vec2& high)
{
 return b2Max(low, b2Min(a, high));
}

template<typename T> inline void b2Swap(T& a, T& b)
{
 T tmp = a;
 a = b;
 b = tmp;
}






inline uint32 b2NextPowerOfTwo(uint32 x)
{
 x |= (x >> 1);
 x |= (x >> 2);
 x |= (x >> 4);
 x |= (x >> 8);
 x |= (x >> 16);
 return x + 1;
}

inline bool b2IsPowerOfTwo(uint32 x)
{
 bool result = x > 0 && (x & (x - 1)) == 0;
 return result;
}

inline void b2Sweep::GetTransform(b2Transform* xf, float32 beta) const
{
 xf->p = (1.0f - beta) * c0 + beta * c;
 float32 angle = (1.0f - beta) * a0 + beta * a;
 xf->q.Set(angle);


 xf->p -= b2Mul(xf->q, localCenter);
}

inline void b2Sweep::Advance(float32 alpha)
{
 ((void)0);
 float32 beta = (alpha - alpha0) / (1.0f - alpha0);
 c0 = (1.0f - beta) * c0 + beta * c;
 a0 = (1.0f - beta) * a0 + beta * a;
 alpha0 = alpha;
}


inline void b2Sweep::Normalize()
{
 float32 twoPi = 2.0f * 3.14159265359f;
 float32 d = twoPi * ((float)floor((double)(a0 / twoPi)));
 a0 -= d;
 a -= d;
}
#line 19 "Box2D_v2.2.1\\Box2D/Common/b2Draw.h"




struct b2Color
{
 b2Color() {}
 b2Color(float32 r, float32 g, float32 b) : r(r), g(g), b(b) {}
 void Set(float32 ri, float32 gi, float32 bi) { r = ri; g = gi; b = bi; }
 float32 r;
 float32 g;
 float32 b;
};




class b2Draw
{
public:
 b2Draw();

 virtual ~b2Draw() {}

 enum
 {
  e_shapeBit = 0x0001,
  e_jointBit = 0x0002,
  e_aabbBit = 0x0004,
  e_pairBit = 0x0008,
  e_centerOfMassBit = 0x0010
 };


 void SetFlags(uint32 flags);


 uint32 GetFlags() const;


 void AppendFlags(uint32 flags);


 void ClearFlags(uint32 flags);


 virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}


 virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}


 virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}


 virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {}


 virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}



 virtual void DrawTransform(const b2Transform& xf) {}

protected:
 uint32 m_drawFlags;
};
#line 35 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Common/b2Timer.h"
#line 23 "Box2D_v2.2.1\\Box2D/Common/b2Timer.h"
class b2Timer
{
public:


 b2Timer();


 void Reset();


 float32 GetMilliseconds() const;

private:


 float64 m_start;
 static float64 s_invFrequency;




};
#line 36 "Box2D_v2.2.1\\Box2D/Box2D.h"


#line 1 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2CircleShape.h"
#line 22 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2CircleShape.h"
#line 1 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2Shape.h"
#line 22 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2Shape.h"
#line 1 "Box2D_v2.2.1\\Box2D/Common/b2BlockAllocator.h"
#line 24 "Box2D_v2.2.1\\Box2D/Common/b2BlockAllocator.h"
const int32 b2_chunkSize = 16 * 1024;
const int32 b2_maxBlockSize = 640;
const int32 b2_blockSizes = 14;
const int32 b2_chunkArrayIncrement = 128;

struct b2Block;
struct b2Chunk;




class b2BlockAllocator
{
public:
 b2BlockAllocator();
 ~b2BlockAllocator();


 void* Allocate(int32 size);


 void Free(void* p, int32 size);

 void Clear();

private:

 b2Chunk* m_chunks;
 int32 m_chunkCount;
 int32 m_chunkSpace;

 b2Block* m_freeLists[b2_blockSizes];

 static int32 s_blockSizes[b2_blockSizes];
 static uint8 s_blockSizeLookup[b2_maxBlockSize + 1];
 static bool s_blockSizeLookupInitialized;
};
#line 22 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2Shape.h"


#line 1 "Box2D_v2.2.1\\Box2D/Collision/b2Collision.h"
#line 31 "Box2D_v2.2.1\\Box2D/Collision/b2Collision.h"
class b2Shape;
class b2CircleShape;
class b2EdgeShape;
class b2PolygonShape;

const uint8 b2_nullFeature = 0xff;



struct b2ContactFeature
{
 enum Type
 {
  e_vertex = 0,
  e_face = 1
 };

 uint8 indexA;
 uint8 indexB;
 uint8 typeA;
 uint8 typeB;
};


union b2ContactID
{
 b2ContactFeature cf;
 uint32 key;
};
#line 71 "Box2D_v2.2.1\\Box2D/Collision/b2Collision.h"
struct b2ManifoldPoint
{
 b2Vec2 localPoint;
 float32 normalImpulse;
 float32 tangentImpulse;
 b2ContactID id;
};
#line 95 "Box2D_v2.2.1\\Box2D/Collision/b2Collision.h"
struct b2Manifold
{
 enum Type
 {
  e_circles,
  e_faceA,
  e_faceB
 };

 b2ManifoldPoint points[2];
 b2Vec2 localNormal;
 b2Vec2 localPoint;
 Type type;
 int32 pointCount;
};


struct b2WorldManifold
{




 void Initialize(const b2Manifold* manifold,
     const b2Transform& xfA, float32 radiusA,
     const b2Transform& xfB, float32 radiusB);

 b2Vec2 normal;
 b2Vec2 points[2];
};


enum b2PointState
{
 b2_nullState,
 b2_addState,
 b2_persistState,
 b2_removeState
};



void b2GetPointStates(b2PointState state1[2], b2PointState state2[2],
       const b2Manifold* manifold1, const b2Manifold* manifold2);


struct b2ClipVertex
{
 b2Vec2 v;
 b2ContactID id;
};


struct b2RayCastInput
{
 b2Vec2 p1, p2;
 float32 maxFraction;
};



struct b2RayCastOutput
{
 b2Vec2 normal;
 float32 fraction;
};



struct b2AABB
{
 b2AABB() {}


 bool IsValid() const;


 b2Vec2 GetCenter() const
 {
  return 0.5f * (lowerBound + upperBound);
 }


 b2Vec2 GetExtents() const
 {
  return 0.5f * (upperBound - lowerBound);
 }


 float32 GetPerimeter() const
 {
  float32 wx = upperBound.x - lowerBound.x;
  float32 wy = upperBound.y - lowerBound.y;
  return 2.0f * (wx + wy);
 }


 void Combine(const b2AABB& aabb)
 {
  lowerBound = b2Min(lowerBound, aabb.lowerBound);
  upperBound = b2Max(upperBound, aabb.upperBound);
 }


 void Combine(const b2AABB& aabb1, const b2AABB& aabb2)
 {
  lowerBound = b2Min(aabb1.lowerBound, aabb2.lowerBound);
  upperBound = b2Max(aabb1.upperBound, aabb2.upperBound);
 }


 bool Contains(const b2AABB& aabb) const
 {
  bool result = true;
  result = result && lowerBound.x <= aabb.lowerBound.x;
  result = result && lowerBound.y <= aabb.lowerBound.y;
  result = result && aabb.upperBound.x <= upperBound.x;
  result = result && aabb.upperBound.y <= upperBound.y;
  return result;
 }

 bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input) const;

 b2Vec2 lowerBound;
 b2Vec2 upperBound;
};


void b2CollideCircles(b2Manifold* manifold,
       const b2CircleShape* circleA, const b2Transform& xfA,
       const b2CircleShape* circleB, const b2Transform& xfB);


void b2CollidePolygonAndCircle(b2Manifold* manifold,
          const b2PolygonShape* polygonA, const b2Transform& xfA,
          const b2CircleShape* circleB, const b2Transform& xfB);


void b2CollidePolygons(b2Manifold* manifold,
        const b2PolygonShape* polygonA, const b2Transform& xfA,
        const b2PolygonShape* polygonB, const b2Transform& xfB);


void b2CollideEdgeAndCircle(b2Manifold* manifold,
          const b2EdgeShape* polygonA, const b2Transform& xfA,
          const b2CircleShape* circleB, const b2Transform& xfB);


void b2CollideEdgeAndPolygon(b2Manifold* manifold,
          const b2EdgeShape* edgeA, const b2Transform& xfA,
          const b2PolygonShape* circleB, const b2Transform& xfB);


int32 b2ClipSegmentToLine(b2ClipVertex vOut[2], const b2ClipVertex vIn[2],
       const b2Vec2& normal, float32 offset, int32 vertexIndexA);


bool b2TestOverlap( const b2Shape* shapeA, int32 indexA,
     const b2Shape* shapeB, int32 indexB,
     const b2Transform& xfA, const b2Transform& xfB);



inline bool b2AABB::IsValid() const
{
 b2Vec2 d = upperBound - lowerBound;
 bool valid = d.x >= 0.0f && d.y >= 0.0f;
 valid = valid && lowerBound.IsValid() && upperBound.IsValid();
 return valid;
}

inline bool b2TestOverlap(const b2AABB& a, const b2AABB& b)
{
 b2Vec2 d1, d2;
 d1 = b.lowerBound - a.upperBound;
 d2 = a.lowerBound - b.upperBound;

 if (d1.x > 0.0f || d1.y > 0.0f)
  return false;

 if (d2.x > 0.0f || d2.y > 0.0f)
  return false;

 return true;
}
#line 24 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2Shape.h"



struct b2MassData
{

 float32 mass;


 b2Vec2 center;


 float32 I;
};




class b2Shape
{
public:

 enum Type
 {
  e_circle = 0,
  e_edge = 1,
  e_polygon = 2,
  e_chain = 3,
  e_typeCount = 4
 };

 virtual ~b2Shape() {}


 virtual b2Shape* Clone(b2BlockAllocator* allocator) const = 0;



 Type GetType() const;


 virtual int32 GetChildCount() const = 0;




 virtual bool TestPoint(const b2Transform& xf, const b2Vec2& p) const = 0;






 virtual bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input,
      const b2Transform& transform, int32 childIndex) const = 0;





 virtual void ComputeAABB(b2AABB* aabb, const b2Transform& xf, int32 childIndex) const = 0;





 virtual void ComputeMass(b2MassData* massData, float32 density) const = 0;

 Type m_type;
 float32 m_radius;
};

inline b2Shape::Type b2Shape::GetType() const
{
 return m_type;
}
#line 22 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2CircleShape.h"



class b2CircleShape : public b2Shape
{
public:
 b2CircleShape();


 b2Shape* Clone(b2BlockAllocator* allocator) const;


 int32 GetChildCount() const;


 bool TestPoint(const b2Transform& transform, const b2Vec2& p) const;


 bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input,
    const b2Transform& transform, int32 childIndex) const;


 void ComputeAABB(b2AABB* aabb, const b2Transform& transform, int32 childIndex) const;


 void ComputeMass(b2MassData* massData, float32 density) const;


 int32 GetSupport(const b2Vec2& d) const;


 const b2Vec2& GetSupportVertex(const b2Vec2& d) const;


 int32 GetVertexCount() const { return 1; }


 const b2Vec2& GetVertex(int32 index) const;


 b2Vec2 m_p;
};

inline b2CircleShape::b2CircleShape()
{
 m_type = e_circle;
 m_radius = 0.0f;
 m_p.SetZero();
}

inline int32 b2CircleShape::GetSupport(const b2Vec2 &d) const
{
 ((void)(d));
 return 0;
}

inline const b2Vec2& b2CircleShape::GetSupportVertex(const b2Vec2 &d) const
{
 ((void)(d));
 return m_p;
}

inline const b2Vec2& b2CircleShape::GetVertex(int32 index) const
{
 ((void)(index));
 ((void)0);
 return m_p;
}
#line 38 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2EdgeShape.h"
#line 27 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2EdgeShape.h"
class b2EdgeShape : public b2Shape
{
public:
 b2EdgeShape();


 void Set(const b2Vec2& v1, const b2Vec2& v2);


 b2Shape* Clone(b2BlockAllocator* allocator) const;


 int32 GetChildCount() const;


 bool TestPoint(const b2Transform& transform, const b2Vec2& p) const;


 bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input,
    const b2Transform& transform, int32 childIndex) const;


 void ComputeAABB(b2AABB* aabb, const b2Transform& transform, int32 childIndex) const;


 void ComputeMass(b2MassData* massData, float32 density) const;


 b2Vec2 m_vertex1, m_vertex2;


 b2Vec2 m_vertex0, m_vertex3;
 bool m_hasVertex0, m_hasVertex3;
};

inline b2EdgeShape::b2EdgeShape()
{
 m_type = e_edge;
 m_radius = (2.0f * 0.005f);
 m_vertex0.x = 0.0f;
 m_vertex0.y = 0.0f;
 m_vertex3.x = 0.0f;
 m_vertex3.y = 0.0f;
 m_hasVertex0 = false;
 m_hasVertex3 = false;
}
#line 39 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2ChainShape.h"
#line 24 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2ChainShape.h"
class b2EdgeShape;







class b2ChainShape : public b2Shape
{
public:
 b2ChainShape();


 ~b2ChainShape();




 void CreateLoop(const b2Vec2* vertices, int32 count);




 void CreateChain(const b2Vec2* vertices, int32 count);



 void SetPrevVertex(const b2Vec2& prevVertex);



 void SetNextVertex(const b2Vec2& nextVertex);


 b2Shape* Clone(b2BlockAllocator* allocator) const;


 int32 GetChildCount() const;


 void GetChildEdge(b2EdgeShape* edge, int32 index) const;



 bool TestPoint(const b2Transform& transform, const b2Vec2& p) const;


 bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input,
     const b2Transform& transform, int32 childIndex) const;


 void ComputeAABB(b2AABB* aabb, const b2Transform& transform, int32 childIndex) const;



 void ComputeMass(b2MassData* massData, float32 density) const;


 b2Vec2* m_vertices;


 int32 m_count;

 b2Vec2 m_prevVertex, m_nextVertex;
 bool m_hasPrevVertex, m_hasNextVertex;
};

inline b2ChainShape::b2ChainShape()
{
 m_type = e_chain;
 m_radius = (2.0f * 0.005f);
 m_vertices = ((void *)0);
 m_count = 0;
 m_hasPrevVertex = ((void *)0);
 m_hasNextVertex = ((void *)0);
}
#line 40 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2PolygonShape.h"
#line 28 "Box2D_v2.2.1\\Box2D/Collision/Shapes/b2PolygonShape.h"
class b2PolygonShape : public b2Shape
{
public:
 b2PolygonShape();


 b2Shape* Clone(b2BlockAllocator* allocator) const;


 int32 GetChildCount() const;




 void Set(const b2Vec2* vertices, int32 vertexCount);




 void SetAsBox(float32 hx, float32 hy);






 void SetAsBox(float32 hx, float32 hy, const b2Vec2& center, float32 angle);


 bool TestPoint(const b2Transform& transform, const b2Vec2& p) const;


 bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input,
     const b2Transform& transform, int32 childIndex) const;


 void ComputeAABB(b2AABB* aabb, const b2Transform& transform, int32 childIndex) const;


 void ComputeMass(b2MassData* massData, float32 density) const;


 int32 GetVertexCount() const { return m_vertexCount; }


 const b2Vec2& GetVertex(int32 index) const;

 b2Vec2 m_centroid;
 b2Vec2 m_vertices[8];
 b2Vec2 m_normals[8];
 int32 m_vertexCount;
};

inline b2PolygonShape::b2PolygonShape()
{
 m_type = e_polygon;
 m_radius = (2.0f * 0.005f);
 m_vertexCount = 0;
 m_centroid.SetZero();
}

inline const b2Vec2& b2PolygonShape::GetVertex(int32 index) const
{
 ((void)0);
 return m_vertices[index];
}
#line 41 "Box2D_v2.2.1\\Box2D/Box2D.h"


#line 1 "Box2D_v2.2.1\\Box2D/Collision/b2BroadPhase.h"
#line 24 "Box2D_v2.2.1\\Box2D/Collision/b2BroadPhase.h"
#line 1 "Box2D_v2.2.1\\Box2D/Collision/b2DynamicTree.h"
#line 23 "Box2D_v2.2.1\\Box2D/Collision/b2DynamicTree.h"
#line 1 "Box2D_v2.2.1\\Box2D/Common/b2GrowableStack.h"
#line 29 "Box2D_v2.2.1\\Box2D/Common/b2GrowableStack.h"
template <typename T, int32 N>
class b2GrowableStack
{
public:
 b2GrowableStack()
 {
  m_stack = m_array;
  m_count = 0;
  m_capacity = N;
 }

 ~b2GrowableStack()
 {
  if (m_stack != m_array)
  {
   b2Free(m_stack);
   m_stack = ((void *)0);
  }
 }

 void Push(const T& element)
 {
  if (m_count == m_capacity)
  {
   T* old = m_stack;
   m_capacity *= 2;
   m_stack = (T*)b2Alloc(m_capacity * sizeof(T));
   std::memcpy(m_stack, old, m_count * sizeof(T));
   if (old != m_array)
   {
    b2Free(old);
   }
  }

  m_stack[m_count] = element;
  ++m_count;
 }

 T Pop()
 {
  ((void)0);
  --m_count;
  return m_stack[m_count];
 }

 int32 GetCount()
 {
  return m_count;
 }

private:
 T* m_stack;
 T m_array[N];
 int32 m_count;
 int32 m_capacity;
};
#line 23 "Box2D_v2.2.1\\Box2D/Collision/b2DynamicTree.h"





struct b2TreeNode
{
 bool IsLeaf() const
 {
  return child1 == (-1);
 }


 b2AABB aabb;

 void* userData;

 union
 {
  int32 parent;
  int32 next;
 };

 int32 child1;
 int32 child2;


 int32 height;
};
#line 61 "Box2D_v2.2.1\\Box2D/Collision/b2DynamicTree.h"
class b2DynamicTree
{
public:

 b2DynamicTree();


 ~b2DynamicTree();


 int32 CreateProxy(const b2AABB& aabb, void* userData);


 void DestroyProxy(int32 proxyId);





 bool MoveProxy(int32 proxyId, const b2AABB& aabb1, const b2Vec2& displacement);



 void* GetUserData(int32 proxyId) const;


 const b2AABB& GetFatAABB(int32 proxyId) const;



 template <typename T>
 void Query(T* callback, const b2AABB& aabb) const;
#line 101 "Box2D_v2.2.1\\Box2D/Collision/b2DynamicTree.h"
 template <typename T>
 void RayCast(T* callback, const b2RayCastInput& input) const;


 void Validate() const;



 int32 GetHeight() const;



 int32 GetMaxBalance() const;


 float32 GetAreaRatio() const;


 void RebuildBottomUp();

private:

 int32 AllocateNode();
 void FreeNode(int32 node);

 void InsertLeaf(int32 node);
 void RemoveLeaf(int32 node);

 int32 Balance(int32 index);

 int32 ComputeHeight() const;
 int32 ComputeHeight(int32 nodeId) const;

 void ValidateStructure(int32 index) const;
 void ValidateMetrics(int32 index) const;

 int32 m_root;

 b2TreeNode* m_nodes;
 int32 m_nodeCount;
 int32 m_nodeCapacity;

 int32 m_freeList;


 uint32 m_path;

 int32 m_insertionCount;
};

inline void* b2DynamicTree::GetUserData(int32 proxyId) const
{
 ((void)0);
 return m_nodes[proxyId].userData;
}

inline const b2AABB& b2DynamicTree::GetFatAABB(int32 proxyId) const
{
 ((void)0);
 return m_nodes[proxyId].aabb;
}

template <typename T>
inline void b2DynamicTree::Query(T* callback, const b2AABB& aabb) const
{
 b2GrowableStack<int32, 256> stack;
 stack.Push(m_root);

 while (stack.GetCount() > 0)
 {
  int32 nodeId = stack.Pop();
  if (nodeId == (-1))
  {
   continue;
  }

  const b2TreeNode* node = m_nodes + nodeId;

  if (b2TestOverlap(node->aabb, aabb))
  {
   if (node->IsLeaf())
   {
    bool proceed = callback->QueryCallback(nodeId);
    if (proceed == false)
    {
     return;
    }
   }
   else
   {
    stack.Push(node->child1);
    stack.Push(node->child2);
   }
  }
 }
}

template <typename T>
inline void b2DynamicTree::RayCast(T* callback, const b2RayCastInput& input) const
{
 b2Vec2 p1 = input.p1;
 b2Vec2 p2 = input.p2;
 b2Vec2 r = p2 - p1;
 ((void)0);
 r.Normalize();


 b2Vec2 v = b2Cross(1.0f, r);
 b2Vec2 abs_v = b2Abs(v);




 float32 maxFraction = input.maxFraction;


 b2AABB segmentAABB;
 {
  b2Vec2 t = p1 + maxFraction * (p2 - p1);
  segmentAABB.lowerBound = b2Min(p1, t);
  segmentAABB.upperBound = b2Max(p1, t);
 }

 b2GrowableStack<int32, 256> stack;
 stack.Push(m_root);

 while (stack.GetCount() > 0)
 {
  int32 nodeId = stack.Pop();
  if (nodeId == (-1))
  {
   continue;
  }

  const b2TreeNode* node = m_nodes + nodeId;

  if (b2TestOverlap(node->aabb, segmentAABB) == false)
  {
   continue;
  }



  b2Vec2 c = node->aabb.GetCenter();
  b2Vec2 h = node->aabb.GetExtents();
  float32 separation = b2Abs(b2Dot(v, p1 - c)) - b2Dot(abs_v, h);
  if (separation > 0.0f)
  {
   continue;
  }

  if (node->IsLeaf())
  {
   b2RayCastInput subInput;
   subInput.p1 = input.p1;
   subInput.p2 = input.p2;
   subInput.maxFraction = maxFraction;

   float32 value = callback->RayCastCallback(subInput, nodeId);

   if (value == 0.0f)
   {

    return;
   }

   if (value > 0.0f)
   {

    maxFraction = value;
    b2Vec2 t = p1 + maxFraction * (p2 - p1);
    segmentAABB.lowerBound = b2Min(p1, t);
    segmentAABB.upperBound = b2Max(p1, t);
   }
  }
  else
  {
   stack.Push(node->child1);
   stack.Push(node->child2);
  }
 }
}
#line 24 "Box2D_v2.2.1\\Box2D/Collision/b2BroadPhase.h"





struct b2Pair
{
 int32 proxyIdA;
 int32 proxyIdB;
 int32 next;
};




class b2BroadPhase
{
public:

 enum
 {
  e_nullProxy = -1
 };

 b2BroadPhase();
 ~b2BroadPhase();



 int32 CreateProxy(const b2AABB& aabb, void* userData);


 void DestroyProxy(int32 proxyId);



 void MoveProxy(int32 proxyId, const b2AABB& aabb, const b2Vec2& displacement);


 void TouchProxy(int32 proxyId);


 const b2AABB& GetFatAABB(int32 proxyId) const;


 void* GetUserData(int32 proxyId) const;


 bool TestOverlap(int32 proxyIdA, int32 proxyIdB) const;


 int32 GetProxyCount() const;


 template <typename T>
 void UpdatePairs(T* callback);



 template <typename T>
 void Query(T* callback, const b2AABB& aabb) const;
#line 93 "Box2D_v2.2.1\\Box2D/Collision/b2BroadPhase.h"
 template <typename T>
 void RayCast(T* callback, const b2RayCastInput& input) const;


 int32 GetTreeHeight() const;


 int32 GetTreeBalance() const;


 float32 GetTreeQuality() const;

private:

 friend class b2DynamicTree;

 void BufferMove(int32 proxyId);
 void UnBufferMove(int32 proxyId);

 bool QueryCallback(int32 proxyId);

 b2DynamicTree m_tree;

 int32 m_proxyCount;

 int32* m_moveBuffer;
 int32 m_moveCapacity;
 int32 m_moveCount;

 b2Pair* m_pairBuffer;
 int32 m_pairCapacity;
 int32 m_pairCount;

 int32 m_queryProxyId;
};


inline bool b2PairLessThan(const b2Pair& pair1, const b2Pair& pair2)
{
 if (pair1.proxyIdA < pair2.proxyIdA)
 {
  return true;
 }

 if (pair1.proxyIdA == pair2.proxyIdA)
 {
  return pair1.proxyIdB < pair2.proxyIdB;
 }

 return false;
}

inline void* b2BroadPhase::GetUserData(int32 proxyId) const
{
 return m_tree.GetUserData(proxyId);
}

inline bool b2BroadPhase::TestOverlap(int32 proxyIdA, int32 proxyIdB) const
{
 const b2AABB& aabbA = m_tree.GetFatAABB(proxyIdA);
 const b2AABB& aabbB = m_tree.GetFatAABB(proxyIdB);
 return b2TestOverlap(aabbA, aabbB);
}

inline const b2AABB& b2BroadPhase::GetFatAABB(int32 proxyId) const
{
 return m_tree.GetFatAABB(proxyId);
}

inline int32 b2BroadPhase::GetProxyCount() const
{
 return m_proxyCount;
}

inline int32 b2BroadPhase::GetTreeHeight() const
{
 return m_tree.GetHeight();
}

inline int32 b2BroadPhase::GetTreeBalance() const
{
 return m_tree.GetMaxBalance();
}

inline float32 b2BroadPhase::GetTreeQuality() const
{
 return m_tree.GetAreaRatio();
}

template <typename T>
void b2BroadPhase::UpdatePairs(T* callback)
{

 m_pairCount = 0;


 for (int32 i = 0; i < m_moveCount; ++i)
 {
  m_queryProxyId = m_moveBuffer[i];
  if (m_queryProxyId == e_nullProxy)
  {
   continue;
  }



  const b2AABB& fatAABB = m_tree.GetFatAABB(m_queryProxyId);


  m_tree.Query(this, fatAABB);
 }


 m_moveCount = 0;


 std::sort(m_pairBuffer, m_pairBuffer + m_pairCount, b2PairLessThan);


 int32 i = 0;
 while (i < m_pairCount)
 {
  b2Pair* primaryPair = m_pairBuffer + i;
  void* userDataA = m_tree.GetUserData(primaryPair->proxyIdA);
  void* userDataB = m_tree.GetUserData(primaryPair->proxyIdB);

  callback->AddPair(userDataA, userDataB);
  ++i;


  while (i < m_pairCount)
  {
   b2Pair* pair = m_pairBuffer + i;
   if (pair->proxyIdA != primaryPair->proxyIdA || pair->proxyIdB != primaryPair->proxyIdB)
   {
    break;
   }
   ++i;
  }
 }



}

template <typename T>
inline void b2BroadPhase::Query(T* callback, const b2AABB& aabb) const
{
 m_tree.Query(callback, aabb);
}

template <typename T>
inline void b2BroadPhase::RayCast(T* callback, const b2RayCastInput& input) const
{
 m_tree.RayCast(callback, input);
}
#line 43 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Collision/b2Distance.h"
#line 25 "Box2D_v2.2.1\\Box2D/Collision/b2Distance.h"
class b2Shape;



struct b2DistanceProxy
{
 b2DistanceProxy() : m_vertices(((void *)0)), m_count(0), m_radius(0.0f) {}



 void Set(const b2Shape* shape, int32 index);


 int32 GetSupport(const b2Vec2& d) const;


 const b2Vec2& GetSupportVertex(const b2Vec2& d) const;


 int32 GetVertexCount() const;


 const b2Vec2& GetVertex(int32 index) const;

 b2Vec2 m_buffer[2];
 const b2Vec2* m_vertices;
 int32 m_count;
 float32 m_radius;
};



struct b2SimplexCache
{
 float32 metric;
 uint16 count;
 uint8 indexA[3];
 uint8 indexB[3];
};




struct b2DistanceInput
{
 b2DistanceProxy proxyA;
 b2DistanceProxy proxyB;
 b2Transform transformA;
 b2Transform transformB;
 bool useRadii;
};


struct b2DistanceOutput
{
 b2Vec2 pointA;
 b2Vec2 pointB;
 float32 distance;
 int32 iterations;
};




void b2Distance(b2DistanceOutput* output,
    b2SimplexCache* cache,
    const b2DistanceInput* input);




inline int32 b2DistanceProxy::GetVertexCount() const
{
 return m_count;
}

inline const b2Vec2& b2DistanceProxy::GetVertex(int32 index) const
{
 ((void)0);
 return m_vertices[index];
}

inline int32 b2DistanceProxy::GetSupport(const b2Vec2& d) const
{
 int32 bestIndex = 0;
 float32 bestValue = b2Dot(m_vertices[0], d);
 for (int32 i = 1; i < m_count; ++i)
 {
  float32 value = b2Dot(m_vertices[i], d);
  if (value > bestValue)
  {
   bestIndex = i;
   bestValue = value;
  }
 }

 return bestIndex;
}

inline const b2Vec2& b2DistanceProxy::GetSupportVertex(const b2Vec2& d) const
{
 int32 bestIndex = 0;
 float32 bestValue = b2Dot(m_vertices[0], d);
 for (int32 i = 1; i < m_count; ++i)
 {
  float32 value = b2Dot(m_vertices[i], d);
  if (value > bestValue)
  {
   bestIndex = i;
   bestValue = value;
  }
 }

 return m_vertices[bestIndex];
}
#line 44 "Box2D_v2.2.1\\Box2D/Box2D.h"


#line 1 "Box2D_v2.2.1\\Box2D/Collision/b2TimeOfImpact.h"
#line 26 "Box2D_v2.2.1\\Box2D/Collision/b2TimeOfImpact.h"
struct b2TOIInput
{
 b2DistanceProxy proxyA;
 b2DistanceProxy proxyB;
 b2Sweep sweepA;
 b2Sweep sweepB;
 float32 tMax;
};


struct b2TOIOutput
{
 enum State
 {
  e_unknown,
  e_failed,
  e_overlapped,
  e_touching,
  e_separated
 };

 State state;
 float32 t;
};






void b2TimeOfImpact(b2TOIOutput* output, const b2TOIInput* input);
#line 46 "Box2D_v2.2.1\\Box2D/Box2D.h"


#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/b2Body.h"
#line 28 "Box2D_v2.2.1\\Box2D/Dynamics/b2Body.h"
class b2Fixture;
class b2Joint;
class b2Contact;
class b2Controller;
class b2World;
struct b2FixtureDef;
struct b2JointEdge;
struct b2ContactEdge;





enum b2BodyType
{
 b2_staticBody = 0,
 b2_kinematicBody,
 b2_dynamicBody



};



struct b2BodyDef
{

 b2BodyDef()
 {
  userData = ((void *)0);
  position.Set(0.0f, 0.0f);
  angle = 0.0f;
  linearVelocity.Set(0.0f, 0.0f);
  angularVelocity = 0.0f;
  linearDamping = 0.0f;
  angularDamping = 0.0f;
  allowSleep = true;
  awake = true;
  fixedRotation = false;
  bullet = false;
  type = b2_staticBody;
  active = true;
  gravityScale = 1.0f;
 }



 b2BodyType type;



 b2Vec2 position;


 float32 angle;


 b2Vec2 linearVelocity;


 float32 angularVelocity;




 float32 linearDamping;




 float32 angularDamping;



 bool allowSleep;


 bool awake;


 bool fixedRotation;





 bool bullet;


 bool active;


 void* userData;


 float32 gravityScale;
};


class b2Body
{
public:







 b2Fixture* CreateFixture(const b2FixtureDef* def);
#line 147 "Box2D_v2.2.1\\Box2D/Dynamics/b2Body.h"
 b2Fixture* CreateFixture(const b2Shape* shape, float32 density);
#line 156 "Box2D_v2.2.1\\Box2D/Dynamics/b2Body.h"
 void DestroyFixture(b2Fixture* fixture);






 void SetTransform(const b2Vec2& position, float32 angle);



 const b2Transform& GetTransform() const;



 const b2Vec2& GetPosition() const;



 float32 GetAngle() const;


 const b2Vec2& GetWorldCenter() const;


 const b2Vec2& GetLocalCenter() const;



 void SetLinearVelocity(const b2Vec2& v);



 b2Vec2 GetLinearVelocity() const;



 void SetAngularVelocity(float32 omega);



 float32 GetAngularVelocity() const;






 void ApplyForce(const b2Vec2& force, const b2Vec2& point);



 void ApplyForceToCenter(const b2Vec2& force);





 void ApplyTorque(float32 torque);






 void ApplyLinearImpulse(const b2Vec2& impulse, const b2Vec2& point);



 void ApplyAngularImpulse(float32 impulse);



 float32 GetMass() const;



 float32 GetInertia() const;



 void GetMassData(b2MassData* data) const;






 void SetMassData(const b2MassData* data);




 void ResetMassData();




 b2Vec2 GetWorldPoint(const b2Vec2& localPoint) const;




 b2Vec2 GetWorldVector(const b2Vec2& localVector) const;




 b2Vec2 GetLocalPoint(const b2Vec2& worldPoint) const;




 b2Vec2 GetLocalVector(const b2Vec2& worldVector) const;




 b2Vec2 GetLinearVelocityFromWorldPoint(const b2Vec2& worldPoint) const;




 b2Vec2 GetLinearVelocityFromLocalPoint(const b2Vec2& localPoint) const;


 float32 GetLinearDamping() const;


 void SetLinearDamping(float32 linearDamping);


 float32 GetAngularDamping() const;


 void SetAngularDamping(float32 angularDamping);


 float32 GetGravityScale() const;


 void SetGravityScale(float32 scale);


 void SetType(b2BodyType type);


 b2BodyType GetType() const;


 void SetBullet(bool flag);


 bool IsBullet() const;



 void SetSleepingAllowed(bool flag);


 bool IsSleepingAllowed() const;




 void SetAwake(bool flag);



 bool IsAwake() const;
#line 340 "Box2D_v2.2.1\\Box2D/Dynamics/b2Body.h"
 void SetActive(bool flag);


 bool IsActive() const;



 void SetFixedRotation(bool flag);


 bool IsFixedRotation() const;


 b2Fixture* GetFixtureList();
 const b2Fixture* GetFixtureList() const;


 b2JointEdge* GetJointList();
 const b2JointEdge* GetJointList() const;




 b2ContactEdge* GetContactList();
 const b2ContactEdge* GetContactList() const;


 b2Body* GetNext();
 const b2Body* GetNext() const;


 void* GetUserData() const;


 void SetUserData(void* data);


 b2World* GetWorld();
 const b2World* GetWorld() const;


 void Dump();

private:

 friend class b2World;
 friend class b2Island;
 friend class b2ContactManager;
 friend class b2ContactSolver;
 friend class b2Contact;

 friend class b2DistanceJoint;
 friend class b2GearJoint;
 friend class b2WheelJoint;
 friend class b2MouseJoint;
 friend class b2PrismaticJoint;
 friend class b2PulleyJoint;
 friend class b2RevoluteJoint;
 friend class b2WeldJoint;
 friend class b2FrictionJoint;
 friend class b2RopeJoint;


 enum
 {
  e_islandFlag = 0x0001,
  e_awakeFlag = 0x0002,
  e_autoSleepFlag = 0x0004,
  e_bulletFlag = 0x0008,
  e_fixedRotationFlag = 0x0010,
  e_activeFlag = 0x0020,
  e_toiFlag = 0x0040
 };

 b2Body(const b2BodyDef* bd, b2World* world);
 ~b2Body();

 void SynchronizeFixtures();
 void SynchronizeTransform();



 bool ShouldCollide(const b2Body* other) const;

 void Advance(float32 t);

 b2BodyType m_type;

 uint16 m_flags;

 int32 m_islandIndex;

 b2Transform m_xf;
 b2Sweep m_sweep;

 b2Vec2 m_linearVelocity;
 float32 m_angularVelocity;

 b2Vec2 m_force;
 float32 m_torque;

 b2World* m_world;
 b2Body* m_prev;
 b2Body* m_next;

 b2Fixture* m_fixtureList;
 int32 m_fixtureCount;

 b2JointEdge* m_jointList;
 b2ContactEdge* m_contactList;

 float32 m_mass, m_invMass;


 float32 m_I, m_invI;

 float32 m_linearDamping;
 float32 m_angularDamping;
 float32 m_gravityScale;

 float32 m_sleepTime;

 void* m_userData;
};

inline b2BodyType b2Body::GetType() const
{
 return m_type;
}

inline const b2Transform& b2Body::GetTransform() const
{
 return m_xf;
}

inline const b2Vec2& b2Body::GetPosition() const
{
 return m_xf.p;
}

inline float32 b2Body::GetAngle() const
{
 return m_sweep.a;
}

inline const b2Vec2& b2Body::GetWorldCenter() const
{
 return m_sweep.c;
}

inline const b2Vec2& b2Body::GetLocalCenter() const
{
 return m_sweep.localCenter;
}

inline void b2Body::SetLinearVelocity(const b2Vec2& v)
{
 if (m_type == b2_staticBody)
 {
  return;
 }

 if (b2Dot(v,v) > 0.0f)
 {
  SetAwake(true);
 }

 m_linearVelocity = v;
}

inline b2Vec2 b2Body::GetLinearVelocity() const
{
 return m_linearVelocity;
}

inline void b2Body::SetAngularVelocity(float32 w)
{
 if (m_type == b2_staticBody)
 {
  return;
 }

 if (w * w > 0.0f)
 {
  SetAwake(true);
 }

 m_angularVelocity = w;
}

inline float32 b2Body::GetAngularVelocity() const
{
 return m_angularVelocity;
}

inline float32 b2Body::GetMass() const
{
 return m_mass;
}

inline float32 b2Body::GetInertia() const
{
 return m_I + m_mass * b2Dot(m_sweep.localCenter, m_sweep.localCenter);
}

inline void b2Body::GetMassData(b2MassData* data) const
{
 data->mass = m_mass;
 data->I = m_I + m_mass * b2Dot(m_sweep.localCenter, m_sweep.localCenter);
 data->center = m_sweep.localCenter;
}

inline b2Vec2 b2Body::GetWorldPoint(const b2Vec2& localPoint) const
{
 return b2Mul(m_xf, localPoint);
}

inline b2Vec2 b2Body::GetWorldVector(const b2Vec2& localVector) const
{
 return b2Mul(m_xf.q, localVector);
}

inline b2Vec2 b2Body::GetLocalPoint(const b2Vec2& worldPoint) const
{
 return b2MulT(m_xf, worldPoint);
}

inline b2Vec2 b2Body::GetLocalVector(const b2Vec2& worldVector) const
{
 return b2MulT(m_xf.q, worldVector);
}

inline b2Vec2 b2Body::GetLinearVelocityFromWorldPoint(const b2Vec2& worldPoint) const
{
 return m_linearVelocity + b2Cross(m_angularVelocity, worldPoint - m_sweep.c);
}

inline b2Vec2 b2Body::GetLinearVelocityFromLocalPoint(const b2Vec2& localPoint) const
{
 return GetLinearVelocityFromWorldPoint(GetWorldPoint(localPoint));
}

inline float32 b2Body::GetLinearDamping() const
{
 return m_linearDamping;
}

inline void b2Body::SetLinearDamping(float32 linearDamping)
{
 m_linearDamping = linearDamping;
}

inline float32 b2Body::GetAngularDamping() const
{
 return m_angularDamping;
}

inline void b2Body::SetAngularDamping(float32 angularDamping)
{
 m_angularDamping = angularDamping;
}

inline float32 b2Body::GetGravityScale() const
{
 return m_gravityScale;
}

inline void b2Body::SetGravityScale(float32 scale)
{
 m_gravityScale = scale;
}

inline void b2Body::SetBullet(bool flag)
{
 if (flag)
 {
  m_flags |= e_bulletFlag;
 }
 else
 {
  m_flags &= ~e_bulletFlag;
 }
}

inline bool b2Body::IsBullet() const
{
 return (m_flags & e_bulletFlag) == e_bulletFlag;
}

inline void b2Body::SetAwake(bool flag)
{
 if (flag)
 {
  if ((m_flags & e_awakeFlag) == 0)
  {
   m_flags |= e_awakeFlag;
   m_sleepTime = 0.0f;
  }
 }
 else
 {
  m_flags &= ~e_awakeFlag;
  m_sleepTime = 0.0f;
  m_linearVelocity.SetZero();
  m_angularVelocity = 0.0f;
  m_force.SetZero();
  m_torque = 0.0f;
 }
}

inline bool b2Body::IsAwake() const
{
 return (m_flags & e_awakeFlag) == e_awakeFlag;
}

inline bool b2Body::IsActive() const
{
 return (m_flags & e_activeFlag) == e_activeFlag;
}

inline void b2Body::SetFixedRotation(bool flag)
{
 if (flag)
 {
  m_flags |= e_fixedRotationFlag;
 }
 else
 {
  m_flags &= ~e_fixedRotationFlag;
 }

 ResetMassData();
}

inline bool b2Body::IsFixedRotation() const
{
 return (m_flags & e_fixedRotationFlag) == e_fixedRotationFlag;
}

inline void b2Body::SetSleepingAllowed(bool flag)
{
 if (flag)
 {
  m_flags |= e_autoSleepFlag;
 }
 else
 {
  m_flags &= ~e_autoSleepFlag;
  SetAwake(true);
 }
}

inline bool b2Body::IsSleepingAllowed() const
{
 return (m_flags & e_autoSleepFlag) == e_autoSleepFlag;
}

inline b2Fixture* b2Body::GetFixtureList()
{
 return m_fixtureList;
}

inline const b2Fixture* b2Body::GetFixtureList() const
{
 return m_fixtureList;
}

inline b2JointEdge* b2Body::GetJointList()
{
 return m_jointList;
}

inline const b2JointEdge* b2Body::GetJointList() const
{
 return m_jointList;
}

inline b2ContactEdge* b2Body::GetContactList()
{
 return m_contactList;
}

inline const b2ContactEdge* b2Body::GetContactList() const
{
 return m_contactList;
}

inline b2Body* b2Body::GetNext()
{
 return m_next;
}

inline const b2Body* b2Body::GetNext() const
{
 return m_next;
}

inline void b2Body::SetUserData(void* data)
{
 m_userData = data;
}

inline void* b2Body::GetUserData() const
{
 return m_userData;
}

inline void b2Body::ApplyForce(const b2Vec2& force, const b2Vec2& point)
{
 if (m_type != b2_dynamicBody)
 {
  return;
 }

 if (IsAwake() == false)
 {
  SetAwake(true);
 }

 m_force += force;
 m_torque += b2Cross(point - m_sweep.c, force);
}

inline void b2Body::ApplyForceToCenter(const b2Vec2& force)
{
 if (m_type != b2_dynamicBody)
 {
  return;
 }

 if (IsAwake() == false)
 {
  SetAwake(true);
 }

 m_force += force;
}

inline void b2Body::ApplyTorque(float32 torque)
{
 if (m_type != b2_dynamicBody)
 {
  return;
 }

 if (IsAwake() == false)
 {
  SetAwake(true);
 }

 m_torque += torque;
}

inline void b2Body::ApplyLinearImpulse(const b2Vec2& impulse, const b2Vec2& point)
{
 if (m_type != b2_dynamicBody)
 {
  return;
 }

 if (IsAwake() == false)
 {
  SetAwake(true);
 }
 m_linearVelocity += m_invMass * impulse;
 m_angularVelocity += m_invI * b2Cross(point - m_sweep.c, impulse);
}

inline void b2Body::ApplyAngularImpulse(float32 impulse)
{
 if (m_type != b2_dynamicBody)
 {
  return;
 }

 if (IsAwake() == false)
 {
  SetAwake(true);
 }
 m_angularVelocity += m_invI * impulse;
}

inline void b2Body::SynchronizeTransform()
{
 m_xf.q.Set(m_sweep.a);
 m_xf.p = m_sweep.c - b2Mul(m_xf.q, m_sweep.localCenter);
}

inline void b2Body::Advance(float32 alpha)
{

 m_sweep.Advance(alpha);
 m_sweep.c = m_sweep.c0;
 m_sweep.a = m_sweep.a0;
 m_xf.q.Set(m_sweep.a);
 m_xf.p = m_sweep.c - b2Mul(m_xf.q, m_sweep.localCenter);
}

inline b2World* b2Body::GetWorld()
{
 return m_world;
}

inline const b2World* b2Body::GetWorld() const
{
 return m_world;
}
#line 48 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/b2Fixture.h"
#line 26 "Box2D_v2.2.1\\Box2D/Dynamics/b2Fixture.h"
class b2BlockAllocator;
class b2Body;
class b2BroadPhase;
class b2Fixture;


struct b2Filter
{
 b2Filter()
 {
  categoryBits = 0x0001;
  maskBits = 0xFFFF;
  groupIndex = 0;
 }


 uint16 categoryBits;



 uint16 maskBits;




 int16 groupIndex;
};



struct b2FixtureDef
{

 b2FixtureDef()
 {
  shape = ((void *)0);
  userData = ((void *)0);
  friction = 0.2f;
  restitution = 0.0f;
  density = 0.0f;
  isSensor = false;
 }



 const b2Shape* shape;


 void* userData;


 float32 friction;


 float32 restitution;


 float32 density;



 bool isSensor;


 b2Filter filter;
};


struct b2FixtureProxy
{
 b2AABB aabb;
 b2Fixture* fixture;
 int32 childIndex;
 int32 proxyId;
};







class b2Fixture
{
public:


 b2Shape::Type GetType() const;




 b2Shape* GetShape();
 const b2Shape* GetShape() const;


 void SetSensor(bool sensor);



 bool IsSensor() const;




 void SetFilterData(const b2Filter& filter);


 const b2Filter& GetFilterData() const;


 void Refilter();



 b2Body* GetBody();
 const b2Body* GetBody() const;



 b2Fixture* GetNext();
 const b2Fixture* GetNext() const;



 void* GetUserData() const;


 void SetUserData(void* data);



 bool TestPoint(const b2Vec2& p) const;




 bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input, int32 childIndex) const;




 void GetMassData(b2MassData* massData) const;



 void SetDensity(float32 density);


 float32 GetDensity() const;


 float32 GetFriction() const;



 void SetFriction(float32 friction);


 float32 GetRestitution() const;



 void SetRestitution(float32 restitution);




 const b2AABB& GetAABB(int32 childIndex) const;


 void Dump(int32 bodyIndex);

protected:

 friend class b2Body;
 friend class b2World;
 friend class b2Contact;
 friend class b2ContactManager;

public:
 b2Fixture();

protected:


 void Create(b2BlockAllocator* allocator, b2Body* body, const b2FixtureDef* def);
 void Destroy(b2BlockAllocator* allocator);


 void CreateProxies(b2BroadPhase* broadPhase, const b2Transform& xf);
 void DestroyProxies(b2BroadPhase* broadPhase);

 void Synchronize(b2BroadPhase* broadPhase, const b2Transform& xf1, const b2Transform& xf2);

 float32 m_density;

 b2Fixture* m_next;
 b2Body* m_body;

 b2Shape* m_shape;

 float32 m_friction;
 float32 m_restitution;

 b2FixtureProxy* m_proxies;
 int32 m_proxyCount;

 b2Filter m_filter;

 bool m_isSensor;

 void* m_userData;
};

inline b2Shape::Type b2Fixture::GetType() const
{
 return m_shape->GetType();
}

inline b2Shape* b2Fixture::GetShape()
{
 return m_shape;
}

inline const b2Shape* b2Fixture::GetShape() const
{
 return m_shape;
}

inline bool b2Fixture::IsSensor() const
{
 return m_isSensor;
}

inline const b2Filter& b2Fixture::GetFilterData() const
{
 return m_filter;
}

inline void* b2Fixture::GetUserData() const
{
 return m_userData;
}

inline void b2Fixture::SetUserData(void* data)
{
 m_userData = data;
}

inline b2Body* b2Fixture::GetBody()
{
 return m_body;
}

inline const b2Body* b2Fixture::GetBody() const
{
 return m_body;
}

inline b2Fixture* b2Fixture::GetNext()
{
 return m_next;
}

inline const b2Fixture* b2Fixture::GetNext() const
{
 return m_next;
}

inline void b2Fixture::SetDensity(float32 density)
{
 ((void)0);
 m_density = density;
}

inline float32 b2Fixture::GetDensity() const
{
 return m_density;
}

inline float32 b2Fixture::GetFriction() const
{
 return m_friction;
}

inline void b2Fixture::SetFriction(float32 friction)
{
 m_friction = friction;
}

inline float32 b2Fixture::GetRestitution() const
{
 return m_restitution;
}

inline void b2Fixture::SetRestitution(float32 restitution)
{
 m_restitution = restitution;
}

inline bool b2Fixture::TestPoint(const b2Vec2& p) const
{
 return m_shape->TestPoint(m_body->GetTransform(), p);
}

inline bool b2Fixture::RayCast(b2RayCastOutput* output, const b2RayCastInput& input, int32 childIndex) const
{
 return m_shape->RayCast(output, input, m_body->GetTransform(), childIndex);
}

inline void b2Fixture::GetMassData(b2MassData* massData) const
{
 m_shape->ComputeMass(massData, m_density);
}

inline const b2AABB& b2Fixture::GetAABB(int32 childIndex) const
{
 ((void)0);
 return m_proxies[childIndex].aabb;
}
#line 49 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/b2WorldCallbacks.h"
#line 24 "Box2D_v2.2.1\\Box2D/Dynamics/b2WorldCallbacks.h"
struct b2Vec2;
struct b2Transform;
class b2Fixture;
class b2Body;
class b2Joint;
class b2Contact;
struct b2ContactResult;
struct b2Manifold;





class b2DestructionListener
{
public:
 b2DestructionListener() {}
 virtual ~b2DestructionListener() {}



 virtual void SayGoodbye(b2Joint* joint) {}



 virtual void SayGoodbye(b2Fixture* fixture) {}
};



class b2ContactFilter
{
public:
 virtual ~b2ContactFilter() {}



 virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
};




struct b2ContactImpulse
{
 float32 normalImpulses[2];
 float32 tangentImpulses[2];
 int32 count;
};
#line 84 "Box2D_v2.2.1\\Box2D/Dynamics/b2WorldCallbacks.h"
class b2ContactListener
{
public:
  b2ContactListener() {}
 virtual ~b2ContactListener() {}


 virtual void BeginContact(b2Contact* contact) { ((void)(contact)); }


 virtual void EndContact(b2Contact* contact) { ((void)(contact)); }
#line 106 "Box2D_v2.2.1\\Box2D/Dynamics/b2WorldCallbacks.h"
 virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
 {
  ((void)(contact));
  ((void)(oldManifold));
 }







 virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
 {
  ((void)(contact));
  ((void)(impulse));
 }
};




class b2QueryCallback
{
public:
 b2QueryCallback() {}
 virtual ~b2QueryCallback() {}



 virtual bool ReportFixture(b2Fixture* fixture) { return false; }
};




class b2RayCastCallback
{
public:
 b2RayCastCallback() {}
 virtual ~b2RayCastCallback() {}
#line 159 "Box2D_v2.2.1\\Box2D/Dynamics/b2WorldCallbacks.h"
 virtual float32 ReportFixture( b2Fixture* fixture, const b2Vec2& point,
         const b2Vec2& normal, float32 fraction) { return 0; }
};
#line 50 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/b2TimeStep.h"
#line 25 "Box2D_v2.2.1\\Box2D/Dynamics/b2TimeStep.h"
struct b2Profile
{
 float32 step;
 float32 collide;
 float32 solve;
 float32 solveInit;
 float32 solveVelocity;
 float32 solvePosition;
 float32 broadphase;
 float32 solveTOI;
};


struct b2TimeStep
{
 float32 dt;
 float32 inv_dt;
 float32 dtRatio;
 int32 velocityIterations;
 int32 positionIterations;
 bool warmStarting;
};


struct b2Position
{
 b2Vec2 c;
 float32 a;
};


struct b2Velocity
{
 b2Vec2 v;
 float32 w;
};


struct b2SolverData
{
 b2TimeStep step;
 b2Position* positions;
 b2Velocity* velocities;
};
#line 51 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/b2World.h"
#line 24 "Box2D_v2.2.1\\Box2D/Dynamics/b2World.h"
#line 1 "Box2D_v2.2.1\\Box2D/Common/b2StackAllocator.h"
#line 24 "Box2D_v2.2.1\\Box2D/Common/b2StackAllocator.h"
const int32 b2_stackSize = 100 * 1024;
const int32 b2_maxStackEntries = 32;

struct b2StackEntry
{
 char* data;
 int32 size;
 bool usedMalloc;
};




class b2StackAllocator
{
public:
 b2StackAllocator();
 ~b2StackAllocator();

 void* Allocate(int32 size);
 void Free(void* p);

 int32 GetMaxAllocation() const;

private:

 char m_data[b2_stackSize];
 int32 m_index;

 int32 m_allocation;
 int32 m_maxAllocation;

 b2StackEntry m_entries[b2_maxStackEntries];
 int32 m_entryCount;
};
#line 25 "Box2D_v2.2.1\\Box2D/Dynamics/b2World.h"
#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/b2ContactManager.h"
#line 24 "Box2D_v2.2.1\\Box2D/Dynamics/b2ContactManager.h"
class b2Contact;
class b2ContactFilter;
class b2ContactListener;
class b2BlockAllocator;


class b2ContactManager
{
public:
 b2ContactManager();


 void AddPair(void* proxyUserDataA, void* proxyUserDataB);

 void FindNewContacts();

 void Destroy(b2Contact* c);

 void Collide();

 b2BroadPhase m_broadPhase;
 b2Contact* m_contactList;
 int32 m_contactCount;
 b2ContactFilter* m_contactFilter;
 b2ContactListener* m_contactListener;
 b2BlockAllocator* m_allocator;
};
#line 26 "Box2D_v2.2.1\\Box2D/Dynamics/b2World.h"



struct b2AABB;
struct b2BodyDef;
struct b2Color;
struct b2JointDef;
class b2Body;
class b2Draw;
class b2Fixture;
class b2Joint;




class b2World
{
public:


 b2World(const b2Vec2& gravity);


 ~b2World();



 void SetDestructionListener(b2DestructionListener* listener);




 void SetContactFilter(b2ContactFilter* filter);



 void SetContactListener(b2ContactListener* listener);




 void SetDebugDraw(b2Draw* debugDraw);




 b2Body* CreateBody(const b2BodyDef* def);





 void DestroyBody(b2Body* body);




 b2Joint* CreateJoint(const b2JointDef* def);



 void DestroyJoint(b2Joint* joint);






 void Step( float32 timeStep,
    int32 velocityIterations,
    int32 positionIterations);
#line 105 "Box2D_v2.2.1\\Box2D/Dynamics/b2World.h"
 void ClearForces();


 void DrawDebugData();





 void QueryAABB(b2QueryCallback* callback, const b2AABB& aabb) const;







 void RayCast(b2RayCastCallback* callback, const b2Vec2& point1, const b2Vec2& point2) const;




 b2Body* GetBodyList();
 const b2Body* GetBodyList() const;




 b2Joint* GetJointList();
 const b2Joint* GetJointList() const;






 b2Contact* GetContactList();
 const b2Contact* GetContactList() const;


 void SetAllowSleeping(bool flag);
 bool GetAllowSleeping() const { return m_allowSleep; }


 void SetWarmStarting(bool flag) { m_warmStarting = flag; }
 bool GetWarmStarting() const { return m_warmStarting; }


 void SetContinuousPhysics(bool flag) { m_continuousPhysics = flag; }
 bool GetContinuousPhysics() const { return m_continuousPhysics; }


 void SetSubStepping(bool flag) { m_subStepping = flag; }
 bool GetSubStepping() const { return m_subStepping; }


 int32 GetProxyCount() const;


 int32 GetBodyCount() const;


 int32 GetJointCount() const;


 int32 GetContactCount() const;


 int32 GetTreeHeight() const;


 int32 GetTreeBalance() const;



 float32 GetTreeQuality() const;


 void SetGravity(const b2Vec2& gravity);


 b2Vec2 GetGravity() const;


 bool IsLocked() const;


 void SetAutoClearForces(bool flag);


 bool GetAutoClearForces() const;


 const b2ContactManager& GetContactManager() const;


 const b2Profile& GetProfile() const;



 void Dump();

private:


 enum
 {
  e_newFixture = 0x0001,
  e_locked = 0x0002,
  e_clearForces = 0x0004
 };

 friend class b2Body;
 friend class b2Fixture;
 friend class b2ContactManager;
 friend class b2Controller;

 void Solve(const b2TimeStep& step);
 void SolveTOI(const b2TimeStep& step);

 void DrawJoint(b2Joint* joint);
 void DrawShape(b2Fixture* shape, const b2Transform& xf, const b2Color& color);

 b2BlockAllocator m_blockAllocator;
 b2StackAllocator m_stackAllocator;

 int32 m_flags;

 b2ContactManager m_contactManager;

 b2Body* m_bodyList;
 b2Joint* m_jointList;

 int32 m_bodyCount;
 int32 m_jointCount;

 b2Vec2 m_gravity;
 bool m_allowSleep;

 b2DestructionListener* m_destructionListener;
 b2Draw* m_debugDraw;



 float32 m_inv_dt0;


 bool m_warmStarting;
 bool m_continuousPhysics;
 bool m_subStepping;

 bool m_stepComplete;

 b2Profile m_profile;
};

inline b2Body* b2World::GetBodyList()
{
 return m_bodyList;
}

inline const b2Body* b2World::GetBodyList() const
{
 return m_bodyList;
}

inline b2Joint* b2World::GetJointList()
{
 return m_jointList;
}

inline const b2Joint* b2World::GetJointList() const
{
 return m_jointList;
}

inline b2Contact* b2World::GetContactList()
{
 return m_contactManager.m_contactList;
}

inline const b2Contact* b2World::GetContactList() const
{
 return m_contactManager.m_contactList;
}

inline int32 b2World::GetBodyCount() const
{
 return m_bodyCount;
}

inline int32 b2World::GetJointCount() const
{
 return m_jointCount;
}

inline int32 b2World::GetContactCount() const
{
 return m_contactManager.m_contactCount;
}

inline void b2World::SetGravity(const b2Vec2& gravity)
{
 m_gravity = gravity;
}

inline b2Vec2 b2World::GetGravity() const
{
 return m_gravity;
}

inline bool b2World::IsLocked() const
{
 return (m_flags & e_locked) == e_locked;
}

inline void b2World::SetAutoClearForces(bool flag)
{
 if (flag)
 {
  m_flags |= e_clearForces;
 }
 else
 {
  m_flags &= ~e_clearForces;
 }
}


inline bool b2World::GetAutoClearForces() const
{
 return (m_flags & e_clearForces) == e_clearForces;
}

inline const b2ContactManager& b2World::GetContactManager() const
{
 return m_contactManager;
}

inline const b2Profile& b2World::GetProfile() const
{
 return m_profile;
}
#line 52 "Box2D_v2.2.1\\Box2D/Box2D.h"


#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Contacts/b2Contact.h"
#line 27 "Box2D_v2.2.1\\Box2D/Dynamics/Contacts/b2Contact.h"
class b2Body;
class b2Contact;
class b2Fixture;
class b2World;
class b2BlockAllocator;
class b2StackAllocator;
class b2ContactListener;



inline float32 b2MixFriction(float32 friction1, float32 friction2)
{
 return std::sqrt(friction1 * friction2);
}



inline float32 b2MixRestitution(float32 restitution1, float32 restitution2)
{
 return restitution1 > restitution2 ? restitution1 : restitution2;
}

typedef b2Contact* b2ContactCreateFcn( b2Fixture* fixtureA, int32 indexA,
          b2Fixture* fixtureB, int32 indexB,
          b2BlockAllocator* allocator);
typedef void b2ContactDestroyFcn(b2Contact* contact, b2BlockAllocator* allocator);

struct b2ContactRegister
{
 b2ContactCreateFcn* createFcn;
 b2ContactDestroyFcn* destroyFcn;
 bool primary;
};







struct b2ContactEdge
{
 b2Body* other;
 b2Contact* contact;
 b2ContactEdge* prev;
 b2ContactEdge* next;

  b2ContactEdge() {}
};




class b2Contact
{
public:



 b2Manifold* GetManifold();
 const b2Manifold* GetManifold() const;


 void GetWorldManifold(b2WorldManifold* worldManifold) const;


 bool IsTouching() const;




 void SetEnabled(bool flag);


 bool IsEnabled() const;


 b2Contact* GetNext();
 const b2Contact* GetNext() const;


 b2Fixture* GetFixtureA();
 const b2Fixture* GetFixtureA() const;


 int32 GetChildIndexA() const;


 b2Fixture* GetFixtureB();
 const b2Fixture* GetFixtureB() const;


 int32 GetChildIndexB() const;



 void SetFriction(float32 friction);


 float32 GetFriction() const;


 void ResetFriction();



 void SetRestitution(float32 restitution);


 float32 GetRestitution() const;


 void ResetRestitution();


 virtual void Evaluate(b2Manifold* manifold, const b2Transform& xfA, const b2Transform& xfB) = 0;

protected:
 friend class b2ContactManager;
 friend class b2World;
 friend class b2ContactSolver;
 friend class b2Body;
 friend class b2Fixture;


 enum
 {

  e_islandFlag = 0x0001,


  e_touchingFlag = 0x0002,


  e_enabledFlag = 0x0004,


  e_filterFlag = 0x0008,


  e_bulletHitFlag = 0x0010,


  e_toiFlag = 0x0020
 };


 void FlagForFiltering();

 static void AddType(b2ContactCreateFcn* createFcn, b2ContactDestroyFcn* destroyFcn,
      b2Shape::Type typeA, b2Shape::Type typeB);
 static void InitializeRegisters();
 static b2Contact* Create(b2Fixture* fixtureA, int32 indexA, b2Fixture* fixtureB, int32 indexB, b2BlockAllocator* allocator);
 static void Destroy(b2Contact* contact, b2Shape::Type typeA, b2Shape::Type typeB, b2BlockAllocator* allocator);
 static void Destroy(b2Contact* contact, b2BlockAllocator* allocator);

 b2Contact() : m_fixtureA(((void *)0)), m_fixtureB(((void *)0)) {}
 b2Contact(b2Fixture* fixtureA, int32 indexA, b2Fixture* fixtureB, int32 indexB);
 virtual ~b2Contact() {}

 void Update(b2ContactListener* listener);

 static b2ContactRegister s_registers[b2Shape::e_typeCount][b2Shape::e_typeCount];
 static bool s_initialized;

 uint32 m_flags;


 b2Contact* m_prev;
 b2Contact* m_next;


 b2ContactEdge m_nodeA;
 b2ContactEdge m_nodeB;

 b2Fixture* m_fixtureA;
 b2Fixture* m_fixtureB;

 int32 m_indexA;
 int32 m_indexB;

 b2Manifold m_manifold;

 int32 m_toiCount;
 float32 m_toi;

 float32 m_friction;
 float32 m_restitution;
};

inline b2Manifold* b2Contact::GetManifold()
{
 return &m_manifold;
}

inline const b2Manifold* b2Contact::GetManifold() const
{
 return &m_manifold;
}

inline void b2Contact::GetWorldManifold(b2WorldManifold* worldManifold) const
{
 const b2Body* bodyA = m_fixtureA->GetBody();
 const b2Body* bodyB = m_fixtureB->GetBody();
 const b2Shape* shapeA = m_fixtureA->GetShape();
 const b2Shape* shapeB = m_fixtureB->GetShape();

 worldManifold->Initialize(&m_manifold, bodyA->GetTransform(), shapeA->m_radius, bodyB->GetTransform(), shapeB->m_radius);
}

inline void b2Contact::SetEnabled(bool flag)
{
 if (flag)
 {
  m_flags |= e_enabledFlag;
 }
 else
 {
  m_flags &= ~e_enabledFlag;
 }
}

inline bool b2Contact::IsEnabled() const
{
 return (m_flags & e_enabledFlag) == e_enabledFlag;
}

inline bool b2Contact::IsTouching() const
{
 return (m_flags & e_touchingFlag) == e_touchingFlag;
}

inline b2Contact* b2Contact::GetNext()
{
 return m_next;
}

inline const b2Contact* b2Contact::GetNext() const
{
 return m_next;
}

inline b2Fixture* b2Contact::GetFixtureA()
{
 return m_fixtureA;
}

inline const b2Fixture* b2Contact::GetFixtureA() const
{
 return m_fixtureA;
}

inline b2Fixture* b2Contact::GetFixtureB()
{
 return m_fixtureB;
}

inline int32 b2Contact::GetChildIndexA() const
{
 return m_indexA;
}

inline const b2Fixture* b2Contact::GetFixtureB() const
{
 return m_fixtureB;
}

inline int32 b2Contact::GetChildIndexB() const
{
 return m_indexB;
}

inline void b2Contact::FlagForFiltering()
{
 m_flags |= e_filterFlag;
}

inline void b2Contact::SetFriction(float32 friction)
{
 m_friction = friction;
}

inline float32 b2Contact::GetFriction() const
{
 return m_friction;
}

inline void b2Contact::ResetFriction()
{
 m_friction = b2MixFriction(m_fixtureA->m_friction, m_fixtureB->m_friction);
}

inline void b2Contact::SetRestitution(float32 restitution)
{
 m_restitution = restitution;
}

inline float32 b2Contact::GetRestitution() const
{
 return m_restitution;
}

inline void b2Contact::ResetRestitution()
{
 m_restitution = b2MixRestitution(m_fixtureA->m_restitution, m_fixtureB->m_restitution);
}
#line 54 "Box2D_v2.2.1\\Box2D/Box2D.h"


#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2DistanceJoint.h"
#line 22 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2DistanceJoint.h"
#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2Joint.h"
#line 24 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2Joint.h"
class b2Body;
class b2Joint;
struct b2SolverData;
class b2BlockAllocator;

enum b2JointType
{
 e_unknownJoint,
 e_revoluteJoint,
 e_prismaticJoint,
 e_distanceJoint,
 e_pulleyJoint,
 e_mouseJoint,
 e_gearJoint,
 e_wheelJoint,
    e_weldJoint,
 e_frictionJoint,
 e_ropeJoint
};

enum b2LimitState
{
 e_inactiveLimit,
 e_atLowerLimit,
 e_atUpperLimit,
 e_equalLimits
};

struct b2Jacobian
{
 b2Vec2 linear;
 float32 angularA;
 float32 angularB;
};






struct b2JointEdge
{
 b2Body* other;
 b2Joint* joint;
 b2JointEdge* prev;
 b2JointEdge* next;
};


struct b2JointDef
{
 b2JointDef()
 {
  type = e_unknownJoint;
  userData = ((void *)0);
  bodyA = ((void *)0);
  bodyB = ((void *)0);
  collideConnected = false;
 }


 b2JointType type;


 void* userData;


 b2Body* bodyA;


 b2Body* bodyB;


 bool collideConnected;
};



class b2Joint
{
public:


 b2JointType GetType() const;


 b2Body* GetBodyA();


 b2Body* GetBodyB();


 virtual b2Vec2 GetAnchorA() const = 0;


 virtual b2Vec2 GetAnchorB() const = 0;


 virtual b2Vec2 GetReactionForce(float32 inv_dt) const = 0;


 virtual float32 GetReactionTorque(float32 inv_dt) const = 0;


 b2Joint* GetNext();
 const b2Joint* GetNext() const;


 void* GetUserData() const;


 void SetUserData(void* data);


 bool IsActive() const;




 bool GetCollideConnected() const;


 virtual void Dump() { b2Log("// Dump is not supported for this joint type.\n"); }

protected:
 friend class b2World;
 friend class b2Body;
 friend class b2Island;
 friend class b2GearJoint;

 static b2Joint* Create(const b2JointDef* def, b2BlockAllocator* allocator);
 static void Destroy(b2Joint* joint, b2BlockAllocator* allocator);

 b2Joint(const b2JointDef* def);
 virtual ~b2Joint() {}

 virtual void InitVelocityConstraints(const b2SolverData& data) = 0;
 virtual void SolveVelocityConstraints(const b2SolverData& data) = 0;


 virtual bool SolvePositionConstraints(const b2SolverData& data) = 0;

 b2JointType m_type;
 b2Joint* m_prev;
 b2Joint* m_next;
 b2JointEdge m_edgeA;
 b2JointEdge m_edgeB;
 b2Body* m_bodyA;
 b2Body* m_bodyB;

 int32 m_index;

 bool m_islandFlag;
 bool m_collideConnected;

 void* m_userData;
};

inline b2JointType b2Joint::GetType() const
{
 return m_type;
}

inline b2Body* b2Joint::GetBodyA()
{
 return m_bodyA;
}

inline b2Body* b2Joint::GetBodyB()
{
 return m_bodyB;
}

inline b2Joint* b2Joint::GetNext()
{
 return m_next;
}

inline const b2Joint* b2Joint::GetNext() const
{
 return m_next;
}

inline void* b2Joint::GetUserData() const
{
 return m_userData;
}

inline void b2Joint::SetUserData(void* data)
{
 m_userData = data;
}

inline bool b2Joint::GetCollideConnected() const
{
 return m_collideConnected;
}
#line 22 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2DistanceJoint.h"
#line 31 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2DistanceJoint.h"
struct b2DistanceJointDef : public b2JointDef
{
 b2DistanceJointDef()
 {
  type = e_distanceJoint;
  localAnchorA.Set(0.0f, 0.0f);
  localAnchorB.Set(0.0f, 0.0f);
  length = 1.0f;
  frequencyHz = 0.0f;
  dampingRatio = 0.0f;
 }



 void Initialize(b2Body* bodyA, b2Body* bodyB,
     const b2Vec2& anchorA, const b2Vec2& anchorB);


 b2Vec2 localAnchorA;


 b2Vec2 localAnchorB;


 float32 length;



 float32 frequencyHz;


 float32 dampingRatio;


 void set_bodyA(b2Body* b) { bodyA = b; }
 void set_bodyB(b2Body* b) { bodyB = b; }
 void set_collideConnected(bool b) { collideConnected = b; }
 b2Body* get_bodyA(b2Body* b) { return bodyA; }
 b2Body* get_bodyB(b2Body* b) { return bodyB; }
 bool get_collideConnected(bool b) { return collideConnected; }
};





class b2DistanceJoint : public b2Joint
{
public:

 b2Vec2 GetAnchorA() const;
 b2Vec2 GetAnchorB() const;



 b2Vec2 GetReactionForce(float32 inv_dt) const;



 float32 GetReactionTorque(float32 inv_dt) const;


 const b2Vec2& GetLocalAnchorA() const { return m_localAnchorA; }


 const b2Vec2& GetLocalAnchorB() const { return m_localAnchorB; }



 void SetLength(float32 length);
 float32 GetLength() const;


 void SetFrequency(float32 hz);
 float32 GetFrequency() const;


 void SetDampingRatio(float32 ratio);
 float32 GetDampingRatio() const;


 void Dump();

 b2DistanceJoint(const b2DistanceJointDef* data);

protected:

 friend class b2Joint;

 void InitVelocityConstraints(const b2SolverData& data);
 void SolveVelocityConstraints(const b2SolverData& data);
 bool SolvePositionConstraints(const b2SolverData& data);

 float32 m_frequencyHz;
 float32 m_dampingRatio;
 float32 m_bias;


 b2Vec2 m_localAnchorA;
 b2Vec2 m_localAnchorB;
 float32 m_gamma;
 float32 m_impulse;
 float32 m_length;


 int32 m_indexA;
 int32 m_indexB;
 b2Vec2 m_u;
 b2Vec2 m_rA;
 b2Vec2 m_rB;
 b2Vec2 m_localCenterA;
 b2Vec2 m_localCenterB;
 float32 m_invMassA;
 float32 m_invMassB;
 float32 m_invIA;
 float32 m_invIB;
 float32 m_mass;
};

inline void b2DistanceJoint::SetLength(float32 length)
{
 m_length = length;
}

inline float32 b2DistanceJoint::GetLength() const
{
 return m_length;
}

inline void b2DistanceJoint::SetFrequency(float32 hz)
{
 m_frequencyHz = hz;
}

inline float32 b2DistanceJoint::GetFrequency() const
{
 return m_frequencyHz;
}

inline void b2DistanceJoint::SetDampingRatio(float32 ratio)
{
 m_dampingRatio = ratio;
}

inline float32 b2DistanceJoint::GetDampingRatio() const
{
 return m_dampingRatio;
}
#line 56 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2FrictionJoint.h"
#line 26 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2FrictionJoint.h"
struct b2FrictionJointDef : public b2JointDef
{
 b2FrictionJointDef()
 {
  type = e_frictionJoint;
  localAnchorA.SetZero();
  localAnchorB.SetZero();
  maxForce = 0.0f;
  maxTorque = 0.0f;
 }



 void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor);


 b2Vec2 localAnchorA;


 b2Vec2 localAnchorB;


 float32 maxForce;


 float32 maxTorque;


 void set_bodyA(b2Body* b) { bodyA = b; }
 void set_bodyB(b2Body* b) { bodyB = b; }
 void set_collideConnected(bool b) { collideConnected = b; }
 b2Body* get_bodyA(b2Body* b) { return bodyA; }
 b2Body* get_bodyB(b2Body* b) { return bodyB; }
 bool get_collideConnected(bool b) { return collideConnected; }
};




class b2FrictionJoint : public b2Joint
{
public:
 b2Vec2 GetAnchorA() const;
 b2Vec2 GetAnchorB() const;

 b2Vec2 GetReactionForce(float32 inv_dt) const;
 float32 GetReactionTorque(float32 inv_dt) const;


 const b2Vec2& GetLocalAnchorA() const { return m_localAnchorA; }


 const b2Vec2& GetLocalAnchorB() const { return m_localAnchorB; }


 void SetMaxForce(float32 force);


 float32 GetMaxForce() const;


 void SetMaxTorque(float32 torque);


 float32 GetMaxTorque() const;


 void Dump();

 b2FrictionJoint(const b2FrictionJointDef* def);

protected:

 friend class b2Joint;

 void InitVelocityConstraints(const b2SolverData& data);
 void SolveVelocityConstraints(const b2SolverData& data);
 bool SolvePositionConstraints(const b2SolverData& data);

 b2Vec2 m_localAnchorA;
 b2Vec2 m_localAnchorB;


 b2Vec2 m_linearImpulse;
 float32 m_angularImpulse;
 float32 m_maxForce;
 float32 m_maxTorque;


 int32 m_indexA;
 int32 m_indexB;
 b2Vec2 m_rA;
 b2Vec2 m_rB;
 b2Vec2 m_localCenterA;
 b2Vec2 m_localCenterB;
 float32 m_invMassA;
 float32 m_invMassB;
 float32 m_invIA;
 float32 m_invIB;
 b2Mat22 m_linearMass;
 float32 m_angularMass;
};
#line 57 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2GearJoint.h"
#line 27 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2GearJoint.h"
struct b2GearJointDef : public b2JointDef
{
 b2GearJointDef()
 {
  type = e_gearJoint;
  joint1 = ((void *)0);
  joint2 = ((void *)0);
  ratio = 1.0f;
 }


 b2Joint* joint1;


 b2Joint* joint2;



 float32 ratio;


 void set_bodyA(b2Body* b) { bodyA = b; }
 void set_bodyB(b2Body* b) { bodyB = b; }
 void set_collideConnected(bool b) { collideConnected = b; }
 b2Body* get_bodyA(b2Body* b) { return bodyA; }
 b2Body* get_bodyB(b2Body* b) { return bodyB; }
 bool get_collideConnected(bool b) { return collideConnected; }
};
#line 66 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2GearJoint.h"
class b2GearJoint : public b2Joint
{
public:
 b2Vec2 GetAnchorA() const;
 b2Vec2 GetAnchorB() const;

 b2Vec2 GetReactionForce(float32 inv_dt) const;
 float32 GetReactionTorque(float32 inv_dt) const;


 b2Joint* GetJoint1() { return m_joint1; }


 b2Joint* GetJoint2() { return m_joint2; }


 void SetRatio(float32 ratio);
 float32 GetRatio() const;


 void Dump();

 b2GearJoint(const b2GearJointDef* data);

protected:

 friend class b2Joint;

 void InitVelocityConstraints(const b2SolverData& data);
 void SolveVelocityConstraints(const b2SolverData& data);
 bool SolvePositionConstraints(const b2SolverData& data);

 b2Joint* m_joint1;
 b2Joint* m_joint2;

 b2JointType m_typeA;
 b2JointType m_typeB;



 b2Body* m_bodyC;
 b2Body* m_bodyD;


 b2Vec2 m_localAnchorA;
 b2Vec2 m_localAnchorB;
 b2Vec2 m_localAnchorC;
 b2Vec2 m_localAnchorD;

 b2Vec2 m_localAxisC;
 b2Vec2 m_localAxisD;

 float32 m_referenceAngleA;
 float32 m_referenceAngleB;

 float32 m_constant;
 float32 m_ratio;

 float32 m_impulse;


 int32 m_indexA, m_indexB, m_indexC, m_indexD;
 b2Vec2 m_lcA, m_lcB, m_lcC, m_lcD;
 float32 m_mA, m_mB, m_mC, m_mD;
 float32 m_iA, m_iB, m_iC, m_iD;
 b2Vec2 m_JvAC, m_JvBD;
 float32 m_JwA, m_JwB, m_JwC, m_JwD;
 float32 m_mass;
};
#line 58 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2WheelJoint.h"
#line 31 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2WheelJoint.h"
struct b2WheelJointDef : public b2JointDef
{
 b2WheelJointDef()
 {
  type = e_wheelJoint;
  localAnchorA.SetZero();
  localAnchorB.SetZero();
  localAxisA.Set(1.0f, 0.0f);
  enableMotor = false;
  maxMotorTorque = 0.0f;
  motorSpeed = 0.0f;
  frequencyHz = 2.0f;
  dampingRatio = 0.7f;
 }



 void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor, const b2Vec2& axis);


 b2Vec2 localAnchorA;


 b2Vec2 localAnchorB;


 b2Vec2 localAxisA;


 bool enableMotor;


 float32 maxMotorTorque;


 float32 motorSpeed;


 float32 frequencyHz;


 float32 dampingRatio;


 void set_bodyA(b2Body* b) { bodyA = b; }
 void set_bodyB(b2Body* b) { bodyB = b; }
 void set_collideConnected(bool b) { collideConnected = b; }
 b2Body* get_bodyA(b2Body* b) { return bodyA; }
 b2Body* get_bodyB(b2Body* b) { return bodyB; }
 bool get_collideConnected(bool b) { return collideConnected; }
};







class b2WheelJoint : public b2Joint
{
public:
 void GetDefinition(b2WheelJointDef* def) const;

 b2Vec2 GetAnchorA() const;
 b2Vec2 GetAnchorB() const;

 b2Vec2 GetReactionForce(float32 inv_dt) const;
 float32 GetReactionTorque(float32 inv_dt) const;


 const b2Vec2& GetLocalAnchorA() const { return m_localAnchorA; }


 const b2Vec2& GetLocalAnchorB() const { return m_localAnchorB; }


 const b2Vec2& GetLocalAxisA() const { return m_localXAxisA; }


 float32 GetJointTranslation() const;


 float32 GetJointSpeed() const;


 bool IsMotorEnabled() const;


 void EnableMotor(bool flag);


 void SetMotorSpeed(float32 speed);


 float32 GetMotorSpeed() const;


 void SetMaxMotorTorque(float32 torque);
 float32 GetMaxMotorTorque() const;


 float32 GetMotorTorque(float32 inv_dt) const;


 void SetSpringFrequencyHz(float32 hz);
 float32 GetSpringFrequencyHz() const;


 void SetSpringDampingRatio(float32 ratio);
 float32 GetSpringDampingRatio() const;


 void Dump();

 b2WheelJoint(const b2WheelJointDef* def);

protected:

 friend class b2Joint;

 void InitVelocityConstraints(const b2SolverData& data);
 void SolveVelocityConstraints(const b2SolverData& data);
 bool SolvePositionConstraints(const b2SolverData& data);

 float32 m_frequencyHz;
 float32 m_dampingRatio;


 b2Vec2 m_localAnchorA;
 b2Vec2 m_localAnchorB;
 b2Vec2 m_localXAxisA;
 b2Vec2 m_localYAxisA;

 float32 m_impulse;
 float32 m_motorImpulse;
 float32 m_springImpulse;

 float32 m_maxMotorTorque;
 float32 m_motorSpeed;
 bool m_enableMotor;


 int32 m_indexA;
 int32 m_indexB;
 b2Vec2 m_localCenterA;
 b2Vec2 m_localCenterB;
 float32 m_invMassA;
 float32 m_invMassB;
 float32 m_invIA;
 float32 m_invIB;

 b2Vec2 m_ax, m_ay;
 float32 m_sAx, m_sBx;
 float32 m_sAy, m_sBy;

 float32 m_mass;
 float32 m_motorMass;
 float32 m_springMass;

 float32 m_bias;
 float32 m_gamma;
};

inline float32 b2WheelJoint::GetMotorSpeed() const
{
 return m_motorSpeed;
}

inline float32 b2WheelJoint::GetMaxMotorTorque() const
{
 return m_maxMotorTorque;
}

inline void b2WheelJoint::SetSpringFrequencyHz(float32 hz)
{
 m_frequencyHz = hz;
}

inline float32 b2WheelJoint::GetSpringFrequencyHz() const
{
 return m_frequencyHz;
}

inline void b2WheelJoint::SetSpringDampingRatio(float32 ratio)
{
 m_dampingRatio = ratio;
}

inline float32 b2WheelJoint::GetSpringDampingRatio() const
{
 return m_dampingRatio;
}
#line 59 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2MouseJoint.h"
#line 27 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2MouseJoint.h"
struct b2MouseJointDef : public b2JointDef
{
 b2MouseJointDef()
 {
  type = e_mouseJoint;
  target.Set(0.0f, 0.0f);
  maxForce = 0.0f;
  frequencyHz = 5.0f;
  dampingRatio = 0.7f;
 }



 b2Vec2 target;




 float32 maxForce;


 float32 frequencyHz;


 float32 dampingRatio;


 void set_bodyA(b2Body* b) { bodyA = b; }
 void set_bodyB(b2Body* b) { bodyB = b; }
 void set_collideConnected(bool b) { collideConnected = b; }
 b2Body* get_bodyA(b2Body* b) { return bodyA; }
 b2Body* get_bodyB(b2Body* b) { return bodyB; }
 bool get_collideConnected(bool b) { return collideConnected; }
};
#line 70 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2MouseJoint.h"
class b2MouseJoint : public b2Joint
{
public:


 b2Vec2 GetAnchorA() const;


 b2Vec2 GetAnchorB() const;


 b2Vec2 GetReactionForce(float32 inv_dt) const;


 float32 GetReactionTorque(float32 inv_dt) const;


 void SetTarget(const b2Vec2& target);
 const b2Vec2& GetTarget() const;


 void SetMaxForce(float32 force);
 float32 GetMaxForce() const;


 void SetFrequency(float32 hz);
 float32 GetFrequency() const;


 void SetDampingRatio(float32 ratio);
 float32 GetDampingRatio() const;


 void Dump() { b2Log("Mouse joint dumping is not supported.\n"); }

 b2MouseJoint(const b2MouseJointDef* def);

protected:
 friend class b2Joint;

 void InitVelocityConstraints(const b2SolverData& data);
 void SolveVelocityConstraints(const b2SolverData& data);
 bool SolvePositionConstraints(const b2SolverData& data);

 b2Vec2 m_localAnchorB;
 b2Vec2 m_targetA;
 float32 m_frequencyHz;
 float32 m_dampingRatio;
 float32 m_beta;


 b2Vec2 m_impulse;
 float32 m_maxForce;
 float32 m_gamma;


 int32 m_indexA;
 int32 m_indexB;
 b2Vec2 m_rB;
 b2Vec2 m_localCenterB;
 float32 m_invMassB;
 float32 m_invIB;
 b2Mat22 m_mass;
 b2Vec2 m_C;
};
#line 60 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2PrismaticJoint.h"
#line 31 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2PrismaticJoint.h"
struct b2PrismaticJointDef : public b2JointDef
{
 b2PrismaticJointDef()
 {
  type = e_prismaticJoint;
  localAnchorA.SetZero();
  localAnchorB.SetZero();
  localAxisA.Set(1.0f, 0.0f);
  referenceAngle = 0.0f;
  enableLimit = false;
  lowerTranslation = 0.0f;
  upperTranslation = 0.0f;
  enableMotor = false;
  maxMotorForce = 0.0f;
  motorSpeed = 0.0f;
 }



 void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor, const b2Vec2& axis);


 b2Vec2 localAnchorA;


 b2Vec2 localAnchorB;


 b2Vec2 localAxisA;


 float32 referenceAngle;


 bool enableLimit;


 float32 lowerTranslation;


 float32 upperTranslation;


 bool enableMotor;


 float32 maxMotorForce;


 float32 motorSpeed;


 void set_bodyA(b2Body* b) { bodyA = b; }
 void set_bodyB(b2Body* b) { bodyB = b; }
 void set_collideConnected(bool b) { collideConnected = b; }
 b2Body* get_bodyA(b2Body* b) { return bodyA; }
 b2Body* get_bodyB(b2Body* b) { return bodyB; }
 bool get_collideConnected(bool b) { return collideConnected; }
};






class b2PrismaticJoint : public b2Joint
{
public:
 b2Vec2 GetAnchorA() const;
 b2Vec2 GetAnchorB() const;

 b2Vec2 GetReactionForce(float32 inv_dt) const;
 float32 GetReactionTorque(float32 inv_dt) const;


 const b2Vec2& GetLocalAnchorA() const { return m_localAnchorA; }


 const b2Vec2& GetLocalAnchorB() const { return m_localAnchorB; }


 const b2Vec2& GetLocalAxisA() const { return m_localXAxisA; }


 float32 GetReferenceAngle() const { return m_referenceAngle; }


 float32 GetJointTranslation() const;


 float32 GetJointSpeed() const;


 bool IsLimitEnabled() const;


 void EnableLimit(bool flag);


 float32 GetLowerLimit() const;


 float32 GetUpperLimit() const;


 void SetLimits(float32 lower, float32 upper);


 bool IsMotorEnabled() const;


 void EnableMotor(bool flag);


 void SetMotorSpeed(float32 speed);


 float32 GetMotorSpeed() const;


 void SetMaxMotorForce(float32 force);
 float32 GetMaxMotorForce() const { return m_maxMotorForce; }


 float32 GetMotorForce(float32 inv_dt) const;


 void Dump();

 b2PrismaticJoint(const b2PrismaticJointDef* def);

protected:
 friend class b2Joint;
 friend class b2GearJoint;

 void InitVelocityConstraints(const b2SolverData& data);
 void SolveVelocityConstraints(const b2SolverData& data);
 bool SolvePositionConstraints(const b2SolverData& data);


 b2Vec2 m_localAnchorA;
 b2Vec2 m_localAnchorB;
 b2Vec2 m_localXAxisA;
 b2Vec2 m_localYAxisA;
 float32 m_referenceAngle;
 b2Vec3 m_impulse;
 float32 m_motorImpulse;
 float32 m_lowerTranslation;
 float32 m_upperTranslation;
 float32 m_maxMotorForce;
 float32 m_motorSpeed;
 bool m_enableLimit;
 bool m_enableMotor;
 b2LimitState m_limitState;


 int32 m_indexA;
 int32 m_indexB;
 b2Vec2 m_localCenterA;
 b2Vec2 m_localCenterB;
 float32 m_invMassA;
 float32 m_invMassB;
 float32 m_invIA;
 float32 m_invIB;
 b2Vec2 m_axis, m_perp;
 float32 m_s1, m_s2;
 float32 m_a1, m_a2;
 b2Mat33 m_K;
 float32 m_motorMass;
};

inline float32 b2PrismaticJoint::GetMotorSpeed() const
{
 return m_motorSpeed;
}
#line 61 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2PulleyJoint.h"
#line 24 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2PulleyJoint.h"
const float32 b2_minPulleyLength = 2.0f;




struct b2PulleyJointDef : public b2JointDef
{
 b2PulleyJointDef()
 {
  type = e_pulleyJoint;
  groundAnchorA.Set(-1.0f, 1.0f);
  groundAnchorB.Set(1.0f, 1.0f);
  localAnchorA.Set(-1.0f, 0.0f);
  localAnchorB.Set(1.0f, 0.0f);
  lengthA = 0.0f;
  lengthB = 0.0f;
  ratio = 1.0f;
  collideConnected = true;
 }


 void Initialize(b2Body* bodyA, b2Body* bodyB,
     const b2Vec2& groundAnchorA, const b2Vec2& groundAnchorB,
     const b2Vec2& anchorA, const b2Vec2& anchorB,
     float32 ratio);


 b2Vec2 groundAnchorA;


 b2Vec2 groundAnchorB;


 b2Vec2 localAnchorA;


 b2Vec2 localAnchorB;


 float32 lengthA;


 float32 lengthB;


 float32 ratio;


 void set_bodyA(b2Body* b) { bodyA = b; }
 void set_bodyB(b2Body* b) { bodyB = b; }
 void set_collideConnected(bool b) { collideConnected = b; }
 b2Body* get_bodyA(b2Body* b) { return bodyA; }
 b2Body* get_bodyB(b2Body* b) { return bodyB; }
 bool get_collideConnected(bool b) { return collideConnected; }
};
#line 89 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2PulleyJoint.h"
class b2PulleyJoint : public b2Joint
{
public:
 b2Vec2 GetAnchorA() const;
 b2Vec2 GetAnchorB() const;

 b2Vec2 GetReactionForce(float32 inv_dt) const;
 float32 GetReactionTorque(float32 inv_dt) const;


 b2Vec2 GetGroundAnchorA() const;


 b2Vec2 GetGroundAnchorB() const;


 float32 GetLengthA() const;


 float32 GetLengthB() const;


 float32 GetRatio() const;


 void Dump();

 b2PulleyJoint(const b2PulleyJointDef* data);

protected:

 friend class b2Joint;

 void InitVelocityConstraints(const b2SolverData& data);
 void SolveVelocityConstraints(const b2SolverData& data);
 bool SolvePositionConstraints(const b2SolverData& data);

 b2Vec2 m_groundAnchorA;
 b2Vec2 m_groundAnchorB;
 float32 m_lengthA;
 float32 m_lengthB;


 b2Vec2 m_localAnchorA;
 b2Vec2 m_localAnchorB;
 float32 m_constant;
 float32 m_ratio;
 float32 m_impulse;


 int32 m_indexA;
 int32 m_indexB;
 b2Vec2 m_uA;
 b2Vec2 m_uB;
 b2Vec2 m_rA;
 b2Vec2 m_rB;
 b2Vec2 m_localCenterA;
 b2Vec2 m_localCenterB;
 float32 m_invMassA;
 float32 m_invMassB;
 float32 m_invIA;
 float32 m_invIB;
 float32 m_mass;
};
#line 62 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2RevoluteJoint.h"
#line 36 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2RevoluteJoint.h"
struct b2RevoluteJointDef : public b2JointDef
{
 b2RevoluteJointDef()
 {
  type = e_revoluteJoint;
  localAnchorA.Set(0.0f, 0.0f);
  localAnchorB.Set(0.0f, 0.0f);
  referenceAngle = 0.0f;
  lowerAngle = 0.0f;
  upperAngle = 0.0f;
  maxMotorTorque = 0.0f;
  motorSpeed = 0.0f;
  enableLimit = false;
  enableMotor = false;
 }



 void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor);


 b2Vec2 localAnchorA;


 b2Vec2 localAnchorB;


 float32 referenceAngle;


 bool enableLimit;


 float32 lowerAngle;


 float32 upperAngle;


 bool enableMotor;


 float32 motorSpeed;



 float32 maxMotorTorque;


 void set_bodyA(b2Body* b) { bodyA = b; }
 void set_bodyB(b2Body* b) { bodyB = b; }
 void set_collideConnected(bool b) { collideConnected = b; }
 b2Body* get_bodyA(b2Body* b) { return bodyA; }
 b2Body* get_bodyB(b2Body* b) { return bodyB; }
 bool get_collideConnected(bool b) { return collideConnected; }
};
#line 100 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2RevoluteJoint.h"
class b2RevoluteJoint : public b2Joint
{
public:
 b2Vec2 GetAnchorA() const;
 b2Vec2 GetAnchorB() const;


 const b2Vec2& GetLocalAnchorA() const { return m_localAnchorA; }


 const b2Vec2& GetLocalAnchorB() const { return m_localAnchorB; }


 float32 GetReferenceAngle() const { return m_referenceAngle; }


 float32 GetJointAngle() const;


 float32 GetJointSpeed() const;


 bool IsLimitEnabled() const;


 void EnableLimit(bool flag);


 float32 GetLowerLimit() const;


 float32 GetUpperLimit() const;


 void SetLimits(float32 lower, float32 upper);


 bool IsMotorEnabled() const;


 void EnableMotor(bool flag);


 void SetMotorSpeed(float32 speed);


 float32 GetMotorSpeed() const;


 void SetMaxMotorTorque(float32 torque);
 float32 GetMaxMotorTorque() const { return m_maxMotorTorque; }



 b2Vec2 GetReactionForce(float32 inv_dt) const;



 float32 GetReactionTorque(float32 inv_dt) const;



 float32 GetMotorTorque(float32 inv_dt) const;


 void Dump();

 b2RevoluteJoint(const b2RevoluteJointDef* def);

protected:

 friend class b2Joint;
 friend class b2GearJoint;

 void InitVelocityConstraints(const b2SolverData& data);
 void SolveVelocityConstraints(const b2SolverData& data);
 bool SolvePositionConstraints(const b2SolverData& data);


 b2Vec2 m_localAnchorA;
 b2Vec2 m_localAnchorB;
 b2Vec3 m_impulse;
 float32 m_motorImpulse;

 bool m_enableMotor;
 float32 m_maxMotorTorque;
 float32 m_motorSpeed;

 bool m_enableLimit;
 float32 m_referenceAngle;
 float32 m_lowerAngle;
 float32 m_upperAngle;


 int32 m_indexA;
 int32 m_indexB;
 b2Vec2 m_rA;
 b2Vec2 m_rB;
 b2Vec2 m_localCenterA;
 b2Vec2 m_localCenterB;
 float32 m_invMassA;
 float32 m_invMassB;
 float32 m_invIA;
 float32 m_invIB;
 b2Mat33 m_mass;
 float32 m_motorMass;
 b2LimitState m_limitState;
};

inline float32 b2RevoluteJoint::GetMotorSpeed() const
{
 return m_motorSpeed;
}
#line 63 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2RopeJoint.h"
#line 29 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2RopeJoint.h"
struct b2RopeJointDef : public b2JointDef
{
 b2RopeJointDef()
 {
  type = e_ropeJoint;
  localAnchorA.Set(-1.0f, 0.0f);
  localAnchorB.Set(1.0f, 0.0f);
  maxLength = 0.0f;
 }


 b2Vec2 localAnchorA;


 b2Vec2 localAnchorB;




 float32 maxLength;


 void set_bodyA(b2Body* b) { bodyA = b; }
 void set_bodyB(b2Body* b) { bodyB = b; }
 void set_collideConnected(bool b) { collideConnected = b; }
 b2Body* get_bodyA(b2Body* b) { return bodyA; }
 b2Body* get_bodyB(b2Body* b) { return bodyB; }
 bool get_collideConnected(bool b) { return collideConnected; }
};
#line 68 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2RopeJoint.h"
class b2RopeJoint : public b2Joint
{
public:
 b2Vec2 GetAnchorA() const;
 b2Vec2 GetAnchorB() const;

 b2Vec2 GetReactionForce(float32 inv_dt) const;
 float32 GetReactionTorque(float32 inv_dt) const;


 const b2Vec2& GetLocalAnchorA() const { return m_localAnchorA; }


 const b2Vec2& GetLocalAnchorB() const { return m_localAnchorB; }


 void SetMaxLength(float32 length) { m_maxLength = length; }
 float32 GetMaxLength() const;

 b2LimitState GetLimitState() const;


 void Dump();

 b2RopeJoint(const b2RopeJointDef* data);

protected:

 friend class b2Joint;

 void InitVelocityConstraints(const b2SolverData& data);
 void SolveVelocityConstraints(const b2SolverData& data);
 bool SolvePositionConstraints(const b2SolverData& data);


 b2Vec2 m_localAnchorA;
 b2Vec2 m_localAnchorB;
 float32 m_maxLength;
 float32 m_length;
 float32 m_impulse;


 int32 m_indexA;
 int32 m_indexB;
 b2Vec2 m_u;
 b2Vec2 m_rA;
 b2Vec2 m_rB;
 b2Vec2 m_localCenterA;
 b2Vec2 m_localCenterB;
 float32 m_invMassA;
 float32 m_invMassB;
 float32 m_invIA;
 float32 m_invIB;
 float32 m_mass;
 b2LimitState m_state;
};
#line 64 "Box2D_v2.2.1\\Box2D/Box2D.h"

#line 1 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2WeldJoint.h"
#line 28 "Box2D_v2.2.1\\Box2D/Dynamics/Joints/b2WeldJoint.h"
struct b2WeldJointDef : public b2JointDef
{
 b2WeldJointDef()
 {
  type = e_weldJoint;
  localAnchorA.Set(0.0f, 0.0f);
  localAnchorB.Set(0.0f, 0.0f);
  referenceAngle = 0.0f;
  frequencyHz = 0.0f;
  dampingRatio = 0.0f;
 }



 void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor);


 b2Vec2 localAnchorA;


 b2Vec2 localAnchorB;


 float32 referenceAngle;



 float32 frequencyHz;


 float32 dampingRatio;


 void set_bodyA(b2Body* b) { bodyA = b; }
 void set_bodyB(b2Body* b) { bodyB = b; }
 void set_collideConnected(bool b) { collideConnected = b; }
 b2Body* get_bodyA(b2Body* b) { return bodyA; }
 b2Body* get_bodyB(b2Body* b) { return bodyB; }
 bool get_collideConnected(bool b) { return collideConnected; }
};




class b2WeldJoint : public b2Joint
{
public:
 b2Vec2 GetAnchorA() const;
 b2Vec2 GetAnchorB() const;

 b2Vec2 GetReactionForce(float32 inv_dt) const;
 float32 GetReactionTorque(float32 inv_dt) const;


 const b2Vec2& GetLocalAnchorA() const { return m_localAnchorA; }


 const b2Vec2& GetLocalAnchorB() const { return m_localAnchorB; }


 float32 GetReferenceAngle() const { return m_referenceAngle; }


 void SetFrequency(float32 hz) { m_frequencyHz = hz; }
 float32 GetFrequency() const { return m_frequencyHz; }


 void SetDampingRatio(float32 ratio) { m_dampingRatio = ratio; }
 float32 GetDampingRatio() const { return m_dampingRatio; }


 void Dump();

 b2WeldJoint(const b2WeldJointDef* def);

protected:

 friend class b2Joint;

 void InitVelocityConstraints(const b2SolverData& data);
 void SolveVelocityConstraints(const b2SolverData& data);
 bool SolvePositionConstraints(const b2SolverData& data);

 float32 m_frequencyHz;
 float32 m_dampingRatio;
 float32 m_bias;


 b2Vec2 m_localAnchorA;
 b2Vec2 m_localAnchorB;
 float32 m_referenceAngle;
 float32 m_gamma;
 b2Vec3 m_impulse;


 int32 m_indexA;
 int32 m_indexB;
 b2Vec2 m_rA;
 b2Vec2 m_rB;
 b2Vec2 m_localCenterA;
 b2Vec2 m_localCenterB;
 float32 m_invMassA;
 float32 m_invMassB;
 float32 m_invIA;
 float32 m_invIB;
 b2Mat33 m_mass;
};
#line 65 "Box2D_v2.2.1\\Box2D/Box2D.h"
#line 21 "root.h"

