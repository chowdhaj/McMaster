#!/bin/bash

i=0
loop=5000

while [ $i -le $loop ]
do
    echo "$i) "
    ./race.conditions.bad
    ((i++))
done
