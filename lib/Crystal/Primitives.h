//----------------------------------------------------------------------------
// File:         Primitives.h
// Description:  Geometric primitive types for the Crystal library
//----------------------------------------------------------------------------
#ifndef CRYSTAL_PRIMITIVES_H
#define CRYSTAL_PRIMITIVES_H
#include <vector>
#include <math.h>
#include <Crystal/Types.h>
namespace Crystal {
	//----------------------------------------------------------------------------
	// 
	//----------------------------------------------------------------------------
	template <typename _T>
	struct Point
	{
		_T x;
		_T y;
		Point()
		{
		}
		Point(_T _x, _T _y)
		: x(_x), y(_y)
		{
		}
	};

	//----------------------------------------------------------------------------
	// 
	//----------------------------------------------------------------------------
	template <typename _T>
	struct Rectangle
	{
		/*Rectangle()
		: x(0), y(0), w(0), h(0)
		{
		}
		Rectangle(_T size)
		: x(0), y(0), w(size), h(size)
		{
		}
		Rectangle(_T x, _T y, _T size)
		: x(x), y(y), w(size), h(size)
		{
		}
	
		Rectangle(_T x, _T y, _T w, _T h)
		: x(x), y(y), w(w), h(h)
		{
		}*/
	
		int GetArea() const {
			return w * h;
		}
    
		bool Intersects(Rectangle<_T>& other) const
	   {
	      return !(other.x > x + w || x + w < other.x ||
	               other.y > y + h || y + h < other.y);
	   }
		bool operator<(const Rectangle<_T>& rect) const
	   {
			return GetArea() < rect.GetArea();
		}
	
		_T  x;
		_T  y;
		_T  w;
		_T  h;
	};

	//----------------------------------------------------------------------------
	// 
	//----------------------------------------------------------------------------
	template <typename _T>
	struct Line
	{
		_T x1, y1;
		_T x2, y2;
	     Line(_T _x1, _T _y1, _T _x2, _T _y2)
	    : x1(_x1), y1(_y1), x2(_x2), y2(_y2)
	    {
	    }
	};

	//----------------------------------------------------------------------------
	// 
	//----------------------------------------------------------------------------
	class Vector
	{
	public:
		Crystal::FloatingPoint x;
		Crystal::FloatingPoint y;
    
	    // constructor
		Vector()
		: x(0),y(0)
		{
		}

	    Vector(Crystal::FloatingPoint _x, Crystal::FloatingPoint _y)
		: x(_x),y(_y)
	    {
	    }
		/*Vector(const Vector& other)
		: x(other.x),y(other.y)
	    {
	    }*/
    
	    // observers
	     Crystal::FloatingPoint Length()
	    {
	        return sqrt((x*x) + (y*y));
	    }
    
	    // mutators
	     void Negate()
	    {
	        x = -x;
	        y = -y;
	    }
	     void Normalize()
	    {
	        Crystal::FloatingPoint len = Length();
	        x /= len;
	        y /= len;
	    }
	    /* void CrossWith( const Vector<_T> &other )
	    {
	        _T x1, y1, z1;
	        x1 = (y * other.z) - (z * other.y);
	        y1 = (z * other.x) - (x * other.z);
	        z1 = (x * other.y) - (y * other.x);
	        x = x1;
	        y = y1;
	        z = z1;
	    }
	     _T DotProduct( const Vector<_T> &other )
	    {
	        return (x * other.x) + (y * other.y) + (z * other.z);
	    }*/

		Vector Rotate(const Crystal::FloatingPoint radians)
		{
			Crystal::FloatingPoint c = cos(radians);
			Crystal::FloatingPoint s = sin(radians);
			return Vector(x*c - y*s, y*c + x*s);
		}
    
		Vector& operator=(const Vector &rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
			return *this;
		}
		Vector& operator+(const Vector &rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			return *this;
		}
		Vector& operator-(const Vector &rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			return *this;
		}
		Vector& operator*(const Vector &rhs)
		{
			this->x *= rhs.x;
			this->y *= rhs.y;
			return *this;
		}
		Vector& operator/(const Vector &rhs)
		{
			this->x /= rhs.x;
			this->y /= rhs.y;
			return *this;
		}
		Vector& operator*(const Crystal::FloatingPoint scale)
		{
			this->x *= scale;
			this->y *= scale;
			return *this;
		}
		Vector operator*=(const Vector &rhs) const
	    {
	        return Vector(x*rhs.x, y*rhs.y);
	    }
		Vector operator/=(const Vector &rhs) const
	    {
	        return Vector(x/rhs.x, y/rhs.y);
	    }
		Vector operator+=(const Vector &rhs) const
	    {
	        return Vector(x+rhs.x, y+rhs.y);
	    }
		Vector operator-=(const Vector &rhs) const
	    {
	        return Vector(x-rhs.x, y-rhs.y);
	    }
		Vector operator*=(const Crystal::FloatingPoint rhs) const
	    {
	        return Vector(x*rhs, y*rhs);
	    }
		Vector operator/=(const Crystal::FloatingPoint rhs) const
	    {
	        return Vector(x*rhs, y*rhs);
	    }
		bool operator ==(const Vector &rhs) const
		{
			return ((x==rhs.x)&&(y==rhs.y));
		}
		bool operator !=(const Vector &rhs) const
		{
			return ((x!=rhs.x)||(y!=rhs.y));
		}
		Vector operator*(const Crystal::FloatingPoint scale) const
	    {
	        return Vector(x*scale, y*scale);
	    }
	};

	//----------------------------------------------------------------------------
	// 
	//----------------------------------------------------------------------------
	template <typename _T>
	class Bezier
	{
	public:
		Point<_T> m_a, m_b, m_c;
		Bezier(Point<_T> a, Point<_T> b, Point<_T> c)
		: m_a(a), m_b(b), m_c(c)
		{
		}
		Point<_T> Plot(_T interval) //from [0.0]...[1.0]
		{
			Point<_T> pt;
			_T a = interval, b = 1.0 - a;
		
			//	X(a) = Ax·a² + Bx·2·a·b + Cx·b²
			//	Y(a) = Ay·a² + By·2·a·b + Cy·b²
			_T aa = a*a;
			_T ab2 = 2.0*a*b;
			_T bb = b*b;
			pt.x = (m_a.x*aa) + (m_b.x*ab2) + (m_c.x * bb);
			pt.y = (m_a.y*aa) + (m_b.y*ab2) + (m_c.y * bb);
			return pt;
		}
	};
}
#endif