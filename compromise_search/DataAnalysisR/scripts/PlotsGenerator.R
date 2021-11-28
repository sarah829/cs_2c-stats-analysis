# input is normal data.frame
# this is the plot that has lines for each small_size value
# all on the same plot
GetPlotWithAll <- function(data_source) {
  thin_size = .1
  thick_size = 1.
  new_data_source <- data_source
  new_data_source <- new_data_source %>%
    mutate(line_size = case_when (
      small_size < 0 ~ thick_size,
      small_size >= 0 ~ thin_size
    ))
  # necessary to get the separate lines and coloring
  new_data_source$small_size <- as.factor(new_data_source$small_size)
  # get right label
  levels(new_data_source$small_size)[match(-1, levels(new_data_source$small_size))] <- "std::binary_search"
  levels(new_data_source$small_size)[match(-2, levels(new_data_source$small_size))] <- "std::find"
  
  plot <- ggplot(data=new_data_source, aes(x=size, y=time, group=small_size)) +
    ggtitle("Timing Compromise Search") +
    geom_line(aes(color=small_size), size=new_data_source$line_size)
  scale_color_brewer(palette = "Dark2")
  return(plot)
}

# only compromise
GetPlotWithCompromise <- function(data_source) {
  thin_size = .1
  thick_size = 1.
  new_data_source <- data_source
  new_data_source <- new_data_source %>%
    mutate(line_size = case_when (
      small_size == 0 ~ thick_size,
      small_size > 0 ~ thin_size
    ))
  # necessary to get the separate lines and coloring
  new_data_source$small_size <- as.factor(new_data_source$small_size)
  # get right label
  levels(new_data_source$small_size)[match(-1, levels(new_data_source$small_size))] <- "std::binary_search"
  levels(new_data_source$small_size)[match(-2, levels(new_data_source$small_size))] <- "std::find"
  
  plot <- ggplot(data=new_data_source, aes(x=size, y=time, group=small_size)) +
    ggtitle("Timing Compromise Search") +
    geom_line(aes(color=small_size), size=new_data_source$line_size)
  scale_color_brewer(palette = "Dark2")
  return(plot)
}

# plot with set size, small_size vs time
GetPlotBySize <- function(data_source, plot_size, pt_size)
{
  data <- subset(data_source, plot_size == data_source$size,)
  graph_data <- data.frame(cbind(data$small_size, data$time))
  colnames(graph_data) = c("small_size", "time")
  title <- paste("size =", plot_size)
  gg <- (ggplot(graph_data, aes(x=small_size, y=time)) + ggtitle(title)
         + geom_point(size = pt_size))
  return(gg)
}

# gets separate graphs with each size graphing small sizes
# skips graph with 1 element
GetAllPlotsBySize <- function(data_source, max_power)
{
  pt_size = 3
  plots <- list(GetPlotBySize(data_source, 2^0, pt_size))
  for (i in c(1:max_power))
  {
    gg <- GetPlotBySize(data_source, 2^i, pt_size)
    plots[[length(plots)+1]] <- gg
    pt_size <- pt_size - .2
  }
  return(plots)
}

# get graphs by small size with all different sizes
GetPlotBySmallSize <- function(data_source, small_size)
{
  colnames(data_source) = c("size", "time", "small_size")
  graph_data <- data.frame(cbind(data_source$size, data_source$time))
  colnames(graph_data) = c("size", "time")
  title <- paste("small_size =", small_size)
  gg <- ggplot(graph_data, aes(x=size, y=time)) + ggtitle(title) + geom_point()
  return(gg)
}

GetAllPlotsBySmallSize <- function(data_source, small_sizes)
{
  plots <- list(GetPlotBySmallSize(data_source$`small_sizes[1]`), 1)
  for (i in c(2:length(small_sizes)))
  {
    gg <- GetPlotBySmallSize(data_source$`small_sizes[i]`, small_sizes[i])
    plots[[length(plots)+1]] <- gg
  }
  return(plots);
}

