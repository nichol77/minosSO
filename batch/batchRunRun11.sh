#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

runtag=minosplus
outtag=runxi_pred_main
filebase=main

DIR=/unix/minos1/rjn/DSTs/2014/R3.05/far/beam/M000200Np11/mixed/



for(( dmi=86; dmi<87; dmi++ ));
do
  outfile=/unix/minos1/rjn/ccPlusNc/farPreds/run11/${filebase}${dmi}.root
  echo $outfile;

  qsub -q medium -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/multiDmiScript.sh -v INPUTDIR=${DIR},OUTPUTFILE=${outfile},RUNTAG=${runtag},OUTTAG=${outtag},STARTDMI=${dmi},ENDDMI=${dmi}
done
