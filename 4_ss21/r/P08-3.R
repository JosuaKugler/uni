library(tidyverse)
library(ggplot2)
rate <- function(df, expr, name) {
    mutate(df, !!name := {{expr}}/sum({{expr}}))
}

show_na <- function(df, expr) {
    filter(df, is.na({{expr}}))
}


ggplot_line <- function(df, expr_x, expr_y) {
    df <- mutate(df, x = {{expr_x}}, y = {{expr_y}})
    ggplot(df, aes(x,y)) + geom_line()
}

athletes <- read_csv("athletes.csv")

plot_olympia <- function(event, sex, metric) {
    medal_color <- c(Bronze = "#6A3805", Silver = "#B4B4B4", Gold = "#AF9500")
    athletes %>%
    filter(Event == event, Sex == sex) %>%
    mutate(Year = as.factor(Year)) ->
    d
    ggplot(d, aes(x = Year, y = {{metric}})) +
    geom_boxplot(na.rm = TRUE) +
    geom_point(data = drop_na(d), aes(color = Medal)) +
    scale_color_manual(values = medal_color) +
    ggtitle(str_c(event,", ", sex))
}

plot_olympia("10,000 metres", "F", Height)
plot_olympia("100 metres", "M", Weight/(Height/100)^2)
