#include <stdio.h>

int main(void)
{
    char s[100]; // Declarar la variable 's'
    
    while (1)
    {
        printf(">> "); // Mostrar el prompt
        scanf("%s", s); // Leer la entrada y almacenarla en 's'
        printf("%s\n", s); // Imprimir la cadena leída
    }
}