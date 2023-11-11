#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca.h"




void limpa_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

//Funcao para prevenir erros no armazenamento e leitura de informacoes.

void le_valores(struct tarefas *armazena) {

    int var_prioridade;
    int var_estado;
    do{
        printf("Digite a prioridade: ");
        scanf("%d", &var_prioridade);

        if(var_prioridade < 0 || var_prioridade > 10){
            printf("Input Invalido. Entre com um valor entre 0 e 10\n");
        }
    } while (var_prioridade < 0 || var_prioridade > 10);

    armazena->prioridade = var_prioridade;
    limpa_buffer();
    printf("Digite a categoria: ");
    scanf("%[^\n]", armazena->categoria);
    limpa_buffer();
    printf("Digite a descricao: ");
    scanf("%[^\n]", armazena->descricao);
    limpa_buffer();
    do{
        printf("Digite o estado da tarefa: \n");
        printf("1 - Nao Iniciada\n2 - Em Andamento\n3 - Completa\n");
        scanf("%d", &var_estado);

        if(var_estado < 1 || var_estado > 3){
            printf("Input invalido. Entre com um valor entre 1 e 3.");
        }
    } while (var_estado < 1 || var_estado > 3);
    armazena->estado = var_estado;
    limpa_buffer();
}

//Funcao que recebe as informacoes do usuario e as armazena na variavel apropriada. O programa recebe os inputs por meio da funcao "scanf" e a funcao "armazena" guarda as informacoes nas variaveis da struct. Utilizamos a
//funcao limpa buffer depois de cada scanf para evitar erros no armazenamento e leitura das informacoes. A funcao tambem utiliza um laco "do while" para impedir que o usuario entre com valores abaixo de 0 ou acima de 10
//no campo de prioridade, ou abaixo de 0 e maior do que 4 no campo de estado, uma vez que o programa so trabalha com valores nesse intervalo para essas variaveis. Caso o usuario entre com um input invalido nesse campos, o programa ira pedir novamente para que entre com outro
//valor de prioridade que atenda ao intervalo entre 0 e 10.

int deletar(int cont, struct tarefas *t){
    printf("Entre o numero da tarefa que deseja deletar: ");

    int posicao;
    char *p_posicao, s_posicao[100];
    fgets(s_posicao, sizeof(s_posicao), stdin);
    posicao = strtol(s_posicao, &p_posicao, 10);
    if(p_posicao == s_posicao || *p_posicao != '\n') {
        printf("Input invalido. Entre somente com numeros inteiros.\n\n");
        return 1;
    }
    else if(posicao <= 0 && cont > 1 || posicao > cont && cont > 1){
        printf("Numero invalido! Entre um numero entre 1 e %d\n\n", cont);
        return 1;
    }
    else if(cont == 0){
        printf("Voce nao tem nenhuma tarefa registrada.\n\n");
        return 1;
    }
    else if(posicao <= 0 && cont == 1 || posicao > cont && cont == 1){
        printf("Numero invalido! Voce tem somente 1 tarefa registrada.\n\n");
        return 1;
    }
    else{
        //printf("erro\n");
        //printf("%d\n",posicao - 1);
        //printf("%d\n",cont);
        for(int i = posicao - 1; i < cont ; i++){
            //printf("%d\n", i);
            //printf("%d\n", posicao);
            //printf("%d\n", cont);
            t[i] = t[i + 1];
        }
        printf("Tarefa deletada\n\n");
        return 0;
    }
}

//Funcao de deletar tarefas. Recebe do usuario a posicao que ele quer deletar e soma 1 ao indice (ja que nosso programa, procurando ser mais user friendly, lista as tarefas a partir do 1 ao inves do 0. Caso o usuario informe um numero menor ou igual a
//0, o programa informa que o numero digitado foi invalido e pede para que o usuario insira um numero entre 1 e o numero de tarefas disponiveis. Com o usuario informando um numero valido, o laco for procura por esse numero na lista de tarefas e a deleta,
//rearrumando a lista. Caso o usuario entre com um input valido (como uma letra, por exemplo), o programa o informa e retorna para o menu. Caso o usuario não tem nenhuma tarefa registrada ou só tenha uma, o programa também o
//informa aproriadamente e retorna para o menu.


int listar(int cont, struct tarefas *t) {
    if (cont == 0){
        printf("Voce nao possui nenhuma tarefa registrada.\n\n");
        return 1;
    }
    //Condicao que informa o usuario que nao possui nenhuma conta registrada, logo, nao há contas para listar.
    int filtrar;
    int verifica = 0;
    do {
        printf("Escolha como deseja listar as tarefas: \n");
        printf("1 - Filtrar por ordem de adicao\n");
        printf("2 - Filtrar por prioridade\n");
        printf("3 - Filtrar por estado\n");
        printf("4 - Filtrar por categoria\n");
        printf("5 - Filtrar por prioridade e categoria\n");
        scanf("%d", &filtrar);
        if (filtrar < 1 || filtrar > 5) {
            printf("Input invalido. Entre com um valor inteiro entre 1 e 5.\n\n");
        }
    } while (filtrar < 1 || filtrar > 5);
    limpa_buffer();
    //Menu que informa ao usuario todos as opcoes de filtragem disponiveis para verificar suas tarefas. Possui uma condicao com do while em que, caso o usuario entre com um valor abaixo de 1 ou acima de 5, o programa ira pedir novamente para entrar com um valor dentro do intervalo permitido.
    
    if (filtrar == 1) {
        printf("Lista de tarefas: \n\n");
        for (int x = 0; x < cont; x++) {
            printf("Tarefa %d\n", x + 1);
            printf("Nivel de prioridade: %d\n", t[x].prioridade);
            printf("Categoria: %s\n", t[x].categoria);
            printf("Descricao: %s\n", t[x].descricao);
            if (t[x].estado == 1) {
                printf("Estado: Tarefa nao iniciada\n\n");
            }
            if (t[x].estado == 2) {
                printf("Estado: Em Andamento\n\n");
            }
            if (t[x].estado == 3) {
                printf("Estado: Tarefa completa\n\n");
            }
        }
        return 0;

    //Condicao que filtra as tarefas por ordem de adicao, demonstrando todas as tarefas registradas para o usuario na ordem em que foram adicionadas ao programa. Para isso, o laco for for itera sobre a lista de struct e printa todas as tarefas na ordem em que foram adicionadas, mostrando para o usuario todos os
    //campos que registrou (Prioridade, Categoria, Descrição e Estado), os laços if identificam qual estado o usuario registrou para cada tarefa.    
        
    } else if (filtrar == 2) {
        int var_prioridade;
        do{
            printf("Entre com a prioridade que deseja utilizar para filtrar as tarefas: \n");
            scanf("%d", &var_prioridade);

            if (var_prioridade < 0 || var_prioridade > 10){
                printf("Input invalido. Entre com um valor entre 0 e 10.\n\n");
            }
        } while (var_prioridade < 0 || var_prioridade > 10);
        limpa_buffer();

        printf("Lista de tarefas: \n\n");
        for (int x = 0; x < cont; x++) {
            if (var_prioridade == t[x].prioridade) {
                verifica++;
                printf("Tarefa %d\n", x + 1);
                printf("Nivel de prioridade: %d\n", t[x].prioridade);
                printf("Categoria: %s\n", t[x].categoria);
                printf("Descricao: %s\n", t[x].descricao);
                if (t[x].estado == 1) {
                    printf("Estado: Tarefa nao iniciada\n\n");
                }
                if (t[x].estado == 2) {
                    printf("Estado: Em Andamento\n\n");
                }
                if (t[x].estado == 3) {
                    printf("Estado: Tarefa completa\n\n");
                }
            }
            else if(x == cont - 1 && verifica == 0){
                printf("Voce nao possui nenhuma tarefa registrada com essa prioridade.\n\n");
                return 1;
            }
        }
        return 0;
    }
        //Condicao que filtra as tarefas por prioridade. Funciona com um laco 'do while' pedindo ao usuario qual valor de prioridade deseja utilizar para listar as tarefas, caso o usuario entre com algum valor invalido de prioridade, o programa ira pedir o input de novo. O laco for itera sobre a lista de struct e, 
        //por meio da condicao if, printa todas as tarefas que possuam a prioridade solicitada pelo usuario, com os lacos if adicionais identificando qual estado o usuario registrou para cada tarefa. A funcao limpa buffer previne erros de armazenamento e leitura dos valores do scanf. A condicao else if informa o
        //usuario que ele nao possui nenhuma tarefa registrada com a prioridade solicitada.

        

    else if (filtrar == 3) {
        int var_estado;
        do{
            printf("Digite o estado que deseja utilizar para filtrar as tarefas: \n");
            printf("1 - Nao Iniciada\n2 - Em Andamento\n3 - Completa\n");
            scanf("%d", &var_estado);

            if(var_estado < 1 || var_estado > 3){
                printf("Input invalido. Entre com um valor entre 1 e 3.");
            }
        } while (var_estado < 1 || var_estado > 3);
        limpa_buffer();
        printf("Lista de tarefas: \n\n");
        for (int x = 0; x < cont; x++) {
            if (var_estado == t[x].estado) {
                verifica++;
                printf("Tarefa %d\n", x + 1);
                printf("Nivel de prioridade: %d\n", t[x].prioridade);
                printf("Categoria: %s\n", t[x].categoria);
                printf("Descricao: %s\n", t[x].descricao);
                if (t[x].estado == 1) {
                    printf("Estado: Tarefa nao iniciada\n\n");
                }
                if (t[x].estado == 2) {
                    printf("Estado: Em Andamento\n\n");
                }
                if (t[x].estado == 3) {
                    printf("Estado: Tarefa completa\n\n");
                }
            }
            else if(x == cont - 1 && verifica == 0){
                printf("Voce nao possui nenhuma tarefa registrada com esse estado.\n\n");
                return 1;
            }
        }
        return 0;
    }
        //Condicao que filtra as tarefas por estado. Tambem utiliza um laco 'do while' pedindo ao usuario qual valor de estado deseja utilizar para listar as tarefas, caso o usuario entre com algum valor invalido, o programa ira pedir o input de novo. O laco for itera sobre a lista de struct e, por meio da condicao
        //if, printa todas as tarefas que possuam o estado solicitado pelo usuario, com os lacos if adicionais identificando qual estado o usuario registrou para cada tarefa. A funcao limpa buffer previne erros de armazenamento e leitura dos valores do scanf. A condicao else if informa o usuario que ele nao possui
        //nenhuma tarefa registrada com o estado solicitado.

    else if (filtrar == 4){
        char categoria_[100];
        printf("Entre com a categoria que deseja utilizar para filtrar as tarefas: \n");
        scanf("%[^\n]", categoria_);
        limpa_buffer();
        printf("Lista de tarefas: \n\n");
        for(int y = 10; y >= 0; y--){
            for(int x = 0; x < cont; x++){
                int r = strcmp(categoria_, t[x].categoria);
                //printf("y: %d\n", y);
                //printf("x: %d\n", x);
                if (r == 0 && y == t[x].prioridade){
                    verifica++;
                    printf("Tarefa %d\n", x + 1);
                    printf("Nivel de prioridade: %d\n", t[x].prioridade);
                    printf("Categoria: %s\n", t[x].categoria);
                    printf("Descricao: %s\n", t[x].descricao);
                    if (t[x].estado == 1) {
                        printf("Estado: Tarefa nao iniciada\n\n");
                    }
                    if (t[x].estado == 2) {
                        printf("Estado: Em Andamento\n\n");
                    }
                    if (t[x].estado == 3) {
                        printf("Estado: Tarefa completa\n\n");
                    }
                }

            }
        }

            //Condicao que filtra as tarefas por categoria. Solicita ao usuario qual categoria deseja utilizar para filtrar as tarefas e trabalha com dois lacos for, um que itera sobre a lista de struct printando as tarefas com a categoria solicitada pelo usuario e outro que ira realizar esse print de maneira que
            //as tarefas sejam listadas em ordem de prioridade decrescente (da maior para menor), a condicao if é aplicada para ambos os lacos for, com os lacos if adicionais identificando qual estado o usuario registrou para cada tarefa. A funcao limpa buffer previne erros de armazenamento e leitura dos valores do 
            //scanf.
        
        if(verifica == 0){
            printf("Voce nao tem nenhuma tarefa registrada com essa categoria.\n\n");
            return 1;
        }
        return 0;
    }
            //Condicao que informa o usuario que nao existe nenhuma tarefa registrada com a categoria que solicitou.

    else if (filtrar == 5){
        int var_prioridade;
        char categoria_[100];
        do{
            printf("Entre com a prioridade que deseja utilizar para filtrar as tarefas: \n");
            scanf("%d", &var_prioridade);

            if (var_prioridade < 0 || var_prioridade > 10){
                printf("Input invalido. Entre com um valor entre 0 e 10.\n\n");
            }
        } while (var_prioridade < 0 || var_prioridade > 10);
        limpa_buffer();
        printf("Entre com a categoria que deseja utilizar para filtrar as tarefas: \n");
        scanf("%[^\n]", categoria_);
        limpa_buffer();
        printf("Lista de tarefas: \n\n");
        for(int x = 0; x < cont; x++){
            int r = strcmp(categoria_, t[x].categoria);
            if(var_prioridade == t[x].prioridade && r == 0){
                verifica++;
                printf("Tarefa %d\n", x + 1);
                printf("Nivel de prioridade: %d\n", t[x].prioridade);
                printf("Categoria: %s\n", t[x].categoria);
                printf("Descricao: %s\n", t[x].descricao);
                if (t[x].estado == 1) {
                    printf("Estado: Tarefa nao iniciada\n\n");
                }
                if (t[x].estado == 2) {
                    printf("Estado: Em Andamento\n\n");
                }
                if (t[x].estado == 3) {
                    printf("Estado: Tarefa completa\n\n");
                }
            }
            else if(x == cont - 1 && verifica == 0){
                printf("Voce nao possui nenhuma tarefa registrada com essa prioridade e com essa categoria simultaneamente.\n\n");
                return 1;
            }
        }
    }
    return 0;
}
            //Condicao que filtra as tarefas por prioridade e categoria. Funcionando como uma juncao das condicoes 2 e 4, funciona com um laco 'do while' solicitando ao usuario que entre com a prioridade que deseja utilizar para filtrar as tarefas, em que, caso o usuario entre com um valor invalido para prioridade,
            //o programa ira solicitar o valor novamente, e depois solicita ao usuario qual categoria deseja utilizar para filtrar. O laco 'for' itera sobre a lista de struct e, por meio da condicao if, lista para o usuario todas as tarefas que possuam a prioridade e a categoria solicitadas pelo usuario, com os
            //lacos if adicionais identificando qual estado o usuario registrou para cada tarefa. A funcao limpa buffer previne erros de armazenamento e leitura dos valores do scanf. A condicao else if, por fim, informa ao usuario que nao possui nenhuma tarefa registrada com a prioridade e/ou com a categoria
            //solicitadas pelo usuario.

int exportar_tarefas(int cont, struct tarefas *t){
    if(cont == 0){
        printf("Voce nao possui tarefas registradas.");
        return 1;
    }
        //Condicao que informa o usuario que nao possui tarefas registradas para exportar.
    
    int exportar;
    int verifica = 0;
    do {
        printf("Escolha como deseja listar as tarefas: \n");
        printf("1 - Exportar por ordem de adicao\n");
        printf("2 - Exportar por prioridade\n");
        printf("3 - Exportar por estado\n");
        printf("4 - Exportar por categoria\n");
        printf("5 - Exportar por prioridade e categoria\n");
        scanf("%d", &exportar);
        if (exportar < 1 || exportar > 5) {
            printf("Input invalido. Entre com um valor inteiro entre 1 e 5");
        }
    } while (exportar < 1 || exportar > 5);
    
    //Menu que informa ao usuario todos as opcoes de filtragem disponiveis para exportar suas tarefas. Possui uma condicao com do while em que, caso o usuario entre com um valor abaixo de 1 ou acima de 5, o programa ira pedir novamente para entrar com um valor dentro do intervalo permitido.
    

    FILE *f = fopen("tarefas.txt", "wb");
    fprintf(f, "Tarefas Exportadas: \n\n");
    //Declaracao do arquivo 'tarefas.txt' e 'abertura' do arquivo tarefas.txt, que exibira ao usuario as tarefas exportadas. O fprintf printara para o arquivo .txt a frase 'Tarefas Exportadas:'.

    if (exportar == 1) {
        for (int x = 0; x < cont; x++) {
            fprintf(f,"Tarefa %d\n", x + 1);
            fprintf(f,"Nivel de prioridade: %d\n", t[x].prioridade);
            fprintf(f,"Categoria: %s\n", t[x].categoria);
            fprintf(f,"Descricao: %s\n", t[x].descricao);
            if (t[x].estado == 1) {
                fprintf(f,"Estado: Tarefa nao iniciada\n\n");
            }
            if (t[x].estado == 2) {
                fprintf(f,"Estado: Em Andamento\n\n");
            }
            if (t[x].estado == 3) {
                fprintf(f,"Estado: Tarefa completa\n\n");
            }
        }
        fclose(f);
        limpa_buffer();
        return 0;

        //Condicao que exporta as tarefas para um arquivo .txt por ordem de adicao. demonstrando todas as tarefas registradas para o usuario na ordem em que foram adicionadas ao programa. Para isso, o laco for for itera sobre a lista de struct e printa todas as tarefas na ordem em que foram adicionadas, mostrando 
        //para o usuario todos os campos que registrou (Prioridade, Categoria, Descrição e Estado), os laços if identificam qual estado o usuario registrou para cada tarefa. A funcao limpa buffer previne erros no armazenamento e leitura dos valores do scanf. A função "fclose(f)" fecha o arquivo .txt para qual as 
        //tarefas estão sendo exportadas.
        
        } else if (exportar == 2) {
        int var_prioridade;
        do{
            printf("Entre com a prioridade que deseja utilizar para exportar as tarefas: \n");
            scanf("%d", &var_prioridade);

            if (var_prioridade < 0 || var_prioridade > 10){
                printf("Input invalido. Entre com um valor entre 0 e 10.\n\n");
            }
        } while (var_prioridade < 0 || var_prioridade > 10);
        limpa_buffer();
        for (int x = 0; x < cont; x++) {
            if (var_prioridade == t[x].prioridade) {
                verifica++;
                fprintf(f,"Tarefa %d\n", x + 1);
                fprintf(f,"Nivel de prioridade: %d\n", t[x].prioridade);
                fprintf(f,"Categoria: %s\n", t[x].categoria);
                fprintf(f,"Descricao: %s\n", t[x].descricao);
                if (t[x].estado == 1) {
                    fprintf(f,"Estado: Tarefa nao iniciada\n\n");
                }
                if (t[x].estado == 2) {
                    fprintf(f,"Estado: Em Andamento\n\n");
                }
                if (t[x].estado == 3) {
                    fprintf(f,"Estado: Tarefa completa\n\n");
                }
            }
            else if(x == cont - 1 && verifica == 0){
                printf("Voce nao possui nenhuma tarefa registrada com essa prioridade.\n\n");
                return 1;
            }
        }
        fclose(f);
        return 0;
    }
        //Condicao que exporta as tarefas filtrando-as por prioridade. Funciona com um laco 'do while' pedindo ao usuario qual valor de prioridade deseja utilizar para listar as tarefas, caso o usuario entre com algum valor invalido de prioridade, o programa ira pedir o input de novo. O laco for itera sobre a lista de struct  
        //e, por meio da condicao if, exporta para um arquivo .txt todas as tarefas que possuam a prioridade solicitada pelo usuario, com os lacos if adicionais identificando qual estado o usuario registrou para cada tarefa. A funcao limpa buffer previne erros de armazenamento e leitura dos valores do scanf. A condicao 
        //else if informa o usuario caso ele nao possua nenhuma tarefa registrada com a prioridade solicitada. A função "fclose(f)" fecha o arquivo .txt para qual as tarefas estão sendo exportadas.

    else if (exportar == 3) {
        int var_estado;
        do{
            printf("Digite o estado que deseja utilizar para exportar as tarefas: \n");
            printf("1 - Nao Iniciada\n2 - Em Andamento\n3 - Completa\n");
            scanf("%d", &var_estado);

            if(var_estado < 1 || var_estado > 3){
                printf("Input invalido. Entre com um valor entre 1 e 3.");
            }
        } while (var_estado < 1 || var_estado > 3);
        limpa_buffer();
        for (int x = 0; x < cont; x++) {
            if (var_estado == t[x].estado) {
                verifica++;
                fprintf(f,"Tarefa %d\n", x + 1);
                fprintf(f,"Nivel de prioridade: %d\n", t[x].prioridade);
                fprintf(f,"Categoria: %s\n", t[x].categoria);
                fprintf(f,"Descricao: %s\n", t[x].descricao);
                if (t[x].estado == 1) {
                    fprintf(f,"Estado: Tarefa nao iniciada\n\n");
                }
                if (t[x].estado == 2) {
                    fprintf(f,"Estado: Em Andamento\n\n");
                }
                if (t[x].estado == 3) {
                    fprintf(f,"Estado: Tarefa completa\n\n");
                }
            }
            else if(x == cont - 1 && verifica == 0){
                printf("Voce nao possui nenhuma tarefa registrada com esse estado.\n\n");
                return 1;
            }
        }
        fclose(f);
        return 0;
    }
        //Condicao que exporta as tarefas por estado. Tambem utiliza um laco 'do while' pedindo ao usuario qual valor de estado deseja utilizar para listar as tarefas, caso o usuario entre com algum valor invalido, o programa ira pedir o input de novo. O laco for itera sobre a lista de struct e, por meio da 
        //condicao if, printa todas as tarefas que possuam o estado solicitado pelo usuario, com os lacos if adicionais identificando qual estado o usuario registrou para cada tarefa. A funcao limpa buffer previne erros de armazenamento e leitura dos valores do scanf. A condicao else if informa o usuario que 
        //ele nao possui nenhuma tarefa registrada com o estado solicitado. A função "fclose(f)" fecha o arquivo .txt para qual as tarefas estão sendo exportadas.

    else if (exportar == 4){
        char categoria_[100];
        printf("Entre com a categoria que deseja utilizar para exportar as tarefas: \n");
        scanf("%[^\n]", categoria_);
        limpa_buffer();
        for(int y = 10; y >= 0; y--){
            for(int x = 0; x < cont; x++){
                int r = strcmp(categoria_, t[x].categoria);
                if (r == 0){
                    verifica++;
                    fprintf(f,"Tarefa %d\n", x + 1);
                    fprintf(f,"Nivel de prioridade: %d\n", t[x].prioridade);
                    fprintf(f,"Categoria: %s\n", t[x].categoria);
                    fprintf(f,"Descricao: %s\n", t[x].descricao);
                    if (t[x].estado == 1) {
                        fprintf(f,"Estado: Tarefa nao iniciada\n\n");
                    }
                    if (t[x].estado == 2) {
                        fprintf(f,"Estado: Em Andamento\n\n");
                    }
                    if (t[x].estado == 3) {
                        fprintf(f,"Estado: Tarefa completa\n\n");
                    }
                }
            }
        }
            //Condicao que exporta as tarefas filtrando-as por categoria. Solicita ao usuario qual categoria deseja utilizar para filtrar as tarefas e trabalha com dois lacos for, um que itera sobre a lista de struct printando as tarefas com a categoria solicitada pelo usuario e outro que ira realizar esse print de maneira que
            //as tarefas sejam listadas em ordem de prioridade decrescente (da maior para menor), a condicao if é aplicada para ambos os lacos for, com os lacos if adicionais identificando qual estado o usuario registrou para cada tarefa. A funcao strcmp compara, por meio do laco for, a string inseridada pelo usuario com as da listra de struct, caso ambas sejam iguais, o print poderá ocorrer.. A funcao limpa buffer previne erros de armazenamento e leitura dos valores do 
            //scanf.
        
        if(verifica == 0){
            printf("Voce nao possui nenhuma tarefa registrada com essa categoria.\n\n");
            return 1;
        }
        fclose(f);
        return 0;
    }
         //Condicao que informa o usuario que nao existe nenhuma tarefa registrada com a categoria que solicitou. A função "fclose(f)" fecha o arquivo .txt para qual as tarefas estão sendo exportadas.

    else if (exportar == 5){
        int var_prioridade;
        char categoria_[100];
        do{
            printf("Entre com a prioridade que deseja utilizar para exportar as tarefas: \n");
            scanf("%d", &var_prioridade);

            if (var_prioridade < 0 || var_prioridade > 10){
                printf("Input invalido. Entre com um valor entre 0 e 10.\n\n");
            }
        } while (var_prioridade < 0 || var_prioridade > 10);
        limpa_buffer();
        printf("Entre com a categoria que deseja utilizar para exportar as tarefas: \n");
        scanf("%[^\n]", categoria_);
        limpa_buffer();
        for(int x = 0; x < cont; x++){
            int r = strcmp(categoria_, t[x].categoria);
            if(var_prioridade == t[x].prioridade && r == 0){
                verifica++;
                fprintf(f,"Tarefa %d\n", x + 1);
                fprintf(f,"Nivel de prioridade: %d\n", t[x].prioridade);
                fprintf(f,"Categoria: %s\n", t[x].categoria);
                fprintf(f,"Descricao: %s\n", t[x].descricao);
                if (t[x].estado == 1) {
                    fprintf(f,"Estado: Tarefa nao iniciada\n\n");
                }
                if (t[x].estado == 2) {
                    fprintf(f,"Estado: Em Andamento\n\n");
                }
                if (t[x].estado == 3) {
                    fprintf(f,"Estado: Tarefa completa\n\n");
                }
            }
            else if(x == cont - 1 && verifica == 0){
                printf("Voce nao possui nenhuma tarefa registrada com essa prioridade e com essa categoria simultaneamente.\n\n");
                return 1;
            }
        }
        fclose(f);
    }
    return 0;

}

int alterar_tarefas(int cont, struct tarefas *t){
    int posicao;
    printf("Digite qual tarefa deseja alterar: \n");
    scanf("%d", &posicao);
    limpa_buffer();
    //declaracao da variavel posicao, que ira receber do usuario, por meio do scanf, qual tarefa ele deseja alterar. A funcao limpa buffer previne erros de armazenamento e leitura dos valores do scanf.
    if(posicao <= 0 && cont > 1 || posicao > cont && cont > 1){
        printf("Numero invalido! Entre um numero entre 1 e %d\n\n", cont);
        return 1;
    }
        //Condicao que informa o usuario que entrou com uma posicao invalida, e pede para o usuario entrar com uma posicao dentro do intervalo disponivel.
        
    else if(posicao <= 0 && cont == 1 || posicao > cont && cont == 1){
        printf("Numero invalido! Voce tem somente 1 tarefa registrada.\n\n");
        return 1;
    }

        //Condicao que informa o usuario que entrou com uma posicao invalida, e o informa que só possui uma tarefa registrada.
        
    else if(cont == 0){
        printf("Voce nao possui nenhuma tarefa registrada.\n\n");
        return 1;
    }

    //Condicao que informa o usuario que nao possui nenhuma tarefa registrada, assim, nao sendo proceder com a funcao de alterar tarefas.

    int var_alterar;
    int verifica = 0;
    do{
        printf("\nDigite qual campo da tarefa deseja alterar: \n");
        printf("1 - Alterar prioridade\n2 - Alterar categoria\n3 - Alterar descrição\n4 - Alterar estado\n\n");
        scanf("%d", &var_alterar);
        limpa_buffer();

        if(var_alterar < 1 || var_alterar > 4){
            printf("Input invalido. Digite um valor entre 1 e 4.\n");
        }
    } while(var_alterar < 1 || var_alterar > 4);

        //Laco do while que realiza o print do menu da funcao alterar tarefas para o usuario, solicitando qual campo da tarefa ele deseja alterar. Caso o usuario entre com um numero abaixo de 1 ou maior do que 4, o programa o informa e retorna ao menu.

    if(var_alterar == 1){
        int var_prioridade;

        do{
            printf("Entre com a nova prioridade: \n");
            scanf("%d", &var_prioridade);
            if(var_prioridade < 0 || var_prioridade > 10){
                printf("Input invalido. Entre com um numero inteiro entre 1 e 10.\n\n");
            }
        } while(var_prioridade < 0 || var_prioridade > 10);
        limpa_buffer();

        for(int x = 0; x < cont; x++){
            if(x == posicao - 1){
                t[x].prioridade = var_prioridade;
                printf("Prioridade alterada com sucesso!\n\n");
                return 0;
            }
        }
    }

        //Condicao que permite ao usuario alterar a prioridade de alguma de suas tarefas. O programa solicita ao usuario a nova prioridade que deseja inserir na tarefa (selecionada pelo input de posicao no inicio da funcao). O laco "do while" previne que o usuario entre com um valor invalido para a variavel
        //de prioridade (menor do que 0 ou maior do que 10). Apos o usuario escolher a nova prioridade, o laco for identifica a posicao da tarefa na lista e altera o valor de prioridade para o novo valor selecionado pelo usuario. A funcao limpa buffer previne erros de leitura e armazenamento dos valores do scanf.
        
    else if(var_alterar == 2){
        char categoria_[100];
        printf("Entre com a nova categoria: \n");
        scanf("%[^\n]", categoria_);
        limpa_buffer();
        for(int x = 0; x < cont; x++){
            if(x == posicao - 1){
                strcpy(t[x].categoria , categoria_);
                printf("Categoria alterada com sucesso!\n\n");
                return 0;
            }
        }
    }

        //Condicao que permite ao usuario alterar a categoria de alguma de suas tarefas. O programa solicita ao usuario a nova categoria que deseja inserir na tarefa (selecionada pelo input de posicao no inicio da funcao). O laco for identifica a tarefa na lista e altera a categoria para a nova string inserida
        //pelo usuario, processo feito pela funcao strcpy. A funcao limpa buffer previne erros de leitura e armazenamento dos valores do scanf.
        
    else if (var_alterar == 3){
        char descricao_[300];
        printf("Entre com a nova descricao: \n");
        scanf("%[^\n]", descricao_);
        limpa_buffer();
        for(int x = 0; x < cont; x++){
            if(x == posicao - 1){
                strcpy(t[x].descricao , descricao_);
                printf("Descricao alterada com sucesso!\n\n");
                return 0;
            }
        }
    }

        //Condicao que permite o usuario alterar a descricao de alguma de suas tarefas. O programa solicita ao usuario a nova descricao que deseja inserir na tarefa (selecionada pelo input de posicao no inicio da funcao). O laco for identifica a tarefa na lista e altera a descricao para a nova string inserida
        //pelo usuario, processo feito pela funcao strcpy. A funcao limpa buffer previne erros de leitura e armazenamento dos valores do scanf.
        
    else if (var_alterar == 4){
        int var_estado;
        do{
            printf("Entre com o novo estado: \n");
            printf("1 - Nao iniciada\n2 - Em Andamento\n3 - Tarefa Completa\n\n");
            scanf("%d", &var_estado);
            if(var_estado < 1 || var_estado > 3){
                printf("Input invalido, entre com um numero inteiro entre 1 e 3.");
            }
        } while(var_estado < 1 || var_estado > 3);
        limpa_buffer();
        for(int x = 0; x < cont; x++){
            if(x == posicao - 1){
                t[x].estado = var_estado;
                printf("Estado alterado com sucesso.\n\n");
            }
        }
    }
  return 0;
}

        //Condicao que permite ao usuario alterar o estado de alguma de suas tarefas. O programa solicita ao usuario o novo valor de estado que deseja inserir na tarefa (selecionada pelo input de posicao no inicio da funcao). O laco 'do while' previne que o usuario entre com algum valor invalido para a variavel
        //de estado (menor do que 1 ou maior do que 3). O laco for identifica a tarefa na lista e altera o estado para o novo valor inserido pelo usuario. A funcao limpa buffer previne erros de leitura e armazenamento dos valores do scanf.


int le_binario(struct tarefas *t, int *cont) {
    FILE *arquivo_binario;
    arquivo_binario = fopen("binario", "rb");
    if (arquivo_binario) {

        fread(cont, sizeof(int), 1, arquivo_binario);
        //printf("%d\n", *cont);



        fread(t, sizeof(struct tarefas), 100, arquivo_binario);

        return 0;
    }
    else{
        return 1;
    }
}


// Funcao que le todas as informacoes dos clientes de um arquivo binario logo na inicializacao do programa, carregando todos os dados salvos de um uso anterior.


void escreve_binario(struct tarefas *t, int cont) {
    FILE *arquivo_binario;
    arquivo_binario = fopen("binario", "wb");
    //printf("%p\n", arquivo_binario);
    if (arquivo_binario) {
        //printf("entrou\n");

        //printf("%d\n", t->prioridade);
        fwrite(&cont, sizeof(int), 1, arquivo_binario);


        fwrite(t, sizeof(struct tarefas), 100, arquivo_binario);

        fclose(arquivo_binario);
    }
    else{
        printf("Erro ao abrir o arquivo\n");
    }

}
//Funcao que, ao usuario escolher sair do programa, registra todas as informacoes salvas em um arquivo binario, que é lido pela funcao 'le_binario' na inicializacao do programa.
