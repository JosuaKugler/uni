#Christian Merten, Josua Kugler

collatz <- function(x, max_iter) {
  x <- as.integer(x)
  stopifnot(length(x) == 1)
  stopifnot(!is.na(x))
  seq <- c(x)
  len <- 1
  while (len < max_iter && x != 1) {
    if (x %% 2 == 0)
      x = as.integer(x / 2)
    else
      x = 3 * x + 1
    len <- len + 1
    seq[len] <- x
  }
  if (len == max_iter)
    len <- NA_integer_
  res = list(seq = seq, len = len)
  res
}