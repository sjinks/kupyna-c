all: kupyna_test

test: kupyna_test
	./kupyna_test

benchmark: kupyna_benchmark
	./kupyna_benchmark

kupyna_test: kupyna512.o kupyna256.o kupyna_tables.o kupyna_test.o
	$(CC) $^ -lcunit $(LDFLAGS) -o "$@"

kupyna_benchmark: kupyna512.o kupyna256.o kupyna_tables.o kupyna_benchmark.o
	$(CC) $^ $(LDFLAGS) -o "$@"

%.o: %.c
	$(CC) $(CPPFLAGS) -std=c99 $(CFLAGS) -c "$<" -o "$@"

clean:
	-rm -f kupyna512.o kupyna256.o kupyna_tables.o kupyna_test.o kupyna_benchmark.o kupyna_test kupyna_benchmark
