#include "../inc/OneMinuteChangesSet.hpp"

#include <algorithm>

using OneMinuteChanges::OneMinuteChangesSet;

OneMinuteChangesSet::SetType OneMinuteChangesSet::changes;

void OneMinuteChangesSet::clear() noexcept
{
  changes.clear();
}

OneMinuteChangesSet::size_type OneMinuteChangesSet::size() const noexcept
{
  return changes.size();
}

void OneMinuteChangesSet::add(Element element)
{
  changes.insert(element);
}

OneMinuteChangesSet::Element OneMinuteChangesSet::findWorstChord() const        
{
  if (!size())
  {
    throw Exceptions::NoElements();
  }
  
  return *std::min_element(changes.begin(), changes.end(), [](const Element &first, const Element &second) -> bool
  {
    return first->bestResult() < second->bestResult();
  }
  );
}

OneMinuteChangesSet::Element OneMinuteChangesSet::findLastWorstChord() const        
{
  if (!size())
  {
    throw Exceptions::NoElements();
  }
  
  return *std::min_element(changes.begin(), changes.end(), [](const Element &first, const Element &second) -> bool
  {
    return first->lastResult() < second->lastResult();
  }
  );
}
