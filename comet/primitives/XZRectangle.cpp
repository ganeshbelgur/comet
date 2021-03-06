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


#include "comet/primitives/XZRectangle.hpp"

using namespace comet;

bool XZRectangle::hit(const Ray& r,
                  float t_min,
                  float t_max,
                  HitRecord& record) const
{
    float t = (m_k - r.origin().y()) / r.direction().y();

    if(t < t_min || t > t_max)
    {
        return false;
    }

    float x = r.origin().x() + t * r.direction().x();
    float z = r.origin().z() + t * r.direction().z();

    if(x < m_x0 || x > m_x1 || z < m_z0 || z > m_z1)
    {
        return false;
    }

    record.u = (x - m_x0) / (m_x1 - m_x0);
    record.v = (z - m_z0) / (m_z1 - m_z0);
    record.t = t;
    record.assignedMaterial = m_material;
    record.hitPosition = r.pointAtParameter(t);
    record.normal = Vec3f(0, 1, 0);
    return true;
}
