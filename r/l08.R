library(tidyverse)
library(rlang)

#1
objs = list(
  1L, 
  1, 
  NULL, 
  "der rkurs ist toll",
  raw(0), 
  complex(real=1, imaginary = 1), 
  TRUE,
  list(1,"a")
  )

objs %>% sapply(typeof) %>% unique() %>% length()

#2
va <- function(n) {
  exps <- 0:n
  sapply(exps, (function(x) 2**x))
}
vb <- function(n) {
  first = n:1
  sec = 1:n
  sec = -sec
  c(first, sec)
}
vc <- function(n) {
  ((0:(n-1)) %% 5) + 1
}
vd <- function(n) {
  unlist(sapply(1:n, function(x) rep(x,x)))
}
vd(5)

#3

center_mat <- function(n) {
  if (n == 0) return(matrix(0, nrow = 1))
  first <- n:0
  sec <- 1:n
  middle_row <- c(first, sec)
  mat <- rep(middle_row, times = 2*n+1)
  bias_mat <- rep(middle_row, each=2*n+1)
  mat_list <- mat + bias_mat
  attr(mat_list, "dim") <- c(2*n + 1, 2*n + 1)
  mat_list
}

#4

`na<-` <- function(x, value) {
  index <- sapply(x, is.na)
  x[index] <- value
  x
}

x <- c(NA, 1, 2, NA, NA , 3)
na(x) <- c(10, 20, 30)

`%+%` <- function(a,b) {
  res <- a + b
  attr(res, 'left') <- a
  attr(res, 'right') <- b
  res
}

#5 
`*`( `:`( `+`(1, 2), 3 ), 4)

#6
data <- function(iter) {
  n <- 1000
  vals <- rt(n, df=1.5)
  a <- sapply(1:n, function(i) mean(vals[1:i]))
  s <- sapply(1:n, function(i) 1/sqrt(i) * sum(vals[1:i]) )
  tibble(index = 1:n, a=a, s=s)
}


data_list <- lapply(1:10, data)

plot_a <- function(data_list) {
  p <- ggplot(data_list[[1]], aes(x = index, y = a))
  for (tb in data_list) {
    p <- p + geom_line(data=tb)
  }
  p
}

plot_s <- function(data_list) {
  p <- ggplot(data_list[[1]], aes(x = index, y = s))
  for (tb in data_list) {
    p <- p + geom_line(data=tb)
  }
  p
}

#7 siehe Blatt 

#8
x[seq(1, 52, by=2)] <- letters
x[seq(2, 52, by=2)] <- LETTERS
do.call(str_c, as.list(x))

args <- as.list(letters)
args$sep  <- "X"

do.call(str_c, args)

c(do.call(str_c, as.list(letters[1:5])),
     do.call(str_c, as.list(letters[6:10])),
     do.call(str_c, as.list(letters[11:15])),
     do.call(str_c, as.list(letters[16:20])),
     do.call(str_c, as.list(letters[21:25])),
     do.call(str_c, as.list(letters[26])))

#9a
pattern <- "en\\b"
#9b
pattern <- "#\\b(\\w+)"
replacement <- "_\\1_"
example_string <- "Guten #Tag! #Heute #ist Samstag. Wie geht #es Ihnen?"
str_replace_all(example_string, pattern, replacement)


#10

col2hex <- function(col) {
  rgb <- col2rgb(col)
  rgb(rgb["red", ], rgb["green", ], rgb["blue", ], max = 255)
}

rgbcolors <- sapply(colors(), col2hex)
colortb = tibble(
  colors = colors(), 
  rgbcolors = rgbcolors
) 

print.Dots <- function(x) {
  n <- nrow(x)
  col = col2hex(attr(x, "color"))
  if (col %in% rgbcolors) {
    col <- filter(colortb, rgbcolors==col)$colors[[1]]
  }
  if (n > 1){
    name = "dots"
  } else {
    name = "dot"
  }
  cat(n, col, name)
}

plot.Dots <- function(x) {
  points(x=x[,1], x[,2], col=col2hex(attr(x, "color")))
}

#11

data <- diamonds
#a
data %>% group_by(cut) %>% count() -> a
#b
data %>% group_by(clarity) %>% summarize(avg_price = mean(price)) %>% arrange(desc(avg_price)) -> b
#c
clarity_levels = c("I1", "SI2", "SI1", "VS2", "VS1", "VVS2", "VVS1", "IF")
color_levels = LETTERS[4:10]
cut_levels = c("Fair", "Good", "Very Good", "Premium", "Ideal")
data %>% mutate(clarity = factor(clarity, levels = clarity_levels),
                color = factor(color, levels = color_levels),
                cut = factor(cut, levels = cut_levels)) %>%
  filter(rank(clarity) == max(rank(clarity)),
         rank(cut) == max(rank(cut)),
         rank(color) == min(rank(color))) %>%
  arrange(price) -> c

#d
data %>%
  mutate(quader_vol = x*y*z) -> d

#e
data %>%
  unite("color_clarity", color, clarity, sep="-") -> e

#f
data %>% mutate(cut = factor(cut, levels = cut_levels)) %>%
  filter(rank(cut) == max(rank(cut))) %>%
  mutate(price_per_carat = price/carat) %>%
  group_by(color, clarity) %>%
  summarize(mean_price_per_carat=mean(price_per_carat)) %>%
  select(c(color, clarity, mean_price_per_carat)) %>%
  pivot_wider(names_from = clarity, values_from = mean_price_per_carat) -> f

#12
brace_yourself <- function(x) {
  x <- expr_text(enexpr(x))
  brace_x <- str_c("{", x, "}")
  parse_expr(brace_x)
}

brace_yourself(1+2)
