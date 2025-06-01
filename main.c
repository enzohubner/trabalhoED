#include <stdio.h>
#include "bdpaciente.h"
#include <stdlib.h>

int main(void) 
{
    BDPaciente bd;
    bd.quantidade = 0;
    char parada = ' ';
    guardar_dados(&bd);

    while (parada != 'q' && parada != 'Q') 
    {
        system("clear");

        printf(
            "1 - Consultar paciente\n"
            "5 - Imprimir lista de pacientes\n"
            "Q - Sair\n"
        );
        printf("Digite a opcao: ");
        scanf(" %c", &parada); 

        if (parada == '1') 
        {
            consultar_pacientes(&bd);
        } 
        else if (parada == '5') 
        {
            imprimir_todos_pacientes(&bd);

            printf("\nPressione ENTER para continuar...");
            getchar(); 
            getchar(); 
        }
    }
    system("clear");

    return 0;
}
