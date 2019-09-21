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


#include "orbinal/materials/Dielectric.hpp"

using namespace Orbinal;

Dielectric::Dielectric(float refractiveIndex) : m_refractiveIndex(refractiveIndex)
{
}

bool Dielectric::scatter(const Ray& r_in,
                         const HitRecord& record,
                         Vec3f& attenuation,
                         Ray& scattered) const
{
    float ni_over_nt;
    float cosine;
    float reflectionProbability = 1.0;
    Vec3f normal;
    Vec3f refracted;

    Vec3f reflected = reflect(unitVector(r_in.direction()),
                             record.normal);
    attenuation = Vec3f(1.0, 1.0, 1.0);

    // Check whether the light ray is moving from a lighter
    // medium to a heavier medium or the opposite
    if(dot(r_in.direction(), record.normal) > 0)
    {
        normal = -record.normal;
        ni_over_nt = m_refractiveIndex;
        cosine =
            m_refractiveIndex * dot(r_in.direction(), record.normal) /
            r_in.direction().length();
    }
    else
    {
        normal = record.normal;
        ni_over_nt = 1.0 / m_refractiveIndex;
        cosine =
            -dot(r_in.direction(), record.normal) /
            r_in.direction().length();
    }

    // Approximating the fresnel effect
    if(refract(r_in.direction(), normal, ni_over_nt, refracted))
    {
        reflectionProbability = schlick(cosine, m_refractiveIndex);
    }

    // Choose to either reflect or refract a ray randomly
    if(drand48() < reflectionProbability)
    {
        scattered = Ray(record.hitPosition, reflected);
    }
    else
    {
        scattered = Ray(record.hitPosition, refracted);
    }

    return true;
}
