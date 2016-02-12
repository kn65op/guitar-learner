#include "one_minute_changes/inc/OneMinuteChangesSet.hpp"
#include <gtest/gtest.h>
#include "OneMinuteChangeMock.hpp"

using namespace ::testing;
using OneMinuteChanges::OneMinuteChangesSet;
using OneMinuteChanges::ut::OneMinuteChangeMock;

struct OneMinuteChangesSetTest : public Test
{

  OneMinuteChangesSetTest() :
      omcs() { }

  OneMinuteChangesSet omcs;

  virtual void TearDown()
  {
    omcs.clear();
  }

  static OneMinuteChanges::IOneMinuteChange::DateType getNow()
  {
    return std::chrono::system_clock::now();
  }

  std::shared_ptr<OneMinuteChangeMock> addOmcToSetWithBestResult(OneMinuteChangeMock::ResultValue bestResult)
  {
    auto omc = std::make_shared<OneMinuteChangeMock>();
    omcs.add(omc);
    EXPECT_CALL(*omc, hasResults()).WillRepeatedly(Return(true));
    EXPECT_CALL(*omc, bestResult()).WillRepeatedly(Return(std::make_pair(bestResult, getNow())));
    return omc;
  }

  std::shared_ptr<OneMinuteChangeMock> addOmcToSetWithLastResult(OneMinuteChangeMock::ResultValue lastResult)
  {
    auto omc = std::make_shared<OneMinuteChangeMock>();
    omcs.add(omc);
    EXPECT_CALL(*omc, hasResults()).WillRepeatedly(Return(true));
    EXPECT_CALL(*omc, lastResult()).WillRepeatedly(Return(std::make_pair(lastResult, getNow())));
    return omc;
  }

  std::shared_ptr<OneMinuteChangeMock> addOmcToSetWithoutBestResult()
  {
    auto omc = std::make_shared<OneMinuteChangeMock>();
    omcs.add(omc);
    EXPECT_CALL(*omc, hasResults()).WillRepeatedly(Return(false));
    EXPECT_CALL(*omc, bestResult()).WillRepeatedly(Throw(OneMinuteChanges::IOneMinuteChange::NoResultsError{"no res"}));
    return omc;
  }

  std::shared_ptr<OneMinuteChangeMock> addOmcToSetWithoutLastResult()
  {
    auto omc = std::make_shared<OneMinuteChangeMock>();
    omcs.add(omc);
    EXPECT_CALL(*omc, hasResults()).WillRepeatedly(Return(false));
    EXPECT_CALL(*omc, lastResult()).WillRepeatedly(Throw(OneMinuteChanges::IOneMinuteChange::NoResultsError{"no res"}));
    return omc;
  }
};

TEST_F(OneMinuteChangesSetTest, ChangeCanBeAdded)
{
  OneMinuteChangeMock *omcMock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc{omcMock};
  ASSERT_EQ(0U, omcs.size());

  omcs.add(omc);

  EXPECT_EQ(1U, omcs.size());
}

TEST_F(OneMinuteChangesSetTest, AfterClearSizeShouldReturn0Elements)
{
  OneMinuteChangeMock *omcMock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc{omcMock};
  omcs.add(omc);
  ASSERT_NE(0U, omcs.size());

  omcs.clear();

  EXPECT_EQ(0U, omcs.size());
}

TEST_F(OneMinuteChangesSetTest, findWorstChangeShouldThowNoElementsExceptionWhenNoElementsInSet)
{
  EXPECT_THROW(omcs.findFirstWorstChangeByBestResult(), OneMinuteChanges::Exceptions::NoElements);
}

TEST_F(OneMinuteChangesSetTest, findWorstChangesShouldThowNoElementsExceptionWhenNoElementsInSet)
{
  EXPECT_THROW(omcs.findWorstChangesByBestResult(), OneMinuteChanges::Exceptions::NoElements);
}

TEST_F(OneMinuteChangesSetTest, FindWorstChangeShouldReturnElementWithLowestMaxValueForOneChange)
{
  int min_result = 1;
  auto omcMockLowest = addOmcToSetWithBestResult(min_result);
  auto omcMockLowest2 = addOmcToSetWithBestResult(min_result);

  EXPECT_EQ(min_result, omcs.findFirstWorstChangeByBestResult()->bestResult().first);
  EXPECT_EQ(omcMockLowest, omcs.findFirstWorstChangeByBestResult());
}

TEST_F(OneMinuteChangesSetTest, FindWorstChangesShouldReturnOneElementWhenThereIsOnlyOneChange)
{
  constexpr OneMinuteChangeMock::ResultValue bestResult{1};
  constexpr int numberOfWorstChanges = 1;
  auto omc = addOmcToSetWithBestResult(bestResult);

  const auto worstChanges = omcs.findWorstChangesByBestResult();
  EXPECT_EQ(numberOfWorstChanges, worstChanges.size());
  EXPECT_THAT(worstChanges, UnorderedElementsAre(omc));
}

TEST_F(OneMinuteChangesSetTest, FindWorstChangesShouldReturnTwoElementWhenThereIsTwoElementsWithTheSameValueAndOneBetter)
{
  constexpr OneMinuteChangeMock::ResultValue bestResultMax{3};
  constexpr OneMinuteChangeMock::ResultValue bestResultMin{1};
  constexpr int numberOfWorstChanges = 2;
  auto firstOmc = addOmcToSetWithBestResult(bestResultMin);
  addOmcToSetWithBestResult(bestResultMax);
  auto secondOmc = addOmcToSetWithBestResult(bestResultMin);

  const auto worstChanges = omcs.findWorstChangesByBestResult();
  EXPECT_EQ(numberOfWorstChanges, worstChanges.size());
  EXPECT_THAT(worstChanges, UnorderedElementsAre(firstOmc, secondOmc));
}

TEST_F(OneMinuteChangesSetTest, WhenNotAllResultsHasBestResultsShouldReturnWorstChangeWithResult)
{
  constexpr OneMinuteChangeMock::ResultValue bestResultMin{1};
  constexpr int numberOfWorstChanges = 1;
  auto firstOmc = addOmcToSetWithBestResult(bestResultMin);
  auto secondOmc = addOmcToSetWithoutBestResult();

  const auto worstChanges = omcs.findWorstChangesByBestResult();
  EXPECT_EQ(numberOfWorstChanges, worstChanges.size());
  EXPECT_THAT(worstChanges, UnorderedElementsAre(firstOmc));
}

TEST_F(OneMinuteChangesSetTest, FindLastWorstChangesShouldReturnOneElementWhenThereIsOnlyOneChange)
{
  constexpr OneMinuteChangeMock::ResultValue lastResult{1};
  constexpr int numberOfWorstChanges = 1;
  auto omc = addOmcToSetWithLastResult(lastResult);

  const auto worstChanges = omcs.findWorstChangesByLastResult();
  EXPECT_EQ(numberOfWorstChanges, worstChanges.size());
  EXPECT_THAT(worstChanges, UnorderedElementsAre(omc));
}

TEST_F(OneMinuteChangesSetTest, FindLastWorstChangesShouldReturnTwoElementWhenThereIsTwoElementsWithTheSameValueAndOneBetter)
{
  constexpr OneMinuteChangeMock::ResultValue lastResultMax{3};
  constexpr OneMinuteChangeMock::ResultValue lastResultMin{1};
  constexpr int numberOfWorstChanges = 2;
  auto firstOmc = addOmcToSetWithLastResult(lastResultMin);
  addOmcToSetWithLastResult(lastResultMax);
  auto secondOmc = addOmcToSetWithLastResult(lastResultMin);

  const auto worstChanges = omcs.findWorstChangesByLastResult();
  EXPECT_EQ(numberOfWorstChanges, worstChanges.size());
  EXPECT_THAT(worstChanges, UnorderedElementsAre(firstOmc, secondOmc));
}

TEST_F(OneMinuteChangesSetTest, WhenNotAllResultsHasResultsShouldReturnWorstLastChangeWithResult)
{
  constexpr OneMinuteChangeMock::ResultValue lastResultMin{1};
  constexpr int numberOfWorstChanges = 1;
  auto firstOmc = addOmcToSetWithLastResult(lastResultMin);
  auto secondOmc = addOmcToSetWithoutLastResult();

  const auto worstChanges = omcs.findWorstChangesByLastResult();
  EXPECT_EQ(numberOfWorstChanges, worstChanges.size());
  EXPECT_THAT(worstChanges, UnorderedElementsAre(firstOmc));
}

TEST_F(OneMinuteChangesSetTest, FindWorstChangeShouldReturnElementWithLowestMaxValue)
{
  int min_result = 1;
  int better_result = 2;
  auto omcMockLowest = addOmcToSetWithBestResult(min_result);
  auto omcMock = addOmcToSetWithBestResult(better_result);

  EXPECT_EQ(min_result, omcs.findFirstWorstChangeByBestResult()->bestResult().first);
}

TEST_F(OneMinuteChangesSetTest, WhenChangeWasAddedShouldBePosibilityToAddNewResult)
{
  int min_result = 1;
  int better_result = 2;
  auto omcMockLowest = addOmcToSetWithBestResult(min_result);
  auto omcMock = addOmcToSetWithBestResult(better_result);

  EXPECT_EQ(min_result, omcs.findFirstWorstChangeByBestResult()->bestResult().first);

  EXPECT_CALL(*omcMockLowest, getFirstChord()).WillRepeatedly(Return("A"));
  EXPECT_CALL(*omcMockLowest, getSecondChord()).WillRepeatedly(Return("B"));
  EXPECT_CALL(*omcMock, getFirstChord()).WillRepeatedly(Return("A"));
  EXPECT_CALL(*omcMock, getSecondChord()).WillRepeatedly(Return("C"));
  EXPECT_CALL(*omcMockLowest, addResult(min_result + 2)).Times(1);
  omcs.getChange("A", "B")->addResult(min_result + 2);

  EXPECT_CALL(*omcMockLowest, bestResult()).WillRepeatedly(Return(std::make_pair(min_result + 2, getNow())));
  EXPECT_CALL(*omcMock, bestResult()).WillRepeatedly(Return(std::make_pair(min_result + 1, getNow())));
  EXPECT_EQ(min_result + 1, omcs.findFirstWorstChangeByBestResult()->bestResult().first);
}

TEST_F(OneMinuteChangesSetTest, WhenChangeWasAddedShouldBePosibilityToAddNewResultWithInvertedChords)
{
  int min_result = 1;
  int better_result = 2;
  auto omcMockLowest = addOmcToSetWithBestResult(min_result);
  auto omcMock = addOmcToSetWithBestResult(better_result);

  EXPECT_EQ(min_result, omcs.findFirstWorstChangeByBestResult()->bestResult().first);

  EXPECT_CALL(*omcMockLowest, getFirstChord()).WillRepeatedly(Return("A"));
  EXPECT_CALL(*omcMockLowest, getSecondChord()).WillRepeatedly(Return("B"));
  EXPECT_CALL(*omcMock, getFirstChord()).WillRepeatedly(Return("A"));
  EXPECT_CALL(*omcMock, getSecondChord()).WillRepeatedly(Return("C"));
  EXPECT_CALL(*omcMockLowest, addResult(min_result + 2)).Times(1);
  omcs.getChange("B", "A")->addResult(min_result + 2);

  EXPECT_CALL(*omcMockLowest, bestResult()).WillRepeatedly(Return(std::make_pair(min_result + 2, getNow())));
  EXPECT_CALL(*omcMock, bestResult()).WillRepeatedly(Return(std::make_pair(min_result + 1, getNow())));
  EXPECT_EQ(min_result + 1, omcs.findFirstWorstChangeByBestResult()->bestResult().first);
}

TEST_F(OneMinuteChangesSetTest, GetChangeShouldThrowNoChangeFoundWhenSearchingForNotPresentChange)
{
  EXPECT_THROW(omcs.getChange("A", "B"), OneMinuteChanges::Exceptions::NoChangeFound);
}

TEST_F(OneMinuteChangesSetTest, GetChangeShouldThrowNoChangeFoundWhenSearchingForNotPresentChangeAndOtherChanges)
{
  OneMinuteChangeMock *omcMockLowest = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omcLowest{omcMockLowest};

  omcs.add(omcLowest);
  EXPECT_CALL(*omcMockLowest, getFirstChord()).WillRepeatedly(Return("C"));
  EXPECT_CALL(*omcMockLowest, getSecondChord()).WillRepeatedly(Return("B"));
  EXPECT_THROW(omcs.getChange("A", "B"), OneMinuteChanges::Exceptions::NoChangeFound);
}

TEST_F(OneMinuteChangesSetTest, findLastWorstChangeShouldThowNoElementsExceptionWhenNoElementsInSet)
{
  EXPECT_THROW(omcs.findFirstWorstChangeByLastResult(), OneMinuteChanges::Exceptions::NoElements);
}

TEST_F(OneMinuteChangesSetTest, findWorstChangesByLastResultShouldThowNoElementsExceptionWhenNoElementsInSet)
{
  EXPECT_THROW(omcs.findWorstChangesByLastResult(), OneMinuteChanges::Exceptions::NoElements);
}

TEST_F(OneMinuteChangesSetTest, FindLastWorstChangeShouldReturnElementWithLowestMaxValueForOneChange)
{
  int min_result = 1;
  auto omcMockLowest = addOmcToSetWithLastResult(min_result);

  EXPECT_EQ(min_result, omcs.findFirstWorstChangeByLastResult()->lastResult().first);
}

TEST_F(OneMinuteChangesSetTest, FindLastWorstChangeShouldReturnElementWithLowestMaxValue)
{
  int min_result = 1;
  int betterResult = 2;
  auto omcMockLowest = addOmcToSetWithLastResult(min_result);
  auto omcMock= addOmcToSetWithLastResult(betterResult);

  EXPECT_EQ(min_result, omcs.findFirstWorstChangeByLastResult()->lastResult().first);
}

TEST_F(OneMinuteChangesSetTest, PrintShouldPrintAllChanges)
{
  auto omc1 = std::make_shared<OneMinuteChangeMock>();
  auto omc2 = std::make_shared<OneMinuteChangeMock>();

  omcs.add(omc1);
  omcs.add(omc2);

  const std::string omcsHeaeder = std::to_string(omcs.size()) + "\n";
  const std::string omc1String = "omc1string";
  const std::string omc2String = "omc2string";

  EXPECT_CALL(*omc1, print()).WillOnce(Return(omc1String));
  EXPECT_CALL(*omc2, print()).WillOnce(Return(omc2String));

  EXPECT_EQ(omcsHeaeder + omc1String + omc2String, omcs.print());
}

TEST_F(OneMinuteChangesSetTest, ChangesShoulBeRead)
{
  std::string input = "2\n"
      "A\nD\n"
      "2\n1 1\n2 2\n"
      "A\nE\n"
      "3\n5 1\n2 2\n1 3\n";
  std::stringstream ss;
  ss << input;
  OneMinuteChangesSet omcs(ss);
  EXPECT_EQ(omcs.findFirstWorstChangeByBestResult()->bestResult().first, 2);
  EXPECT_EQ(omcs.findFirstWorstChangeByLastResult()->lastResult().first, 1);
}

TEST_F(OneMinuteChangesSetTest, RemoveAllContainingChordShouldRemoveAllAndOnlyChangesContainingChord)
{
  int resultOne{1};
  int resultTwo{2};
  int resultThree{3};
  auto omc1Mock = addOmcToSetWithLastResult(resultOne);
  auto omc2Mock = addOmcToSetWithLastResult(resultTwo);
  auto omc3Mock = addOmcToSetWithLastResult(resultThree);

  EXPECT_CALL(*omc1Mock, getFirstChord()).WillRepeatedly(Return("A"));
  EXPECT_CALL(*omc1Mock, getSecondChord()).WillRepeatedly(Return("B"));
  EXPECT_CALL(*omc2Mock, getFirstChord()).WillRepeatedly(Return("B"));
  EXPECT_CALL(*omc2Mock, getSecondChord()).WillRepeatedly(Return("C"));
  EXPECT_CALL(*omc3Mock, getFirstChord()).WillRepeatedly(Return("C"));
  EXPECT_CALL(*omc3Mock, getSecondChord()).WillRepeatedly(Return("A"));

  OneMinuteChangesSet omcs;

  ASSERT_EQ(3U, omcs.size());

  omcs.removeAllContainingChord("A");
  EXPECT_EQ(1U, omcs.size());

  EXPECT_EQ(2, omcs.findFirstWorstChangeByLastResult()->lastResult().first);
}

TEST_F(OneMinuteChangesSetTest, BeginAndEndShouldBeValid)
{
  OneMinuteChangeMock *omc1Mock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc1{omc1Mock};

  OneMinuteChangesSet omcs;
  EXPECT_EQ(omcs.end(), omcs.begin());

  omcs.add(omc1);
  EXPECT_NE(omcs.end(), omcs.begin());
}

TEST_F(OneMinuteChangesSetTest, ShouldReturnEmptyWorstResultsWhenThereIsNoResultForEachChange)
{
  auto omc = addOmcToSetWithoutBestResult();

  EXPECT_THROW(omcs.findWorstChangesByBestResult(), OneMinuteChanges::Exceptions::NoValidElements);
}

TEST_F(OneMinuteChangesSetTest, ShouldReturnEmptyLastWorstResultsWhenThereIsNoResultForEachChange)
{
  auto omc = addOmcToSetWithoutLastResult();

  EXPECT_THROW(omcs.findWorstChangesByLastResult(), OneMinuteChanges::Exceptions::NoValidElements);
}