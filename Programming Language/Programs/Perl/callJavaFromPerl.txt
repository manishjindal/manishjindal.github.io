# Returns DFS root to access network path
sub getDFSRoot() {
    return "//inh.india.mentorg.com/dfs";
}

# Returns tools home path
sub getGridToolsHome() {
    return getDFSRoot()."/project/iesd_grid/ScriptsRoot/AutomationScripts/chsgridtools";
}

# Returns tools lib path
sub getGridToolsLib() {
    return getGridToolsHome()."/lib";
}

sub setClasspath {
    my $classpath = getGridToolsLib()."/*";	#program will try to find chs.CHSConfigFileMgr in the mentioned here. 
    print "classpath => $classpath\n";
    #logMsg("Setting CLASSPATH = ".$classpath);

    $ENV{CLASSPATH} = $classpath;

    print "env => $ENV{CLASSPATH}\n";
}


# Returns Java Home to be used
sub getJavaHome() {
    return "c:/apps/Java/jdk1.8.0_66";
}


sub updateManagerProps {
	setClasspath();
	my $propFile = "C:/GitRepository/iesd-16.1/chs_home/config/chsprops-test.xml";
	 my $cmd = getJavaHome()."/bin/java"
        ." chs.CHSConfigFileMgr"
        ." $clientProps"
        ." $propFile"
		." cer=true"
        ." cerport=48101"
        ." securecerport=48201"
        ." cis=true"
        ." cisport=48401"
        ." analysis=false";

    print "Executing => $cmd\n";
    my @lines = qx/$cmd/;
    print @lines;
}

updateManagerProps();