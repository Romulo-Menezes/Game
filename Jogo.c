#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <SDL2/SDL_mixer.h>

#define LARGURA 1280
#define ALTURA 720

SDL_Renderer* render;
SDL_Event event;
SDL_Window* Janela = NULL;
SDL_Surface* PlayerSurface;
SDL_Surface* Background = NULL;
SDL_Texture* PlayerTexture;
Mix_Chunk* Musica;
SDL_Surface* Background;
SDL_Texture* Textura_Fundo;
//SDL_Surface *surface

SDL_Rect sRect = {0, 0, 40, 47}; //Sprites
SDL_Rect dRect = {620, 300, 76, 96}; //Movimentação

bool esquerda = false, direita = false, cima = false, baixo = false;

bool Inicio();
bool Render_Janela ();
bool Render();
bool XPlayer();
void Andar_Tecla();
void Andar_Logic();
void Musicas_Tops();
bool Colidir_Janela();
void Obter_Fundo ();


int main (){

	SDL_Init (SDL_INIT_EVERYTHING);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

	bool Play = true;

	if (!Inicio()){

		printf ("Ocorreu um erro ao iniciar!\n");

	}
	else{
		Render_Janela ();
		//Imagem_Fundo ();
		const int FPS = 20;                    // // // // // //
		const int FrameDelay = 1000/FPS;      //  Frame Per  //
		unsigned long FrameStart;            //    Second   //
		int FrameTime;                      // // // // // //
		XPlayer();
		Musicas_Tops();
		Obter_Fundo();

			while (Play){

				FrameStart = SDL_GetTicks();
				Render();

				while(SDL_PollEvent(&event)){

					if (event.type == SDL_QUIT){ //Botão X para fechar
						Play = false;
					}

					Andar_Tecla ();
					Colidir_Janela();
					Andar_Logic ();

				}
			FrameTime = SDL_GetTicks() - FrameStart;

			if (FrameDelay > FrameTime){             
				SDL_Delay(FrameDelay - FrameTime); 
			}
			}	
	}
	Mix_FreeChunk(Musica);
	SDL_FreeSurface(PlayerSurface);
    SDL_FreeSurface(Background);

    //Destruindo geral
    Mix_CloseAudio();
    SDL_DestroyWindow(Janela);
    SDL_DestroyRenderer(render); 
    SDL_DestroyTexture(PlayerTexture);
    SDL_DestroyTexture(Textura_Fundo);


    //Fim//
    SDL_Quit();
    return 0;
}

bool Inicio (){

	bool success = true;

	//Inicializando SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf( "ERRO! A tela não pode ser inicializada.");
		success = false;
	}
	
	else { Janela = SDL_CreateWindow ("Jogo 100% boladaço", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE); }

	return success;
}

bool Render_Janela (void){

	render = SDL_CreateRenderer(Janela, -1, 0); //Obtendo render da janela
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
}

void Obter_Fundo (void){ //Imagem de fundo

	Background = IMG_Load("URSS.jpg");
	Textura_Fundo = SDL_CreateTextureFromSurface (render, Background);
}

bool Render (void){ //Precisa de Render Copy para tudo que for ser exibido na tela

	SDL_RenderClear(render);
	SDL_RenderCopy (render, Textura_Fundo, NULL, NULL); // Onde será apresentado, textura do que será apresentado, posição, posição
	SDL_RenderCopy(render, PlayerTexture, &(sRect), &(dRect));
	SDL_RenderPresent(render);
}

bool XPlayer (void){

	PlayerSurface = IMG_Load("Sprites/Morte.png");
	PlayerTexture = SDL_CreateTextureFromSurface(render, PlayerSurface);
}

void Musicas_Tops(){

	Musica = Mix_LoadWAV("Melodia/URSS.mp3");
	Mix_AllocateChannels(8); //Alocar canais para as músicas
	Mix_Volume(1, 5); //Canal e volume do canal, o volume vai de 0 a 10
	Mix_PlayChannel(1, Musica, -1); //Canal que vai tocar, musica que será tocada, quantidade de vezes que será tocada
}

bool Colidir_Janela (void){ 	//Colisão com Janela      
     
    if(dRect.y + dRect.h >= ALTURA){
        baixo = false;
    }
    if(dRect.y <= 0){
    	cima = false;
    }
    if(dRect.x + dRect.w >= LARGURA){
    	direita = false;
    }
    if(dRect.x  <= 0){
    	esquerda = false;
    }
}

void Andar_Tecla(){
	
	if (event.type == SDL_KEYDOWN){ //Usuário pressionou  uma tecla

		if (event.key.keysym.sym == SDLK_UP)
			cima = true;
		if (event.key.keysym.sym == SDLK_DOWN)
			baixo = true;
		if (event.key.keysym.sym == SDLK_LEFT)
			esquerda = true;
		if (event.key.keysym.sym == SDLK_RIGHT)
			direita = true;	
	}
	
	else if (event.type == SDL_KEYUP){ //Usuário parou de pressionar a tecla

		if (event.key.keysym.sym == SDLK_UP)
			cima = false;
		if (event.key.keysym.sym == SDLK_DOWN)
			baixo = false;
		if (event.key.keysym.sym == SDLK_LEFT)
			esquerda = false;
		if (event.key.keysym.sym == SDLK_RIGHT)
			direita = false;
	}
}

void Andar_Logic(){	//Parte de Lógica

	if (esquerda == true && direita == false && cima == false && baixo == false){
		dRect.x -= 5;
		sRect.y = 47;
		if(sRect.x < 120){
			sRect.x += 40;
		}
		else{sRect.x = 0;}
		}

	if (direita == true && esquerda == false && cima == false && baixo == false){
		dRect.x += 5;
		sRect.y = 94;
		if(sRect.x < 120){
			sRect.x += 40;
		}
		else{sRect.x = 0;}
	}

	if (cima == true && baixo == false && esquerda == false && direita == false){
		dRect.y -= 5;
		sRect.y = 141;
		if(sRect.x < 120){
			sRect.x += 40;
		}
		else{sRect.x = 0;}
	}

	if (baixo == true && cima == false && esquerda == false && direita == false){
			dRect.y += 5;
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