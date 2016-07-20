sub defineHash {
	%firsthash = ('fname',"manish",'mname',"kumar",'lname',"jindal");
	
	print "Firstname => $firsthash{'fname'} \n";
	print "Middlename => $firsthash{'mname'} \n";
	print "Lastname => $firsthash{'lname'} \n";
	$firsthash{'RUNNING_ON_VM'}=1;
	print $firsthash{'RUNNING_ON_VM'};

	if (defined($firsthash{'RUNNING_ON_VM'})){
		print "defined";
	}

	if (defined($firsthash{'RUNNING_ON_GRID'})) {
		print "defined";
	}
	else{
		print "not defined";
	}
}

sub iterateHash {
	while (my ($key, $value) = each %CONFIG) {
		print "$key"."="."$value\n";
	}
}

defineHash();
iterateHash();