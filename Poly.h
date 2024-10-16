#ifndef _POLY_H_
#define _POLY_H_

#include <ostream>
#include <string>
class Poly {
private:
  int grau;
  double *a;

public:
  Poly();
  explicit Poly(int N);
  Poly(const Poly &P);
  Poly(Poly &&P) noexcept;

  Poly &operator=(const Poly &P);
  Poly &operator=(Poly &&P) noexcept;
  double operator[](int N) const;
  bool operator==(const Poly &P) const;
  bool operator!=(const Poly &P) const;
  double operator()(double N) const;
  friend std::ostream &operator<<(std::ostream &O, const Poly &P);
  friend std::istream &operator>>(std::istream &O, Poly &P);
  Poly operator-() const;
  Poly operator+(const Poly &P) const;
  Poly operator-(const Poly &P) const;
  Poly operator*(const Poly &P) const;

  int getGrau() const;
  double getCoef(int N) const;
  void setCoef(int N, double value);
  void recriar(int N);
  bool empty() const;
  bool isZero() const;
  double getValor(double N) const;
  bool salvar(std::string file);
  bool ler(std::string file);

  void clear();
  ~Poly();
};

#endif
