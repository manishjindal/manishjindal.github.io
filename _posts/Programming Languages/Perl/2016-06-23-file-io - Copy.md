---
layout: perl
title: Reading and Writting to a file in perl
detail: Write a function to read from one file and write to another file
meta: Write a function to read from one file and write to another file
source:
category: Syntax
---

sub readFromOneFileAndToWriteAnotherFile {

	open(READING_FROM,"./fileToRead.txt");
	open(WRITTING_TO,">./fileToWrite.txt");
	
	while(<READING_FROM>) {
			print $_;
			print WRITTING_TO "$_\n";
		}
	close READING_FROM;
	close WRITTING_TO;
}

readFromOneFileAndToWriteAnotherFile();