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


#include "beamdish/materials/Metal.hpp"

using namespace Beamdish;

Metal::Metal(const Vec3f& albedo, float fuzziness) : m_albedo(albedo)
{
    // Fuzziness cannot be greater than 100%
    if(fuzziness < 1.0)
    {
        m_fuzziness = fuzziness;
    }
    else
    {
        m_fuzziness = 1.0;
    }
}

bool Metal::scatter(const Ray& r_in,
                    const HitRecord& record,
                    Vec3f& attenuation,
                    Ray& scattered) const
{
    Vec3f reflected = reflect(unitVector(r_in.direction()),
                             record.normal);

    // The fuzziness factor diverts the reflected
    // ray from its original direction
    scattered = Ray(record.hitPosition,
                    reflected + (m_fuzziness * randomInUnitSphere()));
    attenuation = m_albedo;

    // Scattering for reflective surfaces only occurs when
    // the incident ray is not tangential to the surface
    return (dot(scattered.direction(), record.normal) > 0);
}
