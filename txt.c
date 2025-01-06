char* questionList(char *pergunta);
int main(){
    char *pergunta;
    if (strstr(questionList(pergunta), "como") != NULL) { 
                if strstr(pergunta, "tornou") != NULL  && strstr(pergunta, "maior") != NULL){
                printf("\nNo cenário de torcida, o Flamengo se tornou um dos maiores clubes com a chegada das rádios que no passado tiveram muita influência para o aumento de público do clube, para coroar nessa época teve a chegada da chamada "Década de Ouro" com o elenco de ídolos como Zico, Junior e Companhia. No cenário financeiro, a gestão ecônomica do ex-presidente de clube Eduardo Bandeira de Mello, trouxe a segurança financeira que o clube necessitava para comportar um clube de elite.\n");
                }
                else if(strstr(pergunta, "trajetória") != NULL){
                printf("\nA trajetória do Flamengo não só nesse ano mas nos ultimos anos parece como um sonho para a maioria dos torcedores, em um espaço de uma década o clube foi capaz de arrecadar receitas bilionárias e títulos que antes eram vistos como milagres, no geral, por mais que exista oscilação em temporadas como qualquer outro clube, a trajetória do Flamengo hoje está em um patamar completamente diferente dos das ultimas 2 décadas.\n");
                }
                else if strstr(pergunta, "influencia") != NULL  && strstr(pergunta, "cultura") != NULL){
                    printf("\nHoje o Flamengo praticamente faz parte do dia a dia do carioca, seja conversar com amigos, planejar uma idã ao maracanã, um churrasco de fim de semana, feiras, eventos, sonhos na infância de jovens de todas as classes sociais, não existe mais Flamengo sem Rio de Janeiro e não existe mais Rio de Janeiro sem Flamengo.\n");
                    }
                else if strstr(pergunta, "administra") != NULL  && strstr(pergunta, "torcedores") != NULL){
                printf("\nSatisfazer a maior torcida do Brasil não é fácil e o Flamengo não mede esforços para isso, com parcerias, sócio-torcedor, e filiais em todos os estados, o Flamengo tenta mitigar a distância do torcedor de outro estado da melhor forma possível, garantindo a transmissão dos seus jogos importantes na televisão aberta e buscando sempre a compra do mando de campo de adversários dispostos a cede-lo para garantir a torcida fora do Rio de Janeiro uma experiência emblemática de ver o Flamengo jogar.\n");
                }
                else if strstr(pergunta, "conquistas") != NULL  && strstr(pergunta, "impactaram") != NULL){
                printf("\nO impacto do flamengo com suas conquistas recentes não só mudou o patamar do clube mas também forçou outros clubes a responderem a altura, movimentando de forma nunca antes vista o mercado financeiro do futebol brasileiro.\n");
                }
                else if strstr(pergunta, "estilo") != NULL  && strstr(pergunta, "jogo") != NULL){
                    printf("\nDescrevendo o estilo de jogo do Flamengo atualmente, o time se mantém na base do elenco de 2019 de Jorge Jesus, forçando o adversário ao erro com um jogo de pressão intensa e com a posse sempre buscando com a criatividade dos seus jogadores expremer ao máximo de suas habilidades para buscar os gols.\n);
                }
                else if strstr(pergunta, "planeja") != NULL  && strstr(pergunta, "futuro") != NULL){
                    printf("\nO Flamengo atual atingiu um patamar sólido e de alto rendimento, acredito que seus planos seja a manutenção disso constanstemente sem perder eficiência, visando aprimoramentos ao longo do caminho.\n);
                }
                else if strstr(pergunta, "rivalidades"){
                    printf("\nAs rivalidades quando não abordadas com cenas de violência, trazem um ambiente empolgante e comunitário dentre todo os torcedores, as brincadeiras pós-jogo a emoção durante a partida, tudo isso molda um sentimento apaixonante inexplicável ao futebol.\n);
                }
                else if strstr(pergunta, "prepara") != NULL  && strstr(pergunta, "internacional") != NULL){
                    printf("\nA preparação internacional do Flamengo é pensada muito antes do jogo de fato, logística de viagem, descanso dos jogadores, consequências na saúde física do jogador, tudo isso é pensado da melhor forma em prol do Flamengo ter a melhor performance possível alinhada com os resultados desejados no momento pelo clube.\n);
                }
                else if strstr(pergunta, "torcida") != NULL  && strstr(pergunta, "contribue") != NULL){
                printf("\nA torcida do Flamengo é a alma do clube, é ela que sustenta a receita do clube e da motivação ao Flamengo a continuar sendo o que ele é atualmente.\n");
                }
    }
return 0;
}