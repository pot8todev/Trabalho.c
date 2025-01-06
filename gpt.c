// Verifica se a pergunta começa com "o que"
if (strcmp(questionList(pergunta), "o que") == 0) {
    
    /** 
     * Verifica se a pergunta fala sobre "Flamengo" e "fundado". 
     * Exemplo: "O que é o Flamengo e quando foi fundado?"
     */
    if (strstr(pergunta, "fundado") != NULL) {
        printf(""); // Preencha com a resposta apropriada.
    } 
    /** 
     * Verifica se a pergunta fala sobre "Flamengo" e "primeiro título". 
     * Exemplo: "O que foi o primeiro título conquistado pelo Flamengo?"
     */
    else if (strstr(pergunta, "primeiro título") != NULL) {
        printf(""); 
    } 
    /** 
     * Verifica se a pergunta fala sobre "Flamengo" e "Libertadores". 
     * Exemplo: "O que representa a Libertadores para o Flamengo?"
     */
    else if (strstr(pergunta, "Libertadores") != NULL) {
        printf(""); 
    } 
    /** 
     * Verifica se a pergunta fala sobre "Flamengo" e "Maracanã". 
     * Exemplo: "O que significa o Maracanã para a história do Flamengo?"
     */
    else if (strstr(pergunta, "Maracanã") != NULL) {
        printf(""); 
    } 
    /** 
     * Verifica se a pergunta fala sobre "Flamengo" e "torcida". 
     * Exemplo: "O que caracteriza a torcida do Flamengo?"
     */
    else if (strstr(pergunta, "torcida") != NULL) {
        printf(""); 
    } 
    /** 
     * Verifica se a pergunta fala sobre "Flamengo" e "Zico". 
     * Exemplo: "O que representa Zico para a história do Flamengo?"
     */
    else if (strstr(pergunta, "Zico") != NULL) {
        printf(""); 
    } 
    /** 
     * Verifica se a pergunta fala sobre "Flamengo" e "time". 
     * Exemplo: "O que faz o Flamengo ser considerado o melhor time do Brasil?"
     */
    else if (strstr(pergunta, "time") != NULL) {
        printf(""); 
    } 
    /** 
     * Verifica se a pergunta fala sobre "Flamengo" e "clássico". 
     * Exemplo: "O que torna os clássicos do Flamengo tão especiais?"
     */
    else if (strstr(pergunta, "clássico") != NULL) {
        printf(""); 
    } 
    /** 
     * Verifica se a pergunta fala sobre "Flamengo" e "história". 
     * Exemplo: "O que marcou a história do Flamengo como um clube de futebol?"
     */
    else if (strstr(pergunta, "história") != NULL) {
        printf(""); 
    } 
    /** 
     * Verifica se a pergunta fala sobre "Flamengo" e "futuro". 
     * Exemplo: "O que podemos esperar do futuro do Flamengo no futebol?"
     */
    else if (strstr(pergunta, "futuro") != NULL) {
        printf(""); 
    }
}

