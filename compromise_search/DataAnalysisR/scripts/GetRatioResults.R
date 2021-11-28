GetRatioResults <- function(data_source)
{
  sizes = unique(data_source[,2])
  for (s in sizes)
  {
    binary_time = filter(data_source, size == s & small_size == -1)$time
    data_source[data_source$size == s,]$time = data_source[data_source$size == s,]$time / binary_time
  }
  return(data_source)
}

GetRatioSmallSize <- function(data_source)
{
  sizes = unique(data_source[,2])
  for (s in sizes)
  {
    binary_time = filter(data_source, size == s & small_size == 0)$time
    data_source[data_source$size == s,]$time = data_source[data_source$size == s,]$time / binary_time
  }
  return(data_source)
}

#Data for ratio without outliers
function()
{
  ratio_by_small_size_0 <- results_by_small_size_huge
  ratio_by_small_size_0 <- GetRatioSmallSize(ratio_by_small_size_0)
  ratio_by_small_size_0 <- ratio_by_small_size_0[ratio_by_small_size_0$small_size >= 0,]
  ratio_by_small_size_0 <- ratio_by_small_size_0[ratio_by_small_size_0$size != 199450 | ratio_by_small_size_0$small_size != 139,]
  ratio_by_small_size_0 <- ratio_by_small_size_0[ratio_by_small_size_0$size != 157625 | ratio_by_small_size_0$small_size != 16,]
}
