#!/usr/bin/perl

#Gionee taochao 2011-12-31  taochao 
#Modify for compatibility with various platforms. 
#If you want to add some plateform,you can add a string in the gn_platform_type
#Gionee xiangzhong 2012-05-10 add "GFE" for GFE790 project
#Gionee liuxw 2013-02-17  modify for compatibility with various projects
@gn_platform_type = ("CB","GB","GF","GN","WB","WF","WQ","NB");

$pmPath = "gn_project";
chdir($pmPath);
@files = <*>;
$i = 0;
foreach $f (@files) {

	#Gionee taochao 2011-12-31  taochao modify for compatibility with various platforms
	$result = 1;
	foreach $type (@gn_platform_type) {
		$result = $result && $f !~ /^$type.*\.mk$/;
	}
    next if ( $result );
    $f =~ /(.*)\.mk/;
    print $1;
    $i++;
    if ($i%3 == 0) {
        print "\n";
    } else {
        print " " x (26-length $f);
    }
}
if ($i%3 != 0) {
    print "\n";
}

exit 0;
