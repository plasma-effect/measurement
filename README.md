# plasma-effect/measurement

C++のコード片の経過時間をgtestっぽく計りたいというライブラリです。

## 構成

- include/
  - 必要なヘッダファイルが入っています。
- src/
  - リンクする必要があるソースファイルが入っています。
- samples/
  - サンプルコードです。
- LICENSE
  - MITライセンスのライセンスファイルです。
- README.md
  - このファイルです。

## 使い方

### cmake

FetchContentを使って引っ張ってきてください。

```
include(FetchContent)

FetchContent_Declare(
    PlasmaMeasurement
    GIT_REPOSITORY https://github.com/plasma-effect/measurement.git
)
FetchContent_MakeAvailable(PlasmaMeasurement)
```

### Makefile

`include/`をパスに渡し`src/`下のファイルをリンクしてください。

```
target.o: target.cpp measurement/src/*.cpp
  g++ $^ -std=c++23 -o $@ -Imeasurement/include 
```
