#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

runtag=runiii
outtag=runiii_pred_tau
outcount=0;

DIR=/unix/minos1/rjn/DSTs/2010/R2.2/MC/D07_dogwood3/tau/r3/micro2010/



# read all file name into an array
fileArray=($(find $DIR -type f))
 
# restore it 
#IFS=$OLDIFS
 
# get length of an array
tLen=${#fileArray[@]}
 
# use for loop read all filenames
for (( i=0; i<${tLen}; i+=4 ));
do
  echo "${fileArray[$i]} ${fileArray[$i+1]} ${fileArray[$i+2]} ${fileArray[$i+3]}"
    outfile=/unix/minos1/rjn/ccPlusNc/farPreds/run3/tau${outcount}.root
    echo $outfile;
    let outcount=outcount+1;
    qsub -q medium -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/multiFileScript.sh -v INPUTFILE1=${fileArray[$i]},INPUTFILE2=${fileArray[$i+1]},INPUTFILE3=${fileArray[$i+2]},INPUTFILE4=${fileArray[$i+3]},OUTPUTFILE=${outfile},RUNTAG=${runtag},OUTTAG=${outtag}
done
