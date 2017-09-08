#!/bin/bash

echo "[VER]" > $2/Gionee_info.ini
if [[ $1 -eq "NBL8910A01_A_IUNI" ]] || [[ $1 -eq "NBL8910A01_A_platform" ]];then
    echo $1 | awk -F '_' '{print "product_info="$1"_"$2}' >> $2/Gionee_info.ini

else
    echo "product_info=$1" >> $2/Gionee_info.ini
fi
chmod 777 $2/Gionee_info.ini
