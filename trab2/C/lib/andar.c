#include "andar.h"
#include <math.h>

int distAndares (Andar *a, Andar *b) {
  return abs(a->numAndar - b->numAndar);
}
