JC=javac
CLASSPATH=.:sce
sources=$(wildcard *.java)
classes=$(sources:.java=.class)

all: $(classes)

%.class: %.java
	$(JC) -cp $(CLASSPATH) $<

clean:
	rm -f *.class
