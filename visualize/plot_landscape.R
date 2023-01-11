library(ggplot2)
library(reshape2)

para <- as.numeric(read.table("parameters.txt"))

width <- para[1]
depth <- para[2]
num_time_units <- para[3]

data <- read.table("landscape_change.txt")
data2 <- as.matrix(read.table("lab_positions.txt"))

max_height <- max(data[,-1], 35)

xs <- numeric(0)
ys <- numeric(0)

for(i in 0:(width-1)){
  for(j in 0:(depth-1)){
    xs <- c(xs, i)
    ys <- c(ys, j)
  }
}

if(dir.exists("pic")){
  list <- list.files("pic")
  for(i in list){
    file.remove(paste("pic/", i, sep=""))
  }
}else{
  dir.create("pic")
}

for(row in 1:(num_time_units+1)){
  xpos <- numeric(0)
  ypos <- numeric(0)
  zpos <- numeric(0)
  
  for(i in 1:((dim(data2)[2]-1)/3)){
    xpos <- c(xpos, data2[row, 3*i-1])
    ypos <- c(ypos, data2[row, 3*i+0])
    zpos <- c(zpos, data2[row, 3*i+1])
  }
  
  df <- data.frame(x=xs, y=ys, sign=c(as.vector(as.matrix(data[row, -1]))), size=c(rep(2, (width)*(depth))))
  df2 <- data.frame(xpos=xpos, ypos=ypos, zpos=zpos)
  
  colors <- colorRampPalette(c("black","green", "yellow", "red"))(50)

  ghm2 <- ggplot(df)
  ghm2 <- ghm2 + theme_bw()
  ghm2 <- ghm2 + theme(panel.grid.minor = element_blank(),
                       panel.grid.major = element_blank(),
                       panel.background = element_blank(),
                       text = element_text(size = 24),
                       legend.position = 'none')
  ghm2 <- ghm2 + geom_point(aes(x = xs, y = ys, colour=sign),shape=15, size=df$size)
  ghm2 <- ghm2 + geom_point(data=df2, aes(x = xpos, y = ypos, size = zpos), colour="white", shape=16)
  ghm2 <- ghm2 + scale_color_gradientn(colours=colors, na.value = "black", limits=c(0, max_height))
  ghm2 <- ghm2 + xlab("x") + ylab("y") + ggtitle(paste("t = ", row-1, sep=""))
  ghm2 <- ghm2 + xlim(0,(width-1)) + ylim(0,(depth-1))
  
  ggsave(file = paste("pic/dist", row-1, ".png", sep=""), plot = ghm2, dpi = 100, width = 4.8, height = 4.8)
}
