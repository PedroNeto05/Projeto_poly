#include "Poly.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

Poly::Poly() : grau(-1), a(nullptr) {}

Poly::Poly(int N) : grau(-1), a(nullptr) {
  if (N < 0) {
    return;
  }

  if (N == 0) {
    grau = N;
    a = new double[1];
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

Poly::Poly(const Poly &P) : grau(P.grau), a(nullptr) {
  a = new double[grau + 1];
  for (int i = 0; i <= grau; i++) {
    a[i] = P.a[i];
  }
}

Poly::Poly(Poly &&P) noexcept : grau(-1), a(nullptr) {
  swap(grau, P.grau);
  swap(a, P.a);
}

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

  swap(grau, P.grau);
  swap(a, P.a);

  return *this;
}

double Poly::operator[](int N) const { return getCoef(N); }

bool Poly::operator==(const Poly &P) const {

  if (grau != P.grau)
    return false;

  for (int i = 0; i <= grau; i++) {
    if (a[i] != P.a[i])
      return false;
  }

  return true;
}

bool Poly::operator!=(const Poly &P) const { return !(*this == P); }

double Poly::operator()(double N) const { return getValor(N); };

ostream &operator<<(ostream &O, const Poly &P) {
  for (int i = P.grau; i >= 0; i--) {
    double ai = P.a[i];

    if (ai == 0.0) {
      if (i == 0 && P.grau == 0) {
        O << ai;
      }
      continue;
    }

    if (ai < 0.0) {
      O << '-';
    } else if (i != P.grau) {
      O << '+';
    }

    if (abs(ai) != 1.0 || i == 0) {
      O << abs(ai);
    }

    if (i != 0) {
      if (abs(ai) != 1.0) {
        O << '*';
      }
      O << 'x';
      if (i > 1) {
        O << '^' << i;
      }
    }
  }

  return O;
}

istream &operator>>(istream &O, Poly &P) {
  if (P.empty()) {
    return O;
  }

  for (int i = P.grau; i >= 0; i--) {
    if (i == P.grau) {
      do {
        cout << "Digite o coeficiente de x^" << i << ": ";
        O >> P.a[i];
      } while (P.a[i] == 0 && P.grau != 0);
      continue;
    }
    cout << "Digite o coeficiente de x^" << i << ": ";
    O >> P.a[i];
  }

  return O;
}

Poly Poly::operator-() const {

  if (empty())
    return *this;

  Poly prov(*this);

  for (int i = 0; i <= grau; i++) {
    prov.a[i] = -prov.a[i];
  }

  return prov;
}

Poly Poly::operator+(const Poly &P) const {
  Poly prov(max(grau, P.grau));

  for (int i = 0; i <= prov.grau; i++)
    prov.a[i] = getCoef(i) + P[i];

  while (prov.grau > 0 && prov.a[prov.grau] == 0.0) {
    prov.grau--;
  }
  return prov;
}

Poly Poly::operator-(const Poly &P) const {
  Poly prov(max(grau, P.grau));

  for (int i = 0; i <= prov.grau; i++)
    prov.a[i] = getCoef(i) - P[i];

  while (prov.grau > 0 && prov.a[prov.grau] == 0.0) {
    prov.grau--;
  }

  return prov;
}

Poly Poly::operator*(const Poly &P) const {

  if (empty() || P.empty())
    return Poly();

  if (isZero() || P.isZero())
    return Poly(0);

  Poly prov(grau + P.grau);

  for (int i = 0; i <= prov.grau; i++) {
    prov.a[i] = 0.0;
  }

  for (int i = 0; i <= grau; i++) {
    for (int j = 0; j <= P.grau; j++) {
      prov.a[i + j] += a[i] * P.a[j];
    }
  }

  return prov;
}

int Poly::getGrau() const { return grau; }

double Poly::getCoef(int N) const {

  if (N < 0 || N > grau)
    return 0.0;

  return a[N];
}

void Poly::setCoef(int N, double value) {

  if (N < 0 || N > grau) {
    cerr << "[ERRO] O Indice não pode ser maior que o grau ou menor que 0"
         << endl;
    return;
  }
  if (value == 0 && N == grau && grau > 0) {
    cerr << "[ERRO] valor nulo para o coeficiente de maior grau em um "
            "polinômio não nulo"
         << endl;
    return;
  }

  a[N] = value;
}

void Poly::recriar(int N) {
  Poly prov(N);
  *this = std::move(prov);
}

bool Poly::empty() const { return grau < 0; }

bool Poly::isZero() const {
  if (grau > 0 || grau < 0)
    return false;
  return a[0] == 0;
}

double Poly::getValor(double N) const {
  double res(0.0);

  if (empty()) {
    return res;
  }

  for (int i = 0.0; i <= grau; i++) {
    res += a[i] * pow(N, i);
  }

  return res;
}

bool Poly::salvar(string file) {
  ofstream stream_out(file);

  if (!stream_out.is_open())
    return false;

  stream_out << "POLY" << " " << grau << endl;

  if (empty())
    return true;

  for (int i = 0; i <= grau; i++) {
    stream_out << a[i] << " ";
  }

  stream_out << endl;
  return true;
}

bool Poly::ler(string file) {
  ifstream stream_out(file);

  if (!stream_out.is_open()) {
    cout << "aqui 1" << endl;
    return false;
  }

  string header;
  stream_out >> header;

  if (stream_out.fail() || header != "POLY") {
    cout << header << endl;
    cout << "aqui 2" << endl;
    return false;
  }

  int prov_grau;
  stream_out >> prov_grau;

  if (stream_out.fail()) {
    cout << "aqui 3" << endl;
    return false;
  }

  if (prov_grau < 0) {
    *this = std::move(Poly(-1));
    return true;
  }

  Poly prov(prov_grau);

  double prov_idx;

  for (int i = 0; i <= prov.grau; i++) {
    stream_out >> prov_idx;

    if (stream_out.fail()) {
      cout << "aqui 4" << endl;
      return false;
    }

    if (prov.grau > 0 && i == grau && prov_idx == 0) {
      cout << "aqui 5" << endl;
      return false;
    }

    prov.a[i] = prov_idx;
  }

  *this = std::move(prov);
  return true;
}

void Poly::clear() {
  delete[] a;

  grau = -1;
  a = nullptr;
}
Poly::~Poly() { clear(); }
