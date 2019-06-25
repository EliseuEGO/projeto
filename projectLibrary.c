#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <locale.h>


#define NP 31
#define NG 61
#define NGG 10000
#define ANSI_COLOR_RED      "\x1b[31m"

/*------------------inicio-------------------------*/

#define TAMA 30
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void fundo_tela(){
    system("Color 06");
}






/*----------------------ESTRUTURAS-------------*/

//LIVROS
typedef struct livros{

  int codlivro;
  char nomelivro[NG];
  char nomeautor[NP];
  int exem_emprestimo;
  char arealivro[NG];
}LIVROS;

//ALUNOS
typedef struct alunos{
  int matricula;
  char nomealuno[NP];
  int cpf;
  int qnt; //quantidade de emprestimos por aluno

}ALUNOS;

//EMPRESTIMOS
typedef struct emprestimo{
  int protocolo;
  int codlivro;
  int matricula;
  char nomelivro[NG];
  int datadia;
  int datames;
  int dataano;

}EMPRESTIMO;

/*----------OUTRAS FUN��ES---------------------*/
void decrementar_livro(int d){
	FILE *fp;
	FILE *fp2;
    LIVROS livro;
    LIVROS temp;
    fp2 = fopen("arquivos\\temp.txt","ab");
    fp = fopen("arquivos\\livros.txt","rb");

    while (fread(&livro, sizeof(LIVROS), 1,fp)){
                if(d==livro.codlivro){
                    livro.exem_emprestimo = livro.exem_emprestimo -1;
                    fwrite(&livro, sizeof(LIVROS), 1,fp2);

                }else{
                fwrite(&livro, sizeof(LIVROS), 1,fp2);
                }
            }
            fclose(fp);
            fclose(fp2);
            remove("arquivos\\livros.txt");
            rename("arquivos\\temp.txt","arquivos\\livros.txt");

}

void incrementar(int *i){
printf("cod em incrementar %d\n", *i);


	FILE *fp;
	FILE *fp2;
    LIVROS livro;
    LIVROS temp;
    fp2 = fopen("arquivos\\temp.txt","ab");
    fp = fopen("arquivos\\livros.txt","rb");

    while (fread(&livro, sizeof(LIVROS), 1,fp)){
                if(*i==livro.codlivro){
                    livro.exem_emprestimo = livro.exem_emprestimo +1;
                    printf("exemplares pra empres em incrementar %d",livro.exem_emprestimo);
                    fwrite(&livro, sizeof(LIVROS), 1,fp2);

                }else{
                fwrite(&livro, sizeof(LIVROS), 1,fp2);
                }
    }
    fclose(fp);
    fclose(fp2);
    remove("arquivos\\livros.txt");
    rename("arquivos\\temp.txt","arquivos\\livros.txt");


}

int um_livro(int m,int u){

    FILE *fp;

    EMPRESTIMO emp;


    fp = fopen("arquivos\\emprestimos.txt","rb");

        while(fread(&emp, sizeof(EMPRESTIMO), 1,fp)){
            if(m==emp.matricula&&u==emp.codlivro){
                printf("O aluno ja pegou um livro desse t�tulo\n");
                return 0;
            }else{
            return 1;
            }
        }
}

void emp_qnt(int q){
    FILE *fp;
	FILE *fp2;
    ALUNOS aluno;
    ALUNOS temp;
    fp2 = fopen("arquivos\\temp.txt","ab");
    fp = fopen("arquivos\\alunos.txt","rb");

    while (fread(&aluno, sizeof(ALUNOS), 1,fp)){
                if(q==aluno.matricula){
                    aluno.qnt=aluno.qnt+1;
                    printf("Quantidade de empr�stimos %d\n",aluno.qnt);
                    if(aluno.qnt>3){

                        puts("O aluno atingiu o m�ximo de empr�stimos permitido");
                        break;
                    }
                    fwrite(&aluno, sizeof(ALUNOS), 1,fp2);

                }else{
                fwrite(&aluno, sizeof(ALUNOS), 1,fp2);
                }
    }
    fclose(fp);
    fclose(fp2);
    remove("arquivos\\alunos.txt");
    rename("arquivos\\temp.txt","arquivos\\alunos.txt");

}

/* ---------------MENU-------------------- */


//---------------ACERVO-------------------
//Cadastrar livro
void cadastrolivro(void){


    FILE *fp;
    LIVROS livro;
    if ((fp = fopen("arquivos\\livros.txt", "ab")) == NULL){
        fprintf(stderr, "Banco de dados n�o existe.\n");
        exit(EXIT_FAILURE);
    }
      //codigo do livro
      srand(time(NULL));
      livro.codlivro = 1+(rand()% NGG);//gerar um numero aleatorio entre 1 e 10000

      puts("Nome do Livro");
      setbuf(stdin, NULL);
      fgets(livro.nomelivro,NG,stdin);
      puts("Nome do autor");
      setbuf(stdin,NULL);
      fgets(livro.nomeautor,NP,stdin);
      /*puts("Numero de exemplares");
      scanf("%d",&livro.exem_total);*/
      puts("Exemplares para emprestimo");
      scanf("%d",&livro.exem_emprestimo);
      puts("Area de conhecimento");
      setbuf(stdin,NULL);
      fgets(livro.arealivro,NG,stdin);
      puts("Livro cadastrado");

    fwrite(&livro, sizeof(LIVROS), 1, fp);
    fclose(fp);

}

//Editar livro
void editarlivro(void){
    int id, op, n;
    char novonome[NG];

    puts("Insira o c�digo do livro que deseja alterar os dados");
    scanf("%d",&id);
    putchar('\n');

    FILE *fp;
    FILE *fp2;
    LIVROS livro;
    LIVROS temp;
    fp2 = fopen("arquivos\\temp.txt","ab");
    fp = fopen("arquivos\\livros.txt","rb");

    while(fread(&livro, sizeof(LIVROS), 1,fp)){
        if(livro.codlivro==id){
            puts("1- Nome do livro");
            puts("2- Autor do livro");
            puts("3- Exemplares disponiveis para empr�stimo");
            puts("4- Area de conhecimento");
            puts("Insira o digito do dado deseja alterar?");
            scanf("%d",&op);
            switch(op){
                case 1:{
                    puts("Insira o novo nome do livro");
                    setbuf(stdin, NULL);
                    fgets(novonome,NG,stdin);
                    strcpy(livro.nomelivro,novonome);

                    break;
                }
                case 2:{
                    puts("Insira o novo nome do autor");
                    setbuf(stdin, NULL);
                    fgets(novonome,NG,stdin);
                    strcpy(livro.nomeautor,novonome);
                    break;
                }

                case 3:{
                    puts("Insira nova quantidade de exemplares para emprestimo");
                    scanf("%d",&n);
                    livro.exem_emprestimo=n;
                    break;
                }
                case 4:{
                    puts("Insira a area de conhecimento");
                    setbuf(stdin, NULL);
                    fgets(novonome,NG,stdin);
                    strcpy(livro.arealivro,novonome);
                    break;
                }
                default:puts("Nenhuma op��o correspondente"); break;
            }
            fwrite(&livro, sizeof(LIVROS),1,fp2);
        }else{
            fwrite(&livro, sizeof(LIVROS),1,fp2);
        }
    }
    puts("Altera�oes conclu�das");
    fclose(fp);
    fclose(fp2);
    remove("arquivos\\livros.txt");
    rename("arquivos\\temp.txt","arquivos\\livros.txt");
}

//REMOVER LIVRO
void remover_livro(void){
    int id;
    puts("Insira o c�digo do livro que deseja remover");
    scanf("%d",&id);
    putchar('\n');

    FILE *fp;
    FILE *fp2;
    LIVROS livro;
    LIVROS temp;
    fp2 = fopen("arquivos\\temp.txt","ab");
    fp = fopen("arquivos\\livros.txt","rb");

    while(fread(&livro, sizeof(LIVROS), 1,fp)){
        if(livro.codlivro!=id){
            fwrite(&livro, sizeof(LIVROS),1,fp2);
        }
    }
    puts("Livro Removido");
    fclose(fp);
    fclose(fp2);
    remove("arquivos\\livros.txt");
    rename("arquivos\\temp.txt","arquivos\\livros.txt");
}

//listar livros cadastrados
void listar_livros(void){
  putchar('\n');
  puts("Livros cadastrados:");
  FILE *fp;
  LIVROS livro;
    fp = fopen("arquivos\\livros.txt", "rb");
    while (fread(&livro, sizeof(LIVROS), 1,fp)){

        printf("COD.:%d - %s\n",livro.codlivro, livro.nomelivro);
    }
    fclose(fp);

}
//listar livro especifico
void listar_um_livro(void){
    int id;
    puts("Insira o c�digo do livro");
    scanf("%d",&id);
    FILE *fp;
    LIVROS livro;
    fp = fopen("arquivos\\livros.txt","rb");
    //fread(&livro, sizeof(LIVROS), 1,fp);
    while(fread(&livro, sizeof(LIVROS), 1,fp)){
        if(livro.codlivro==id){
            printf("Autor: %s\n",livro.nomeautor);
            printf("Livro: %s\n",livro.nomelivro);
           // printf("%d Exemplares\n\n",livro.exem_total);
            printf("Exemplares disponiveis para emprestimo: %d\n\n",livro.exem_emprestimo);
            printf("Area de conhecimento: %s\n",livro.arealivro);
        }
    }
fclose(fp);
}



/*--------------------ALUNO-----------------*/

//Cadastrar aluno
void cadastroaluno(void){
    FILE *fp;
    ALUNOS aluno;
    if ((fp = fopen("arquivos\\alunos.txt", "ab")) == NULL){
        fprintf(stderr, "Banco de dados n�o existe.\n");
        exit(EXIT_FAILURE);
    }
      //matricula do aluno
      srand(time(NULL));
      aluno.matricula = 1+(rand()% NGG);//gerar um numero aleatorio entre 1 e 10000
      printf("Matricula: %d\n",aluno.matricula);
      puts("Nome do aluno");
      setbuf(stdin, NULL);
      fgets(aluno.nomealuno,NG,stdin);
      puts("CPF do aluno (apenas n�meros)");
      scanf("%d",&aluno.cpf);
      aluno.qnt = 0;
      puts("Matricula completa");

    fwrite(&aluno, sizeof(ALUNOS), 1, fp);
    fclose(fp);

}
//remover aluno
void remover_aluno(void){
    int id;
    puts("Insira a matricula do aluno que deseja remover");
    scanf("%d",&id);
    putchar('\n');

    FILE *fp;
    FILE *fp2;
    ALUNOS aluno;
    ALUNOS temp;
    fp2 = fopen("arquivos\\temp.txt","ab");
    fp = fopen("arquivos\\alunos.txt","rb");

    while(fread(&aluno, sizeof(ALUNOS), 1,fp)){
        if(aluno.matricula!=id){
            fwrite(&aluno, sizeof(ALUNOS),1,fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    remove("arquivos\\alunos.txt");
    rename("arquivos\\temp.txt","arquivos\\alunos.txt");
}

//editar aluno
void editaraluno(void){
    int id, op, n;
    char novonome[NG];

    puts("Insira a matricula do aluno que deseja alterar os dados");
    scanf("%d",&id);
    putchar('\n');

    FILE *fp;
    FILE *fp2;
    ALUNOS aluno;
    ALUNOS temp;
    fp2 = fopen("arquivos\\temp.txt","ab");
    fp = fopen("arquivos\\alunos.txt","rb");

    while(fread(&aluno, sizeof(ALUNOS), 1,fp)){
        if(aluno.matricula==id){
            puts("1- Nome do aluno");
            puts("2- CPF do aluno");
            puts("Insira o digito do dado deseja alterar ");
            scanf("%d",&op);
            switch(op){
                case 1:{
                    puts("Insira o novo nome do aluno");
                    setbuf(stdin, NULL);
                    fgets(novonome,NG,stdin);
                    strcpy(aluno.nomealuno,novonome);

                    break;
                }
                case 2:{
                    puts("Insira o novo CPF do aluno");
                    scanf("%d",&aluno.cpf);
                    break;
                }

                default: break;
            }
            fwrite(&aluno, sizeof(ALUNOS),1,fp2);
        }else{
            fwrite(&aluno, sizeof(ALUNOS),1,fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    remove("arquivos\\alunos.txt");
    rename("arquivos\\temp.txt","arquivos\\alunos.txt");
}
//listar alunos cadastrados
void listar_alunos(void){
  putchar('\n');
  puts("Os alunos cadastrados s�o:");
  FILE *fp;
  ALUNOS aluno;
    fp = fopen("arquivos\\alunos.txt", "rb");
    while (fread(&aluno, sizeof(ALUNOS), 1,fp)){

        printf("Matricula:%d - %s - CPF: %d\n",aluno.matricula, aluno.nomealuno,aluno.cpf);
    }
    fclose(fp);

}


/*-----------------EMPRESTIMO--------------*/
//novo empr�stimo;
void novo_emprestimo(void){

    FILE *fp;

    EMPRESTIMO emp;

    if ((fp = fopen("arquivos\\emprestimos.txt", "ab")) == NULL){
        fprintf(stderr, "Banco de dados n�o existe.\n");
        exit(EXIT_FAILURE);
    }
      //codigo do livro
      srand(time(NULL));
      emp.protocolo = 1+(rand()% NGG);//gerar um numero de protocolo
        printf("Protocolo do emprestimo �: %d\n",emp.protocolo);

      puts("C�digo do Livro");
      scanf("%d",&emp.codlivro);
        //Retirar o livro do sistema
        decrementar_livro(emp.codlivro);
      puts("Nome do Livro");
      setbuf(stdin,NULL);
      fgets(emp.nomelivro,NP,stdin);
      puts("Matricula do aluno");
      scanf("%d",&emp.matricula);
        //verificar se o aluno ja pegou esse livro
        /*if(um_livro(emp.matricula, emp.codlivro)==0){
            goto fecha;
        }*/
        emp_qnt(emp.matricula);

            //data
            //C�digo de captura de data retirado da internet. Manipula��o feita por aluno.
              struct tm *data_hora_atual;
              time_t segundos;
              time(&segundos);
              data_hora_atual = localtime(&segundos);
              //data atual
              int dia_atual = data_hora_atual->tm_mday, mes_atual = data_hora_atual->tm_mon+1, ano_atual = data_hora_atual->tm_year+1900;

              int novo_dia, novo_mes;
              novo_dia = dia_atual +10;
              if(novo_dia>30){
                novo_mes=mes_atual + 1;
                novo_dia=novo_dia - 30;
                emp.datadia=novo_dia;
                emp.datames=novo_mes;
                emp.dataano=ano_atual;
                printf("Data de devolu��o �:  %d/%d/%d\n\n",novo_dia,novo_mes,ano_atual);
              }else{
                emp.datadia=novo_dia;
                emp.datames=mes_atual;
                emp.dataano=ano_atual;
              printf("Data de devolu��o �:  %d/%d/%d\n\n",novo_dia,mes_atual,ano_atual);
              }


    fwrite(&emp, sizeof(EMPRESTIMO), 1, fp);
    //fecha:
    fclose(fp);
}

//confirmar devolu��o
void confirmar_devolucao(void){
    int id;
    puts("Insira o protocolo do empr�stimo:");
    scanf("%d",&id);
    putchar('\n');

    FILE *fp;
    FILE *fp2;
    EMPRESTIMO emp;
    EMPRESTIMO temp;
    fp2 = fopen("arquivos\\temp.txt","ab");
    fp = fopen("arquivos\\emprestimos.txt","rb");




    while(fread(&emp, sizeof(EMPRESTIMO), 1,fp)){
        if(emp.protocolo!=id){
            fwrite(&emp, sizeof(EMPRESTIMO),1,fp2);
        }/*else{
            printf("codigo em confifirmar devo %d\n",emp.codlivro);
        incrementar(&emp.codlivro);
        }*/
    }
    puts("Empr�stimo finalizado");
    fclose(fp);
    fclose(fp2);
    remove("arquivos\\emprestimos.txt");
    rename("arquivos\\temp.txt","arquivos\\emprestimos.txt");
}

//cancelar empr�stimo
void cancelar_emprestimo(void){
    int id;
    puts("Insira o protocolo do empr�stimo:");
    scanf("%d",&id);
    putchar('\n');

    FILE *fp;
    FILE *fp2;
    EMPRESTIMO emp;
    EMPRESTIMO temp;
    fp2 = fopen("arquivos\\temp.txt","ab");
    fp = fopen("arquivos\\emprestimos.txt","rb");

        /*while(fread(&emp, sizeof(EMPRESTIMO), 1,fp)){
            if(emp.protocolo==id){
                incrementar(&emp.codlivro);
            }

        }rewind(fp);*/


    while(fread(&emp, sizeof(EMPRESTIMO), 1,fp)){
        if(emp.protocolo!=id){
            fwrite(&emp, sizeof(EMPRESTIMO),1,fp2);
        }
    }
    puts("Empr�stimo cancelado");
    fclose(fp);
    fclose(fp2);
    remove("arquivos\\emprestimos.txt");
    rename("arquivos\\temp.txt","arquivos\\emprestimos.txt");
}

//LISTAR EMPR�STIMOS
//listar todos empr�stimos
void listar_emprestimos(void){
  putchar('\n');
  puts("Lista de emprestimos:");
  FILE *fp;
  EMPRESTIMO emp;
    fp = fopen("arquivos\\emprestimos.txt", "rb");
    while (fread(&emp, sizeof(EMPRESTIMO), 1,fp)){

        printf("Protocolo: %d \nMatricula do aluno: %d \nLivro: %s\n",emp.protocolo, emp.matricula, emp.nomelivro);
    }
    fclose(fp);

}

//listar por aluno espec�fico
void listar_emp_aluno(void){
    puts("Pesquisar empr�stimo por aluno");
    int id;
    puts("Insira a matricula do aluno");
    scanf("%d",&id);
    FILE *fp;
    EMPRESTIMO emp;
    fp = fopen("arquivos\\emprestimos.txt","rb");

    while(fread(&emp, sizeof(EMPRESTIMO), 1,fp)){
        if(emp.matricula==id){
            printf("Protocolo %d\n",emp.protocolo);
            printf("Livro: %s\n",emp.nomelivro);
            printf("Data de devolu��o: %d/%d/%d\n",emp.datadia,emp.datames,emp.dataano);

        }
    }
fclose(fp);
}

//listar por livro espec�fico
void listar_emp_livro(void){
    puts("Pesquisar emprestimo por livro");
    int id;
    puts("Insira o codigo do livro");
    scanf("%d",&id);
    FILE *fp;
    EMPRESTIMO emp;
    fp = fopen("arquivos\\emprestimos.txt","rb");

    while(fread(&emp, sizeof(EMPRESTIMO), 1,fp)){
        if(emp.codlivro==id){
            printf("Protocolo %d\n",emp.protocolo);
            printf("Matricula do aluno: %s\n",emp.matricula);
            printf("Data de devolu��o: %d/%d/%d\n",emp.datadia,emp.datames,emp.dataano);

        }
    }
fclose(fp);
}


      /*Um aluno poder� no m�ximo realizar 2 empr�stimos de livros diferentes simultaneamente.
       Ao se emprestar o livro, a quantidade de exemplares dispon�veis para empr�stimo dever� ser decrementada,
        assim como ser incrementada ap�s a devolu��o do exemplar.
        Um aluno s� poder� realizar o empr�stimo de um exemplar por t�tulo.
      */



/*--------------------OP��ES--------------------*/

void menuprincipal(){
  int op,op2,op3;

  do{
system("cls");
        fundo_tela();

       gotoxy(TAMA,6); printf(" ***           ***  ***********  ***********    *********** ");
       gotoxy(TAMA,7); printf(" ***           ***  ***********  ***       ***  ***       *** ");
       gotoxy(TAMA,8); printf(" ***           ***  ****         ***        *** ***        *** ");
       gotoxy(TAMA,9); printf(" ***           ***  ****         ***        *** ***        *** ");
       gotoxy(TAMA,10);printf(" ***           ***  *******      ***       ***  ***      *** ");
       gotoxy(TAMA,11);printf(" ***           ***  *******      **********     ***********   ");
       gotoxy(TAMA,12);printf(" ***           ***  *******      ***            ***       ***  ");
       gotoxy(TAMA,13);printf(" ****         ****  ****         ***            ***         *** ");
       gotoxy(TAMA,14);printf("  ****       ****   ****         ***            ***         *** ");
       gotoxy(TAMA,15);printf("   *************    ***********  ***            ***        ***   ");
       gotoxy(TAMA,16);printf("     *********      ***********  ***            ************    ");


       gotoxy(33,17);printf("_________________________________________________________");

        //gotoxy(54,18); puts("BIBLIOTECA");
        gotoxy(53,18); puts("MENU PRINCIPAL");
        gotoxy(45,20); puts("1-Acervo");
        gotoxy(60,20); puts("2-Alunos");
        gotoxy(45,21); puts("3-Emprestimos");
        gotoxy(60,21); puts("4-Sair");

        putchar('\n');
       printf("Digite a opcao desejada: ");




    scanf("%d",&op);
    switch(op){
    case 1:{
        system("cls");
      puts("ACERVO");
      puts("1- Cadastrar livro");//
      puts("2- Editar livro");
      puts("3- Remover livro");
      puts("4- Listar livros cadastrados");
      puts("5- Voltar ao menu principal");

      scanf("%d",&op2);

      switch(op2){
        case 1:{
          cadastrolivro();
          system("pause");
          break;
        }
        case 2:{
            editarlivro();
            system("pause");
          break;
        }
        case 3:{
            remover_livro();
            system("pause");
          break;
        }
        case 4:{
            puts("Digite 1 para listar todos os livros");
            puts("Digite 2 para listar dados de apenas um livro");
            scanf("%d",&op3);
            switch(op3){
                case 1: listar_livros();
                system("pause");
                break;
                case 2: listar_um_livro();
                system("pause");
                break;
            }
          break;
        }
        case 5:{
          break;
        }
      }

      break;
    }
    case 2:{
        system("cls");
      puts("ALUNOS");
      puts("1- Cadastrar aluno");
      puts("2- Editar aluno");
      puts("3- Remover aluno");
      puts("4- Listar alunos cadastrados");
      puts("5- Voltar ao menu principal");
      scanf("%d",&op2);

      switch(op2){
        case 1:{
            cadastroaluno();
            system("pause");
          break;
        }
        case 2:{
            editaraluno();
            system("pause");
          break;
        }
        case 3:{
            remover_aluno();
            system("pause");
          break;
        }
        case 4:{
            listar_alunos();
            system("pause");
          break;
        }
        case 5:{
          break;
        }
      }
      break;
    }
    case 3:{
        system("cls");
      puts("EMPRESTIMOS");
      puts("1- Novo emprestimo");//
      puts("2- Confirmar devolu��o");
      puts("3- Cancelar emprestimo");//remover
      puts("4- Listar empr�stimos");
      puts("5- Voltar ao menu principal");
      scanf("%d",&op2);

      switch(op2){
        case 1:{
            novo_emprestimo();
            system("pause");
          break;
        }
        case 2:{
            confirmar_devolucao();
            system("pause");
          break;
        }
        case 3:{
            cancelar_emprestimo();
            system("pause");
          break;
        }
        case 4:{
            system("cls");
          puts("LISTAR EMPRESTIMOS");
          puts("1- Listar todos empr�stimos");
          puts("2- Pesquisar empr�stimo por livro");
          puts("3- Pesquisar empr�stimo por aluno");
          printf("Insira a op��o desejada:");
          scanf("%d",&op3);
          switch(op3){
            case 1:{
              listar_emprestimos();
              system("pause");
              break;
            }
            case 2:{
              listar_emp_livro();
              system("pause");
              break;
            }
            case 3:{
              listar_emp_aluno();
              system("pause");
              break;
            }
          }
          break;
        }
        case 5:{
          break;
        }
      }
      break;
    }
    case 4:{
      puts("Fim do programa");
      break;
    }
  }
  }while(op!=4);
}

int main(void){

    //criar a pasta de arquivos
    if(!CreateDirectory("arquivos", NULL)) {
            if(GetLastError()==183){
                printf("\n");
            }else{
        fprintf(stderr, "ERRO: %d\n", GetLastError());
            }
    }
setlocale(LC_ALL, "Portuguese");

menuprincipal();


return 0;

}
