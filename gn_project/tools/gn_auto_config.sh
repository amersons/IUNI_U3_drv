#!/bin/bash

#Gionee lingfen add for CR00740221 start
if [ -f "system/core/rootdir/init.rc" ];then
    if ! `grep -wq "#Gionee lingfen add for CR00740221 start" system/core/rootdir/init.rc` ;then
        sed -i "/mkdir \/data\/app 0771 system system/a \ \t#Gionee lingfen add for CR00740221 start\n\tmkdir /data/amt 0777 shell system\n\t#Gionee lingfen add for CR00740221  start\n" system/core/rootdir/init.rc
    fi
fi
#Gionee lingfen add for CR00740221 end
#Gionee lingfen 20120930 add for CR00705251 start
#Gionee lichao 20130822 modify for CR00859899 begin
#if [ "${GN_APP_CUSTOMERSERVICE_SUPPORT:0:3}" == "yes" ];then
#    version=${GN_APP_CUSTOMERSERVICE_SUPPORT:4}
if [ "${GN_APK_CUSTOMERSERVICE_SUPPORT:0:3}" == "yes" ];then
    version=${GN_APK_CUSTOMERSERVICE_SUPPORT:4}
    if [ -f "packages/apps/GN_CustomerService$version/assets/product_info.xml" ];then
        file="packages/apps/GN_CustomerService$version/assets/product_info.xml"

        if [ -n "$GN_PRODUCT_INFO_YEAR" ];then
            sed -i "s/2011年/$GN_PRODUCT_INFO_YEAR/"  $file
        fi

        if [ -n "$GN_PRODUCT_INFO_TYPE" ];then
            sed -i "s/3G手机，智能手机，拍照手机/$GN_PRODUCT_INFO_TYPE/"  $file
        fi

        if [ -n "$GN_PRODUCT_INFO_APPEARANCE" ];then
            sed -i "s/直板/$GN_PRODUCT_INFO_APPEARANCE/"  $file
        fi

        if [ -n "$GN_PRODUCT_INFO_SIZE" ];then
            sed -i "s/4.3英寸/$GN_PRODUCT_INFO_SIZE/"  $file
        fi

        if [ -n "$GN_PRODUCT_INFO_SCREEN" ];then
            sed -i "s/电容屏，多点触控/$GN_PRODUCT_INFO_SCREEN/" $file
        fi

        if [ -n "$GN_PRODUCT_INFO_MATERIAL" ];then
            sed -i "s/SUPER AMOLED PLUS/$GN_PRODUCT_INFO_MATERIAL/" $file
        fi

        if [ -n "$GN_PRODUCT_INFO_RESOLUTION" ];then
            sed -i "s/800 x 480像素/$GN_PRODUCT_INFO_RESOLUTION/" $file
        fi
        
        if [ -n "$GN_PRODUCT_INFO_COLOR" ];then
            sed -i "s/26万色/$GN_PRODUCT_INFO_COLOR/" $file
        fi

        if [ -n "$GN_PRODUCT_INFO_NETWORK_TYPE" ];then
            sed -i "s/双卡双模/$GN_PRODUCT_INFO_NETWORK_TYPE/" $file
        fi

        if [ -n "$GN_PRODUCT_INFO_NETWORK_MODE" ];then
            sed -i "s/GSM，WCDMA/$GN_PRODUCT_INFO_NETWORK_MODE/" $file
        fi

        if [ -n "$GN_PRODUCT_INFO_DATA_SERVICE" ];then
           sed -i "s/GPRS，EDGE，HSPA/$GN_PRODUCT_INFO_DATA_SERVICE/"  $file
        fi

        if [ -n "$GN_PRODUCT_INFO_DATA_FREQUENCY" ];then
            sed -i "s@2G，GSM850/900/1800/1900@$GN_PRODUCT_INFO_DATA_FREQUENCY@" $file
        fi
    fi

    if [ -d "packages/apps/GN_CustomerService$version/assets/" ];then
        while read dir
        do
            `dirname $0`/gn_auto_cfg_customservice.sh $dir
        done < <(find packages/apps/GN_CustomerService$version/assets/ -type d )
    fi
fi
#Gionee lichao 20130822 modify for CR00859899 end
#gionee lairufei add to produce Android.mk in packages/apps/GN_system_data/ begin
    system_data_dir="packages/apps/GN_system_data/"
    if [ -d "$system_data_dir" ]
    then
        list_file(){
            dir=$1
            find $dir \( -name "Android.mk" -o -path "*\.svn" \) -prune -o -type f -print|while read file 
        do
            echo -e "\t\$(LOCAL_PATH)/${file##$dir}:system/app/${file##$dir} \\"
        done
    }

    list=$(list_file $system_data_dir)
    if [ -n "$list" ]
    then
        cat > $system_data_dir/Android.mk <<EOF
LOCAL_PATH := \$(call my-dir)
PRODUCT_COPY_FILES += \\
$list
EOF
    fi
    fi
#gionee lairufei add to produce Android.mk in packages/apps/GN_system_data/ end

#Gionee lingfen 20120930 add for CR00705251 end

#Gionee lingfen add for Firm id res start
. `dirname $0`/gn_auto_add_id.sh
#Gionee lingfen add for Firm id res end
