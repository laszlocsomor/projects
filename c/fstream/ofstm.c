#include "ofstm.h"

#include <string.h>

int ofstm(FILE *f, struct ofstm *out) {
  if (!f) {
    return 1;
  }
  out->f = f;
  out->pos = 0;
  return 0;
}

int ofstm_wr(struct ofstm *s, const void *p, size_t n) {
  size_t n1 = n + s->pos > _OFSTM_BUF ? _OFSTM_BUF - s->pos : n;
  memcpy(s->buf + s->pos, p, n1);
  if (n1 == n) {
    s->pos += n1;
    return 0;
  }
  s->pos = 0;
  int r = fwrite(s->buf, 1, _OFSTM_BUF, s->f);
  if (r != _OFSTM_BUF) {
    return 1;
  }
  if (n >= _OFSTM_BUF) {
    r = fwrite(((uint8_t *)p) + n1, 1, n - n1, s->f);
    return r == n - n1 ? 0 : 1;
  } else {
    memcpy(s->buf, ((uint8_t *)p) + n1, n - n1);
    s->pos = n - n1;
  }
  return 0;
}

int ofstm_pnt(struct ofstm *s, const char *p) {
  return ofstm_wr(s, p, strlen(p));
}

int ofstm_fsh(struct ofstm *s) {
  if (s->pos) {
    size_t n = fwrite(s->buf, 1, s->pos, s->f);
    s->pos = 0;
    return n ? 0 : 1;
  } else {
    return 0;
  }
}
