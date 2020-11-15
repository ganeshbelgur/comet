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


#ifndef COMET_CAMERA_HPP
#define COMET_CAMERA_HPP

#include "comet/utils/Ray.hpp"

namespace comet
{

class Camera
{
    public:
        Camera(Vec3f lookfrom,
               Vec3f lookat,
               Vec3f vup,
               float vfov,
               float aspect,
               float aperture,
               float focus_distance
        );

        Ray getRay(float s, float t) const;

    private:
        // Member variables
        // Set up the screen for shooting rays through
        Vec3f m_left_bottom_corner;
        Vec3f m_horizontal;
        Vec3f m_vertical;
        Vec3f m_u, m_v, m_w;
        Vec3f m_origin; // Camera's eye position
        float m_lens_radius;
};
COMET_DECLARE_SMART(Camera);

} // namespace comet

#endif
