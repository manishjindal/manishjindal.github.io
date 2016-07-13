sub defineHash {
	%firsthash = ('fname',"manish",'mname',"kumar",'lname',"jindal");
	
	print "Firstname => $firsthash{'fname'} \n";
	print "Middlename => $firsthash{'mname'} \n";
	print "Lastname => $firsthash{'lname'} \n";
}

defineHash();