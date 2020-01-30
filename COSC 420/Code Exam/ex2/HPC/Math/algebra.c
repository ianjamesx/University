#ifndef ALGEBRA
#define ALGEBRA

// ((x1c)x+n)*((x2c)x+m);
double* quadratic_formula(double n, double m, double x1c, double x2c, double* roots) {
  double a = x1c*x2c;
  double b = x1c*m+x2c*n;
  double c = n*m;
  //printf("%0.2f %0.2f %0.2f\n",a,b,c);

  double root = sqrt(pow(-b,2)-4*a*c);
  double twoa = 2*a;
  roots[0] = (-b + root)/twoa;
  roots[1] = (-b - root)/twoa;
  //printf("%0.2f %0.2f\n",roots[0],roots[1]);

  return roots;
}
double find_root(double shift, double xc) {
  return (0-shift)/xc;
}
void find_roots_varxc(int degree, double* shifts, double* xc, double* results) {
  for(int root_ind = 0; root_ind < degree; root_ind++) {
    results[root_ind] = find_root(shifts[root_ind], xc[root_ind]);
  }
}
void find_roots_xc(int degree, double* shifts, double xc, double* results) {
  for(int root_ind = 0; root_ind < degree; root_ind++) {
    results[root_ind] = find_root(shifts[root_ind], xc);
  }
}
void find_eigenvalues(int matrixsize, double* shifts, double* results) {
  find_roots_xc(matrixsize, shifts, -1, results);
}


#endif
