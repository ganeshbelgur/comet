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

#ifndef BEAMDISH_YZRECTANGLE_HPP
#define BEAMDISH_YZRECTANGLE_HPP

#include "beamdish/primitives/Hitable.hpp"
#include "beamdish/materials/Material.hpp"

namespace Beamdish
{

class YZRectangle: public Hitable
{
    public:
        YZRectangle()
        {
        }

        YZRectangle(float y0,
                    float y1,
                    float z0,
                    float z1,
                    float k,
                    MaterialPtr inMaterial) :
            m_y0(y0),
            m_y1(y1),
            m_z0(z0),
            m_z1(z1),
            m_k(k),
            m_material(inMaterial)
        {
        }

        virtual bool hit(const Ray& r,
                         float t_min,
                         float t_max,
                         HitRecord& record) const;

        // Member variables
        float m_y0, m_y1, m_z0, m_z1, m_k;
        MaterialPtr m_material;
};
BEAMDISH_DECLARE_SMART(YZRectangle);

} // namespace Beamdish

#endif
