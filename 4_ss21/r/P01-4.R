# Christian Merten, Josua Kugler

# create data --------------------------------------------------------
beta <- c(1, 2)
n <- 20
x <- runif(n)
X <- matrix(c(rep(1, n), x), ncol=2)
noise <- rnorm(n, mean=0, sd=0.5) # normally distributed noise
# sd = 0.5 => var = 0.5^2 = 0.25
y <- X %*% beta + noise # data from linear model with noise

least_squares_estimator <- function(X, y) {
  return( solve( t(X) %*% X )  %*% t(X) %*% y )
}

betahat <- least_squares_estimator(X, y)

# plot data ----------------------------------------------------------
plot(x, y)
abline(beta[1], beta[2], col="blue")
abline(betahat[1], betahat[2], col="red")
