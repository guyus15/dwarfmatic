/**
 * \file system.h
 */

#ifndef SYSTEM_H
#define SYSTEM_H

class ISystem
{
public:
    ISystem() = default;

    ISystem(const ISystem&) noexcept = default;
    ISystem(ISystem&&) = default;

    ISystem& operator=(const ISystem&) = default;
    ISystem& operator=(ISystem&&) noexcept = default;

    virtual ~ISystem() = default;
    virtual void Update(const double dt) = 0;
};

#endif // SYSTEM_H