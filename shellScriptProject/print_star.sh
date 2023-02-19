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

    for ((k=0; k<$i \* 2 - 1; k++))                 #k=0,2,4...
    do
      printf '*'                                    #print *
    done

    printf "\n"                                     #print \n
 done 
 break;
}

print_squ()                                         #print square
{
 for ((i=1; i<=4; i++))                             #i=1~5
 do 
    for ((j=1; j<=6; j++))                          #j=1~7
    do 
      printf '*'                                    #print *
    done
    printf "\n"                                     #print \n
 done
 break;
}

print_dia()                                         #print diamond
{
 for ((i=1; i<=5; i++))                             #i=1~5
 do 
    if [ $i -le 3 ]                                   #if i<=3
    then
      for ((j=4 - $i; j>0; j--))                    #j=4~1
      do 
        printf " "                                  #print null
      done
    
      for ((k=0; k<$i \*2 - 1; k++))                #k=0,2,4...
      do 
        printf '*'                                  #print *
      d