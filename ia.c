#include<stdio.h>
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
    while (1)  //fazer o quit mais genrérico
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
        printf("\neu retornei\n");
        return "o que";
    }
    if(strstr(pergunta, "por") != NULL && strstr(pergunta, "que") != NULL) {
        return "por que";
    }
     //lista de strings
    
    char *questionList[]={ "onde","quando", "qual" ,"quais", "como", "quanto", "quantos",NULL};
    for (int i = 0; questionList[i] != NULL ; i++) {
        if (strstr(pergunta, questionList[i]) != NULL){
            //algumas redundancias do plural
            if ( strcmp(questionList[i], "qual") == 0 || strcmp(questionList[i], "quais") == 0) {  
                return "qual"; 
            }
            if ( strcmp(questionList[i], "quanto") == 0 || strcmp(questionList[i], "quantos") == 0) {  
                return "quanto"; 
            }
            
            return questionList[i];
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
    else if(questionList(pergunta) != NULL){
        if(strcmp(questionList(pergunta), "o que") == 0){ //completo nathan helped
            if(strstr(pergunta, "bola") != NULL){
            printf(" um objeto esférico, necessário para que as partidas de futebol aconteçam");
            } else if(strstr(pergunta, "jogador") != NULL){
            printf("\nprofissional pago para esta em campo e marcar o maximo de gols possível\n");
            } else if(strstr(pergunta, "gol") != NULL){
                printf("\ngol é o ponto do futebol e tambem o nome da area defendida pelo goleiro.Quando uma bola nao é defendida pelo goleiro e passa pela linha demarcada gol, um ponto de gol é contado\n");
            } else if(strstr(pergunta, "goleiro") != NULL){
                printf("\n jogador responsavel por defender a area do gol de pontos adiversários\n");
            }else if(strstr(pergunta, "trave") != NULL){
                printf("\n o aro de ferro que delimita o limite do gol\n");
            }else if(strstr(pergunta, "chuteira") != NULL){
                printf("\n tenis específico para a prática de futebol\n");
            }else if (strstr(pergunta, "time") != NULL) {
            printf("\ntime é um conjunto de jogadores que se unem para DESTRUIR os adversários, é por isso que o flamengo é considerado o melhor time.\n");
            }  else if(strstr(pergunta, "campo") != NULL){
            printf("\ncampo é a área em que o jogo de futebol acontece\n");
            }else if(strstr(pergunta, "torcida") != NULL){
            printf("\nconjunto de pessoas que observam o jogo, onde desejam ativamente pelo sucesso de um deles especifico, e a destruição completa dos adiversários\n");
            }
            else if(strstr(pergunta, "zagueiro central") != NULL){
        printf("\nFica no centro da defesa, tentando impedir que os atacantes adversários marquem gols. Trabalha junto com o outro zagueiro para proteger a área do goleiro.\n");
            }else if(strstr(pergunta, "lateral direito") != NULL){
                printf("\n\n");
            }else if(strstr(pergunta, "zagueiro lateral") != NULL){
                printf("\nSimilar aos laterais, mas com funções de defesa mais centradas. São mais comuns em esquemas táticos específicos, como no futebol de linha de 3 zagueiros.\n");
            }else if(strstr(pergunta, "lateral") != NULL){
                printf("\nFicam nas laterais da defesa, defendendo as investidas do time adversário pelas linhas laterais do campo. Eles também podem apoiar o ataque, cruzando bolas para a área.\n");
            }else if(strstr(pergunta, "volante") != NULL){
                printf("\n\n");
            }else if(strstr(pergunta, "campista") != NULL || strstr(pergunta, "organizador") != NULL) {
                printf("\n Controla o meio-campo, distribuindo passes e criando jogadas ofensivas. Eles têm boa visão de jogo e fazem a transição entre defesa e ataque. \n");
            }else if(strstr(pergunta, "armador") != NULL){
                printf("\nFica mais perto do ataque e tem a função de criar jogadas ofensivas, com passes que desorganizam a defesa adversária e geram oportunidades de gol.\n");
            }else if(strstr(pergunta, "ponta") != NULL){
                printf("\nJoga nas laterais do ataque, utilizando a velocidade para correr ao longo da linha e cruzar para a área ou cortar para o centro e finalizar a gol.\n");
            }else if(strstr(pergunta, "centroavante") != NULL || (strstr(pergunta, "pivo") != NULL)){
                printf("\nA principal função é marcar gols. Fica na posição central no ataque e tenta finalizar as jogadas criadas pelos meio-campistas ou laterais. É o jogador mais focado no ataque.\n");
            }
            else if(strstr(pergunta, "mais") != NULL && strstr(pergunta, "populares") != NULL){
                printf("\nSua fama do passado e presente, somado também com seus ídolos e a cultura dos torcedores de passarem o time que amam para as seguintes gerações\n ");
            }
            else if (strstr(pergunta, "conquistar") != NULL  && strstr(pergunta, "titulos") != NULL){
                printf("\nSua gestão a longo prazo e desempenho fora do esperado, foi o que ajudou o Flamengo a conquistar tantos títulos\n");
            }
            else if (strstr(pergunta, "diferencia") != NULL  && strstr(pergunta, "outros") != NULL){
            printf("\nO Flamengo possui uma das histórias mais emblemáticas dos clubes brasileiros, é um clube de muita tradição, possuinte da maior torcida do Brasil \n");
            }
            else if (strstr(pergunta, "torcida") != NULL  && strstr(pergunta, "representa") != NULL){
            printf("\nA torcida do Flamengo é a alma do clube, é ela que sustenta a receita do clube e da motivação ao Flamengo a continuar sendo o que ele é atualmente.\n");
            }
            else if (strstr(pergunta, "investir") != NULL  && strstr(pergunta, "base") != NULL){
                printf("\nO Flamengo possui uma das melhores estruturas no Brasil para formação de novos jogadores, não só no Rio de Janeiro mas em todos os Estados \n");
                }
            else if (strstr(pergunta, "melhorar") != NULL){
                printf("\nPara melhorar o Flamengo ainda percorre um caminho abstrato para desenvolver essa resposta, porém conseguimos perceber que com o trabalho do clube de ano podemos serguir com o feedback e fe dos torcedores!\n");
                }
            else if (strstr(pergunta, "torcida") != NULL  && strstr(pergunta, "fora") != NULL){
                printf("\nAcredito que o mesmo que a torcida para dentro do Rio de Janeiro, o sentimento rubro-negro atravessa distâncias e atinge ao coração de todos igualmente.\n");
                }
            else if (strstr(pergunta, "Maracana") != NULL  && strstr(pergunta, "Especial") != NULL){
                printf("\nToda a história já construída no Maracanã não pode ser reposta em outro estádio, esse carinho emblemático da torcida e do clube vai se manter até o fim\n");
                }
            else if (strstr(pergunta, "jogadores") != NULL  && strstr(pergunta, "fas") != NULL){
                printf("\nCreio que a personificação e intimidade de fãs com membros do clube é inevitável, não só com jogadores mas com toda a equipe, seja por memórias especiais ou por conhecimento pessoal mesmo nossa tocida é a alma do flamengo\n");
                }
            else if (strstr(pergunta, "planeja") != NULL  && strstr(pergunta, "futuro") != NULL){
                printf("\nSão muitas coisas, seja planejamentos de temporada ou sonhos distantes, o Flamengo não deixa de ser um clube que se projeta para o amanhã\n");
                }
            else if(strstr(pergunta, "libertadores") != NULL){
                printf("\nA Copa Libertadores da América é a principal competição entre clubes da América Latina\n");
                } 
            else if(strstr(pergunta, "flamengo") != NULL){
                if(strstr(pergunta, "libertadores") != NULL){
                printf("\n Nos últimos anos, o Flamengo se estabeleceu como um dos principais times da América. Desde 2019, a equipe carioca conquistou dois títulos da Copa Libertadores  \n");
                }
            } 
            
        }

        else if (strcmp(questionList(pergunta), "quando") == 0){ //completo
            if(strstr(pergunta, "regatas") != NULL){
                printf("\n Fundado no bairro do Flamengo[nota 1] para disputas do esporte remo em 17 de novembro de 1895,[2][11] tornou-se um dos clubes mais bem-sucedidos e populares do esporte brasileiro\n");
            }
            else if(strstr(pergunta, "titulo") != NULL || strstr(pergunta,"campeao") != NULL){
                if (strstr(pergunta, "primeiro") != NULL)
                {
                    printf("oficialmente, flamengo conseguiu seu primeiro título em 1980");
                }else if (strstr(pergunta, "segundo") != NULL)
                {
                    
                    printf("oficialmente, flamengo conseguiu seu primeiro título em 1982");

                }else if (strstr(pergunta, "terceiro") != NULL)
                {
                    printf("oficialmente, flamengo conseguiu seu primeiro título em 1983");
                } else if (strstr(pergunta, "quarto") != NULL)
                {
                    printf("oficialmente, flamengo conseguiu seu primeiro título em 1992");
                } else if (strstr(pergunta, "quinto") != NULL)
                {
                    printf("oficialmente, flamengo conseguiu seu primeiro título em 2009");
                }else if (strstr(pergunta, "sexto") != NULL)
                {
                    printf("oficialmente, flamengo conseguiu seu primeiro título em 2019");
                }else if (strstr(pergunta, "setimo") != NULL || strstr(pergunta, "ultimo") != NULL )
                {
                    printf("oficialmente, flamengo conseguiu seu primeiro título em 2020");
                }
                else{
                    printf("\n o Flamengo é, por decisão judicial, e em seguida, pela Confederação Brasileira de Futebol (CBF), oficialmente detentor de sete títulos do Campeonato Brasileiro  \n");
                }
            
            }
            else if(strstr(pergunta, "libertadores") != NULL ){
                printf("\nA primeira aconteceu em 1981 sob o comando de Zico, o maior ídolo do clube. Em Montevidéu\n");
                if (strstr(pergunta, "ultima") != NULL|| strstr(pergunta, "segunda") != NULL)
                {
                    printf("\n a ultima vez que flamengo ganhou a libertadores foi em 2019\n");
                    
                }
            }
            else if(strstr(pergunta, "maracana") != NULL){
                if (strstr(pergunta, "construido") != NULL){
                printf("\n 16 de junho de 1950, maracana foi construido \n");
                }
                else if(strstr(pergunta,"reformado") != NULL || strstr(pergunta,"reinaugurado") != NULL){
                    printf("O novo Maracanã foi reinaugurado, no dia 27 de abril de 2013, com a capacidade para cerca de 78 mil torcedores e um custo de reforma, aproximadamente, R$ 1,05 bilhão.");
                }
                else if(strstr(pergunta," copa ") != NULL){
                    printf("O novo Maracanã foi reinaugurado, no dia 27 de abril de 2013, com a capacidade para cerca de 78 mil torcedores e um custo de reforma, aproximadamente, R$ 1,05 bilhão.");
                }
            }
            else if(strstr(pergunta, "flamengo") != NULL){
                if (strstr(pergunta, "maracana") != NULL )
                {
                    printf("\nO Flamengo tem o Estádio José Bastos Padilha, na Gávea, onde recebia jogos contra equipes menores até a década de 1990. Desde então, passou a ser mandante no Maracanã.\n");
                }else if (strstr(pergunta, "rival") != NULL ||  strstr(pergunta,"rivalidade")   != NULL|| strstr(pergunta,"classico")  != NULL|| strstr(pergunta," remo ") != NULL)
                {
                    printf("\nA história do clássico da Rivalidade com o botafogocomeça no remo, e sporte mais popular do Rio de Janeiro no final do século XIX.[4] O primeiro confronto entre Botafogo e Flamengo, também chamado desde a década de 1960 como Clássico da Rivalidade, ocorreu em 13 de maio de 1913, no Campo da rua General Severiano, válido pelo Campeonato Carioca daquele ano. A partida terminou 1–0 para o Botafogo, gol de Mimi Sodré, na partida que inaugurou o novo campo do Botafogo.[5]\n");
                }
                else if (strstr(pergunta, "sequencia") != NULL )
                {
                    printf("\no Flamengo também alcançou marcas incríveis na Libertadores. Tricampeão da competição, o Rubro-Negro alcançou a sua maior marca de invencibilidade no torneio em 2021, quando ficou 12 jogos sem perder e chegou na final de forma invicta, onde acabou sendo derrotado pelo Palmeiras.\n ");
                }
                else if (strstr(pergunta, "camisa") != NULL )
                {
                    printf("\n O primeiro uniforme do clube carioca foi criado no ano de 1895, quando ainda só haviam atividades náuticas no quadro esportivo do Flamengo.7 de set. de 2024 \n");
                }
                else if (strstr(pergunta, "primei") != NULL ){
                    if (strstr(pergunta,"partida") != NULL){
                        printf("Em 3 de maio de 1912 acontece a primeira partida do Flamengo: uma grande vitória de 15 x 2 sobre o Mangueira");
                    }
                    else if(strstr(pergunta,"resultado") != NULL){
                        printf("vitória de 15 x 2 sobre o Mangueira");
                    }
                }
            }
            else if (strstr(pergunta, "zico") != NULL )// redundancia caso perguntem do zico sem perguntar do flamengo
                {
                    printf("Notabilizou-se como o líder da vitoriosa trajetória do Flamengo nas décadas de 1970 e 1980, com ápice nas conquistas da Copa Libertadores da América e da Copa Intercontinental pela equipe carioca");
                }
            else{
                printf("desculpe, eu entendo partes da sua pergunta mas nao ela completa, poderia tentar refrasear?");
            }
        }

        else if (strcmp(questionList(pergunta), "quanto") == 0) { 
            if(strstr(pergunta, "titulo") != NULL){
            printf("\nAo longo de sua história, o Rubro-Negro levantou mais de 100 troféus\n");
            }
            else if(strstr(pergunta,"placar") != NULL || strstr(pergunta,"gol") != NULL && strstr(pergunta, "maior") != NULL){
            printf("\n no classico o maior numero de gols numa mesma partida foi: Flamengo 6 x 1 Vasco - 02/06/2024. para o flamengo e Vasco 7 x 0 Flamengo - 26/04/1931 contra o flamengo \n");
            }
            else if(strstr(pergunta, "flamengo") != NULL){
                
                if (strstr(pergunta,"final") != NULL)
                {
                    if (strstr(pergunta,"placar") != NULL)
                    {
                        printf("O título. O Flamengo tem um título do Mundial. Em 1981, a equipe comandada por Zico derrotou o Liverpool por 3 a 0 no Japão");
                    }
                    
                    if (strstr(pergunta,"primeira") != NULL)
                    {
                        printf("\nRubro-Negro fez a última partida da competição como visitante nas edições de 1990\n");
                    }
                    
                    else if (strstr(pergunta,"segunda") != NULL)
                    {
                        printf("\nRubro-Negro fez a última partida da competição como visitante nas edições de 2003\n");
                    }
                    else if (strstr(pergunta,"terceira") != NULL)
                    {
                        printf("\nRubro-Negro fez a última partida da competição como visitante nas edições de 2017\n");
                    }
                    else if (strstr(pergunta,"quarta") != NULL)
                    {
                        printf("\nRubro-Negro fez a última partida da competição como visitante nas edições de 2022\n");
                    }
                    else if (strstr(pergunta,"ultima") != NULL)
                    {
                        printf("\nRubro-Negro fez a última partida da competição como visitante nas edições de 2022\n");
                    }
                    else{
                        printf("\nRubro-Negro fez a última partida da competição como visitante nas edições de 1990, 2003, 2017 e 2022. \n");
                    }
                }
                
                else if(strstr(pergunta, "copa") != NULL){
                printf("\nCom relação aos clubes que mais revelaram jogadores que foram convocados para a Seleção Brasileira em uma Copa do Mundo, a liderança é do Flamengo, com 37 convocações de 26 jogadores\n");
                }
                else if(strstr(pergunta, "gol") != NULL){
                printf("\nna história do futebol brasileiro: Flamengo: 13.001.\n");
                }
                else if(strstr(pergunta, "gol") != NULL){
                printf("\nna história do futebol brasileiro: Flamengo: 13.001.\n");
                }
                else if(strstr(pergunta, "gol") != NULL){
                printf("\nna história do futebol brasileiro: Flamengo: 13.001.\n");
                }
                else if(strstr(pergunta, "tempo") != NULL){
                printf("Cada partida de futebol tem dois tempos de 45 minutos, salvo acordo anterior ao contrário.");
                } 
                else if(strstr(pergunta, "minutos") != NULL){
                printf("Cada partida de futebol tem dois tempos de 45 minutos, salvo acordo anterior ao contrário.");
                }
                else if(strstr(pergunta, "times") != NULL){
                printf("\n  \nCom relação aos clubes que mais revelaram jogadores que foram convocados para a Seleção Brasileira em uma Copa do Mundo, a liderança é do Flamengo, com 37 convocações de 26 jogadores\n\n");
                }
                else if(strstr(pergunta, "cart") != NULL){
                printf("Art. 29º - Para cada serie de três cartões amarelos o atleta cumprirá suspensão de uma partida automática.");
                }
                else if(strstr(pergunta, "arbitro") != NULL){
                printf("\nUma partida de futebol conta com a presença de quatro árbitros\n");
                }
                else if(strstr(pergunta, "subtitui") != NULL){
                printf("\n quantidade de substituições subiu de três para cinco, podendo haver até três paradas enquanto o jogo estiver com bola rolando\n");
                }
                

            }

            } 
        
        else if (strcmp(questionList(pergunta), "como") != 0) {//nathan 
            if (strstr(pergunta, "tornou") != NULL  && strstr(pergunta, "maior") != NULL){
            printf("\nNo cenário de torcida, o Flamengo se tornou um dos maiores clubes com a chegada das rádios que no passado tiveram muita influência para o aumento de público do clube, para coroar nessa época teve a chegada da chamada Década de Ouro com o elenco de ídolos como Zico, Junior e Companhia. No cenário financeiro, a gestão ecônomica do ex-presidente de clube Eduardo Bandeira de Mello, trouxe a segurança financeira que o clube necessitava para comportar um clube de elite.\n");
            }
            else if(strstr(pergunta, "trajetória") != NULL){
            printf("\nA trajetória do Flamengo não só nesse ano mas nos ultimos anos parece como um sonho para a maioria dos torcedores, em um espaço de uma década o clube foi capaz de arrecadar receitas bilionárias e títulos que antes eram vistos como milagres, no geral, por mais que exista oscilação em temporadas como qualquer outro clube, a trajetória do Flamengo hoje está em um patamar completamente diferente dos das ultimas 2 décadas.\n");
            }
            else if (strstr(pergunta, "influencia") != NULL  && strstr(pergunta, "cultura") != NULL){
                printf("\nHoje o Flamengo praticamente faz parte do dia a dia do carioca, seja conversar com amigos, planejar uma idã ao maracanã, um churrasco de fim de semana, feiras, eventos, sonhos na infância de jovens de todas as classes sociais, não existe mais Flamengo sem Rio de Janeiro e não existe mais Rio de Janeiro sem Flamengo.\n");
                }
            else if (strstr(pergunta, "administra") != NULL  && strstr(pergunta, "torcedores") != NULL){
            printf("\nSatisfazer a maior torcida do Brasil não é fácil e o Flamengo não mede esforços para isso, com parcerias, sócio-torcedor, e filiais em todos os estados, o Flamengo tenta mitigar a distância do torcedor de outro estado da melhor forma possível, garantindo a transmissão dos seus jogos importantes na televisão aberta e buscando sempre a compra do mando de campo de adversários dispostos a cede-lo para garantir a torcida fora do Rio de Janeiro uma experiência emblemática de ver o Flamengo jogar.\n");
            }
            else if (strstr(pergunta, "conquistas") != NULL  && strstr(pergunta, "impactaram") != NULL){
            printf("\nO impacto do flamengo com suas conquistas recentes não só mudou o patamar do clube mas também forçou outros clubes a responderem a altura, movimentando de forma nunca antes vista o mercado financeiro do futebol brasileiro.\n");
            }
            else if (strstr(pergunta, "estilo") != NULL  && strstr(pergunta, "jogo") != NULL){
                printf("\nDescrevendo o estilo de jogo do Flamengo atualmente, o time se mantém na base do elenco de 2019 de Jorge Jesus, forçando o adversário ao erro com um jogo de pressão intensa e com a posse sempre buscando com a criatividade dos seus jogadores expremer ao máximo de suas habilidades para buscar os gols.\n");
            }
            else if (strstr(pergunta, "planeja") != NULL  && strstr(pergunta, "futur") != NULL){
                printf("\nO Flamengo atual atingiu um patamar sólido e de alto rendimento, acredito que seus planos seja a manutenção disso constanstemente sem perder eficiência, visando aprimoramentos ao longo do caminho.\n");
            }
            else if (strstr(pergunta, "rivalidades") != NULL){
                printf("\nAs rivalidades quando não abordadas com cenas de violência, trazem um ambiente empolgante e comunitário dentre todo os torcedores, as brincadeiras pós-jogo a emoção durante a partida, tudo isso molda um sentimento apaixonante inexplicável ao futebol.\n");
            }
            else if (strstr(pergunta, "prepara") != NULL  && strstr(pergunta, "internacional") != NULL){
                printf("\nA preparação internacional do Flamengo é pensada muito antes do jogo de fato, logística de viagem, descanso dos jogadores, consequências na saúde física do jogador, tudo isso é pensado da melhor forma em prol do Flamengo ter a melhor performance possível alinhada com os resultados desejados no momento pelo clube.\n");
            }
            else if (strstr(pergunta, "torcida") != NULL  && strstr(pergunta, "contribue") != NULL){
                printf("\nA torcida do Flamengo é a alma do clube, é ela que sustenta a receita do clube e da motivação ao Flamengo a continuar sendo o que ele é atualmente.\n");
            }
        } 

        else if (strcmp(questionList(pergunta) , "por que") == 0) {
           // Verifica se a pergunta começa com "por que"
if (strcmp(questionList(pergunta), "por que") == 0) {
            
            /** 
             * Verifica se a pergunta fala sobre "torcida". 
             * Exemplo: "Por que a torcida do Flamengo é considerada a maior do Brasil?"
             */
            if (strstr(pergunta, "torcida") != NULL) {
                printf("Porque o Flamengo tem milhões de torcedores espalhados por todo o Brasil, sendo o clube com a maior torcida do país.");
            } 
            /** 
             * Verifica se a pergunta fala sobre "títulos". 
             * Exemplo: "Por que o Flamengo é um dos clubes com mais títulos no Brasil?"
             */
            else if (strstr(pergunta, "títulos") != NULL) {
                printf("\nPorque o Flamengo conquistou diversos títulos nacionais e internacionais, incluindo várias edições do Campeonato Brasileiro e da Copa Libertadores. sem contar ser o melhor!\n");
            } 
            /** 
             * Verifica se a pergunta fala sobre "Maracanã". 
             * Exemplo: "Por que o Flamengo joga tantas partidas no Maracanã?"
             */
            else if (strstr(pergunta, "Maracanã") != NULL) {
                printf("\nPorque o Maracanã é o estádio mais icônico do Rio de Janeiro e serve como casa histórica para o Flamengo.\n");
            } 
            /** 
             * Verifica se a pergunta fala sobre "Libertadores". 
             * Exemplo: "Por que a conquista da Libertadores de 2019 foi tão especial para o Flamengo?"
             */
            else if (strstr(pergunta, "Libertadores") != NULL) {
                printf("\nPorque marcou o retorno do Flamengo ao topo do futebol sul-americano após 38 anos, com uma vitória emocionante sobre o River Plate.\n");
            } 
            /** 
             * Verifica se a pergunta fala sobre "rivalidade". 
             * Exemplo: "Por que o Flamengo tem tanta rivalidade com o Vasco da Gama?"
             */
            else if (strstr(pergunta, "rivalidade") != NULL) {
                printf("\nPorque os dois clubes são grandes forças do futebol carioca e disputam clássicos históricos e emocionantes.\n");
            } 
            /** 
             * Verifica se a pergunta fala sobre "técnico". 
             * Exemplo: "Por que o técnico Jorge Jesus é tão lembrado pela torcida do Flamengo?"
             */
            else if (strstr(pergunta, "técnico") != NULL) {
                printf("\nPorque Jorge Jesus liderou o Flamengo em 2019, conquistando títulos importantes como a Libertadores e o Brasileirão com um estilo de jogo marcante.\n");
            } 
            /** 
             * Verifica se a pergunta fala sobre "gols". 
             * Exemplo: "Por que o Flamengo é conhecido por marcar muitos gols em decisões importantes?"
             */
            else if (strstr(pergunta, "gols") != NULL) {
                printf("\nPorque o Flamengo sempre contou com grandes atacantes e equipes ofensivas que se destacam em momentos decisivos.\n");
            } 
            /** 
             * Verifica se a pergunta fala sobre "patrimônio". 
             * Exemplo: "Por que o Flamengo é considerado um patrimônio cultural do Rio de Janeiro?"
             */
            else if (strstr(pergunta, "patrimônio") != NULL) {
                printf("\nPorque o Flamengo é mais do que um clube de futebol, sendo parte da identidade cultural e histórica do Rio de Janeiro.\n");
            } 
            /** 
             * Verifica se a pergunta fala sobre "tradição". 
             * Exemplo: "Por que o Flamengo é visto como um dos clubes mais tradicionais do Brasil?"
             */
            else if (strstr(pergunta, "tradição") != NULL) {
                printf("\nPorque o Flamengo tem mais de um século de história, com grandes conquistas e uma base de torcedores apaixonada.\n");
            } 
            /** 
             * Verifica se a pergunta fala sobre "ídolos". 
             * Exemplo: "Por que jogadores como Zico e Gabigol são considerados ídolos do Flamengo?"
             */
            else if (strstr(pergunta, "ídolos") != NULL) {
                printf("\nPorque marcaram épocas importantes do clube, com Zico sendo o maior ídolo da história e Gabigol decisivo nas conquistas recentes.\n");
            }
    }
 
        }
        else if (strcmp(questionList(pergunta) , "qual") == 0) { 
            if(strstr(pergunta, "principal") != NULL && strstr(pergunta, "desafio") != NULL){
                printf("\nManter a constância e o patamar atual do clube todos os anos.\n");
            }
                else if (strstr(pergunta, "momento") != NULL  && strstr(pergunta, "marcante") != NULL){
                    printf("\nÉ impossível definir o momento mais marcante do Flamengo, mas creio que atualmente mundos acreditam que a virada na libertadores de 2019 com 2 gols de Gabigol\n");
                }
                else if (strstr(pergunta, "jogador") != NULL  && strstr(pergunta, "iconico") != NULL){
                    printf("\nO Flamengo tem muitos ícones, creio que os mais icônicos sejam, Zico, Gabigol e Júnior.\n");
                }
                else if (strstr(pergunta, "importancia") != NULL  && strstr(pergunta, "carioca") != NULL){
                    printf("\nO Flamengo é o clube que gera a maior visibilidade ao futebol carioca, sem ele o estado teria uma lacuna muito grande que nenhum outro time poderia supriran");
                }
                else if (strstr(pergunta, "titulo") != NULL  && strstr(pergunta, "importante") != NULL){
                    printf("\nCreio que os títulos mais importantes sejam o Mundial de 1981, e a Libertadores de 2019\n");
                }
                else if (strstr(pergunta, "tecnico") != NULL  && strstr(pergunta, "papel") != NULL){
                    printf("\nNão só dentro de campo, o técnico tem um dos papéis mais relevantes ao clube, administrar o dia a dia e garantir uma performance de alto nível são seus papeis principais e mais conhecidos\n");
                }
                else if (strstr(pergunta, "impacto") != NULL  && strstr(pergunta, "conquistas") != NULL){
                    printf("\nFinanceiramente falando o Flamengo conseguir atingir suas metas de colocações, não só é bom para a história do clube, mas garante o cumprimento da receita\n");
                }
                else if (strstr(pergunta, "novos") != NULL  && strstr(pergunta, "jogadores") != NULL){
                    printf("\nA relevância do Flamengo na criação de novos jogadores não é só para o país mas sim para o mundo do futebol como um todo, hoje o maior jogador Brasileiro é aquele que consegue ser popular o fuciente para gerar uma nova geração de craque inspirados por ele\n");
                }
                else if (strstr(pergunta, "estrategia") != NULL  && strstr(pergunta, "internacional") != NULL){
                    printf("\nSabemos que quando se trata de outros países o nível das competições pode tanto aumentar quanto diminuir, o Flamengo busca investir diversas vezes no mercado internacional\n");
                }
                else if (strstr(pergunta, "torcida") != NULL  && strstr(pergunta, "gestao") != NULL){
                    printf("\nA relação da torcida com a gestão muita das vezes oscila, quando algum jogador influente comenta negativamente sobre a gestão muita das vezes a torcida toma o lado dele, o que poe pressao sobre a gerencia para mudar mesmo medidas razoaveis, portanto temos que tomar muito cuidado com a maneira que a gestao é percebida pelo time, numeros nao sao tudo !\n");
                }
                else{
                    printf("\ndesculpe eu nao reconheço esta pergunta tente refrasea-la\n");
                }
        }
        else
        {
            printf("\nMe desculpe, ainda não reconheço esse tipo de pergunta, poderia realizar uma pergunta diferente?\n");
        }
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

        if (strstr(pergunta, "favorito") != NULL) 
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
    
    else if (strstr(pergunta, "regras") != NULL ) 
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
        else if (strstr(pergunta, "futebol") != NULL)
        {
            printf("\nUma partida de Futebol é dividida em 2 tempos de 45 minutos mais acréscimos, formada por 11 jogadores para cada lado, seu objetivo é marcar mais gols que a equipe adversária.\n");
        }
    }
    return 0;
}