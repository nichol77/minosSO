#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

for(( ar=0; ar<1000; ar++ ));
do

  qsub -q short -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/alexFitScript.sh -v ALEXRUN=${ar}
done
