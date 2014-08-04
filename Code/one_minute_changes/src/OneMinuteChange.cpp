#include "../inc/OneMinuteChange.hpp"
#include <algorithm>

using OneMinuteChanges::OneMinuteChange;

OneMinuteChange::OneMinuteChange(const std::string &chordA, const std::string &chordB) :
  first(std::min(chordA, chordB)),
  second(std::max(chordA, chordB)),
  results()
{
}

bool OneMinuteChange::operator==(const OneMinuteChange &other) const
{
  return first == other.first && second == other.second;
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

int OneMinuteChange::lastResult() const
{
  return results.back();
}               

std::string OneMinuteChange::getFirstChord() const
{
  return first;
}

std::string OneMinuteChange::getSecondChord() const
{
  return second;
}

std::ostream& OneMinuteChanges::operator<<(std::ostream &os, const OneMinuteChange& omc)
{
  os << omc.getFirstChord() << "\n";
  os << omc.getSecondChord() << "\n";
  for (auto res : omc.getResults())
  {
    os << res << "\n";
  }
  return os;
}