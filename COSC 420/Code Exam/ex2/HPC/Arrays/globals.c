#ifndef ARRAYGLOBALS
#define ARRAYGLOBALS

static int defaultArrayElemMin = 1;
static int defaultArrayElemMax = 10;

void updateDefaultMin(int newmin) {
  defaultArrayElemMin = newmin;
}
void updateDefaultMax(int newmax) {
  defaultArrayElemMax = newmax;
}
void updateDefaults(int newmin, int newmax) {
  updateDefaultMin(newmin);
  updateDefaultMax(newmax);
}
#endif
