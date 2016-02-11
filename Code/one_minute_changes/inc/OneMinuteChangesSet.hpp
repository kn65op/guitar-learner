#pragma once

#include "OneMinuteChange.hpp"
#include <set>
#include <memory>
#include <istream>
#include <algorithm>

namespace OneMinuteChanges
{

namespace Exceptions
{

struct NoElements
{
};

struct NoChangeFound
{
};

}

class OneMinuteChangesSet
{
public:
  typedef std::shared_ptr<IOneMinuteChange> Element;
  typedef std::vector<Element> ContainerType;
  typedef ContainerType::iterator iterator_type;
  typedef ContainerType::size_type size_type;

  OneMinuteChangesSet();
  OneMinuteChangesSet(std::istream & in);

  void clear() noexcept;
  void add(Element omc);
  void removeAllContainingChord(const Guitar::Chord::ChordNameType &chord);
  size_type size() const noexcept;

  ContainerType findWorstChangesByBestResult() const;
  ContainerType findWorstChangesByLastResult() const;
  Element findFirstWorstChangeByBestResult() const;
  Element findFirstWorstChangeByLastResult() const;
  Element getChange(const Guitar::Chord::ChordNameType &first_chord,
                    const Guitar::Chord::ChordNameType &second_chord) const;
  std::string print() const;
  iterator_type begin() const;
  iterator_type end() const;

private:
  typedef ContainerType::iterator SetIterator;
  static ContainerType changes;

  template <typename Rule> ContainerType getAllChangesWitRule(const Rule& rule) const
  {
    ContainerType changesFiltered;
    std::copy_if(changes.begin(), changes.end(), std::back_inserter(changesFiltered), [=](const Element &element)
    {
      return rule(element);
    });
    return changesFiltered;
  }
};

}