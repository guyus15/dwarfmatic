/**
 * \file uuid.cpp
 */

#include "uuid.h"

#include <random>

static std::random_device s_rd;
static std::mt19937_64 s_engine{ s_rd()};
static std::uniform_int_distribution<uint64_t> s_uniform_distribution;

UUID::UUID()
    : m_id{ s_uniform_distribution(s_engine) }
{
}

UUID::UUID(const uint64_t uuid)
    : m_id{ uuid}
{
}

UUID::operator uint64_t() const
{
    return m_id;
}

bool UUID::operator==(const UUID& other) const
{
    return m_id == other.m_id;
}