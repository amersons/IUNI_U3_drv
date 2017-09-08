#!/bin/bash
#################################################
#
if [ -z "${GIONEEPRODUCTID}" ]; then
    echo "*** procuction invalid. ***"
    exit 1
else
    rm -rf "./packages"
    VENDOR="$1"
    [ -n "$2" ] && PLATFORM_VERSION="_$2"
fi

copy_to_alps(){
    sourcedir="$1"
    destdir="$2"
    if [ -d "$sourcedir" ];then
        cd $sourcedir
        find . -path "*\.svn" -prune -o -type f -follow -print | cpio -pdmu $destdir
        cd - &>/dev/null
    fi
}

if [ -z "${GN_APPS_NAME}" ]; then
    GN_APPS_NAME="packages_qc_kk_qct8974" 
    if [ -d "../${GN_APPS_NAME}" ];then
        ln -f -s "../${GN_APPS_NAME}/packages" "./packages"
    else
        echo "*** Link package directory error ***" >&2
        exit 1
    fi
fi

alps_dir=`pwd`
####add by wangyong for IUNI version
if [ "${GIONEEPRODUCTID:(-4):4}" == "IUNI" ]; then
    if [ -d "../aurora_data" ];then
             ln -f -s "../aurora_data" "./aurora_data"
    else
             echo "*** Link aurora_data  directory error ***" >&2
             exit 1
    fi
            copy_to_alps "./gionee/alps_IUNI/" "$alps_dir"
fi
####end by wangyongliang
 
#copy gionee/alps_drv to alps 
echo "copy ./gionee/alps_drv to alps."
copy_to_alps "./gionee/alps_drv" $alps_dir

#copy gionee/{projectID}_drv to alps 
if [ -d "./gionee/project/${GIONEEPROJECTID}_drv" ];then
    echo "copy ./gionee/project/${GIONEEPROJECTID}_drv to alps."
    copy_to_alps "./gionee/project/${GIONEEPROJECTID}_drv" "$alps_dir"
fi

#copy gionee/alps/alps_cta/alps_cmcc/alps_platform to alps
if [ "${BUILD_OPTIONS}" == "platform" -a "${GIONEEPRODUCTID:(-8):8}" == "platform" ];then
    echo "copy ./gionee/alps_platform to alps."
    copy_to_alps "./gionee/alps_platform" "$alps_dir"
elif [ "${BUILD_OPTIONS}" == "platform" -a "${GIONEEPRODUCTID:(-3):3}" == "CTA" ];then
    echo "copy ./gionee/alps_cta to alps."
    copy_to_alps "./gionee/alps_cta" "$alps_dir"
elif [ "${BUILD_OPTIONS}" == "platform" -a "${GIONEEPRODUCTID:(-4):4}" == "CMCC" ];then
    echo "copy ./gionee/alps_cmcc to alps."
    copy_to_alps "./gionee/alps_cmcc" "$alps_dir"
else
   echo "copy ./gionee/alps/ to alps."
    copy_to_alps "./gionee/alps/" "$alps_dir"
fi

#copy gionee/{projectID} to alps 
echo "copy ./gionee/project/${GIONEEPROJECTID} to alps."
copy_to_alps "./gionee/project/${GIONEEPROJECTID}" "$alps_dir"

#copy gionee/{productID} to alps 
if [ -d "./gionee/project/${GIONEEPRODUCTID}" ];then
    echo "copy ./gionee/project/${GIONEEPRODUCTID} to alps."
    copy_to_alps "./gionee/project/${GIONEEPRODUCTID}" "$alps_dir"
fi



if [ "${BUILD_OPTIONS}" != "platform" ];then
    #copy gionee/alps_oversea to alps
    if [ "${GN_OVERSEA_PRODUCT}" == "yes" ];then
        copy_to_alps "./gionee/alps_oversea/" "$alps_dir"
    fi

    #copy gionee/{projectID}_alps to alps 
    if [ -d "./gionee/project/${GIONEEPROJECTID}_alps" ];then
        echo "copy ./gionee/project/${GIONEEPROJECTID}_alps to alps."
        copy_to_alps "./gionee/project/${GIONEEPROJECTID}_alps" "$alps_dir"
    fi

    #copy gionee/{productID}_alps to alps 
    if [ -d "./gionee/project/${GIONEEPRODUCTID}_alps" ];then
        echo "copy ./gionee/project/${GIONEEPRODUCTID}_alps to alps."
        copy_to_alps "./gionee/project/${GIONEEPRODUCTID}_alps" "$alps_dir"
    fi

    #copy gionee/gnframework to alps/gnframework
    #copy gionee/amigoframework to alps/amigoframework
    echo "copy ./gionee/gnframework/ to alps/gnframework/"
    copy_to_alps "./gionee/gnframework/" "$alps_dir/gnframework/" 
    echo "copy ./gionee/amigoframework/ to alps/amigoframework/"
    copy_to_alps "./gionee/amigoframework/" "$alps_dir/amigoframework/"

    #Gionee lingfen 20130925 add for CR00886949 start 
    if [ -d "./gionee/Amigo_Framework/" ];then
        rm -rf "$alps_dir/amigoframework/"
        copy_to_alps "./gionee/Amigo_Framework/" "$alps_dir/amigoframework/"
    fi
    #Gionee lingfen 20130925 add for CR00886949  end
else
    echo "*****platform*****"
fi

if [ "${BUILD_OPTIONS}" != "platform" ]
then

    #copy platform to alps
    if [ -d "../${GN_APPS_NAME}/platform" ];then
        copy_to_alps "../${GN_APPS_NAME}/platform/common"  "$alps_dir"
        copy_to_alps "../${GN_APPS_NAME}/platform/${VENDOR}" "$alps_dir"
    fi

    #copy packages to alps
    if [ -d "../${GN_APPS_NAME}/packages" ];then
        copy_to_alps "../${GN_APPS_NAME}/packages/common/" "$alps_dir"
    fi

    #copy gionee packages to alps
    if [ -d "../${GN_APPS_NAME}/packages/${VENDOR}/gionee_apps" ];then
        copy_to_alps "../${GN_APPS_NAME}/packages/${VENDOR}/gionee_apps/" "$alps_dir"
    fi

    #unzip gn_image.zip and copy to alps
    if [ -e "../${GN_APPS_NAME}/gn_image/gn_img_"${GIONEEPRODUCTID}".zip" ]
    then
        unzip -o -q ../${GN_APPS_NAME}/gn_image/gn_img_"${GIONEEPRODUCTID}".zip  -d ../${GN_APPS_NAME}/gn_image
        if [ -d "../${GN_APPS_NAME}/gn_image/gn_img" ];then
            find ../${GN_APPS_NAME}/gn_image/gn_img -type f -name "Thumbs.db*" | xargs rm -rf
            copy_to_alps "../${GN_APPS_NAME}/gn_image/gn_img" "$alps_dir"
        else
            echo "*** gn_image dirs tree error ***"
        fi
    fi

    #GIONEE: dingwen 20120724 add oversea folder begin
    #GIONEE: luohui 2013-02-03 modify for android4.0/4.1 build oversea start->
    if [ "${GN_OVERSEA_PRODUCT}" == "yes" ];then
        ANDROID_VERSION="$2"
        copy_to_alps "../${GN_APPS_NAME}/gn_config/product_data/oversea/COMMON/${ANDROID_VERSION}/" "$alps_dir"

        if [ "${GN_OVERSEA_ODM}" == "yes" ];then
            copy_to_alps "../${GN_APPS_NAME}/gn_config/product_data/oversea/ODM/${ANDROID_VERSION}/" "$alps_dir"
        else
            copy_to_alps "../${GN_APPS_NAME}/gn_config/product_data/oversea/GIONEE/${ANDROID_VERSION}/" "$alps_dir"
        fi

        copy_to_alps "../${GN_APPS_NAME}/gn_config/product_data/${GIONEEPROJECTID}" "$alps_dir"
    fi
    #GIONEE: luohui 2013-02-03 modify for android4.0/4.1 build oversea end<-
    #GIONEE: dingwen 20120724 add oversea folder end

    #copy gn_config to alps
    copy_to_alps "../${GN_APPS_NAME}/gn_config/product_data/${GIONEEPRODUCTID}"  "$alps_dir"

    if [ "${GN_THEME_WHITE_SUPPORT}" == "yes" ];then
        copy_to_alps "../${GN_APPS_NAME}/gn_config/theme_white" "$alps_dir"
    else
        copy_to_alps "../${GN_APPS_NAME}/gn_config/theme_black" "$alps_dir"
    fi

    . `dirname $0`/gn_auto_config.sh
else
    echo "*** platform ***"
fi
