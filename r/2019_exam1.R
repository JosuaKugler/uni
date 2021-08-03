foo <- function(lst) {
  names(lst) %>% unique() %>% length() -> diff
  diff < length(lst)
}

foo <- function(a, b, c) {
  expr(!!a * sin(!!b * (x - !!c)))
}
