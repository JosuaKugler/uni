# Christian Merten, Josua Kugler

x <- c(1.3, .5, 42, -8e-5)
x[1:4] <- x[4:1]
x[x < 1] <- -2
sum(x^2)
q <- 1:100
q[q %%2 == 0] <- 0
