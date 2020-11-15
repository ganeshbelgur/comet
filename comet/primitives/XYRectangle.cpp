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


#include "comet/primitives/XYRectangle.hpp"

using namespace comet;

bool XYRectangle::hit(const Ray& r,
                      float t_min,
                      float t_max,
                      HitRecord& record) const
{
    float t = (m_k - r.origin().z()) / r.direction().z();

    if(t < t_min || t > t_max)
    {
        return false;
    }

    float x = r.origin().x() + t * r.direction().x();
    float y = r.origin().y() + t * r.direction().y();

    if(x < m_x0 || x > m_x1 || y < m_y0 || y > m_y1)
    {
        return false;
    }

    record.u = (x - m_x0) / (m_x1 - m_x0);
    record.v = (y - m_y0) / (m_y1 - m_y0);
    record.t = t;
    record.assignedMaterial = m_material;
    record.hitPosition = r.pointAtParameter(t);
    record.normal = Vec3f(0, 0, 1);
    return true;
}
