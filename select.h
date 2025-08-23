#ifndef SELECT
#define SELECT

#include "mem.h"

void mem_display(const mem* member);
int self_service_search(const char* num, mem* result);
void mem_key(void);
void select_by_num(void);
void select_by_name(void);
void select_by_phone(void);

#endif
