#1
babynames::babynames %>% filter(year >= 2000) %>% group_by(name, sex) %>% summarize(n = sum(n)) %>% ungroup() -> bn20

#2
bn20 %>% filter(sex == "F") -> girls
bn20 %>% filter(sex == "M") -> boys
inner_join(boys, girls, by="name") %>% 
 filter(n.x + n.y > 1e5) %>% arrange(abs(n.x - n.y) / (n.x + n.y)) -> bn20_sim

#3
bn20 %>% mutate(name_length = nchar(name)) %>% 
 group_by(name_length) %>% 
 summarize(n = sum(n)) %>% 
 select(name_length, n) -> bn20_nl

#4
bn20 %>% filter(nchar(name) == 2) %>% arrange(desc(n)) -> twoletters
#print(twoletters)

#5
babynames::babynames %>% group_by(year, sex) %>% summarize(avg_len = mean(nchar(name))) %>% select(year, sex, avg_len) -> bn_avg_len
bn_avg_len %>%
  ggplot() +
  geom_line(aes(x=year, y=avg_len, color=sex))

#6
babynames::babynames %>%
  select(-prop) %>%
  filter(year >= 2000) ->
  bn



bn %>% 
  mutate(year = year + 1) %>%
  left_join(bn, by=c('year', 'sex', 'name')) -> 
  bn_prev
#print(bn_prev)

n_mean <- mean(bn$n)

 bn_prev %>% 
   mutate(s_incr = ((n.x - n.y) / (n.y + n_mean))) %>% 
   group_by(year, sex)  %>% 
   filter(rank(desc(s_incr)) <= 3) %>%
   select(year, sex, name, s_incr) -> 
   bn_trending
print(bn_trending)