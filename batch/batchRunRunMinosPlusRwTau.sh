#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

runtag=runiii
outtag=minosplus_pred_tau
filebase=tau

DIR=/unix/minos1/rjn/DSTs/2010/R2.2/MC/D07_dogwood3/tau/r3/micro2010/



for(( dmi=0; dmi<100; dmi++ ));
do
  outfile=/unix/minos1/rjn/ccPlusNc/farPreds/minosPlus/${filebase}${dmi}.root
  echo $outfile;

  qsub -q medium -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/multiDmiRwScript.sh -v INPUTDIR=${DIR},OUTPUTFILE=${outfile},RUNTAG=${runtag},OUTTAG=${outtag},STARTDMI=${dmi},ENDDMI=${dmi}
done
