javac -cp ".:201305578_src/gsp.jar" 201305578_src/*.java
java -cp "201305578_src:201305578_src/gsp.jar" DBSystem "$1"
