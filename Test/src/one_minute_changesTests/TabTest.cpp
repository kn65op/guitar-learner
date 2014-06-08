#include <one_minute_changes/inc/Tab.hpp>
#include "gtest/gtest.h"
#include <sstream>

using namespace ::testing;
using Guitar::Tab;

struct TabTest : public Test
{
};

TEST_F(TabTest, DefaultTabShouldBeAllZeros)
{
  Tab t;
  std::stringstream ss;
  ss << t;
  EXPECT_EQ(
            "    1   2   3   4   5   6   7   8   9  10 \n"
            "E |---|---|---|---|---|---|---|---|---|---\n" 
            "H |---|---|---|---|---|---|---|---|---|---\n" 
            "G |---|---|---|---|---|---|---|---|---|---\n" 
            "D |---|---|---|---|---|---|---|---|---|---\n" 
            "A |---|---|---|---|---|---|---|---|---|---\n" 
            "E |---|---|---|---|---|---|---|---|---|---\n",
            ss.str());
}

TEST_F(TabTest, TabWithSpecifiedFretsShouldPrintCorrectFrets)
{
  Tab t{-1, 0, 1, 2, 3, 10};
  std::stringstream ss;
  ss << t;
  EXPECT_EQ(
            "    1   2   3   4   5   6   7   8   9  10 \n"
            "E |-X-|---|---|---|---|---|---|---|---|---\n" 
            "H |---|---|---|---|---|---|---|---|---|---\n" 
            "G |-0-|---|---|---|---|---|---|---|---|---\n" 
            "D |---|-0-|---|---|---|---|---|---|---|---\n" 
            "A |---|---|-0-|---|---|---|---|---|---|---\n" 
            "E |---|---|---|---|---|---|---|---|---|-0-\n",
            ss.str());
}