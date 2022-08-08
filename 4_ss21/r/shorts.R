library(tidyverse)
library(rlang)
library(sloop) # for OOP
library(nycflights13) # for examples

flights2 <- flights %>% select(year:day, hour, tailnum, carrier, origin, dest)
airports2 <- airports %>% select(faa, name)
stocks <- tibble(year = sample(2011:2015, rep=T, 8),
                 qtr = sample(1:4, rep=T, 8),
                 return = c(1.88, 0.59, 0.35, NA, 0.92, NA, 2.66, 3.55)) %>% unique

# definitionen

students <- tibble(
    name = c("Alice", "Bob", "Carl", "Dave", "Eve"),
    grade = c(1, 2, 2, 3, 1)
)

info <- tibble(
    grade = 3:1,
    desc = c("Poor", "Good", "Excellent"),
    fail = c(T, F, F)
)

# Sequenzen

1:42
0.5:-3.9

seq(0, 3, by=0.75)
seq(0.5, -3.9, len=5)

rep(c(0,2), times=5)
rep(c(0,2), each=5)

cumsum(1:10)

# Indexing

x <- 21:42

x[c(3, 7, 6, 7.9)] # position
x[-c(1, 3, 5)] # ausschluss von angegebenen positionen

x[FALSE] # integer(0)

seq_along(x[FALSE]) # zuverlässiger
1:length(x[FALSE])

x[] # nichts: alles wird zurückgegeben
x[x %% 2 == 0] # wahrheitswerte
x[(seq_along(x)-1) %% 5 == 0]
x[c(T, F)] # jedes zweite, da T, F recycled wird

y <- structure(x, names=letters[seq_along(x)])

y[c("a", "j", "e", "e", "z")] # namen
y[setdiff(names(y), c("a", "e", "z"))] # analogon zu negativen zahlen

m <- outer(1:5, 1:4, paste, sep=",")
m[2:7] # indizierung auf zugrundeliegendem vektor
m[c(4,3), c(1,4,3)] # indizierung nach dimensionen

m[1,, drop=FALSE] # dimensionsvereinfachung verhindern

select <- rbind(
    c(1, 1),
    c(3, 1),
    c(2, 4)
)

m[select] # matrix: jede zeile gibt eine koordinatenkombination an

m <- matrix(1:9, nrow=3)

which(m %% 2 == 0, arr.ind=F) # gibt koordinaten der TRUE values
arrayInd(which(m %% 2 == 0), dim(m)) # wandelt vektor koordinaten in koordinatenmatrix um

## tibbles

tb <- tibble(x = 1:3, y = 3:1, z = letters[1:3])

tb[tb$x == 2, ] # wie bei matrizen
tb[c("x", "z")] # wie bei listen, gibt spalten x und z
tb[tb$x == 2, "z", drop=T] # drop um tibble struktur zu vergessen

## Einzelne Elemente

x <- list(bla=1:3, blub=list("fritz", "hans"), 4:6)
x[1]  # liste mit einem element
x[[1]] # element der liste

x[[c(2, 1)]] # verschachtelte indizierung
x[["blub"]][[1]] # das selbe

x <- 1:10
x[[3]] # geht auch fuer atomare vektoren
m[[2, 3]] # bei arrays mit entsprechenden dimensionen

key <- "bla"
x$bla
x[[key]]

options(warnPartialMatchDollar=T)
x$blu # partial matching von "blub"

## Fehlende Indizes

x <- 1:3
x[4] # NA
x[[4]] # Error

lst <- as.list(x)

lst[4] # NA
lst[[4]] # Error

names(x) <- letters[1:3]
names(lst) <- letters[1:3]

x[["d"]] # Error, ABER:
lst[["d"]] # NULL
lst$d # NULL

## assignment

x <- 1:5
x[c(1, 2, NA)] <- c(1,2) # Error
x[c(1, 2, NA)] <- 1 # funktioniert

lst <- list(abc=1)

lst$ab # partial matching
lst$ab <- 2 # kein partial matching, neuer eintrag

x <- 1:9
x[1:6] <- 11:13 # recycling

x <- 7
x[1e5] <- 5 # funktioniert, out of bound assignment vergroessert vektor

tb <- tibble(x=2^(1:4), y=c("1.2", "2.3", "3.4", "4.2"))
tb[] <- lapply(tb, as.integer) # erhaelt tibble struktur, weil subsetting assignment

lst["abc"] <- NULL # element aus liste entfernen
lst["ab"] <- list(NULL) # NULL liste einfügen

## helpers for indexing

### match and merge

id <- match(students$grade, info$grade) # find index of entries in students$grade in info$grade
cbind(students, info[id, -1])

merge(students, info, by.x="grade", by.y="grade") # kurzform

### sorting

x <- runif(100, min=-40, max=52)
order(x) # x[order(x)] = sort(x)
sort(x) # sortiert
rank(x) # ranked alle elemente aufsteigend

students[order(students$grade), ] # sortiere nach noten

# Missing values

## NULL
c() # NULL
c(typeof(NULL), length(NULL)) # NULL, 0

## BASE_TYPE(0)
c(typeof(integer(0)), length(integer(0)))

## NA...
c(typeof(NA_integer_), length(NA)) # laenge 1 und entsprechenden typ

## indexing
x <- 1:3

x[0]
x[NULL]

x[]

x[NA]

x[NA_integer_]

## pruefen

x <- list(1, NA, NaN, NA_real_, NA_integer_, NA_character_)

is.na(x)
is.null(x)

is.nan(NaN)

## vergleich
1:3 == NA
NA == NA
identical(NA, NA)
NULL == NULL
identical(NULL, NULL)

# Plots

x <- seq(-3, 3, len=100)
plot(x, sin(x),
     type="l",
     main="Titel",
     xlab="x-Achse",
     ylab="y-Achse",
     xlim=c(-2, 2),
     ylim=c(-1, 1),
     lwd=3,
     lty=2,
     col="cyan")
points(x, sin(x), pch=3, col="red")

hist(rnorm(1000))
barplot(1:5)

x <- seq(0, 1, len=100)
y <- seq(0, pi, len=100)
f <- function(x,y) x^2 - sin(y)
outer(x,y,f)
contour(x,y,outer(x,y,f))

# Randomness

## random deviates

set.seed(42)

rnorm(8, mean=12, sd=3)
rbinom(42, size=13, prob=0.45)
runif(10, min=-13, max=26)

# Printing 

print(1:10)

cat("3 + 5 ist", 3+5, "\n", sep=" ")
paste("3 + 5 ist", 3+5, "\n", sep=" ")

as.character(pi)

sprintf("Eine Zufallszahl aus der %s ist %.2f.", "Normalverteilung", rnorm(1))

# Listen
lst <- list(1:3,
            "a",
            c(T, F, T),
            runif(10),
            list(1, "b"),
            sum)
identical(lst[[c(5,2)]], "b")
str(lst)
c(typeof(lst), class(lst), length(lst))

is.vector(lst)
is.list(lst)

unlist(list(1:10))
as.list(1:10)

lst[2]
lst[[2]]
lst[[2]] <- NULL
lst[1] <- list(NULL)

str(c(list(), letters[1:5], 42))

# Matrizen

n <- 1e3
m1 <- matrix(rnorm(n^2), nrow=n)
m2 <- matrix(rnorm(n^2), nrow=n)

m <- matrix(1:16, nrow=4, byrow=F)
m[2,2] <- 0
m[1,1] <- 0

dim(m)
length(m)
nrow(m)
ncol(m)
rowSums(m)
colSums(m)
det(m)

r <- sample(4)
y <- solve(m, r)
m %*% y

solve(m) # inverse
qr(m) # qr zerlegung
chol(m) # cholesky zerlegung
svd(m) # singulaerwertzerlegung
eigen(m) # eigenwerte und vektoren

m1 + m2
m1 * m2 # elementweise mult
m1 %*% m2 # matrix mult
t(m1) # transpose
aperm(m1) # auf arrays verallgemeinert

cbind(m, 1:4)
rbind(m, 1:4)

## allgemeiner

x <- 1:6
attr(x, "dim") <- c(2,3)
dim(x) <- c(2,3,1)
array(1:16, dim=c(2,2,2))

matrix(list("a", 1, T, list()),
       nrow=2,
       dimnames=list(Zeilen=NULL, Spalten=c("hi", "fritz")))
rownames(x) <- letters[1:2]
colnames(x) <- LETTERS[1:3]

NROW(1:12) == nrow(matrix(1:12)) # aber nrow(1:12) ist NULL

# Tibbles

tb <- tibble(x=1:3, y=letters[1:3])

as_tibble %$% list(x=1:3, y=letters[1:3])
as_tibble %$% matrix(1:4, ncol=2, dimnames=list(NULL, c("A", "B")))

add_column(tb, z=-1:1, w = 0)
add_row(tb, x=4:5, y=letters[4:5], .before=2)

head(tb, 2)
tail(tb, 1)

dplyr::bind_rows(tb, tibble(x=42:45, y="E"))
dplyr::bind_cols(tb, tibble(e=42:44, d="E"))

options(tibble.print_min=6,    # makes output more compact
        tibble.print_max=6,
        tibble.max_etra_cols=0)

readr::read_csv("bla.csv")

## dplyr verbes

filter(flights, (arr_delay - dep_delay) < -60, dep_delay > 30) # zeilen filtern

arrange(flights, desc(dep_delay)) # zeilen sortieren

nms <- c("month", "year")
select(flights, 5, 5, carrier, "origin", arr_time:flight, -flight,
       all_of(nms), -any_of(nms)) # position select
select(flights, # condition select
       where(is.character) | contains("delay"),
       fritz = ends_with("delay"),
       -starts_with("dep_"),
       tag = contains("day"), # no regex
       matches("^y"), # regex
       everything()) # alle restlichen spalten (umsortierung)

rename(flights, monat = month, tag = day)

mutate(airlines, name_length = nchar(name), carrier=NULL)
transmute(flights, carrier, gain = dep_delay - arr_delay)

summarize(flights, total_delay = sum(abs(dep_delay), na.rm = T),
                   delay_range = range(dep_delay, na.rm = T),
                   count_origin = n_distinct(origin))

count(flights, year, month, day, origin, sort=T) # group by variables and summarize n()

group_by(flights, month) %>% summarize(delay_mean = mean(dep_delay, na.rm=T))

group_by(flights, month, carrier, dep_time) %>% select(group_cols())

group_by(flights, carrier) %>% filter(sum(distance, na.rm = T) > 5e7)

group_by(flights, carrier) %>% mutate(prop = distance / sum(distance, na.rm=T))

summarize(flights,
          across(where(is.numeric) & !(year | month | day | hour),
                 list(min = min,max = max,mean=mean),
                 na.rm = T,
                 .names = "{fn}.{col}"))

mutate(flights, across(dep_time:arr_delay, partial(`*`, 2)))

filter(flights, across(where(is.numeric) & !flight & !year, partial(`>`, 700) %.% abs))

rowwise(flights) %>% mutate(m = mean(c_across(dep_time:arr_time)), .keep="used") # vermeiden

## non standard evaluation austricksen

tobefiltered <- "dep_delay"
filter(flights, .data[[tobefiltered]] > +120)

## join und co.

left_join(flights2, airports2, by=c("origin" = "faa")) %>%
    left_join(airports2, by=c("dest" = "faa"), suffix=c("_origin", "_dest"))

right_join(flights2, airports2, by=c("dest" = "faa")) # priorisiert rechts
inner_join(flights2, airports2, by=c("dest" = "faa")) # keins na
full_join(flights2, airports2, by=c("dest" = "faa")) # egal

top_dest <- count(flights, dest, sort=T) %>% head(10)
semi_join(flights, top_dest) # only keep rows that join with row in top_dest
anti_join(flights, top_dest) # only keep rows that DO NOT join with row in top dest

## tidy tables

pivot_longer(table4a, cols=where(is.numeric), names_to="year", values_to="cases")

pivot_wider(table2, names_from=type, values_from=count)

separate(table3, rate, into = c("cases", "population"), sep = "/", convert = T)

extract(table3, rate, into = c("cases", "population"), regex = "^(.*?)/(.*?)$", convert = T)

unite(table5, "year", century, year, sep="") %>% mutate(year = as.integer(year))

## fix missing values

complete(stocks, year, qtr) # make implicit missing values explicit

drop_na(stocks)

replace_na(stocks, list(return = 42))

mutate(stocks, return = na_if(return, "my custom na"))

# Apply und co.

f <- function(x) sprintf("a random number is %.2f which is %.3f probable", x, pnorm(x))

lapply(rnorm(100), f)

sapply(rnorm(100), f)
simplify2array(lapply(rnorm(100), f))

replicate(5, runif(10), simplify = TRUE)

mapply(`+`, 1:100, 1:100)

m <- matrix(1:12, nrow=3)
dimnames(m) <- list(cols=NULL, rows=NULL)
apply(m, 1, mean)

a <- array(1:24, dim=2:4, dimnames=list(x1=NULL, x2=NULL, x3=NULL))
apply(a, c(1,2), range)

outer(1:3, 1:5, `*`)

funs <- list(mean=mean, median=median, var=var)
X <- replicate(5, runif(sample(20, 1)), simplify=F)

outer(X, funs, function(x_list, f_list) mapply(function(f, x) f(x), f_list, x_list))

## mathematische funktionale

integrate(sin, 0, pi)

optimize(sin, c(0, 2*pi), maximum=T)

x <- seq(0, 2*pi, len=10)
f_lin <- approxfun(x, sin(x))
f_cub <- splinefun(x, sin(x))

## funktionsoperatoren

fib <- function(n) {
    if (n<2) return(1)
    fib(n-2) + fib(n-1)
}

fib <- memoise::memoise(fib)

capture.output(print("hi"))

sample2 <- Vectorize(sample, "size")

# types

sapply(list(NULL,
            TRUE, # -- basetypes --
            1L,
            1,
            "",
            raw(3), 
            1+3i, # ^^ basetypes ^^
            list(),
            expr(a),
            expr(1+2),
            expression(1+2),
            env(),
            mean,
            sin,
            `[`),
       typeof) %>% unique()

sapply(list(NULL,
            TRUE, # -- basetypes --
            1L,
            1,
            "",
            raw(3), 
            1+3i, # ^^ basetypes ^^
            list(),
            expr(a),
            expr(1+2),
            expression(1+2),
            env(),
            mean,
            tibble(), # tidyverse
            data.frame(),
            matrix(),
            array(),
            factor(),
            Sys.Date(),
            Sys.time(),
            proc.time()),
       class) %>% unique()

## basetypes
misc <- list(T, 1:3, pi, "hi", 1+3i, raw(4))
sapply(misc, typeof)

is.numeric(c(0.3, 3)) # TRUE
is.integer(0.3) # FALSE

is.atomic(list()) # FALSE

str(list(logical(3), integer(3), double(3), character(3), complex(3), raw(3)))

### integer

c(42L, NA_integer_, 1:3, .Machine$integer.max)

### double
c(3, 4.2, pi, 1e4, .Machine$xmax, Inf, NaN, NA_real_)

c(1/0, -1/0, 0/0, 1/Inf)

# numeric synonym zu double in class(), as_numeric(), numeric(n), print(), str()
# ABER:
is.numeric(1L) # TRUE

# Not available type fuer double ist:
NA_real_

### character

"bla 'einca' asdf"
cat('asdf "as" asdf \\ hi\n')
x <- c("ä", "Hallo", "", NA_character_, "\n")
nchar(x)
cat(r"(\n \ )", "\n")

letters
LETTERS
month.name
month.abb

## coercion

as.double("2.2")
c(TRUE, 15)
c(TRUE, 1L, 1, "eins")
c(c(TRUE, 1L), 1, "eins")

# attributes

x <- seq(-2, 3, len=42)

attr(x, "asdf") <- c(1,2)
structure(x, "asdf" = c(1,2))
attributes(x)$asdf <- c(1,2) # geht auch wenn x <- NULL

attr(x, "asdf")
attributes(x)$asdf

identical(x, seq(-2, 3, len=42))

## names

x <- 1:4
attr(x, "names") <- letters[1:4]
names(x) <- letters[1:4]
x <- c("a"=1, "b"=2, "c"=3, "d"=4)

unname(x) # does not modify x
names(x) <- NULL # modifies x

# S3 Objekte / Klassen

x <- runif(100)
attr(x, "class") <- "Toller Hecht"
class(x) <- "Toller Hecht"

unclass(x) # does not modify x
class(x) <- NULL # modifies x

## implizite klassen
# falls class nicht gesetzt -> implizite klasse: matrix, array, function, numeric oder typeof(x)

## spezielle S3 Objekte

### factors
# integer vektoren mit class = factor und attribut levels

x <- sample(13, 100, rep=T)
x_factor <- factor(letters[x*2])

typeof(x_factor) # integer
class(x_factor) # factor
str(attributes(x_factor)) # levels

table(x_factor) # summarize factor

x_factor[c(3,7), drop = TRUE] # wegwerfen der anderen level

### Date
# double vektoren mit class = Date

Sys.Date()
str(attributes(Sys.Date()))

unclass(Sys.Date()) # anzahl tage seit 1.1.1970

### POSIXct
# double vektoren mit class = c(POSIXct, POSIXt)

Sys.time()
str(attributes(Sys.time()))

unclass(Sys.time()) # anzahl sekunden seit 1.1.1970

### proc_time
# double vektor der länge 5 mit class = proc_time

proc.time()
str(attributes(proc.time())) # in sekunden, genauer:
# user: beanspruchung der CPU durch R
# system: beanspruchung der CPU durch betriebssystem im auftrag von R
# elapsed: gesamt

str(unclass(proc.time()))

system.time({
    data <- runif(1e6)
    stats <- c(mean(data), var(data))
}) # gibt auch proc_time objekt

### tibble
# data.frame mit class = c(tbl_df, tbl). ein data.frame ist wiederum eine liste seiner spalten

tb <- tibble(x = 1:3, y = letters[3:1])
str(attributes(tb))
typeof(tb)

str(unclass(tb))

tb$x
tb$z <- matrix(1:15, nrow=3) # kann matrizen
tb$e <- tibble(a=sample(100, 3), b=rnorm(3)) # und tibbles

as_tibble(as.matrix(tb[,-2]))

# funktionen

## pipe

pi %>% `*`(2,.) %>% sin %>% abs %>% `<`(., 1e-14) -> res

## eigene operatoren

`%.%` <- function(f, g) function(...) f(g(...))
`%$%` <- function(f, x) f(x)

str %.% attributes %$% tibble (a = sample(100, 3), b = rnorm(3))

## ersetzungsfunktionen

`modify<-` <- function(x, position, value) {
    x[position] <- value
    x
}

x <- 1:10
modify(x, 3) <- 42L

modify(names(x), 3) <- "hi"

## do.call

do.call(mean, list(x=sample(100), na.rm=T))

## funktionstypen
# funktionen haben class = function, aber

c(typeof(mean), typeof(sum), typeof(`[`)) # builtin und special sind primitive, alle anderen closure

f <- function(x) {
    # kommentar
    10
}
formals(f)
body(f)
environment(f)

formals(args(sum)) # argument liste primitiver funktionen

## lazy evaluation

f(stop("hi")) # argument wird nicht ausgewertet

## default arguments

f <- function(x = y*2, y = 1, z = a+b, e=ls()) { # defaults refer to other arguments
    a <- 10
    b <- 100
    print(e)
    cat(sprintf("missing x: %s, missing y: %s\n", missing(x), missing(y)))
    c(x, y, z)
}
f(x=3, e=ls()) # ls is evaluated in caller env
f() # ls is evaluated in execution env

## dot-dot-dot

f <- function(x, ...) { # potentially infinite additional parameters
    str(list(first = ..1, third = ..3)) # access additional parameters
    mean(unlist(list(...)))
}
f(1,2,3,42)

## return values

invisible(42) # hide return value

f <- function(x) {
    print("Hello")
    on.exit(print(1))
    on.exit(print(2), add = TRUE, after = FALSE)
    if (x) return(10) else stop("Error")
    print("Well...")
}

f(TRUE)
f(FALSE)

# strings

## basics

str_length(c("a", "abs", NA, ""))

str_c("prefix", LETTERS[sample(26, 3, rep=T)], "suffix", # vektorisiert in allen args
      sep = "-",
      collapse = " * ")

x <- "Fritz Walter   ist   toll.   "
str_sub(x, start=3, end=5)
str_sub(x, end=-5) # only drop last 4 chars
str_sub(x, start=7, end=12) <- "Hasl"

str_trim(x) # remove whitespace in beginning and end

str_squish(x) # remove repeated whitespace inside

str_to_upper(x)

str_to_lower(x)

str_to_title(x)

str_dup(c("a", "bB"), 2:5)

## formatting

str_glue("3 * pi = {format(3*pi, digits=3)} und das ist {'{toll}'}, weil {x}.") # auch vektorisiert

str_glue_data(tibble(x=1:3, y=letters[1:3]), "Es ist x={x} <-> y={y}")

## regex

str_detect(x, "[aeiou]") # alles vektorisiert

str_subset(letters, "[aeiou]") # recycling

str_which(letters, "[aeiou]")

str_count(letters, letters[1:13])

str_extract(c(x, "Stopp"), ".t")
str_extract_all(c(x, "Stopp"), ".t")

str_locate(c(x, "Stopp"), ".t")
str_locate_all(c(x, "Stopp"), ".t")

str_split(c("Kaffee,Klettern_Sport.Wald", "Bla.Furz"), "[,_\\.]")
str_split("Fritz.kann.kochen", fixed(".K", ignore_case=T))

str_match("Fritz.kann.kochen", "(.)\\.(.)") # gibt gruppen aus
str_match_all("Fritz.kann.kochen", "(.)\\.(.)")

str_replace("Fritz.kann.kochen", "(.)\\.(.)", "\\2$\\1") # use \1.. in replacement to access groups
str_replace_all("Fritz.kann.kochen", "(.)\\.(.)", "\\2$\\1")

# environments

e1 <- env(a = FALSE, b = "a", c = 2.3, d = 1:3)
c(class(e1), typeof(e1), length(e1))

e2 <- e1 # environments werden per referenz uebergeben
e2$a = T
e1$a
identical(e1, e2)
e1$d <- e1

## env infos

env_print(e1)

env_names(e1)
env_names(empty_env()) # leere umgebung
env_names(global_env()) # globale umgebung (konsole)

env_label(global_env())
env_label(e1)
env_label(current_env()) # aktuelle umgebung

e2 <- env(e1, z = 42)
env_parent(e1)
env_parent(e2)
env_parent(empty_env()) # error, leere umgebung hat kein parent

env_parents(e1)
env_parents(e2)

## manipulate environments

env_bind(e1, z=69, asdf="fritz")

env_get(e2, "b", inherit=T) # inherit = T search in parent env if not found here

str(env_get_list(e1, c("a", "b", "d")))

env_has(e2, c("b", "z"), inherit=F)

env_unbind(e2, c("b", "z"))

## function environments

a <- 42
f <- function(x) x + a

env_label(current_env())
env_label(fn_env(f))
fn_env(f) <- e1

g <- function(x) {
    print(env_label(current_env()))
    function(y) x+y
}

h <- g(3)

## lazy evaluation

x <- 1
y <- 2
env_bind_lazy(current_env(), v = c(x,y)) # creates promise v pointing to c(x,y)
x <- 5
v

# OOP

# sloop inspectino

otype(tibble(x=1:3, y=3:1))

s3_class(matrix(1:10, nrow=2))

ftype(print)
ftype(apply)

s3_methods_generic("elapse_time")

inherits(tibble(x=1:12), "tbl_df")

s3_dispatch(print(tibble(x=1:12)))

## S3

tyrion <- structure(list(name = "Tyrion", age = 42), class = c("Noble", "Person"))

print.Person <- function(p) cat(str_glue("{p$name} ({p$age})"), "\n")

elapse_time <- function(obj, time) { # generic function
    UseMethod("elapse_time")
}

elapse_time.Person <- function(p, time) { # implementierte methode
    p$age <- p$age + time
    p
}

elapse_time.default <- function(o, t) {
    stop(str_glue("Cannot elapse time for object of class {class(o)}."))
}

elapse_time.Noble <- function(p, time) {
    cat("A noble person does not age\n") # actually wrong
    NextMethod() # go to next method in dispatch list
}

### constructor helpers

new_Person <- function(x, subclass = NULL) {
    stopifnot("Person must be a list" = is.list(x))
    structure(x, class=c(subclass, "Person"))
}

new_Noble <- function(x, subclass = NULL) {
    new_Person(x, subclass=c(subclass, "Noble"))
}

validate_Person <- function(p) {
    if(!inherits(p, "Person")) stop("Object must inherit Person")
    invisible(p)
}

Person <- function(name, age) {
    p <- new_Person(list(name = name, age = age))
    validate_Person(p)
    p
}

### coercion

as_Person <- function(x, ...) UseMethod("as_Person")
as_Person.Person <- `(`
as_Person.character <- function(name, age) Person(name, age)

### internal generics

c.numeric <- function(...) return("c: numeric")
c(42) # does not use c.numeric because class is implicit
c(structure(42, class="numeric"))

### group generics

units <- c(kg = 1, g = 1e-3, mg = 1e-6)

m <- structure(1:12, class="Mass", unit="kg")
m2 <- structure(350, class="Mass", unit="g")

print.Mass <- function(x) print(str_glue("{x} {attr(x, 'unit')}"))

Summary.Mass <- function(x, ...) {
    m <- NextMethod()
    structure(m, class="Mass", unit=attr(x, "unit"))
}

### double dispatch

`+.Person` <- function(x, y) print("+ on person")

`+.Mass` <- function(x, y) {
    a <- unclass(x)
    b <- unclass(y)
    structure(a * units[[attr(x, "unit")]] + b * units[[attr(y, "unit")]], class="Mass",
              unit = "kg")
}

m + m2
m + tyrion # error because of incompatible methods
m + 1 # error in +.Mass

## S4

.Person <- setClass("Person", slots = c(name = "character", age = "numeric"))
.Employee <- setClass("Employee", contains = "Person", slots = c(boss = "Person"))

Person <- function(name, age) {
    stopifnot(length(name) == 1 && length(age))
    .Person(name = name, age = age)
}

Employee <- function(name, age, boss) {
    p <- Person(name = name, age = age)
    .Employee(p, boss = boss)
}

tyrion <- Person(name = "Tyrion", age = 42)
peter <- Employee(name = "Peter", age = 13, boss = tyrion)

tyrion@age <- tyrion@age + 1
tyrion@name <- 42

slotNames(tyrion)

is(tyrion)
is(peter, "Person")

typeof(tyrion)
class(tyrion)

### generics

setGeneric("laugh", function(x) standardGeneric("laugh"))

setMethod("laugh", "Person", function(x) {
    cat(str_glue("{x@name} laughs out loudly."), "\n")
})
setMethod("laugh", "Employee", function(x) {
    cat(str_glue("{x@name} laughs out shyly."), "\n")
})

formals(getGeneric("show"))

setMethod("show", "Person", function(object) {
    cat(str_glue("{object@name} ({object@age})"), "\n")
})
setMethod("show", "Employee", function(object) {
    cat(str_glue("{object@name} ({object@age}) an Employee"), "\n")
})

### getters and setters

setGeneric("name", function(x) standardGeneric("name"))
setMethod("name", "Person", function(x) x@name)
setGeneric("name<-", function(x, value) standardGeneric("name<-"))
setMethod("name<-", "Person", function(x, value) {
    x@name <- value
    x
})

### coercion

as(peter, "Person") # default
emp <- as(tyrion, "Employee") # default
emp@boss

setAs("Person", "Employee", function(from) {
    stop("Can not coerce a Person to an Employee")
})

### introspection

s4_methods_generic("laugh")

s4_methods_class("Person")

### inheriting S3 classes

RangedNumeric <- setClass(
    "RangedNumeric",
    contains = "numeric",
    slots = c(min = "numeric", max = "numeric")
)

rn <- RangedNumeric(1:10, min=1, max=10)
rn@.Data # access underlying S3 or implicite class

# meta programming

## basics

x <- expr(3+5*y)
y <- 12
eval(x)

str(exprs(name = 1+2, f(x), sin(42)))
typeof(expr(1))

c(typeof(expr(variable)), class(expr(variable))) # symbol name
c(typeof(expr(sin(x))), class(expr(sin(x)))) # language call

lobstr::ast(f(g(x, h(), 1), x))
a <- expr(f(g(x, h(), 1), x))
str(as.list(a))
a[[2]][[3]][[1]]
a[[c(2,3,1)]] <- expr(q)

expr_text(a)

identical(parse_expr("f(g(x, q(), 1), x)"), a)

parse_exprs("x <- 4\nprint(x+5)") # parse multiple expressions as expr list

## arguments

f <- function(x, ...) {
    print(enexpr(x)) # does not use promise
    force(x)
    print(enexpr(x))
    enexprs(...)
}
f(3+4, sin(pi), 0/0)

## evaluation

x <- y <- 3
eval(expr(x+y), envir = env(`+` = `-`))

## quosures

f <- function() {
    x <- 10
    quo(1+x)
}
x <- 100
q <- f()

eval(quo_get_expr(q)) # evaluates in current environment
eval_tidy(q) # evaluates in captured environment

expr_text(quo(1+2)) # prints weird ~ in front
quo_text(quo(1+2))

foo <- function(x, y) {
    z <- 1
    x <- enexpr(x)
    y <- enquo(y)
    c(eval(x), eval_tidy(y))
}
z <- 100
foo(z*2, z*2) # 2 200 (x is evaluated in execution env of foo, y is evaluated in global env)

eval_tidy(expr(a <- 42)) # does not actually assign
eval(expr(a <- 42)) # does assign

x <- 1
eval_tidy(quo(x+y), list(y = 100))

## tidy eval framework

### bang bang

a <- expr(f(x))
expr(1 + !!a) # Bang-Bang Operator

lobstr::ast(expr(f(x)))
lobstr::ast(!!expr(f(x)))

### big bang
x <- 1:3
str(exprs(!!x))
str(exprs(!!!x)) # big bang

### walrus
name <- "asdf"
tibble(!!name := 1:5)

### pronouns

y <- 4
tb <- tibble(x = 1:3, y=3:1)
eval_tidy(quo(.data$y + .env$y*10), tb) # .data datamask, .env environment

### geschachtelte quosures

x <- 1
lobstr::ast(7 + !!(x+2))
lobstr::ast(7 + !!quo(x+2)) # unwraps quosure and puts it in main quosure

y <- 1
create_q <- function() {
    y <- 10
    quo(y)
}
qu <- create_q()
eval_tidy(quo(y + !!qu))

## applications

var <- quo(y)
tb <- tibble(x=1:5, y = 5:1)
eval_tidy(quo(!!var == 4), tb)

var <- "y"
eval_tidy(quo(.data[[var]] == 4), tb)

mysummarise <- function(tb, mean_var, ...) {
    qg <- enquos(...)
    qm <- enquo(mean_var)
    mean_name <- str_glue("mean_{quo_name(qm)}")
    tb %>%
        group_by(!!!qg) %>%
        summarise(!!mean_name := mean(!!qm))
}

filterx <- function(var) {
    filter2(tb, {{var}} == 1)
}

source2 <- function(path) {
    l <- readLines(path)
    exs <- lapply(l, parse_expr)
    model <- env(base_env())
    for (ex in exs)
        res <- eval_tidy(ex, model)
    res
}
source2("test.R")

namedlist <- function(...) {
    qs <- enquos(...)
    l <- list(...)
    names(l) <- lapply(qs, quo_text)
    l
}
namedlist(letters, 1:10)

filter2 <- function(tb, ex) {
    ex <- enquo(ex)
    tb[eval_tidy(ex, tb), ]
}

mkInfix <- function(f) {
    f <- enexpr(f)
    e <- caller_env()
    name <- expr_text(f)
    e[[str_glue("%{name}%")]] <- eval(f)
}

`%->%` <- function(x, y) {
    y <- enexpr(y)
    e <- caller_env()
    e[[expr_text(y)]] <- x
    invisible(x)
}

# conditions

stop("Error!")
stopifnot("Error!" = 3 == 4)

warning("Warning!")
warnings()
last.warning

message("Message!")

{
    try(stop("hi"), silent = FALSE)
    print("hallo")
}

suppressWarnings({warning("warn"); message("msg")})
suppressMessages({warning("warn"); message("msg")})

tryCatch(
    message = msgHandler,
    warning = warnHandler,
    error = errorHandler,
    expr = {

    }
)

withCallingHandlers(
    message = msgHandler,
    warning = warnHandler,
    error = errorHandler,
    expr = {

    }
)
