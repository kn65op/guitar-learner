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

TEST_F(TabTest, TabShouldBeReadFromInputWithCarriageReturn)
{
  std::string format = "    1   2   3   4   5   6   7   8   9  10 \r\n"
      "E |-X-|---|---|---|---|---|---|---|---|---\r\n"
      "H |-0-|---|---|---|---|---|---|---|---|---\r\n"
      "G |---|---|---|---|---|---|---|---|---|---\r\n"
      "D |---|---|---|---|---|---|-0-|---|---|---\r\n"
      "A |---|---|---|-0-|---|---|---|---|---|---\r\n"
      "E |---|---|-0-|---|---|---|---|---|---|---\r\n";
  std::string format_without_carriage{format};
  std::string::size_type pos;
  while ((pos = format_without_carriage.find('\r')) != std::string::npos)
  {
    format_without_carriage.replace(pos, 1, "");
  }
  std::stringstream iss;
  iss << format;
  Tab tab{iss};
  std::stringstream oss;
  oss << tab;
  EXPECT_EQ(format_without_carriage, oss.str());
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
