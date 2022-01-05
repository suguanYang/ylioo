#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1048576

static uint8_t* alloc_random_array(size_t len) {

	uint8_t* a = malloc(len);

        size_t i;
	for (i = 0; i < len; ++i)
		a[i] = (random() & 0x7F);

	return a;
}

static bool search_naive(uint8_t key, uint8_t* array, size_t len) {
    uint8_t* end;
	for (end = array + len; array != end; ++array) {
		if (*array == key)
			return true;
	}

	return false;
}

static bool search_knuth(uint8_t key, uint8_t* array, size_t len) {
	array[len] = key;

	uint8_t* end;
	for (end = array + len; *array != key; ++array);

	return array != end;
}

static void do_benchmark(bool (*search)(uint8_t, uint8_t*, size_t),
			 uint8_t key, uint8_t* array, size_t len, int iterations) {
	unsigned long total_time = 0;

        int i;
	for (i = 0; i < iterations; ++i) {
		bool found;
		struct timespec t[2];
		unsigned long time_ns;
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t[0]);
		found = search(key, array, len);
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t[1]);

		time_ns = t[1].tv_nsec - t[0].tv_nsec + 1000000 * (t[1].tv_sec - t[0].tv_sec);
		total_time += time_ns;
		printf("found: %d, took %ld ns\n", found, time_ns);
	}

	printf("average: %.2f ns\n", (float) total_time / iterations);
}

int main(void) {

	uint8_t* array_a = alloc_random_array(ARRAY_SIZE);
	uint8_t* array_b = alloc_random_array(ARRAY_SIZE + 1);

	puts("naive search");
	do_benchmark(search_naive, 0xFF, array_a, ARRAY_SIZE, 10);
	puts("knuth search");
	do_benchmark(search_knuth, 0xFF, array_b, ARRAY_SIZE, 10);

	return 0;
}