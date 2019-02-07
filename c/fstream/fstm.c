#include "fstm.h"

int ifstm(FILE* f, struct fstm* out) {
  if (!f) {
    return 1;
  }
  size_t n = fread(out->pages, 1, _IFSTM_PAGE * 2, f);
  if (n == 0 && !feof(f)) {
    return 1;
  }

  if (out->f) {
    fclose(out->f);
  }
  out->f = f;
  out->pos = 0;
  out->end = n < _IFSTM_PAGE ? n : _IFSTM_PAGE;
  out->p1size = out->end;
  out->p2size = n < _IFSTM_PAGE ? 0 : (n - _IFSTM_PAGE);
  return 0;
}

int ifstm_rd(struct fstm* s) {
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
  if (s->pos < _IFSTM_PAGE) {
    s->pos = _IFSTM_PAGE;
    s->end = _IFSTM_PAGE + s->p2size;
    s->p1size = read;
  } else {
    s->pos = 0;
    s->end = s->p1size;
    s->p2size = read;
  }
  return result;
}

size_t ifstm_pk(struct fstm* s, size_t n, uint8_t* out) {
  if (s->pos == s->end) {
    return 0;
  }

  size_t n1 = s->end - s->pos;
  if (n1 > n) {
    n1 = n;  // all 'n' bytes are on the current page
  }
  for (size_t i = 0; i < n1; ++i) {
    out[i] = s->pages[s->pos + i];
  }
  if (n1 == n) {
    return n;
  }

  size_t offs;  // where the other page starts
  size_t n2 = n - n1;  // how much is left to read
  if (s->pos < _IFSTM_PAGE) {
    offs = _IFSTM_PAGE;
    if (n2 > s->p2size) {
      n2 = s->p2size;  // read no more than the other page's size
    }
  } else {
    offs = 0;
    if (n2 > s->p1size) {
      n2 = s->p1size;  // read no more than the other page's size
    }
  }
  for (size_t i = 0; i < n2; ++i) {
    out[n1 + i] = s->pages[offs + i];
  }
  return n1 + n2;
}

int ifstm_eof(struct fstm* s) {
  return s->pos == s->end;
}

void ifstm_close(struct fstm* s) {
  if (s->f) {
    fclose(s->f);
    s->f = 0;
  }
}
