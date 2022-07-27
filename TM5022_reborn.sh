#!/bin/sh
# TM5022_reborn.sh
urlULD="/home/pi/Desktop/TM5022-ULD"
fileULD="${urlULD##*/}"
urlULDTeacher="/home/pi/Desktop/TM5022-ULD-Teacher"
fileULDTeacher="${urlULD##*/}"
cd
[ -d "$fileULDTeacher" ] && echo "Found" && sudo rm -r "$fileULDTeacher" && echo "Deleted"
cd Desktop
[ -d "$fileULD" ] && echo "Found" && sudo rm -r "$fileULD" && git clone https://github.com/Summer-Lo/TM5022-ULD.git

[ ! -d "$fileULD" ] && echo "Not Found!" && git clone https://github.com/Summer-Lo/TM5022-ULD.git
echo "Completed reborn for TM5022-ULD!"
