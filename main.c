#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

SDL_Renderer* render;
SDL_Event event;
SDL_Window* Janela = NULL;
SDL_Surface* PlayerSurface;
SDL_Texture* PlayerTexture;

SDL_Rect sRect = {0, 0, 40, 47};

SDL_Rect dRect = {520, 300, 76, 96};

bool esquerda = false, direita = false, cima = false, baixo = false;

bool Inicio ();

bool Render ();
 
bool XPlayer ();

void Andar ();

int main (){

	//Início//
	SDL_Init (SDL_INIT_EVERYTHING);

	bool Play = true;

	if (!Inicio()){

		printf ("Ocorreu um erro ao iniciar!\n");

	}
	else{

		const int FPS = 20;                    // // // // // //
		const int FrameDelay = 1000/FPS;      //  Frame Per  //
		unsigned long FrameStart;            //    Second   //
		int FrameTime;                      // // // // // //
		XPlayer();

			while (Play){

				FrameStart = SDL_GetTicks();
				Render();

				while(SDL_PollEvent(&event)){
					//X para fechar
					if (event.type == SDL_QUIT){
						Play = false;
					}

					Andar();

				}
			FrameTime = SDL_GetTicks() - FrameStart;

			if (FrameDelay > FrameTime){             
				SDL_Delay(FrameDelay - FrameTime); 
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

	SDL_RenderCopy(render, PlayerTexture, &(sRect), &(dRect));

	SDL_RenderPresent(render);

	SDL_RenderClear(render);
}

bool XPlayer (void){

	PlayerSurface = IMG_Load("Sprites/Morte.png");

	PlayerTexture = SDL_CreateTextureFromSurface(render, PlayerSurface);
}

void Andar(){
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
		dRect.x -= 4;
		sRect.y = 47;
		if(sRect.x < 120){
			sRect.x += 40;
		}
		else{sRect.x = 0;}
		}

	if (direita == true && esquerda == false && cima == false && baixo == false){
		dRect.x += 4;
		sRect.y = 94;
		if(sRect.x < 120){
			sRect.x += 40;
		}
		else{sRect.x = 0;}
		}

	if (cima == true && baixo == false && esquerda == false && direita == false){
		dRect.y -= 4;
		sRect.y = 141;
		if(sRect.x < 120){
			sRect.x += 40;
		}
		else{sRect.x = 0;}
	}

	if (baixo == true && cima == false && esquerda == false && direita == false){
			dRect.y += 4;
			sRect.y = 0;
		if(sRect.x < 120){
			sRect.x += 40;
		}
		else{sRect.x = 0;}
	}

	if ((cima == true && baixo == true) || (esquerda == true && direita == true) ||
		(cima == true && esquerda == true) || (cima == true && direita == true) ||
		(baixo == true && esquerda == true) || (baixo == true && direita == true)){

			sRect.x = 0;
	}

		if(cima == false && baixo == false && esquerda == false && direita == false){
			sRect.x = 0;
	}
}