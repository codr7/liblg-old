#include "lg/type.h"
#include "lg/types/bool.h"
#include "lg/val.h"

struct lg_type lg_bool_type;

void lg_bool_type_init() {
    lg_type_init(&lg_bool_type, "Bool");
    lg_bool_type.refs = -1;
}
