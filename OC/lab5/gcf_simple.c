#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int GCF (int A, int B) {
    for (int i = MIN (A, B); i > 1; --i) {
        if (A % i == 0 && B % i == 0) {
            return i;
        }
    }
    return 1;
}