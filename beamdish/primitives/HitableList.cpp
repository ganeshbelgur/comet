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


#include "beamdish/primitives/HitableList.hpp"

using namespace Beamdish;

HitableList::HitableList(HitablePtr *list, int list_size)
  : m_list(list), m_list_size(list_size)
{
}

// Calls the hit method of all the children hitable objects
bool HitableList::hit(const Ray& r,
                      float t_min,
                      float t_max,
                      HitRecord& record) const
{
    HitRecord temp_record;
    bool hit_anything = false;
    double closest_point_so_far = t_max;

    for(int i = 0; i < m_list_size; i++)
    {
        // Perform ray-object intersection tests
        // for all the hitable objects in the list
        if(m_list[i]->hit(r, t_min, closest_point_so_far, temp_record))
        {
            hit_anything = true;
            closest_point_so_far = temp_record.t;
            record = temp_record;
        }
    }

    return hit_anything;
}
