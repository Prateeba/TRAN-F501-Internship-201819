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
#tmp=melt(df,id.vars=c("time"),variable.name="species",value.name="conc")
#ggplot(data=tmp,aes(x=time,y=conc,color=species))+geom_point(size=3)+geom_blank()

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
	t=c(seq(0,20,0.01),df$time)
	t=sort(unique(t))
	
	# parameters from the parameter estimation routine
	kn=parms[1]
	nc=parms[2]
	k2=parms[3]
	n2=parms[4]
	kplus=parms[5]
	
	# solve ODE for a given set of parameters
	out=ode(y=cinit,times=t,func=rxnrate,parms=parms, method = "rk4")
	
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
fitval=nls.lm(par=parms,fn=ssq,lower=c(0, 0, 0, 0, 0),upper=c(Inf, 5, Inf, 5, Inf),control=nls.lm.control(maxiter=1000))

# Estimated parameter
parest=as.list(coef(fitval))

# simulated predicted profile at estimated parameter values
cinit=c(mt=1e-6,Mt=0,Pt=0)	
t=c(seq(0,20,0.01),df$time)
t=sort(unique(t))
parms=as.list(parest)

out=ode(y=cinit,times=t,func=rxnrate,parms=parms, method="rk4")
outdf=data.frame(out)
names(outdf)=c("time","Ab42_rep1_5uM_pred")

# Overlay predicted profile with experimental data
tmppred=melt(outdf,id.var=c("time"),variable.name="species",value.name="conc")
tmpexp=melt(df,id.var=c("time"),variable.name="species",value.name="conc")
p=ggplot(data=tmppred,aes(x=time,y=conc,color=species,linetype=species))+geom_line()
p=p+geom_line(data=tmpexp,aes(x=time,y=conc,color=species,linetype=species))
p=p+geom_point(data=tmpexp,aes(x=time,y=conc,color=species))
p=p+scale_linetype_manual(values=c(0,1,0,1,0,1))
p=p+scale_color_manual(values=rep(c("red","blue","green"),each=2))+theme_bw()
print(p)