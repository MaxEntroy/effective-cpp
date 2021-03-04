#ifndef SET_H_
#define SET_H_

#include <algorithm>
#include <list>

namespace ec {

template<class T>
class Set : private std::list<T> {
 public:
  typedef std::list<T> Base;

  bool Member(const T& val) const;
  void Insert(const T& val);
  void Remove(const T& val);
  std::size_t Size() const;
};

template<class T>
bool Set<T>::Member(const T& val) const {
  return std::find(Base::begin(), Base::end(), val) != Base::end();
}

template<class T>
void Set<T>::Insert(const T& val) {
  Base::insert(Base::begin(), val);
}

template<class T>
void Set<T>::Remove(const T& val) {
  Base::remove(val);
}

template<class T>
std::size_t Set<T>::Size() const {
  return Base::size();
}

} // namespace ec

#endif // SET_H_
