/*
	Don't ever use jumptables along this bullshit :)
	Switch statements are simply better.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

_Bool check_diff(size_t len, size_t *n) {
	for(size_t i = 0; i != len; ++i)
		for(size_t a = 0; a != len; ++a) 
			if (i != a && n[i] == n[a])
				return 1;

	return 0;
}

void try(
	size_t *n,
	size_t len,
	size_t (*op)(size_t, size_t),
	size_t i,
	size_t add,
	size_t end
) {
	size_t a[len];

	do
		for(size_t b = 0; b != len; ++b)
			a[b] = op(n[b], i);
	while ((i += add) != end && check_diff(len, a));

	printf("%zu	", i - add);

	for(size_t i = 0; i != len; ++i)
		printf("[%zu] = ,", a[i]);
	
	putchar('\n');
}

size_t and(size_t x, size_t y) {
	return x & y;
}

size_t sub(size_t x, size_t y) {
	return x - y;
}

size_t shr(size_t x, size_t y) {
	if (y >= sizeof(size_t) * 8)
		return 0;

	//printf("%d >> %d = %d\n", x, y, x>>y);
	return x >> y;
}

/*
	Tries
		&
		-
		>>
*/
void translate(size_t len, size_t *n) {
	if (len)
		try(n, len, and, 0, 1, 999999),
		//try(n, len, sub, 999999, -1, 0),
		try(n, len, shr, 999999, -1, 0);
}

void into_n(char **argv, size_t *n) {
	while (*++argv) *n++ = atoi(*argv);
}

int main(int argc, char **argv) {
	size_t n[argc];
	into_n(argv, n);
	translate(--argc, n);
}
