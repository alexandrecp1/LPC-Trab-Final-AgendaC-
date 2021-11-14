//Dependencias para inicialização do trabalho

#include <stdio.h>      //Entradas padronizadas, utilizadas para auxilio de entrada e saida de dados.
#include <string.h>     //Cocatenação de strings
#include <stdlib.h>     //Funções basicas de C (padrão de linguagem)
#include <conio.h>      //Entrada e saida de dados
#include <ctype.h>      //Manipulação de Caracteres.
#include <locale.h>     //Utilização ascentuação
#define TAM 100         
//Recebe valor (100)



//Funções iniciais a tabela.

int main (){
    int var;
    system("title AGENDA");
    printf("\n\n\t\tAgenda em C\n\n");
    printf("\tTrabalho de Logica p/ computacao\n");
    printf("\tUtilize os numeros para selecionar o que deseja.\n");
    printf("\tPressione qualquer tecla para continuar.\n\tPressione espaco para sair do programa.\n\t");
    var=getch();
    if(var == 32){ exit(0);}
menu();
system("pause");
}



//Estrutura inicial da Agenda

typedef struct Agenda{
        char Nome[50];
        char Telefone[17];
        char Email[80];
}contatos;



//Funções da Agenda e definições (Crud e bonus)

void Incluir(void);    //Inclusão
char AddMais();        //Acrescentar Mais Contatos
void Formata(void);    //Apagar Contatos
void Organizar(void);  //Ordenar
void Pesquisar(void);  //Pesquisa
void Listar(void);     //Mostrar dados



//Variaveis Globais

static int quantidade = 0;      //Define Quantidade
contatos max[TAM];              //Maximo de contatos
FILE *arq;                      //Arquivo que salva dados



//Inclusão de contatos

void Incluir(void){
     int cont = 0;
     int retorno;
     char op = 's';

    //Abre o arquivo ja existente, caso não exista cria um novo e/ou informa a não possiblidade de acrescentar a mesma.
     arq = fopen("agenda.txt", "a");
     if (arq == NULL){
        printf ("Erro!\nO arquivo não pode ser aberto/encontrado\n");
        getch();
        exit(1);
     }

     while ((cont < TAM) && (op == 's')){
           printf (" Digite o Nome: ");
           gets(max[cont].Nome);
           printf (" Digite o Telefone: ");
           gets(max[cont].Telefone);
           printf (" Digite o E-mail: ");
           gets(max[cont].Email);

           retorno = fwrite (&max[cont], sizeof(contatos) ,1,arq);
           if (retorno == 1) {
               printf("\n Contato cadastrado com sucesso.");
            }
           cont++;
           op = AddMais();
           quantidade++;
     }
     fclose (arq);
}



//Função para definir se quer acrescentar mais contatos a Agenda, sendo a mesma um "laço" de repetição até o limite citado em "MAX"

char AddMais() {
   char op;
   do {
      printf("\n Deseja inserir novos dados?" );
      printf("\n [S] Para sim | [N] Para nao" );
      op = getch();
      printf("\n" );
   } while (op != 's' && op != 'n');
   return op;
}



//Exclusão de dados (Formata a Agenda)

void Formata() {
    arq = fopen("agenda.txt","w+"); 
    printf("\n\tAgenda formatada com sucesso.\n ");
    fclose(arq);
    getch();
}



//Organiza em ordem alfabetica a Agenda

void Organizar(void){
     contatos vet;
     int aux, i, j, k, retorno;

     char *str, *str2, *straux;
     aux = quantidade;
     for (i = 0 ; i < aux ; i++){
         str = max[i].Nome;
         for (j = i+1 ; j < aux ; j++){
             str2 = max[j].Nome;
             if ( strcmp ( str, str2 ) > 0 ){
                 vet = max[i];
                 max[i] = max[j];
                 max[j] = vet;
             }
         }
     }

     //Apaga o arquivo agenda anterior e cria um novo com a ordenação feita de forma alfabetica

     remove("agenda.txt");
     arq = fopen("agenda.txt", "w+");
     if (arq == NULL){
        printf (" ERRO!\n ");
        getch();
        exit(1);
     }

     for (k = 0 ; k < aux ; k++){
           retorno = fwrite (&max[k], sizeof(contatos) ,1,arq);
           if (retorno != 1) {
               printf("\n ERRO! ");
           }
     }

     fclose(arq);
     printf("\n Lista Ordenada!\n ");
     getch();
}



//Pesquisa por nome

void Pesquisar(void){
     int i=0, retorno=1, cont=0;//
     char Nome[50],op;

    //Abre o arquivo salvo com os contatos da Agenda
     arq = fopen("agenda.txt", "r");
     if (arq == NULL){
         printf (" Erro!\nO arquivo não pode ser aberto/encontrado \n");
         getch();
         exit(1);
     }

     //Imprime o nome e retorna o que foi pedido
     printf (" Digite o Nome (Escreva conforme cadastrado): ");
     gets(Nome);
     retorno = fread(&max[i], sizeof(contatos), 1, arq);
     while (retorno == 1){
         if (strcmp(Nome, max[i].Nome) == 0 ){
            printf("\n Nome....: %s",max[i].Nome);
            printf("\n Telefone....: %s",max[i].Telefone);
            printf("\n E-mail..: %s\n ",max[i].Email);
            cont++;
         }
     i++;
     
     retorno = fread(&max[i], sizeof(contatos), 1, arq);
     }
     if(cont == 0){
        printf("Nao ha contatos com este Nome!\n ");
     }
     getch();
     fclose(arq);
}



//Listar contatos cadastrados

void Listar(void){
    int i = 0, retorno;

    //Abre o arquivo com os usuarios cadastrados
    arq = fopen("agenda.txt", "r");
    if (arq == NULL){
       printf ("Erro!\nO arquivo não pode ser aberto/encontrado \n");
       getch();
       exit(1);
    }

    retorno = fread(&max[i], sizeof(contatos), 1, arq);
    while (retorno == 1){ 
      printf("\n Nome....: %s",max[i].Nome);
      printf("\n Telefone....: %s",max[i].Telefone);
      printf("\n E-mail..: %s\n",max[i].Email);
      i++;
      retorno = fread(&max[i], sizeof(contatos), 1, arq);
    }
    printf(" \n\n %d Contatos salvos!\n ", i);
    getch();
    fclose(arq);
}

//Menu de interações
void menu(void){
    char op;
    do{
        system("cls");
        printf("\n\n\t\tAGENDA EM LINGUAGUEM C\n");
        printf("\n 1. Incluir\n 2. Listar\n 3. Organizar Alfabeticamente\n 4. Pesquisar por Nome\n");
        printf(" 5. Formatar lista\n 6. Voltar\n\n");
        op = getch();
        switch(op){
            case '1':
                Incluir();
                break;
            case '2':
                Listar();
                break;
            case '3':
                Organizar();
                break;
            case '4':
                Pesquisar();
                break;
            case '5':
                Formata();
                break;
            case '6':
                system("cls");
                main();
                break;
            default:
                printf("\a Digite uma opção valida\n");
                getch();
        }
    }
    while (op);
}

//Utilizei CamelCase para identação de arquivos e cls para uma limpeza de console e melhor identação do código.