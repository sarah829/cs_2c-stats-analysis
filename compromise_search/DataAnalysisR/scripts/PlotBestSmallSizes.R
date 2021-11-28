# this is for getting data so that it can be used for plot best sizes
ProcessData <- function(data) {
  data <- data[data$small_size <= data$size,]
  data <- data[, c(2, 1, 3)]
  data <- data[data$small_size != -2 & data$small_size != -1,]
  data <- data[order(data$size, data$time),]
  rankings <- MakeRankings(data)
  data <- cbind(data, rankings)
  rownames(data) <- NULL
  point_size <- GetPointSize(data)
  data <- cbind(data, point_size)
  sizes <- unique(data$size)
  sizes <- c(sizes[c(1:5)], sample(sizes[c(6:length(sizes))], length(sizes) / 3))
  sizes <- sort(sizes)
  graph_data <- data[data$size %in% sizes,]
  graph_data <- graph_data[order(graph_data$point_size),] # makes best pt on top
  return(graph_data)
}

BestSmallSizesPlot <- function(data) {
  ggplot(data, aes(x=size, y=small_size)) +
    geom_point(aes(colour=rankings, size=point_size)) + 
    scale_colour_gradient(low="darkblue", high="aliceblue") + 
    scale_size(range=c(.5, 1)) + 
    scale_x_log2(labels = trans_format("log2", math_format(2^.x)), breaks = trans_breaks("log2", function(x) 2^x, n=11)) + 
    scale_y_continuous(breaks = scales::pretty_breaks(n = 10)) + 
    ggtitle("Plot of the best small_sizes by size") + 
    guides(size = "none") + labs(caption = "big points = best value")
}

BestSmallSizesPlotNoLog <- function(data) {
  ggplot(data, aes(x=size, y=small_size)) +
    geom_point(aes(colour=rankings, size=point_size)) + 
    scale_colour_gradient(low="darkblue", high="aliceblue") + 
    scale_size(range=c(.5, 1.5)) + 
    ggtitle("Plot of the best small_sizes by size") + 
    guides(size = "none") + labs(caption = "big points = best value")
}