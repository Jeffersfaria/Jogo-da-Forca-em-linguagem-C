#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include<time.h>
#include"forca.h"

	//Variáveis globais
	char palavrasecreta[TAMANHO];
	char chutes[26];
	int  chutesdados = 0;


void abertura (){
  printf("\n\t\t**********************\n");
    printf("\t\t*    Bem-vindo ao    *\n");
//    printf("**********************\n");
	printf("\t\t* * Jogo da Forca  * *\n");
//	printf("**********************\n");
	printf("\t\t*   Dê o teu chute   *\n");
    printf("\t\t**********************\n\n");
}

void chute (){
	
		char chute;
		scanf(" %c", &chute);
		
		chutes[chutesdados] = chute;
		chutesdados++;
}

void desenhaforca(){

   	system("cls");

	    int erros = chuteserrados();

    printf("\t  _______       \n");
    printf("\t |/      |      \n");
    printf("\t |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf("\t |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf("\t |       %c     \n", (erros>=2?'|':' '));
    printf("\t |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf("\t |              \n");
    printf("\t_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavrasecreta); i++) {

        if(jachutou(palavrasecreta[i])) {
            printf("\t%c ", palavrasecreta[i]);
        } else {
            printf("\t_ ");
        }

    }
    printf("\n");

	
}

void adcionapalavra(){
	
	char quer; 
	
	printf("\tDeseja adcionar uma nova palavra ao jogo? (S/N)\n");
//O espaço avisa o scanf que eu quero um char só. Muito importante!
	scanf(" %c", &quer);
	
	
	char novapalavra[TAMANHO];
	
	if(quer == 'S'){
		printf("\t\tQual a nova palavra?\n");
		scanf("%s", &novapalavra);
		
		FILE* f;
		
		f = fopen("palavras.txt", "r+");
		
		if(f == 0){
			printf("\t\tDesculpe, banco de dados não disponível\n\n");
			exit(1);
			
		} 
		
		int qtd;
		fscanf(f,"%d", &qtd);
		qtd++;
		
		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);
		
		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novapalavra);
		
		fclose(f);
		
		
	}
	
}



void escolhepalavra (){
	
	FILE* f;
	
	f = fopen("palavras.txt", "r");
	
	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);
		if(f == 0){
			printf("\t\tDesculpe, banco de dados não disponível\n\n");
			exit(1);
			
		} 
	
	
	srand(time(0));
	int randomico = rand() % qtddepalavras;
	
	for(int i = 0; i <= randomico; i++){
		
		fscanf(f, "%s", palavrasecreta);
	}
	
	
	fclose(f);
}

int acertou(){
	for(int i = 0; i < strlen(palavrasecreta); i++){
		if(!jachutou(palavrasecreta[i])){
			return 0;
		}
	}
	
	return 1;
}

int enforcou(){
		return chuteserrados() >= 5;
}

int letraexiste(char letra) {

    for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}


int chuteserrados(){
	 int erros = 0;

    for(int i = 0; i < chutesdados; i++) {

        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}


int jachutou(char letra){
	
	
		int achou = 0;
			
		
			for(int j = 0; j < chutesdados; j++){
				
				if (chutes[j] == letra){
				achou = 1;
					break;
				}
				
			}
			
			return achou;
	
}


	int main(){
		setlocale(LC_ALL, "Portuguese");
	
			escolhepalavra();
	
	
	do{
		
	
			desenhaforca();
			abertura();
		
			chute();
				
		
}	while(!acertou() && !enforcou());

	if(acertou()){
		
		system("cls");
		        printf("\n\t\tParabéns, você ganhou!\n\n");
               printf("\tA palavra secreta em questão, era **%s**\n\n", palavrasecreta);
        printf("\t\t       ___________      \n");
        printf("\t\t      '._==_==_=_.'     \n");
        printf("\t\t      .-\\:      /-.    \n");
        printf("\t\t     | (|:.     |) |    \n");
        printf("\t\t      '-|:.     |-'     \n");
        printf("\t\t        \\::.    /      \n");
        printf("\t\t         '::. .'        \n");
        printf("\t\t           ) (          \n");
        printf("\t\t         _.' '._        \n");
        printf("\t\t        '-------'       \n\n");
        
        adcionapalavra();
		
	}else{
		system("cls");
		        printf("\n\t\tPuxa, você foi enforcado!\n");
        		printf("\n\tA palavra secreta em questão, era **%s**\n", palavrasecreta);
				printf("\n\t\tMais sorte da próxima vez!\n\n");
        printf("\t\t    _______________         \n");
        printf("\t\t   /               \\       \n"); 
        printf("\t\t  /                 \\      \n");
        printf("\t\t//                   \\/\\  \n");
        printf("\t\t\\|   XXXX     XXXX   | /   \n");
        printf("\t\t |   XXXX     XXXX   |/     \n");
        printf("\t\t |   XXX       XXX   |      \n");
        printf("\t\t |                   |      \n");
        printf("\t\t \\__      XXX      __/     \n");
        printf("\t\t   |\\     XXX     /|       \n");
        printf("\t\t   | |           | |        \n");
        printf("\t\t   | I I I I I I I |        \n");
        printf("\t\t   |  I I I I I I  |        \n");
        printf("\t\t   \\_             _/       \n");
        printf("\t\t     \\_         _/         \n");
        printf("\t\t       \\_______/           \n\n");
		
		
	}

}

