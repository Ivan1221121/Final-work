#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <memory.h>
#include <locale.h>

int finish;
char digit;
int res[50];
char str[50];
int num, i;

// Функция преобразования ASCII строки в число
_declspec(naked) void ascbin() {
    _asm {
        mov num, 0           
moveax, num
LabelStart3 :
xorecx, 
movcl, [edi]   
cmpcl, 0        
je LabelEnd3
subecx, 0x30    
movdigit, cl
xorebx, ebx
movbx, 10       
mulbx
xorebx, ebx
movbl, digit
addeax, ebx
incedi
jmp LabelStart3
            LabelEnd3 :
movnum, eax
ret
    }
}

// Функция вычисления y = a / b + c * d - e
_declspec(naked) void func() {
    _asm {
        push ebp
        mov ebp, esp

        mov eax, [ebp + 8]    // a
        mov ebx, [ebp + 12]   // b
        mov ecx, [ebp + 16]   // c
        mov edx, [ebp + 20]   // d
        mov esi, [ebp + 24]   // e

        // Вычисляем a / b
cdq
idivebx
pusheax

        // Вычисляем c * d
movedx, [ebp + 20]
moveax, ecx
imuledx

        // Складываем (a/b) + (c*d)
popecx
        add eax, ecx

        // Вычитаем e
        sub eax, esi

// Восстанавливаем стек и возвращаемся
movesp, ebp
popebp
ret 20                
    }
}

_declspec(naked) void binasc() {
    _asm {
        push ebp
        mov ebp, esp

        mov eax, [ebp + 8]     
movesi, [ebp + 12]    
movedi, [ebp + 16]    

        LabelStart2:
cmpesi, edi
je LabelEnd2
movedx, [esi]       
addedx, 0x30        
mov[eax], dl
addesi, 4           
inceax
jmp LabelStart2
            LabelEnd2 :
movbyteptr[eax], 0 
mov i, eax
pop ebp
            ret
    }
}

void main() {
setlocale(LC_ALL, "rus");
    int a, b, c, d, e;
	double z;

// Ввод данных
printf("Введите a: ");
scanf("%d", &a);
printf("Введите b: ");
scanf("%d", &b);
printf("Введите c: ");
scanf("%d", &c);
printf("Введите d: ");
scanf("%d", &d);
printf("Введите e: ");
scanf("%d", &e);

    // Вычисление выражения
    _asm {
push e
push d
push c
        push b
        push a
        call func
        mov finish, eax
addesp, 20          
    }

    // Вывод результата
printf("Результат y = a / b + c * d - e: %d\n", finish);
    getch();
}
