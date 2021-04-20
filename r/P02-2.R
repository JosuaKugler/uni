#Christian Merten, Josua Kugler

my_matrix <- function(vec, nrow=NULL, ncol=NULL, colnames=NULL, rownames=NULL) {
  
  if (length(vec) == 1) {
    if (is.null(ncol)) {
      ncol = 1
    } else if (is.null(nrow)) {
      nrow = 1
    }
    vec <- rep(vec, ncol*nrow)
  }
  else {
    stopifnot(!(is.null(nrow) && is.null(ncol)))
    if (is.null(ncol)) {
      stopifnot((length(vec) %% nrow) == 0)
      ncol <- length(vec) / nrow
    }
    else if (is.null(nrow)) {
      stopifnot((length(vec) %% ncol) == 0)
      nrow <- length(vec) / ncol
    }
      else stopifnot(nrow * ncol == length(vec))
  }
  dim(vec) <- c(nrow, ncol)
  if (!is.null(rownames) && is.null(colnames)) attr(vec, "dimnames") <- list(rows = rownames, NULL)
  if (is.null(rownames) && !is.null(colnames)) attr(vec, "dimnames") <- list(NULL, columns = colnames)
  if (!is.null(rownames) && !is.null(colnames)) attr(vec, "dimnames") <- list("rows" = rownames, "columns" = colnames)
  print(vec)
}

my_matrix(1:6)
my_matrix(1:6, ncol=1)
my_matrix(1:6, ncol=2)
my_matrix(1:6, ncol=3)
my_matrix(1:6, ncol=6)
my_matrix(1:6, ncol=4)
my_matrix(1:6, nrow=2)
my_matrix(1:6, nrow=7)
my_matrix(1:6, ncol=2, nrow=2)
my_matrix(1:6, ncol=2, nrow=3)
my_matrix(1:6, ncol=2, nrow=1)
my_matrix(0, ncol=3, nrow=2)
my_matrix(1:6, ncol=3, colnames=LETTERS[1:3])
my_matrix(1:6, ncol=3, colnames=LETTERS[1:2])
my_matrix(1:6, ncol=3, rownames=letters[24 + 1:2])
my_matrix(1:6, ncol=3, colnames=LETTERS[1:3], rownames=letters[24 + 1:2])

