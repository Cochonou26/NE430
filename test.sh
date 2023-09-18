#!/bin/bash

IP=( $(cat iptest.resultat) )
COMPTEUR=0

for (( I = 0; I < ${#IP[*]}; I = I + 2 ))
do
  OUTPUT=$(echo "${IP[I]}" | ./main)

  if [ "$OUTPUT" != "${IP[I+1]}" ]
  then
    echo "PAS OK " "${IP[I]}"
    COMPTEUR=$((COMPTEUR+1))
  fi
done

echo "$COMPTEUR" errors