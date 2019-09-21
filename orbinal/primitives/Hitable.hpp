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


#ifndef ORBINAL_HITABLE_HPP
#define ORBINAL_HITABLE_HPP

#include "orbinal/utils/Ray.hpp"
// #include "orbinal/materials/Material.hpp"

namespace Orbinal
{

ORBINAL_DECLARE_FORWARD(Material);

// Hit record holds the properties of the
// point at the ray-object intersection
struct HitRecord
{
    float t;
    float u;
    float v;
    Vec3f hitPosition;
    Vec3f normal;
    MaterialPtr assignedMaterial;
};

// Abstract base class for things that a ray can hit
class Hitable
{
    public:
        Hitable()
        {
        }

        virtual ~Hitable()
        {
        }

        // The derived objects need to
        // implement their own hit functions
        virtual bool hit(const Ray& r,
                         float t_min,
                         float t_max,
                         HitRecord& record) const = 0;
};
ORBINAL_DECLARE_SMART(Hitable);

} //namespace Orbinal

#endif
