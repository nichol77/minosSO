#!/bin/bash


if [ "$RUN" = "" ]
then
   echo "Need RUN set"
   exit 1
fi


if [ "$FAKE_DMI" = "" ]
then
   echo "Need FAKE_DMI set"
   exit 1
fi

if [ "$FAKE_T23" = "" ]
then
   echo "Need FAKE_T23 set"
   exit 1
fi

if [ "$FAKE_T13" = "" ]
then
   echo "Need FAKE_T13 set"
   exit 1
fi

if [ "$FAKE_DELTA" = "" ]
then
   echo "Need FAKE_DELTA set"
   exit 1
fi

if [ "$FIRST_EXP" = "" ]
then
   echo "Need FIRST_EXP set"
   exit 1
fi

if [ "$LAST_EXP" = "" ]
then
   echo "Need LAST_EXP set"
   exit 1
fi


cd /home/rjn/minos/ccPlusNc
source /home/rjn/.bash_profile

echo "./fitting/makeFakeSurfaceFiles ${RUN} ${FAKE_DMI} ${FAKE_T23} ${FAKE_T13} ${FAKE_DELTA} ${FIRST_EXP} ${LAST_EXP}"

./fitting/makeFakeSurfaceFiles ${RUN} ${FAKE_DMI} ${FAKE_T23} ${FAKE_T13} ${FAKE_DELTA} ${FIRST_EXP} ${LAST_EXP}