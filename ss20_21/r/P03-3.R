#Christian Merten, Josua Kugler

#1-----------------------------------------------------------------
size <- function(mat) attr(mat, "size")

`size<-` <- function(mat, value) {
    attr(mat, "size") <- value
    mat
}

#2-----------------------------------------------------------------
sudoku <- function(mat, n=nrow(mat)/m, m=nrow(mat)/n) {
    class(mat) <- "sudoku"
    size(mat) <- c(n,m)
    mat
}

#3-----------------------------------------------------------------
is_sudoku <- function(s) class(s) == "sudoku" && is.numeric(size(s)) && identical(size(s), c(size(s)[1], size(s)[2])) && is.numeric(x)

#4-----------------------------------------------------------------
is_sub_valid <- function(x, y=x[!is.na(x)]) is.numeric(x) && sum(y>length(x)) == 0 && length(y) == length(unique(y))

#5-----------------------------------------------------------------
partition_index <- function(n, m) {
    m1 <- rep(rep(1:n, each=m), times=n*m)
    m1 <- matrix(m1, byrow=TRUE, nrow=n*m)
    m2 <- n*rep(rep(0:(m-1), each=n),times = m*n)
    m2 <- matrix(m2,nrow = n*m)
    m1 + m2
}



#6-----------------------------------------------------------------
get_field <- function(s, k) s[partition_index(size(s)[1], size(s)[2]) == k]

col_validity <- function(s) apply(s, 1, is_sub_valid)
row_validity <- function(s) apply(s, 2, is_sub_valid)
field_validity <- function(s) sapply(1:nrow(s), function(k) is_sub_valid(get_field(s,k)))

is_valid <- function(s) {
    all(col_validity, row_validity, field_validity)
}

is_filled_in <- function(s) sum(is.na(x)) == 0
is_solved <- function(s) is_filled_in(s) && is_valid(s)

#7-----------------------------------------------------------------
is_solution_of <- function(s, s_star) {
    comp <- s == s_star
    comp <- comp[!is.na(comp)]
    all(comp) && is_solved(s_star)
}

#8-----------------------------------------------------------------

print_non_valid <- function(s, print_missing=TRUE) {
    if (print_missing) {
        apply(which(is.na(s), arr.ind = TRUE), 1, function(x) cat("missing value at ", x[1], ",", x[2],"\n", sep=""))
    }
    sapply(which(!col_validity(s)), function(x) cat("column ", x, " invalid\n"))
    sapply(which(!row_validity(s)), function(x) cat("row ", x, " invalid\n"))
    field_validity_vec <- field_validity(s)
    dim(field_validity_vec) <- size(s)
    if (length(which(!field_validity_vec)) > 0) {
        apply(which(!field_validity_vec, arr.ind = TRUE), 1, function(x) cat("field ", x[1], ",", x[2]," invalid\n", sep=""))
    }
    invisible(NULL)
}

x <- matrix(
c(5,2,6,4,3,1,6,1,3,2,5,4,3,4,1,5,2,6,2,6,4,3,1,5,1,3,5,6,4,2,4,5,2,1,6,3),
ncol=6)
s <- sudoku(x,3,2)
print_non_valid(s)