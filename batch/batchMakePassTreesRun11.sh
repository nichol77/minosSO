#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

runtag=minosplus
outtag=runxi_pred_main
filebase=main

DIR=/unix/minos1/rjn/DSTs/2014/R3.05/far/beam/M000200Np11/mixed/

outfile=/unix/minos1/rjn/ccPlusNc/passTrees/run11/${filebase}Pass.root
echo $outfile;
#qsub -q medium -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/passTreeScript.sh -v INPUTDIR=${DIR},OUTPUTFILE=${outfile},RUNTAG=${runtag},OUTTAG=${outtag}

runtag=minosplus
outtag=runxi_pred_nue
filebase=nue
DIR=/unix/minos1/rjn/DSTs/2014/R3.05/far/beam/M000200Np11/nue
outfile=/unix/minos1/rjn/ccPlusNc/passTrees/run11/${filebase}Pass.root
echo $outfile;
qsub -q medium -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/passTreeScript.sh -v\
 INPUTDIR=${DIR},OUTPUTFILE=${outfile},RUNTAG=${runtag},OUTTAG=${outtag}


runtag=minosplus
outtag=runxi_pred_tau
filebase=tau
DIR=/unix/minos1/rjn/DSTs/2014/R3.05/far/beam/M000200Np11/tau
outfile=/unix/minos1/rjn/ccPlusNc/passTrees/run11/${filebase}Pass.root
echo $outfile;
qsub -q medium -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/passTreeScript.sh -v\
 INPUTDIR=${DIR},OUTPUTFILE=${outfile},RUNTAG=${runtag},OUTTAG=${outtag}

