#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PATRICIA.h"
#include "interface.h"

int main()
{
    PTRC p = NULL;

    while (1)
	{

		int index = menu();
		fflush(stdin);

		switch (index)
		{
		case 1:
            system("cls");
			p = menu_ler_arquivo(p, 1);
			break;
        case 2:
            system("cls");
			p = menu_ler_arquivo(p, 0);
			break;
        case 3:
            system("cls");
			menu_consultar(p);
			break;
        case 4:
            system("cls");
            menu_imprimir_tudo(p);
			break;
        case 5:
            system("cls");
			menu_imprimir_sub(p);
			break;
        case 6:
            system("cls");
			free(p);
            p = NULL;
			break;
        case 0:
            exit(1);
			break;
        }
        
    }
    return 0;
}
