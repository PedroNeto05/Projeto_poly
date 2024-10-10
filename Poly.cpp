#include "Poly.h"
#include <utility>

Poly::Poly() : grau(-1), a(nullptr) {} // Construtor Default
Poly::Poly(int N) {                    // Construtor expecifico
  if (N < 0) {
    grau = -1;
    a = nullptr;
    return;
  }
  if (N == 0) {
    grau = N;
    a = new double[grau + 1];
    a[0] = 0.0;
    return;
  }

  grau = N;
  a = new double[grau + 1];
  a[grau] = 1.0;
}
Poly::Poly(const Poly &N) : grau(N.grau) {
  a = new double[grau + 1];
  for (int i = 0; i <= grau; i++) {
    a[i] = N.a[i];
  }
} // Construtor por copia
Poly::Poly(Poly &&N) : grau(-1), a(nullptr) {
  std::swap(grau, N.grau);
  std::swap(a, N.a);
} // Construtor por movimento

void Poly::clear() {
  delete[] a;

  grau = -1;
  a = nullptr;
}
Poly::~Poly() { clear(); }
