/*******************************************************
 * Copyright (c) 2020, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <arrayfire.h>
#include <gtest/gtest.h>
#include <af/context.h>
#include <af/multiarray.h>

using namespace af;

TEST(BasicTest, Basic) {
    setDevice(0);
    array a = randu(10);

    multi::context c({0, 1});
    multi::setContext(c);
    multi::info();
    multi::array ma(dim4{10});

    auto ma2 = multi::randu(dim4{10, 10});

    print("ma2", ma2);
    c.sync();
}
