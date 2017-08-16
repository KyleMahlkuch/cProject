#!/bin/bash
#

echo '********************************************************************************'
echo 'Starting script to make an input file...'

echo -en '' > test.txt

FOR_NUM=$((RANDOM % 4096))+1

for ((number=1;number < ${FOR_NUM};number++)) {
  echo -en $((RANDOM % 4294967295)) >> test.txt
  echo -en ',' >> test.txt
}

echo -en '.\n' >> test.txt

echo 'End script. Input file is test.txt'
echo '********************************************************************************'
