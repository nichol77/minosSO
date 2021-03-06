#!/bin/bash


if [ "$1" = "" ]
then
   echo "Usage $0 <run>"
   exit 1
fi


cd /home/rjn/minos/ccPlusNc/logs

WHICH_RUN=$1
FILE_TYPE=doublecatmain
OUT_PREFIX=treblecatmain

DIR=/unix/minos1/rjn/ccPlusNc/farPreds/run${WHICH_RUN}

outcount=0;


# read all file name into an array
fileArray=($(find $DIR/${FILE_TYPE}* -type f))
 
# restore it 
#IFS=$OLDIFS
 
# get length of an array
tLen=${#fileArray[@]}
 
# use for loop read all filenames
for (( i=0; i<${tLen}; i+=4 ));
do
  echo "${fileArray[$i]} ${fileArray[$i+1]} ${fileArray[$i+2]} ${fileArray[$i+3]}"
  outfile=/unix/minos1/rjn/ccPlusNc/farPreds/run${WHICH_RUN}/${OUT_PREFIX}_${FILE_TYPE}_${outcount}.root
  echo $outfile
  let outcount=${outcount}+1
  qsub -q short -M rjn@hep.ucl.ac.uk ~/minos/ccPlusNc/batch/multiConcatanate.sh -v INPUTFILE1=${fileArray[$i]},INPUTFILE2=${fileArray[$i+1]},INPUTFILE3=${fileArray[$i+2]},INPUTFILE4=${fileArray[$i+3]},OUTPUTFILE=${outfile}
sleep 1
done
