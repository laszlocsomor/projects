#include "ifstm.h"

int ifstm(FILE *f, struct ifstm *out) {
  if (!f) {
    return 1;
  }
  size_t n = fread(out->pages, 1, _IFSTM_PAGE * 2, f);
  if (n == 0 && !feof(f)) {
    return 1;
  }

  out->f = f;
  out->pos = 0;
  out->end = n < _IFSTM_PAGE ? n : _IFSTM_PAGE;
  out->next_size = n < _IFSTM_PAGE
                       ? 0
                       : (n < _IFSTM_PAGE * 2 ? n - _IFSTM_PAGE : _IFSTM_PAGE);
  return 0;
}

int ifstm_rd(struct ifstm *s) {
  if (s->pos == s->end) {
    return IFSTM_RD_EOF;
  }

  int result = s->pages[s->pos];
  if (s->pos + 1 < s->end) {
    s->pos++;
    return result;
  }

  if (!s->f) {
    return IFSTM_RD_IO;
  }
  // Overwrite the *active* page: we are about to move off of it.
  size_t offs = (s->pos < _IFSTM_PAGE) ? 0 : _IFSTM_PAGE;
  size_t read = fread(s->pages + offs, 1, _IFSTM_PAGE, s->f);
  if (read == 0 && !feof(s->f)) {
    return IFSTM_RD_IO;
  }
  s->pos = (s->pos < _IFSTM_PAGE) ? _IFSTM_PAGE : 0;
  s->end = s->pos + s->next_size;
  s->next_size = read;
  return result;
}

size_t ifstm_pk(struct ifstm *s, size_t n, void *out) {
  if (s->pos == s->end) {
    return 0;
  }

  size_t n1 = s->end - s->pos;
  if (n1 > n) {
    n1 = n; // all 'n' bytes are on the current page
  }
  for (size_t i = 0; i < n1; ++i) {
    ((uint8_t *)out)[i] = s->pages[s->pos + i];
  }
  if (n1 == n) {
    return n;
  }

  size_t offs = (s->pos < _IFSTM_PAGE) ? _IFSTM_PAGE : 0;
  size_t n2 = n - n1; // how much is left to read
  if (n2 > s->next_size) {
    n2 = s->next_size; // read no more than the other page's size
  }
  for (size_t i = 0; i < n2; ++i) {
    ((uint8_t *)out)[n1 + i] = s->pages[offs + i];
  }
  return n1 + n2;
}
