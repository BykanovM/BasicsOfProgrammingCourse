#ifndef ARRAY_STRING__H
#define ARRAY_STRING__H

//возвращает количество символов в строке не считая ноль-символ
size_t strlen_(const char *begin);

//возвращает указатель на первый элемент с кодом ch, расположенным
//на ленте памяти между адресами begin и end не включая end
char* find(char *begin, char *end, int ch);

#endif //ARRAY_STRING__H