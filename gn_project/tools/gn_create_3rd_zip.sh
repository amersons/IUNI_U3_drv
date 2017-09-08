#!/bin/bash
#Gionee lingfen 20120428 add for CR00585858 start
#TARGET_PRODUCT=msm8625
#GN_3RD_RECOVER_FROM_SDCARD=y
PROJECT_DIR="out/target/product/${TARGET_PRODUCT}"
SDCARD_DIR="${PROJECT_DIR}/tcard"
META_INF_TREE="${SDCARD_DIR}/META-INF/com/google/android"
UPDATER_FILE="${PROJECT_DIR}/obj/EXECUTABLES/updater_intermediates/updater"
UPDATER_SCRIPT="${META_INF_TREE}/updater-script"
UPDATE_BINARY="${META_INF_TREE}/update-binary"
GN_APPS_FILE="${SDCARD_DIR}/.gn_apps.zip"


TESTKEY1="build/target/product/security/testkey.x509.pem"
TESTKEY2="build/target/product/security/testkey.pk8"
TOOLS="out/host/linux-x86/framework/signapk.jar"

create_updater_script(){
#recovery.fstab file
#mount point   fstype      device          [device2]
#
#/boot       mtd           boot
#/cache      yaffs2        cache
#/data       yaffs2        userdata
#/misc       mtd           misc
#/recovery   mtd           recovery
#/sdcard     vfat          /dev/block/mmcblk0p1    /dev/block/mmcblk0
#/system     yaffs2        system

recovery_fstab="$PROJECT_DIR/recovery/root/etc/recovery.fstab"
info=(`cat $recovery_fstab | awk '$2 ~ /\/data/ {print $0}'`)

MOUNT_POINT=${info[1]}
FS_TYPE=${info[2]}
DEVICE=${info[0]}
PARTITION_TYPE="EMMC"

if [ -z "$MOUNT_POINT" -o -z "$FS_TYPE" -o -z "$DEVICE" -o -z "$PARTITION_TYPE" ];then
    echo "device info error. don't mount the device"
    echo "create updater_script error"
    return
fi

cat > $1 <<EOF
ui_print("install gionee 3rd start...");

ui_print("mount device:",mount("$FS_TYPE","$PARTITION_TYPE", "$DEVICE", "$MOUNT_POINT"));
package_extract_dir("system/gn_app_bk", "/data/app");
set_perm_recursive(1000,1000,0751,0644,"/data/app");
unmount("$MOUNT_POINT");

ui_print("install gionee 3rd end");
EOF
}

if [ -d "${SDCARD_DIR}" -a "${GN_3RD_RECOVER_FROM_SDCARD}" == "y" ];then
    #build META-INF tree 
    mkdir -p ${META_INF_TREE}
    cp ${UPDATER_FILE} ${UPDATE_BINARY}
    create_updater_script ${UPDATER_SCRIPT}
    
    #build 3rd_tmp.zip package
    rm -rf /tmp/3rd_tmp.zip
    cd ${SDCARD_DIR}
    find system -type f | zip -q "/tmp/3rd_tmp.zip" -@
    find META-INF -type f | zip -q "/tmp/3rd_tmp.zip" -@
    cd - > /dev/null

    #Encryption
    java -jar $TOOLS -w $TESTKEY1 $TESTKEY2 "/tmp/3rd_tmp.zip" "${GN_APPS_FILE}"
    rm -rf /tmp/3rd_tmp.zip
fi
#Gionee lingfen 20120428 add for CR00585858 end
