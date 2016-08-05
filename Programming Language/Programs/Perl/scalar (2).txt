
sub scalarVariable {

	my $int = 577;
	my $string = "manish";
	my $oct = 0377;
	my $hex = 0xff;

	print $int."\n";
	print $string."\n";
	print $oct."\n";
	print $hex."\n";

	#my %firsthash = {"manish"}
}

sub specialLiterals {
	print __FILE__ . "\n";
	print __LINE__ . "\n";
	print __PACKAGE__ . "\n";
}


scalarVariable();
specialLiterals();

=POD
Special Literals
Three special literals __FILE__, __LINE__, and __PACKAGE__ represent the current filename, line number, and package name 
at that point in your program.

They may be used only as separate tokens and will not be interpolated into strings. Check the below example −

=cut