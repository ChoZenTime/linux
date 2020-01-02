#! /bin/bash 
#compton --config ~/.config/compton/compton.conf &
picom --config ~/.dwm/picom.conf &
nitrogen --restore &
urxvtd -q -o -f &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
/usr/lib/xfce4/notifyd/xfce4-notifyd &
run xfce4-power-manager &
numlockx on &

dte(){
  #dte="$(date +"%A, %B %d | 🕒 %k:%M%p")"
  dte="$(date "+%a %d %b | 🕒 %H:%M")"
  echo -e "🗓 $dte"
}

mem(){
  mem=`free -m | awk 'NR==2{printf "%s/ %sMB (%.2f%%)\n", $3,$2,$3*100/$2 }'`   
  echo -e "🖪 $mem mem"
}

cpu(){
  read cpu a b c previdle rest < /proc/stat
  prevtotal=$((a+b+c+previdle))
  sleep 0.5
  read cpu a b c idle rest < /proc/stat
  total=$((a+b+c+idle))
  cpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))
  echo -e "💻 $cpu% cpu"
}


while true; do
     xsetroot -name "$(cpu) | $(mem) | $(dte)"
     sleep 10s    # Update time every ten seconds
done &
