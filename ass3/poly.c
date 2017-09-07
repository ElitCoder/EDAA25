#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "error.h"
#include "poly.h"

struct poly_t {
    poly_t *next;
    int exponent;
    int value;
    bool sign;
};

void init_poly(poly_t *p)
{
    p->next = NULL;
    p->exponent = 0;
    p->value = 0;
    p->sign = false;
}

poly_t* simplify_poly(poly_t *p)
{
    if (p == NULL)
        return NULL;
    poly_t *h = p;
    poly_t *r = malloc(sizeof(poly_t));
    poly_t *r_start = r;
    poly_t *last = NULL;
    init_poly(r);
    int value;
    int highest_exponent = 0;
    while (p != NULL) {
        if (p->exponent > highest_exponent)
            highest_exponent = p->exponent;
        p = p->next;
    }
    for (int i = highest_exponent; i != -1; --i) {
        p = h;
        value = 0;
        while (p != NULL) {
            if (p->exponent == i)
                value += p->sign ? p->value : -p->value;
            p = p->next;
        }
        if (value == 0)
            continue;
        r->exponent = i;
        r->value = abs(value);
        r->sign = value > 0 ? true : false;
        r->next = malloc(sizeof(poly_t));
        last = r;
        r = r->next;
        init_poly(r);
    }
    free_poly(last->next);
    last->next = NULL;
    return r_start;
}

poly_t* new_poly_from_string(const char *str)
{
    poly_t *h = NULL;
    poly_t *p = malloc(sizeof(poly_t));
    bool is_num = false;
    bool is_exponent = false;
    p->value = 1;
    p->exponent = 0;
    p->sign = true;
    p->next = NULL;
    h = p;
    while (*str != '\0') {
        if (*str == ' ') {
            ++str;
            is_num = false;
            is_exponent = false;
            continue;
        }
        if (isdigit(*str)) {
            if (is_exponent) {
                p->exponent = p->exponent * 10 + *str - '0';
                is_exponent = true;
            } else if (is_num) {
                p->value = p->value * 10 + (*str - '0');
                is_num = true;
            } else {
                p->value = *str - '0';
                is_num = true;
            }
        }
        if (isalpha(*str)) {
            p->exponent = 1;
            is_num = false;
        }
        if (*str == '^') {
            p->exponent = 0;
            is_num = false;
            is_exponent = true;
        }
        if (*str == '-') {
            p->next = malloc(sizeof(poly_t));
            p = p->next;
            init_poly(p);
            is_num = false;
        }
        if (*str == '+') {
            p->next = malloc(sizeof(poly_t));
            p = p->next;
            init_poly(p);
            p->sign = true;
            is_num = false;
        }
        ++str;
    }
    return h;
}

void free_poly(poly_t *p)
{
    poly_t *current = p;
    poly_t *next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

poly_t* mul(poly_t *p, poly_t *q)
{
    poly_t *q_start = q;
    poly_t *r = malloc(sizeof(poly_t));
    poly_t *r_start = r;
    bool sign;
    init_poly(r);
    while (p != NULL) {
        while (q != NULL) {
            r->value = p->value * q->value;
            r->exponent = p->exponent + q->exponent;
            if (!p->sign) {
                if(q->sign)
                    sign = false;
                else
                    sign = true;
            } else {
                if(q->sign)
                    sign = true;
                else
                    sign = false;
            }
            r->sign = sign;
            r->next = malloc(sizeof(poly_t));
            r = r->next;
            init_poly(r);
            q = q->next;
        }
        q = q_start;
        p = p->next;
    }
    //return r_start;
    poly_t *r_finished = simplify_poly(r_start);
    free_poly(r_start);
    return r_finished;
}

void print_poly(poly_t *p)
{
    while (p != NULL) {
        if (p->exponent > 0) {
            if (p->value > 1)
                printf("%d", p->value);
            printf("x");
            if (p->exponent > 1)
                printf("^%d", p->exponent);
        } else {
            printf("%d", p->value);
        }
        if (p->next != NULL)
            printf(" %c ", p->next->sign ? '+' : '-');
        p = p->next;
    } 
    printf("\n");
}