/*******************************************************
 * Copyright (c) 2020, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <af/context.h>
#include <af/device.h>
#include <vector>

using std::vector;

namespace af {
namespace multi {

context::context(const vector<int>& devices) : worker_threads_(devices.size()) {
    af_init();

    int i = 0;
    for (auto& worker : worker_threads_) {
        worker.enqueue([=] { setDevice(devices[i]); });
        worker.sync();
        i++;
    }
}

void context::sync() {
    for (auto& worker : worker_threads_) { worker.sync(); }
}

context*& getCurrentContext() {
    static context* c = nullptr;
    return c;
}

context& getContext() { return *getCurrentContext(); }

void setContext(context& c) { getCurrentContext() = &c; }

}  // namespace multi
}  // namespace af
