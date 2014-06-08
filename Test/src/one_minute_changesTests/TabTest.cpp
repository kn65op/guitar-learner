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

TEST_F(TabTest, TabShouldBeReadFromInput)
{
  std::string format = "    1   2   3   4   5   6   7   8   9  10 \n"
                       "E |---|---|---|---|---|---|---|---|---|---\n" 
                       "H |---|---|---|---|---|---|---|---|---|---\n" 
                       "G |---|---|---|---|---|---|---|---|---|---\n" 
                       "D |---|---|---|---|---|---|---|---|---|---\n" 
                       "A |---|---|---|---|---|---|---|---|---|---\n" 
                       "E |---|---|---|---|---|---|---|---|---|---\n";
  std::stringstream iss;
  iss << format;
  Tab t{iss};
  std::stringstream oss;
  oss << t;
  EXPECT_EQ(format, oss.str());
}

TEST_F(TabTest, TwoTabsShouldBeReadFromInput)
{
  std::string format1 = "    1   2   3   4   5   6   7   8   9  10 \n"
                       "E |---|---|---|---|---|---|---|---|---|---\n" 
                       "H |---|---|---|---|---|---|---|---|---|---\n" 
                       "G |---|---|---|---|---|---|---|---|---|---\n" 
                       "D |---|---|---|---|---|---|---|---|---|---\n" 
                       "A |---|---|---|---|---|---|---|---|---|---\n" 
                       "E |---|---|---|---|---|---|---|---|---|---\n";
  std::string format2 = "    1   2   3   4   5   6   7   8   9  10 \n"
                       "E |-X-|---|---|---|---|---|---|---|---|---\n" 
                       "H |-0-|---|---|---|---|---|---|---|---|---\n" 
                       "G |---|---|---|---|---|---|---|---|---|-0-\n" 
                       "D |---|---|---|---|---|---|-0-|---|---|---\n" 
                       "A |---|---|---|-0-|---|---|---|---|---|---\n" 
                       "E |---|---|-0-|---|---|---|---|---|---|---\n";
  std::stringstream iss;
  iss << format1 << format2;
  Tab t1{iss};
  Tab t2{iss};
  std::stringstream oss1;
  oss1 << t1;
  std::stringstream oss2;
  oss2 << t2;
  EXPECT_EQ(format1, oss1.str());
  EXPECT_EQ(format2, oss2.str());
}