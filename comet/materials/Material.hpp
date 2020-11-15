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


#ifndef COMET_MATERIAL_HPP
#define COMET_MATERIAL_HPP

#include "comet/primitives/Hitable.hpp"
#include "comet/textures/Texture.hpp"
#include "comet/materials/ScatterUtils.hpp"

namespace comet
{

// Class definitions for the materials
class Material
{
    public:
        virtual ~Material()
        {
        }

        // All materials should implement a scatter method
        // which returns a scattered ray for a given incoming ray
        // based on the properties of the material.
        virtual bool scatter(const Ray& r_in,
                             const HitRecord& record,
                             Vec3f& attenuation,
                             Ray& scattered) const = 0;

        virtual Vec3f emitted(float u, float v, const Vec3f &p) const
        {
            // Implemented here as only emitting materials
            // need to implement this method to specialise
            // it.
            return Vec3f(0.0f, 0.0f, 0.0f);
        }
};
COMET_DECLARE_SMART(Material);

} // namespace comet

#endif
