# a) --------------------------------------------------------------------------

poly1 <- structure(
  list(sides = c(2, 2, 2, 2), angles = c(pi/3, 2*pi/3, pi/3, 2*pi/3)),
  class = c("Quadrilateral", "Polygon"))
poly2 <- structure(
  list(sides = c(3, 4, 3, 4), angles = rep(pi/2, 4)),
  class = c("Rectangle", "Quadrilateral", "Polygon"))
poly3 <- structure(
  list(sides = c(2, 2, 2), angles = rep(pi/3, 3)),
  class = c("Triangle", "Polygon"))
poly4 <- structure(
  list(sides = rep(1, 5), angles = rep(3/5*pi, 5)),
  class = c("Polygon"))

get_corners <- function(x) {
  n <- length(x$sides)
  if (n < 3) return(invisible(NULL))
  out <- matrix(ncol = 2, nrow = length(x$sides))
  direction <- c(1, 0)
  point <- c(0, 0)
  out[1, ] <- point
  for (i in 1:(n-1)) {
    point <- point + direction * x$sides[i]
    out[i+1, ] <- point
    a <- pi - x$angles[i]
    direction <- matrix(c(cos(a), sin(a), -sin(a), cos(a)), ncol=2) %*% direction
  }
  out
}

plot_polygon <- function(x) {
  corners <- get_corners(x)
  plot(range(corners[,1]), range(corners[,2]), type = 'n', axes=FALSE, ann=FALSE, asp=1)
  polygon(corners[,1], corners[,2], lwd = 3)
}

plot.Polygon <- function(polygon) {
  plot_polygon(polygon)
}

Rectangle <- function(w, h) {
  structure(
    list(sides = c(w,h,w,h), angles = rep(pi/2, 4)),
    class=c("Rectangle", "Quadrilateral", "Polygon"))
}

inner_angle <- function(a, b, c) {
  acos((b^2 + c^2 - a^2) / (2*b*c))
}
third_side <- function(a, b, angle) {
  sqrt(a^2 + b^2 - 2*a*b*cos(angle))
}

Triangle <- function(s1, s2, a1) {
  s3 <- third_side(s1, s2, a1)
  a2 <- inner_angle(s1, s2, s3)
  a3 <- pi - a2 - a1
  return(structure(list(
      sides = c(s1, s2, s3),
      angles = c(a1, a2, a3)), 
    class = c("Triangle", "Polygon")))
}

validate_Triangle <- function(obj) {
  if (!(all(0 <= obj$angles) & all(obj$angles < 2*pi))) {
    stop("invalid angles")
  }
  if (abs(sum(obj$angles) - pi) > 1e-14) {
    stop("sum of angles must be pi")
  }
  if (!all(0 < obj$sides)) {
    stop("sides must be nonnegative")
  }
  a <- obj$sides[1]
  b <- obj$sides[2]
  gamma <- obj$angles[1]
  c <- third_side(a, b, gamma)
  alpha <- inner_angle(a, b, c)
  if ((abs(c - obj$sides[3]) + abs(alpha - obj$angles[2])) > 1e-14)
    stop("sides and angles do not fit")
  invisible(obj)
}

circumference <- function(p) {
  UseMethod("circumference")
}

circumference.Polygon <- function(p) {
  sum(p[["sides"]])
}

area <- function(p) {
  UseMethod("area")
}

area.Triangle <- function(p) {
  sides <- p[["sides"]]
  angles <- p[["angles"]]
  height <- sin(angles[1])*sides[2]
  area <- height * sides[1] * 0.5
  area
}
