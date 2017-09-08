factory=`cat ~/trunk/alps/alps_google/gionee/alps_drv/build/tools/factoryver`
let factory+=1
echo $factory>~/trunk/alps/alps_google/gionee/alps_drv/build/tools/factoryver
echo "ro.gn.gnznvernumber=NBW8902A01_A_T"$factory

