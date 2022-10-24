#!/bin/bash

declare -i width=120                                                  #set frame width
declare -i length=30                                                  #set frame length
declare -i px                                                         #set present x
declare -i py                                                         #set present y
declare -i ax=20                                                      #set addition for x
declare -i ay=6                                                       #set addition for y
declare -i cx                                                         #declare cursor x
declare -i cy                                                         #declare cursor y
a_c=("$null" "$null" "$null" "$null")                                 #array for copy
a_m=("$null" "$null" "$null" "$null")                                 #array for move

set_base(){
  p_f_list=`ls -a | grep '\.\.'; ls -1F | grep '/$'; ls -1F | grep '*$'; ls -1F | grep -v '[/*|]$'`  #present file list < directory
  for AB in *
  do
    if ! [ -d $AB ] && ! [ -f $AB ]
    then
      p_f_list="$p_f_list $AB"                                        #to deal with special file
    fi
  done
  a_list=($p_f_list)
}

print_equal(){                                                        #print =====...
  printf " "
  for ((line=1 ; line<$wid