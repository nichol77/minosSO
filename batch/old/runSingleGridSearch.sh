#!/bin/bash

if [ "$2" = "" ]
then
   echo "Usage $0 <dmbin> <t23bin>"
   exit 1
fi


cd /home/rjn/minos/ccPlusNc/logs

for run in 4 7 9; do
    echo "qsub -q long -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/singleGridSearch.sh -v RUN=${run},DMBIN=${1},T23BIN=${2}"
    qsub -q long  -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/singleGridSearch.sh -v RUN=${run},DMBIN=${1},T23BIN=${2}
done
