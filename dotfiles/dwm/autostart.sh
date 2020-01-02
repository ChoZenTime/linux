#! /bin/bash 
#compton --config ~/.config/compton/compton.conf &
picom --config ~/.dwm/picom.conf &
nitrogen --restore &
urxvtd -q -o -f &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
/usr/lib/xfce4/notifyd/xfce4-notifyd &
run xfce4-power-manager &
numlockx on &
#start dwm-bar-scripts
/home/xen/dwm-bar/dwm_bar.sh &