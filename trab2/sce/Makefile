JC=javac
sources=$(wildcard *.java)
classes=$(sources:.java=.class)

all: $(classes)

%.class: %.java
	$(JC) $<

clean:
	rm -f *.class
