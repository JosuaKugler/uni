find_primes <- function(n) {
  primes <- c(2)
  cnt <- 3
  while (length(primes) < n) {
    #print(primes)
    isprime <- TRUE
    for (prime in primes[primes < sqrt(cnt) +1])  {
      if (cnt %% prime == 0) {isprime <- FALSE; break}
    }
    if (isprime) primes <- c(primes, cnt)
    cnt <- cnt + 1
  }
  return(primes)
}