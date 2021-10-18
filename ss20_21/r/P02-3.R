#Christian Merten, Josua Kugler

my_tibble <- function(data) {
   len <- length(data[[1]])
   attr(data, "row.names") <- 1:len
   attr(data, "class") <- c("tbl_df", "tbl", "data.frame")
   print(data)
}


my_factor <- function(data) {
  levels <- typeof(data)[0]
  for (elem in data) {
    if (!is.element(elem, levels)) {
      levels[length(levels) + 1 ] <- elem
    }
  }
  for (i in 1:length(levels)) {
    for (j in 1:length(data)) {
      if (data[j] == levels[i]) {
        data[j] <- i
      }
    }
  }
  
  data <- as.integer(data)
  
  attr(data, "levels") <- levels
  attr(data, "class") <- "factor"
  
  print(data)
}
