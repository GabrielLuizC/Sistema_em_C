#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
void cadastroItem();
void listarEstoque();
void editarItem();
void valorEstoque();
void quantidadeEstoque();
void relatorio();
void itensCadastrados();

struct cadastrar{
	char nome[50];
	float valor;
	float quantidade;
	float vtotal;
};

struct cadastrar cadastro;

main(){
	menu();
    return 0;
}

void menu(){
    int escolha;
    do{
    	printf("\n=-=-= Sistema =-=-= \n");
	    printf("1 - Cadastrar Item \n");
	    printf("2 - Listar Estoque \n");
	    printf("3 - Editar Item \n");
	    printf("4 - Excluir Item \n");
	    printf("5 - Relatorio \n");
	    printf("6 - Venda \n");
	    printf("7 - Sair \n\n");
	    printf("Escolha uma das opcoes: ");
	    
	    scanf("%d", &escolha);   
	    
	        switch(escolha){
	    case 1:
			cadastroItem();
	        break;
	    case 2:
			listarEstoque();
		    break;
		case 3:
			editarItem();
			break;
		case 5:
			relatorio();
			break;
	    case 7:
			printf("\nSaindo ...");
		    break;
	    default:
	    	printf("ERROR");
		}	
	}while(escolha != 7);
}

void cadastroItem(){
	int recebe;
	system("cls");
	
	fflush(stdin);
	
	printf("=-=-=-=-= Cadastro de Itens =-=-=-=-=\n");		
    printf("Digite o Nome: ");
    fgets(cadastro.nome, 50, stdin);
    
    printf("\nDigite a Quantidade: ");
    scanf("%f", &cadastro.quantidade);
    
    printf("\nDigite o Valor Unitario do Produto: ");
    scanf("%f", &cadastro.valor);
    
    system("cls");
    
    printf("%s%d \nR$ %.2f", cadastro.nome, cadastro.quantidade, cadastro.valor);
    
    FILE *arq;
    
    arq = fopen("Estoque.txt", "a");
    
    if(arq == NULL){
    	printf("\nArquivo Nao Encontrado");
	}
	
	system("cls");
	
	fprintf(arq, "Item: %sQuantidade: %.1f \nValor: R$ %.2f\n =-=-=-=-=-=-=-=-=-=-=-=-=\n", cadastro.nome, cadastro.quantidade, cadastro.valor);
	
	fclose(arq);
	
	printf("Item Cadastrado Com Sucesso!!\n\n");
	cadastro.vtotal = cadastro.valor * cadastro.quantidade;
	valorEstoque();
	quantidadeEstoque();
	itensCadastrados();
	printf("Digite 1 Para Continuar!!\n");
	scanf(" ");
	system("cls");
	fflush(stdin);
}
		

void listarEstoque(){
		
	char listar[255];
	
	FILE *arq;
	    
    arq = fopen("Estoque.txt", "r");
    
    if(arq == NULL){
    	printf("\nArquivo Nao Encontrado");
	}else{
		printf("\nArquivo Encontrado\n\n");
	}
	
	system("cls");
	
	while(fgets(listar, 255, arq) != NULL) printf("%s", listar);
	
	printf("Digite 1 Para Continuar!!\n");
	scanf(" ");
	
	fflush(stdin);
	system("cls");
	fclose(arq);
}

void editarItem(){
		
	char listar[255];
	char aux[255];
	int linha;
	int l = 1;
	
	FILE *arq;
	    
    arq = fopen("Estoque.txt", "r");
    
    while(fgets(listar, 255, arq) != NULL){
		printf("Linha %d - %s", l++, listar);
	}
    
    printf("Qual Linha Desenha Editar?? ");
	scanf("%d", &linha);
    
	fgets(aux, linha+1, arq);
	printf("TESTE: %s", aux);
	
	fclose(arq);
}

void valorEstoque(){
	float total = cadastro.vtotal;
	float aux;
	char listar[255];
	
	FILE *vtotal;
	
	vtotal = fopen("Valor Estoque.txt", "r");
	
	while(fgets(listar, 255, vtotal) != NULL);
	
	fclose(vtotal);
	
	vtotal = fopen("Valor Estoque.txt", "w");
	
	aux = atof(listar);	
	aux = aux + total;
	
	fprintf(vtotal, "%.2f", aux);
	
	fclose(vtotal);
	
}

void quantidadeEstoque(){
	float total = cadastro.quantidade;
	float aux;
	char listar[255];
	
	FILE *qtotal;
	
	qtotal = fopen("Quantidade Estoque.txt", "r");
	
	while(fgets(listar, 255, qtotal) != NULL);
	
	fclose(qtotal);
	
	qtotal = fopen("Quantidade Estoque.txt", "w");
	
	aux = atof(listar);	
	aux = aux + total;
	
	fprintf(qtotal, "%.2f", aux);
	
	fclose(qtotal);
}

void itensCadastrados(){
	char item[50];
	
	item[50] = cadastro.nome[50];
	
	FILE *icadastro;
	printf("%s", item);
	icadastro = fopen("Peças Cadastradas.txt", "a");
	
	fprintf(icadastro, "%s", item);
	
	fclose(icadastro);
}

void relatorio(){
	FILE *vtotal;
	char listar[50];
	
	vtotal = fopen("Valor Estoque.txt", "r");
	system("cls");
	while(fgets(listar, 255, vtotal) != NULL) printf("\nVALOR TOTAL DO ESTOQUE: %s\n\n", listar);
	
	fclose(vtotal);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	FILE *qtotal;
	char listar1[50];
	
	qtotal = fopen("Quantidade Estoque.txt", "r");
	while(fgets(listar1, 255, qtotal) != NULL) printf("\nQUANTIDADE TOTAL DE ITENS NO ESTOQUE: %s\n\n", listar1);
	
	printf("Digite 1 Para Continuar!!\n");
	scanf(" ");
	system("cls");
	fflush(stdin);
	
	fclose(qtotal);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	FILE *ptotal;
	char listar2[50];
	int pt = 1;
	
	ptotal = fopen("Peças Cadastradas.txt", "r");
	while(fgets(listar2, 255, qtotal) != NULL) printf("\nITEM %d: %s\n\n", pt++, listar2);
	
	printf("Digite 1 Para Continuar!!\n");
	scanf(" ");
	system("cls");
	fflush(stdin);
	
	fclose(ptotal);
}
		

