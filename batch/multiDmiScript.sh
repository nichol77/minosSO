#!/bin/bash

if [ "$INPUTDIR" = "" ]
then
   echo "Need INPUTDIR set"
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
echo "./src/makePredictionsMultiFile ${OUTPUTFILE} ${RUNTAG} ${OUTTAG} ${INPUTDIR} ${STARTDMI} ${ENDDMI}"
./src/makePredictionsMultiFile ${OUTPUTFILE} ${RUNTAG} ${OUTTAG} ${INPUTDIR} ${STARTDMI} ${ENDDMI}