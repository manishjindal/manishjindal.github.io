def num = 3

def date = new Date();

print date;
new File('c:/installer_debug.txt').eachLine { line ->
	//println "$line";
}

println ( [String , List , Arrays] *.package *.name )