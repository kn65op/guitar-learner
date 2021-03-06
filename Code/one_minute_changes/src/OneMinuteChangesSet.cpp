#include "OneMinuteChangesSet.hpp"

#include <algorithm>
#include <tuple>
#include <TLogger.h>

using OneMinuteChanges::OneMinuteChangesSet;

OneMinuteChangesSet::ContainerType OneMinuteChangesSet::changes;

OneMinuteChangesSet::OneMinuteChangesSet() { }

OneMinuteChangesSet::OneMinuteChangesSet(std::istream &in)
{
  ContainerType::size_type size;
  in >> size;
  for (ContainerType::size_type i = 0; i < size; ++i)
  {
    Element omc(new OneMinuteChanges::OneMinuteChange(in));
    changes.push_back(omc);
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
  changes.push_back(element);
}

OneMinuteChangesSet::Element OneMinuteChangesSet::findFirstWorstChangeByBestResult() const
{
  if (changes.empty())
  {
    LOG << "Changes are empty";
    throw Exceptions::NoElements();
  }

  const auto changesWithResults = getAllChangesWithResults();

  auto worstChange = std::min_element(changesWithResults.begin(), changesWithResults.end(), [](const Element &first, const Element & second)
  {
    return first->bestResult() < second->bestResult();
  });
  if (worstChange != changesWithResults.end())
  {
    return *worstChange;
  }
  throw Exceptions::NoValidElements();
}

OneMinuteChangesSet::ContainerType OneMinuteChangesSet::findWorstChangesByBestResult() const
{
  auto worstValue = findFirstWorstChangeByBestResult()->bestResult().first;
  return getAllChangesWitRule([=](const Element &element)
  {
    try
    {
      return element->bestResult().first == worstValue;
    }
    catch (const OneMinuteChanges::IOneMinuteChange::NoResultsError &)
    {
      return false;
    }
  });
}

OneMinuteChangesSet::Element OneMinuteChangesSet::findFirstWorstChangeByLastResult() const
{
  if (changes.empty())
  {
    LOG << "Changes are empty";
    throw Exceptions::NoElements();
  }

  const auto changesWithResults = getAllChangesWithResults();

  auto worstChange = std::min_element(changesWithResults.begin(), changesWithResults.end(), [](const Element &first, const Element & second)
  {
    return first->lastResult() < second->lastResult();
  });
  if (worstChange != changesWithResults.end())
  {
    return *worstChange;
  }
  throw Exceptions::NoValidElements();
}

OneMinuteChangesSet::ContainerType OneMinuteChangesSet::findWorstChangesByLastResult() const
{
  auto worstValue = findFirstWorstChangeByLastResult()->lastResult().first;
  return getAllChangesWitRule([=](const Element &element)
  {
    try
    {
      return element->lastResult().first == worstValue;
    }
    catch (const OneMinuteChanges::IOneMinuteChange::NoResultsError &)
    {
      return false;
    }
  });
}

std::string OneMinuteChangesSet::print() const
{
  std::string ret = std::to_string(changes.size()) + "\n";
  for (auto c : changes)
  {
    ret += c->print();
  }
  return ret;
}

OneMinuteChangesSet::Element OneMinuteChangesSet::getChange(const Guitar::Chord::ChordNameType &first_chord,
                                                            const Guitar::Chord::ChordNameType &second_chord) const
{
  Guitar::Chord::ChordNameType chord_min, chord_max;
  std::tie(chord_min, chord_max) = std::minmax(first_chord, second_chord);
  auto change = std::find_if(changes.begin(), changes.end(), [&chord_min, &chord_max] (const Element & element)
  {
     return chord_min == element->getFirstChord() && chord_max == element->getSecondChord();
  });
  if (change == changes.end())
  {
    throw Exceptions::NoChangeFound();
  }
  return *change;
}

void OneMinuteChangesSet::removeAllContainingChord(const Guitar::Chord::ChordNameType &chord)
{
  changes.erase(std::remove_if(changes.begin(), changes.end(), [&chord](const Element & element)
  {
    return element->getFirstChord() == chord || element->getSecondChord() == chord;
  }) , changes.end());
}

OneMinuteChangesSet::iterator_type OneMinuteChangesSet::begin() const
{
  return changes.begin();
}

OneMinuteChangesSet::iterator_type OneMinuteChangesSet::end() const
{
  return changes.end();
}

OneMinuteChangesSet::ContainerType OneMinuteChangesSet::getAllChangesWithResults() const
{
  return getAllChangesWitRule([](const auto &change)
  {
    return change->hasResults();
  });
}

OneMinuteChangesSet::ContainerType OneMinuteChangesSet::findChangesWithoutResults() const
{
  ContainerType changesWithoutResults;
  std::copy_if(changes.begin(), changes.end(), std::back_inserter(changesWithoutResults), [](const auto &change)
  {
    return !change->hasResults();
  });
  return changesWithoutResults;
}
