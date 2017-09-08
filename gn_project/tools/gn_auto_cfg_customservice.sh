#!/bin/bash
#
#       DESCRIPTION:   To generate Product Configuration information html file 
#
#       SCRIPT NAME:    gn_auto_cfg_customservice.sh
#
#       Usage:  gn_auto_cfg_customservice.sh  $dirname
#                
#
#       Input:  stdin
#                       1. dirname
#
#       Output:         html file
#
#       AUTHOR:         Ling Fen
#
#       EMAIL:          lingfen@gionee.com
#
#       DATE:           2013-3-8
#
#       HISTORY:
#       REVISOR         DATE                    MODIFICATION
#       LingFen         2012-8-5              create

usage(){
printf "
Download the specified code from svn server

Usage : $0 

options:
    [--help] Show help message

example: 
"
}
get_opts(){
    opts=$(getopt -o h --long help -- "$@")     
    if [ $? -ne 0 ];then
        usage 
        exit 1
    fi

    eval set -- "$opts"
    while true 
    do
        case "$1" in 
            -h|--help)
                usage
                exit 0
                ;;
            --)
                shift
                break
                ;;
            *)
                usage
                exit 1
                ;;
        esac
    done
    GN_CUSTOMSERVICE_PATH_DIR=$1
}

create_html(){
    local png_path_file=$1
    png_path_dir=$(dirname $png_path_file)  
    png_file=$(basename $png_path_file)
    png_name=${png_file%.*}
    html_file=${png_name}.html
    
    png_parent_dir_name=$(basename $png_path_dir)

    #offset
    png_file_counts=$(ls $png_path_dir/*.png|wc -l)
    #png_offset=$(echo "scale=1;$png_file_counts * 15 / 2" | bc)

    #input style info
    [ ! -f "$png_path_dir/$png_parent_dir_name.txt" ] && return 
    unset size head body
    eval $(sed -n "/id=$png_file/,/body/p" $png_path_dir/$png_parent_dir_name.txt)

cat >$png_path_dir/$html_file<<EOF
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>

<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>1</title>
<style type="text/css">
<!--.dot { position:absolute; top:94%; left:50%; margin:0 0 0 -${size}px;}
.phone { position:absolute; top:22%; left:50%; margin:0 0 0 -160px;}
.STYLE2 {font-size: x-large}
.STYLE3 {font-size: large}
-->
</style>
</head>

<body>
<table width="100%" height="100%" border="0" style="padding:0">
<tr >
<td><span class="STYLE2">$head</span></td>
</tr>
<tr>
<td><span class="STYLE3">$body</span></td>
</tr>
</table>
<div class="phone">
<tr>
<td><img src="$png_file" width="320" height="360"/></td>
</tr>
</div>
<div class="dot">
<tr>
<td>
`for((i=1; i<=$png_file_counts; i++))
do
if [ "$i" -eq "$png_name" ];then
echo '<img src="../img/dot_selected.png" width="15" height="15"/>'
else
echo '<img src="../img/dot.png" width="15" height="15"/>'
fi
done
`
</td>
</tr>
</div>
</body>
</html>
EOF
}

main(){
   get_opts "$@" 
   while read file
   do
        create_html $file
   done < <(find $GN_CUSTOMSERVICE_PATH_DIR -name "*.png" | sort)
}

GN_CUSTOMSERVICE_PATH_DIR=

main "$@"
