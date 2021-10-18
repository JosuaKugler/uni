#Christian Merten, Josua Kugler

rec_series <- function(start, f, n) {
    m <- length(start)
    for (i in (m+1):n) {
       start[[i]] <- f(start[(i-1):(i-m)])
    }
    start
}