/**
 * \file uuid.h
 */

#ifndef UUID_H
#define UUID_H

#include <cstdint>
#include <functional>

class UUID
{
public:
    UUID();
    explicit UUID(uint64_t uuid);
    explicit operator uint64_t() const;
    bool operator==(const UUID& other) const;
private:
    uint64_t m_id;
};

template <>
struct std::hash<UUID>
{
    std::size_t operator()(const UUID& uuid) const noexcept
    {
        return std::hash<uint64_t>{}(static_cast<uint64_t>(uuid));
    }
};

#endif // UUID_H