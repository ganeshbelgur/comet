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


#ifndef COMET_FLIP_NORMALS_HPP
#define COMET_FLIP_NORMALS_HPP

#include "comet/primitives/Hitable.hpp"

namespace comet
{

class FlipNormals : public Hitable
{
    public:
        FlipNormals(HitablePtr object) : m_object(object)
        {
        }

        virtual bool hit(const Ray& r,
                         float t_min,
                         float t_max,
                         HitRecord& record) const
        {
            if(m_object->hit(r, t_min, t_max, record))
            {
                record.normal = -record.normal;
                return true;
            }
            else
            {
                return false;
            }
        }

        // Member variables
        HitablePtr m_object;
};
COMET_DECLARE_SMART(FlipNormals);

} // namespace comet

#endif
