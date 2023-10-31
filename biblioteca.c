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
//no campo de prioridade, uma vez que o programa so trabalha com valores nesse intervalo para essa variavel. Caso o usuario entre com um input invalido nesse campo, o programa ira pedir novamente para que entre com outro
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
        limpa_buffer();
        return 0;

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

    else if (filtrar == 3) {
        int var_estado;
        printf("Entre com o estado que deseja utilizar para filtrar as tarefas: \n");
        printf("1 - Nao Iniciada\n2 - Em Andamento\n3 - Completa\n");
        scanf("%d", &var_estado);
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

    else if (filtrar == 4){
        char categoria_[100];
        printf("Entre com a categoria que deseja utilizar para filtrar as tarefas: \n");
        scanf("%[^\n]", categoria_);
        limpa_buffer();
        printf("Lista de tarefas: \n\n");
        for(int x = 0; x < cont; x++){
            int r = strcmp(categoria_, t[x].categoria);
            if (r == 0){
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
                printf("Voce nao possui nenhuma tarefa registrada com essa categoria.\n\n");
                return 1;
            }
        }
        return 0;
    }

    else if (filtrar == 5){
        int var_prioridade;
        char categoria_[100];
        printf("Entre com a prioridade que deseja utilizar para filtrar as tarefas: \n");
        scanf("%d", &var_prioridade);
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

void exportar_tarefas(int cont, struct tarefas *t){
    if(cont == 0){
        printf("Voce nao possui tarefas registradas.");
    }
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

    FILE *f = fopen("tarefas.txt", "wb");
    fprintf(f, "Tarefas Exportadas: \n\n");

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

    } else if (exportar == 2) {
        int var_prioridade;
        printf("Entre com a prioridade que deseja utilizar para filtrar as tarefas: \n");
        scanf("%d", &var_prioridade);
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
            }
        }
        fclose(f);
    }

    else if (exportar == 3) {
        int var_estado;
        printf("Entre com o estado que deseja utilizar para filtrar as tarefas: \n");
        printf("1 - Nao Iniciada\n2 - Em Andamento\n3 - Completa\n");
        scanf("%d", &var_estado);
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
            }
        }
        fclose(f);
    }

    else if (exportar == 4){
        char categoria_[100];
        printf("Entre com a categoria que deseja utilizar para filtrar as tarefas: \n");
        scanf("%[^\n]", categoria_);
        limpa_buffer();
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
            else if(x == cont - 1 && verifica == 0){
                printf("Voce nao possui nenhuma tarefa registrada com essa categoria.\n\n");
            }
        }
        fclose(f);
    }

    else if (exportar == 5){
        int var_prioridade;
        char categoria_[100];
        printf("Entre com a prioridade que deseja utilizar para filtrar as tarefas: \n");
        scanf("%d", &var_prioridade);
        limpa_buffer();
        printf("Entre com a categoria que deseja utilizar para filtrar as tarefas: \n");
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
            }
        }
        fclose(f);
    }

}

void alterar_tarefas(int cont, struct tarefas *t){
  int posicao;
  printf("Digite qual tarefa deseja alterar: \n");
  scanf("%d", &posicao);
  limpa_buffer();
  if(posicao <= 0 && cont > 1 || posicao > cont && cont > 1){
    printf("Numero invalido! Entre um numero entre 1 e %d\n\n", cont);
  }
  else if(posicao <= 0 && cont == 1 || posicao > cont && cont == 1){
    printf("Numero invalido! Voce tem somente 1 tarefa registrada.\n\n");
  }
  else if(cont == 0){
    printf("Voce nao possui nenhuma tarefa registrada.\n\n");
  }
  
  int var_alterar;
  int verifica = 0;
  do{
    printf("\nDigite qual campo da tarefa deseja alterar: \n");
    printf("1 - Alterar prioridade\n2 - Alterar categoria\n3 - Alterar descrição\n4 - Alterar estado\n\n");
    scanf("%d", &var_alterar);
    limpa_buffer();

    if(var_alterar < 1 || var_alterar > 5){
      printf("Input invalido. Digite um valor entre 1 e 4.\n");
    }
  } while(var_alterar < 1 || var_alterar > 5);
  
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
    
    for(int x = posicao - 1; x < cont; x++){
      if(x == posicao - 1){
        t[x].prioridade = var_prioridade;
        printf("Prioridade alterada com sucesso!\n\n");
      }
    }
  }
  else if(var_alterar == 2){
    char categoria_[100];
    printf("Entre com a nova categoria: \n");
    scanf("%[^\n]", categoria_);
    limpa_buffer();
    for(int x = posicao - 1; x < cont; x++){
      if(x == posicao - 1){
        strcpy(t[x].categoria , categoria_);
        printf("Categoria alterada com sucesso!\n\n");
      }
    }
  }
  else if (var_alterar == 3){
    char descricao_[300];
    printf("Entre com a nova descricao: \n");
    scanf("%[^\n]", descricao_);
    limpa_buffer();
    for(int x = posicao - 1; x < cont; x++){
      if(x == posicao - 1){
        strcpy(t[x].descricao , descricao_);
        printf("Descricao alterada com sucesso!\n\n");
      }
    }
  }
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
  for(int x = posicao - 1; x < cont; x++){
    if(x == posicao - 1){
      t[x].estado = var_estado;
      printf("Estado alterado com sucesso.\n\n");
      }
    }
  }
}  

//Funcao de alterar tarefas. 

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


//Funcao que le um arquivo binario com as informacoes registradas pelo usuario assim que o programa é iniciado, evitando assim que as informacoes se percam quando o usuario sai e entra novamente no programa. Para isso,
//declaramos a variavel "FILE *arquivo_binario*, que, por meio da funcao fopen, abre o arquivo binario com as informacoes escritas pela funcao "escreve_binario" e realiza a leitura, salvando elas na strucutre da maneira
//como que estavam na utilizacao anterior do programa. O laco while aumenta uma variavel "y", que, na main.c, será recebida pela variavel "cont", que´é o contador de tarefas utilizado em outras funcoes. Por exemplo, caso
//a funcao "le_binario" leia 3 tarefas, o valor do contador (variavel cont) será atualizado para 3, garantindo o funcionamento normal do programa.


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
//Funcao que, ao usuario escolher sair do programa, registra todas as informacoes salvas em um arquivo binario, para que assim, quando o usuario decidir utilizar o programa novamente, suas informacoes estejam salvas.
//Para fazer isso, declaramos a variavel "FILE *arquivo_binario", assim como na funcao anterior, e ela, por meio da funcao fopen, com o mode "wb", escreve todas as informacoes salvas no programa para um arquivo binario,
//que é lido ao iniciar programa pela funcao "le_binario", por fim, antes de parar a execucao da programa, a funcao "fclose" fecha o arquivo, agora salvo com todas as informacoes do usuario.
