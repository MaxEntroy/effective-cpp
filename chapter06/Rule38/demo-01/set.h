#ifndef SET_H_
#define SET_H_

#include <algorithm>
#include <list>

namespace ec {

template<class T>
class Set : public std::list<T> {
 public:
  typedef std::list<T> Base;

  bool Member(const T& item) const;
  void Insert(const T& item);
  void Remove(const T& item);
  std::size_t Size() const;
};

template<class T>
bool Set<T>::Member(const T& item) const {
  return std::find(Base::begin(), Base::end(), item) != Base::end();
}

template<class T>
void Set<T>::Insert(const T& item) {
  Base::insert(Base::begin(), item);
}

template<class T>
void Set<T>::Remove(const T& item) {
  Base::remove(item);
}

template<class T>
std::size_t Set<T>::Size() const {
  return Base::size();
}

} // namespace ec

#endif // SET_H_
