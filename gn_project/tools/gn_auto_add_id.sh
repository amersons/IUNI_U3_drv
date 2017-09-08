#!/bin/bash

#gn_strings_xml="frameworks/base/core/res/res/values/strings.xml"
gn_string_buffer_size="0xFF"            #0x010400ff ~ 0x01040000
if [ -f "$gn_strings_xml" ];then
    if `! grep -rwq "Gionee lingfen add for strings id buffer start" $gn_strings_xml` ;then
        sed -i "/<\/resources>/i\\\t<!-- Gionee lingfen add for strings id buffer start-->" $gn_strings_xml
        for((i=0; i<=$gn_string_buffer_size; i++))
        do
            sed -i "/<\/resources>/i\\\t<string name=\"zzzzz_gionee_buffer${i}\">gn_buf${i}<\/string>" $gn_strings_xml
        done
        sed -i "/<\/resources>/i\\\t<!-- Gionee lingfen add for string id buffer end-->" $gn_strings_xml
    fi
fi

#gn_ids_xml="frameworks/base/core/res/res/values/ids.xml"
gn_ids_buffer_size="0xFF"               #0x010200ff ~ 0x01020000
if [ -f "$gn_ids_xml" ];then
    if `! grep -rwq "Gionee lingfen add for ids buffer start" $gn_ids_xml` ; then
        sed -i "/<\/resources>/i\\\t<!-- Gionee lingfen add for ids buffer start-->" $gn_ids_xml
        for((i=0; i<=$gn_ids_buffer_size; i++))
        do
            sed -i "/<\/resources>/i\\\t<item type=\"id\" name=\"zzzzz_gionee_buffer${i}\" \/>" $gn_ids_xml
        done
        sed -i "/<\/resources>/i\\\t<!-- Gionee lingfen add for ids buffer end-->" $gn_ids_xml
    fi
fi

#gn_dimens_xml="frameworks/base/core/res/res/values/dimens.xml"
gn_dimens_buffer_size="0xFF"            #0x010500ff ~ 0x01050000
if [ -f "$gn_dimens_xml" ];then
    if `! grep -rwq "Gionee lingfen add for dimens id buffer start" $gn_dimens_xml` ;then
        sed -i "/<\/resources>/i\\\t<!-- Gionee lingfen add for dimens id buffer start-->" $gn_dimens_xml
        for((i=0; i<=$gn_dimens_buffer_size; i++))
        do
            sed -i "/<\/resources>/i\\\t<dimen name=\"zzzzz_gionee_buffer${i}\">1${i}dp<\/dimen>" $gn_dimens_xml
        done
        sed -i "/<\/resources>/i\\\t<!-- Gionee lingfen add for dimens id buffer end-->" $gn_dimens_xml
    fi
fi

gn_styles_xml="frameworks/base/core/res/res/values/styles.xml"
gn_styles_buffer_size="0xFF"        #0x010302d0 ~ 0x010301d0  
if [ -f "$gn_styles_xml" ];then
    if `! grep -rwq "Gionee lingfen add for styles buffer start" $gn_styles_xml` ;then
        sed -i "/<\/resources>/i\\\t<!-- Gionee lingfen add for styles buffer start-->" $gn_styles_xml
        for((i=0; i<=$gn_styles_buffer_size; i++))
        do
            sed -i "/<\/resources>/i\\\t<style name=\"zzzzz_gionee_buffer${i}\" \/>" $gn_styles_xml
        done
        sed -i "/<\/resources>/i\\\t<!-- Gionee lingfen add for styles buffer end-->" $gn_styles_xml
    fi
fi

gn_attrs_xml="frameworks/base/core/res/res/values/attrs.xml"
gn_attrs_buffer_size="0xFF"        #0x0101034a0 ~ 0x0101033a0
if [ -f "$gn_attrs_xml" ];then
    if `! grep -rwq "Gionee lingfen add for attrs id buffer start" $gn_attrs_xml` ;then
        sed -i "/<\/resources>/i\\\t<!-- Gionee lingfen add for attrs id buffer start-->" $gn_attrs_xml
        sed -i "/<\/resources>/i\\\t<declare-styleable name=\"GioneeBuffer\">" $gn_attrs_xml
        for((i=0; i<=$gn_attrs_buffer_size; i++))
        do
            sed -i "/<\/resources>/i\\\t<attr name=\"zzzzz_gionee_buffer${i}\" format=\"reference\" \/>" $gn_attrs_xml
        done
        sed -i "/<\/resources>/i\\\t<\/declare-styleable>" $gn_attrs_xml
        sed -i "/<\/resources>/i\\\t<!-- Gionee lingfen add for attrs id buffer end-->" $gn_attrs_xml
    fi
fi

#放入N个zzzzz_gionee_buffer.png
#gn_drawable_dir="frameworks/base/core/res/res/drawable"
#gn_drawable_files_counts="0xFF"
#if [ -d "$gn_drawable_dir" ];then
#    for((i=0; i<=$gn_drawable_files_counts; i++))
#    do
#        #create counts png files
#        :
#    done
#
#fi
#做出N个layout.xml文件

