# plasma-effect/measurement

C++のコード片の経過時間をgtestっぽく計りたいというライブラリです。

## 目標

こんな感じで書きたい。

```cpp
#include "measurement.hpp"

MEASURE(Vector, Sum) {
  std::vector<int> vec(100);
  std::iota(vec.begin(), vec.end(), 0);
  int sum = 0;
  Start();
  for(auto v: vec) {
    sum += v;
  }
  Stop();
  DUMMY(sum);
}
```

```cpp
#include "measurement.hpp"

class VectorMeasure: public ::measurement::Measure {
protected:
  std::vector<int> vec;
  void Save(std::ostream& ost) override {
    ost << vec.size() << std::endl;
    for(auto v: vec) {
      ost << v << std::endl;
    }
  }
  void Load(std::istream& ist) {
    int N;
    ist >> N;
    vec.resize(N);
    for(auto& v: vec) {
      ist >> v;
    }
  }
};

MEASURE_F(VectorMeasure, Sum) {
  int sum = 0;
  Start();
  for(auto v: vec) {
    sum += v;
  }
  Stop();
  DUMMY(sum);
}
```
