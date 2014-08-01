#ifndef ONEMINUTECHANGESSET_H
#define ONEMINUTECHANGESSET_H

#include "OneMinuteChange.hpp"
#include <set>

namespace OneMinuteChanges
{
  
class OneMinuteChangesSet
{
public:
  typedef std::set<OneMinuteChange> SetType;
  void clear();
private:
  static SetType changes;
};

}

#endif // ONEMINUTECHANGESSET_H
