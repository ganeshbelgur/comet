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


#ifndef BEAMDISH_DIELECTRIC_HPP
#define BEAMDISH_DIELECTRIC_HPP

#include "beamdish/materials/Material.hpp"

namespace Beamdish
{

class Dielectric : public Material
{
    public:
        Dielectric(float refractiveIndex);

        virtual bool scatter(const Ray& r_in,
                             const HitRecord& record,
                             Vec3f& attenuation,
                             Ray& scattered) const;
    private:
        // Member variables
        float m_refractiveIndex;
};
BEAMDISH_DECLARE_SMART(Dielectric);

} // namespace Beamdish

#endif
