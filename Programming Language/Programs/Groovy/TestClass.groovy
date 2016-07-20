/*
	Everything looks much like Java, except there’s no accessibility modifier: methods are
	public by default.

*/


class Book {

	private String name 
	void setName(String bookName) {
		name=bookName
		print "Book Name => "+bookName+"\n";
	}

	String getName(){

		return name;
	}
}

class GroovyWay {
	private String title;
}


class TestClass {

	static  main(args) {
		def a = 5
		def b = 'abe';
		print a + "\n";
		print "$a"+"\n"
		print "$b is equal to abe";
		//print args[0]

		Book t = new Book();
		t.setName("First Book");
		print "book title=>"+t.getName()+"\n"

		GroovyWay gw = new GroovyWay(title:"mjindal");
		print "Title set in grrovy way = > " + gw.title + "\n";

		print gw.title.reverse() + "\n";

	}
}
