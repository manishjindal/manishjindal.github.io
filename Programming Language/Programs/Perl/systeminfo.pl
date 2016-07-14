sub isSystemVM {
    my @lines = qx/systeminfo/;
    my @list = grep(/^OS Name/,@lines);
    print @list;
    if ($list[0] =~ /server/){
        return false;
    }
    return true;
}

sub getsysteminfo {

	if (!isSystemVM){
		print "running on grid";
	}else {
		print "running on VM";
	}

}

getsysteminfo();
