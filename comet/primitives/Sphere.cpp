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


#include "comet/primitives/Sphere.hpp"

using namespace comet;

namespace
{
    void getSphereUV(const Vec3f &p, float u, float v)
    {
        float phi = atan2(p.z(), p.x());
        float theta = asin(p.y());
        u = 1 - (phi + M_PI) / (2 * M_PI);
        v = (theta + M_PI/2) / M_PI;
    }
}

bool Sphere::hit(const Ray& r,
                 float t_min,
                 float t_max,
                 HitRecord& record) const
{
    // Calculating the discriminant
    Vec3f oc = r.origin() - m_center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - m_radius * m_radius;
    float discriminant = b * b - 4 * a * c;

    // Calculating the first root
    float root = (-b - sqrt(discriminant)) / (2.0 * a);

    // Calculate the hitPosition and normal to update the
    // record if within t_min and t_max
    if(root > t_min && root < t_max)
    {
        record.t = root;
        record.hitPosition = r.pointAtParameter(record.t);
        record.normal = (record.hitPosition - m_center) / m_radius;
        getSphereUV(record.normal, record.u, record.v);
        record.assignedMaterial = m_material;
        return true;
    }

    // Calculating the second root
    root = (-b + sqrt(discriminant)) / (2.0 * a);

    // Calculate the hitPosition and normal to update the
    // record if within t_min and t_max
    if (root > t_min && root < t_max)
    {
        record.t = root;
        record.hitPosition = r.pointAtParameter(record.t);
        record.normal = (record.hitPosition - m_center) / m_radius;
        getSphereUV(record.normal, record.u, record.v);
        record.assignedMaterial = m_material;
        return true;
    }

    return false;
}
