#pragma once


template <typename _Derived>
class CRTP {
public:
    // The type of the derived class.
    using Derived = _Derived;


public:
    Derived& derived() { return static_cast<Derived&>(*this); }
    const Derived& derived() const { return static_cast<const Derived&>(*this); }
};

