
#!/bin/bash

declare -i width=120                                                #set frame width
declare -i length=25                                                #set frame length
declare -i px                                                       #set present x
declare -i py                                                       #set present y
declare -i ax=20                                                    #set addition for x
declare -i ay=6                                                     #set addition for y
declare -i cx                                                       #declare cursor x
declare -i cy                                                       #declare cursor y

p_f_list=`ls -a | grep '\.\.'; ls -1F | grep '/$'; ls -1F | grep '*$'; ls -1F | grep -v '[/*|]$'`  #present file list < directory
for AB in *
do
  if [ -d $AB ]
  then
    $NULL
  elif [ -f $AB ]
  then
    $NULL
  else
    p_f_list="$p_f_list $AB"                                        #to deal with special file
  fi
done
a_list=($p_f_list)                                                  #make array 

print_equal(){                                                      #print =====...
  printf " "
  for ((line=1 ; line<$width ; line++))
  do
    printf "="
  done
  printf "\n"
}
 
make_frame(){                                                       #print total frame
  clear                                                             #first, clear terminal
 
  print_equal                                                       
  for ((i=0 ; i<$length ; i++))
  do
    echo "|                   |"                                    #print 1st left right frame
    tput cup `expr $i + 1` $width                                   #print 2nd right frame
    echo "|"
  done
  tput cup 0 20                                                     #no connection with length, so x represent 20
  printf " "
  tput cup $i $width
  printf " "
  tput cup $i 0
 
  print_equal                                                       
  for ((i=`expr $length + 1` ; i<32 ; i++))                         #print 3rd left right frame
  do
    echo "|"
    tput cup $i $width
    echo "|"
  done
  tput cup $length 20
  printf " "
  tput cup $i 0

  print_equal                                                       
  printf "|"                                                        #print 4th left right frame
  tput cup 33 $width
  echo "|"
  print_equal
}

print_4th_inform(){                                                 #print 4th information
  pt_num=`ls | wc -l`                                               #present total number
  pd_num=`ls -lF | grep '/$' | wc -l`                               #present directory number
  ps_num=`ls -lF | grep '|$' | wc -l`                               #present special file number
  pf_num=`expr $pt_num - $pd_num - $ps_num`                         #present file number
  pt_size=`du . | tail -n 1 | head -c 3`                            #present total size
  tput cup 33 30
  echo "$pt_num total   $pd_num directory   $pf_num file   $ps_num s-file   $pt_size total size"