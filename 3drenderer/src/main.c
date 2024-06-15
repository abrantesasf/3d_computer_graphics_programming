#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <SDL2/SDL.h>

// Declarações globais:
SDL_Window *janela = NULL;             // ponteiro para uma janela
SDL_Renderer *renderizador = NULL;     // ponteiro para um renderizador
bool esta_rodando = false;             // status de execução do programa
uint32_t *buffer_de_cor = NULL;        // ponteiro para o color buffer
int largura = 800;                     // largura da janela
int altura = 600;                      // altura da janela

// Protótipos de funções:
bool inicializar_janela(void);         // inicializa uma janela
void configurar(void);                 // setup inicial da aplicação
void processar_input(void);            // recebe e processa inputs do usuário
void atualizar(void);                  // atualiza o estado do programa
void renderizar(void);                 // renderiza a aplicação
void destruir_janela(void);            // faz a limpeza de estruturas da memória


// Função main:
int main(void)
{
    esta_rodando = inicializar_janela();

    configurar();

    while (esta_rodando)
    {
        processar_input();
        atualizar();
        renderizar();
    }

    destruir_janela();
    
    return 0;
}



// Definição das funções:
bool inicializar_janela(void)
{
    // Inicializa o ambiente SDL. Podemos inicializar os
    // gráficos, o mouse, o teclado, etc. Iremos, no momento,
    // inicializar tudo:
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Erro na inicialização do SDL.\n");
        return false;
    }

    // Agora temos que criar uma janela SDL. A função que cria a janela
    // tem 6 parâmetros: título, x, y, w, h, flags. Se o título for null,
    // a janela não terá um título.
    janela = SDL_CreateWindow(NULL,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              largura,
                              altura,
                              SDL_WINDOW_BORDERLESS);
    if (!janela)
    {
        fprintf(stderr, "Erro na criação da janela SDL.\n");
        return false;
    }

    // Agora temos que criar um renderer para a janela que foi criada,
    // um renderer que vai acompanhar nossa janela. Temos que passar
    // o ponteiro para a janela, o display onde a janela será exibida (-1
    // significa o display padrão), e flags (0 significa que não tem
    // nenhuma flag especial).
    renderizador = SDL_CreateRenderer(janela, -1, 0);
    if (!renderizador)
    {
        fprintf(stderr, "Erro na criação do renderizador SDL.\n");
    }

    // Se chegamos aqui, conseguimos inicializar o SDL, criamos uma
    // janela e acoplamos um renderizador para essa janela.
    return true;
}


void configurar(void)
{
    buffer_de_cor = (uint32_t *) malloc(sizeof(uint32_t) * largura * altura);
    if (!buffer_de_cor)
    {
        fprintf(stderr, "Erro na alocação do buffer de cor.\n");
    }
}

void processar_input(void)
{
    // Structure para receber os eventos
    SDL_Event evento;

    // Recebe o evento:
    SDL_PollEvent(&evento);

    // Testa o evento recebido:
    switch (evento.type)
    {
        case SDL_QUIT:
            esta_rodando = false;
            break;
        case SDL_KEYDOWN:
            if (evento.key.keysym.sym == SDLK_ESCAPE)
                esta_rodando = false;
            break;
    }
}

void atualizar(void)
{
    
}

void renderizar(void)
{
    // Ajusta a cor do renderer. Tem 5 parâmetros: o renderer, os valores
    // RGB e o valor do alpha (transparência)
    SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255);

    // Agora vamos limpar tudo:
    SDL_RenderClear(renderizador);

    // E agora vamos renderizar:
    SDL_RenderPresent(renderizador);
}

void destruir_janela (void)
{
    free(buffer_de_cor);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();
}
