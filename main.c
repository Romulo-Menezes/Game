#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

SDL_Renderer* render;
 
SDL_Event event;

SDL_Window* Janela = NULL;

SDL_Surface* PlayerSurface;
 
SDL_Texture* PlayerTexture;
 
int Px = 520, Py = 300;
//variaveis da movimentação
int P1x = 0, P1y = 0;

bool Inicio (){

	bool success = true;

	//Inicializando SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0){

		printf( "ERRO! A tela não pode ser inicializada. Erro: %s\n", SDL_GetError());

		success = false;
	}
	else {

		Janela = SDL_CreateWindow ("Jogo 100% boladaço", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE);

		if (Janela == NULL){

		printf ("A janela não pôde ser criada! Erro: %s\n", SDL_GetError());

		success = false;
	}
		else {

			//Obtendo render da janela
			render = SDL_CreateRenderer(Janela, -1, 0);

			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

		}
	}
	return success;
}
 
bool Render (void){

	SDL_RenderClear(render);

	SDL_Rect sRect = {P1x, P1y, 40, 47};

	SDL_Rect dRect = {Px, Py, 96, 116};

	SDL_RenderCopy(render, PlayerTexture, &sRect, &dRect);

	SDL_RenderPresent(render);
}
 
bool XPlayer (void){

	PlayerSurface = IMG_Load("Sprites/Morte.png");

	PlayerTexture = SDL_CreateTextureFromSurface(render, PlayerSurface);
}
 
int main (void){

	//Início//
	SDL_Init (SDL_INIT_EVERYTHING);

	bool Play = true;

	bool esquerda = false, direita = false, cima = false, baixo = false;

	if (!Inicio()){

		printf ("Ocorreu um erro ao iniciar!\n");

	}
	else{

		const int FPS = 24;                    // // // // // //
		const int FrameDelay = 1000 / FPS;    //  Frame Per  //
		unsigned long FrameStart;            //    Second   //
		int FrameTime;                      // // // // // //

			while (Play){

				FrameStart =SDL_GetTicks();

				Render();

				XPlayer();

				while(SDL_PollEvent(&event)){

					//X para fechar
					if (event.type == SDL_QUIT){

						Play = false;

					}
					//Usuário pressionou uma tecla
					if (event.type == SDL_KEYDOWN){

						if (event.key.keysym.sym == SDLK_UP)
							cima = true;

						if (event.key.keysym.sym == SDLK_DOWN)
							baixo = true;

						if (event.key.keysym.sym == SDLK_LEFT)
							esquerda = true;

						if (event.key.keysym.sym == SDLK_RIGHT)
							direita = true;	

					}
					//Usuário parou de pressionar a tecla
					else if (event.type == SDL_KEYUP){

						if (event.key.keysym.sym == SDLK_UP)
							cima = false;

						if (event.key.keysym.sym == SDLK_DOWN)
							baixo = false;

						if (event.key.keysym.sym == SDLK_LEFT)
							esquerda = false;

						if (event.key.keysym.sym == SDLK_RIGHT)
							direita = false;

					}
					//Parte de Lógica
					if (esquerda == true && direita == false && cima == false && baixo == false){

						Px = Px - 6;

						P1y = 47;

						if(P1x < 120){

							P1x += 40;

						}
						else{

							P1x = 0;

						}
					}

					if (direita == true && esquerda == false && cima == false && baixo == false){

						Px = Px + 6;

						P1y = 94;

						if(P1x < 120){

							P1x += 40;

						}
						else{

							P1x = 0;

						}
					}

					if (cima == true && baixo == false && esquerda == false && direita == false){

						Py = Py - 6;

						P1y = 141;

						if(P1x < 120){

							P1x += 40;

						}
						else{

							P1x = 0;

						}
					}

					if (baixo == true && cima == false && esquerda == false && direita == false){

						Py = Py + 6;

						P1y = 0;

						if(P1x < 120){

							P1x += 40;

						}
						else{

							P1x = 0;

						}
					}

					if ((cima == true && baixo == true) || (esquerda == true && direita == true) ||
						(cima == true && esquerda == true) || (cima == true && direita == true) ||
						(baixo == true && esquerda == true) || (baixo == true && direita == true)){

						P1x = 0;
					}

					if(cima == false && baixo == false && esquerda == false && direita == false){

						P1x = 0;

					}
				}

				FrameTime = SDL_GetTicks() - FrameStart;  // // // //
				if (FrameDelay > FrameTime){             //  FPS  //
					SDL_Delay(FrameDelay - FrameTime);  // // // //
				}
			}
	}
    //Destruindo geral
    SDL_DestroyWindow(Janela);

    SDL_DestroyRenderer(render); 

    SDL_DestroyTexture(PlayerTexture);

    SDL_FreeSurface(PlayerSurface);

    //Fim//
    SDL_Quit();
    return 0;
}
