all: kupyna_test

test: kupyna_test
	./kupyna_test

kupyna_test: kupyna512.o kupyna256.o kupyna_tables.o kupyna_test.o
	$(CC)  $^ -lcunit $(LDFLAGS) -o "$@"

%.o: %.c
	$(CC) $(CPPFLAGS) -std=c11 $(CFLAGS) -c "$<" -o "$@"

clean:
	-rm -f kupyna512.o kupyna256.o kupyna_tables.o kupyna_test.o kupyna_test
