#!/bin/bash

cd /home/rjn/minos/ccPlusNc/logs

runtag=runvii
outtag=runvii_pred_nue
outcount=0;

DIR=/unix/minos1/rjn/DSTs/2011/R2.7_2011-09-07/MC/nue/r4



# read all file name into an array
fileArray=($(find $DIR -type f))
 
# restore it 
#IFS=$OLDIFS
 
# get length of an array
tLen=${#fileArray[@]}
 
# use for loop read all filenames
for (( i=0; i<${tLen}; i+=8 ));
do
  echo "${fileArray[$i]} ${fileArray[$i+1]} ${fileArray[$i+2]} ${fileArray[$i+3]}"
    outfile=/unix/minos1/rjn/ccPlusNc/farPreds/run7/nue${outcount}.root
    echo $outfile;
    let outcount=outcount+1;
    qsub -q medium -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/multiFileScript.sh -v INPUTFILE1=${fileArray[$i]},INPUTFILE2=${fileArray[$i+1]},INPUTFILE3=${fileArray[$i+2]},INPUTFILE4=${fileArray[$i+3]},INPUTFILE5=${fileArray[$i+4]},INPUTFILE6=${fileArray[$i+5]},INPUTFILE7=${fileArray[$i+6]},INPUTFILE8=${fileArray[$i+7]},OUTPUTFILE=${outfile},RUNTAG=${runtag},OUTTAG=${outtag}
done
