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


#include "comet/materials/ScatterUtils.hpp"

namespace comet
{

Vec3f randomInUnitSphere()
{
    Vec3f p;

    do
    {
        p = 2.0 * Vec3f(drand48(), drand48(), drand48()) - Vec3f(1, 1, 1);
    } while (p.squaredLength() >= 1.0);

    return p;
}

Vec3f reflect(const Vec3f& v, const Vec3f& normal)
{
    return v - 2.0 * dot(v, normal) * normal;
}

bool refract(const Vec3f& incident,
             const Vec3f& normal,
             float ni_over_nt,
             Vec3f& refracted)
{
    // Converting the incident ray into a unit vector
    Vec3f unit_incident = unitVector(incident);
    float dt = dot(unit_incident, normal);

    // As long as the discriminant is positive, the Snell's law has real roots
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);

    if(discriminant > 0)
    {
        // Getting the refracted ray direction by
        // using the vector form of Snell's law
        refracted = ni_over_nt *
            (unit_incident - normal * dt) - normal * sqrt(discriminant);

        return true;
    }

    return false;
}

float schlick(float cosine, float refractiveIndex)
{
    float r0 = (1.0 - refractiveIndex) / (1.0 + refractiveIndex);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow((1.0 - cosine), 5);
}

} // namespace comet
