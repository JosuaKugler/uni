
# a) ----------------------------------------------------------------------- 
midpoint <- function(f, a, b) {
  height <- f((a + b)/2)
  height * (b-a)
}

trapezoid <- function(f, a, b) {
  height <- (f(a) + f(b))/2
  height * (b-a)
}

# b) ----------------------------------------------------------------------
nc_integrate <- function(f, lower, upper, n, rule) {
  a <- lower + 0:(n-1) * (upper - lower)/n
  b <- lower + 1:n * (upper - lower)/n
  sum(rule(f, a, b))
}

# c) ------------------------------------------------------------------------

newton_cotes <- function(coef, closed=TRUE) {
  m <- length(coef)
  w <- coef / sum(coef)
  function(f, a, b) {
    base <- outer(a, rep(1, m), function(x, y) x* y)
    if (closed) t <- base + outer((b-a)/(m-1), 0:(m-1), function(x, y) x * y)
    else t <- base + outer((b-a)/(m+1), 1:m, function(x, y) x * y)
    val <- f(t)
    val <- matrix(val, nrow=length(a))
    print(val)
    wval <- w %*% t(val)
    (b-a) * wval
  }
}



# d) ------------------------------------------------------------------------

# some objects for param_fun-list
sin1x <- function(x) {
  y <- suppressWarnings(sin(1/x))
  y[is.na(y)] <- 0
  y
}
set.seed(0)
x <- c(0:1, runif(5))
y <- runif(7)

# list of functions with integral interval
param_fun <- list(
  poly = list(f = function(x) x^4 - x^3 - 3*x^2 + x + 2, lower = 0, upper = 2),
  sin1x = list(f = sin1x, lower = 0, upper = 1),
  lin = list(f = approxfun(x, y), lower = 0, upper = 1),
  spline = list(f = splinefun(x, y), lower = 0, upper = 1)
)

# true values of integrals
true <- c(
  poly = 0.4, 
  sin1x = 0.504067061906928, 
  lin = 0.472878602164825, 
  spline = 0.97236924451286)

# options for creating integral-rules
param_rule <- list(
  midpoint = list(coef = 1, closed=FALSE),
  trapezoid = list(coef = c(1,1), closed=TRUE),
  simpson = list(coef = c(1,4,1), closed=TRUE),
  boole = list(coef = c(7,32,12,32,7), closed=TRUE),
  open5 = list(coef = c(611, -453, 562, 562, -453, 611), closed=FALSE)
)

# how many function evaluations are allowed
param_n <- 5*(2:20)

library(tidyverse)

param <- as_tibble(
  expand.grid(
    n=param_n,
    fun_name=names(param_fun), rule_name=names(param_rule),
    stringsAsFactors=FALSE))

help_newton_cotes <- function(x) newton_cotes(x$coef, closed = x$closed)
nc_rules <- lapply(param_rule, help_newton_cotes)

sapply(nc_rules, typeof)

# run nc_integrate with given options
call_nc <- function(n, fun_name, rule_name) {
  opts <- param_fun[[fun_name]]
  opts$rule = nc_rules[[rule_name]]
  # to make things fair:
  # a rule which evaluates f at m points may only be called n/m times
  opts$n = round(n / length(param_rule[[rule_name]]$coef))
  print(opts)
  do.call(nc_integrate, opts)
}

# TODO:
# param %>% ... -> res
param %>% 
  rowwise() %>%
  mutate(value = call_nc(n, fun_name, rule_name), true=true[[fun_name]], error = abs(value - true)) -> res

res[30*(1:10), ]

# plot results
plots <- lapply(names(param_fun), function(nm) 
  res %>%
    filter(fun_name == nm) %>%
    ggplot(aes(x = n, y = error, color = rule_name)) +
    scale_y_log10() +
    geom_line() + geom_point() + labs(title = nm)
)
gridExtra::grid.arrange(grobs = plots, nrow=2)
