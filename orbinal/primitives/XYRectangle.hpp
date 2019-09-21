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


#ifndef ORBINAL_XYRECTANGLE_HPP
#define ORBINAL_XYRECTANGLE_HPP

#include "orbinal/primitives/Hitable.hpp"
#include "orbinal/materials/Material.hpp"

namespace Orbinal
{

class XYRectangle: public Hitable
{
    public:
        XYRectangle()
        {
        }

        XYRectangle(float x0,
                    float x1,
                    float y0,
                    float y1,
                    float k,
                    MaterialPtr inMaterial) :
            m_x0(x0),
            m_x1(x1),
            m_y0(y0),
            m_y1(y1),
            m_k(k),
            m_material(inMaterial)
        {
        }

        virtual bool hit(const Ray& r,
                         float t_min,
                         float t_max,
                         HitRecord& record) const;

        // Member variables
        float m_x0, m_x1, m_y0, m_y1, m_k;
        MaterialPtr m_material;
};
ORBINAL_DECLARE_SMART(XYRectangle);

} // namespace Orbinal

#endif
