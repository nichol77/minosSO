#!/bin/bash

if [ "$RUN" = "" ]
then
   echo "Need RUN set"
   exit 1
fi

if [ "$DMBIN" = "" ]
then
   echo "Need DMBIN set"
   exit 1
fi


if [ "$T23BIN" = "" ]
then
   echo "Need T23BIN set"
   exit 1
fi


cd /home/rjn/minos/ccPlusNc
source /home/rjn/.bash_profile
./fitting/doGridSearchFake ${RUN} ${DMBIN} ${T23BIN}
