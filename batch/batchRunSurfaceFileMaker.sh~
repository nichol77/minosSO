#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

if [ "$5" = "" ]
then
   echo "Usage $0 <run> <dmbin> <t23bin> <t13bin> <deltabin>"
   exit 1
fi

run=$1
fakeDmi=$2
fakeT23=$3
fakeT13=$4
fakeDelta=$5


for(( dmi=0; dmi<100; dmi++ ));
do
    echo "qsub -q short -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/gridSearchScript.sh -v RUN=${run},FAKE_DMI=${fakeDmi},FAKE_T23=${fakeT23},FAKE_T13=${fakeT13},FAKE_DELTA=${fakeDelta},DMI=${dmi}"
    qsub -q short -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/gridSearchScript.sh -v RUN=${run},FAKE_DMI=${fakeDmi},FAKE_T23=${fakeT23},FAKE_T13=${fakeT13},FAKE_DELTA=${fakeDelta},DMI=${dmi}

done
