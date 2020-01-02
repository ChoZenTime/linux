#!/bin/sh

# A dwm_bar function to display information regarding system memory, CPU temperature, and storage
# Joe Standring <git@joestandring.com>
# GNU GPLv3

dwm_resources () {

  mem=`free -m | awk 'NR==2{printf "%s/%sMB-> %.2f%%\n", $3,$2,$3*100/$2 }'`   
  echo -e "$SEP1""🖪 $mem""$SEP2"
}

dwm_resources


#mem=`free -m | awk 'NR==2{printf "%s/ %sMB (%.2f%%)\n", $3,$2,$3*100/$2 }'` 