## Simple R script to read data from serial interface
## and store data to disc


library(serial)

con <- serialConnection(name="test_con", port = "com7", mode = "9600,n,8,1")

listPorts()

open(con)

cat("Zeit\t", "Temperatur\n", file="record.txt")

flush(con)
repeat {
  Sys.sleep(0.1) # wait 100 ms
  temp <- read.serialConnection(con)
  if (!is.null(temp)) {
    cat(as.character(Sys.time()), "\t", temp, "\n")
    cat(as.character(Sys.time()), "\t", temp, "\n", file="record.txt", append=TRUE)
  }
}
close(con)
