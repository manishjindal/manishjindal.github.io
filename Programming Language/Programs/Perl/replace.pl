sub replace {

	my $a = "2015.1";
	my $b = $a =~ s/\./\_/r;


	print $b;
}

replace();