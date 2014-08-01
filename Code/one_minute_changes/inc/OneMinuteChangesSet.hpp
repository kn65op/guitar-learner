#ifndef ONEMINUTECHANGESSET_H
#define ONEMINUTECHANGESSET_H

#include "OneMinuteChange.hpp"
#include <set>
#include <memory>

namespace OneMinuteChanges
{
  
class OneMinuteChangesSet
{
public:
  typedef std::shared_ptr<IOneMinuteChange> Element;
  typedef std::set<Element> SetType;
  typedef SetType::size_type size_type;
  void clear() noexcept;
  void add(Element omcMock);
  size_type size() const noexcept;
  
private:
  static SetType changes;
};

}

#endif // ONEMINUTECHANGESSET_H
