// gcc -o Jogo Jogo.c -lSDL2 -lSDL2_image -lSDL2_mixer  <-- compilar

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <SDL2/SDL_mixer.h>

#define LARGURA 3200
#define ALTURA 1800
#define PLAYER_w 31 // Largura da sprite
#define PLAYER_h 46 // Altura da sprite

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

SDL_Rect sPlayer = {0, 0, PLAYER_w, PLAYER_h}; //Sprites Player
SDL_Rect dPlayer = {640, 360, 75, 90}; //Movimentação Player
SDL_Rect sMapa = {0, 0, 320, 180}; //Movimento do mapa

bool esquerda = false, direita = false, cima = false, baixo = false;

bool Inicio();
bool Render_Janela ();
bool Render();
bool XPlayer();
void Andar_Tecla();
void Andar_Logic();
void Musicas_Tops();
//bool Colidir_Janela();
void Obter_Fundo ();
void Rolamento_Tela();


int main (){

	SDL_Init (SDL_INIT_EVERYTHING);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

	bool Play = true;

	if (!Inicio()){

		printf ("Ocorreu um erro ao iniciar!\n");

	}
	else{
		Render_Janela ();
		Musicas_Tops();
		const int FPS = 20;                    // // // // // //
		const int FrameDelay = 1000/FPS;      //  Frame Per  //
		unsigned long FrameStart;            //    Second   //
		int FrameTime;                      // // // // // //
		XPlayer();
		Obter_Fundo();

			while (Play){

				FrameStart = SDL_GetTicks();
				Render();

				while(SDL_PollEvent(&event)){

					if (event.type == SDL_QUIT){ //Botão X para fechar
						Play = false;
					}

					Andar_Tecla ();
					//Colidir_Janela();
					Rolamento_Tela();
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

	Background = IMG_Load("Mapa.png");
	Textura_Fundo = SDL_CreateTextureFromSurface (render, Background);
}

bool Render (void){ //Precisa de Render Copy para tudo que for ser exibido na tela

	SDL_RenderClear(render);
	SDL_RenderCopy (render, Textura_Fundo, &sMapa, NULL); // Onde será apresentado, textura do que será apresentado, posição, posição
	SDL_RenderCopy(render, PlayerTexture, &(sPlayer), &(dPlayer));
	SDL_RenderPresent(render);
}

bool XPlayer (void){

	PlayerSurface = IMG_Load("Sprites/Player.png");
	PlayerTexture = SDL_CreateTextureFromSurface(render, PlayerSurface);
}

void Musicas_Tops(){

	Musica = Mix_LoadWAV("Melodia/URSS.mp3");
	Mix_AllocateChannels(8); //Alocar canais para as músicas
	Mix_Volume(1, 8); //Canal e volume do canal, o volume vai de 0 a 10
	Mix_PlayChannel(1, Musica, -1); //Canal que vai tocar, musica que será tocada, quantidade de vezes que será tocada
}

/*bool Colidir_Janela (void){ 	//Colisão com Janela      
     
    if(dPlayer.y + dPlayer.h >= ALTURA){
        baixo = false;
    }
    if(dPlayer.y <= 0){
    	cima = false;
    }
    if(dPlayer.x + dPlayer.w >= LARGURA){
    	direita = false;
    }
    if(dPlayer.x  <= 0){
    	esquerda = false;
    }
}*/

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

	if (baixo == true && direita == false && esquerda == false){
		sPlayer.y = PLAYER_h * 0;
		if(sPlayer.x < PLAYER_w * 3){
			sPlayer.x += PLAYER_w;
		}
		else{sPlayer.x = 0;}
	}

	if (cima == true && direita == false && esquerda == false){
		sPlayer.y = PLAYER_h;
		if(sPlayer.x < PLAYER_w * 3){
			sPlayer.x += PLAYER_w;
		}
		else{sPlayer.x = 0;}
	}

	if (esquerda == true && cima == false && baixo == false){
		sPlayer.y = PLAYER_h * 2;
		if(sPlayer.x < PLAYER_w * 3){
			sPlayer.x += PLAYER_w;
		}
		else{sPlayer.x = 0;}
	}

	if (direita == true && cima == false && baixo == false){
		sPlayer.y = PLAYER_h * 3;
		if(sPlayer.x < PLAYER_w * 3){
			sPlayer.x += PLAYER_w;
		}
		else{sPlayer.x = 0;}
	}

	if(cima == false && baixo == false && esquerda == false && direita == false)
		sPlayer.x = 0;

	if ((cima == true && baixo == true) || (esquerda == true && direita == true)){ 
		sPlayer.x = 0;
	}
}

void Rolamento_Tela(){

	if (baixo == true && direita == false && esquerda == false){
		if(sMapa.y + sMapa.h + 2 <= ALTURA) // colisão da tela
			sMapa.y += 2; // O mapa anda e o player fica parado, so movimenta a sprite
		else
			dPlayer.y += 2; //Quando o mapa chega no fim o player anda
	}

	if (cima == true && direita == false && esquerda == false){
		if(sMapa.y - 2 >= 0)
			sMapa.y -= 2;
		else
			dPlayer.y -= 2;
	}

	if (direita == true && cima == false && baixo == false){
		if(sMapa.x + sMapa.w + 2 <= LARGURA)
			sMapa.x += 2;
		else
			dPlayer.x += 2;
	}

	if (esquerda == true && cima == false && baixo == false){
		if(sMapa.x - 2 >= 0)
			sMapa.x -= 2;
		else
			dPlayer.x -= 2;
	}	
}