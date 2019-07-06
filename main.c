// gcc -o main main.c -lSDL2 -lSDL2_image -lSDL2_mixer
// git clone https://github.com/romul0/Game.git

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <SDL2/SDL_mixer.h>

#define LIMITE 4
#define JANELA_W 800
#define JANELA_H 600
#define LARGURA 3264
#define ALTURA 1920
#define PLAYER_W 31 // Largura da sprite
#define PLAYER_H 46 // Altura da sprite

//VARIÁVEIS DO MENU

int seletor = 0, menu = 1, how = 1, rank = 1, cred = 1;

int SPEED = 2;

bool Play = true;

int Limitador = 0;

bool esquerda = false, direita = false, cima = false, baixo = false;

//Janela
SDL_Window* Janela = NULL;
SDL_Renderer* render;

SDL_Event event;

//Player
SDL_Surface* PlayerSurface;
SDL_Texture* PlayerTexture;

//Fundo
SDL_Surface* Background;
SDL_Surface* Background_Up;
SDL_Texture* Textura_Fundo;
SDL_Texture* Layer_Up_Fundo;

//Musicas
Mix_Chunk* Musica_1;
Mix_Chunk* Musica_2;
Mix_Chunk* Musica_3;

//Menu 
SDL_Surface* Image_Menu;
SDL_Surface* Image_Box;
SDL_Surface* Image_Control;
SDL_Surface* Image_Ranking;
SDL_Surface* Image_Credits;
SDL_Texture* Textura_Menu;
SDL_Texture* Text_Options_Box;
SDL_Texture* Text_Control;
SDL_Texture* Text_Ranking;
SDL_Texture* Text_Credits;



SDL_Rect sPlayer = {0, 0, PLAYER_W, PLAYER_H}; //Sprites Player
SDL_Rect dPlayer = {JANELA_W /2, JANELA_H /2, 55, 75}; //Movimentação Player

SDL_Rect sCamera = {424, 930, 272, 160}; //Movimento da câmera
SDL_Rect dCamera = {0, 0, 800, 600};


SDL_Rect sBox = {0, 0, 228, 38}; // Sprites da Caixa
SDL_Rect dBox = {285, 320, 228, 38}; // Posição X, Posição Y, Tamanho // OBS: SE MEXER AQUI TEM QUE MEXER NO SWITCH DO SELETOR TBM


typedef struct
{
	int Px;
	int Py;	
} Jogador;

Jogador player;

bool Inicio();
bool Render_Janela ();
void Menu();
void Render_Menu();
void Jogo_Inteiro();
void Ranking();
void HowPlay();
void Credits();
bool Render();
bool XPlayer();
void Andar_Tecla();
void Andar_Logic();
void Musicas_Tops();
void Liberar_Musicas();
void Obter_Fundo();
void Colisao_Fixa();
void Animation_Logic();
void Render_HowPlay ();
void Destruir_Menu ();

int main (){
	SDL_Init (SDL_INIT_EVERYTHING);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

	bool Play = true;

	player.Px = dPlayer.x + sCamera.x;
	player.Py = dPlayer.y + sCamera.y;

	if (!Inicio()){

		printf ("Ocorreu um erro ao iniciar!\n");
	}
	else {
		Render_Janela();
		Menu();
	}
}

bool Inicio (){

	bool success = true;

	//Inicializando SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf( "ERRO! A tela não pode ser inicializada.");
		success = false;
	}
	
	else { Janela = SDL_CreateWindow ("Jogo 100% boladaço", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, JANELA_W, JANELA_H, SDL_WINDOW_RESIZABLE); }

	return success;
}

void Menu (){

	Render_Menu();

	while (menu){

		SDL_RenderCopy (render, Textura_Menu, NULL, NULL);
		SDL_RenderCopy (render, Text_Options_Box, &(sBox), &(dBox));

		SDL_RenderPresent(render);
		SDL_RenderClear(render);

		SDL_Delay(1000/30);

		while(SDL_PollEvent(&event)){

			if (event.type == SDL_QUIT){ //Botão X para fechar
				
				menu = 0;

				Destruir_Menu ();		
			}

			if (event.type == SDL_KEYDOWN){

				if (event.key.keysym.scancode == SDL_SCANCODE_DOWN){

					seletor++;

					if (seletor > 3)
						seletor = 0;
				}		

				if (event.key.keysym.scancode == SDL_SCANCODE_UP){
							
					seletor--;

					if (seletor < 0)
						seletor = 3;
				}		

				if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){ // Return = Tecla ENTER

					if (seletor == 0){
						menu = 0;
						SDL_RenderClear(render);
						Jogo_Inteiro();
					}

					if (seletor == 1){

						SDL_RenderClear(render);
						how = 1;
						SDL_Delay(1000/30);

						while (how){
							HowPlay();
						}
					}

					if (seletor == 2){

						SDL_RenderClear(render);
						rank = 1;
						SDL_Delay(1000/30);

						while (rank){
							Ranking();
						}
					}

					if (seletor == 3){

						SDL_RenderClear(render);
						cred = 1;
						SDL_Delay(1000/30);

						while (cred){
							Credits();
						}
					}
				}
			}

		if (seletor == 0)
			dBox.y = 322; 

		if (seletor == 1)
			dBox.y = 372;

		if (seletor == 2)
			dBox.y = 422;

		if (seletor == 3)
			dBox.y = 472;
	
		}
	}
}

void Destruir_Menu (){

	SDL_FreeSurface(Image_Box);
	SDL_FreeSurface(Image_Ranking);
	SDL_FreeSurface(Image_Credits);
	SDL_FreeSurface(Image_Menu);
	SDL_FreeSurface(Image_Control);
	SDL_DestroyTexture(Textura_Menu);
    SDL_DestroyTexture(Text_Options_Box);
    SDL_DestroyTexture(Text_Ranking);
    SDL_DestroyTexture(Text_Credits);
    SDL_DestroyTexture(Text_Control);
    SDL_DestroyWindow(Janela);
    SDL_Quit();
}

void HowPlay (){

	SDL_RenderClear(render);
	SDL_RenderCopy(render, Text_Control, NULL, NULL);
	SDL_RenderPresent(render);

	while(SDL_PollEvent(&event)){

		if (event.type == SDL_QUIT){ //Fechar e acabar com Geral
			how = 0;
			menu = 0;
			Destruir_Menu ();
		}
		
		if (event.type == SDL_KEYDOWN){

			if (event.key.keysym.sym == SDLK_ESCAPE){
				how = 0;
				seletor = 0;
			}
		}
	}
}


void Ranking (){

	SDL_RenderClear(render);
	SDL_RenderCopy(render, Text_Ranking, NULL, NULL);
	SDL_RenderPresent(render);

	while(SDL_PollEvent(&event)){

		if (event.type == SDL_QUIT){ //Fechar e acabar com Geral
			rank = 0;
			menu = 0;
			Destruir_Menu ();
		}
		
		if (event.type == SDL_KEYDOWN){

			if (event.key.keysym.sym == SDLK_ESCAPE){
				rank = 0;
				seletor = 0;
			}
		}
	}
}

void Credits (){

	SDL_RenderClear(render);
	SDL_RenderCopy(render, Text_Credits, NULL, NULL);
	SDL_RenderPresent(render);

	while(SDL_PollEvent(&event)){

		if (event.type == SDL_QUIT){ //Fechar e acabar com Geral
			cred = 0;
			menu = 0;
			Destruir_Menu ();
		}
		
		if (event.type == SDL_KEYDOWN){

			if (event.key.keysym.sym == SDLK_ESCAPE){
				cred = 0;
				seletor = 0;
			}
		}
	}
}

void Jogo_Inteiro (){

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
			Colisao_Fixa();
			Andar_Logic ();
			Animation_Logic();
			
			printf("Player x: %d Player y: %d\n", player.Px, player.Py);
			Limitador++;

		}
		
		FrameTime = SDL_GetTicks() - FrameStart;

		if (FrameDelay > FrameTime){             
			SDL_Delay(FrameDelay - FrameTime); 
		}
	}	

	Liberar_Musicas();
	SDL_FreeSurface(PlayerSurface);
    SDL_FreeSurface(Background);

    Mix_CloseAudio();

    //Destruindo coisas do Menu também
    SDL_FreeSurface(Image_Box);
	SDL_FreeSurface(Image_Menu);
	SDL_FreeSurface(Image_Control);
	SDL_DestroyTexture(Textura_Menu);
	SDL_DestroyTexture(Text_Options_Box);
    SDL_DestroyTexture(Text_Control);

    //Destruindo geral
    SDL_DestroyRenderer(render); 
    SDL_DestroyTexture(PlayerTexture);
    SDL_DestroyTexture(Textura_Fundo);
    SDL_DestroyWindow(Janela);
    
    //Fim//
    SDL_Quit();
}

void Render_Menu (void){ // Colocar aqui as imagens e texturas que serão carregadas para serem usadas nas coisas do menu
	Image_Menu = IMG_Load("Resources/Image/Menu.png");
	Textura_Menu = SDL_CreateTextureFromSurface(render, Image_Menu);

	Image_Box = IMG_Load("Resources/Image/Borda.png");
	Text_Options_Box = SDL_CreateTextureFromSurface(render, Image_Box);

	Image_Control = IMG_Load("Resources/Image/Controles.png");
	Text_Control = SDL_CreateTextureFromSurface(render, Image_Control);

	Image_Ranking = IMG_Load("Resources/Image/Recordes.png");
	Text_Ranking = SDL_CreateTextureFromSurface(render, Image_Ranking);

	Image_Credits = IMG_Load("Resources/Image/Creditos.png");
	Text_Credits = SDL_CreateTextureFromSurface(render, Image_Credits);

}

bool Render_Janela (void){

	render = SDL_CreateRenderer(Janela, -1, 0); //Obtendo render da janela
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
}

void Obter_Fundo (void){ //Imagem de fundo

	Background = IMG_Load("Resources/Image/Mapa.png");
	Background_Up = IMG_Load("Resources/Image/LayerUpMapa.png");
	Textura_Fundo = SDL_CreateTextureFromSurface (render, Background);
	Layer_Up_Fundo = SDL_CreateTextureFromSurface (render, Background_Up);
}

bool Render (void){ //Precisa de Render Copy para tudo que for ser exibido na tela

	SDL_RenderClear(render);
	SDL_RenderCopy (render, Textura_Fundo, &sCamera, &dCamera); // Onde será apresentado, textura do que será apresentado, posição, posição
	SDL_RenderCopy(render, PlayerTexture, &(sPlayer), &(dPlayer));
	SDL_RenderCopy (render, Layer_Up_Fundo, &sCamera, &dCamera);
	SDL_RenderPresent(render);
}

bool XPlayer (void){

	PlayerSurface = IMG_Load("Resources/Sprites/Player.png");
	PlayerTexture = SDL_CreateTextureFromSurface(render, PlayerSurface);
}

void Musicas_Tops(){

	Musica_1 = Mix_LoadWAV("Melodia/The Wolven Storm.mp3");
	Musica_2 = Mix_LoadWAV("Melodia/Sword of Destiny.mp3");
	Musica_3 = Mix_LoadWAV("Melodia/Potência.mp3");
	Mix_AllocateChannels(8); //Alocar canais para as músicas
	Mix_Volume(1, 7); //Canal e volume do canal, o volume vai de 0 a 10
	Mix_Volume(2, 6);

	srand (time(NULL));

	int music = ((rand()) % 3);

	if (music == 0)
		Mix_PlayChannel(2, Musica_1, 1); //Canal que vai tocar, musica que será tocada, quantidade de vezes que será tocada.

	else if (music == 1)
		Mix_PlayChannel(2, Musica_2, 1);

	else if (music == 2)
		Mix_PlayChannel(1, Musica_3, 1);
}

void Liberar_Musicas (void){

	Mix_FreeChunk(Musica_1);
	Mix_FreeChunk(Musica_2);
	Mix_FreeChunk(Musica_3);
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

void Animation_Logic(){	//Parte de Lógica

	if (baixo == true && direita == false && esquerda == false){
		sPlayer.y = PLAYER_H * 0;
		if(sPlayer.x < PLAYER_W * 3 && Limitador >= LIMITE){
			sPlayer.x += PLAYER_W;
			Limitador = 0;
		}
		else if(sPlayer.x >= PLAYER_W * 3 && Limitador >= LIMITE){
			sPlayer.x = 0;
			Limitador = 0;
		}
	}

	if (cima == true && direita == false && esquerda == false){
		sPlayer.y = PLAYER_H;
		if(sPlayer.x < PLAYER_W * 3 && Limitador >= LIMITE){
			sPlayer.x += PLAYER_W;
			Limitador = 0;
		}
		else if(sPlayer.x >= PLAYER_W * 3 && Limitador >= LIMITE){
			sPlayer.x = 0;
			Limitador = 0;
		}
	}

	if (esquerda == true && cima == false && baixo == false){
		sPlayer.y = PLAYER_H * 2;
		if(sPlayer.x < PLAYER_W * 3 && Limitador >= LIMITE){
			sPlayer.x += PLAYER_W;
			Limitador = 0;
		}
		else if(sPlayer.x >= PLAYER_W * 3 && Limitador >= LIMITE){
			sPlayer.x = 0;
			Limitador = 0;
		}
	}

	if (direita == true && cima == false && baixo == false){
		sPlayer.y = PLAYER_H * 3;
		if(sPlayer.x < PLAYER_W * 3 && Limitador >= LIMITE){
			sPlayer.x += PLAYER_W;
			Limitador = 0;
		}
		else if(sPlayer.x >= PLAYER_W * 3 && Limitador >= LIMITE){
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

		if(sCamera.y + sCamera.h + SPEED <= ALTURA && dPlayer.y == JANELA_H/2){
			sCamera.y += SPEED;
			player.Py += SPEED; 
		}

		else if (dPlayer.y + dPlayer.h + SPEED <= JANELA_H){
			dPlayer.y += SPEED;
			player.Py += SPEED; 
		}
	}

	if (cima == true && direita == false && esquerda == false){

		if(sCamera.y - SPEED >= 0 && dPlayer.y <= JANELA_H/2){
			sCamera.y -= SPEED;
			player.Py -= SPEED; 
		}

		else if (dPlayer.y - 2 >= 0){
			dPlayer.y -= SPEED;
			player.Py -= SPEED; 
		}
	}

	if (direita == true && cima == false && baixo == false){

		if(sCamera.x + sCamera.w + SPEED <= LARGURA && dPlayer.x == JANELA_W/2){
			sCamera.x += SPEED;
			player.Px += SPEED; 
		}

		else if (dPlayer.x + dPlayer.w + SPEED <= JANELA_W){
			dPlayer.x += SPEED;
			player.Px += SPEED; 
		}
	}

	if (esquerda == true && cima == false && baixo == false){

		if(sCamera.x - SPEED >= 0 && dPlayer.x <= JANELA_W/2){
			sCamera.x -= SPEED;
			player.Px-= SPEED;
		} 

		else if (dPlayer.x - SPEED >= 0){
			dPlayer.x -= SPEED;
			player.Px -= SPEED; 
		}
	}
}

void Colisao_Fixa(){

	int Posx1, Posx2, Posy1, Posy2, i;

	if(cima == true){

		FILE *C_top = fopen("Resources/Collision/C_top.txt","r");

		for(i = 0; i < 26; i++){

			fscanf(C_top, "%d %d %d", &Posy1, &Posx1, &Posx2);

			if(player.Py == Posy1 && player.Px < Posx1 && player.Px > Posx2){
				SPEED = 0;
				break;
			}
			else{
				SPEED = 2;
			}
		}

		fclose(C_top);
	}
	else if (esquerda == true){

		FILE *C_left = fopen("Resources/Collision/C_left.txt","r");	

		for(i = 0; i < 23; i++){

			fscanf(C_left, "%d %d %d", &Posx1, &Posy1, &Posy2);

			if(player.Px == Posx1 && player.Py < Posy1 && player.Py > Posy2){
				SPEED = 0;
				break;
			}
			else{
				SPEED = 2;
			}
		}

		fclose(C_left);
	}
	else if (direita == true){

		FILE *C_right = fopen("Resources/Collision/C_right.txt","r");

		for(i = 0; i < 20; i++){

			fscanf(C_right, "%d %d %d", &Posx1, &Posy1, &Posy2);

			if(player.Px == Posx1 && player.Py < Posy1 && player.Py > Posy2){
				SPEED = 0;
				break;
			}
			else{
				SPEED = 2;
			}
		}

		fclose(C_right);
	}
	else if (baixo == true){

		FILE *C_down = fopen("Resources/Collision/C_down.txt","r");

			for(i = 0; i < 16; i++){

			fscanf(C_down, "%d %d %d", &Posy1, &Posx1, &Posx2);

			if(player.Py == Posy1 && player.Px < Posx1 && player.Px > Posx2){
				SPEED = 0;
				break;
			}
			else{
				SPEED = 2;
			}
		}

		fclose(C_down);
	}
}