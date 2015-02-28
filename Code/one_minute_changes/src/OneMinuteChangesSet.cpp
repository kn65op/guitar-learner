#include "../inc/OneMinuteChangesSet.hpp"

#include <algorithm>
#include <tuple>

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

OneMinuteChangesSet::Element OneMinuteChangesSet::findWorstChord() const
{
  if (!size())
  {
    throw Exceptions::NoElements();
  }

  return *std::min_element(changes.begin(), changes.end(), [](const Element &first, const Element & second)
  {
    return first->bestResult() < second->bestResult();
  });
}

OneMinuteChangesSet::Element OneMinuteChangesSet::findLastWorstChord() const
{
  if (!size())
  {
    throw Exceptions::NoElements();
  }

  return *std::min_element(changes.begin(), changes.end(), [](const Element &first, const Element & second)
  {
    return first->lastResult() < second->lastResult();
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