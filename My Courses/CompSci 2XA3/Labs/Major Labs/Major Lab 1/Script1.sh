#!/bin/bash

# Script1
# Jatin C. | 400033011

# creates week_day1 and adds stuff to it
echo "I am week_day1" > week_day1
echo "I love being Monday" >> week_day1

# creates week_day2 and adds stuff to it
echo "I am week_day2" > week_day2
echo "I love being Tuesday" >> week_day2

# creates week_day3 and adds stuff to it
echo "I am week_day3" > week_day3
echo "I love being Wednesday" >> week_day3

# creates week_day4 and adds stuff to it
echo "I am week_day4" > week_day4
echo "I love being Thursday" >> week_day4

# creates week_day5 and adds stuff to it
echo "I am week_day5" > week_day5
echo "I love being Friday" >> week_day5

# displays contents of week_day1
echo "week_day1:"
cat week_day1
echo "%%%%%%%%%%%%%%%%%%%"
# displays contents of week_day2
echo "week_day2:"
cat week_day2
echo "%%%%%%%%%%%%%%%%%%%"
# displays contents of week_day3
echo "week_day3:"
cat week_day3
echo "%%%%%%%%%%%%%%%%%%%"
# displays contents of week_day4
echo "week_day4:"
cat week_day4
echo "%%%%%%%%%%%%%%%%%%%"
# displays contents of week_day5
echo "week_day5:"
cat week_day5
echo "%%%%%%%%%%%%%%%%%%%"

# creates a newfile called Weekdays and 
# appends the contents of 
# weekday_3,5,1,2,4 (in that order) to it
cat week_day3 > Weekdays
cat week_day5 >> Weekdays
cat week_day1 >> Weekdays
cat week_day2 >> Weekdays
cat week_day4 >> Weekdays

# prints the contents of Weekdays
echo "Weekdays:"
cat Weekdays

# prints current directory and
# deletes all week_day files & Weekdays 
echo "current directory:"
ls -la 
rm -rf week_day*
rm -rf Weekdays
ls -la