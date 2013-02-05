#!/bin/bash

if [ "$INPUTFILE1" = "" ]
then
   echo "Need INPUTFILE1 set"
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
echo "./src/makePredictionsMultiFile ${OUTPUTFILE} ${RUNTAG} ${OUTTAG} ${INPUTFILE1} ${INPUTFILE2} ${INPUTFILE3} ${INPUTFILE4} ${INPUTFILE5} ${INPUTFILE6} ${INPUTFILE7} ${INPUTFILE8}"
./src/makePredictionsMultiFile ${OUTPUTFILE} ${RUNTAG} ${OUTTAG} ${INPUTFILE1} ${INPUTFILE2} ${INPUTFILE3} ${INPUTFILE4} ${INPUTFILE5} ${INPUTFILE6} ${INPUTFILE7} ${INPUTFILE8}
