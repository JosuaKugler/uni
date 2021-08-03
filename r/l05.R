std_runs <- c("100 metres", "200 metres", "400 metres", "800 metres",
"1,500 metres", "5,000 metres", "10,000 metres", "Marathon")
read_csv("repos/uni/r/athlete_events.csv") %>%
filter(Sport == "Athletics") %>%
select(Name, Sex, Age, Height, Weight, Year, Event, Medal) %>%
mutate(
Event = str_remove(Event, "Athletics Women's "),
Event = str_remove(Event, "Athletics Men's ")) %>%
filter(Event %in% std_runs) ->
athletes

athletes %>%
  pivot_wider(names_from = Medal, values_from = Medal) %>%
  mutate(across(c(Bronze, Gold, Silver), (function(x) !is.na(x)))) %>%
  group_by(Name) %>%
  summarize(across(c(Bronze, Gold, Silver), sum)) %>%
  arrange(desc(Gold), desc(Silver), desc(Bronze)) %>%
  transmute(Name, Gold, Silver, Bronze) -> medal_ranking

medal_color <- c(Bronze = "#6A3805", Silver = "#B4B4B4", Gold = "#AF9500")

athletes %>%
  filter(Event == "Marathon", Sex == "F", Year > 1980) ->
  d

aplot <- ggplot(d) + geom_boxplot(aes(x = Year, y = Age, group=Year))
aplot + geom_point(aes(x = Year, y = Age, color=medal_color[Medal], group=Year), na.rm = TRUE)


athletes %>%
  mutate(Event = factor(Event, levels=std_runs)) %>%
  filter(Year > 1900, Sex=="M") %>% 
  drop_na(Height) %>%
  group_by(Year, Event) %>%
  summarize(MeanHeight = mean(Height)) -> 
  d

ggplot(d, aes(x = Year, y = MeanHeight, color = Event)) +
  geom_point() +
  geom_smooth(se = FALSE) +
  ggtitle("Men's runs - mean across participants")

  