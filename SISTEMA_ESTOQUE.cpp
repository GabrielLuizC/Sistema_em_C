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
void listar();
void excluirItem();
void vendasEstoque();
void metodoPagamento();

struct cadastrar{
	int id;
	char nome[50];
	float valor;
	float quantidade;
	char excluir;
};

main(){
	menu();
    return 0;
}

void menu(){
    int escolha;
    do{
    	printf("=-=-=-=-=-=-=-=-= Sistema =-=-=-=-=-=-=-=-=\n");
	    printf("	1 - Cadastrar Item \n");
	    printf("	2 - Listar e Consultar Estoque \n");
	    printf("	3 - Editar Item \n");
	    printf("	4 - Excluir Item \n");
	    printf("	5 - Relatorio Geral \n");
	    printf("	6 - Venda \n");
	    printf("	7 - Sair\n");
	    printf("=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-==-=-=\n\n");
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
			case 4:
				excluirItem();
				break;
			case 5:
				relatorio();
				break;
			case 6:
				vendasEstoque();
				break;
		    case 7:
				printf("\nSAINDO DO SISTEMA ...");
			    break;
		    default:
		    	printf("\n\nERROR - REINICIE O SISTEMA\n\n");
		}	
	}while(escolha != 7);
}

void cadastroItem(){
	struct cadastrar cadastro;
	int recebe;
	
	FILE *arq;
    
    arq = fopen("Estoque.pro", "ab");
    
    if(arq == NULL){
    	printf("\nArquivo Nao Encontrado");
	}
	
	
	system("cls");
	
	printf("=-=-=-=-= Cadastro de Itens =-=-=-=-=\n");	
	printf("Digite o ID: ");
    scanf("%d", &cadastro.id);
	
	fflush(stdin);
	
    printf("\nDigite o Nome: ");
    gets(cadastro.nome);
    
    printf("\nDigite a Quantidade: ");
    scanf("%f", &cadastro.quantidade);
    
    printf("\nDigite o Valor Unitario do Produto: ");
    scanf("%f", &cadastro.valor);
    
    system("cls");	
    
	fwrite(&cadastro, sizeof(cadastro), 1, arq);
	
	fclose(arq);
	
	printf("=-=-=-=-=-=-= Cadastro de Itens =-=-=-=-=-=-=\n");
	printf("\n	  ITEM CADASTRADO COM SUCESSO!!\n\n");
	printf("=-=-=-=-=-=-= Cadastro de Itens =-=-=-=-=-=-=\n\n");
	printf("DIGITE 1 PARA CONTINUAR!!\n");
	scanf(" ");
	system("cls");
	fflush(stdin);
}
		

void listarEstoque(){
	struct cadastrar cadastro;
	int consulta;
	int procuraid;
	int aux;
	
	FILE *arq;
	    
    arq = fopen("Estoque.pro", "rb");
    
    if(arq == NULL){
    	printf("\nArquivo Nao Encontrado");
	}
	
	system("cls");
	
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
	printf("1 - LISTAR ESTOQUE COMPLETO \n2 - CONSULTAR ITEM POR ID CADASTRADO\n\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
	printf("Escolha uma opcao: ");
	scanf("%d", &consulta);
	
	system("cls");
	
	if(consulta == 1){	
		printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
		printf("LISTAGEM DE ESTOQUE COMPLETA (OBS: 'STATUS: P', INDICA QUE O ITEM NO ESTOQUE ESTA PERMITIDO PARA VISUALIZACAO)\n\n");
		printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
		while(fread(&cadastro, sizeof(cadastro),1 , arq) != NULL){
			if(cadastro.excluir != '*'){
				printf("ID: %d | Item: %s | Quantidade: %.1f | Valor: R$ %.2f | Status: %c\n", cadastro.id, cadastro.nome, cadastro.quantidade, cadastro.valor, cadastro.excluir);	
			}	
		} 
	}
	if(consulta == 2){
		printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
		printf("CONSULTA DE ITEM A PARTIR DO ID CADASTRADO NO ESTOQUE\n\n");
		printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
		printf("DIGITE O CODIGO ID A SER CONSULTADO: ");
		scanf("%d", &procuraid);
		while (fread (&cadastro, sizeof(cadastro), 1, arq)){
			if(cadastro.excluir != '*'){
				if ((procuraid == cadastro.id)) {
					printf("ID: %d | Item: %s | Quantidade: %.1f | Valor: R$ %.2f\n", cadastro.id, cadastro.nome, cadastro.quantidade, cadastro.valor);
					aux = 1;
				}	
			}
		}
		
		if (!aux) printf("\nCODIGO DIGITADO NAO FOI ENCONTRADO!!\n");
	}
	printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
	printf("\nDIGITE 1 PARA CONTINUAR!!\n");
	scanf(" ");
	
	fflush(stdin);
	system("cls");
	fclose(arq);
}

void listar(){
	struct cadastrar cadastro;
	FILE *arquivo;
	    
    arquivo = fopen("Estoque.pro", "rb");
    
    while(fread(&cadastro, sizeof(cadastro),1 , arquivo) != NULL){
    	if(cadastro.excluir != '*'){
			printf("ID: %d | Item: %s | Quantidade: %.1f | Valor: R$ %.2f\n", cadastro.id, cadastro.nome, cadastro.quantidade, cadastro.valor);	
		}
	}
    
    fclose(arquivo);
}

void editarItem(){
	int procuraid;
	int aux;
	
	FILE *arq;
	    
    arq = fopen("Estoque.pro", "r+b");
    
    if(arq == NULL){
    	printf("\nArquivo Nao Encontrado");
	}else{
		printf("\nArquivo Encontrado\n\n");
	}
	
	system("cls");

	listar();

	struct cadastrar cadastro;
	
	printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
	printf("DIGITE O CODIGO ID A SER EDITADO: ");
	scanf("%d", &procuraid);
	
	while (fread (&cadastro, sizeof(cadastro), 1, arq)){
		if(cadastro.excluir != '*'){
			if ((procuraid == cadastro.id)) {
				printf("\nID: %d | ITEM: %s | QUANTIDADE: %.1f | VALOR: R$ %.2f\n", cadastro.id, cadastro.nome, cadastro.quantidade, cadastro.valor);
				aux = 1;
				fflush(stdin);
				fseek(arq, sizeof(struct cadastrar)*-1, SEEK_CUR);
				printf("\nDIGITE O NOVO NOME: ");
			    gets(cadastro.nome);
			    
			    printf("\nDIGITE A NOVA QUANTIDADE SE TIVER SOFRIDO ALTERACAO: ");
			    scanf("%f", &cadastro.quantidade);
			    
			    printf("\nDIGITE O NOVO VALOR UNITARIO DO PRODUTO SE TIVER SOFRIDO ALTERACAO: ");
			    scanf("%f", &cadastro.valor);
			    
			    fwrite(&cadastro, sizeof(cadastro), 1, arq);
			    fseek(arq, sizeof(cadastro)* 0, SEEK_END);
			}	
		}	
	}
	
	if (!aux) printf ("\nCODIGO DIGITADO NAO FOI ENCONTRADO!!\n");
	
	printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
	
	fclose(arq);
	
	printf("DIGITE 1 PARA CONTINUAR!!\n");
	scanf(" ");
	
	fflush(stdin);
	system("cls");
}

void excluirItem(){
	struct cadastrar cadastro;
	int procuraid = 0;
	int aux;
	
	FILE *arqs = fopen("Estoque.pro", "r+b");
	
	char certeza;
	
	system("cls");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
	printf("\n\nDIGITE O CODIGO ID DO ITEM QUE SERA EXCLUIDO: ");
	scanf("%d", &procuraid);
	
	while (fread (&cadastro, sizeof(cadastro), 1, arqs)){
		if(cadastro.excluir != '*'){
			if (procuraid == cadastro.id){
				printf("\nID: %d | Item: %s | Quantidade: %.1f | Valor: R$ %.2f\n", cadastro.id, cadastro.nome, cadastro.quantidade, cadastro.valor);
				aux = 1;
				
				printf("\nTEM CERTEZA QUE DESEJA EXCLUIR ESTE ITEM?? (s para SIM | n para NAO) \n");
				fflush(stdin);
				scanf("%c", &certeza);
				if (certeza == 's'){
					cadastro.excluir = '*';
					printf("\nPPRODUTO EXCLUIDO COM SUCESSO!!\n");
					fseek(arqs,sizeof(struct cadastrar)*-1, SEEK_CUR);
					fwrite(&cadastro, sizeof(cadastro), 1, arqs);
					fseek(arqs, sizeof(cadastro)* 0, SEEK_END);
					//return;
				}else if (certeza == 'n'){
					system("cls");
					printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
					printf("\n\nEXCLUSAO DE ITEM CANCELADA!!\n");
					//return;
				}	
			}
		}
	}
		
		if (!aux) printf("\nCODIGO DIGITADO NAO FOI ENCONTRADO!!\n");
		
		printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
	fclose(arqs);
	printf("\n\nDIGITE 1 PARA CONTINUAR!!\n");
	scanf(" ");
	
	fflush(stdin);
	system("cls");
}

void valorEstoque(){
	struct cadastrar cadastro;
	int count = 1;
	float total;
	FILE *arq;
	    
    arq = fopen("Estoque.pro", "rb");
    
	while(fread(&cadastro, sizeof(cadastro),1 , arq) != NULL){
		if(cadastro.excluir != '*'){
			total = total + (cadastro.quantidade * cadastro.valor);	
		}	
	} 
	
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
	printf("\n\nVALOR TOTAL DO ESTOQUE: %.1f\n\n", total);
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    fclose(arq);
	
}

void quantidadeEstoque(){
	struct cadastrar cadastro;
	float quant = 0;
	FILE *arquivo;
	    
    arquivo = fopen("Estoque.pro", "rb");
    
    while(fread(&cadastro, sizeof(cadastro),1 , arquivo) != NULL) {
    	if(cadastro.excluir != '*'){
			quant += cadastro.quantidade;
		}
	}
	
	printf("\n\nQUANTIDADE TOTAL DE ITENS NO ESTOQUE: %.1f\n\n", quant);
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    fclose(arquivo);
}

void itensCadastrados(){
	struct cadastrar cadastro;
	int count = 1;
	FILE *arquivo;
	    
    arquivo = fopen("Estoque.pro", "rb");
    
    
    while(fread(&cadastro, sizeof(cadastro),1 , arquivo) != NULL) 
	if(cadastro.excluir != '*'){
			printf("ITEM %d: %s\n", count++, cadastro.nome);
	}
	
	printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    fclose(arquivo);
}

void relatorio(){
	system("cls");
	valorEstoque();
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	quantidadeEstoque();
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	itensCadastrados();
	
	printf("\nDigite 1 Para Continuar!!\n");
	scanf(" ");
	system("cls");
	fflush(stdin);
	
}

void vendasEstoque(){
	struct cadastrar cadastro;
	int count = 1;
	int procuraid = 0;
	float quantidade;
	float valorCompra;
	char confirma;
	int escolha;
	float desconto;
	FILE *arq;
	    
    arq = fopen("Estoque.pro", "rb");
    
    system("cls");
    
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    listar();
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\nDIGITE O ID DO PRODUTO QUE DESEJA COMPRAR?? ");
	scanf("%d", &procuraid);
    
    while(fread(&cadastro, sizeof(cadastro),1 , arq) != NULL) 
	if(cadastro.excluir != '*'){
		if(procuraid == cadastro.id){
			printf("\nID: %d | Item: %s | Quantidade: %.1f | Valor: R$ %.2f\n", cadastro.id, cadastro.nome, cadastro.quantidade, cadastro.valor);
			printf("\nDIGITE A QUANTIDADE DO PRODUTO QUE DESEJA COMPRAR?? ");
			scanf("%f", &quantidade);
			
			valorCompra = quantidade * cadastro.valor;
			
			system("cls");
			
			printf("=-=-=-=-=-=-=-=-=-=-= CARRINHO DE COMPRAS =-=-=-=-=-=-=-=-=-=-=\n");
			printf("	PRODUTO SELECIONADO: %s\n", cadastro.nome);
			printf("	QUANTIDADE SELECIONADA: %.1f\n", quantidade);
			printf("	VALOR UNITARIO DO PRODUTO: R$ %.2f\n", cadastro.valor);
			printf("	VALOR TOTAL DA COMPRA: R$ %.2f\n", valorCompra);
			printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
			
			printf("\nDESEJA CONFIRMAR A COMPRA?? (s para SIM | n para NAO) :  ");
			scanf("%s", &confirma);
			
			if(confirma == 's' || confirma == 'S'){
				fseek(arq, sizeof(struct cadastrar)*-1, SEEK_CUR);
				cadastro.quantidade -= quantidade;
			    fwrite(&cadastro, sizeof(cadastro), 1, arq);
			    fseek(arq, sizeof(cadastro)* 0, SEEK_END);
			    
			    system("cls");
			    
			    metodoPagamento();
			    
			    printf("\nESCOLHA UMA FORMA DE PAGAMENTO: ");
			    scanf("%d", &escolha);
			    
			    system("cls");
			    
			    switch(escolha){
			    	case 1:
			    		printf("=-=-=-=-=-=-=-=-=-=-= CARTAO DE CREDITO =-=-=-=-=-=-=-=-=-=-=\n");
						printf("		    1 - 1x SEM JUROS\n");
						printf("		    2 - 2x SEM JUROS\n");
						printf("		    3 - 3x SEM JUROS\n");
						printf("		    4 - 4x SEM JUROS\n");
						printf("		    5 - 5x SEM JUROS\n");
						printf("		    6 - 6x SEM JUROS\n");
						printf("		    7 - 7x SEM JUROS\n");
						printf("		    8 - 8x SEM JUROS\n");
						printf("		    9 - 9x SEM JUROS\n");
						printf("		    10 - 10x SEM JUROS\n");
						printf("	  	    11 - 11x COM JUROS\n");
						printf("	  	    12 - 12x COM JUROS\n");
						printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
						
						printf("\nESCOLHA A FORMA DE PARCELAMENTO: ");
			    		scanf("%d", &escolha);
			    		if(escolha == 1) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra);
			    		if(escolha == 2) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/2);
			    		if(escolha == 3) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/3);
			    		if(escolha == 4) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/4);
			    		if(escolha == 5) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/5);
			    		if(escolha == 6) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/6);
			    		if(escolha == 7) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/7);
			    		if(escolha == 8) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/8);
			    		if(escolha == 9) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/9);
			    		if(escolha == 10) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/10);
			    		if(escolha == 11) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/(11 + 0.5/100));
			    		if(escolha == 12) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/(12 + 50/100));
			    		break;
			    	case 2:
			    		printf("=-=-=-=-=-=-=-=-=-=-= BOLETO BANCARIO =-=-=-=-=-=-=-=-=-=-=\n");
						printf("		    1 - 1x COM JUROS\n");
						printf("		    2 - 2x COM JUROS\n");
						printf("		    3 - 3x COM JUROS\n");
						printf("		    4 - 4x COM JUROS\n");
						printf("		    5 - 5x COM JUROS\n");
						printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
						
						printf("\nESCOLHA A FORMA DE PARCELAMENTO: ");
			    		scanf("%d", &escolha);
			    		if(escolha == 1) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra);
			    		if(escolha == 2) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/2 + 5);
			    		if(escolha == 3) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/3 + 5);
			    		if(escolha == 4) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/4 + 5);
			    		if(escolha == 5) printf("\nCOMPRA DE %dx PARCELAS DE: R$ %.2f\n", escolha, valorCompra/5 + 5);
			    		break;
					case 3:
			    		printf("=-=-=-=-=-=-=-=-=-=-= DINHEIRO =-=-=-=-=-=-=-=-=-=\n");
						printf("	1 - ADICIONAR DESCONTO DE 15 POR CENTO\n");
						printf("	2 - NAO ADICIONAR DESCONTO\n");
						printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
						
						printf("\nESCOLHA A FORMA DE PARCELAMENTO: ");
			    		scanf("%d", &escolha);
			    		if(escolha == 1){
			    			desconto = valorCompra*0.15;
			    			valorCompra = valorCompra - desconto;
			    			printf("\nVALOR DA COMPRA DEU UM TOTAL DE: R$ %.2f\n", valorCompra);
						}
			    		if(escolha == 2) printf("\nVALOR DA COMPRA DEU UM TOTAL DE: R$ %.2f\n", valorCompra);
			    		break;
			    		
				}
			}
			
			if(confirma == 'n'){
				printf("COMPRA CANCELADA");
			}
		}
	}

	printf("\nCOMPRA CONFIRMADA COM SUCESSO\n");
	printf("\nDIGITE 1 PARA VOLTA AO MENU\n");
	scanf(" ");
	system("cls");
	fflush(stdin);
    fclose(arq);
}

void metodoPagamento(){	
	printf("=-=-=-=-=-=-=-=-=-=-= METODO DE PAGAMENTO =-=-=-=-=-=-=-=-=-=-=\n");
	printf("	  	    1 - CARTAO DE CREDITO\n");
	printf("		    2 - BOLETO BANCARIO\n");
	printf("		    3 - PAGAMENTO EM DINHEIRO\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

}
		

