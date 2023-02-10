#!/bin/bash

#take a menu number, that number do it's shape making


#function definnition

print_tri()                                         #print triangle function
{
 for ((i=1; i<=4; i++))                             #i=1~4
 do 
    for ((j=4 - $i; j>0; j--))                      #j=3~1 
    do
      printf " "                                    #print null
    done 

    for ((k=0; k<$i \* 2 - 1; k++))   