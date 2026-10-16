#include <stdio.h>
#define MAX_DIM   100
#define MAX_TERMS 10001

typedef struct { int row, col, value; } term;
int row_terms[MAX_DIM];
int starting_pos[MAX_DIM + 1];

void print_triples(const char *title, term x[])
{
    int i;
    printf("%s\n", title);
    printf("  idx  row  col  value\n");
    for (i = 0; i <= x[0].value; i++)
        printf("  %3d  %3d  %3d  %5d\n", i, x[i].row, x[i].col, x[i].value);
}

void fast_transpose(term a[], term b[])
{
    int i, j;
    int num_cols = a[0].col;
    int num_terms = a[0].value;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    if (num_terms > 0) {
        for (i = 0; i < num_cols; i++)
            row_terms[i] = 0;
        for (i = 1; i <= num_terms; i++)
            row_terms[a[i].col]++;
        starting_pos[0] = 1;
        for (i = 1; i < num_cols; i++)
            starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];

        printf("\nrow_terms[]    : ");
        for (i = 0; i < num_cols; i++) printf("%d ", row_terms[i]);
        printf("\nstarting_pos[] : ");
        for (i = 0; i < num_cols; i++) printf("%d ", starting_pos[i]);
        printf("\n");
        for (i = 1; i <= num_terms; i++) {
            j = starting_pos[a[i].col]++;
            b[j].row   = a[i].col;
            b[j].col   = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

int is_row_major(term x[])
{
    int i;
    for (i = 2; i <= x[0].value; i++) {
        if (x[i].row < x[i - 1].row) return 0;
        if (x[i].row == x[i - 1].row && x[i].col <= x[i - 1].col) return 0;
    }
    return 1;
}

int main(void)
{
    static term a[MAX_TERMS], b[MAX_TERMS];
    int rows, cols, i, j, v, n = 0;

    printf("Enter rows and cols (each 1-%d): ", MAX_DIM);
    if (scanf("%d %d", &rows, &cols) != 2 ||
        rows < 1 || rows > MAX_DIM || cols < 1 || cols > MAX_DIM) {
        printf("Invalid dimensions.\n");
        return 1;
    }

    printf("Enter the %d elements row by row:\n", rows * cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (scanf("%d", &v) != 1) {
                printf("Invalid element.\n");
                return 1;
            }
            if (v != 0) {
                n++;
                a[n].row = i;
                a[n].col = j;
                a[n].value = v;
            }
        }
    }
    a[0].row = rows;
    a[0].col = cols;
    a[0].value = n;

    printf("\n");
    print_triples("Original matrix (triples):", a);

    fast_transpose(a, b);

    printf("\n");
    print_triples("Transposed matrix (triples):", b);

    printf("\nTransposed triples already in row-major order? %s\n",
           is_row_major(b) ? "YES" : "NO");
    return 0;
}
