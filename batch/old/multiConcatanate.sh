#!/bin/bash

if [ "$INPUTFILE1" = "" ]
then
   echo "Need INPUTFILE1 set"
   exit 1
fi

if [ "$INPUTFILE2" = "" ]
then
    cp ${INPUTFILE1} ${OUTPUTFILE}
    exit 1
fi

if [ "$OUTPUTFILE" = "" ]
then
   echo "Need OUTPUTFILE set"
   exit 1
fi



cd /home/rjn/minos/ccPlusNc
source /home/rjn/.bash_profile
hadd ${OUTPUTFILE} ${INPUTFILE1} ${INPUTFILE2} ${INPUTFILE3} ${INPUTFILE4}