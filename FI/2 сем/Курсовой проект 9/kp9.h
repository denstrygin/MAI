typedef struct _Key{
	long long int a;
	double b;
} Key;

typedef struct _Row{
	Key key;
	char val[81];
} Row;

void printTable(const Row *rows, const int size);
int binSearch(const Row *rows, const int size, const Key key);
void shaker_sort(Row *rows, const int size);
void scramble(Row *rows, const int size);
void reverse(Row *rows, const int size);
void getRow(FILE *stream, char *str, const int size);
void swapRows(Row *rows, const int a, const int b);
int comparator(const Key k1, const Key k2);
int randomAB(const int a, const int b);
int isSorted(const Row *rows, const int size);