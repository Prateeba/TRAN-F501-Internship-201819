# set working directory
setwd("./")
 
# load libraries
library(ggplot2) #library for plotting
library(reshape2) # library for reshaping data (tall-narrow <-> short-wide)
library(deSolve) # library for solving differential equations
library(minpack.lm) # library for least squares fit using levenberg-marquart algorithm


#load concentration data
df=read.table("test2.dat")
#names(df)=c("time", "Ab42_rep1_5uM","Ab42_rep2_5uM","Ab42_rep3_5uM","Ab42_rep4_5uM","Ab42_rep1_4uM","Ab42_rep2_4uM","Ab42_rep3_4uM","Ab42_rep4_4uM","Ab42_rep1_3.5uM","Ab42_rep2_3.5uM","Ab42_rep3_3.5uM","Ab42_rep4_3.5uM","Ab42_rep1_3uM","Ab42_rep2_3uM","Ab42_rep3_3uM","Ab42_rep4_3uM","Ab42_rep1_2.5uM","Ab42_rep2_2.5uM","Ab42_rep3_2.5uM","Ab42_rep4_2.5uM","Ab42_rep1_2uM","Ab42_rep2_2uM","Ab42_rep3_2uM","Ab42_rep4_2uM","Ab42_rep1_1.75uM","Ab42_rep2_1.75uM","Ab42_rep3_1.75uM","Ab42_rep4_1.75uM","Ab42_rep1_1.5uM","Ab42_rep2_1.5uM","Ab42_rep3_1.5uM","Ab42_rep4_1.5uM","Ab42_rep1_1.35uM","Ab42_rep2_1.35uM","Ab42_rep3_1.35uM","Ab42_rep4_1.35uM","Ab42_rep1_1.1uM","Ab42_rep2_1.1uM","Ab42_rep3_1.1uM","Ab42_rep4_1.1uM")
names(df)=c("time", "Ab42_rep1_5uM") 

# plot data
tmp=melt(df,id.vars=c("time"),variable.name="species",value.name="concentration")
ggplot(data=tmp,aes(x=time,y=concentration,color=species))+geom_point(size=3)+geom_blank()

rxnrate=function(t,c,parms){
 	# rate constant passed through a list called parms
 	kn=parms$kn
 	nc=parms$nc
 	k2=parms$k2
 	n2=parms$n2
 	kplus=parms$kplus
 	 	
 	# c is the initial values of the variables 
 	# derivatives dc/dt are computed below
 	r=rep(0,length(c)) # !!!!!! Problem more variables than equations .. 
 	r[1]=kn*c["mt"]^nc+k2*c["mt"]^n2*c["Mt"] #dP/dt
 	r[2]=2*c["mt"]*kplus*c["Pt"] #dM/dt
 	
 	# the computed derivatives are returned as a list
 	# order of derivatives needs to be the same as the order of species in c
 	return(list(r))
}

#cinit=c(mt=3831,Mt=0,Pt=0)
#t=df$time
#parms=list(kn=1,nc=1,k2=1,n2=1,kplus=1)
#out=ode(y=cinit,times=t,func=rxnrate,parms=parms)
#head(out)

ssq=function(parms){
	# inital concentration
	cinit=c(mt=1e-6,Mt=0,Pt=0)
	# time points for which conc is reported
	# include the points where data is available
	t=c(seq(0,20,0.1),df$time)
	t=sort(unique(t))
	
	# parameters from the parameter estimation routine
	kn=parms[1]
	nc=parms[2]
	k2=parms[3]
	n2=parms[4]
	kplus=parms[5]
	
	# solve ODE for a given set of parameters
	out=ode(y=cinit,times=t,func=rxnrate,parms=parms)
	
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

parms=list(kn=1,nc=1,k2=1,n2=1,kplus=1)
fitval=nls.lm(par=parms,fn=ssq)
parest=as.list(coef(fitval))
parest