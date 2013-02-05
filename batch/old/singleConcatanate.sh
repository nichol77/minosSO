#!/bin/bash

if [ "$FIRST_RUN" = "" ]
then
   echo "Need FIRST_RUN set"
   exit 1
fi

if [ "$SECOND_RUN" = "" ]
then
   echo "Need SECOND_RUN set"
   exit 1
fi



cd /home/rjn/minos/ccPlusNc
source /home/rjn/.bash_profile
root -b utilities/runConcatanate.C\(${FIRST_RUN},${SECOND_RUN}\)