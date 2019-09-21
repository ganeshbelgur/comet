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


#include "orbinal/utils/Camera.hpp"

using namespace Orbinal;

namespace
{
    Vec3f randomInUnitDisk()
    {
        Vec3f p;

        do
        {
            // The difference with the randomInUnitSphere is that the
            // Z-coordinate here is 0.0f always
            p = 2.0f * Vec3f(drand48(), drand48(), 0.0f) - Vec3f(1.0, 1.0, 0.0f);
        } while (dot(p, p) >= 1.0f);

        return p;
    }
}

Camera::Camera(Vec3f lookfrom,
       Vec3f lookat,
       Vec3f vup,
       float vfov,
       float aspect,
       float aperture,
       float focus_distance
)
{
    // Radius of the lens is half of aperture
    // since aperture size is the diameter of
    // the lens
    m_lens_radius = aperture / 2.0f;

    // Calculate one half of the height and the width of
    // the image frame with the help of the aspect ratio
    float theta = vfov * M_PI / 180.0f;
    float half_height = tan(theta / 2.0f);
    float half_width = aspect * half_height;

    // Calculate the coordinate system
    // for the camera
    m_origin = lookfrom;
    m_w = unitVector(lookfrom - lookat);
    m_u = unitVector(cross(vup, m_w));
    m_v = cross(m_w, m_u);

    // Think of the positions of the following objects in
    // this order in the scene with respect to the origin,
    // camera == lens == image frame == origin.
    // To get the left bottom point of the image frame, we
    // need to effectively calculate the position vector to
    // the left bottom point of the image frame.
    m_left_bottom_corner =
        m_origin - half_width * focus_distance *
        m_u - half_height * focus_distance *
        m_v - focus_distance * m_w;

    // Calculating the complete height and width of the image frame
    m_horizontal = 2.0f * half_width * focus_distance * m_u;
    m_vertical = 2.0f * half_height * focus_distance * m_v;
}

Ray Camera::getRay(float s, float t) const
{
    Vec3f rd = m_lens_radius * randomInUnitDisk();
    Vec3f offset = m_u * rd.x() + m_v * rd.y();
    return Ray(m_origin + offset,
               m_left_bottom_corner + s * m_horizontal +
               t * m_vertical - m_origin - offset);
}
