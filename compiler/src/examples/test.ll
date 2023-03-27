; ModuleID = 'file'
source_filename = "file"

define void @main() {
entry:
  %i = alloca i32, align 4
  %n = alloca i32, align 4
  %is_prime = alloca i1, align 1
  %0 = alloca i1, align 1
  store i1 true, i1* %0, align 1
  %1 = load i1, i1* %0, align 1
  store i1 %1, i1* %is_prime, align 1
  %2 = alloca i32, align 4
  store i32 32749, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  store i32 %3, i32* %n, align 4
  %4 = alloca i32, align 4
  store i32 2, i32* %4, align 4
  %5 = load i32, i32* %4, align 4
  store i32 %5, i32* %i, align 4
  br label %6

6:                                                ; preds = %39, %entry
  %7 = load i32, i32* %i, align 4
  %8 = load i32, i32* %i, align 4
  %9 = mul i32 %7, %8
  %10 = alloca i32, align 4
  store i32 %9, i32* %10, align 4
  %11 = load i32, i32* %10, align 4
  %12 = load i32, i32* %n, align 4
  %13 = icmp sle i32 %11, %12
  %14 = alloca i1, align 1
  store i1 %13, i1* %14, align 1
  %15 = load i1, i1* %14, align 1
  %16 = load i1, i1* %is_prime, align 1
  %17 = and i1 %15, %16
  %18 = alloca i1, align 1
  store i1 %17, i1* %18, align 1
  %19 = load i1, i1* %18, align 1
  br i1 %19, label %20, label %31

20:                                               ; preds = %6
  %21 = load i32, i32* %n, align 4
  %22 = load i32, i32* %i, align 4
  %23 = srem i32 %21, %22
  %24 = alloca i32, align 4
  store i32 %23, i32* %24, align 4
  %25 = load i32, i32* %24, align 4
  %26 = alloca i32, align 4
  store i32 0, i32* %26, align 4
  %27 = load i32, i32* %26, align 4
  %28 = icmp eq i32 %25, %27
  %29 = alloca i1, align 1
  store i1 %28, i1* %29, align 1
  %30 = load i1, i1* %29, align 1
  br i1 %30, label %36, label %39

31:                                               ; preds = %6
  %32 = load i1, i1* %is_prime, align 1
  %33 = load i32, i32* %n, align 4
  %34 = alloca [8 x i8], align 1
  store [8 x i8] c"%d %d \0A\00", [8 x i8]* %34, align 1
  %35 = bitcast [8 x i8]* %34 to i8*
  %printCall = call i32 (i8*, i1, i32, ...) @printf(i8* %35, i1 %32, i32 %33)
  ret void

36:                                               ; preds = %20
  %37 = alloca i1, align 1
  store i1 false, i1* %37, align 1
  %38 = load i1, i1* %37, align 1
  store i1 %38, i1* %is_prime, align 1
  br label %39

39:                                               ; preds = %36, %20
  %40 = load i32, i32* %i, align 4
  %41 = alloca i32, align 4
  store i32 1, i32* %41, align 4
  %42 = load i32, i32* %41, align 4
  %43 = add i32 %40, %42
  %44 = alloca i32, align 4
  store i32 %43, i32* %44, align 4
  %45 = load i32, i32* %44, align 4
  store i32 %45, i32* %i, align 4
  br label %6
}

declare i32 @printf(i8*, i1, i32, ...)
