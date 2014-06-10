#include "../inc/OneMinuteChange.hpp"
#include <algorithm>

using OneMinuteChanges::OneMinuteChange;

OneMinuteChange::OneMinuteChange(const std::string &chordA, const std::string &chordB) :
  first(chordA),
  second(chordB)
{
  
}

bool OneMinuteChange::operator==(const OneMinuteChange &other) const
{
  return (first == other.first && second == other.second)
         || (first == other.second && second == other.first);
}

bool OneMinuteChanges::operator!=(const OneMinuteChange &first, const OneMinuteChange &other)
{
  return !(first == other);
}

void OneMinuteChange::addResult(int result)
{
  results.push_back(result);
}

int OneMinuteChange::bestResult() const
{
  auto max = std::max_element(results.begin(), results.end());
  if (max != results.end())
  {
    return *max;
  }
  return 0;
}

const OneMinuteChange::Results& OneMinuteChange::getResults() const
{
  return results;
}