/*******************************************************
 * Copyright (c) 2020, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#pragma once

#include <arrayfire.h>
#include <af/array.h>
#include <vector>

namespace af {
namespace multi {

class array {
   public:
    std::vector<af::array> arrays_;
    array();
    array(array &&other) = default;
    array &operator=(array &&other) = default;
    explicit array(const dim4 &shape);
};

array randu(const dim4 &shape);

void print(const char *msg, const array &arr);

void info();
}  // namespace multi
}  // namespace af
