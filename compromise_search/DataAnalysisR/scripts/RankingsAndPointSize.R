
MakeRankings <- function(data_source)
{
  rankings = rep(NA, nrow(data_source))
  ranking = 1
  current_size = -5
  for (i in c(1:nrow(data_source)))
  {
    if (data_source$size[i] != current_size)
    {
      ranking = 1
    }
    rankings[i] <- ranking
    ranking <- ranking + 1
    current_size = data_source$size[i]
  }
  return(rankings)
}

GetPointSize <- function(frame)
{
  rankings = rep(NA, nrow(frame))
  for (i in c(1:nrow(frame)))
  {
    if (frame$rankings[i] == 1)
    {
      rankings[i] = .7
    }
    else
    {
      rankings[i] = .5
    }
  }
  return(rankings)
}