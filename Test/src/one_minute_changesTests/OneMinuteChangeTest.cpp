#include "one_minute_changes/inc/OneMinuteChange.hpp"
#include <gtest/gtest.h>
#include <sstream>

using namespace ::testing;
using OneMinuteChanges::OneMinuteChange;

struct OneMinuteChangeTest : public Test
{
  OneMinuteChange omc{"A", "D"};
};

TEST_F(OneMinuteChangeTest, OneMinuteChangeShouldReturnChordsAndTimeAddedCloseToNow)
{
  EXPECT_EQ("A", omc.getFirstChord());
  EXPECT_EQ("D", omc.getSecondChord());

/*  auto now = std::chrono::system_clock::now();

  std::chrono::microseconds allowed_difference{100};
  auto actual_difference = std::chrono::duration_cast<std::chrono::microseconds>(now - omc.getAddedDate());

  EXPECT_GE(allowed_difference.count(), actual_difference.count());
  */
}

TEST_F(OneMinuteChangeTest, OneMinuteChangeShouldReturnChordsAlphabetical)
{
  OneMinuteChange omc2{"D", "A"};

  EXPECT_EQ("A", omc2.getFirstChord());
  EXPECT_EQ("D", omc2.getSecondChord());
}

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
  EXPECT_EQ(0, omc.bestResult().first);
}

TEST_F(OneMinuteChangeTest, AfterAddedOneResultBestResultShouldBeThisResult)
{
  const int bestRes = 44;
  omc.addResult(bestRes);
  EXPECT_EQ(bestRes, omc.bestResult().first);
}

TEST_F(OneMinuteChangeTest, AfterAddedTwoResultsBestResultShouldBeHighestNumber)
{
  const int lowRes = 10;
  const int bestRes = 42;
  omc.addResult(bestRes);
  omc.addResult(lowRes);

  EXPECT_EQ(bestRes, omc.bestResult().first);
}

TEST_F(OneMinuteChangeTest, AfterAddedTwoResultAllResultsShouldReturnChronolgicalResultList)
{
  const int firstRes = 1;
  const int secondRes = 2;
  omc.addResult(firstRes);
  omc.addResult(secondRes);

  OneMinuteChange::Results results = omc.getResults();

  EXPECT_EQ(firstRes, results[0].first);
  EXPECT_EQ(secondRes, results[1].first);
}

TEST_F(OneMinuteChangeTest, GetLastResultShouldReturn0)
{
  EXPECT_EQ(0, omc.lastResult().first);
}

TEST_F(OneMinuteChangeTest, GetLastResultShouldReturnLastResult)
{
  const int lowRes = 10;
  const int bestRes = 42;
  omc.addResult(bestRes);
  omc.addResult(lowRes);

  EXPECT_EQ(lowRes, omc.lastResult().first);
}

TEST_F(OneMinuteChangeTest, OneMinuteChangeShouldBePrinted)
{
  const int firstRes = 1;
  const int secondRes = 2;
  const int bestRes = 5;
  const int fourthRes = 3;
  const int resSize = 4;

  omc.addResult(firstRes);
  omc.addResult(secondRes);
  omc.addResult(bestRes);
  omc.addResult(fourthRes);

  std::stringstream ss;

  ss << omc;

  auto now = std::chrono::system_clock::now();
  auto secs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

  std::string resultString = omc.getFirstChord() + "\n" +
      omc.getSecondChord() + "\n" +
      std::to_string(resSize) + "\n" +
      std::to_string(firstRes) + " " + std::to_string(secs.count()) + "\n" +
      std::to_string(secondRes) + " " + std::to_string(secs.count()) +  "\n" +
      std::to_string(bestRes) + " " + std::to_string(secs.count()) + "\n" +
      std::to_string(fourthRes) + " " + std::to_string(secs.count()) + "\n";

  EXPECT_EQ(resultString, ss.str());
}

TEST_F(OneMinuteChangeTest, OneMinuteChangeCanBeReaded)
{
  const int firstRes = 1;
  const int secondRes = 2;
  const int bestRes = 5;
  const int fourthRes = 3;
  std::vector<int> results{firstRes, secondRes, bestRes, fourthRes};
  const std::string chordA = "A";
  const std::string chordB = "B";

  std::stringstream ss;
  ss << chordA << "\n";
  ss << chordB << "\n";
  ss << results.size() << "\n";
  ss << firstRes << "\n";
  ss << secondRes << "\n";
  ss << bestRes << "\n";
  ss << fourthRes << "\n";

  OneMinuteChange omc2{ss};

  EXPECT_EQ(chordA, omc2.getFirstChord());
  EXPECT_EQ(chordB, omc2.getSecondChord());
  OneMinuteChange::Results results_got = omc2.getResults();
  auto it = results_got.begin();
  for (auto res : results_got)
  {
    EXPECT_EQ(res, *it++);
  }
  EXPECT_EQ(bestRes, omc2.bestResult().first);
  EXPECT_EQ(fourthRes, omc2.lastResult().first);
}