#!/bin/bash

if [ "$ALEXRUN" = "" ]
then
   echo "Need ALEXRUN set"
   exit 1
fi



cd /home/rjn/minos/ccPlusNc
source /home/rjn/.bash_profile

echo "./fitting/doGridSearchAlex 11 $ALEXRUN"
./fitting/doGridSearchAlex 11 $ALEXRUN
