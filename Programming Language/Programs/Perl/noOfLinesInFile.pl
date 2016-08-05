sub lineCount {

	my $file = "./test.txt";
	my $lines = `wc -l < $file`;
	print "number of lines".$lines;

}

lineCount();