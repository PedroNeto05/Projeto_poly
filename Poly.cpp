#include "Poly.h"
#include <iostream>
#include <utility>

Poly::Poly() : grau(-1), a(nullptr) {
  std::cout << "Def" << std::endl;
} // Construtor Default
Poly::Poly(int N) { // Construtor expecifico
  std::cout << "Exp" << std::endl;
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
  for (int i = 0; i < grau; i++) {
    a[i] = 0.0;
  }
  a[grau] = 1.0;
}
Poly::Poly(const Poly &P) : grau(P.grau) {
  std::cout << "Copia" << std::endl;
  a = new double[grau + 1];
  for (int i = 0; i <= grau; i++) {
    a[i] = P.a[i];
  }
} // Construtor por copia
Poly::Poly(Poly &&P) noexcept : grau(-1), a(nullptr) {
  std::cout << "Movimento" << std::endl;
  std::swap(grau, P.grau);
  std::swap(a, P.a);
} // Construtor por movimento

Poly &Poly::operator=(const Poly &P) {
  if (this == &P)
    return *this;
  delete[] a;

  grau = P.grau;
  if (grau > 0)
    a = new double[grau + 1];
  else
    a = nullptr;
  for (int i = 0; i <= grau; i++) {
    a[i] = P.a[i];
  }
  return *this;
}

Poly &Poly::operator=(Poly &&P) noexcept {
  delete[] a;
  grau = -1;
  a = nullptr;

  std::swap(grau, P.grau);
  std::swap(a, P.a);

  return *this;
}

int Poly::getGrau() const { return grau; }

double Poly::getCoef(int N) const {

  if (N < 0 || N > grau)
    return 0.0;

  return a[N];
}

void Poly::setCoef(int i, double value) {

  if (i < 0 || i > grau) {
    std::cerr << "[ERRO] O Indice não pode ser maior que o grau ou menor que 0"
              << std::endl;
    return;
  }
  if (value == 0 && i == grau && grau > 0) {
    std::cerr << "[ERRO] valor nulo para o coeficiente de maior grau em um "
                 "polinômio não nulo"
              << std::endl;
    return;
  }

  a[i] = value;
}

void Poly::clear() {
  delete[] a;

  grau = -1;
  a = nullptr;
}
Poly::~Poly() { clear(); }
