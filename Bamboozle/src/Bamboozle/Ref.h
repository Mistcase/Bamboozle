#pragma once

#include <memory>

namespace bbzl
{
    template <typename T>
    using Ref = std::shared_ptr<T>;

} // namespace bbzl
