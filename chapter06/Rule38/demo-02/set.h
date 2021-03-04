#ifndef SET_H_
#define SET_H_

#include <algorithm>
#include <list>

namespace ec {

template<class T>
class Set {
 public:
   Set() {}

 public:
   bool Member(const T& item) const;
   void Insert(const T& item);
   void Remove(const T& item);
   std::size_t Size() const;

 private:
  std::list<T> l_;
};

template<class T>
bool Set<T>::Member(const T& item) const {
  return std::find(l_.begin(), l_.end(), item) != l_.end();
}

template<class T>
void Set<T>::Insert(const T& item) {
  l_.insert(l_.begin(), item);
}

template<class T>
void Set<T>::Remove(const T& item) {
  l_.remove(item);
}

template<class T>
std::size_t Set<T>::Size() const {
  return l_.size();
}

} // namespace ec

#endif // SET_H_
