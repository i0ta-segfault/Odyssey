# Odyssey Grammar (LL(2))

## **Program Structure**
```plaintext
program → stmt*
stmt → assignment
     | declaration
     | if_stmt
     | loop
     | function_def
     | return_stmt
     | block
     | expr_stmt
     | struct_def
     | enum_def
     | ";"
```

## **Expressions**
```plaintext
expr_stmt → expr ";"
expr → primary | expr op expr
primary → IDENT | NUMBER | STRING | BOOL | tuple_expr | array_expr | "(" expr ")"
        | function_call | struct_access | enum_access
op → "+" | "-" | "*" | "/" | "==" | "!=" | "<" | ">" | "&&" | "||" | "%" | "^"
```

## **Tuples & Arrays**
```plaintext
tuple_expr → "[" expr ("," expr)+ "]"
array_expr → "{" expr ("," expr)* "}"
```

## **Function Calls**
```plaintext
function_call → IDENT "(" arg_list? ")"
arg_list → expr ("," expr)*
```

## **Struct & Enum Access**
```plaintext
struct_access → IDENT "." IDENT
enum_access → IDENT "." IDENT
```

## **Assignments & Declarations**
```plaintext
declaration → IDENT ("," IDENT)* ":" type "=" expr ("," expr)* ";"
assignment → IDENT (shorthand_op | "=") expr ("," IDENT (shorthand_op | "=") expr)* ";"
shorthand_op → "+=" | "-=" | "*=" | "/=" | "%="
tuple_destructuring → "[" IDENT ("," IDENT)+ "]" "=" expr ";"
```

## **Conditionals & Loops**
```plaintext
if_stmt → "if" "(" expr ")" block ("else" block)?
loop → "while" "(" expr ")" block
     | "for" "(" assignment ";" expr ";" assignment ")" block
```

## **Blocks & Scope**
```plaintext
block → "{" stmt* "}"
```

## **Functions**
```plaintext
function_def → "fn" IDENT "(" param_list? ")" return_type? block
return_type → ":" type
param_list → IDENT ":" type ("," IDENT ":" type)*
return_stmt → "return" expr ";"
```

## **Structs**
```plaintext
struct_def → "struct" IDENT "{" struct_body "}"
struct_body → (IDENT ":" type ";")*
```

## **Enums**
```plaintext
enum_def → "enum" IDENT "{" enum_body "}"
enum_body → (enum_variant | enum_variable | enum_struct)*
enum_variant → IDENT ( "=" expr )? ","?
enum_variable → IDENT ":" type "=" expr ";"
enum_struct → "struct" IDENT "{" struct_body "}"
```

## **Types & Type Annotations**
```plaintext
type → "int" | "float" | "string" | "bool" | IDENT | pointer_type | array_type | tuple_type
pointer_type → "*" type
array_type → "{" type "}"
tuple_type → "[" type ("," type)+ "]"
```