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


#ifndef BEAMDISH_SPHERE_HPP
#define BEAMDISH_SPHERE_HPP

#include "beamdish/primitives/Hitable.hpp"

namespace Beamdish
{

// Sphere class which is inherited from hitable abstract
// class tells a ray how to collide with a Sphere
class Sphere : public Hitable
{
    public:
        Sphere()
        {
        }

        Sphere(float radius, Vec3f center, MaterialPtr inMaterial) :
            m_radius(radius), m_center(center), m_material(inMaterial)
        {
        }

        virtual bool hit(const Ray& r,
                         float t_min,
                         float t_max,
                         HitRecord& record) const;

        // Member variables
        float m_radius;
        Vec3f m_center;
        MaterialPtr m_material;
};
BEAMDISH_DECLARE_SMART(Sphere);

} // namespace Beamdish

#endif
