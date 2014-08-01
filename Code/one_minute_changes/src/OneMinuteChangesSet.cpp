#include "../inc/OneMinuteChangesSet.hpp"

using OneMinuteChanges::OneMinuteChangesSet;

OneMinuteChangesSet::SetType OneMinuteChangesSet::changes;

void OneMinuteChangesSet::clear() noexcept
{
}

OneMinuteChangesSet::size_type OneMinuteChangesSet::size() const noexcept
{
  return changes.size();
}

void OneMinuteChangesSet::add(Element element)
{
  changes.insert(element);
}