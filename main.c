#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca.h"

int main() {

    struct tarefas t[100];
    int cont = 0;
    le_binario(t, &cont);
    int posicao = 0;
    //Variaveis utilizadas no programa, juntamente com a chamada da funcao que abre e le o arquivo binario assim que o programa é iniciado, ja salvando as informacoes do usuario na lista de struct.

    while (1) {

        printf("Menu das Tarefas (Somente entre com numeros): \n");
        printf(" 1 - Inserir tarefa: \n");
        printf(" 2 - Deletar tarefa: \n");
        printf(" 3 - Listar tarefas: \n");
        printf(" 4 - Exportar Tarefas: \n");
        printf(" 5 - Alterar Tarefas: \n");
        printf(" 6 - Sair\n");
        printf("Digite o numero da opcao que deseja usar: \n");

        //Funcao do menu de tarefas, roda em while infinito mostrando o menu para o usuario printando as funcoes disponiveis, ate o usuario optar por sair.


        char *p, s_opcao[100];
        int opcao;
        fgets(s_opcao, sizeof(s_opcao), stdin);
        opcao = strtol(s_opcao, &p, 10);

        //Preparacao do fgets para receber input do usuario.

        if (opcao == 1) {
            printf("Voce entrou na funcao inserir tarefas.\n");
            le_valores(&t[cont]);

            //printf("%d\n",t[cont].prioridade); (debug)
            //printf("%s\n",t[cont].categoria); (debug)
            //printf("%s\n",t[cont].descricao); (debug)
            printf("Tarefa cadastrada com sucesso!\n\n");
            cont++;
            //printf("%d\n",cont); (debug)

            //Funcao de registrar tarefas. Chama a funcao "le_valores" que, como explicado no biblioteca.c, recebe as informacoes do usuario e registra a tarefa.

        } else if (opcao == 2) {
            printf("Voce entrou na funcao deletar tarefas.\n\n");
            int verifica = deletar(cont, t);
            if (verifica == 0) {
                cont--;
            }
        }

            //Funcao de deletar tarefas. Chama a funcao "deletar", que, como explicado no biblioteca.c, recebe o input do usuario e deleta a tarefa. Caso o usuario entre com um input invalido, o programa também o informa e
            //retorna para o menu.


        else if (opcao == 3) {
            //printf("%d\n", tarefas.prioridade); (debug)
            printf("Voce entrou na funcao de listar tarefas.\n\n");
            //printf("%d\n",cont); (debug)
            listar(cont, t);
        }
            //Funcao que lista tarefas. Chama a funcao "listar", que, como explicado no biblioteca.c, itera sobre a lista de struct e mostra para o usuario as informacoes registradas no programa de maneira organizada, com o usuario podendo filtrar quais tarefas quer listar.


        else if (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4  && opcao != 5 && opcao != 6 || p == s_opcao || *p != '\n') {
            printf("Input invalido. Entre somente com valores inteiros entre 1 e 4.\n\n");
        }
            //Print que informa o usuario que entrou com uma opcao nao disponivel pelo programa e retorna ao menu.

        else if (opcao == 4){
            printf("Voce entrou na funcao de exportar tarefas.\n\n");              
            exportar_tarefas(cont, t);
        }
            //Funcao que exporta tarefas para um arquivo .txt a parte. Chama a funcao 'exportar_tarefas', que, como explicado no biblioteca.c, itera sobre a lista de struct e exporta para o usuario as informacoes registradas no programa de maneira organizada, com o usuario podendo filtrar quais tarefas deseja exportar.

        else if (opcao == 5){
          printf("Voce entrou na funcao de alterar tarefas.\n\n");
          alterar_tarefas(cont, t);
            //Funcao que permite ao usuario alterar as variaveis das tarefas que possui registradas. Chama a funcao 'alterar_tarefas", que, como explicado no biblioteca.c, itera sobre a lista de struct, procurando qual tarefa o usuario deseja alterar e depois permite ao usuario escolher qual campo deseja alterar e como/para o que esse campo deve ser alterado.
        }

        else if (opcao == 6) {
            escreve_binario(t, cont);
            printf("Saindo do programa");
            break;
        }
        //Print que escreve as informações em um arquivo binário (verificando se ele foi aberto com sucesso) e sai do programa.
    }
}
