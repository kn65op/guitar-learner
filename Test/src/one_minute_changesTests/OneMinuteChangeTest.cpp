#include "one_minute_changes/inc/OneMinuteChange.hpp"
#include <gtest/gtest.h>
#include <sstream>

using namespace ::testing;
using OneMinuteChanges::OneMinuteChange;

struct OneMinuteChangeTest : public Test
{
  OneMinuteChange omc {"A", "D"};
};

TEST_F(OneMinuteChangeTest, OneMinuteChangeShouldReturnChordsAndTimeAddedCloseToNow)
{
  EXPECT_EQ("A", omc.getFirstChord());
  EXPECT_EQ("D", omc.getSecondChord());
}

TEST_F(OneMinuteChangeTest, OneMinuteChangeShouldReturnChordsAlphabetical)
{
  OneMinuteChange omc2 {"D", "A"};

  EXPECT_EQ("A", omc2.getFirstChord());
  EXPECT_EQ("D", omc2.getSecondChord());
}

TEST_F(OneMinuteChangeTest, OneMinuteChangesShouldBeEuaqlWithSameChords)
{
  OneMinuteChange omc2 {"A", "D"};
  EXPECT_EQ(omc, omc2);
}

TEST_F(OneMinuteChangeTest, OneMinuteChangesShouldBeEuaqlWithSwappedChords)
{
  OneMinuteChange omc2 {"D", "A"};
  EXPECT_EQ(omc, omc2);
}

TEST_F(OneMinuteChangeTest, OneMinuteChangesShouldBeNotEqualWithDifferentChords)
{
  OneMinuteChange omc2 {"A", "B"};
  EXPECT_NE(omc, omc2);
}

TEST_F(OneMinuteChangeTest, WithoutAnyResultsBestResultShouldThrowNoResults)
{
  EXPECT_THROW(omc.bestResult(), OneMinuteChange::NoResultsError);
}

TEST_F(OneMinuteChangeTest, WithoutAnyResultsHasResultsShouldReturnFalse)
{
  EXPECT_FALSE(omc.hasResults());
}

TEST_F(OneMinuteChangeTest, WithResultsHasResultsShouldReturnTrue)
{
  omc.addResult(0);
  EXPECT_TRUE(omc.hasResults());
}

TEST_F(OneMinuteChangeTest, AfterAddedOneResultBestResultShouldBeThisResultAndShouldBeAddedNow)
{
  const int bestRes = 44;
  omc.addResult(bestRes);

  auto now = std::chrono::system_clock::now();

  std::chrono::microseconds allowed_difference {100};
  auto actual_difference = std::chrono::duration_cast < std::chrono::microseconds > (now - omc.bestResult().second);

  EXPECT_EQ(bestRes, omc.bestResult().first);
  EXPECT_GE(allowed_difference.count(), actual_difference.count());
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

TEST_F(OneMinuteChangeTest, WithoutAnyResultsGetLastResultShouldThrowNoResults)
{
  EXPECT_THROW(omc.lastResult(), OneMinuteChange::NoResultsError);
}

TEST_F(OneMinuteChangeTest, GetLastResultShouldReturnLastResult)
{
  const int lowRes = 10;
  const int bestRes = 42;
  omc.addResult(bestRes);
  omc.addResult(lowRes);

  EXPECT_EQ(lowRes, omc.lastResult().first);
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
  auto secs = std::chrono::duration_cast < std::chrono::seconds > (now.time_since_epoch());

  std::string resultString = omc.getFirstChord() + "\n" +
      omc.getSecondChord() + "\n" +
      std::to_string(resSize) + "\n" +
      std::to_string(firstRes) + " " + std::to_string(secs.count()) + "\n" +
      std::to_string(secondRes) + " " + std::to_string(secs.count()) + "\n" +
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
  std::vector<int> results {firstRes, secondRes, bestRes, fourthRes};
  const std::string chordA = "A";
  const std::string chordB = "B";

  auto now = std::chrono::system_clock::now();
  auto secs = std::chrono::duration_cast < std::chrono::seconds > (now.time_since_epoch());

  std::stringstream ss;
  ss << chordA << "\n";
  ss << chordB << "\n";
  ss << results.size() << "\n";
  ss << firstRes << " 0\n";
  ss << secondRes << " 0\n";
  ss << bestRes << " " << secs.count() << "\n";
  ss << fourthRes << " " << secs.count() + 1 << "\n";

  OneMinuteChange omc2 {ss};

  EXPECT_EQ(chordA, omc2.getFirstChord());
  EXPECT_EQ(chordB, omc2.getSecondChord());
  OneMinuteChange::Results results_got = omc2.getResults();
  auto it = results_got.begin();
  for (auto res : results_got)
  {
    EXPECT_EQ(res, *it++);
  }

  std::chrono::seconds allowed_difference {0};
  auto actual_best_difference = std::chrono::duration_cast < std::chrono::seconds > (now - omc2.bestResult().second);
  auto actual_last_difference = std::chrono::duration_cast < std::chrono::seconds > ((now + std::chrono::seconds {1}) - omc2.lastResult().second);

  EXPECT_EQ(bestRes, omc2.bestResult().first);
  EXPECT_GE(allowed_difference.count(), actual_best_difference.count());
  EXPECT_EQ(fourthRes, omc2.lastResult().first);
  EXPECT_GE(allowed_difference.count(), actual_last_difference.count());
}
