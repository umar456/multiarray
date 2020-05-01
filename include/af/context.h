/*******************************************************
 * Copyright (c) 2020, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#pragma once

#include <async_queue.hpp>

#include <thread>
#include <vector>

namespace af {
namespace multi {

class context {
   public:
    std::vector<threads::async_queue> worker_threads_;
    context(const std::vector<int> &devices);
    ~context() = default;
    void sync();

    template<typename FUNC, typename... ARGS>
    void call(FUNC f, ARGS... args) {
        size_t narrays = worker_threads_.size();
        for (int i = 0; i < narrays; i++) {
            worker_threads_[i].enqueue(f, args..., i);
        }
    }
};

context &getContext();

void setContext(context &c);

}  // namespace multi
}  // namespace af
