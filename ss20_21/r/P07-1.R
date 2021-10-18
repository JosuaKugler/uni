mem_near <- function(f_in) {
    saved_x <- saved_y <- double(0)
    f_out <- function(x, nearest) {
        if (nearest) {
            table <- outer(x, saved_x, function(x, y) abs(x-y))
            indices <- apply(table, 1, order)[1,] #index of minimum difference
            saved_y[indices]
        } else {
            #append new values to saved values
            y <- f_in(x)
            n <- length(saved_x)
            work_x <- saved_x
            work_y <- saved_y
            work_x[(n+1):(n+length(x))] <- x
            work_y[(n+1):(n+length(x))] <- y
            x_order = order(work_x)
            saved_x <<- work_x[x_order]
            saved_y <<- work_y[x_order]
            y
        }
    }
}