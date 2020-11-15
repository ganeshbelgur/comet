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


#ifndef COMET_TEXTURE_HPP
#define COMET_TEXTURE_HPP

#include "comet/utils/Vec3f.hpp"

namespace comet
{

class Texture
{
    public:
        virtual Vec3f value(float u, float v, const Vec3f &p) const = 0;
};
COMET_DECLARE_SMART(Texture);

// Class for representing colors as textures
class ConstantTexture : public Texture
{
    public:
        ConstantTexture()
        {
        }

        ConstantTexture(Vec3f color) : m_color(color)
        {
        }

        virtual Vec3f value(float u, float v, const Vec3f &p) const
        {
            return m_color;
        }

        // Member variables
        Vec3f m_color;
};
COMET_DECLARE_SMART(ConstantTexture);

// Class for checker texture
class CheckerTexture : public Texture
{
    public:
        CheckerTexture()
        {
        }

        CheckerTexture(TexturePtr t0, TexturePtr t1) : m_even(t0), m_odd(t1)
        {
        }

        virtual Vec3f value(float u, float v, const Vec3f &p) const
        {
            float sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());

            if(sines < 0)
            {
                return m_odd->value(u, v, p);
            }
            else
            {
                return m_even->value(u, v, p);
            }
        }

        // Member variables
        TexturePtr m_even;
        TexturePtr m_odd;
};
COMET_DECLARE_SMART(CheckerTexture);

} // namespace comet

#endif
