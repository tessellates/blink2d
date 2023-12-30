#pragma once

#include <optional>

template<typename T>
T* getOptionalPtr(std::optional<T>& opt) 
{
    return opt.has_value() ? &*opt : nullptr;
};
