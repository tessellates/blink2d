#pragma once

#include <CRTP.hpp>

template <typename _Derived>
class Singleton : public CRTP<_Derived> {
private:
    static _Derived* instance_;

protected:
    Singleton() = default;
    ~Singleton() = default;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    static _Derived* instance() {
        if (!instance_) {
            instance_ = new _Derived();
        }
        return instance_;
    }

    static void destroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }
};

template <typename _Derived>
_Derived* Singleton<_Derived>::instance_ = nullptr;