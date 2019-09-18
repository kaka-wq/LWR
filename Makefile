OPENSSL_DIR=/usr
CC=cc

OPENSSL_INCLUDE_DIR=$(OPENSSL_DIR)/include
OPENSSL_LIB_DIR=$(OPENSSL_DIR)/lib

CFLAGS=-O2  -Wall  -I$(OPENSSL_INCLUDE_DIR) # -DDEBUG_LOGS
LDFLAGS=-L$(OPENSSL_LIB_DIR) -lcrypto -lssl

all:
	#$(CC) $(CFLAGS) -o generate_a generate_a.c $(LDFLAGS) 
	$(CC) $(CFLAGS) -c cpucyclesprint.c $(LDFLAGS) 
	$(CC) $(CFLAGS) -c changefrodoh.c $(LDFLAGS) 
	$(CC) $(CFLAGS) -c gena.c $(LDFLAGS) 
	$(CC) $(CFLAGS) -c keygensharedadb.c $(LDFLAGS) 
	$(CC) $(CFLAGS) -c recsameorno.c $(LDFLAGS) 
	$(CC) $(CFLAGS) -o test cpucyclesprint.o changefrodoh.o gena.o keygensharedadb.o recsameorno.c $(LDFLAGS) 

test: all
	./test

clean:
	rm -f *.o
	#rm -f generate_a
	rm -f test

prettyprint:
	astyle --style=java --indent=tab --pad-header --pad-oper --align-pointer=name --align-reference=name --suffix=none *.c *.h
