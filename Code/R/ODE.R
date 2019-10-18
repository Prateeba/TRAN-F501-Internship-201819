# set working directory
setwd("./")
 
# load libraries
library(ggplot2) #library for plotting
library(reshape2) # library for reshaping data (tall-narrow <-> short-wide)
library(deSolve) # library for solving differential equations
library(minpack.lm) # library for least squares fit using levenberg-marquart algorithm

#load concentration data
df=read.table("ABC_data.dat")
names(df)=c("time","ca","cb","cc")
 
# plot data
tmp=melt(df,id.vars=c("time"),variable.name="species",value.name="conc")
ggplot(data=tmp,aes(x=time,y=conc,color=species))+geom_point(size=3)



# rate equations are captured in a function that is an input parameter to the ODE solver -> model the differential equations 
# rate function
rxnrate=function(t,c,parms){
 	# rate constant passed through a list called parms
 	k1=parms$k1
 	k2=parms$k2
 	
 	# c is the concentration of species
 	# derivatives dc/dt are computed below
 	r=rep(0,length(c))
 	r[1]=-k1*c["A"] #dcA/dt
 	r[2]=k1*c["A"]-k2*c["B"] #dcB/dt
 	r[3]=k2*c["B"] #dcC/dt
 	
 	# the computed derivatives are returned as a list
 	# order of derivatives needs to be the same as the order of species in c
 	return(list(r))
}

#Computing the predicted concentration for a given set of rate constants involves just solving the ODEs with intial conditions.
# EX : 
# 	cinit=c(A=1,B=0,C=0)
# 	t=df$time
# 	parms=list(k1=2,k2=1)
# 	out=ode(y=cinit,times=t,func=rxnrate,parms=parms)
# 	head(out)

# function whose input is the parameters to be estimated and the output is the residuals
ssq=function(parms){
	# inital concentration
	cinit=c(A=1,B=0,C=0)
	# time points for which conc is reported
	# include the points where data is available
	t=c(seq(0,5,0.1),df$time)
	t=sort(unique(t))
	# parameters from the parameter estimation routine
	k1=parms[1]
	k2=parms[2]
	# solve ODE for a given set of parameters
	out=ode(y=cinit,times=t,func=rxnrate,parms=list(k1=k1,k2=k2))
	
	# Filter data that contains time points where data is available
	outdf=data.frame(out)
	outdf=outdf[outdf$time %in% df$time,]
	# Evaluate predicted vs experimental residual
	preddf=melt(outdf,id.var="time",variable.name="species",value.name="conc")
	expdf=melt(df,id.var="time",variable.name="species",value.name="conc")
	ssqres=preddf$conc-expdf$conc
	
	# return predicted vs experimental residual
	return(ssqres)
}

# parameter fitting using levenberg marquart algorithm
# initial guess for parameters
parms=c(k1=0.5,k2=0.5)
# fitting
fitval=nls.lm(par=parms,fn=ssq)

summary(fitval)


