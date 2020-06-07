#include "lg/type.h"
#include "lg/types/int64.h"
#include "lg/val.h"

struct lg_type lg_int64_type;

void lg_int64_type_init() {
    lg_type_init(&lg_int64_type, "Int64");
    lg_int64_type.refs = -1;
}
