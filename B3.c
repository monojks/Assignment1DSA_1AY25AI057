#include <stdio.h>

typedef struct {
    int   degree;
    float coef[101];
} polynomial;

polynomial read_poly(const char *label)
{
    polynomial p;
    int i;

    do {
        printf("Degree of %s (0-100): ", label);
        if (scanf("%d", &p.degree) != 1) {
            printf("Invalid input.\n");
            p.degree = -1;
            while (getchar() != '\n')
                ;
        }
    } while (p.degree < 0 || p.degree > 100);

    printf("Enter %d coefficients of %s from x^%d down to x^0\n"
           "(use 0 for missing terms):\n", p.degree + 1, label, p.degree);
    for (i = 0; i <= p.degree; i++) {
        printf("  coef of x^%d: ", p.degree - i);
        scanf("%f", &p.coef[i]);
    }
    return p;
}

polynomial add(polynomial a, polynomial b)
{
    polynomial r;
    int e, max_deg, ca, cb;
    float va, vb;

    max_deg = (a.degree > b.degree) ? a.degree : b.degree;
    r.degree = max_deg;
    for (e = 0; e <= max_deg; e++) {
        va = (e <= a.degree) ? a.coef[a.degree - e] : 0.0f;
        vb = (e <= b.degree) ? b.coef[b.degree - e] : 0.0f;
        r.coef[max_deg - e] = va + vb;
    }
    (void)ca; (void)cb;
    return r;
}

void display(polynomial p)
{
    int i, exp, first = 1;
    float c, mag;

    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];
        if (c == 0.0f) continue;
        exp = p.degree - i;
        if (first) {
            if (c < 0) printf("-");
        } else {
            printf(c < 0 ? " - " : " + ");
        }
        mag = (c < 0) ? -c : c;
        if (exp == 0) {
            printf("%g", mag);
        } else {
            if (mag != 1.0f) printf("%g", mag);
            if (exp == 1) printf("x");
            else          printf("x^%d", exp);
        }
        first = 0;
    }
    if (first) printf("0");
    printf("\n");
}

int main(void)
{
    polynomial A, B, S;

    A = read_poly("A(x)");
    printf("\n");
    B = read_poly("B(x)");

    S = add(A, B);

    printf("\nA(x)       = "); display(A);
    printf("B(x)       = ");   display(B);
    printf("A(x)+B(x)  = ");   display(S);
    return 0;
}
