#include "../inc/OneMinuteChangesSet.hpp"

#include <algorithm>

using OneMinuteChanges::OneMinuteChangesSet;

OneMinuteChangesSet::SetType OneMinuteChangesSet::changes;

OneMinuteChangesSet::OneMinuteChangesSet()
{
}

OneMinuteChangesSet::OneMinuteChangesSet(std::istream &in)
{
  SetType::size_type size;
  in >> size;
  for (SetType::size_type i = 0; i < size; ++i)
  {
    Element omc(new OneMinuteChanges::OneMinuteChange(in));
    changes.insert(omc);
  }
}

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

std::string OneMinuteChangesSet::print() const
{
  std::string ret = std::to_string(changes.size()) + "\n";
  for (auto c: changes)
  {
    ret += c->print();
  }
  return ret;
}