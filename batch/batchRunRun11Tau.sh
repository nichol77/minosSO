#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

runtag=minosplus
outtag=runxi_pred_tau
filebase=tau

DIR=/unix/minos1/rjn/DSTs/2014/R3.05/far/beam/M000200Np11/tau



for(( dmi=0; dmi<100; dmi++ ));
do
  outfile=/unix/minos1/rjn/ccPlusNc/farPreds/run11/${filebase}${dmi}.root
  echo $outfile;
  usleep 100
  qsub -q medium -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/multiDmiScript.sh -v INPUTDIR=${DIR},OUTPUTFILE=${outfile},RUNTAG=${runtag},OUTTAG=${outtag},STARTDMI=${dmi},ENDDMI=${dmi}
done
