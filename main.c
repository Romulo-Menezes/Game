// gcc -o main main.c -lSDL2 -lSDL2_image -lSDL2_mixer  <-- compilar

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <SDL2/SDL_mixer.h>

#define LIMITE 4
#define JANELA_w 1080
#define JANELA_h 640
#define LARGURA 3264
#define ALTURA 1920
#define PLAYER_w 31 // Largura da sprite
#define PLAYER_h 46 // Altura da sprite
int SPEED = 2;

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
SDL_Rect dPlayer = {JANELA_w /2, JANELA_h /2, 65, 80}; //Movimentação Player
SDL_Rect sCamera = {426, 930, 272, 160}; //Movimento da camera
SDL_Rect dCamera = {0, 0, 1080, 640};

int Limitador = 0;
bool esquerda = false, direita = false, cima = false, baixo = false;

typedef struct
{
	int Px;
	int Py;	
} Jogador;
Jogador player;

bool Inicio();
bool Render_Janela ();
bool Render();
bool XPlayer();
void Andar_Tecla();
void Andar_Logic();
void Musicas_Tops();
void Obter_Fundo ();
void Colisao();
void Animacao_Logic();

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
		const int FPS = 24;                    // // // // // //
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
					Colisao();
					Andar_Logic ();
					Animacao_Logic();
					printf("Player x: %d Player y: %d\n", player.Px, player.Py);
					Limitador++;

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
	
	else { Janela = SDL_CreateWindow ("Jogo 100% boladaço", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, JANELA_w, JANELA_h, SDL_WINDOW_RESIZABLE); }

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
	SDL_RenderCopy (render, Textura_Fundo, &sCamera, &dCamera); // Onde será apresentado, textura do que será apresentado, posição, posição
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

void Animacao_Logic(){	//Parte de Lógica

	if (baixo == true && direita == false && esquerda == false){
		sPlayer.y = PLAYER_h * 0;
		if(sPlayer.x < PLAYER_w * 3 && Limitador >= LIMITE){
			sPlayer.x += PLAYER_w;
			Limitador = 0;
		}
		else if(sPlayer.x >= PLAYER_w * 3 && Limitador >= LIMITE){
			sPlayer.x = 0;
			Limitador = 0;
		}
	}

	if (cima == true && direita == false && esquerda == false){
		sPlayer.y = PLAYER_h;
		if(sPlayer.x < PLAYER_w * 3 && Limitador >= LIMITE){
			sPlayer.x += PLAYER_w;
			Limitador = 0;
		}
		else if(sPlayer.x >= PLAYER_w * 3 && Limitador >= LIMITE){
			sPlayer.x = 0;
			Limitador = 0;
		}
	}

	if (esquerda == true && cima == false && baixo == false){
		sPlayer.y = PLAYER_h * 2;
		if(sPlayer.x < PLAYER_w * 3 && Limitador >= LIMITE){
			sPlayer.x += PLAYER_w;
			Limitador = 0;
		}
		else if(sPlayer.x >= PLAYER_w * 3 && Limitador >= LIMITE){
			sPlayer.x = 0;
			Limitador = 0;
		}
	}

	if (direita == true && cima == false && baixo == false){
		sPlayer.y = PLAYER_h * 3;
		if(sPlayer.x < PLAYER_w * 3 && Limitador >= LIMITE){
			sPlayer.x += PLAYER_w;
			Limitador = 0;
		}
		else if(sPlayer.x >= PLAYER_w * 3 && Limitador >= LIMITE){
			sPlayer.x = 0;
			Limitador = 0;
		}
	}

	if(cima == false && baixo == false && esquerda == false && direita == false)
		sPlayer.x = 0;

	if ((cima == true && baixo == true) || (esquerda == true && direita == true)){ 
		sPlayer.x = 0;
	}
}

void Andar_Logic(){

	if (baixo == true && direita == false && esquerda == false){
		if(sCamera.y + sCamera.h + SPEED <= ALTURA && dPlayer.y + dPlayer.h >= JANELA_h/2) // colisão da tela
			sCamera.y += SPEED; // O mapa anda e o player fica parado, so movimenta a sprite
		else if (dPlayer.y + dPlayer.h + SPEED*2 <= JANELA_h)
			dPlayer.y += SPEED*2; //Quando o mapa chega no fim o player anda
	}

	if (cima == true && direita == false && esquerda == false){
		if(sCamera.y - SPEED >= 0 && dPlayer.y <= JANELA_h/2)
			sCamera.y -= SPEED;
		else if (dPlayer.y - 4 >= 0)
			dPlayer.y -= 4;
	}

	if (direita == true && cima == false && baixo == false){
		if(sCamera.x + sCamera.w + SPEED <= LARGURA && dPlayer.x + dPlayer.w >= JANELA_w/2)
			sCamera.x += SPEED;
		else if (dPlayer.x + dPlayer.w + SPEED*2 <= JANELA_w)
			dPlayer.x += SPEED*2;
	}

	if (esquerda == true && cima == false && baixo == false){
		if(sCamera.x - SPEED >= 0 && dPlayer.x <= JANELA_w/2)
			sCamera.x -= SPEED;
		else if (dPlayer.x - SPEED*2 >= 0)
			dPlayer.x -= SPEED*2;
	}
}

void Colisao(){ // tá dando merda isso

	player.Px = dPlayer.x + sCamera.x;  //tá dando merda por causa disso//
	player.Py = dPlayer.y + sCamera.y; /// // // // // // // // // // ///

	if(direita == true){

		if(player.Px + SPEED >= 1020 && player.Px <= 1070 && player.Py >= 1240 && player.Py <= 1258){
			SPEED = 0;
		}
		if(player.Px + SPEED >= 870 && player.Px <= 872 && player.Py >= 1190 && player.Py <= 1246){
			SPEED = 0;
		}		
	}
	else if(cima == true){
		if(player.Py - SPEED <= 1246 && player.Py >= 1190 && player.Px >= 870 && player.Px <= 1236){
			SPEED = 0;
		}
		else if(player.Py - SPEED <= 1260 && player.Py >= 1248 && player.Px >= 1020 && player.Px <= 1070){
			SPEED = 0;
		}
	}
	else if(esquerda == true){
		if(player.Px - SPEED <= 1070 && player.Px >= 1020 && player.Py >= 1240 && player.Py <= 1258){
			SPEED = 0;
		}
		else if(player.Px - SPEED <= 530 && player.Px >= 0 && player.Py >= 424 && player.Py <= 1378){
			SPEED = 0;
		}
	}
	else
		SPEED = 2;

}
