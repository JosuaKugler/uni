library(tidyverse)
library(babynames)

# 1)
# babynames %>%
#   ... ->
#   bn20

# 2)
# bn20 %>%
#   ... ->
#   bn20_sim

# 3)
# bn20 %>%


# 4)  
# bn20 %>%
  

# 5)
# babynames %>% 
#    ... -> 
#   bn_avg_len

bn_avg_len %>%
  ggplot() +
  geom_line(aes(x=year, y=avg_len, color=sex))
  
# 6)
babynames %>%
  select(-prop) %>%
  filter(year >= 2000) ->
  bn

# bn %>% 
#   ... -> 
#   bn_prev

n_mean <- mean(bn$n)

# bn_prev %>% 
#   ... ->
#   bn_trending
