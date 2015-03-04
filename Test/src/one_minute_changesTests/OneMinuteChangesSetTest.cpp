#include "one_minute_changes/inc/OneMinuteChangesSet.hpp"
#include <gtest/gtest.h>
#include "OneMinuteChangeMock.hpp"

using namespace ::testing;
using OneMinuteChanges::OneMinuteChangesSet;
using OneMinuteChanges::ut::OneMinuteChangeMock;

struct OneMinuteChangesSetTest : public Test
{

  OneMinuteChangesSetTest() :
      omcs() {
 }

  OneMinuteChangesSet omcs;

  virtual void TearDown()
  {
    omcs.clear();
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

TEST_F(OneMinuteChangesSetTest, findWorstChordShouldThowNoElementsExceptionWhenNoElementsInSet)
{
  EXPECT_THROW(omcs.findFirstWorstChordByBestResult(), OneMinuteChanges::Exceptions::NoElements);
}

TEST_F(OneMinuteChangesSetTest, FindWorstChordShouldReturnElementWithLowestMaxValueForOneChange)
{
  OneMinuteChangeMock *omcMockLowest = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omcLowest{omcMockLowest};
  OneMinuteChangeMock *omcMockLowest2 = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omcLowest2{omcMockLowest2};

  omcs.add(omcLowest);
  omcs.add(omcLowest2);
  int min_result = 1;

  EXPECT_CALL(*omcMockLowest, bestResult()).WillRepeatedly(Return(min_result));
  EXPECT_CALL(*omcMockLowest2, bestResult()).WillRepeatedly(Return(min_result));

  EXPECT_EQ(min_result, omcs.findFirstWorstChordByBestResult()->bestResult());
  EXPECT_EQ(omcLowest, omcs.findFirstWorstChordByBestResult());
}

TEST_F(OneMinuteChangesSetTest, FindWorstChordShouldReturnElementWithLowestMaxValue)
{
  OneMinuteChangeMock *omcMockLowest = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omcLowest{omcMockLowest};
  OneMinuteChangeMock *omcMock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc{omcMock};

  omcs.add(omcLowest);
  omcs.add(omc);
  int min_result = 1;

  EXPECT_CALL(*omcMockLowest, bestResult()).WillRepeatedly(Return(min_result));
  EXPECT_CALL(*omcMock, bestResult()).WillRepeatedly(Return(min_result + 1));

  EXPECT_EQ(min_result, omcs.findFirstWorstChordByBestResult()->bestResult());
}

TEST_F(OneMinuteChangesSetTest, WhenChangeWasAddedShouldBePosibilityToAddNewResult)
{
  OneMinuteChangeMock *omcMockLowest = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omcLowest{omcMockLowest};
  OneMinuteChangeMock *omcMock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc{omcMock};

  omcs.add(omcLowest);
  omcs.add(omc);
  int min_result = 1;

  EXPECT_CALL(*omcMockLowest, bestResult()).WillRepeatedly(Return(min_result));
  EXPECT_CALL(*omcMock, bestResult()).WillRepeatedly(Return(min_result + 1));

  EXPECT_EQ(min_result, omcs.findFirstWorstChordByBestResult()->bestResult());

  EXPECT_CALL(*omcMockLowest, getFirstChord()).WillRepeatedly(Return("A"));
  EXPECT_CALL(*omcMockLowest, getSecondChord()).WillRepeatedly(Return("B"));
  EXPECT_CALL(*omcMock, getFirstChord()).WillRepeatedly(Return("A"));
  EXPECT_CALL(*omcMock, getSecondChord()).WillRepeatedly(Return("C"));
  EXPECT_CALL(*omcMockLowest, addResult(min_result + 2)).Times(1);
  omcs.getChange("A", "B")->addResult(min_result + 2);

  EXPECT_CALL(*omcMockLowest, bestResult()).WillRepeatedly(Return(min_result + 2));
  EXPECT_CALL(*omcMock, bestResult()).WillRepeatedly(Return(min_result + 1));
  EXPECT_EQ(min_result + 1, omcs.findFirstWorstChordByBestResult()->bestResult());
}

TEST_F(OneMinuteChangesSetTest, WhenChangeWasAddedShouldBePosibilityToAddNewResultWithInvertedChords)
{
  OneMinuteChangeMock *omcMockLowest = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omcLowest{omcMockLowest};
  OneMinuteChangeMock *omcMock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc{omcMock};

  omcs.add(omcLowest);
  omcs.add(omc);
  int min_result = 1;

  EXPECT_CALL(*omcMockLowest, bestResult()).WillRepeatedly(Return(min_result));
  EXPECT_CALL(*omcMock, bestResult()).WillRepeatedly(Return(min_result + 1));

  EXPECT_EQ(min_result, omcs.findFirstWorstChordByBestResult()->bestResult());

  EXPECT_CALL(*omcMockLowest, getFirstChord()).WillRepeatedly(Return("A"));
  EXPECT_CALL(*omcMockLowest, getSecondChord()).WillRepeatedly(Return("B"));
  EXPECT_CALL(*omcMock, getFirstChord()).WillRepeatedly(Return("A"));
  EXPECT_CALL(*omcMock, getSecondChord()).WillRepeatedly(Return("C"));
  EXPECT_CALL(*omcMockLowest, addResult(min_result + 2)).Times(1);
  omcs.getChange("B", "A")->addResult(min_result + 2);

  EXPECT_CALL(*omcMockLowest, bestResult()).WillRepeatedly(Return(min_result + 2));
  EXPECT_CALL(*omcMock, bestResult()).WillRepeatedly(Return(min_result + 1));
  EXPECT_EQ(min_result + 1, omcs.findFirstWorstChordByBestResult()->bestResult());
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

TEST_F(OneMinuteChangesSetTest, findLastWorstChordShouldThowNoElementsExceptionWhenNoElementsInSet)
{
  EXPECT_THROW(omcs.findFirstWorstChordByLastResult(), OneMinuteChanges::Exceptions::NoElements);
}

TEST_F(OneMinuteChangesSetTest, FindLastWorstChordShouldReturnElementWithLowestMaxValueForOneChange)
{
  OneMinuteChangeMock *omcMockLowest = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omcLowest{omcMockLowest};

  omcs.add(omcLowest);
  int min_result = 1;

  EXPECT_CALL(*omcMockLowest, lastResult()).WillRepeatedly(Return(min_result));

  EXPECT_EQ(min_result, omcs.findFirstWorstChordByLastResult()->lastResult());
}

TEST_F(OneMinuteChangesSetTest, FindLastWorstChordShouldReturnElementWithLowestMaxValue)
{
  OneMinuteChangeMock *omcMockLowest = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omcLowest{omcMockLowest};
  OneMinuteChangeMock *omcMock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc{omcMock};

  omcs.add(omcLowest);
  omcs.add(omc);
  int min_result = 1;

  EXPECT_CALL(*omcMockLowest, lastResult()).WillRepeatedly(Return(min_result));
  EXPECT_CALL(*omcMock, lastResult()).WillRepeatedly(Return(min_result + 1));

  EXPECT_EQ(min_result, omcs.findFirstWorstChordByLastResult()->lastResult());
}

TEST_F(OneMinuteChangesSetTest, PrintShouldPrintAllChanges)
{
  OneMinuteChangeMock *omc1Mock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc1{omc1Mock};
  OneMinuteChangeMock *omc2Mock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc2{omc2Mock};

  omcs.add(omc1);
  omcs.add(omc2);

  const std::string omcsHeaeder = std::to_string(omcs.size()) + "\n";
  const std::string omc1String = "omc1string";
  const std::string omc2String = "omc2string";

  EXPECT_CALL(*omc1Mock, print()).WillOnce(Return(omc1String));
  EXPECT_CALL(*omc2Mock, print()).WillOnce(Return(omc2String));

  EXPECT_EQ(omcsHeaeder + omc1String + omc2String, omcs.print());
}

TEST_F(OneMinuteChangesSetTest, ChangesShoulBeRead)
{
  std::string input = "2\n"
      "A\nD\n"
      "2\n1\n2\n"
      "A\nE\n"
      "3\n5\n2\n1\n";
  std::stringstream ss;
  ss << input;
  OneMinuteChangesSet omcs(ss);
  EXPECT_EQ(omcs.findFirstWorstChordByBestResult()->bestResult(), 2);
  EXPECT_EQ(omcs.findFirstWorstChordByLastResult()->lastResult(), 1);
}

TEST_F(OneMinuteChangesSetTest, RemoveAllContainingChordShouldRemoveAllAndOnlyChangesContainingChord)
{
  OneMinuteChangeMock *omc1Mock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc1{omc1Mock};
  OneMinuteChangeMock *omc2Mock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc2{omc2Mock};
  OneMinuteChangeMock *omc3Mock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc3{omc3Mock};

  EXPECT_CALL(*omc1Mock, getFirstChord()).WillRepeatedly(Return("A"));
  EXPECT_CALL(*omc1Mock, getSecondChord()).WillRepeatedly(Return("B"));
  EXPECT_CALL(*omc2Mock, getFirstChord()).WillRepeatedly(Return("B"));
  EXPECT_CALL(*omc2Mock, getSecondChord()).WillRepeatedly(Return("C"));
  EXPECT_CALL(*omc3Mock, getFirstChord()).WillRepeatedly(Return("C"));
  EXPECT_CALL(*omc3Mock, getSecondChord()).WillRepeatedly(Return("A"));
  EXPECT_CALL(*omc1Mock, lastResult()).WillRepeatedly(Return(1));
  EXPECT_CALL(*omc2Mock, lastResult()).WillRepeatedly(Return(2));
  EXPECT_CALL(*omc3Mock, lastResult()).WillRepeatedly(Return(3));

  OneMinuteChangesSet omcs;
  omcs.add(omc1);
  omcs.add(omc2);
  omcs.add(omc3);

  ASSERT_EQ(3, omcs.size());

  omcs.removeAllContainingChord("A");
  EXPECT_EQ(1, omcs.size());

  EXPECT_EQ(2, omcs.findFirstWorstChordByLastResult()->lastResult());
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