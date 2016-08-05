sub writeToFile {

	open(DUMMY,'>./temp.txt');

	print DUMMY "first line";
	print DUMMY "second line";
	print DUMMY "third line";
	print DUMMY "fourth line";
	print DUMMY "fifth line";
	print DUMMY "sixth line";
	print DUMMY "seventh line";

	close DUMMY;
}

writeToFile();