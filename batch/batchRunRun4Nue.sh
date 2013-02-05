#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

runtag=runiv
outtag=runiv_pred_nue
filebase=nue

DIR=/unix/minos1/rjn/DSTs/2011/R2.7_2011-09-07/MC/nue/r4



for(( dmi=0; dmi<100; dmi++ ));
do
  outfile=/unix/minos1/rjn/ccPlusNc/farPreds/run4/${filebase}${dmi}.root
  echo $outfile;

  qsub -q medium -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/multiDmiScript.sh -v INPUTDIR=${DIR},OUTPUTFILE=${outfile},RUNTAG=${runtag},OUTTAG=${outtag},STARTDMI=${dmi},ENDDMI=${dmi}
done
