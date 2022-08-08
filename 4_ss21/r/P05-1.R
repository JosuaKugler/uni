# install.packages("babynames")
library(tidyverse)

## Create some data-----------------------------------------------------------

set.seed(1)

baseset <- list()
baseset$grade <- as.integer(c(5,6,7,8,9,10,11))
baseset$grade_boost <- c(1,3,5,7,8,9,10)
baseset$letter <- letters[1:4]
baseset$letter_boost <- sample(1:5, 4, replace=T)
babynames::babynames %>%
  group_by(sex, name) %>% 
  summarise(n = sum(n)) %>%
  arrange(desc(n)) %>%
  mutate(rank = min_rank(-n)) %>% 
  filter (rank <= 3000) ->
  ranked_names
baseset$name <- ranked_names$name
baseset$distance <- c(100,200,400,1000)
baseset$distance_boost <- c(14,12,10,8)

sample_observation <- function(n) {
  res <- list()
  res$name <- sample(baseset$name, n, replace=T)
  res$grade <- sample(baseset$grade, n, replace=T)
  res$letter <- sample(baseset$letter, n, replace=T)
  boost_base <- 
    baseset$grade_boost[match(res$grade,baseset$grade)] + 
    baseset$letter_boost[match(res$letter,baseset$letter)]
  res$time100 <- sample_time(100, baseset$distance_boost[1] + boost_base)
  res$time200 <- sample_time(200, baseset$distance_boost[2] + boost_base)
  res$time400 <- sample_time(400, baseset$distance_boost[3] + boost_base)
  res$time1000 <- sample_time(1000, baseset$distance_boost[4] + boost_base)
  as_tibble(res)
}

sample_time <- function(dist, boost) {
  (runif(length(boost))/2+2.5)/boost*dist*2
}

sports <- sample_observation(1000)

requirements <- tibble(
  level = 1:11,
  min100 = seq(43,23,len=11),
  min1000 = seq(500,300,len=11)
)



## Exercises -----------------------------------------------------------------


# a)
# get all students who failed in 100m or 1000m
sports %>% mutate("level" = grade) %>%
 left_join(requirements, by = "level") %>%
 filter(time100 > min100 | time1000 > min1000) -> a

# b)
# get names, grade and letter of all students who failed 1000m by less than 1s
# so you can still let them pass :)
a %>% filter(time1000 > min1000 + 1) %>% select('name':'letter') -> b

# c)
# tidy the data:
# create two columns from all timeXXX-columns:
# a column "time" with the entries from all timeXXX-columns
# a column "distance" of the distance the time refers to
# make sure all columns have a suitable type
sports %>% pivot_longer(time100:time1000, names_to = "distance", values_to = "time") %>% 
 extract(distance, into = "distance", regex = "time([0-9]+)", convert = TRUE) -> c
