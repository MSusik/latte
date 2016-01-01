#!/bin/bash

EXECUTABLE=`pwd`/../latc_x86_64
OFFICIAL_BAD=`pwd`/official/bad/
STUDENTS_BAD=`pwd`/students/bad/semantic

<<COM
for i in `find  $OFFICIAL_BAD -iname "*.lat" | sort`
do
    echo "test" $i ;
    $EXECUTABLE $i ;
    if [ $? == 0 ]
    then
        echo "Returned 0, but it shouldn't!" $i
    fi
done

find $OFFICIAL_BAD -iname "*.s" | xargs rm
find $OFFICIAL_BAD -not -iname "*.lat" | xargs rm


# students -> bad

echo "STUDENTS BAD"

for i in `find  $STUDENTS_BAD -iname "*.lat" | sort`
do
    echo "test" $i ;
    $EXECUTABLE $i ;
    if [ $? == 0 ]
    then
        echo "Returned 0, but it shouldn't!" $i
    fi
done

find $STUDENTS_BAD -iname "*.s" | xargs rm
find $STUDENTS_BAD -not -iname "*.lat" | xargs rm
COM