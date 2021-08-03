#x

foo <- function(...) {
  args <- list(...)
  
  print(args)
  if (all(sapply(args, is.numeric)) && all(sapply(args, length) == 1)) {
    df <- data.frame(x = c(...), sin_x = sin(c(...)))
    return(df)
  }
}

#xi

foo <- function() {
  identical(caller_env(), global_env()) 
}


#iv
foo <- function(string, x) {
  a <- expr(string)
  total <- expr(do.call(!!a, list(x)))
  eval(total)
}


#vi
batman <- function(na) {
  str_replace(na, "(Na Na Na Na Na Na Na Na Na Na Na Na Na Na)", "\\1 Batman")
}

proj <- tibble(
  topics = c("Statistics", "Probability"),
  member1 = c("Ferdinand", "Claudia"),
  member2 = c("Boris", "Damian"),
  member3 = c("Elsa", "Anna")
)


simplify <- function(proj) {
  proj %>% 
    pivot_longer(cols=member1:member3, names_to="member", values_to="student") %>%
    select(student, topics)
}
