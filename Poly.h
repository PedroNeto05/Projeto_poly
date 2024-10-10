#ifndef _POLY_H_
#define _POLY_H_

class Poly {
private:
  int grau;
  double *a;
  void clear();

public:
  Poly();
  explicit Poly(int N);
  Poly(const Poly &P);
  Poly(Poly &&N);
  Poly &operator=(const Poly &P);
  Poly &operator=(Poly &&P) noexcept;

  int getGrau() const;
  double getCoef(int N) const;
  void setCoef(int i,double value);
  ~Poly();
};

#endif
