#!/bin/bash

if [ "$PASSTREE" = "" ]
then
   echo "Need PASSTREE set"
   exit 1
fi

if [ "$OUTPUTFILE" = "" ]
then
   echo "Need OUTPUTFILE set"
   exit 1
fi

if [ "$STARTDMI" = "" ]
then
   echo "Need STARTDMI set"
   exit 1
fi

if [ "$ENDDMI" = "" ]
then
   echo "Need STARTDMI set"
   exit 1
fi


cd /home/rjn/minos/ccPlusNc
source /home/rjn/.bash_profile
echo "./src/loopOverPassTreeMakePredictions ${OUTPUTFILE} ${PASSTREE} ${STARTDMI} ${ENDDMI}"
./src/loopOverPassTreeMakePredictions ${OUTPUTFILE} ${PASSTREE} ${STARTDMI} ${ENDDMI}
