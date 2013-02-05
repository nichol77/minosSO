#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

if [ "$5" = "" ]
then
   echo "Usage $0 <dmbin> <t23bin> <t13bin> <deltabin> <do minos+>"
   exit 1
fi

fakeDmi=$1
fakeT23=$2
fakeT13=$3
fakeDelta=$4
doMinosPlus=$5


for(( exp=0; exp<1000; exp+=100 ));
do
  let secondExp=$exp+99;
  echo "qsub -q short -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/makeFinalPlotScript.sh -v FAKE_DMI=${fakeDmi},FAKE_T23=${fakeT23},FAKE_T13=${fakeT13},FAKE_DELTA=${fakeDelta},FIRST_EXP=${exp},LAST_EXP=${secondExp}"
  qsub -q short -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/makeFinalPlotScript.sh -v FAKE_DMI=${fakeDmi},FAKE_T23=${fakeT23},FAKE_T13=${fakeT13},FAKE_DELTA=${fakeDelta},FIRST_EXP=${exp},LAST_EXP=${secondExp},DO_MINOS_PLUS=${doMinosPlus}

done
