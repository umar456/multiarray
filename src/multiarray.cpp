/*******************************************************
 * Copyright (c) 2020, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <af/array.h>
#include <af/context.h>
#include <af/device.h>
#include <af/dim4.hpp>
#include <af/multiarray.h>
#include <af/random.h>

#include <vector>

using af::array;
using af::dim4;
using std::vector;

namespace af {
namespace multi {

array::array() : arrays_() {}

array::array(const af::dim4& shape) : arrays_() {
    size_t narrays = getContext().worker_threads_.size();

    arrays_.reserve(narrays);
    getContext().call([](vector<af::array>& arrs, const af::dim4& shape,
                         int id) { arrs.emplace_back(shape); },
                      arrays_, shape);
}

array randu(const dim4& shape) {
    size_t narrays = getContext().worker_threads_.size();
    multi::array out;
    out.arrays_.resize(narrays);
    getContext().call([&](int id) {
        out.arrays_[id] = af::randu(shape);
        printf("randu: %p\n", out.arrays_[id].get());
    });
    return out;
}

void print(const char* msg, const multi::array& arr) {
    getContext().call([&arr, msg](int id) { af::print(msg, arr.arrays_[id]); });
}

void info() {
    getContext().call([](int id) { af::info(); });
}
}  // namespace multi
}  // namespace af
