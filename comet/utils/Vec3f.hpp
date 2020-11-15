// MIT License

// Copyright (c) 2019 Ganesh Belgur Ramachandra

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#ifndef COMET_VEC3F_H
#define COMET_VEC3F_H

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <ostream>

#include "comet/utils/Smart.hpp"

namespace comet
{

class Vec3f
{
    public:
        // Constructors
        Vec3f() : m_x(0.0f), m_y(0.0f), m_z(0.0f)
        {
        }

        Vec3f(float e0, float e1, float e2)
          : m_x(e0), m_y(e1), m_z(e2)
        {
        }

        // Inline getter functions
        inline float x() const
        {
            return m_x;
        }

        inline float y() const
        {
            return m_y;
        }

        inline float z() const
        {
            return m_z;
        }

        inline float r() const
        {
            return m_x;
        }

        inline float g() const
        {
            return m_y;
        }

        inline float b() const
        {
            return m_z;
        }

        // Operator overloading methods
        // Unary operators
        inline const Vec3f& operator+() const
        {
            return *this;
        }

        inline Vec3f operator-() const
        {
            return Vec3f(-m_x, -m_y, -m_z);
        }

        // Binary operators
        inline Vec3f& operator+=(const Vec3f &v);
        inline Vec3f& operator-=(const Vec3f &v);
        inline Vec3f& operator*=(const Vec3f &v);
        inline Vec3f& operator/=(const Vec3f &v);
        inline Vec3f& operator*=(const float t);
        inline Vec3f& operator/=(const float t);

        // Utility functions
        inline float length() const
        {
            return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
        }

        inline float squaredLength() const
        {
            return m_x * m_x + m_y * m_y + m_z * m_z;
        }

        inline void makeUnitVector();

        // Member variables
        float m_x;
        float m_y;
        float m_z;
};

inline void Vec3f::makeUnitVector()
{
    float k = 1.0 / sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    m_x *= k;
    m_y *= k;
    m_z *= k;
}

inline Vec3f& Vec3f::operator+=(const Vec3f &v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
    return *this;
}

inline Vec3f& Vec3f::operator-=(const Vec3f &v)
{
    m_x -= v.m_x;
    m_y -= v.m_y;
    m_z -= v.m_z;
    return *this;
}

inline Vec3f& Vec3f::operator*=(const Vec3f &v)
{
    m_x *= v.m_x;
    m_y *= v.m_y;
    m_z *= v.m_z;
    return *this;
}

inline Vec3f& Vec3f::operator/=(const Vec3f &v)
{
    m_x /= v.m_x;
    m_y /= v.m_y;
    m_z /= v.m_z;
    return *this;
}

inline Vec3f& Vec3f::operator*=(const float t)
{
    m_x *= t;
    m_y *= t;
    m_z *= t;
    return *this;
}

inline Vec3f& Vec3f::operator/=(const float t)
{
    m_x /= t;
    m_y /= t;
    m_z /= t;
    return *this;
}

// Standalone binary operators
inline Vec3f operator+(const Vec3f &v1, const Vec3f &v2)
{
    return Vec3f(v1.m_x + v2.m_x,
                v1.m_y + v2.m_y,
                v1.m_z + v2.m_z);
}

inline Vec3f operator-(const Vec3f &v1, const Vec3f &v2)
{
    return Vec3f(v1.m_x - v2.m_x,
                v1.m_y - v2.m_y,
                v1.m_z - v2.m_z);
}

inline Vec3f operator*(const Vec3f &v1, const Vec3f &v2)
{
    return Vec3f(v1.m_x * v2.m_x,
                v1.m_y * v2.m_y,
                v1.m_z * v2.m_z);
}

inline Vec3f operator/(const Vec3f &v1, const Vec3f &v2)
{
    return Vec3f(v1.m_x / v2.m_x,
                v1.m_y / v2.m_y,
                v1.m_z / v2.m_z);
}

inline Vec3f operator*(float t, const Vec3f &v)
{
    return Vec3f(t * v.m_x, t * v.m_y, t * v.m_z);
}

inline Vec3f operator*(const Vec3f &v, float t)
{
    return Vec3f(t * v.m_x, t * v.m_y, t * v.m_z);
}

inline Vec3f operator/(const Vec3f &v, float t)
{
    return Vec3f(v.m_x / t, v.m_y / t, v.m_z / t);
}

// Stream operators
inline std::istream& operator>>(std::istream &is, Vec3f &t)
{
    is >> t.m_x >> t.m_y >> t.m_z;
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec3f &t)
{
    os << t.m_x << t.m_y << t.m_z;
    return os;
}

// Standalone utility methods
inline Vec3f unitVector(Vec3f v)
{
    return v / v.length();
}

inline float dot(const Vec3f &v1, const Vec3f &v2)
{
    return v1.m_x * v2.m_x + v1.m_y * v2.m_y + v1.m_z * v2.m_z;
}

inline Vec3f cross(const Vec3f &v1, const Vec3f &v2)
{
    return Vec3f((v1.m_y * v2.m_z - v1.m_z * v2.m_y),
                -(v1.m_x * v2.m_z - v1.m_z * v2.m_x),
                (v1.m_x * v2.m_y - v1.m_y * v2.m_x));
}

} // namespace comet

#endif
