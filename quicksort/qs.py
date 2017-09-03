def qs(xs, left, right, cmpfunc, swapfunc):
  print("qs(%s, left=%d, right=%d)" % (xs, left, right))
  if right <= left:
    return
  if right == left + 1:
    if cmpfunc(xs, left, right) < 0:
      swapfunc(xs, left, right)
    return
  pl = left
  pr = right
  while pl < pr:
    while pl < pr and cmpfunc(xs, pl, right) >= 0:
      pl += 1
    while pl < pr and cmpfunc(xs, pr, right) <= 0:
      pr -= 1
    if pl < pr:
      swapfunc(xs, pl, pr)
    else:
      break
  if pl < right and cmpfunc(xs, pl, right) < 0:
    swapfunc(xs, pl, right)
  if left < pl - 1:
    qs(xs, left, pl - 1, cmpfunc, swapfunc)
  if pr + 1 < right:
    qs(xs, pr + 1, right, cmpfunc, swapfunc)


def cmpfunc(vec, a, b):
  return vec[b] - vec[a]

def swapfunc(vec, a, b):
  t = vec[a]
  vec[a] = vec[b]
  vec[b] = t

xs = [6,5,4,3,2,1]
qs(xs, 0, len(xs) - 1, cmpfunc, swapfunc)
