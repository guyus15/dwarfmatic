#ifndef ASSERTION_H
#define ASSERTION_H

#include "utils/logging.h"

#include <cstdlib>

#define DFM_ASSERTION 1
#if DFM_ASSERTION
#define DFM_ASSERT(COND, MSG) do { \
    if (COND) \
    { \
        DFM_CORE_CRITICAL("Assertion failed ({0}:{1}): {2}", __FILE__, __LINE__, (MSG)); \
    } \
} \
while (0)
#else
#define DFM_ASSERT(COND, MSG)
#endif

#endif // ASSERTION_H