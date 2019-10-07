
library(stats)
#' Get half time by linear fitting
#'
#' get half time according to http://www.amylofit.ch.cam.ac.uk
#' The algorithm for the extraction of the half times proceeds as follows: first the middle
#' part of the curve is selected, by determining when the average over several points is first
#' above 0.3 and when the average is last below 0.7. The number of points to be averaged
#' over depends on the number of points in the curve. A straight line is then fitted to this
#' middle part of the curve, the point at which it crosses the value of 0.5 is recorded as the
#' half time. (source: DOI: nprot.2016.010)
#' @param time vector of time
#' @param val vector of values
#'
#' @return half time
#' @export
get.halftime <- function(time, val){
    if(!(length(time)==length(val) & length(time)>1)) {
        stop('Length of time and val should be equal and >= 2')
    }
    val <- normalize(val)
    val.smoothed <- smooth.mean(val, ceiling(length(val)/100))
    lm.D9 <- lm(val ~ time, subset=(which(0.3<=val.smoothed & val.smoothed<=0.7)))
    return( (0.5 - lm.D9$coefficients[1]) / lm.D9$coefficients[2])
}  # time and normalized var 0.3-0.7

time <- list (1,2,3)
val <- list(3.4, 1.2, 2.1)
get.halftime(time, val)