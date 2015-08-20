#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct caracteres{
	int comparando;
	int comparado;
}caracteres;


int buscaCaracteres(int num, caracteres v[]){
	int inicio,media,fim;
	inicio = 0;
	fim = 255;
	while(inicio <= fim){
		media = (inicio + fim)/2;
		if(v[media].comparando == num);
			return media;
		if(v[media].comparando < num){
			inicio = media + 1;
		}
		else{
			fim = media - 1;
		}
	}
	return -1;
}


void Cesar(int chave, FILE *arq,char url[],int op){
	FILE* write;
	FILE* write2;
	char le;
	char cifrado[] = "cifradoCesar.txt";
	char decifrado[] = "decifradoCesar.txt";
	if(op == 1){
		arq = fopen(url,"r");
		write = fopen(cifrado,"w");
		if(arq == NULL){
			printf("Erro, nao foi possivel abrir o write\n");
		}
		else{
			while( (le=fgetc(arq))!=EOF){
				le=(le+256+chave)%256;
				fputc(le, write);
			}
		fclose(arq);
		fclose(write);
		}
	}
	if(op == 2){
		write = fopen(cifrado,"r");
		write2 = fopen(decifrado,"w");
		if(write == NULL){
			printf("Erro, nao foi possivel abrir o write\n");
		}	
		else{
			while( (le=fgetc(write))!=EOF){
				le=(le+256-chave)%256;
				fputc(le, write2);
			}
		fclose(write);
		fclose(write2);
		}
	}
}

void CesarEscuro(char *visible_text, char *hidden_text){
	
	FILE *write=NULL,*write2=NULL;
	int read=0,read2=0,escreve=0;
	
	write = fopen(hidden_text,"r");//abriu o arquivo passado por parametro
	if(write == NULL){
		printf("Nao foi possivel abrir arquivo texto hidden\n");
		return;
	}
	
	write2 = fopen(visible_text,"r");//abriu o arquivo passado por parametro
	if(write2 == NULL){
		printf("Nao foi possivel abrir arquivo texto visible\n");
		return;
	}
	
	fseek(write,0,SEEK_SET);//aqui é posicionado a agulha no começo do arquivo
	fseek(write2,0,SEEK_SET);//aqui é posicionado a agulha no começo do arquivo
	
	read=fgetc(write); //le o arquivo write e write2
	read2=fgetc(write2);
	escreve=read-read2; //o primeiro caracter do texto "escondido" menos o primeiro do texto visivel

	printf("chave = %d\n",escreve);
	fclose(write);
	fclose(write2);
}

void Vigenere(char chave[],FILE *arq,int opcao){
	int entrada =0,aux =0,i=0;
	char percorre;
	unsigned char inicio[1000],cifra[1000];
	unsigned int tamanho_chave =0;
	FILE *write;
	
	while( (percorre=fgetc(arq))!= EOF ){// le o arquivo e guarda em uma string
		inicio[entrada]=percorre;// string que vai guardar a entrada
		entrada++; // guarda o tamanho da entrada
	}

	inicio[entrada]='\0';
	
	while(chave[i] != '\0'){ // para saber o tamanho da chave pois o unsigned char nao funciona strlen
		tamanho_chave++;
		i++;		
	}
	
	while(tamanho_chave < entrada){// para deixar a chave do tamanho da entrada
		chave[tamanho_chave] = chave[aux];
		tamanho_chave++;
		aux++;
	}
	
	chave[tamanho_chave]='\0';
	
	if(opcao==1){// cifrando
		for(i=0;i < entrada;i++){		
			cifra[i] = ((inicio[i]+chave[i]+256)%256);
		}
		cifra[i]='\0';
		write = fopen("cifradoVigenere.txt","w+");// cria o arquivo onde vai ser gravado a cifra
		if(!write){
			printf("Erro ao abrir o arquivo\n");
			return;
		}

		fprintf(write,"%s",cifra); // escreve no arquivo
		fclose(write);
		
	}
	if(opcao==2){

		for(i=0;i < entrada;i++){
			
			cifra[i] = ((inicio[i]-chave[i]+256)%256);
		}
		cifra[i]='\0';
	
		write = fopen("decifradoVigenere.txt","w+"); // cria o arquivo onde vai ser gravado o decifra
		if(!write){
			printf("Erro ao abrir arquivo\n");
			return;
		}
	
		fprintf(write,"%s",cifra); // escreve no arquivo
		fclose(write);
	}

}

void VigenereEscuro(char *texto_claro,char *texto_escuro){
	FILE *hidden=NULL,*visible=NULL;
	int i = 0;
	int read=0,read2=0;
	
	visible = fopen(texto_claro,"r");
	if(visible == NULL){
		printf("Nao foi possivel abrir o arquivo visible\n");
		return;
	}
	hidden = fopen(texto_escuro,"r");
	if(hidden == NULL){
		printf("Nao foi possivel abrir o arquivo hidden\n");
		return;
	}

	fseek(visible,0,SEEK_SET);
	while((read= fgetc(hidden))!=EOF){
		read2 = fgetc(visible);
		read = read-read2;
		printf("%c",read);
		i++;
	}

	printf("\n");
	fclose(visible);
	fclose(hidden);

}	

void Transposicao(int chave,FILE *arq,char url[],int opcao){
	int i=0,j=0,cont=0,res=0,linhas=0;
	char vetor[1000];
	char le;
	FILE *write;
	FILE *write2;
	char cifrado[] = "cifradoTransposicao.txt";
	char decifrado[] = "decifradoTransposicao.txt";
	

	while( (le=fgetc(arq))!= EOF ){ // le o arquivo e guarda-o em uma string
		vetor[cont]= le;
		cont++; // guarda o tamanho da entrada
	}
	fclose(arq);

	res = cont/chave; // res recebe o numero de colunas que tera
	
	while(cont % chave!=0){ // o tamanho da entrada tem que ter divisao exata pela chave
		vetor[cont]='/';// simbolo que representa o vazio
		cont++;
		res = cont/chave;
	}
	char matriz[chave][res];
	
	if(opcao == 1){ // opcao para cifrar texto
		arq = fopen(url,"r"); // escreve o texto a ser cifrado
		write = fopen(cifrado,"w"); // escreve no arquivo a cifra
		for(i=0;i<res;i++){ // insere elementos do vetor na matriz
			for(j=0;j<chave;j++){ // insere elementos na matriz na vertical
				matriz[j][i] = vetor[linhas];
				linhas++;
			}
		}
		if(arq == NULL){ // se o arquivo estiver vazio
				printf("Erro, nao foi possivel abrir o arquivo\n");
				return;
		} else{

		for(i=0;i < chave;i++){	// le a matriz na horizontal e escreve no arquivo cifrado
			for(j=0;j < res;j++){
				
				putc (matriz[i][j],write); // escreve o caracter no arquivo
				printf("%c",matriz[i][j]);
			}
		}
		fclose(write);
		}
	}
	if(opcao == 2){ // opcao para decifrar
		write = fopen(cifrado,"r"); // abre o texto a ser decifrado
		write2 = fopen(decifrado,"w"); // escreve o texto a ser decifrado
		cont =0;
		for(i=0;i < chave;i++){ // coloca os valores na matriz na horizontal
			for(j=0;j <res;j++){		
				matriz[i][j]=vetor[cont];
				cont++;
			}
		}
		
		if(write == NULL){ // caso o arquivo esteja vazio
				printf("Erro, nao foi possivel abrir o arquivo\n");
				return;
		} else{
			for(i=0;i < chave; i++){ // le os valores na vertical
				for(j=0;j<res;j++){
					if(matriz[j][i]=='/') // retira o @
						putc (' ',write); // escreve o espaço no lugar do @
					else
						putc (matriz[i][j],write2); // escreve o caracter no arquivo
						printf("%c",matriz[i][j]);
				}
			}
		fclose(write2);
		}
	}
	
}

void TransposicaoEscuro(char *texto_claro,char *texto_escuro){
	int chave = 1, tamanho = 0, tamanho2;
	FILE *hidden=NULL,*visible=NULL,*decifrado=NULL;
	char texto_visible[200],texto_decifrado[200];
	hidden = fopen(texto_escuro,"r");
	if(hidden == NULL){
		printf("Impossivel ler o arquivo cifrado\n");
		return;
	}
	visible = fopen(texto_claro,"r");
	if(visible == NULL){
		printf("Impossivel ler o arquivo original\n");
		return;
	}

	fgets(texto_visible,sizeof(texto_visible),visible);

	while(tamanho<=strlen(texto_visible)){
		if(texto_visible[tamanho] == '\n'){
			texto_visible[tamanho] = '\0';
			break;
		}
		tamanho++;
	}

	while(chave<256){
		Transposicao(chave,hidden,texto_escuro,2);

		decifrado = fopen("top secret message.txt","r");
		if(!decifrado){
			printf("Nao foi possivel abrir o texto decifrado\n");
			return;
		}

		tamanho=0;
		fseek(decifrado,0,SEEK_SET);
		fgets(texto_decifrado,sizeof(texto_decifrado),decifrado);
		while(tamanho <= strlen(texto_decifrado)){
			if(texto_decifrado[tamanho] == '\n'){
				texto_decifrado[tamanho] = '\0';
				break;
			}
			tamanho++;
		}

		printf("%s\n",texto_visible);
		printf("%s\n",texto_decifrado);

		printf("%d\n",tamanho2=strlen(texto_visible));
		printf("%d\n",tamanho2=strlen(texto_decifrado));

		if(strcmp(texto_decifrado,texto_visible)==0){
			printf("Texto compativel com chave = %d\n",chave);
			break;
		}
		chave++;
		fclose(decifrado);

	}
	fclose(hidden);
	fclose(visible);

}

void Substituicao(FILE *arq, char *tabela_carac, int op){
	char le,p;
	char cifrado[]="cifradoSubstituicao.txt";
	char decifrado[]="decifradoSubstituicao.txt";
	int i=0;
	int aux = 0;
	int procura;
	FILE *write,*tabela;
	caracteres v[256];

	if(op == 1){
		write = fopen(cifrado,"w");
		if(write == NULL){
			printf("Nao foi possivel abrir o arquivo que salva os dados\n");
			return;
		}
	}
	if(op == 2){
		write = fopen(decifrado,"w");
		if(write == NULL){
			printf("Nao foi possivel abrir o arquivo que salva os dados\n");
			return;
		}
	}

	tabela = fopen(tabela_carac,"r");
	if(tabela_carac == NULL){
		printf("Nao foi possivel abrir a tabela de caracteres\n");
		return;
	}

	while((fscanf(tabela,"%d%c%d",&v[i].comparando,&p,&v[i].comparado))!=EOF){
		i++;
	}

	while((le=fgetc(arq))!= EOF){
		if(le<0){
			procura = 256+le;
			aux = buscaCaracteres(procura,v);
		}
		else{
			aux = buscaCaracteres(le,v);
		}
		if(op==1){
			fputc(v[aux].comparado,write);
		}
		else{
			fputc(v[aux].comparado,write);
		}
	}
	
	fclose(tabela);
	fclose(write);
}

int main(void)
{
	int opcao;
	
	int opcao_msg;

	char aocontrario[]="cifradoTransposicao.txt";

	char url[]="top secret message.txt";

	char tabela[]="tabela.txt";

	char urlcesar[]="pg11.txt";

	char urlcesarcifrado[]="pg11.txt.enc";

	char urlvigenere[]="pg174.txt";

	char urlvigenerecifrado[]="pg174.txt.enc";
	
	char urlvigenere2[]="pg27827.txt";

	char urlvigeneredecifrado2[]="pg27827.txt.enc";

	char ch;
	
	char chave_texto[1000];

	FILE *arq;

	FILE *arq2;

	int num;

	printf("MENU\n1 - Ver a mensagem original\n2 - cifra de cesar\n3 - cifra de vigenere\n4 - cifra de transposicao\n5 - cifra de substituicao\n6 - cifra cesar escuro\n7 - cifra vigenere escuro\n8 - cifra transposicao escuro\n9 - sair\n");
	
	scanf("%d",&opcao);
	
	switch(opcao){
		while(opcao!=6){
			case 1:
			arq = fopen(url, "r");
			if(arq == NULL)
		    	printf("Erro, nao foi possivel abrir o write\n");
			else{
		    	while( (ch=fgetc(arq))!= EOF )
		    		putchar(ch);
		    }
		    fclose(arq);
		  	break;

		  	case 2:
		  	printf("1 - Cifrar 2 - Decifrar\n");
		  	scanf("%d",&opcao_msg);
		  	arq = fopen(url, "r");
			if(arq == NULL){
		    	printf("Erro, nao foi possivel abrir o write\n");
		    	return 0;
		    }
			else{
			  	printf("Digite a chave\n");
			  	scanf("%d",&num);
			  	Cesar(num,arq,url,opcao_msg);
		  	}
		  	break;

			case 3:
			printf("1 cifrar - 2 decifrar\n");
			scanf("%d", & opcao_msg);
			printf("Digite a chave\n");
			getchar();//limpeza do buffer
			fgets(chave_texto,sizeof(chave_texto),stdin);//chave de ate 100 caracteres
			chave_texto[strlen(chave_texto)-1]='\0';//substitui /n por /0
			if(opcao_msg==1){
				arq = fopen(url,"r");//abriu o arquivo passado por parametro
				if(!arq){
					printf("Impossivel abrir arquivo\n");
				return 0;
				}

				Vigenere(chave_texto,arq,opcao_msg);//cifrando
		
				fclose(arq);
			}
		
			if(opcao_msg==2){
				arq = fopen("cifradoVigenere.txt","r");
				if(!arq){
					printf("Impossivel abrir arquivo\n");
					return 0;
				}
				
				Vigenere(chave_texto,arq,opcao_msg);//decifrando
		
				fclose(arq);
			}
			break;
			case 4:
			printf("1 - Cifrar 2 - Decifrar\n");
			scanf("%d",&opcao_msg);
			printf("Digite a chave\n");
			scanf("%d",&num);
			arq = fopen(url,"r");
			if(arq == NULL){
				printf("Erro, nao foi possivel ler o write\n");
				return 0;
			}
			else{
				Transposicao(num,arq,url,opcao_msg);
				fclose(arq);
			}
			break;

			case 5:
			printf("1 - Cifra 2 - Decifrar\n");
			scanf("%d",&opcao_msg);
			arq = fopen(url,"r");
			if(arq == NULL){
				printf("Erro, nao foi possivel ler o arquivo\n");
				return 0;
			}
			else{
				Substituicao(arq,tabela,opcao_msg);
				fclose(arq);
			}
			break;
			case 6:
			arq = fopen(urlcesar, "r");
			arq2 = fopen(urlcesarcifrado,"r");
			if(arq == NULL || arq2 == NULL){
				printf("Erro, nao foi possivel abrir os arquivos\n");
				return 0;
			}else{
			CesarEscuro(urlcesar,urlcesarcifrado);
			}
			break;
			case 7:
			printf("Qual arquivo?\n1 - pg174 2 - pg27827\n");
			scanf("%d",&opcao_msg);
			if(opcao_msg == 1){
				arq = fopen(urlvigenere, "r");
				arq2 = fopen(urlvigenerecifrado,"r");
				if(arq == NULL || arq2 == NULL){
					printf("Erro, nao foi possivel abrir os arquivos\n");
					return 0;
				}else{
				VigenereEscuro(urlvigenere,urlvigenerecifrado);
				}
			}else{
				arq = fopen(urlvigenere2, "r");
				arq2 = fopen(urlvigeneredecifrado2,"r");
				if(arq == NULL || arq2 == NULL){
					printf("Erro, nao foi possivel abrir os arquivos\n");
					return 0;
				}else{
				VigenereEscuro(urlvigenere2,urlvigeneredecifrado2);
				}
			}
			break;
			case 8:
			arq = fopen(url,"r");
			arq = fopen(aocontrario,"r");
			TransposicaoEscuro(url,aocontrario);
			break;

			case 9:
			return 0;
			break;
			
		}
	}
	
	return 0;
}