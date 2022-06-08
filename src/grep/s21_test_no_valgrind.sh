#!/bin/bash

echo "TESTS for GREP"
#say -v Victoria Hello, $LOGNAME, happy project presentation!
DIFF_RES=""
COUNTER_SUCCESS=0
COUNTER_FAIL=0
NUMBER=1
for file in "s21_grep.c" "Makefile" "text" "vova" "world" "joke" "log.txt" 
do
    for word in "while" "if" "void" "God"
    do
        for var1 in -i -n -c -l -v
        do
            for var2 in -l -v -c -n -i
            do
                if [ $var1 != $var2 ]
                then
                TEST0="-e while $file $var1 $var2"
                ./s21_grep $TEST0 > s21_grep.txt
                grep $TEST0 > grep.txt
                DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
                if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                    then
                        # osascript -e 'beep'
                        echo TEST $NUMBER "$TEST0" SUCCESS
                        (( COUNTER_SUCCESS++ ))
                        echo "$TEST0"
                    else
                        echo TEST $NUMBER "$TEST0" FAIL
                        echo "--------0---------" >> log.txt
                        echo "$TEST0" >> log.txt
                        echo "------------------" >> log.txt
                        (( COUNTER_FAIL++ ))
                    fi
                ((NUMBER++))
                rm s21_grep.txt grep.txt
                fi
            done
        done
    done
done


for file in "s21_grep.c" "Makefile" "text" "vova" "world" "joke" "log.txt" 
do
    for word in "while" "if" "void" "God"
    do
        for var in -c -e -n -v -i -s -h -l
        do
          TEST1="$var $word $file"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt
        done
    done
done

# for file in "s21_grep.c" "Makefile" "s21_grep.h"
# do
#     for var1 in -i -v -c -l -n -s -i -v -c -l -n -s
#     do
#         for var2 in -i -v -c -l -n -s -i -v -c -l -n -s
#         do
#             if [ $var1 != $var2 ]
#             then
#             TEST0="-e while $file $var1 $var2 -e for -ehandler -f patterns"
#             ./s21_grep $TEST0 > s21_grep.txt
#             grep $TEST0 > grep.txt
#             DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#             if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#                 then
#                     echo TEST $NUMBER "$TEST0" SUCCESS
#                     (( COUNTER_SUCCESS++ ))
#                     echo "$TEST0"
#                 else
#                     echo TEST $NUMBER "$TEST0" FAIL
#                     echo "--------0---------" >> log.txt
#                     echo "$TEST0" >> log.txt
#                     echo "------------------" >> log.txt
#                     (( COUNTER_FAIL++ ))
#                 fi
#             ((NUMBER++))
#             rm s21_grep.txt grep.txt
#             fi
#         done
#     done
# done



echo SUCCESS $COUNTER_SUCCESS
echo FAIL $COUNTER_FAIL