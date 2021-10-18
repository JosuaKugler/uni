#Christian Merten, Josua Kugler

lsq <- function(X, y) {
  stopifnot("X must not have length 0" = length(X) > 0)
  stopifnot("y must not have length 0" = length(y) > 0)
  stopifnot("X must be numeric" = (typeof(X) == "integer" || typeof(X) == "double"))
  stopifnot("y must be numeric" = (typeof(y) == "integer" || typeof(y) == "double"))
  stopifnot("X must be matrix" = (class(X) == "matrix")[1])
  stopifnot("y must be matrix or vector" = (is.vector(y) || (class(y) == "matrix")[1]))
  stopifnot("y must not have more than 1 column" = (is.vector(y) || ncol(y) == 1))
  stopifnot("X may not contain NA" = (sum(sapply(as.vector(X), is.na)) == 0))
  stopifnot("y may not contain NA" = (sum(sapply(as.vector(y), is.na)) == 0))
  stopifnot("dimensions of X and y do not fit" = (nrow(X) == length(y)))
  A <- t(X) %*% X
  stopifnot("det(t(X)%*% X) must not be 0" = det(A) != 0)
  solve(A, t(X) %*% y)
}

lsq(matrix(1:6, nrow=3), 1:3)
lsq(matrix(runif(6), nrow=3), matrix(runif(3), ncol=1))
lsq(matrix(letters[1:6] , nrow=2), 1:3)
lsq(matrix(1:6, nrow=3), list(1,2,3))
lsq(1:6, 1:3)
lsq(matrix(1:6, nrow=3), array(1:3, dim=c(1,1,3)))
lsq(matrix(1:6, nrow=3), 1:4)
lsq(matrix(1:6, nrow=3), matrix(1:3, nrow=1))
lsq(matrix(1:6, nrow=3), matrix(1:6, nrow=3))
lsq(matrix(double(0), nrow=0, ncol=0), matrix(double(0), nrow=0, ncol=0))
lsq(matrix(1:6, nrow=3), c(1,NA,3))
lsq(matrix(c(1:5, NA), nrow=3), 1:3)
lsq(matrix(c(1,1,2,1,1,2), nrow=3), 1:3)
