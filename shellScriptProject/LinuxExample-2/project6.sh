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
  for ((line=1 ; line<$width ; line++))
  do
    printf "="
  done
  printf "\n"
}
 
make_frame(){                                                         #print total frame
  clear                                                               #first, clear terminal
 
  print_equal                                                       
  for ((i=0 ; i<$length ; i++))
  do
    echo "|                   |"                                      #print 1st left right frame
    tput cup `expr $i + 1` $width                                     #print 2nd right frame
    echo "|"
  done
  tput cup 0 20                                                       #no connection with length, so x represent 20
  printf " "
  tput cup $i $width
  printf " "
  tput cup $i 0
 
  print_equal                                                       
  for ((i=`expr $length + 1` ; i<`expr $length + 7` ; i++))           #print 3rd left right frame
  do
    echo "|"
    tput cup $i $width
    echo "|"
  done
  tput cup $length 20
  printf " "
  tput cup $i 0

  print_equal                                                       
  printf "|"                                                          #print 4th left right frame
  tput cup `expr $i + 1` $width
  echo "|"
  print_equal
}

print_4th_inform(){                                                   #print 4th information
  pt_num=`ls | wc -l`                                                 #present total number
  pd_num=`ls -lF | grep '/$' | wc -l`                                 #present directory number
  ps_num=`ls -lF | grep '|$' | wc -l`                                 #present special file number
  pf_num=`expr $pt_num - $pd_num - $ps_num`                           #present file number
  pt_size=`du -h . | tail -n 1 | head -c 4`                              #present total size
  tput cup 38 30
  echo "$pt_num total   $pd_num directory   $pf_num file   $ps_num s-file   $pt_size total size"
#  tput cup 31
}

print_1st_inform(){                                                   #print 1st information
  declare -i i=2
  p_dir=`pwd`
  cd ..
  tput cup `expr $i - 1` 1
  tput setaf 1
  echo ".."
  
  for up_file in *                                                    #upper directory files
  do
    tput cup $i 1
    if [ -d $up_file ]
    then
      tput setaf 4
      echo "$up_file" | cut -b -10                                        
    elif [ -f $up_file ]
    then
      if [ -x $up_file ]
      then
        tput setaf 1
        echo "$up_file" | cut -b -10                                       
      else
        tput setaf 7
        echo "$up_file" | cut -b -10                                    
      fi
    else
      tput setaf 2
      echo "$up_file" | cut -b -10                                         
    fi
    tput setaf 7
    i=`expr $i + 1`
    
    if [ $i -eq 22 ]                                                  #if over 20 line, break
    then
      break
    fi
  done
  cd $p_dir
}

print_3rd_inform(){                                                   #print 3rd information
  tput cup `expr $length + 1` 30
  echo "file name : `stat -c %n ${a_list[$I]}`"
  tput cup `expr $length + 2` 30
   if [ -d ${a_list[$I]} ]
     then
       echo -e [34m"file type : `stat -c %F ${a_list[$I]}`"         #]
     elif [ -f ${a_list[$I]} ]
     then
       if [ -x ${a_list[$I]} ]
       then
         echo -e [31m"file type : `stat -c %F ${a_list[$I]}`"       #]
       else
         echo -e [0m"file type : `stat -c %F ${a_list[$I]}`"        #]
       fi
     else
       echo -e [32m"file type : `stat -c %F ${a_list[$I]}`"         #]
   fi
  tput cup `expr $length + 3` 30
  echo -e [0m"file size : `stat -c %s ${a_list[$I]}`"               #]
  tput cup `expr $length + 4` 30
  echo "modification time : `stat -c %y ${a_list[$I]}`"
  tput cup `expr $length + 5` 30
  echo "permition : `stat -c %a ${a_list[$I]}`"
  tput cup `expr $length + 6` 30
  echo "absolute path : `realpath -e ${a_list[$I]}`"
  tput cup $cy $cx
}

print_d_icon(){                                                       #print direcory icon / blue color
  if [ -d ${a_list[$i+$scroll*5]} ]
  then
    if [ "${a_list[$i+$scroll*5]}" = ".." ]
    then
      tput setaf 1
      if [ `expr $py + 4` = $cy ] && [ $px == $cx ]                   #if selected
      then
        tput rev
      fi
      echo '  -----'                                              
      tput cup `expr $py + 1` $px
      echo '--    -'
      tput cup `expr $py + 2` $px
      echo '-  D  -'
      tput cup `expr $py + 3` $px
      echo '-------'
      tput cup `expr $py + 4` $px
      echo `