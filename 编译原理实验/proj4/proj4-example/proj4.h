
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proj2.h"
#include "proj3.h"

void start_generate_code(tree syntax_tree);
void create_println();
void create_readln();
void array_init(char* label, tree init_tree, int is_beyond_1d);
int get_size(tree init_tree);
void emit_if_start(tree syntax_tree);
void emit_if(tree syntax_tree, int cur_endif_num);
void emit_data(tree decl_tree, int* offset_ptr);
void quote_it_right(char * properly_quoted_str, char * orig_str);
void emit_call(tree func_tree, tree cur_class);
void handle_decls(tree syntax_tree);
void create_function(tree syntax_tree, tree cur_class);
tree class_var_access(tree syntax_tree, tree base_class);
tree get_class(tree syntax_tree);
void evaluate_addr(tree syntax_tree);
void evaluate_alu(tree syntax_tree);
void evaluate_expression(tree syntax_tree);
void generate_code(tree syntax_tree);
int handle_function_decls(tree syntax_tree, int cur_offset);
int handle_function_params(tree syntax_tree, int cur_offset, int cur_param_num);
