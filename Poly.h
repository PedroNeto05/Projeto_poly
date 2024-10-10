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
  Poly(const Poly &N);
  Poly(Poly &&N);
  Poly &operator=(const Poly &P);
  ~Poly();
};

#endif
