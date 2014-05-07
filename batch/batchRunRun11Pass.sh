#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

if [[ $1 = "" ]]; then
    echo "`basename $0` <filebase> "
    exit 1
fi

filebase=$1


#for(( dmi=65; dmi<66; dmi++ ));
for(( dmi=0; dmi<100; dmi++ ));
do
    passtree=/unix/minos1/rjn/ccPlusNc/passTrees/run11/${filebase}Pass.root
    outfile=/unix/minos1/rjn/ccPlusNc/farPreds/run11/${filebase}${dmi}.root
    echo $outfile;

    qsub -q medium -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/multiDmiPassTreeLoopScript.sh -v PASSTREE=${passtree},OUTPUTFILE=${outfile},STARTDMI=${dmi},ENDDMI=${dmi}
done
