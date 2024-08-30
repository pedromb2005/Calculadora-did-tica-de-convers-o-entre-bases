#include <stdio.h>

void convertedorBi(int num) {
    int binario[32];
    int i = 0;

    while (num > 0) {
        binario[i] = num % 2;
        num /= 2;
        i++;
    }

    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binario[j]);
    }
    printf("\n");
}

void convertedorOc(int num) {
    int octal[32];
    int i = 0;

    while (num > 0) {
        octal[i] = num % 8;
        num /= 8;
        i++;
    }

    for (int j = i - 1; j >= 0; j--) {
        printf("%d", octal[j]);
    }
    printf("\n");
}

void convertedorHex(int num) {
    char hexadecimal[32];
    int i = 0;

    while (num > 0) {
        int resto = num % 16;

        if (resto < 10) {
            hexadecimal[i] = 48 + resto;
        } else {
            hexadecimal[i] = 55 + resto; 
        }

        num /= 16;

        i++;
    }

    for (int j = i - 1; j >= 0; j--) {
        printf("%c", hexadecimal[j]);
    }
    printf("\n");
}

void convertedorBCD(int num) {
    int bcd[32];
    int i = 0;

    while (num > 0) {
        int dgt = num % 10;

        for (int j = 0; j < 4; j++) {
            bcd[i + 3 - j] = dgt % 2;
            dgt /= 2;
        }

        i += 4;

        num /= 10;
    }

    for (int j = i - 1; j >= 0; j--) {
        printf("%d", bcd[j]);
    }
    printf("\n");
}

void convertedorComplemento2(int num) {
    unsigned short binario[16];
    int i = 15;
    
    if (num < 0) {
        num = (1 << 16) + num;
    }

    for (; i >= 0; i--) {
        binario[i] = num % 2;
        num /= 2;
    }

    for (i = 0; i < 16; i++) {
        printf("%d", binario[i]);
    }
    printf("\n");
}

void printBits(size_t tam, const void *ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    for (i = tam - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    printf("\n");
}

void convertedorFloat(float num) {
    union {
        float f;
        unsigned int i;
    } u;

    u.f = num;

    int snal = (u.i >> 31) & 1;
    int exp = (u.i >> 23) & 0xFF;
    int exp_c_vies = exp - 127;
    int fracao = u.i & 0x7FFFFF;

    printf("Float: %f\n", num);
    printf("Sinal: %d\n", snal);
    printf("Expoente: %d\n", exp);
    printf("Expoente com sesgo: %d\n", exp_c_vies);
    printf("Fracção: 0x%06X\n", fracao);

    printf("Representação binária completa: ");
    printBits(sizeof(float), &num);
}

void convertedorDouble(double num) {
    union {
        double d;
        unsigned long long i;
    } u;

    u.d = num;
    int snal = (u.i >> 63) & 1;
    int exp = (u.i >> 52) & 0x7FF;
    int exp_c_vies = exp - 1023;
    unsigned long long fracao = u.i & 0xFFFFFFFFFFFFF;

    printf("Double : %lf\n", num);
    printf("Sinal : %d\n", snal);
    printf("Expoente : %d\n", exp);
    printf("Expoente com vies : %d\n", exp_c_vies);
    printf("Fracção : 0x%013llX\n", fracao);

    printf("Representação binária completa: ");
    printBits(sizeof(double), &num);
}


int main(void) {
    int num, i = 1;
    char opcao;
    float numFloat;
    double numDouble;

    while (i) {
        printf("*** Conversor de Bases ***\n");
        printf("1 - Binário [B]\n");
        printf("2 - Octal [O]\n");
        printf("3 - Hexadecimal [H]\n");
        printf("4 - BCD [D]\n");
        printf("5 - Complemento a 2 com 16 bits [C]\n");
        printf("6 - Float [F]\n");
        printf("7 - Double [D]\n");
        printf("Digite um número decimal para converter : ");
        scanf("%d", &num);
        printf("Escolha para qual base deseja converter : ");
        scanf(" %c", &opcao);

        if (opcao == 'B' || opcao == 'b') {
            printf("Binário : ");
            convertedorBi(num);
        } 
        
        else if (opcao == 'O' || opcao == 'o') {
            printf("Octal  : ");
            convertedorOc(num);
        } 
        
        else if (opcao == 'H' || opcao == 'h') {
            printf("Hexadecimal : ");
            convertedorHex(num);
        }

        else if (opcao == 'D' || opcao == 'd') {
            printf("BCD : ");
            convertedorBCD(num);
        }

        else if (opcao == 'C' || opcao == 'c') {
            printf("Complemento a 2 com 16 bits : ");
            convertedorComplemento2(num);
        }

        else if (opcao == 'F' || opcao == 'f') {
            printf("Digite um número real (float): ");
            scanf("%f", &numFloat);
            convertedorFloat(numFloat);
        } 
        
        else if (opcao == 'D' || opcao == 'd') {
            printf("Digite um número real (double): ");
            scanf("%lf", &numDouble);
            convertedorDouble(numDouble);
        } 
        
        else {
            printf("Opção inválida.\n");
        }

        printf("Deseja converter outro número? (1 para Sim, 0 para Não): ");
        scanf("%d", &i);
    }

    return 0;
}
