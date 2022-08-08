# Christian Merten, Josua Kugler

make_store <- function(n) {
    list <- vector(mode = "list", length = n)
    cnt <- 1
    function(item = NULL, reset = FALSE) {
        if (!is.null(item)) {
            if (reset) {
            list <<- vector(mode = "list", length = n)
            cnt <- 1
            }
            list[[cnt]] <<- item
            if (cnt < n) cnt <<- cnt + 1 else cnt <<- 1
            invisible(list)
        } else list
    }
}