RankOfZero <- function(data) {
  rank_of_zero <- data[data$small_size == 0,]
  rank_of_zero <- rank_of_zero[, c(1, 4)]
  rownames(rank_of_zero) <- NULL
  string_ratings <- rep("temp", nrow(rank_of_zero))
  small_size_count = data[nrow(data),]$rankings
  for (i in c(1:nrow(rank_of_zero))) 
  {
    denominator = min(small_size_count, (rank_of_zero$size[i] + 1))
    string_ratings[i] = paste(rank_of_zero$rankings[i], "/", denominator, sep="")
  }
  rank_of_zero <- cbind(rank_of_zero, string_ratings)
  rank_of_zero <- rank_of_zero[, c(1, 3)]
}