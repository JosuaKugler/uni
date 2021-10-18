library(R6)

GridPath <- R6Class("GridPath", list(
    path = NULL,
    dir = "",
    rotate_right = function() {
        if (self$dir == "N") self$dir <- "E"
        else if (self$dir == "E") self$dir <- "S"
        else if (self$dir == "S") self$dir <- "W"
        else if (self$dir == "W") self$dir <- "N"   
        invisible(self)
    },
    rotate_left = function() {
        if (self$dir == "N") self$dir <- "W"
        else if (self$dir == "E") self$dir <- "N"
        else if (self$dir == "S") self$dir <- "E"
        else if (self$dir == "W") self$dir <- "S" 
        invisible(self)  
    },
    move = function(n) {
        incr <- c(0,0)
        if (self$dir == "N") incr <- c(0,1)
        else if (self$dir == "E") incr <- c(1,0)
        else if (self$dir == "S") incr <- c(0,-1)
        else if (self$dir == "W") incr <- c(-1,0)
        for (i in 1:n) {
           self$path <- rbind(self$path, self$path[nrow(self$path), ] + incr)
        }
        invisible(self)
    },
    initialize = function(dir) {
        self$dir <- dir
        self$path <- matrix(c(0, 0), nrow=1)
    },
    print = function() {
      par(mar=c(0,0,0,0))
      p <- self$path
      plot(NA,      
           xlim=range(p[,1])+c(-1,1), 
           ylim=range(p[,2])+c(-1,1), 
           asp=1)
      rect(p[,1]-1, p[,2]-1, p[,1], p[,2], col='black')
      a <- p[nrow(p), ]
      b <- a + dir_to_delta[[self$dir]]
      arrows(a[1]-0.5, a[2]-0.5, b[1]-0.5, b[2]-0.5, col='red', lwd=2)
    }
))
gpath3 <- GridPath$new('N')
gpath3$move(7)$
rotate_right()$move(8)$
rotate_right()$move(7)$
rotate_right()$move(6)$
rotate_right()$move(5)
gpath3 # calls print(gpath3) calls print.R6(gpath3) calls gpath3$print()