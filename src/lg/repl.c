#include "lg/block.h"
#include "lg/error.h"
#include "lg/liblg.h"
#include "lg/parse.h"
#include "lg/repl.h"
#include "lg/op.h"
#include "lg/stack.h"
#include "lg/stream.h"
#include "lg/vm.h"

void lg_repl(struct lg_vm *vm, FILE *in, FILE *out) {
  fprintf(out,
	  "liblg v%d.%d\n\n"
	  "Press Return twice to evaluate.\n\n",
	  LG_VERSION1, LG_VERSION2);

  struct lg_stream is;
  lg_stream_init(&is);

  struct lg_stream os;
  lg_stream_init(&os);

  struct lg_stack forms;
  lg_stack_init(&forms, NULL);

  struct lg_block block;
  lg_block_init(&block);

  while (!feof(in)) {
    printf("  ");
    char *l = lg_getline(&is, in);

    if (!l || l[0] == '\n') {
      if (feof(in)) {
	break;
      }

      struct lg_pos p;
      lg_pos_init(&p, "repl", 0, 0);

      if (is.len > 1) {
	if (!lg_parse(&p, is.data, &forms, vm) ||
	    !(lg_compile(&forms, &block, vm) && lg_emit(&block, p, LG_STOP)) ||
	    !lg_eval(lg_block_start(&block), vm)) {
	  lg_stack_do(&vm->errors, e) {
	    fputs(e->as_error->message, out);
	    fputs("\n\n", out);	  
	  }
	  
	  lg_stack_clear(&vm->errors);
	}
      } else {
	lg_stack_clear(vm->stack);
      }

      lg_pos_deinit(&p);
      lg_block_clear(&block);
      lg_stack_clear(&forms);
      lg_stream_reset(&is);

      lg_stack_dump(vm->stack, &os);
      fprintf(out, "%s\n\n", os.data);
      lg_stream_reset(&os);
    }
  }

  lg_block_deinit(&block);
  lg_stack_deinit(&forms);
  lg_stream_deinit(&is);
}
