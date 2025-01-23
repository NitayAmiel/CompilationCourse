@.str0 = constant [5 x i8] c"true\00"@.str1 = constant [5 x i8] c"true\00"@.str2 = constant [12 x i8] c"val is true\00"@.str3 = constant [13 x i8] c"val is false\00"
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
%t0 = add i1 0, true
%t1 = call void @printByValue(i1 %t0)
%t2 = add i1 0, false
%t3 = call void @printByValue(i1 %t2)
%t4 = add i1 0, true
br i1 %t4 ,label %label_1 ,label %label_2
label_1:
%t5 = getelementptr [5 x i8], [5 x i8]* @.str0, i32 0, i32 0
%t6 = call void @print(i8* %t5)
br label %label_2
label_2:
%t7 = add i1 0, false
br i1 %t7 ,label %label_3 ,label %label_5
label_5:
%t8 = add i1 0, false
%t9 = add i1 0, true
%t10 = and i1 %t8, %t9
%t11 = or i1 %t7, %t10
br i1 %t11 ,label %label_3 ,label %label_4
label_3:
%t12 = getelementptr [5 x i8], [5 x i8]* @.str1, i32 0, i32 0
%t13 = call void @print(i8* %t12)
br label %label_4
label_4:
ret void 
}
define void @printByValue(i1 ) {
label_6:
%t14 = load i1 , i1* %val
br i1 %t14 ,label %label_7 ,label %label_8
label_7:
%t15 = getelementptr [12 x i8], [12 x i8]* @.str2, i32 0, i32 0
%t16 = call void @print(i8* %t15)
br label %label_9
label_8:
%t17 = getelementptr [13 x i8], [13 x i8]* @.str3, i32 0, i32 0
%t18 = call void @print(i8* %t17)
br label %label_9
label_9:
ret void 
}
