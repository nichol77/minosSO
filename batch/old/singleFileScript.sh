#!/bin/bash

if [ "$INPUTFILE" = "" ]
then
   echo "Need INPUTFILE set"
   exit 1
fi

if [ "$OUTPUTFILE" = "" ]
then
   echo "Need OUTPUTFILE set"
   exit 1
fi

if [ "$RUNTAG" = "" ]
then
   echo "Need RUNTAG set"
   exit 1
fi

if [ "$OUTTAG" = "" ]
then
   echo "Need OUTTAG set"
   exit 1
fi



cd /home/rjn/minos/ccPlusNc
source /home/rjn/.bash_profile
root -b uclscripts/runNuDstLooperPredMaker.C\(\"${INPUTFILE}\",\"${OUTPUTFILE}\",\"${RUNTAG}\",\"${OUTTAG}\"\)