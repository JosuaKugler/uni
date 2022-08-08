# Christian Merten, Josua Kugler

lines <- read_lines("books.txt")

split <- function(char) str_split(char, ";|\\.")
remove_comments <- function(char) str_replace(char, "\\(.*\\)", "")
remove_rest <- function(char) str_replace_all(char, "\\s*[:punct:]*", "")
extract_category <- function(char) str_extract(char, "[A-Z]+")
extract_count <- function(char) str_extract(char, "\\d+")

lines <- lines %>% 
    sapply(split) %>% 
    unlist(use.names = FALSE) %>% 
    lapply(remove_comments) %>%
    lapply(remove_rest) %>%
    lapply(toupper)

category <- unlist(lapply(lines, extract_category))
count <- unlist(lapply(lines, extract_count))

data <- tibble(category, count)
data <- arrange(data, category)

books_of_category <- function(data, cat_let) {
    data %>% 
        filter(str_detect(category, cat_let)) %>%
        rowwise() %>%
        transmute(d = paste("We have",  count, "books of category",  category)) -> newdata
    unlist(newdata, use.names=FALSE)
}

print(books_of_category(data, "R"))