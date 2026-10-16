#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int  emp_id;
    enum { FULL_TIME, CONTRACT } type;
    union {
        float salary;
        struct { float hourly_rate; int hours_worked; } contract_info;
    } pay;
} Employee;

static void flush_line(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

static int read_int(const char *prompt, int min, int max)
{
    int v, r;
    for (;;) {
        printf("%s", prompt);
        r = scanf("%d", &v);
        if (r == EOF) exit(1);
        flush_line();
        if (r == 1 && v >= min && v <= max) return v;
        printf("  Invalid input, try again.\n");
    }
}

static float read_float(const char *prompt)
{
    float v;
    int r;
    for (;;) {
        printf("%s", prompt);
        r = scanf("%f", &v);
        if (r == EOF) exit(1);
        flush_line();
        if (r == 1 && v >= 0) return v;
        printf("  Invalid input, try again.\n");
    }
}

static void read_employee(Employee *e)
{
    printf("Name: ");
    if (fgets(e->name, sizeof e->name, stdin) == NULL) exit(1);
    e->name[strcspn(e->name, "\n")] = '\0';

    e->emp_id = read_int("Employee ID: ", 1, 1000000);
    e->type   = read_int("Type (0 = Full-time, 1 = Contract): ", 0, 1)
                    ? Employee::CONTRACT : Employee::FULL_TIME;

    switch (e->type) {
    case Employee::FULL_TIME:
        e->pay.salary = read_float("Monthly salary: ");
        break;
    case Employee::CONTRACT:
        e->pay.contract_info.hourly_rate  = read_float("Hourly rate: ");
        e->pay.contract_info.hours_worked = read_int("Hours worked: ", 0, 10000);
        break;
    }
}

static double compute_pay(const Employee *e)
{
    if (e->type == Employee::FULL_TIME)
        return e->pay.salary;
    return (double)e->pay.contract_info.hourly_rate *
           e->pay.contract_info.hours_worked;
}

static void print_payslip(const Employee *e)
{
    printf("\n+--------------------------------+\n");
    printf("| ID   : %-23d |\n", e->emp_id);
    printf("| Name : %-23s |\n", e->name);
    if (e->type == Employee::FULL_TIME) {
        printf("| Type : %-23s |\n", "Full-time");
        printf("| Fixed salary : %-15.2f |\n", e->pay.salary);
    } else {
        printf("| Type : %-23s |\n", "Contract");
        printf("| Rate : %-8.2f x %4d hrs      |\n",
               e->pay.contract_info.hourly_rate,
               e->pay.contract_info.hours_worked);
    }
    printf("| TOTAL PAY : %-18.2f |\n", compute_pay(e));
    printf("+--------------------------------+\n");
}

int main(void)
{
    int n = read_int("Enter number of employees: ", 1, 100000);

    Employee *emp = (Employee *)calloc(n, sizeof *emp);
    if (emp == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("\n--- Employee %d of %d ---\n", i + 1, n);
        read_employee(&emp[i]);
    }

    double total_bill = 0.0;
    printf("\n============== PAYSLIPS ==============\n");
    for (int i = 0; i < n; i++) {
        print_payslip(&emp[i]);
        total_bill += compute_pay(&emp[i]);
    }

    printf("\nTotal salary bill of the company: %.2f\n", total_bill);

    free(emp);
    return 0;
}
