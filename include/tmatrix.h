// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//
#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__
#include <iostream>
#include <numeric>

#ifdef USE_OPENMP
#include <omp.h>
#endif

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;


template<typename T>
class TDynamicVector {
protected:
  size_t sz = 0;
  T* pMem = nullptr;
public:
  TDynamicVector(size_t size = 1) : sz(size) {
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
      throw std::out_of_range("Vector size should be greater than zero and less than MAX_SIZE");
    pMem = new T[sz]();
  }

  TDynamicVector(T* arr, size_t size) : sz(size) {
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
      throw std::out_of_range("Vector size should be greater than zero and less than MAX_SIZE");
    assert(arr != nullptr && "TDynamicVector requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }

  TDynamicVector(const TDynamicVector& v)
    : sz(v.sz), pMem(new T[sz]) {
    std::copy(v.pMem, v.pMem + sz, pMem);
  }

  TDynamicVector(TDynamicVector&& v) noexcept
    : sz(v.sz), pMem(v.pMem) {
    v.sz = 0;
    v.pMem = nullptr;
  }

  ~TDynamicVector() {
    delete[] pMem;
  }

  // ну вдруг new T[sz] бросит исключение а память уже освобождена, так безопаснее
  TDynamicVector& operator=(const TDynamicVector& v) {
    if (this != &v) {
      TDynamicVector temp(v);
      swap(*this, temp);
    }
    return *this;
  }

  TDynamicVector& operator=(TDynamicVector&& v) noexcept {
    if (this != &v) {
      delete[] pMem;
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
    }
    return *this;
  }

  size_t size() const noexcept { return sz; }

  T& operator[](size_t ind) noexcept { return *(pMem+ind); }

  const T& operator[](size_t ind) const noexcept { return *(pMem+ind); }

  T& at(size_t ind) {
    if (ind >= sz) {
      throw std::out_of_range("wrong index");
    }
    return *(pMem+ind);
  }

  const T& at(size_t ind) const {
    if (ind >= sz) {
      throw std::out_of_range("wrong index");
    }
    return *(pMem+ind);
  }

  // написать можно специализацию для флотов и интов, но мне лень
  // (еще можно написать через std::is_same как предлагал на паре)
  bool operator==(const TDynamicVector& v) const noexcept {
    return sz == v.sz && std::equal(pMem, pMem + sz, v.pMem);
  }

  bool operator!=(const TDynamicVector& v) const noexcept {
    return !operator==(v);
  }

  // скалярные операции
  TDynamicVector operator+(T val) {
    TDynamicVector temp(sz);
    for (size_t i = 0; i < sz; ++i) {
      temp[i] = pMem[i] + val;
    }
    return temp;
  }

  TDynamicVector operator-(double val) {
    TDynamicVector temp(sz);
    for (size_t i = 0; i < sz; ++i) {
      temp[i] = pMem[i] - val;
    }
    return temp;
  }

  TDynamicVector operator*(double val) {
    TDynamicVector temp(sz);
    for (size_t i = 0; i < sz; ++i) {
      temp[i] = pMem[i] * val;
    }
    return temp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) {
    if (sz != v.sz) {
      throw std::invalid_argument("Vector sizes must match for addition");
    }
    TDynamicVector temp(sz);
    for (size_t i = 0; i<sz; ++i) {
      temp[i] = pMem[i] + v.pMem[i];
    }
    return temp;
  }

  TDynamicVector operator-(const TDynamicVector& v) {
    if (sz != v.sz) {
      throw std::invalid_argument("Vector sizes must match for addition");
    }
    TDynamicVector temp(sz);
    for (size_t i = 0; i<sz; ++i) {
      temp[i] = pMem[i] - v.pMem[i];
    }
    return temp;
  }

  T operator*(const TDynamicVector& v) {
    if (sz != v.sz) {
      throw std::invalid_argument("Vector sizes must match for dot product");
    }
    T temp = std::inner_product(pMem, pMem + sz, v.pMem, T());
    return temp;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  friend std::istream& operator>>(std::istream& istr, TDynamicVector& v) {
    for (size_t i = 0; i < v.sz; ++i)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }

  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v) {
    for (size_t i = 0; i < v.sz; ++i)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : TDynamicVector<TDynamicVector<T>> {
  using TBASE = TDynamicVector<TDynamicVector<T>>;
  using TBASE::pMem;
  using TBASE::sz;
public:
  TDynamicMatrix(size_t s = 1) : TBASE(s) {
    if (s == 0 || s > MAX_MATRIX_SIZE)
      throw std::out_of_range("Matrix size should be greater than zero and less than MAX_SIZE");
    for (size_t i = 0; i<sz; ++i)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TBASE::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept {
    if (sz != m.sz) return false;
    for (size_t i = 0; i<sz; ++i) {
      if (pMem[i] != m.pMem[i]) return false;
    }
    return true;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept {
    return !operator==(m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) {
    TDynamicMatrix temp(sz);
    for (size_t i = 0; i < sz; ++i) {
      temp[i] = pMem[i] * val;
    }
    return temp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
    if (sz != v.size()) {
      throw std::invalid_argument("Matrix and vector sizes must match for multiplication");
    }
    TDynamicVector<T> temp(sz);
    for (size_t i = 0; i<sz; ++i) {
      temp[i] = pMem[i]*v;
    }
    return temp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) {
    if (sz != m.sz) {
      throw std::invalid_argument("Matrix sizes must match for addition");
    }
    TDynamicMatrix temp(sz);
    for (size_t i = 0; i<sz; ++i) {
      temp[i] = pMem[i]+m.pMem[i];
    }
    return temp;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m) {
    if (sz != m.sz) {
      throw std::invalid_argument("Matrix sizes must match for subtraction");
    }
    TDynamicMatrix temp(sz);
    for (size_t i = 0; i<sz; ++i) {
      temp[i] = pMem[i]-m.pMem[i];
    }
    return temp;
  }

  TDynamicMatrix operator*(const TDynamicMatrix& m) {
    if (sz != m.sz) {
      throw std::invalid_argument("Matrix sizes must match for multiplication");
    }
    size_t n = sz;
    TDynamicMatrix res(n);
    const size_t BLOCK_SIZE = 64; // от 32 до 128, можно побаловаться

    #pragma omp parallel for
    for (size_t i = 0; i<n; i+=BLOCK_SIZE) {
      for (size_t k = 0; k<n; k+=BLOCK_SIZE) {
        for (size_t j = 0; j<n; j+=BLOCK_SIZE) {

          for (size_t ii = i; ii<std::min(i+BLOCK_SIZE, n); ++ii) {
            for (size_t kk = k; kk<std::min(k+BLOCK_SIZE, n); ++kk) {
              T temp = (*this)[ii][kk];
              /*
               * Если смотреть ассемблер, то можно заметить, что создание
               * переменной раньше цикла с умножением сразу грузит значение в
               * регистр, то есть происходит только одна загрузка и последующее
               * умножение происходит с регистром
               * Иначе, если написать res[ii][jj] += a[ii][kk]*b[kk][jj],
               * будет каждый раз искать и грузить из памяти значение
               *
               * (я проверил, работает быстрее примерно на 35-40%)
               * amd ryzen 8845hs
               * g++ (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
               */
              #pragma omp simd
              for (size_t jj = j; jj < std::min(j + BLOCK_SIZE, n); ++jj) {
                res[ii][jj] += temp * m[kk][jj];
              }
            }
          }
        }
      }
    }
    return res;
  }

  size_t size() const noexcept { return sz; }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& m) {
    for (size_t i = 0; i<m.sz; ++i) {
      istr >> m.pMem[i];
    }
    return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& m) {
    for (size_t i = 0; i<m.sz; ++i) {
      ostr << m.pMem[i] << std::endl;
    }
    return ostr;
  }
};

#endif
