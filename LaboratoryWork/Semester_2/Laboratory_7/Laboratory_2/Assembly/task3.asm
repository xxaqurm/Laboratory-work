section .data
    numbers dd 3, 12, 5, 444, 0     ; Массив чисел (0 - маркер конца)
    buffer db 12 dup(0)             ; Буфер для вывода
    space db ' '                    ; Пробел
    newline db 0xA                  ; Перевод строки

section .text
    global _start

_start:
    mov esi, numbers                ; Указатель на массив чисел

process_number:
    mov eax, [esi]                  ; Загружаем текущее число
    cmp eax, 0                      ; Проверяем конец массива
    je exit_program
    
    call count_odd_digits           ; Подсчет нечетных цифр
    call print_number               ; Вывод результата
    
    add esi, 4                      ; Переход к следующему числу
    mov eax, [esi]                  ; Проверяем следующее число
    cmp eax, 0                      ; Если не 0 - продолжаем
    je exit_program
    
    ; Выводим пробел между числами
    mov eax, 4
    mov ebx, 1
    mov ecx, space
    mov edx, 1
    int 0x80
    
    jmp process_number              ; Обрабатываем следующее число

exit_program:
    ; Выводим перевод строки
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80
    
    ; Завершаем программу
    mov eax, 1
    xor ebx, ebx
    int 0x80

; Подсчет нечетных цифр в числе (eax -> eax)
count_odd_digits:
    push ebx
    push ecx
    push edx
    
    xor ebx, ebx                    ; Счетчик нечетных цифр
    mov ecx, 10                     ; Для деления на 10
    
digit_loop:
    xor edx, edx
    div ecx                         ; Делим число на 10
    test dl, 1                      ; Проверяем младший бит
    jz even_digit                   ; Если четная цифра
    
    inc ebx                         ; Увеличиваем счетчик нечетных
    
even_digit:
    test eax, eax                   ; Проверяем, осталось ли число
    jnz digit_loop                  ; Продолжаем цикл
    
    mov eax, ebx                    ; Возвращаем результат в eax
    
    pop edx
    pop ecx
    pop ebx
    ret

; Вывод числа (eax)
print_number:
    push eax
    push ebx
    push ecx
    push edx
    
    mov edi, buffer + 11            ; Указатель на конец буфера
    mov byte [edi], 0               ; Нуль-терминатор
    mov ebx, 10                     ; Для деления на 10
    
convert_loop:
    dec edi
    xor edx, edx
    div ebx                         ; Делим число на 10
    add dl, '0'                     ; Преобразуем цифру в символ
    mov [edi], dl                   ; Сохраняем символ
    test eax, eax                   ; Проверяем, осталось ли число
    jnz convert_loop                ; Продолжаем цикл
    
    ; Вычисляем длину строки
    mov eax, buffer + 12
    sub eax, edi
    
    ; Выводим число
    mov eax, 4
    mov ebx, 1
    mov ecx, edi
    mov edx, buffer + 12
    sub edx, edi
    int 0x80
    
    pop edx
    pop ecx
    pop ebx
    pop eax
    ret