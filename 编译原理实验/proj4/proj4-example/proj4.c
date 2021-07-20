#include "proj4.h"

extern char strg_tbl[];
extern tree SyntaxTree;
extern FILE *treelst;


FILE* output_file;
tree cur_method;
tree cur_class;



int main()
{
  SyntaxTree = NULL;
  yyparse(); 

  if ( SyntaxTree == NULL )
    {
      printf( "Syntax Tree not created, exiting...\n" );
      return 1;
    }
  treelst = stdout;
  STInit();
  MkST(SyntaxTree);

  STPrint();
  
  printtree(SyntaxTree, 0);


  start_generate_code(SyntaxTree);
}

void create_readln() {
	


	fprintf(output_file, "system_readln:\n");
	
	
	fprintf(output_file, "move $t2 $a0\n");

	
	fprintf(output_file, "li $v0 5     # readln\n");
	fprintf(output_file, "syscall\n");

	
	fprintf(output_file, "sw $v0 0($t2)\n");

	fprintf(output_file, "jr $ra\n");
}

void start_generate_code(tree syntax_tree) {
	
	
	
	output_file = fopen("code.s", "wb");

	
	fprintf(output_file, "j main\n");

	create_println();
	create_readln();

	fprintf(output_file, ".data\n");
	fprintf(output_file, ".align 4\n");
	fprintf(output_file, "base:\n");
	fprintf(output_file, ".text\n");

	generate_code(syntax_tree);

	fclose(output_file);

}



void create_println() {
	
	fprintf(output_file, ".data\n");
	fprintf(output_file, ".align 4\n");
	fprintf(output_file, "system_println_newline: .asciiz \"\\n\"\n");
	

	fprintf(output_file, ".text\n");
	fprintf(output_file, "system_println:\n");

	
	fprintf(output_file, "li $t1 1\n");
	fprintf(output_file, "blt $s0 $t1 system_println_string_print\n");

	
	fprintf(output_file, "lw $a0 0($a0)\n");

	
	fprintf(output_file, "system_println_int_by_val_print:\n");
	fprintf(output_file, "li $v0 1     # println - int\n");
	fprintf(output_file, "syscall\n");
	fprintf(output_file, "j system_println_newline_print\n");

	

	fprintf(output_file, "system_println_string_print:\n");
	fprintf(output_file, "li $v0 4     # println - string\n");
	
	fprintf(output_file, "syscall\n");
	
	fprintf(output_file, "jr $ra\n");
	
	fprintf(output_file, "system_println_newline_print:\n");

	fprintf(output_file, "li $v0 4\n");
	fprintf(output_file, "la $a0 system_println_newline\n");
	fprintf(output_file, "syscall\n");
	fprintf(output_file, "jr $ra\n");

}


int get_size(tree init_tree) {
	
	if  (NodeKind(init_tree) != EXPRNode) {
		
		return 4;
	}
	else if  (init_tree == NullExp()) {
		
		return 4;
	}
	else if (NodeOp(init_tree) == ArrayTypeOp) {
		
		int returnVal ;
                returnVal=0;
		while (init_tree != NullExp()) {
			returnVal += get_size(RightChild(init_tree));
			init_tree = LeftChild(init_tree);
		}
		return returnVal;
	}
	else {
		
		return 1;
	}
}


void array_init(char* Lable, tree init_tree, int is_beyond_1d) {
	
	if ((NodeOp(init_tree) == ArrayTypeOp) && !is_beyond_1d) {
		
		fprintf(output_file, " %s  .word", Lable);
	}




	
	else if (init_tree == NullExp()) 
{
		
		return;	
}
	array_init(Lable, LeftChild(init_tree), is_beyond_1d);
	if (!(NodeOp(init_tree) == ArrayTypeOp) )
        {

               if ((NodeKind(RightChild(init_tree)) == EXPRNode) && (NodeOp(RightChild(init_tree)) == ArrayTypeOp)) {
			
			array_init(Lable, RightChild(init_tree), 1);
		}
		else if ((NodeKind(init_tree) == EXPRNode) && (NodeOp(init_tree) == BoundOp)) {
			
			int i = IntVal(RightChild(init_tree));
			for ( ; i > 0; i--) {
				fprintf(output_file, " 0");
			}
		}
		else {
			fprintf(output_file, " %d", IntVal(RightChild(init_tree)));
		}
		
			}
	else 
        {
		if (!is_beyond_1d) 
                {
			fprintf(output_file, "\n");
		}

		
	}
}


void emit_if_start(tree syntax_tree) {
	static int EndIfFreq = 0;

	emit_if (syntax_tree, EndIfFreq);

	
	fprintf(output_file, "if_endif_%d:\n", EndIfFreq);
	EndIfFreq++;
}


void emit_loop(tree syntax_tree) {
	

	static int LoopFreq = 0;

	
	fprintf(output_file, "while_start_%d:\n", LoopFreq);
	
	
	evaluate_expression(LeftChild(syntax_tree));

	fprintf(output_file, "beq $0 $t0 while_end_%d\n", LoopFreq);

	generate_code(RightChild(syntax_tree));
	fprintf(output_file, "j while_start_%d\n", LoopFreq);

	
	fprintf(output_file, "while_end_%d:\n", LoopFreq);
	LoopFreq++;


}



void emit_if(tree syntax_tree, int EndIfFreq) {
	

	static int IfFreq = 0;

	
	tree TreeTemp = LeftChild(syntax_tree);
	if (TreeTemp == NullExp())
{
}
else {
		emit_if(TreeTemp, EndIfFreq);
	}

	TreeTemp = RightChild(syntax_tree);
	if( !(NodeOp(TreeTemp) == CommaOp)) {
		
		
              fprintf(output_file, "     # else\n");
		generate_code(TreeTemp);
		fprintf(output_file, "j if_endif_%d\n", EndIfFreq);
	}
	else {

fprintf(output_file, "     # if stmt\n");
		evaluate_expression(LeftChild(TreeTemp));

		
		fprintf(output_file, "beq $0 $t0 if_false_%d\n", IfFreq);

	
		generate_code(RightChild(TreeTemp));
		fprintf(output_file, "j if_endif_%d\n", EndIfFreq);

		
		fprintf(output_file, "if_false_%d:\n", IfFreq);
		IfFreq++;
		
		
	}

}


void quote_it_right(char * properly_quoted_str, char * orig_str) {


	strcpy(properly_quoted_str, orig_str);
	properly_quoted_str[0] = '"';
	properly_quoted_str[strlen(properly_quoted_str) - 1] = '"';
}

void emit_data(tree TreeDecl, int* offset_ptr) {

	if (TreeDecl == NullExp()) {
		
		return;
	}

	SetAttr(IntVal(LeftChild(TreeDecl)), OFFSET_ATTR, *offset_ptr);

	tree FuncNAme = LeftChild(TreeDecl);
	int SizeObj = get_size(RightChild(RightChild(TreeDecl)));

	
	
	
	char* ParNAme = strg_tbl + GetAttr(IntVal(RightChild(cur_class)), NAME_ATTR);
	char* var_name;
	if (LeftChild(FuncNAme) == NullExp())
        {
var_name = strg_tbl + GetAttr(IntVal((FuncNAme)), NAME_ATTR);
	}
	else 
       {
		var_name = strg_tbl + GetAttr(IntVal(LeftChild(FuncNAme)), NAME_ATTR);
		
	}
	char* Lable = malloc(strlen(ParNAme) + strlen(var_name) + 7);
	strcpy(Lable, "var_");
	strcat(Lable, ParNAme);
	strcat(Lable, "_");
	strcat(Lable, var_name);
	strcat(Lable, ":");

	*offset_ptr += SizeObj;
	tree TreeType = RightChild(TreeDecl);
	
	if (NodeKind(RightChild(TreeType)) == EXPRNode) {
		
		if (NodeOp(RightChild(TreeType)) == ArrayTypeOp) {
			
			array_init(Lable, RightChild(TreeType), 0);
		}
		else {
			
			fprintf(output_file, " %s  .word %d\n", Lable, -IntVal(LeftChild(RightChild(TreeType))));
		}
	}
	else if (RightChild(TreeType) != NullExp()) 

		fprintf(output_file, " %s  .word %d\n", Lable, IntVal(RightChild(TreeType)));
	
	else {

		fprintf(output_file, " %s  .word 0\n", Lable);
	}
	free(Lable);
}




void handle_decls(tree syntax_tree) {
	 
	fprintf(output_file, ".data\n");
	fprintf(output_file, ".align 4\n");
	 
	static int offset = 0;
	if (LeftChild(syntax_tree) != NullExp()) {
		 
		handle_decls(LeftChild(syntax_tree));
	}
	 
	tree TreeDecl = RightChild(syntax_tree);

	while (TreeDecl != NullExp()) {
		emit_data(RightChild(TreeDecl), &offset);
		TreeDecl = LeftChild(TreeDecl);
	}

}

void emit_call(tree func_tree, tree cur_class) {

	static int str_num = 0;

	char * ParNAme;
	char * function_name;


	tree FuncNAme = LeftChild(func_tree);
	if (RightChild(FuncNAme) == NullExp()) {

		ParNAme = strg_tbl + GetAttr(IntVal(RightChild(cur_class)), NAME_ATTR);
		function_name = strg_tbl + GetAttr(IntVal(LeftChild(FuncNAme)), NAME_ATTR);
	}
	else {
		
		tree class_tree = get_class(LeftChild(FuncNAme));
		
		while (RightChild(RightChild(FuncNAme)) != NullExp()) {

			FuncNAme = RightChild(FuncNAme);
			class_tree = get_class(LeftChild(LeftChild(FuncNAme)));
		}
		

		ParNAme = strg_tbl + GetAttr(IntVal(class_tree), NAME_ATTR);
		function_name = strg_tbl + GetAttr(IntVal(LeftChild(LeftChild(RightChild(FuncNAme)))), NAME_ATTR);
	}

	fprintf(output_file, "move $s0 $0    # clear s0 before passing params\n");
	fprintf(output_file, "move $t8 $0\n");


	tree param_tree = RightChild(func_tree);
	tree cur_param;
	int str_addr;
	int i;
	for (i = 0; (i <= 3) && (param_tree != NullExp()); i++) {
		cur_param = LeftChild(param_tree);
				if (NodeKind(cur_param) == STRINGNode) {
			
			char* properly_quoted_str = malloc(strlen(strg_tbl + IntVal(cur_param)));
			quote_it_right(properly_quoted_str, strg_tbl + IntVal(cur_param));
			fprintf(output_file, ".data\n");
	fprintf(output_file, ".align 4\n");
			fprintf(output_file, "string_%d: .asciiz %s\n", str_num, properly_quoted_str);
			free(properly_quoted_str);
			
			fprintf(output_file, ".text\n");
 			fprintf(output_file, "la $a%d string_%d      # string param\n", i, str_num++);
		}
		else if (NodeKind(cur_param) == EXPRNode) {

			if (NodeOp(cur_param) == VarOp) {

				evaluate_addr(cur_param);
				fprintf(output_file, "move $a%d $t0\n", i);
				fprintf(output_file, "addi $s0 $0 2\n");
			}
			else {

				evaluate_alu(cur_param);

				fprintf(output_file, "sw $t0 ($sp)   # move alu_eval into stack\n");
				fprintf(output_file, "move $a%d $sp\n", i);
				fprintf(output_file, "addi $sp $sp -4\n");
				fprintf(output_file, "addi $t8 $t8 4\n");

				fprintf(output_file, "addi $s0 $0 2\n");


			}
		}
		else {

			fprintf(output_file, "addi $t0 $0 %d\n", IntVal(cur_param));
			fprintf(output_file, "sw $t0 ($sp)   # move int val into stack\n");
			fprintf(output_file, "move $a%d $sp\n", i);
			fprintf(output_file, "addi $sp $sp -4\n");
			fprintf(output_file, "addi $t8 $t8 4\n");

			fprintf(output_file, "addi $s0 $0 2\n");

		}

		param_tree = RightChild(param_tree);
	}



	for (i = 0; i <= 9; i++) {
		fprintf(output_file, "sw $t%d 0($sp)\n", i);
		fprintf(output_file, "addi $sp $sp -4\n");
	}

	
	fprintf(output_file, "sw $ra 0($sp)\n", i);
	fprintf(output_file, "addi $sp $sp -4\n");
	fprintf(output_file, "sw $fp 0($sp)\n", i);
	fprintf(output_file, "addi $sp $sp -4\n");

	
	fprintf(output_file, "move $fp $sp\n");
	fprintf(output_file, "jal %s_%s\n", ParNAme, function_name);
	fprintf(output_file, "move $sp $fp\n");


	fprintf(output_file, "addi $sp $sp 4\n");
	fprintf(output_file, "lw $fp 0($sp)\n", i);
	fprintf(output_file, "addi $sp $sp 4\n");
	fprintf(output_file, "lw $ra 0($sp)\n", i);
	
 
	for (i = 9; i >= 0; i--) {
		fprintf(output_file, "addi $sp $sp 4\n");
		fprintf(output_file, "lw $t%d 0($sp)\n", i);
	}

	 
	fprintf(output_file, "add $sp $sp $t8\n");
}




int handle_function_params(tree syntax_tree, int cur_offset, int cur_param_num) {
	 
	if (syntax_tree == NullExp()) 
		 
		return cur_offset;
	

	if (RightChild(syntax_tree) != NullExp()) 
	 
		cur_offset = handle_function_params(RightChild(syntax_tree), cur_offset, cur_param_num + 1);
	


	if (NodeOp(syntax_tree) == RArgTypeOp) {
		 
		SetAttr(IntVal(LeftChild(LeftChild((syntax_tree)))), OFFSET_ATTR, cur_offset);

		 

		fprintf(output_file, "sw $a%d 0($sp)    # pass by reference\n", cur_param_num);
		fprintf(output_file, "addi $sp $sp -4\n");
 
		return cur_offset - 4;

	}
	else {
		 
		SetAttr(IntVal(LeftChild(LeftChild((syntax_tree)))), OFFSET_ATTR, cur_offset);

		 
		fprintf(output_file, "addi $t5 $sp -4\n");
		fprintf(output_file, "sw $t5 0($sp)\n");
		fprintf(output_file, "addi $sp $sp -4\n");

	 
		fprintf(output_file, "lw $t4 0($a%d)    # load -- by value param\n", cur_param_num);
		fprintf(output_file, "sw $t4 0($sp)    # init parameter\n", cur_param_num);
		fprintf(output_file, "addi $sp $sp -4\n");

		 
		return cur_offset - 8;

	}

}

int stumpy_array_initializer(tree syntax_tree) {
	 
	evaluate_expression(RightChild(syntax_tree));
	
 

	fprintf(output_file, "li $t3 -4     # init array -- size\n");
	fprintf(output_file, "mul $t2 $t0 $t3\n");
	fprintf(output_file, "add $sp $sp $t2\n");
	return -4 - 4*IntVal(RightChild(syntax_tree));
}

int array_initializer(tree syntax_tree, int cur_val) {
	int returnVal = cur_val;
	if (LeftChild(syntax_tree) != NullExp()) 
		 
		returnVal = array_initializer(LeftChild(syntax_tree), cur_val);
	

	evaluate_expression(RightChild(syntax_tree));

	fprintf(output_file, "sw $t0 0($sp)    # init array -- given values\n");
	fprintf(output_file, "addi $sp $sp -4\n");

	return returnVal - 4;
}



void create_function(tree syntax_tree, tree cur_class) {
	 
	if (!strcmp(strg_tbl + GetAttr(IntVal(LeftChild(LeftChild(syntax_tree))), NAME_ATTR), "main")) {
		fprintf(output_file, "la $gp base\n");
		fprintf(output_file, "main:\n");
	}
	else {
		fprintf(output_file, "%s_%s:\n", strg_tbl + GetAttr(IntVal(RightChild(cur_class)), NAME_ATTR), strg_tbl + GetAttr(IntVal(LeftChild(LeftChild(syntax_tree))), NAME_ATTR));
	}
	
 
	fprintf(output_file, "move $t9 $sp\n");
	handle_function_params(LeftChild(RightChild(LeftChild(syntax_tree))), 0, 0);
	int cur_offset = handle_function_decls(LeftChild(RightChild(syntax_tree)), 0);
	
	 
	fprintf(output_file, "sw $ra 0($sp)\n");
	fprintf(output_file, "addi $sp $sp -4\n");

	 
	generate_code(RightChild(syntax_tree));
 

	 
	if (!strcmp(strg_tbl + GetAttr(IntVal(LeftChild(LeftChild(syntax_tree))), NAME_ATTR), "main")) {
		 
		fprintf(output_file, "li $v0 10   # exit\n");
		fprintf(output_file, "syscall\n");

	}
	else {
		 
		fprintf(output_file, "addi $sp $sp 4\n");
		fprintf(output_file, "lw $ra 0($sp)\n");
		fprintf(output_file, "jr $ra\n");
	}


}

int handle_function_decls(tree syntax_tree, int cur_offset) {
	 

	int UpdateOffset ;
        UpdateOffset = 0;
	
	if (LeftChild(syntax_tree) != NullExp()) 
		 
		cur_offset = handle_function_decls(LeftChild(syntax_tree), cur_offset);
	

	 
	tree TreeDecl = RightChild(syntax_tree);
	while (TreeDecl != NullExp()) {
		 
		SetAttr(IntVal(LeftChild(RightChild(TreeDecl))), OFFSET_ATTR, cur_offset);
 
		fprintf(output_file, "addi $t5 $sp -4\n");
		fprintf(output_file, "sw $t5 0($sp)\n");
		fprintf(output_file, "addi $sp $sp -4\n");


		tree init_tree = RightChild(RightChild(RightChild(TreeDecl)));
		if (!(init_tree == NullExp()))
                {
		 if (NodeKind(init_tree) == EXPRNode && (NodeOp(init_tree) == ArrayTypeOp)) {
				 
				tree init_value_tree = LeftChild(init_tree);
				if (NodeOp(init_value_tree) == CommaOp) {
					 
					UpdateOffset = array_initializer(init_value_tree, -4);
				}
				else {
					 
					UpdateOffset = stumpy_array_initializer(init_value_tree);
				}
			}
			else {
				evaluate_expression(init_tree);
				fprintf(output_file, "sw $t0 0($sp)    # init local var\n");
				fprintf(output_file, "addi $sp $sp -4\n");
				UpdateOffset = -8;
			}
			
		}
		else {


                        fprintf(output_file, "li $t2 0    # uninitialized local var decl\n");
			fprintf(output_file, "sw $t2 0($sp)\n");
			fprintf(output_file, "addi $sp $sp -4\n");
			UpdateOffset = -8;




			 
			
		}

		TreeDecl = LeftChild(TreeDecl);
		 
		cur_offset += UpdateOffset;
	}
	return cur_offset;

}




void evaluate_addr(tree syntax_tree) {
	 
	int base_addr;
	if (GetAttr(IntVal(LeftChild(syntax_tree)), NEST_ATTR) > 0) {
		base_addr = GetAttr(IntVal(LeftChild(syntax_tree)), OFFSET_ATTR);
	}
	int array_or_class_offset = 0;
	int is_array = 0;
	int is_class_access = 0;
	int additional_addr;
	 
	fprintf(output_file, "move $t2 $0    # begin eval addr\n");
	fprintf(output_file, "move $t3 $0\n");
	
	tree TreeTemp = RightChild(syntax_tree);
	tree nearest_class = get_class(LeftChild(syntax_tree));
	while (TreeTemp != NullExp()) {
		 
		if (NodeOp(LeftChild(TreeTemp)) == IndexOp) {
			 
			tree index_tree = LeftChild(TreeTemp);
			is_array = 1;
			 
			fprintf(output_file, "sw $t2 0($sp)\n");
			fprintf(output_file, "addi $sp $sp -4\n");
			fprintf(output_file, "sw $t3 0($sp)\n");
			fprintf(output_file, "addi $sp $sp -4\n");

			evaluate_alu(LeftChild(index_tree));
			
		 
			fprintf(output_file, "addi $sp $sp 4\n");
			fprintf(output_file, "lw $t3 0($sp)\n");
			fprintf(output_file, "addi $sp $sp 4\n");
			fprintf(output_file, "lw $t2 0($sp)\n");
			
			 
			fprintf(output_file, "addi $t1 $0 -4\n");
			fprintf(output_file, "mul $t0 $t0 $t1\n");
			fprintf(output_file, "add $t3 $t3 $t0\n");
			
			 
			if (is_class_access) {
				fprintf(output_file, "sub $t2 $t2 $t3    # array index\n");
			}
			else {
				fprintf(output_file, "add $t2 $t2 $t3    # array index\n");
			}
		}
		else if (NodeOp(LeftChild(TreeTemp)) == FieldOp) {
			 
			class_var_access(LeftChild(TreeTemp), nearest_class);
			nearest_class = get_class(LeftChild(LeftChild(TreeTemp)));
			is_class_access = 1;
		}
		else {
		 
			printf("error calculating address:\n");
			printtree(LeftChild(TreeTemp), 0);
		}
		TreeTemp = RightChild(TreeTemp);
	}

	 
	fprintf(output_file, "move $t0 $t2   # prepare to return\n");


	 
	if (is_class_access) {
		 
	}
	else if (GetAttr(IntVal(LeftChild(syntax_tree)), NEST_ATTR) <= 1) {
		 
		class_var_access(syntax_tree, nearest_class);

	}
	else {
		 
		fprintf(output_file, "add $t0 $t0 $t9    # local var access\n");
		if (!is_array)
			fprintf(output_file, "lw $t0 %d($t0)    # get the addr\n", GetAttr(IntVal(LeftChild(syntax_tree)), OFFSET_ATTR));
		 
	}
	 
	
}
tree get_class(tree syntax_tree) {
	 

	int nest_level = GetAttr(IntVal(syntax_tree), NEST_ATTR);
	
	if (nest_level != 0) {

                tree TreeType = GetAttr(IntVal(syntax_tree), TYPE_ATTR);
		if (!(NodeKind(LeftChild(TreeType)) == INTEGERTNode)) 
{
			
return LeftChild(TreeType);

		}
		else 
{
return RightChild(cur_class);
					}
	}
	else {

		 		 return syntax_tree;

		
	}

}

void evaluate_alu(tree syntax_tree) {
	 
	if (syntax_tree == NullExp()) {
		 
		fprintf(output_file, "move $t0 $0\n");
		return;
	}
	else if (NodeKind(syntax_tree) == EXPRNode) {
		if (NodeOp(syntax_tree) == VarOp) {
			 
			evaluate_addr(syntax_tree);
			fprintf(output_file, "move $t3 $t0\n");
			fprintf(output_file, "lw $t0 0($t3)\n");
		}
		else if (NodeOp(syntax_tree) == UnaryNegOp) {
			 
			evaluate_alu(LeftChild(syntax_tree));
			fprintf(output_file, "sub $t0 $0 $t0     # negation of an int\n");
		}
		else {
			 
			if (NodeOp(syntax_tree) != RoutineCallOp) {
			 
				evaluate_alu(LeftChild(syntax_tree));
				 
				fprintf(output_file, "sw $t0 0($sp)\n");
				fprintf(output_file, "addi $sp $sp -4\n");
				 
				evaluate_alu(RightChild(syntax_tree));
				 
				fprintf(output_file, "sw $t0 0($sp)\n");
				fprintf(output_file, "addi $sp $sp -4\n");

 				fprintf(output_file, "addi $sp $sp 4\n");
				fprintf(output_file, "lw $t3 0($sp)\n");
				fprintf(output_file, "addi $sp $sp 4\n");
				fprintf(output_file, "lw $t2 0($sp)\n");
			}
			switch (NodeOp(syntax_tree)) {
				case AddOp:
					fprintf(output_file, "add $t0 $t2 $t3\n");
					break;

				case SubOp:
					fprintf(output_file, "sub $t0 $t2 $t3\n");
					break;

				case MultOp:
					fprintf(output_file, "mul $t0 $t2 $t3\n");
					break;

				case DivOp:
					fprintf(output_file, "div $t0 $t2 $t3\n");
					break;

				case AndOp:
					fprintf(output_file, "and $t0 $t2 $t3\n");
					break;

				case OrOp:
					fprintf(output_file, "or $t0 $t2 $t3\n");
					break;

				case UnaryNegOp:
					fprintf(output_file, "sub $t0 $0 $t2\n");
					break;

				case NotOp:
					fprintf(output_file, "nor $t0 $t2 $t2\n");
					break;


				case LTOp:
					fprintf(output_file, "slt $t0 $t2 $t3\n");
					break;

				case GTOp:
					fprintf(output_file, "slt $t0 $t2 $t3     # calculate >\n");
					fprintf(output_file, "li $t1 1\n");
					fprintf(output_file, "slt $t0 $t0 $t1\n");
					 
					fprintf(output_file, "slt $t4 $t2 $t3\n");
					fprintf(output_file, "slt $t5 $t3 $t2\n");
					fprintf(output_file, "or $t4 $t4 $t5\n");
					fprintf(output_file, "slt $t4 $t4 $t1\n");
					 
					fprintf(output_file, "xor $t5 $t0 $t4\n");
					fprintf(output_file, "and $t0 $t0 $t5\n");

					break;

				case EQOp:
					fprintf(output_file, "slt $t4 $t2 $t3    # calculate ==\n");
					fprintf(output_file, "slt $t5 $t3 $t2\n");
					fprintf(output_file, "or $t4 $t4 $t5\n");
					fprintf(output_file, "li $t1 1\n");
					fprintf(output_file, "slt $t0 $t4 $t1\n");
					break;

				case NEOp:
					fprintf(output_file, "sub $t0 $t2 $t3\n");
					break;

				case LEOp:
					fprintf(output_file, "slt $t0 $t2 $t3     # calculate <=\n");
					 
					fprintf(output_file, "slt $t4 $t2 $t3\n");
					fprintf(output_file, "slt $t5 $t3 $t2\n");
					fprintf(output_file, "or $t4 $t4 $t5\n");
					fprintf(output_file, "li $t1 1\n");
					fprintf(output_file, "slt $t4 $t4 $t1\n");
					fprintf(output_file, "or $t0 $t0 $t4\n");
					break;

				case GEOp:
					fprintf(output_file, "slt $t0 $t2 $t3     # calculate >=\n");
					fprintf(output_file, "li $t1 1\n");
					fprintf(output_file, "slt $t0 $t0 $t1\n");
					break;

				case RoutineCallOp:
					 
					generate_code(syntax_tree);
				 
					fprintf(output_file, "move $t0 $v0\n");
					break;



				default:
					printf("ERROR: Unknown ALU op: %d\n", NodeOp(syntax_tree));
			}
		}
	}
	else {
		 
		fprintf(output_file, "addi $t0 $0 %d\n", IntVal(syntax_tree));
	}
}


tree class_var_access(tree syntax_tree, tree base_class) {
	 

	char* ParNAme ;
        tree child_tree;
        ParNAme = strg_tbl + GetAttr(IntVal(base_class), NAME_ATTR);
	char* var_name;
	
	if (LeftChild(syntax_tree) != NullExp()) {
		child_tree = LeftChild(syntax_tree);
		var_name = strg_tbl + GetAttr(IntVal(child_tree), NAME_ATTR);
	}
	else {
		child_tree = syntax_tree;
		var_name = strg_tbl + GetAttr(IntVal(child_tree), NAME_ATTR);
	}
	 
	child_tree = get_class(child_tree);

	char* Lable = malloc(strlen(ParNAme) + strlen(var_name) + 6);
	strcpy(Lable, "var_");
	strcat(Lable, ParNAme);
	strcat(Lable, "_");
	strcat(Lable, var_name);

	fprintf(output_file, "la $t0 %s    # undo everything!\n", Lable);
	fprintf(output_file, "sub $t0 $t0 $t3\n");
	fprintf(output_file, "move $t2 $t0   # copy address\n");
		
	free(Lable);

	tree returnVal = base_class;

	return returnVal;

}

void generate_code(tree syntax_tree) {
	 
	if (syntax_tree == NullExp()) 
		 
		return;
	else
{
	switch (NodeOp(syntax_tree)) {
		case ClassDefOp:
			 
			cur_class = syntax_tree;
			tree TreeDecl = LeftChild(syntax_tree);
			 
			while (TreeDecl != NullExp() && (NodeOp(RightChild(TreeDecl)) == MethodOp)) {
				TreeDecl = LeftChild(TreeDecl);
			}
			handle_decls(TreeDecl);
			fprintf(output_file, ".text\n");
			generate_code(LeftChild(syntax_tree));
			generate_code(RightChild(syntax_tree));
			break;
case ReturnOp:
			 
			evaluate_alu(LeftChild(syntax_tree));
			fprintf(output_file, "move $v0 $t0    # set return value\n");
			break;
		case RoutineCallOp:
			 
			emit_call(syntax_tree, cur_class);
			break;
		case MethodOp:
			 
			create_function(syntax_tree, cur_class);
			break;

		

		case AssignOp:
			 
			evaluate_alu(RightChild(syntax_tree));
			fprintf(output_file, "sw $t0 ($sp)   # stash RHS\n");
			fprintf(output_file, "addi $sp $sp -4\n");
			 
			evaluate_addr(RightChild(LeftChild(syntax_tree)));
			fprintf(output_file, "addi $sp $sp 4\n");
			fprintf(output_file, "lw $t2 ($sp)   # load RHS\n");
			fprintf(output_file, "sw $t2 0($t0)  # assign RHS to LHS\n");
			break;

		 
		
			evaluate_alu(syntax_tree);
			 
			break;
		 

		case IfElseOp:
			 
			emit_if_start(syntax_tree);
			break;

		case LoopOp:
		 
			emit_loop(syntax_tree);
			break;

		default:
			 
			if (LeftChild(syntax_tree) != NullExp())
				generate_code(LeftChild(syntax_tree));
			if (RightChild(syntax_tree) != NullExp())
				generate_code(RightChild(syntax_tree));
	}
}
}
void evaluate_expression(tree syntax_tree) {
	 
	evaluate_alu(syntax_tree);
}



