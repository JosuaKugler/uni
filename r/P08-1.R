library(magrittr) # lädt %>%
library(rlang)

`%->%` <- function(x, y) {
  force(x)
  name <- expr_text(enexpr(y))
  e <- caller_env()
  e[[name]] <- x
  return(x)
}

c(3,4) %->% x1 %>%
`^`(2) %->% x2 %>%
sum() %->% x3 %>%
sqrt() -> res
