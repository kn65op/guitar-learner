#include "one_minute_changes/inc/OneMinuteChangesSet.hpp"
#include <gtest/gtest.h>
#include "OneMinuteChangeMock.hpp"

using namespace ::testing;
using OneMinuteChanges::OneMinuteChangesSet;
using OneMinuteChanges::ut::OneMinuteChangeMock;

struct OneMinuteChangesSetTest : public Test
{
  OneMinuteChangesSetTest() :
    omcs()
  {
    
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
  EXPECT_THROW(omcs.findWorstChord(), OneMinuteChanges::Exceptions::NoElements);
}

TEST_F(OneMinuteChangesSetTest, FindWorstChordShouldReturnElementWithLowestMaxValueForOneChange)
{
  OneMinuteChangeMock *omcMockLowest = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omcLowest{omcMockLowest};
  
  omcs.add(omcLowest);
  int min_result = 1;
  
  EXPECT_CALL(*omcMockLowest, bestResult()).WillRepeatedly(Return(min_result));
  
  EXPECT_EQ(min_result, omcs.findWorstChord()->bestResult());
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
  EXPECT_CALL(*omcMock, bestResult()).WillRepeatedly(Return(min_result+1));
  
  EXPECT_EQ(min_result, omcs.findWorstChord()->bestResult());
}

TEST_F(OneMinuteChangesSetTest, findLastWorstChordShouldThowNoElementsExceptionWhenNoElementsInSet)
{
  EXPECT_THROW(omcs.findLastWorstChord(), OneMinuteChanges::Exceptions::NoElements);
}

TEST_F(OneMinuteChangesSetTest, FindLastWorstChordShouldReturnElementWithLowestMaxValueForOneChange)
{
  OneMinuteChangeMock *omcMockLowest = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omcLowest{omcMockLowest};
  
  omcs.add(omcLowest);
  int min_result = 1;
  
  EXPECT_CALL(*omcMockLowest, lastResult()).WillRepeatedly(Return(min_result));
  
  EXPECT_EQ(min_result, omcs.findLastWorstChord()->lastResult());
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
  EXPECT_CALL(*omcMock, lastResult()).WillRepeatedly(Return(min_result+1));
  
  EXPECT_EQ(min_result, omcs.findLastWorstChord()->lastResult());
}

TEST_F(OneMinuteChangesSetTest, PrintShouldPrintAllChanges)
{
  OneMinuteChangeMock *omc1Mock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc1{omc1Mock};
  OneMinuteChangeMock *omc2Mock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc2{omc2Mock};
  
  omcs.add(omc1);
  omcs.add(omc2);
  
  const std::string omc1String = "omc1string";
  const std::string omc2String = "omc2string";
  
  EXPECT_CALL(*omc1Mock, print()).WillOnce(Return(omc1String));
  EXPECT_CALL(*omc2Mock, print()).WillOnce(Return(omc2String));
  
  EXPECT_EQ(omc1String + omc2String, omcs.print());
}