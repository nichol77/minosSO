#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

runtag=runiv
outtag=runiv_pred_main
outcount=0;

DIR=/unix/minos1/rjn/DSTs/2011/R2.7_2011-09-07/MC/far/r4




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
    outfile=/unix/minos1/rjn/ccPlusNc/farPreds/run4/main${outcount}.root
    echo $outfile;
    let outcount=outcount+1;
    qsub -q medium -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/multiFileScript.sh -v INPUTFILE1=${fileArray[$i]},INPUTFILE2=${fileArray[$i+1]},INPUTFILE3=${fileArray[$i+2]},INPUTFILE4=${fileArray[$i+3]},OUTPUTFILE=${outfile},RUNTAG=${runtag},OUTTAG=${outtag}
done
