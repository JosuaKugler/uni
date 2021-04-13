eucl_dist <- function(x, y) {
  A <- length(x); B <- length(y); 
  if (A == B) {
    res = list("ok", sqrt(sum((x-y)^2)))
    } else {
      retstr = sprintf("lengths differ: %d vs %d", A, B)
      res <- list(retstr, NaN)
    }
  return(res)
}