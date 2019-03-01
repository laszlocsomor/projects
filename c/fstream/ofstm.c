#include "ofstm.h"

#include <string.h>

int ofstm(FILE *f, struct ofstm *s, size_t buf_size) {
  if (!f) {
    return 1;
  }
  s->f = f;
  s->pos = 0;
  s->buf_size = buf_size;
  return 0;
}

int ofstm_write(struct ofstm *s, const void *p, size_t n) {
  size_t n1 = n + s->pos > s->buf_size ? s->buf_size - s->pos : n;
  memcpy(s->buf + s->pos, p, n1);
  if (n1 == n) {
    s->pos += n1;
    return 0;
  }
  s->pos = 0;
  int r = fwrite(s->buf, 1, s->buf_size, s->f);
  if (r != s->buf_size) {
    return 1;
  }
  if (n >= s->buf_size) {
    r = fwrite(((uint8_t *)p) + n1, 1, n - n1, s->f);
    return r == n - n1 ? 0 : 1;
  } else {
    memcpy(s->buf, ((uint8_t *)p) + n1, n - n1);
    s->pos = n - n1;
  }
  return 0;
}

int ofstm_print(struct ofstm *s, const char *p) {
  return ofstm_write(s, p, strlen(p));
}

int ofstm_flush(struct ofstm *s) {
  if (s->pos) {
    size_t n = fwrite(s->buf, 1, s->pos, s->f);
    s->pos = 0;
    return n ? 0 : 1;
  } else {
    return 0;
  }
}
