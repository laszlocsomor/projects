#include "ifstm.h"

int ifstm(FILE *f, struct ifstm *s, size_t page_size) {
  if (!f) {
    return 1;
  }
  size_t n = fread(s->pages, 1, page_size * 2, f);
  if (n == 0 && !feof(f)) {
    return 1;
  }

  s->f = f;
  s->pos = 0;
  s->end = n < page_size ? n : page_size;
  s->next_size =
      n < page_size ? 0 : (n < page_size * 2 ? n - page_size : page_size);
  s->page_size = page_size;
  return 0;
}

int ifstm_read(struct ifstm *s) {
  if (s->pos == s->end) {
    return IFSTM_READ_EOF;
  }

  int result = s->pages[s->pos];
  if (s->pos + 1 < s->end) {
    s->pos++;
    return result;
  }

  if (!s->f) {
    return IFSTM_READ_IO;
  }
  // Overwrite the *active* page: we are about to move off of it.
  size_t offs = (s->pos < s->page_size) ? 0 : s->page_size;
  size_t read = fread(s->pages + offs, 1, s->page_size, s->f);
  if (read == 0 && !feof(s->f)) {
    return IFSTM_READ_IO;
  }
  s->pos = (s->pos < s->page_size) ? s->page_size : 0;
  s->end = s->pos + s->next_size;
  s->next_size = read;
  return result;
}

size_t ifstm_peek(struct ifstm *s, size_t n, void *out) {
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

  size_t offs = (s->pos < s->page_size) ? s->page_size : 0;
  size_t n2 = n - n1; // how much is left to read
  if (n2 > s->next_size) {
    n2 = s->next_size; // read no more than the other page's size
  }
  for (size_t i = 0; i < n2; ++i) {
    ((uint8_t *)out)[n1 + i] = s->pages[offs + i];
  }
  return n1 + n2;
}
