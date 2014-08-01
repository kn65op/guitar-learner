#include "one_minute_changes/inc/OneMinuteChange.hpp"
#include <gtest/gtest.h>

using namespace ::testing;
using OneMinuteChanges::OneMinuteChange;

struct OneMinuteChangeTest : public Test
{
  OneMinuteChange omc{"A", "D"};
};

TEST_F(OneMinuteChangeTest, OneMinuteChangesShouldBeEuaqlWithSameChords)
{
  OneMinuteChange omc2{"A", "D"};
  EXPECT_EQ(omc, omc2);
}

TEST_F(OneMinuteChangeTest, OneMinuteChangesShouldBeEuaqlWithSwappedChords)
{
  OneMinuteChange omc2{"D", "A"};
  EXPECT_EQ(omc, omc2);
}
  
TEST_F(OneMinuteChangeTest, OneMinuteChangesShouldBeNotEqualWithDifferentChords)
{
  OneMinuteChange omc2{"A", "B"};
  EXPECT_NE(omc, omc2);
}

TEST_F(OneMinuteChangeTest, WithoutAnyResultsBestResultShouldBe0)
{
  EXPECT_EQ(0, omc.bestResult());
}

TEST_F(OneMinuteChangeTest, AfterAddedOneResultBestResultShouldBeThisResult)
{
  const int bestRes = 44;
  omc.addResult(bestRes);
  EXPECT_EQ(bestRes, omc.bestResult());
}

TEST_F(OneMinuteChangeTest, AfterAddedTwoResultsBestResultShouldBeHighestNumber)
{
  const int lowRes = 10;
  const int bestRes = 42;
  omc.addResult(bestRes);
  omc.addResult(lowRes);
  
  EXPECT_EQ(bestRes, omc.bestResult());
}

TEST_F(OneMinuteChangeTest, AfterAddedTwoResultAllResultsShouldReturnChronolgicalResultList)
{
  const int firstRes = 1;
  const int secondRes = 2;
  omc.addResult(firstRes);
  omc.addResult(secondRes);
  
  OneMinuteChange::Results results = omc.getResults();
  
  EXPECT_EQ(firstRes, results[0]);
  EXPECT_EQ(secondRes, results[1]);
}

TEST_F(OneMinuteChangeTest, GetLastResultShouldReturnLastResult)
{
  const int lowRes = 10;
  const int bestRes = 42;
  omc.addResult(bestRes);
  omc.addResult(lowRes);
  
  EXPECT_EQ(lowRes, omc.lastResult());
}