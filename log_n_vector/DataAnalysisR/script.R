# libraries
library(readr)
library(ggplot2)

# get the data
access_results_1000000 <- read_csv("~/Documents/Programs/C++Stuff/cs_2c/homework02/results/access_results_1000000.csv", col_types = cols(index = col_integer()))
amortized_1000000 <- read_csv("~/Documents/Programs/C++Stuff/cs_2c/homework02/results/amortized_1000000.csv", col_types = cols(index = col_integer()))
insert_by_index_1000000_50_powers_only <- read_csv("~/Documents/Programs/C++Stuff/cs_2c/homework02/results/insert_by_index_1000000_50_powers_only.csv", col_types = cols(index = col_integer()))
insert_by_index_max_100000_rep_50 <- read_csv("~/Documents/Programs/C++Stuff/cs_2c/homework02/results/insert_by_index_max_100000_rep_50.csv", col_types = cols(index = col_integer()))


# access descriptive stats
Q <- quantile(access_results_1000000$`log_vector/std_vector`, probs=c(.25, .75), na.rm = FALSE)
iqr <- IQR(access_results_1000000$`log_vector/std_vector`)
median <- median(access_results_1000000$`log_vector/std_vector`)
mean <- mean(access_results_1000000$`log_vector/std_vector`)
std_dev <- sd(access_results_1000000$`log_vector/std_vector`)

# amortized graph
amortized_graph1 <- amortized_1000000[, c(1, 2)]
amortized_graph2 <- amortized_1000000[, c(1, 3)]
amortized_graph1 <- cbind(amortized_graph1, rep("log", 1000000))
amortized_graph2 <- cbind(amortized_graph2, rep("std", 1000000))
colnames(amortized_graph1) <- c("index", "time", "type")
colnames(amortized_graph2) <- c("index", "time", "type")
amortized_graph_data <- rbind(amortized_graph1, amortized_graph2)
amortized_graph_data <- amortized_graph_data[order(amortized_graph_data$index, amortized_graph_data$type),]
amortized_plot <- ggplot(amortized_graph_data) + aes(x=index, y=time, group=type) + 
  ggtitle("Amortized Time: Previous 50 push_backs") + 
  geom_line(aes(color=type)) + scale_color_brewer(palette = "Dark2")

# powers of two graph
d1 <- insert_by_index_1000000_50_powers_only[, c(1, 2)]
d2 <- insert_by_index_1000000_50_powers_only[, c(1, 3)]
d1 <- cbind(d1, rep("log", 1000000))
d2 <- cbind(d2, rep("std", 1000000))
colnames(d1) <- c("index", "ratio", "ratio_type")
colnames(d2) <- c("index", "ratio", "ratio_type")
powers_of_two_data <- rbind(d1, d2)
powers_of_two_data <- powers_of_two_data[order(powers_of_two_data$index, powers_of_two_data$ratio_type),]
powers_plot <- ggplot(powers_of_two_data) + aes(x=index, y=ratio, group=ratio_type) + 
  ggtitle("Ratio of push_back Times (Powers of 2)") + 
  geom_line(aes(color=ratio_type)) + scale_color_brewer(palette = "Dark2")

rm(amortized_graph1, amortized_graph2, d1, d2, powers_of_two_data, amortized_graph_data)
