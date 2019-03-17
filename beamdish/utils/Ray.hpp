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


#ifndef BEAMDISH_RAY_HPP
#define BEAMDISH_RAY_HPP

#include "beamdish/utils/Vec3f.hpp"

namespace Beamdish
{

class Ray
{
    public:
        Ray();

        Ray(const Vec3f& origin, const Vec3f& direction);

        // Utility methods
        // Returns the starting point of the ray
        Vec3f origin() const;

        // Returns the direction in which the ray travels
        Vec3f direction() const;

        // Returns the point along the ray at the parametric value 't'
        Vec3f pointAtParameter(float t) const;

        // Member variables
        Vec3f m_ray_origin;
        Vec3f m_ray_direction;
};
BEAMDISH_DECLARE_SMART(Ray);

} // namespace Beamdish

#endif
