#Christian Merten, Josua Kugler

n_diag <- function(mat, n) {
    len <- (nrow(mat) - abs(n))
    vec <- numeric(len)
    if (n < 0)  mat <- t(mat)
    for (i in 1:len) vec[i] <- mat[i, i + abs(n)]
    vec
}

`n_diag<-` <- function(mat, n, value) {
    len <- (nrow(mat) - abs(n))
    vec <- numeric(len)
    vec[] <- value
    if (n < 0)  mat <- t(mat)
    for (i in 1:length(vec)) mat[i, i + abs(n)] <- vec[i]
    if (n < 0)  mat <- t(mat)
    mat
}
