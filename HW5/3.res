@.str0 = constant [23 x i8] c"Error division by zero\00"
declare i32 @scanf(i8*, ...)
declare i32 @printf(i8*, ...)
declare void @exit(i32)
@.int_specifier_scan = constant [3 x i8] c"%d\00"
@.int_specifier = constant [4 x i8] c"%d\0A\00"
@.str_specifier = constant [4 x i8] c"%s\0A\00"

define i32 @readi(i32) {
    %ret_val = alloca i32
    %spec_ptr = getelementptr [3 x i8], [3 x i8]* @.int_specifier_scan, i32 0, i32 0
    call i32 (i8*, ...) @scanf(i8* %spec_ptr, i32* %ret_val)
    %val = load i32, i32* %ret_val
    ret i32 %val
}

define void @printi(i32) {
    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0
    call i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)
    ret void
}

define void @print(i8*) {
    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0
    call i32 (i8*, ...) @printf(i8* %spec_ptr, i8* %0)
    ret void
}


define void @main() {
label_0:
%vy = alloca i32 
store i32 5 , i32* %vy
%vz = alloca i32 
store i32 5 , i32* %vz
%t0 = load i32 , i32* %vy
%t1 = load i32 , i32* %vz
%t2 = sub i32 %t0, %t1
%t4 = icmp eq i32 %t2, 0
 br i1 %t4, label %zero_case, label %non_zero_case
zero_case:
 %msg_ptr = getelementptr  [23 x i8], [23 x i8]* @.str0, i32 0, i32 0
 call void @print(i8* %msg_ptr)
 call void @exit(i32 1)
 br label %non_zero_case
 non_zero_case:

%t3 = sdiv i32 2, %t2
%vb = alloca i32 
store i32 %t3 , i32* %vb
ret void 
}
