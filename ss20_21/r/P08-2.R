library(rlang)

validate_Prop <- function(p) {
    stopifnot(class(p) == "Prop")
    validate_Language(p)
}

validate_Language <- function(L) {
    #cat(c("call validate with ", expr_text(L)), "\n")
    isValid <- FALSE
    binary = c("`&`", "`|`", "`>=`", "`<=`", "`==`")
    unary = c("`!`", "`(`")
    props = c("A", "B", "C", "D", "E", "F", "G")
    
    if (class(L) == "name" || class(L) == "numeric") {
        if (L == 1 || L == 0) isValid <- TRUE #0 or 1 are valid Props
        else if (expr_text(L) %in% props) isValid <- TRUE #A-G are valid Props
    }
    else {
        first = expr_text(L[[1]])
        if (first %in% binary) {
            #print(c("binary operator: ", first))
            isValid <- (validate_Language(L[[2]]) & validate_Language(L[[3]]))#is valid if both arguments are valid   
        }
        else if (first %in% unary) {
            #print(c("unary operator: ", first))
            isValid <- validate_Language(L[[2]])
        }
    }
    #if (isValid) {
    #    cat(c("validate with ", expr_text(L), " returns True\n"))       
    #}
    #else cat(c("validate with ", expr_text(L), " returns False\n"))
    stopifnot(isValid)
    isValid
}

Prop <- function(L) {
    exp <- enexpr(L)
    print(typeof(exp))
    if (typeof(exp) == "symbol") {
        exp <- expr(((!!exp)))
        print(exp)
    }
    prop <- structure(exp, class="Prop")
    validate_Prop(prop)
    prop
}

ops_expr_str <- c("==", "<=", ">=", "&", "|", "!")
ops_print_str <- c("\u2194","\u2190","\u2192","\u2227","\u2228","\u00AC")

print.Prop <- function(prop) {
    text <- expr_text(unclass(prop))
    for (i in 1:length(ops_expr_str)) {
        str_replace_all(text, ops_expr_str[[i]], ops_print_str[[i]])
    }
    cat(text, "\n")
}

evaluate <- function(L, interpretation) {
    isTrue <- FALSE
    binary = c("`&`", "`|`", "`>=`", "`<=`", "`==`")
    unary = c("`!`", "`(`")
    props = c("A", "B", "C", "D", "E", "F", "G")

    print(L)
    if (class(L) == "name" | class(L) == "numeric") {
        if (L == 1) isTrue <- TRUE
        else if (L==0) isTrue <- FALSE
        else if (expr_text(L) %in% props) isTrue <- interpretation[[expr_text(L)]]
    }
    else {
        first = expr_text(L[[1]])
        if (first %in% binary) {
            if (first == "`>=`") {
                isTrue <- ( !evaluate(L[[2]], interpretation) | evaluate(L[[3]], interpretation) )
            }
            else if (first =="`<=`") {
                isTrue <- ( evaluate(L[[2]], interpretation) | !evaluate(L[[3]], interpretation) )
            }
            else {
                isTrue <- eval(L[[1]])(evaluate(L[[2]], interpretation), evaluate(L[[3]], interpretation) )   
            }
        }
        else if (first == "`!`") {
            isTrue <- !evaluate(L[[2]], interpretation)
        } else if (first == "`(`") {
            isTrue <- evaluate(L[[2]], interpretation)
        }
    }
    isTrue
}



interprete <- function (prop, vars, append=FALSE) {
    res = logical(0)
    for (i in 1:length(vars[[1]])) {
       res <- c(res, evaluate(prop, vars[i,]))
    }

    if (append) {
        name <- expr_text(unclass(prop))
        tb <- mutate(tb, !!name := res)
        tb
    }
    else res
}

all_symbols <- function(proposition) {
    proposition <- expr_text(unclass(proposition))
    props = c("A", "B", "C", "D", "E", "F", "G")
    symbols <- list()
    for (prop in props) {
        if (grepl( prop, proposition, fixed = TRUE))
        symbols <- c(symbols, prop)
    }
    symbols
}

get_vars <- function(symbols) {
    n <- length(symbols)
    vars <- tibble(!!symbols[[1]] := rep(c(0,1), each=2^(n-1)))
    if (n >= 2) {
        for (i in 2:n) {
            vars <- mutate(vars, !!symbols[[i]] := rep(rep(c(0,1), each=2^(n-i), times=2^(i-1))))
        }
    }
    vars
}


get_vars(all_symbols(Prop((A & (A >= B)) >= B)))

is_tautology <- function(prop) {
    vars <- get_vars(all_symbols(prop))
    res <- interprete(prop, vars, append=FALSE)
    all(res)
}