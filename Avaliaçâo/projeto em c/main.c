#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct agenda{
  int id;
  char nome[80];
  char profissao[26];
  long telefone;
}Agenda;

// Requisito 1 Liste todos os contatos por nome.
// Requisito 2 Liste os contatos por nome e telefone

int tam(){
  FILE* arq = fopen("agenda.dat", "rb");
  if(arq == NULL){
    printf("Erro ao abrir arquivo!\n");
    exit(1);
  }
  int cont = 0;
  Agenda ag;
  while(fread(&ag,sizeof(Agenda),1,arq)){
    cont++;
  }
  fclose(arq);
  return cont;
}

int verificarID(Agenda* ag, int n, int id){
  int i, check = -1;
  for(i = 0; i < n; i++){
    if(ag[i].id == id){
      check = 1;
    }
  }
  return check;
}


void lerDadosAgenda(Agenda* ag, int n){
  int i;
  for(i = 0; i < n; i++){
    printf("--------------------------------------------\n");
    printf("digias informacoes do contato abaixo %d!\n",i+1);
    printf("--------------------------------------------\n");
    printf("digite id: ");
    scanf("%d",&ag[i].id);
    printf("digite nome: ");
    scanf(" %s",ag[i].nome);
    printf("digite profisao: ");
    scanf(" %s",ag[i].profissao);
    printf("digite telefone: ");
    scanf(" %ld",&ag[i].telefone);
    printf("--------------------------------------------\n");
  }
}

void imprimirPeloNome(Agenda* ag, int n){
  if(tam() > 0){
     printf("--------------------------------------------\n");
    printf("Total de contados\n");
    printf("--------------------------------------------\n");
    int i;
    for(i = 0; i < n; i++){
      printf("nome: %s\n",ag[i].nome);
      printf("--------------------------------------------\n");
    }
  }
}


void imprimirNome_telefone(Agenda* ag, int n){
  printf("--------------------------------------------\n");
  printf("Total de contados\n");
  printf("--------------------------------------------\n");
  int i;
  for(i = 0; i < n; i++){
    printf("nome: %s\n",ag[i].nome);
    printf("telefone: %ld\n",ag[i].telefone);
    printf("--------------------------------------------\n");
  }
  printf("--------------------------------------------\n");
}

void acessa_contato(Agenda* ag, int n, int index){
  if(index < tam() && index >= 0){
    printf("--------------------------------------------\n");
    printf("Informacao do contao\n");
    printf("--------------------------------------------\n");
    printf("id: %d\n",ag[index].id);
    printf("nome: %s\n",ag[index].nome);
    printf("profisao: %s\n",ag[index].profissao);
    printf("telefone: %ld\n",ag[index].telefone);
    printf("--------------------------------------------\n");
  }else{
    printf("Contato nao existe\n");
  }
}

void resertaDados(Agenda* ag, int n){
  FILE* arq = fopen("agenda.dat", "w");
  if(arq == NULL){
    printf("Erro ao abrir arquivo!\n");
    exit(1);
  }

  fwrite(ag, sizeof(Agenda), n, arq);

  fclose(arq);
}

void salvaDados(Agenda* ag, int n){
  FILE* arq = fopen("agenda.dat", "ab");
  if(arq == NULL){
    printf("Erro ao abrir arquivo!\n");
    exit(1);
  }

  fwrite(ag, sizeof(Agenda), n, arq);

  fclose(arq);
}

void imprime_profissao(Agenda* ag, int n, char* profissao){
  printf("--------------------------------------------\n");
  printf("Informacao do contao profissao\n");
  printf("--------------------------------------------\n");
  int i;
  for(i = 0; i < n; i++){
   if(strcmp(ag[i].profissao, profissao) == 0){
    printf("id: %d\n",ag[i].id);
    printf("nome: %s\n",ag[i].nome);
    printf("profisao: %s\n",ag[i].profissao);
    printf("telefone: %ld\n",ag[i].telefone);
   }
  }
}


Agenda* retornaDadosContato(){
  FILE* arq = fopen("agenda.dat", "rb");
  if(arq == NULL){
    printf("Erro ao abrir arquivo!\n");
    exit(1);
  }
  
  Agenda* ag = (Agenda*) malloc(tam() * sizeof(Agenda));
  fread(ag,sizeof(Agenda),tam(),arq);
  
  fclose(arq);
  return ag;
}

void deleta_id(Agenda* ag, int n, int id){
  if(verificarID(ag, n, id)){
    int d = tam() - 1;
    Agenda* aux = (Agenda*) malloc(d*sizeof(Agenda));
    
    int i, cont = 0;
    for(i = 0; i < n; i++){
     if(ag[i].id != id){
       aux[cont].id = ag[i].id;
       strcpy(aux[cont].nome, ag[i].nome);
       strcpy(aux[cont].profissao, ag[i].profissao);
       aux[cont].telefone = ag[i].telefone;
       cont++;
     }
    }
    
    imprimirPeloNome(aux, d);
    resertaDados(aux, d);
  }else{
    printf("Contato nao existe!!");
  }
}

void apagar_contatos(){
  FILE* arq = fopen("agenda.dat", "w");
  Agenda* ag;
  fwrite(ag, sizeof(Agenda),0,arq);
  fclose(arq);
}

void editar_nome(Agenda* ag, int n, int id, char* novoNome){
  if(verificarID(ag, n, id) == 1){
    int i;
    for(i = 0; i < n; i++){
      if(ag[i].id == id){
        strcpy(ag[i].nome, novoNome);
      }
      
    }
    printf("Contato alterando com  sucesso!!");
    resertaDados(ag, tam());
  }else{
    printf("Contato nao existe!!");
  }
}

  void editar_telefone(Agenda* ag, int n, int id, long novoTelefone){
  if(verificarID(ag, n, id) == 1){
    int i;
    for(i = 0; i < n; i++){
      if(ag[i].id == id){
        ag[i].telefone = novoTelefone;
      }
    }
    printf("Contato alterando com  sucesso!!");
    resertaDados(ag, tam());
  }else{
    printf("Contato nao existe!!");
  }
}

void exporte_contato_arquivo(Agenda* ag, int n, int id){
   if(verificarID(ag, n, id) == 1){
    int i;
    for(i = 0; i < n; i++){
      if(ag[i].id == id){
        char nomeAux[30];
        strcpy(nomeAux, ag[i].nome);
        strcat(nomeAux,".dat");
        FILE* arq = fopen(nomeAux,"wb");
        fwrite(&ag[i],sizeof(Agenda),1,arq);
        fclose(arq);
      }
    }
    printf("Contato alterando com  sucesso!!");
  }else{
    printf("Contato nao existe!!");
  }
}

void imprimir_inicio_letra(Agenda* ag, int n, char letra){
  int i;
    for(i = 0; i < n; i++){
      if(ag[i].nome[0] == letra){
        imprimirNome_telefone(&ag[i], 1);
      }
    }
}

int main(void) {
  Agenda* ag = retornaDadosContato();
  
  // Requisito 1 Liste todos os contatos por nome.
  // imprimirPeloNome(ag, tam());
  
  // Requisito 2 Liste os contatos por nome e telefone
  // imprimirNome_telefone(ag, tam());

  /*
  Requisito 3 Apresente todos os contatos que come-
  cem com uma letra específica. Nesse caso, apresente
  o nome e o telefone.
*/
  imprimir_inicio_letra(ag, tam(), 'a');

  
 //   Requisito 4 Acesse um contato através de um indice;
  // acessa_contato(ag, tam(), 0);
  
  // Requisito 5 Liste os contatos em função de sua profissão.
  //imprime_profissao(ag, tam(), "2");
  // Requisitos de Remoção
  // deleta_id(ag, tam(), 1);


  // Requisito 7 Apague todos os contatos;
  // apagar_contatos();

  // Requisito 8 Edite o nome de um contato, passando
  // como parâmetro o Id desse contato e da nova string
  // que deve substituir o campo nome;
  // editar_nome(ag, tam(), 0, "caralho2025");

//   Requisito 9 Edite o telefone de um contato, pas-
// sando como parâmetro o Id desse contato e um novo
// valor para o telefone;
// editar_telefone(ag, tam(), 1, 12313);

//   Requisito 10 Exporte um contato a partir de seu
// ID para um novo arquivo com o nome do contato.
  // exporte_contato_arquivo(ag, tam(), 1);
  

  // criar dados
  // Agenda* ag = (Agenda*) malloc(2*sizeof(Agenda));
  // lerDadosAgenda(ag,2);
  // salvaDados(ag,2);

  
  return 0;
}