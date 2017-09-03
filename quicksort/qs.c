#include <stdio.h>

void printvec(void* xs, int len) {
  printf("[");
  for (int i = 0; i < len; i++) {
    if (i > 0) {
      printf(", ");
    }
    printf("%d", ((int*) xs)[i]);
  }
  printf("]\n");
}

void qs(
    void* xs,
    int len,
    int left,
    int right,
    int (* cmpfunc)(void*, int, int),
    void (* swapfunc)(void*, int, int)) {
  printvec(xs, len);
  if (right <= left) {
    return;
  }
  if (right == left + 1) {
    if (cmpfunc(xs, left, right) < 0) {
      swapfunc(xs, left, right);
    }
    return;
  }
  int pl = left;
  int pr = right;
  while (pl < pr) {
    while (pl < pr && cmpfunc(xs, pl, right) >= 0) {
      pl++;
    }
    while (pl < pr && cmpfunc(xs, pr, right) <= 0) {
      pr--;
    }
    if (pl < pr) {
      swapfunc(xs, pl, pr);
    } else {
      break;
    }
  }
  if (pl < right && cmpfunc(xs, pl, right) < 0) {
    swapfunc(xs, pl, right);
  }
  if (left < pl - 1) {
    qs(xs, len, left, pl - 1, cmpfunc, swapfunc);
  }
  if (pr + 1 < right) {
    qs(xs, len, pr + 1, right, cmpfunc, swapfunc);
  }
}

int cmpfunc(void* vec, int a, int b) {
  return ((int*) vec)[b] - ((int*) vec)[a];
}

void swapfunc(void* vec, int a, int b) {
  int t = ((int*) vec)[a];
  ((int*) vec)[a] = ((int*) vec)[b];
  ((int*) vec)[b] = t;
}

int main(int argc, char** argv) {
  int xs[9] = {6, 1, 7, 3, 8, 9, 4, 7, 6};
  qs(xs, 9, 0, 8, cmpfunc, swapfunc);
  return 0;
}
