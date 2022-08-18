#!/bin/bash

# creates a directory called WEEK_DAYS
echo "creating subdirectory WEEK_DAYS"
mkdir WEEK_DAYS

# creates a file called WEEK_DAY2 inside WEEK_DAYS
echo "creating file WEEK_DAY2 in WEEK_DAYS"
touch WEEK_DAYS/WEEK_DAY2

# lists the contents of WEEK_DAYS
echo "listing directory WEEK_DAYS"
ls WEEK_DAYS/

# displays the contents of WEEK_DAYS2
echo "displaying file WEEK_DAY2"
cat WEEK_DAYS/WEEK_DAY2

# prints stuff
echo "%% tuesday %"

# stores the permission of WEEK_DAYS to 'var' 
# and prints it to console
var=`ls -la | grep WEEK\_DAYS`
echo "original permissions of WEEK_DAYS: ${var:0:10}"

# removing everyone's permission
chmod a-rwx WEEK\_DAYS

# gives user reading permissions and
# prints it to console
echo "change it to dr--------"
chmod u+r WEEK\_DAYS
var=`ls -la | grep WEEK\_DAYS`
echo "new permissions of WEEK_DAYS: ${var:0:10}"

# gives everyone reading permissions and
# prints it to the screen
echo "change it to dr--r--r--"
chmod a+r WEEK\_DAYS
var=`ls -la | grep WEEK\_DAYS`
echo "new permissions of WEEK_DAYS: ${var:0:10}"

# removes read permissions from group and other
# gives writing permissions to user and group
# gives executing permissions to all
# prints the permissions to console
echo "change it to drwx-wx--x"
chmod go-r WEEK\_DAYS
chmod ug+w WEEK\_DAYS
chmod a+x WEEK\_DAYS
var=`ls -la | grep WEEK\_DAYS`
echo "new permissions of WEEK_DAYS: ${var:0:10}"

# tries to remove WEEK_DAYS with rm
echo "trying to remove WEEK_DAYS" by rm
rm WEEK\_DAYS

# tries to remove WEEK_DAYS with rmdir
echo "trying to remove WEEK_DAYS" by rmdir
rmdir WEEK\_DAYS

# removes WEEK_DAYS with rm -r
echo "trying to remove WEEK_DAYS by rm -r"
rm -r WEEK\_DAYS