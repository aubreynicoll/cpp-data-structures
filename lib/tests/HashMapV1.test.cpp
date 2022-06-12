#include "../HashMapV1.h"

#include <gtest/gtest.h>

/* Having a ton of issues getting GTest to work with this data structure...
Still investigating for now. I've independently tested the HashMap and it seems
to work just fine. Will update tests later when I get to the bottom of it. */

/* Must use typedef because template args confuses the macros */
typedef HashMap<char, int> Map;

TEST(HashMapV1Test, BasicConstructor) { EXPECT_NO_FATAL_FAILURE(Map map); }
