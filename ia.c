#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h> //tolower()
#include <unistd.h>//usleep()
// #include <locale.h> para pode acemtuar.
// Função que processa as perguntas usando uma "árvore de decisão"
//comando usado pra adicionar perguntas
//        else if (strstr(pergunta,"") != NULL)
//        {
//             printf("\n");
//        }
// Função para converter string para minúsculas
void charsensivel(char *str);
// Função pra receber uma palavra e transformar characteres especiais para characteres ascII
int IA_tutorFutebol(char pergunta[]); 

int main() {
	setlocale(LC_ALL, "Portuguese"); // assim a acentuação fica ok no programa
    char *pergunta = NULL;
    size_t buffer = 0;
    ssize_t imputsize;


    
    printf("Bem-vindo ao Tutor Inteligente de Futebol!\n");
    printf("Este programa usa uma técnica de IA chamada arvores de decisões\n\n\n");
    printf("Pergunte algo sobre futebol e seus sub-tópicos (ex.: 'time, jogador, campeonato, regras') ou digite 'sair' para encerrar:\n");
    
    // Loop para interação contínua
    while (1) 
    {
        printf("\nSua pergunta: ");

        imputsize = getline(&pergunta, &buffer, stdin);
        if (imputsize == -1) {
            perror("Erro ao ler a entrada");
            free(pergunta);
            return 1;
        }    
        // Remover o caractere de nova linha
        if (imputsize > 0 &&  pergunta[imputsize -1 ] == '\n') {
            pergunta[imputsize -1 ] = '\0';
        }
        charsensivel(pergunta);// pergunta se torna uma str sem characteres sensiveis.
        

        // Verificar se o usuário quer sair
        if (strcmp(pergunta, "sair") == 0) 
        {
            printf("Até mais! Vamos conversar sobre futebol novamente outro dia!\n");
            break;
        }

        // se a ia quiser parar a conversa por algum motivo
        if (IA_tutorFutebol(pergunta) == 1){
            break;

        }
    }
    free(pergunta);
    return 0;
}

int elogioList(char *pergunta){ // função esta quebrando
    //lista de strings
    char *elogioList[]={"melhor", "melhor", "bom", "mais", "rico", "habilidoso",
    "foda", "pica", "pika", "zinho", "zao", "inigualavel", NULL};
    for (int i = 0; elogioList[i] != NULL ; i++) {
        if (strstr(pergunta, elogioList[i]) != NULL){
            return 1;
        }
    }
        return 0; // if the code reads here, than it found nothing
    
}
int xingamentosList(char *pergunta){
    //xingamentos compostos
    if(strstr(pergunta, "bola") != NULL && strstr(pergunta, "murcha") != NULL||
    strstr(pergunta, "sem") != NULL && strstr(pergunta, "igual") != NULL ||
    strstr(pergunta, "todos") != NULL && strstr(pergunta, "os") != NULL && strstr(pergunta, "tempos") != NULL){
        return 1;
    }
     //lista de strings
    
    char *xingamentosList[]={"merda", "menor","ruim","nojento","pior", "esquizito", "feio", "molenga", "preguiçoso", "zinho", "zao","horrivel", NULL};
    for (int i = 0; xingamentosList[i] != NULL ; i++) {
        if (strstr(pergunta, xingamentosList[i]) != NULL){
            return 1;
        }
    }
    return 0; // if the code reads here, than it found nothing
    
}
   
    

char *questionList(char *pergunta){
    if(strstr(pergunta, "o ") != NULL && strstr(pergunta, "que") != NULL){
        return "o que";
    }
    if(strstr(pergunta, "por") != NULL && strstr(pergunta, "que") != NULL) {
        return "por que";
    }
     //lista de strings
    
    char *questionlist[]={ "quando", "qual", "como", "onde",NULL};
    for (int i = 0; questionlist[i] != NULL ; i++) {
        if (strstr(pergunta, questionlist[i]) != NULL){
            return questionlist[i];
        }
    }
    return NULL; // if the code reads here, than it found nothing
    
    
}
void charsensivel(char *str) {
    char *weird[] = {"á", "à", "ä", "â","ã", "é", "è", "ë", "ê", 
                     "í", "ì", "ï", "î", "ó", "ò", "ö", "ô","õ"
                     "ú", "ù", "ü", "û", "ç"};
    char *normal[] = {"a", "a", "a", "a","a", "e", "e", "e", "e", 
                      "i", "i", "i", "i", "o", "o", "o", "o","o",
                      "u", "u", "u", "u", "c"};
    int weird_count = sizeof(weird) / sizeof(weird[0]);

    char bigList[1024] = {0};  // evitando problema de memotria, lista auxiliar com espaços nulos
    int letraEstranha = 0, i, j, replaced;           

    for ( i = 0; str[i] != '\0'; i++) {
         replaced = 0;

        // Check if the current character matches any "weird" character
        for ( j = 0; j < weird_count; j++) {
            if (strncmp(&str[i], weird[j], strlen(weird[j])) == 0) { // compara as variaveis nos endereços listados
                
                bigList[letraEstranha] = normal[j][0]; // substitui a i-ésima letra estranha pelo equivalente
                i += strlen(weird[j]) - 1; // Skip the rest of the multi-byte character
                replaced = 1;
                letraEstranha++;
                break;
            }
        }

        // se nenhuma troca aconteceu, copie a string
        if (replaced == 0) {
            bigList[letraEstranha] = str[i];
            letraEstranha++;
        }
    }

    strcpy(str, bigList); // copiar devolta pra uma lista unidimensional

    // botando tudo em minusculo depois.
    for (i = 0; str[i]; i++) 
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int IA_tutorFutebol(char pergunta[]) {   
    int i,j;
    if (strlen(pergunta) == 0)
    {
        
        printf("\nNao tenha medo, me pergunte o que quiser! \n");
    }
    else if (strstr(pergunta, "?") == NULL)
    {
        printf("Por favor, faça uma PERGUNTA!!"); 
    }
    
    else if (strstr(pergunta, "flamengo") != NULL) {
        if (strstr(pergunta, "o que é") != NULL) 
        {
            printf("\n Flamengo é um time de futebol, atualmente melhor e maior do RJ\n");
        }  
        else if (strstr(pergunta, "elenco") != NULL)
        {
            printf("\nO elenco titular do Flamengo 2024 consta atualmente com: Rossi/Goleiro, Léo Ortiz e Léo Pereira/Zagueiros, Wesley e Alecsandro/Laterais, Erick Pulgar e Everton Araujo/Volantes, Gerson e De Arrascaeta/Meio-Campo, Michael e Gabigol/Atacantes.\n");
        }
        else if (strstr(pergunta, "formacao") != NULL)
        {
            printf("\nA formação atual do Flamengo 2024, é a formação 4-2-3-1.\n");
        }
        else if (strstr(pergunta, "tecnico") != NULL)
        {
            printf("\nO atual técnico do Flamengo é Filipe Luís, Ex-Jogador do Clube e técnico recém-formado assumiu a vaga de Tite.\n");
        }
        else if (strstr(pergunta, "titulos") != NULL)
        {
            printf("\nO Flamengo possui diversos títulos, sua conquista mais recente foi a Copa do Brasil 2024 contra o Atlético MG em um agregado de 4-1!, o Flamengo é Octa Campeão Brasileiro, Penta Campeão da Copa do Brasil e Tri Campeão da Copa Libertadores da América.\n");
        }
        else if (strstr(pergunta, "jogos") != NULL)
        {
            printf("\nOs ultimos jogos do Flamengo foram 2-2 vs Vitória, 3-0 vs Críciuma e 3-2 vs Internacional, seu próximo confronto está marcado para 2025 dia 11/01 contra o Boavista pelo campeonato Carioca.\n");
        }
        else if (strstr(pergunta, "idolos") != NULL)
        {
            printf("\nOs maiores ídolos do Flamengo são: Zico, Gabigol, Junior, Leandro, Arrascaeta, Zizinho, Leonidas, Adílio, entre muitos outros nomes.\n");
        }
        else if (strstr(pergunta, "estadio") != NULL)
        {
            printf("\nO estádio atual do Flamengo é o Maracanã, porém o Flamengo está projetando a construção de um novo estádio para o clube.\n");
        }
        else if (strstr(pergunta, "mascote") != NULL)
        {
            printf("\nO mascote do Flamengo é o Urubu.\n");
        }
        else if (strstr(pergunta, "presidente") != NULL)
        {
            printf("\nO novo presidente do flamengo eleito em 2024 foi Luiz Eduardo Batista, também conhecido como BAP.\n");
        }
        else if (strstr(pergunta, "estatisticas") != NULL)
        {
            printf("\nO Flamengo está 11 jogos seguidos sem perder!.\n");
        }
        else if (strstr(pergunta, "temporada") != NULL)
        {
            printf("\nO Flamengo na temporada 2024 foi Campeão da Copa do Brasil e Campeão Carioca, Terceiro Colocado no Brasileirão e Eliminado nas Quartas de Final da Libertadores pela equipe do Peñarol.\n");
        }
        else if (elogioList(pergunta) == 1)
        {
        
                printf("\n\n\nMM");
                for ( j = 0; i <10 ; i++)
                {
                    printf("E");
                    usleep(10000);
                }
                j=0;
                for ( j = 0; i <6 ; i++)
                {
                    printf("N");
                    usleep(100000);
                }
                j=0;
                printf("GOOOOOOOOOO\n");
            
            
        }
        else if (xingamentosList(pergunta))
        {
            printf("\nVOCE é ruim. \n \n tchau\n ");
            return 1;
        }
        
      
        
        else
        {
            printf("\nFundado em 1895 o Flamengo chegou ao futebol apenas em 1911, é o clube com maior número de torcedores no Brasil!");
        }
    }
    else if (strstr(pergunta, "time") != NULL) {
        if (strstr(pergunta, "o que é") != NULL) 
        {
            printf("\ntime é um conjunto de jogadores que se unem para DESTRUIR os adversários, é por isso que o flamengo é considerado o melhor time.\n");
        }  
        else if (strstr(pergunta, "favorito") != NULL) 
        {
            printf("\nMeu time favorito é o fictício Clube de Regatas Flamengo!\n");
        } 
        else if (strstr(pergunta, "melhor") != NULL) 
        {
            printf("\nO melhor time varia de acordo com o torneio. No Brasil e no Mundo é o Flamengo!\n");
        }
        else if (strstr(pergunta,"outro") != NULL)
        {
            printf("\nPra que você quer saber de outro time além do Flamengo? você não precisa disso amigo, o Flamengo supre todas suas necessidades!\n");
        }
        else 
        {
            printf("\nOs times têm 11 jogadores em campo, e o objetivo é marcar gols, experimente detalhar mais sobre algum time.\n");
        }
    } 
    
    
    else if (strstr(pergunta, "jogador") != NULL) 
    {
        if (strstr(pergunta, "o que é") != NULL) 
        {
            printf("\n Jogadores sao aqueles que constituem um time de fudebol, eles carregam consigo o peso da torcida brasao e a responsabilidade de seu brasao\n");
        }  
        else if (strstr(pergunta, "melhor") != NULL) 
        {
            printf("\nO melhor jogador é uma questão de opinião! Muitos consideram Pelé ou Messi como candidatos mas o verdadeiro é o Gabigol, empatado com o De Arrascaeta.\n");
        } 
        else if (strstr(pergunta, "posicao") != NULL) 
        {
            printf("\nAs posições mais comuns são atacante, meio-campo, zagueiro e goleiro, mas também possuímos, laterais, volantes, meia-armadores, falso-9, centro-avante, dentre outras ainda mais desconhecidas.\n");
        }
        else if (strstr(pergunta, "famoso") != NULL)
        {
            printf("\nOs jogadores mais famosos atualmente no Flamengo são, Pedro, Gabigol, De Arrascaeta e Gerson, ídolos da torcida, esses jogadores são peças fundamentais para as conquistas passadas do Flamengo.\n");
        } 
        else if (strstr(pergunta, "pedro") != NULL)
        {
            printf("\nPedro é um jogador do Flamengo que joga como Centro-Avante, lesionado desde metade de 2024, o jogador programa seu retorno aos gramados em 2025.\n");
        }
        else if (strstr(pergunta, "arrascaeta") != NULL)
        {
            printf("\nArrascaeta é um dos ídolos do Flamengo, o jogador Uruguaio atua como Meio-Campo e vem se recuperando de uma cirurgia, voltará aos gramados em 2025.\n");
        }
        else if (strstr(pergunta, "gabigol") != NULL)
        {
            printf("\nGabriel Barbosa, também conhecido como Gabigol, é um dos maiores ídolos do Flamengo, sendo resonsável por diversos títulos relevantes como a Libertadores de 2019, após conflitos com a diretoria em relação a sua renovação, Gabigol encerrou seu ciclo no Flamengo.\n");
        }
        else if (strstr(pergunta, "gerson") != NULL)
        {
            printf("\nGerson é um dos jogadores do Flamengo que joga como meio-campo, o jogador vem colecionando boas atuações e tem sido convocado para a seleção Brasileira, essa é sua segunda passgem pelo flamengo, com a primeira sendo em 2019, quando foi campeão pelo clube.\n");
        }
        else 
        {
            printf("\nOs jogadores são essenciais para o futebol, cada um com uma função no time, experimente detalhar mais sobre algum jogador.\n");
        }
    } 
    
    else if (strstr(pergunta, "campeonato") != NULL) 
    {
         if (strstr(pergunta, "o que é") != NULL) 
        {
            printf("\nCampeonato é a disputa de times, equipes e torcida para decidir quem é superior.\n");
        }  
        else if (strstr(pergunta, "mundial") != NULL) 
        {
            printf("\nA Copa do Mundo é o campeonato mundial mais importante, realizado a cada 4 anos, com vários países classificados participando, também temos agora o Mundial de Clubes, onde times classificados participam também a cada 4 anos, inclusive, o Flamengo está classificado para o mundial de Clubes de 2025 e foi campeão Mundial em 1981!\n");
        } 
        else if (strstr(pergunta, "brasileiro") != NULL) 
        {
            printf("\nO Campeonato Brasileiro é disputado por times de todo o Brasil, dividido em várias séries: A, B, C e D, o Flamengo atualmente joga na primeira divisão série A, suas colocações garantem vaga em campeonatos como, Libertadores e Sul-Americana, o Flamengo é Octa Campeão Brasileiro.\n");
        }
        else if (strstr(pergunta, "copa do brasil") != NULL)
        {
            printf("\nA Copa do Brasil é um campeonato nacional realizado com equipes de todo o país, é formada por clubes de quaisquer divisão em um formato mata-mata, o Flamengo é Penta Campeão da Copa do Brasil.\n");
        }
        else if (strstr(pergunta, "libertadores") != NULL)
        {
            printf("\nA Libertadores é um campeonato de fase de grupos e mata-mata que junta equipes de toda a América Latina, sua conquista é comumente chamada de ''La Gloria Eterna'' também garante ao clube vencedor vaga ao Mundial de Clubes, o Flamengo é Tri Campeão da Libertadores.\n");
        }
        else if (strstr(pergunta, "sul americana") != NULL)
        {
            printf("\nA Sul Americana segue a mesma similaridade da Libertadores, porém não concede vaga ao Mundial de Clubes e é composta por equipes que não conseguiram se classificar para a Libertadores.\n");
        } 
        else 
        {
            printf("\nExistem muitos campeonatos no futebol, desde locais até internacionais, experimente perguntar sobre algum em especifico.\n");
        }
    } 
    
    else if (strstr(pergunta, "regras") != NULL || questionList(pergunta) != NULL) 
    {
        if (strstr(pergunta, "impedimento") != NULL)
        {
            printf("\nImpedimento é uma regra do futebol que indica que um jogador não pode continuar a jogada por estar posicionado de forma irregular. A regra é considerada uma das mais importantes do futebol, pois evita que os jogadores se aproveitem de situações vantajosas para marcar gols.\n");
        }
        else if (strstr(pergunta, "falta") != NULL)
        {
            printf("\nNo futebol, uma falta é uma infração das regras do jogo, marcada pelo árbitro quando um jogador comete uma irregularidade. As faltas podem ser cometidas de forma proposital ou não, e podem ser cometidas por qualquer jogador em campo, incluindo o goleiro.\n");
        }
        else if (strstr(pergunta, "escanteio") != NULL)
        {
            printf("\nNo futebol, escanteio é uma falta cometida quando um jogador da equipe defensora atinge a bola e ela ultrapassa a linha de fundo do gol, sem que um gol tenha sido marcado. A equipe adversária recomeça o jogo com um pontapé de canto, ou seja, um pontapé de reposição no canto do campo.\n");
        }
        else if (strstr(pergunta, "tiro de meta") != NULL)
        {
            printf("\nNo futebol, o tiro de meta é uma forma de reiniciar o jogo quando a bola sai da linha de fundo do campo, sem que um gol tenha sido marcado. É concedido à equipe defensora, que deve cobrar o tiro de dentro da pequena área.\n");
        }
        else if (strstr(pergunta, "lateral") != NULL)
        {
            printf("\nA cobrança lateral é um método de reinício do jogo de futebol, quando a bola sai do campo pela linha lateral. É feita pelo jogador adversário ao que mandou a bola para fora.\n");
        }
        else if (strstr(pergunta, "inicio") != NULL)
        {
            printf("\nA saída inicial de uma partida de futebol é um pontapé que dá início ao jogo, sendo executado pelo árbitro após a bola ser colocada no centro do campo.\n");
        }
        else if (strstr(pergunta, "cartoes") != NULL || strstr(pergunta, "cartao") != NULL)
        {
            printf("\nOs cartões amarelo e vermelho são usados no futebol para advertir ou expulsar jogadores que cometem infrações.\n");
        }
        else if (strstr(pergunta, "var") != NULL)
        {
            printf("\nVAR é a sigla para Video Assistant Referee, que em português significa árbitro assistente de vídeo. É um sistema que ajuda o árbitro central a tomar decisões em lances duvidosos, através de imagens fornecidas por câmeras posicionadas no estádio.\n");
        }
        else 
        {
            printf("\nUma partida de Futebol é dividida em 2 tempos de 45 minutos mais acréscimos, formada por 11 jogadores para cada lado, seu objetivo é marcar mais gols que a equipe adversária.\n");
        }
    }
        else
        {
            printf("\nMe desculpe, ainda não reconheço esse tipo de pergunta, poderia realizar uma pergunta diferente?\n");
        }
    return 0;
}