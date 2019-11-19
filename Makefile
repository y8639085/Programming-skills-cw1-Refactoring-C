CC=	gcc -O3
LDFLAGS=-lcunit
CFLAGS= -g
LFLAGS= -lm

SRCDIR= src
TESTDIR= test
INC=	-I$(SRCDIR) -I$(TESTDIR) -I$(HOME)/include

OBJS=	percolate.o \
	arralloc.o \
	uni.o
TESTS=	percolate_cunit_test.o

percolate: $(OBJS) percolate_program.o
	$(CC) -o $@ $^ $(INC) $(CFLAGS) $(LFLAGS)

percolate-tests: $(OBJS) $(TESTS) cunit_test_driver.o
	$(CC) -o $@ $^ $(INC) $(LDFLAGS)

%.o :   $(SRCDIR)/%.c
	$(CC) -c $^ -o $@ $(INC)
%.o :   $(TESTDIR)/%.c
	$(CC) -c $< -o $@ $(INC)

.PHONY : xunit-report
xunit-report :
	xsltproc -novalid cunit-to-junit.xsl CUnitAutomated-Results.xml > TestResults.xml

.PHONY : test
test : percolate-tests
	./$<

.PHONY : all
all : percolate test

.PHONY : clean
clean :
	rm -f percolate
	rm -f percolate-tests
	rm -f map.*
	rm -f testlog.*
	rm -f CUnit*.xml
	rm -f TestResults.xml
	rm -f *.o
	rm -f *~
	rm -f src/*~
	rm -f test/*~
