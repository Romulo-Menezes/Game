// gcc -o main main.c -lSDL2 -lSDL2_image -lSDL2_mixer
// git clone https://github.com/romul0/Game.git

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <SDL2/SDL_mixer.h>

#define JANELA_W 800
#define JANELA_H 600
#define PLAYER_W 31 // Largura da sprite
#define PLAYER_H 46 // Altura da sprite

//VARIÁVEIS DO MENU

int seletor = 0, menu = 1, how = 1, rank = 1, cred = 1;

//Variaveis do "ESC"

int escolha = 0, pause = 1;

//VARIÁVEIS DO MENU DA MORTE

int again = 0, morreu = 0;

int Muda_Mapa = 1;
int LARGURA = 3264;
int ALTURA = 1920;
int LIMITE = 8;

int SPEED = 2;

bool Play = true, Ataque = false;

int Limitador = 0;
int Passos = 1;
int Imunidade = 0, Imunidade_Mob = 0, Golem_M = 0, Golem_Vida = 10;
int Boss_Vida = 20;

int mob0 = 2, mob1 = 2, mob2 = 2, mob3 = 2, mob4 = 2;

int Contador = 0;
int Contador_Ataque = 0;
int Limitador_Ataque = 0;
int Pos_Ataque;

bool esquerda = false, direita = false, cima = false, baixo = false;
bool colidiu = false;

//Janela
SDL_Window* Janela = NULL;
SDL_Renderer* render;

SDL_Event event;

//Player
SDL_Surface* PlayerSurface;
SDL_Texture* PlayerTexture;

SDL_Surface* EsqueletoSurface;
SDL_Texture* EsqueletoTexture;

SDL_Surface* MagicaLR_Surface;
SDL_Surface* MagicaTD_Surface;
SDL_Texture* MagicaLR;
SDL_Texture* MagicaTD;

SDL_Rect dMagiaLR = {-100, -100, 60, 30};
SDL_Rect dMagiaTD = {-100, -100, 30, 60};
SDL_Rect sMagiaLR = {0, 0, 30, 15};
SDL_Rect sMagiaTD = {0, 0, 15, 30};

SDL_Surface* GolemS;
SDL_Texture* Golem;
SDL_Surface* BOSS_S;
SDL_Texture* BOSS;

SDL_Rect sBoss = {0, 0, 25, 45};
SDL_Rect dBoss = {374, 100, 55, 75};
SDL_Rect sGolem = {0 , 0, 33, 53};
SDL_Rect dGolem = {-1240, -780, 95, 115};

//Fundo
SDL_Surface* Background;
SDL_Surface* Background_Up;
SDL_Surface* CavernaS;
SDL_Surface* Sala_FinalS;
SDL_Surface* Caverna_PortaS;
SDL_Texture* Textura_Fundo;
SDL_Texture* Layer_Up_Fundo;
SDL_Texture* Caverna;
SDL_Texture* Porta_Caverna;
SDL_Texture* Sala_Final;

//HUD
SDL_Surface* HUD_Surface;
SDL_Surface* Vida_Surface;
SDL_Surface* Chave_S;
SDL_Surface* Vida_Golem_S;
SDL_Surface* Vida_Boss_S;

SDL_Texture* HUD;
SDL_Texture* Vida;
SDL_Texture* Chave_T;
SDL_Texture* Vida_Golem_T;
SDL_Texture* Vida_Boss_T;

SDL_Rect sVida_Boss = {0, 0, 800, 600};
SDL_Rect sVida_Golem = {0, 0, 800, 600};
SDL_Rect dVida_Golem = {0, 0, 800, 600};
SDL_Rect sVida = {0, 0, 800, 600};
SDL_Rect dVida = {0, 0, 800, 600};

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

//Menu ESC
SDL_Surface* Image_Esc;
SDL_Texture* Text_Esc;
SDL_Surface* Image_BordaEsc;
SDL_Texture* Text_BordaEsc;

//Menu Morte
SDL_Surface* Image_MenuMorte;
SDL_Texture* Text_MenuMorte;
SDL_Surface* Image_MorteBorda;
SDL_Texture* Text_MorteBorda;

SDL_Rect sEsqueleto = {0, 0, PLAYER_W, PLAYER_H};
SDL_Rect dEsqueleto = {JANELA_W, JANELA_H, 55, 75};

SDL_Rect dMob1 = {JANELA_W, JANELA_H, 55, 75};
SDL_Rect dMob2 = {JANELA_W, JANELA_H, 55, 75};
SDL_Rect dMob3 = {JANELA_W, JANELA_H, 55, 75};
SDL_Rect dMob4 = {JANELA_W, JANELA_H, 55, 75};
SDL_Rect dMob5 = {JANELA_W, JANELA_H, 55, 75};

SDL_Rect sMob1 = {0, 0, PLAYER_W, PLAYER_H};
SDL_Rect sMob3 = {0, 0, PLAYER_W, PLAYER_H};
SDL_Rect sMob4 = {0, 0, PLAYER_W, PLAYER_H};
SDL_Rect sMob5 = {0, 0, PLAYER_W, PLAYER_H};

SDL_Rect sPlayer = {0, 0, PLAYER_W, PLAYER_H}; //Sprites Player
SDL_Rect dPlayer = {JANELA_W/2, JANELA_H/2, 55, 75}; //Movimentação Player

SDL_Rect sCamera = {424, 930, 272, 160}; //Movimento da câmera
SDL_Rect dCamera = {0, 0, 800, 600};


SDL_Rect sBox = {0, 0, 228, 38}; // Sprites da Caixa
SDL_Rect dBox = {285, 320, 228, 38}; // Posição X, Posição Y, Tamanho // OBS: SE MEXER AQUI TEM QUE MEXER NO SWITCH DO SELETOR TBM

SDL_Rect sEsc = {0, 0, 115, 50}; // Sprites da caixa seletora do ESC
SDL_Rect dEsc = {267, 326, 115, 50}; 

SDL_Rect sBordaMorte = {0, 0, 180, 85}; // Sprites da caixa seletora do ESC
SDL_Rect dBordaMorte = {145, 340, 180, 85}; 


typedef struct
{
	int Px;
	int Py;
	int Vida;
	int Chave;	
} Entidade;


Entidade player;

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
void Inimigo ();
void Inimigo_Anda();
void Inimigo_Animacao();
void Colisao_Inimigo();
void Muda_Vida();
void MudancaDeMapa();
void Obter_Esc();
void ESC();
void Player_Ataque();
void Ataque_False();
void Movimento_Magia();
void Inimigo_Dano();
void Inimigo_Morto();
void Reset();
void Pos_Golem();
void Golem_Movimento();
void Golem_Hit();
void Golem_Dano();
void Colisa_Mundo3();
void Boss_movimento();
void Boss_Dano();
void Boss_Hit();
//----------------------------------------------------------------------------------------------

int main (){

	SDL_Init (SDL_INIT_EVERYTHING);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

	bool Play = true;

	if (!Inicio()){

		printf ("Ocorreu um erro ao iniciar!\n");
	}
	else {
		Render_Janela();
		Menu();
	}

	Liberar_Musicas();
    Mix_CloseAudio();

	//Destruindo e liberando geral
	SDL_FreeSurface(PlayerSurface);
	SDL_FreeSurface(Background);
	SDL_FreeSurface(Background_Up);
	SDL_FreeSurface(EsqueletoSurface);
	SDL_FreeSurface(CavernaS);
	SDL_FreeSurface(Sala_FinalS);
	SDL_FreeSurface(Image_Esc);
	SDL_FreeSurface(Image_BordaEsc);
	SDL_FreeSurface(HUD_Surface);
	SDL_FreeSurface(Vida_Surface);
	SDL_FreeSurface(Image_MenuMorte);
	SDL_FreeSurface(Image_MorteBorda);

	SDL_DestroyTexture(PlayerTexture);
	SDL_DestroyTexture(Text_MorteBorda);
	SDL_DestroyTexture(HUD);
	SDL_DestroyTexture(Vida);
	SDL_DestroyTexture(Text_MenuMorte);
	SDL_DestroyTexture(Caverna);
	SDL_DestroyTexture(Layer_Up_Fundo);
	SDL_DestroyTexture(Textura_Fundo);
	SDL_DestroyTexture(Sala_Final);
	SDL_DestroyTexture(Text_Esc);
	SDL_DestroyTexture(Text_BordaEsc);

	SDL_DestroyRenderer(render); 
	SDL_DestroyWindow(Janela);

	//Fim//
	SDL_Quit();

}
//-----------------------------------------------------------------------------------------------

bool Inicio (){

	bool success = true;

	//Inicializando SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf( "ERRO! A tela não pode ser inicializada.");
		success = false;
	}
	
	else { Janela = SDL_CreateWindow ("Jogo 100% Boladaço", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, JANELA_W, JANELA_H, SDL_WINDOW_RESIZABLE); }

	return success;
}

void Menu (){

	Render_Menu();

	menu = 1;

	while (menu){

		SDL_RenderCopy (render, Textura_Menu, NULL, NULL);
		SDL_RenderCopy (render, Text_Options_Box, &(sBox), &(dBox));

		SDL_RenderPresent(render);
		SDL_RenderClear(render);

		SDL_Delay(1000/30);

		while(SDL_PollEvent(&event)){

			if (event.type == SDL_QUIT){ //Botão X para fechar
				
				menu = 0;	
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

	Destruir_Menu ();
	SDL_Quit();	
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
			SDL_Quit();
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
			SDL_Quit();
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
			SDL_Quit();
		}
		
		if (event.type == SDL_KEYDOWN){

			if (event.key.keysym.sym == SDLK_ESCAPE){
				cred = 0;
				seletor = 0;
			}
		}
	}
}

//**************************************************************************************************************
void Jogo_Inteiro (){

	Reset();

	player.Px = dPlayer.x + sCamera.x;
	player.Py = dPlayer.y + sCamera.y;
	player.Vida = 30;

	mob0 = 2; mob1 = 2;	mob2 = 2; mob3 = 2;	mob4 = 2;

	Play = true;
	Musicas_Tops();
	const float FPS = 60;                    // // // // // //
	const float FrameDelay = 1000/FPS;      //  Frame Per  //
	unsigned long FrameStart;              //    Second   //
	float FrameTime;                      // // // // // //
	XPlayer();
	Obter_Fundo();
	Obter_Esc();

	while (Play){

		FrameStart = SDL_GetTicks();
		
		Render();

		while(SDL_PollEvent(&event)){

			if (event.type == SDL_KEYDOWN){
				if (event.key.keysym.sym == SDLK_q)
					Ataque = true;
			}
		
			MudancaDeMapa();
			Andar_Tecla ();
			ESC();
		}

		Ataque_False();

		if (Muda_Mapa != 3){
			Colisao_Fixa();
		}
		if (Muda_Mapa == 3){
			Colisa_Mundo3();
			Boss_movimento();
			Boss_Dano();
			Boss_Hit();
		}
		Andar_Logic ();
		Pos_Golem();
		Golem_Movimento();
		Golem_Hit();

		if (colidiu == false){
			Animation_Logic();
		}

		Player_Ataque();
		Movimento_Magia();

		Inimigo ();
		Inimigo_Anda();
		Colisao_Inimigo();
		Inimigo_Morto();
		Muda_Vida();

		if (Imunidade != 0)
			Imunidade--;

		if (Imunidade_Mob != 0)
			Imunidade_Mob--;

		Limitador++;
		Contador ++;
		Passos++;
		//printf("C.x: %d C.w: %d\nC.y: %d C.h: %d\n\n",sCamera.x, sCamera.w +sCamera.x, sCamera.y, sCamera.h+sCamera.y);
		printf("Player X: %d Player Y:%d\n", player.Px, player.Py);
		//printf("mob1: %d mob2: %d mob3: %d mob4: %d mob5: %d\n", mob0, mob1, mob2, mob3, mob4);


		if(Limitador_Ataque == 1)
			Contador_Ataque++;
		
		FrameTime = SDL_GetTicks() - FrameStart;
		if (FrameDelay > FrameTime){             
			SDL_Delay(FrameDelay - FrameTime); 
		}
	}	
}
//********************************************************************************************************************

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

void Obter_Esc (void){
	Image_Esc = IMG_Load("Resources/Image/MenuESC.png");
	Text_Esc = SDL_CreateTextureFromSurface(render, Image_Esc);

	Image_BordaEsc = IMG_Load("Resources/Image/BordaESC.png");
	Text_BordaEsc = SDL_CreateTextureFromSurface(render, Image_BordaEsc);
}

void ESC (){

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT){

		pause = 1;

		while (pause){

			while(SDL_PollEvent(&event)){

				if (escolha == 0){
					dEsc.x = 267;
				}

				if (escolha == 1){
					dEsc.x = 417;
				}

				if (event.type == SDL_KEYDOWN){

					if (event.key.keysym.sym == SDLK_LEFT){
								
						escolha--;

						if (escolha < 0)
							escolha = 0;
					}

					if (event.key.keysym.sym == SDLK_RIGHT){
								
						escolha++;

						if (escolha > 1)
							escolha = 1;
					}

					if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){
								
						if (escolha == 0){ // 0 é o lado esquerdo e é SIM
							pause = 0;
							Play = false;
						}
								
						if (escolha == 1){
							pause = 0;
						}
					}
				}

				SDL_RenderCopy(render, Text_Esc, NULL, NULL);
				SDL_RenderCopy(render, Text_BordaEsc, &sEsc, &dEsc);
				SDL_RenderPresent(render);
			}
		}
	}
}

void Obter_Fundo (void){ //Imagem de fundo

	Background = IMG_Load("Resources/Image/Mapa.png");
	Background_Up = IMG_Load("Resources/Image/LayerUpMapa.png");
	Textura_Fundo = SDL_CreateTextureFromSurface (render, Background);
	Layer_Up_Fundo = SDL_CreateTextureFromSurface (render, Background_Up);

	CavernaS = IMG_Load("Resources/Image/Caverna_Mapa.png");
	Caverna_PortaS = IMG_Load("Resources/Image/Caverna_Porta.png");
	Sala_FinalS = IMG_Load("Resources/Image/Sala_Final.png");
	Caverna = SDL_CreateTextureFromSurface(render, CavernaS);
	Porta_Caverna = SDL_CreateTextureFromSurface(render, Caverna_PortaS);
	Sala_Final = SDL_CreateTextureFromSurface(render, Sala_FinalS);

	HUD_Surface = IMG_Load("Resources/Image/HUD.png");
	Vida_Surface = IMG_Load("Resources/Image/Vida.png");
	Vida_Golem_S = IMG_Load("Resources/Image/Vida_Golem.png");
	Chave_S = IMG_Load("Resources/Image/Chave.png");
	Vida_Boss_S =IMG_Load("Resources/Image/Boss_Vida.png");

	HUD = SDL_CreateTextureFromSurface(render, HUD_Surface);
	Vida = SDL_CreateTextureFromSurface(render, Vida_Surface);
	Vida_Golem_T = SDL_CreateTextureFromSurface(render, Vida_Golem_S);
	Chave_T = SDL_CreateTextureFromSurface(render, Chave_S);
	Vida_Boss_T = SDL_CreateTextureFromSurface (render, Vida_Boss_S);

	Image_MenuMorte = IMG_Load("Resources/Image/MorteMenu.png");
	Text_MenuMorte = SDL_CreateTextureFromSurface(render, Image_MenuMorte);
	Image_MorteBorda = IMG_Load("Resources/Image/MorteBorda.png");
	Text_MorteBorda = SDL_CreateTextureFromSurface(render, Image_MorteBorda);
}

bool Render (void){ //Precisa de Render Copy para tudo que for ser exibido na tela

	SDL_RenderClear(render);
	if(Muda_Mapa == 1){
		SDL_RenderCopy (render, Textura_Fundo, &sCamera, &dCamera); // Onde será apresentado, textura do que será apresentado, posição, posição
		SDL_RenderCopy(render, PlayerTexture, &(sPlayer), &(dPlayer));

		SDL_RenderCopy(render, EsqueletoTexture, &sEsqueleto, &dEsqueleto);
		SDL_RenderCopy(render, EsqueletoTexture, &sMob1, &dMob1);
		//SDL_RenderCopy(render, EsqueletoTexture, &sEsqueleto, &dMob2);
		SDL_RenderCopy(render, EsqueletoTexture, &sMob3, &dMob3);
		SDL_RenderCopy(render, EsqueletoTexture, &sMob4, &dMob4);
		SDL_RenderCopy(render, EsqueletoTexture, &sMob5, &dMob5);
		SDL_RenderCopy(render, Golem, &sGolem, &dGolem);

		SDL_RenderCopy(render, MagicaLR, &sMagiaLR, &dMagiaLR); // esquerda e direita
		SDL_RenderCopy(render, MagicaTD, &sMagiaTD, &dMagiaTD); // cima e baixo

		SDL_RenderCopy (render, Layer_Up_Fundo, &sCamera, &dCamera);

		SDL_RenderCopy (render, Vida, &sVida, &dVida);
		if (Golem_M == 1)
			SDL_RenderCopy (render, Vida_Golem_T, &sVida_Golem, &dVida_Golem);

		SDL_RenderCopy (render, HUD, NULL, NULL);

		if (player.Chave == 1)
			SDL_RenderCopy (render, Chave_T, NULL, NULL);

	}
	else if(Muda_Mapa == 2){

		SDL_RenderCopy(render,Caverna, &sCamera, &dCamera);
		SDL_RenderCopy(render,Porta_Caverna, &sCamera, &dCamera);
		SDL_RenderCopy(render, PlayerTexture, &sPlayer, &dPlayer);

		SDL_RenderCopy(render, MagicaLR, &sMagiaLR, &dMagiaLR); // esquerda e direita
		SDL_RenderCopy(render, MagicaTD, &sMagiaTD, &dMagiaTD); // cima e baixo

		SDL_RenderCopy (render, Vida, &sVida, &dVida);
		SDL_RenderCopy (render, HUD, NULL, NULL);
		if (player.Chave == 1)
			SDL_RenderCopy(render, Chave_T, NULL, NULL);
	}

	else if(Muda_Mapa == 3){

		SDL_RenderCopy(render,Sala_Final, &sCamera, &dCamera);
		SDL_RenderCopy(render, PlayerTexture, &sPlayer, &dPlayer);

		SDL_RenderCopy (render, BOSS, &sBoss, &dBoss);

		SDL_RenderCopy(render, MagicaLR, &sMagiaLR, &dMagiaLR); // esquerda e direita
		SDL_RenderCopy(render, MagicaTD, &sMagiaTD, &dMagiaTD); // cima e baixo

		SDL_RenderCopy (render, Vida, &sVida, &dVida);
		SDL_RenderCopy (render, HUD, NULL, NULL);

		if (Boss_Vida > 0)
			SDL_RenderCopy (render, Vida_Boss_T, &sVida_Boss, &dVida_Golem);

		if (player.Chave == 1)
			SDL_RenderCopy(render, Chave_T, NULL, NULL);

	}
	SDL_RenderPresent(render);
}

bool XPlayer (void){

	PlayerSurface = IMG_Load("Resources/Sprites/Player.png");
	PlayerTexture = SDL_CreateTextureFromSurface(render, PlayerSurface);

	MagicaLR_Surface = IMG_Load("Resources/Image/Magia_LR.png");
	MagicaLR = SDL_CreateTextureFromSurface(render, MagicaLR_Surface);
	MagicaTD_Surface = IMG_Load("Resources/Image/Magia_TD.png");
	MagicaTD = SDL_CreateTextureFromSurface(render, MagicaTD_Surface);

	EsqueletoSurface = IMG_Load("Resources/Sprites/Esqueleto.png");
	EsqueletoTexture = SDL_CreateTextureFromSurface(render, EsqueletoSurface);

	GolemS = IMG_Load("Resources/Sprites/Golem.png");
	Golem = SDL_CreateTextureFromSurface(render, GolemS);

	BOSS_S = IMG_Load("Resources/Sprites/boss.png");
	BOSS = SDL_CreateTextureFromSurface(render, BOSS_S);

}

void Musicas_Tops(){

	Musica_1 = Mix_LoadWAV("Resources/Melodias/Musica1.mp3");
	Musica_2 = Mix_LoadWAV("Resources/Melodias/Musica2.mp3");
	Musica_3 = Mix_LoadWAV("Resources/Melodias/Musica3.mp3");
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
		 else if (event.key.keysym.sym == SDLK_DOWN)
			baixo = true;
		else if (event.key.keysym.sym == SDLK_LEFT)
			esquerda = true;
		else if (event.key.keysym.sym == SDLK_RIGHT)
			direita = true;	
	}
	
	else if (event.type == SDL_KEYUP){ //Usuário parou de pressionar a tecla

		if (event.key.keysym.sym == SDLK_UP)
			cima = false;
		else if (event.key.keysym.sym == SDLK_DOWN)
			baixo = false;
		else if (event.key.keysym.sym == SDLK_LEFT)
			esquerda = false;
		else if (event.key.keysym.sym == SDLK_RIGHT)
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

	int Posx1, Posx2, Posy1, Posy2, i, vezes = 0;

	if(cima == true){

		FILE *C_top;

		if(Muda_Mapa == 1){

			C_top = fopen("Resources/Collision/C_top1.txt","r");

			vezes = 26;
		}
		else if(Muda_Mapa == 2){

			C_top = fopen("Resources/Collision/C_top2.txt","r");

			vezes = 10;
		}

		for(i = 0; i < vezes; i++){

			fscanf(C_top, "%d %d %d", &Posy1, &Posx1, &Posx2);

			if(player.Py == Posy1 && player.Px < Posx1 && player.Px > Posx2){
				SPEED = 0;
				colidiu = true;
				break;
			}
			else{
				colidiu = false;
				SPEED = 2;
			}
		}

		fclose(C_top);
	}
	else if (esquerda == true){

		FILE *C_left;

		if(Muda_Mapa == 1){

			C_left = fopen("Resources/Collision/C_left1.txt","r");

			vezes = 23;
		}
		else if(Muda_Mapa == 2){

			C_left = fopen("Resources/Collision/C_left2.txt","r");

			vezes = 9;
		}

		for(i = 0; i < vezes; i++){

			fscanf(C_left, "%d %d %d", &Posx1, &Posy1, &Posy2);

			if(player.Px == Posx1 && player.Py < Posy1 && player.Py > Posy2){
				SPEED = 0;
				colidiu = true;
				break;
			}
			else{
				colidiu = false;
				SPEED = 2;
			}
		}

		fclose(C_left);
	}
	else if (direita == true){

		FILE *C_right;

		if(Muda_Mapa == 1){

			C_right = fopen("Resources/Collision/C_right1.txt","r");

			vezes = 20;
		}
		else if(Muda_Mapa == 2){

			C_right = fopen("Resources/Collision/C_right2.txt","r");

			vezes = 7;
		}

		for(i = 0; i < vezes; i++){

			fscanf(C_right, "%d %d %d", &Posx1, &Posy1, &Posy2);

			if(player.Px == Posx1 && player.Py < Posy1 && player.Py > Posy2){
				SPEED = 0;
				colidiu = true;
				break;
			}
			else{
				colidiu = false;
				SPEED = 2;
			}
		}

		fclose(C_right);
	}
	else if (baixo == true){

		FILE *C_down;

		if (Muda_Mapa == 1){

			C_down = fopen("Resources/Collision/C_down1.txt","r");

			vezes = 16;
		}
		else if (Muda_Mapa == 2){

			C_down = fopen("Resources/Collision/C_down2.txt","r");

			vezes = 11;
		}

		for(i = 0; i < vezes; i++){

			fscanf(C_down, "%d %d %d", &Posy1, &Posx1, &Posx2);

			if(player.Py == Posy1 && player.Px < Posx1 && player.Px > Posx2){
				SPEED = 0;
				colidiu = true;
				break;
			}
			else{
				colidiu = false;
				SPEED = 2;
			}
		}

		fclose(C_down);
	}

	if (Golem_Vida > 0 && direita == true && player.Px == 2318 && player.Py >= 0 && player.Py <= 666){
			SPEED = 0;
			colidiu = true;
		}
	else if (Golem_Vida <= 0 && direita == true && player.Px == 2318 && player.Py >= 0 && player.Py <= 666){
		SPEED = 2;
		colidiu = false;
		}
}

void MudancaDeMapa (){

	if(Muda_Mapa == 1 && player.Px >= 3136 && player.Px <= 3168 && player.Py == 1348){

		if (event.type == SDL_KEYDOWN){

			if (event.key.keysym.sym == SDLK_e){

				Muda_Mapa = 2;

				ALTURA = 1200;

				LARGURA = 800;

				sCamera.x = 184; sCamera.y = 890; sCamera.w = 400; sCamera.h = 300;

				player.Px = dPlayer.x + sCamera.x; player.Py = dPlayer.y + sCamera.y;

				SPEED = 2;					
			}
		}
	}

	if(Muda_Mapa == 2 && player.Px >= 542 && player.Px <= 630 && player.Py == 1194){

		if(event.type == SDL_KEYDOWN){

			if(event.key.keysym.sym == SDLK_e){

				Muda_Mapa = 1;

				ALTURA = 1920;

				LARGURA = 3264;

				sCamera.x = 2752; sCamera.y = 1048; sCamera.w = 272; sCamera.h = 160;

				player.Px = dPlayer.x + sCamera.x; player.Py = dPlayer.y + sCamera.y;

				SPEED =2;
			}
		}
	}

	if(player.Chave == 1 && Muda_Mapa == 2 && player.Px >= 568 && player.Px <= 603 && player.Py == 230){

		if(event.type == SDL_KEYDOWN){

			if(event.key.keysym.sym == SDLK_e){

				Muda_Mapa = 3;

				colidiu = false;

				ALTURA = 300;

				LARGURA = 400;

				sCamera.x = 0; sCamera.y = 0; sCamera.w = 400; sCamera.h = 300;

				dPlayer.x = 374; dPlayer.y = 422;

				player.Px = dPlayer.x + sCamera.x; player.Py = dPlayer.y + sCamera.y;

				SPEED = 2;
			}
		}
	}
}

void Inimigo(){

	if(mob0 > 0 && sCamera.x >= 408 && sCamera.x +sCamera.w <= 952 && sCamera.y >= 26 && sCamera.y + sCamera.h <= 346){
		if (direita == true && esquerda == false && cima == false && baixo == false)
			dEsqueleto.x -= SPEED*3;
		if (esquerda == true && direita == false && cima == false && baixo == false)
			dEsqueleto.x += SPEED*3;
		if (cima == true && baixo == false && direita == false && esquerda == false)
			dEsqueleto.y += SPEED*4;
		if (baixo == true && cima == false && direita == false && esquerda == false)
			dEsqueleto.y -= SPEED*4;

		Inimigo_Dano(&dEsqueleto, &mob0);
	}
	else if (sCamera.x < 408){
		dEsqueleto.x = JANELA_W;
		dEsqueleto.y = JANELA_H/2;
	}
	else if (sCamera.x > 650){
		dEsqueleto.x = -10 - dEsqueleto.w;
		dEsqueleto.y = JANELA_H/2;		
	}

	if(mob1 > 0 && sCamera.x >= 854 && sCamera.x +sCamera.w <= 1398 && sCamera.y >= 124 && sCamera.y + sCamera.h <= 444){
		if (direita == true && esquerda == false && cima == false && baixo == false)
			dMob1.x -= SPEED*3;
		if (esquerda == true && direita == false && cima == false && baixo == false)
			dMob1.x += SPEED*3;
		if (cima == true && baixo == false && direita == false && esquerda == false)
			dMob1.y += SPEED*4;
		if (baixo == true && cima == false && direita == false && esquerda == false)
			dMob1.y -= SPEED*4;
		Inimigo_Dano(&dMob1, &mob1);
	}
	else if (sCamera.x < 854){
		dMob1.x = JANELA_W;
		dMob1.y = JANELA_H/2;
	}
	else if (sCamera.x > 1000){
		dMob1.x = -10 - dMob1.w;
		dMob1.y = JANELA_H/2;	
	}

	if(mob2 > 0 && sCamera.x >= 2470 && sCamera.x +sCamera.w <= 3182 && sCamera.y >= 256 && sCamera.y + sCamera.h <= 582){
		if (direita == true && esquerda == false && cima == false && baixo == false)
			dMob3.x -= SPEED*3;
		if (esquerda == true && direita == false && cima == false && baixo == false)
			dMob3.x += SPEED*3;
		if (cima == true && baixo == false && direita == false && esquerda == false)
			dMob3.y += SPEED*4;
		if (baixo == true && cima == false && direita == false && esquerda == false)
			dMob3.y -= SPEED*4;
		Inimigo_Dano(&dMob3, &mob2);
	}
	else if (sCamera.x < 2470){
		dMob3.x = JANELA_W;
		dMob3.y = JANELA_H/2 + 150;
	}
	else if (sCamera.x > 3182){
		dMob3.x = -10 - dMob1.w;
		dMob3.y = JANELA_H/2 + 150;		
	}

	if(mob3 > 0 && sCamera.x >= 228  && sCamera.x +sCamera.w <= 772 && sCamera.y >= 1584 && sCamera.y + sCamera.h <= 1956){
		if (direita == true && esquerda == false && cima == false && baixo == false)
			dMob4.x -= SPEED*3;
		if (esquerda == true && direita == false && cima == false && baixo == false)
			dMob4.x += SPEED*3;
		if (cima == true && baixo == false && direita == false && esquerda == false)
			dMob4.y += SPEED*4;
		if (baixo == true && cima == false && direita == false && esquerda == false)
			dMob4.y -= SPEED*4;
		Inimigo_Dano(&dMob4, &mob3);
	}
	else if (sCamera.x < 228){
		dMob4.x = JANELA_W;
		dMob4.y = JANELA_H/2;
	}
	else if (sCamera.x > 550){
		dMob4.x = -10 - dMob1.w;
		dMob4.y = JANELA_H/2;	
	}

	if(mob4 > 0 && sCamera.x >= 2182  && sCamera.x +sCamera.w <= 2726 && sCamera.y >= 1582 && sCamera.y + sCamera.h <= 1920){
		if (direita == true && esquerda == false && cima == false && baixo == false)
			dMob5.x -= SPEED*3;
		if (esquerda == true && direita == false && cima == false && baixo == false)
			dMob5.x += SPEED*3;
		if (cima == true && baixo == false && direita == false && esquerda == false)
			dMob5.y += SPEED*4;
		if (baixo == true && cima == false && direita == false && esquerda == false)
			dMob5.y -= SPEED*4;
		Inimigo_Dano(&dMob5, &mob4);
	}
	else if (sCamera.x < 2182){
		dMob5.x = JANELA_W;
		dMob5.y = JANELA_H/2;
	}
	else if (sCamera.x > 2400){
		dMob5.x = -10 - dMob1.w;
		dMob5.y = JANELA_H/2;	
	}

}
void Inimigo_Anda(){

	if (Passos <= 80){

		dEsqueleto.y -= SPEED;

		dMob1.y -= SPEED;

		dMob3.y -= SPEED;

		dMob4.y -= SPEED;

		dMob5.y -= SPEED;
	}
	else if (Passos <= 240){

		dEsqueleto.y += SPEED;

		dMob1.y += SPEED;

		dMob3.y += SPEED;

		dMob4.y += SPEED;

		dMob5.y += SPEED;		
	}
	else{
		Passos = -80;
	}

	Inimigo_Animacao(&sEsqueleto);
	Inimigo_Animacao(&sMob1);
	Inimigo_Animacao(&sMob3);
	Inimigo_Animacao(&sMob4);
	Inimigo_Animacao(&sMob5);

}

void Colisao_Inimigo (){

	// MOB 0 
	if (dPlayer.y >= dEsqueleto.y && dPlayer.y <= dEsqueleto.y + dEsqueleto.h && Imunidade == 0){
		if(dPlayer.x + dPlayer.w >= dEsqueleto.x && dPlayer.x <= dEsqueleto.x + dEsqueleto.w){
			player.Vida -= 5;
			Imunidade = 100;
		}
	}
	if (dPlayer.x >= dEsqueleto.x && dPlayer.x <= dEsqueleto.x + dEsqueleto.w && Imunidade == 0){
		if(dPlayer.y + dPlayer.h >= dEsqueleto.y && dPlayer.y <= dEsqueleto.y + dEsqueleto.h){
			player.Vida -= 5;
			Imunidade = 100;
		}
	}
	// MOB 1
	if (dPlayer.y >= dMob1.y && dPlayer.y <= dMob1.y + dMob1.h && Imunidade == 0){
		if(dPlayer.x + dPlayer.w >= dMob1.x && dPlayer.x <= dMob1.x + dMob1.w){
			player.Vida -= 5;
			Imunidade = 100;
		}
	}
	if (dPlayer.x >= dMob1.x && dPlayer.x <= dMob1.x + dMob1.w && Imunidade == 0){
		if(dPlayer.y + dPlayer.h >= dMob1.y && dPlayer.y <= dMob1.y + dMob1.h){
			player.Vida -= 5;
			Imunidade = 100;
		}
	}
	//MOB 2
	if (dPlayer.y >= dMob3.y && dPlayer.y <= dMob3.y + dMob3.h && Imunidade == 0){
		if(dPlayer.x + dPlayer.w >= dMob3.x && dPlayer.x <= dMob3.x + dMob3.w){
			player.Vida -= 5;
			Imunidade = 100;
		}
	}
	if (dPlayer.x >= dMob3.x && dPlayer.x <= dMob3.x + dMob3.w && Imunidade == 0){
		if(dPlayer.y + dPlayer.h >= dMob3.y && dPlayer.y <= dMob3.y + dMob3.h){
			player.Vida -= 5;
			Imunidade = 100;
		}
	}
	//MOB 3
	if (dPlayer.y >= dMob4.y && dPlayer.y <= dMob4.y + dMob4.h && Imunidade == 0){
		if(dPlayer.x + dPlayer.w >= dMob4.x && dPlayer.x <= dMob4.x + dMob4.w){
			player.Vida -= 5;
			Imunidade = 100;
		}
	}
	if (dPlayer.x >= dMob4.x && dPlayer.x <= dMob4.x + dMob4.w && Imunidade == 0){
		if(dPlayer.y + dPlayer.h >= dMob4.y && dPlayer.y <= dMob4.y + dMob4.h){
			player.Vida -= 5;
			Imunidade = 100;
		}
	}
	//MOB 4
	if (dPlayer.y >= dMob5.y && dPlayer.y <= dMob5.y + dMob5.h && Imunidade == 0){
		if(dPlayer.x + dPlayer.w >= dMob5.x && dPlayer.x <= dMob5.x + dMob5.w){
			player.Vida -= 5;
			Imunidade = 100;
		}
	}
	if (dPlayer.x >= dMob5.x && dPlayer.x <= dMob5.x + dMob5.w && Imunidade == 0){
		if(dPlayer.y + dPlayer.h >= dMob5.y && dPlayer.y <= dMob5.y + dMob5.h){
			player.Vida -= 5;
			Imunidade = 100;
		}
	}
}

void Muda_Vida(){

	if(player.Vida == 25){
		sVida.y = 600;
	}
	else if (player.Vida == 20){
		sVida.y = 1200;
	}
	else if (player.Vida == 15){
		sVida.y = 1800;
	}
	else if (player.Vida == 10){
		sVida.y = 2400;
	}
	else if (player.Vida == 5){
		sVida.y = 3000;
	}
	else if (player.Vida <= 0){
		
				morreu = 1;

		while (morreu){

			while(SDL_PollEvent(&event)){

				if (event.type == SDL_KEYDOWN){

					if (again == 0){
						dBordaMorte.x = 145;
					}

					if (again == 1){
						dBordaMorte.x = 455;
					}

					if (event.key.keysym.sym == SDLK_LEFT){
											
						again--;

						if (again < 0){
							again = 1;
						}
					}
					
					if (event.key.keysym.sym == SDLK_RIGHT){
											
						again++;

						if (again > 1){
							again = 0;
						}
					}

					if (event.key.keysym.scancode == SDL_SCANCODE_RETURN){
											
						if (again == 0){ // 0 é o lado esquerdo e é SIM
							morreu = 0;
							Play = false;
						}
											
						if (again == 1){
							morreu = 0;
							Play = false;
						}
					}
				}

				SDL_RenderClear(render);
				SDL_RenderCopy(render, Text_MenuMorte, NULL, NULL);
				SDL_RenderCopy(render, Text_MorteBorda, &sBordaMorte, &dBordaMorte);
				SDL_RenderPresent(render);
					
			}
		}
	}

	if(Imunidade != 0){
		if(sVida.x != 800){
			if(Limitador <= LIMITE){
				sVida.x += 800;
			}
			else{
				Limitador = 0;
			}
		}
		else{
			sVida.x = 0;
		}
	}
	else{
		sVida.x = 0;
	}
}

void Inimigo_Animacao(SDL_Rect *mob){

	if(Passos >= -80 && Passos <= 80){
		mob->y = PLAYER_H;
		if(mob->x < PLAYER_W * 3 && Contador >= LIMITE){
			mob->x += PLAYER_W;
		}
		else if(mob->x >= PLAYER_W * 3 && Contador >= LIMITE){
			Contador = 0;
			mob->x = 0;
		}
	}
	else{
		mob->y = 0;
		if(mob->x < PLAYER_W * 3 && Contador >= LIMITE){
			mob->x += PLAYER_W;
		}
		else if(mob->x >= PLAYER_W * 3 && Contador >= LIMITE){
			Contador = 0;
			mob->x = 0;
		}
	}

}

void Player_Ataque(){

	if(Ataque == true){
		if (sPlayer.y == 0 && Limitador_Ataque == 0){// cima
			dMagiaTD.y = dPlayer.y + dPlayer.h;
			dMagiaTD.x = dPlayer.x;
			sMagiaTD.x = 15;
			Limitador_Ataque = 1;
			Pos_Ataque = 1;

		}
		else if (sPlayer.y == PLAYER_H && Limitador_Ataque == 0){ // baixo
			dMagiaTD.y = dPlayer.y - dMagiaTD.h;
			dMagiaTD.x = dPlayer.x + 30;
			sMagiaTD.x = 0;
			Limitador_Ataque = 1;
			Pos_Ataque = 2;

		}
		else if (sPlayer.y == PLAYER_H * 2 && Limitador_Ataque == 0){ // esquerda
			dMagiaLR.x = dPlayer.x - dMagiaLR.w;
			dMagiaLR.y = dPlayer.y + 30;
			sMagiaLR.y = 15;
			Limitador_Ataque = 1;
			Pos_Ataque = 3;

		}
		else if (sPlayer.y == PLAYER_H * 3 && Limitador_Ataque == 0){ // direita
			dMagiaLR.x = dPlayer.x + dPlayer.w;
			dMagiaLR.y = dPlayer.y + 30;
			sMagiaLR.y = 0;
			Limitador_Ataque = 1;
			Pos_Ataque = 4;

		}
	}
}

void Movimento_Magia(){
	if (Pos_Ataque == 1 && Limitador_Ataque == 1){

		if(Contador_Ataque <= 60){
			dMagiaTD.y += 4;
		}
		else{
			Contador_Ataque = 0;
			Limitador_Ataque = 0;
			Ataque = false;
		}

	}

	if (Pos_Ataque == 2 && Limitador_Ataque == 1){

		if(Contador_Ataque <= 60){
			dMagiaTD.y -= 4;
		}
		else{
			Contador_Ataque = 0;
			Limitador_Ataque = 0;
			Ataque = false;
		}

	}

	if (Pos_Ataque == 3 && Limitador_Ataque == 1){

		if(Contador_Ataque <= 60){
			dMagiaLR.x -= 4;
		}
		else{
			Contador_Ataque = 0;
			Limitador_Ataque = 0;
			Ataque = false;
		}

	}

	if (Pos_Ataque == 4 && Limitador_Ataque == 1){

		if(Contador_Ataque <= 60){
			dMagiaLR.x += 4;
		}
		else{
			Contador_Ataque = 0;
			Limitador_Ataque = 0;
			Ataque = false;
		}

	}
}

void Ataque_False(){

	if (Ataque == false){
		dMagiaTD.x = -100;
		dMagiaLR.x = -100;
	}

}

void Inimigo_Dano(SDL_Rect *mob, int *vida){

	if (dMagiaLR.y + dMagiaLR.h  >= mob->y && dMagiaLR.y <= mob->y + mob->h && Imunidade_Mob == 0){
		if(dMagiaLR.x + dMagiaLR.w >= mob->x && dMagiaLR.x <= mob->x + mob->w){
			*vida -= 1;
			Imunidade_Mob = 50;
			dMagiaLR.x = -500;
		}
	}
	else if (dMagiaLR.x + dMagiaLR.w >= mob->x && dMagiaLR.x <= mob->x + mob->w && Imunidade_Mob == 0){
		if(dMagiaLR.y + dMagiaLR.h >= mob->y && dMagiaLR.y <= mob->y + mob->h){
			*vida -= 1;
			Imunidade_Mob = 50;
			dMagiaLR.x = -500;

		}
	}

	else if (dMagiaTD.y + dMagiaTD.h >= mob->y && dMagiaTD.y <= mob->y + mob->h && Imunidade_Mob == 0){
		if(dMagiaTD.x + dMagiaTD.w >= mob->x && dMagiaTD.x <= mob->x + mob->w){
			*vida -= 1;
			Imunidade_Mob = 50;
			dMagiaTD.x = -500;

		}
	}
	else if (dMagiaTD.x + dMagiaTD.w >= mob->x && dMagiaTD.x <= mob->x + mob->w && Imunidade_Mob == 0){
		if(dMagiaTD.y + dMagiaTD.h >= mob->y && dMagiaTD.y <= mob->y + mob->h){
			*vida -= 1;
			Imunidade_Mob = 50;
			dMagiaTD.x = -500;

		}
	}
}

void Inimigo_Morto(){

	if(mob0 <= 0)
		dEsqueleto.x = -200;

	if(mob1 <= 0)
		dMob1.x = -200;

	if(mob2 <= 0)
		dMob3.x = -200;

	if(mob3 <= 0)
		dMob4.x = -200;

	if(mob4 <= 0)
		dMob5.x = -200;
}

void Reset(){

	Boss_Vida = 20;
	player.Chave = 0;
	seletor = 0; menu = 1, how = 1, rank = 1, cred = 1;
	escolha = 0; pause = 1;
	again = 0; morreu = 0;
	Muda_Mapa = 1;
	LARGURA = 3264;
	ALTURA = 1920;
	LIMITE = 8;
	SPEED = 2;
	Play = true, Ataque = false;
	Limitador = 0;
	Passos = 1;
	Imunidade = 0, Imunidade_Mob = 0;
	Contador = 0;
	Contador_Ataque = 0;
	Limitador_Ataque = 0;
	Pos_Ataque;
	esquerda = false; direita = false; cima = false; baixo = false;
	colidiu = false;


	dMagiaLR.x = -100; dMagiaLR.y = -100; dMagiaLR.w = 60; dMagiaLR.h = 30;
	dMagiaTD.x = -100; dMagiaTD.y = -100; dMagiaTD.w = 30; dMagiaTD.h = 60;

	sMagiaLR.x = 0; sMagiaLR.y = 0; sMagiaLR.w = 30; sMagiaLR.h = 15;
	sMagiaTD.x = 0; sMagiaTD.y = 0; sMagiaTD.w = 15; sMagiaTD.h = 30;
	
	sVida.x = 0; sVida.y = 0; sVida.w = 800; sVida.h = 600;
	dVida.x = 0; dVida.y = 0; dVida.w = 800; dVida.h = 600;

	sEsqueleto.x = 0; sEsqueleto.y = 0; sEsqueleto.w = PLAYER_W; sEsqueleto.h = PLAYER_H;
	dEsqueleto.x = JANELA_W; dEsqueleto.y = JANELA_H; dEsqueleto.w = 55; dEsqueleto.h = 75;

	dMob1.x = JANELA_W; dMob1.y = JANELA_H; dMob1.w = 55; dMob1.h = 75;
	dMob3.x = JANELA_W; dMob3.y = JANELA_H; dMob3.w = 55; dMob3.h = 75;
	dMob4.x = JANELA_W; dMob4.y = JANELA_H; dMob4.w = 55; dMob4.h = 75;
	dMob5.x = JANELA_W; dMob5.y = JANELA_H; dMob5.w = 55; dMob5.h = 75;

	sMob1.x = 0; sMob1.y = 0; sMob1.w = PLAYER_W; sMob1.h = PLAYER_H;
	sMob3.x = 0; sMob3.y = 0; sMob3.w = PLAYER_W; sMob3.h = PLAYER_H;
	sMob4.x = 0; sMob4.y = 0; sMob4.w = PLAYER_W; sMob4.h = PLAYER_H;
	sMob5.x = 0; sMob5.y = 0; sMob5.w = PLAYER_W; sMob5.h = PLAYER_H;

	sPlayer.x = 0; sPlayer.y = 0; sPlayer.w = PLAYER_W; sPlayer.h = PLAYER_H;
	dPlayer.x = JANELA_W/2; dPlayer.y = JANELA_H/2; dPlayer.w = 55; dPlayer.h = 75;

	sCamera.x = 424; sCamera.y = 930; sCamera.w = 272; sCamera.h = 160;
	dCamera.x = 0; dCamera.y = 0; dCamera.w = 800; dCamera.h = 600;

	dGolem.x = -10 - dGolem.w;
	dGolem.y = JANELA_H/2;
	Golem_Vida = 10;
	sGolem.y = 0; sGolem.x = 0;
}

void Pos_Golem(){
	if(Golem_Vida > 0 && player.Px >= 1962 && player.Py >= 0 && player.Py <= 660 && player.Px <= 2318){
		if (direita == true && esquerda == false && cima == false && baixo == false)
			dGolem.x -= SPEED*3;
		if (esquerda == true && direita == false && cima == false && baixo == false)
			dGolem.x += SPEED*3;
		if(cima == true && esquerda == false && direita == false && baixo == false)
			dGolem.y += SPEED*4;
		if(baixo == true && esquerda == false && direita == false && cima == false)
			dGolem.y -= SPEED*4;

		Golem_M = 1;

		Golem_Dano();
	}
	else{
		Golem_M = 0;
	}

}

void Golem_Movimento(){

	if(Golem_M == 1 && dGolem.x > dPlayer.x)
		dGolem.x -= 1;
	if(Golem_M == 1 && dGolem.x < dPlayer.x)
		dGolem.x += 1;
	if(Golem_M == 1 && dGolem.y > dPlayer.y && dGolem.x == dPlayer.x)
		dGolem.y -= 1;
	if(Golem_M == 1 && dGolem.y < dPlayer.y && dGolem.x == dPlayer.x)
		dGolem.y += 1;

	if (Golem_Vida == 10){
		sVida_Golem.y = 0;
	}
	if (Golem_Vida == 8){
		sVida_Golem.y = 600;
	}
	if (Golem_Vida == 6){
		sVida_Golem.y = 1200;
	}
	if (Golem_Vida == 4){
		sVida_Golem.y = 1800;
	}
	if (Golem_Vida == 2){
		sVida_Golem.y = 2400;
	}
	if(Golem_Vida <= 0){
		dGolem.x = -1000;
		player.Chave = 1;
	}

}

void Golem_Hit(){

	if (dPlayer.x + dPlayer.w >= dGolem.x && dPlayer.x <= dGolem.x + dGolem.w && Imunidade == 0){
		if (dPlayer.y + dPlayer.w >= dGolem.y && dPlayer.y <= dGolem.y + dGolem.h){
			player.Vida -= 10;
			Imunidade = 100;
		}
	}

	if (dPlayer.y + dPlayer.w >= dGolem.y && dPlayer.y <= dGolem.y + dGolem.h && Imunidade == 0){
		if (dPlayer.x + dPlayer.w >= dGolem.x && dPlayer.x <= dGolem.x + dGolem.w){
			player.Vida -= 10;
			Imunidade = 100;
		}
	}
}

void Golem_Dano(){

	if (dMagiaLR.x + dMagiaLR.w >= dGolem.x && dMagiaLR.x <= dGolem.x + dGolem.w && Imunidade_Mob == 0){
		if (dMagiaLR.y + dMagiaLR.h >= dGolem.y && dMagiaLR.y <= dGolem.y + dGolem.h){
			Golem_Vida -= 1;
			Imunidade_Mob = 200;
		}
	}
	if (dMagiaTD.x + dMagiaTD.w >= dGolem.x && dMagiaTD.x <= dGolem.x + dGolem.w && Imunidade_Mob == 0){
		if (dMagiaTD.y + dMagiaTD.h >= dGolem.y && dMagiaTD.y <= dGolem.y + dGolem.h){
			Golem_Vida -= 1;
			Imunidade_Mob = 200;
		}
	}

	if (dMagiaLR.y + dMagiaLR.h >= dGolem.y && dMagiaLR.y <= dGolem.y + dGolem.h && Imunidade_Mob == 0){
		if (dMagiaLR.x + dMagiaLR.w >= dGolem.x && dMagiaLR.x <= dGolem.x + dGolem.w){
			Golem_Vida -= 1;
			Imunidade_Mob = 200;
		}
	}

	if (dMagiaTD.y + dMagiaTD.h >= dGolem.y && dMagiaTD.y <= dGolem.y + dGolem.h && Imunidade_Mob == 0){
		if (dMagiaTD.x + dMagiaTD.w >= dGolem.x && dMagiaTD.x <= dGolem.x + dGolem.w){
			Golem_Vida -= 1;
			Imunidade_Mob = 200;
		}
	}
}

void Colisa_Mundo3(){

	if (esquerda == true && player.Px == 52 && player.Py >=0 && player.Py <= 600){
		SPEED = 0;
	}
	else if (direita == true && player.Px == 692 && player.Py >=0 && player.Py <= 600){
		SPEED = 0;
	}
	else if (cima == true && player.Py == 42 && player.Px >= 0 && player.Px <= 800){
		SPEED = 0;
	}
	else if (baixo == true && player.Py == 424 && player.Px >= 0 && player.Px <= 800){
		SPEED = 0;
	}
	else{
		SPEED = 2;
	}
}

void Boss_movimento(){

	if(dBoss.x > dPlayer.x)
		dBoss.x -= 1;
	if(dBoss.x < dPlayer.x)
		dBoss.x += 1;
	if (dBoss.y > dPlayer.y && dBoss.x == dPlayer.x)
		dBoss.y -= 1;
	if (dBoss.y < dPlayer.y && dBoss.x == dPlayer.x)
		dBoss.y += 1;

	if (Boss_Vida == 20)
		sVida_Boss.y = 0;
	if (Boss_Vida == 18)
		sVida_Boss.y = 600;
	if (Boss_Vida == 16)
		sVida_Boss.y = 1200;
	if (Boss_Vida == 14)
		sVida_Boss.y = 1800;
	if (Boss_Vida == 12)
		sVida_Boss.y = 2400;
	if (Boss_Vida == 10)
		sVida_Boss.y = 3000;
	if (Boss_Vida == 8)
		sVida_Boss.y = 3600;
	if (Boss_Vida == 6)
		sVida_Boss.y = 4200;
	if (Boss_Vida == 4)
		sVida_Boss.y = 4800;
	if (Boss_Vida == 2)
		sVida_Boss.y = 5400;
	if(Boss_Vida <= 0){
		// Fim do Jogo
	}

}

void Boss_Dano(){

	if (dMagiaLR.x + dMagiaLR.w >= dBoss.x && dMagiaLR.x <= dBoss.x + dBoss.w && Imunidade_Mob == 0){
		if (dMagiaLR.y + dMagiaLR.h >= dBoss.y && dMagiaLR.y <= dBoss.y + dBoss.h){
			Boss_Vida -= 1;
			Imunidade_Mob = 150;
		}
	}
	if (dMagiaTD.x + dMagiaTD.w >= dBoss.x && dMagiaTD.x <= dBoss.x + dBoss.w && Imunidade_Mob == 0){
		if (dMagiaTD.y + dMagiaTD.h >= dBoss.y && dMagiaTD.y <= dBoss.y + dBoss.h){
			Boss_Vida -= 1;
			Imunidade_Mob = 150;
		}
	}

	if (dMagiaLR.y + dMagiaLR.h >= dBoss.y && dMagiaLR.y <= dBoss.y + dBoss.h && Imunidade_Mob == 0){
		if (dMagiaLR.x + dMagiaLR.w >= dBoss.x && dMagiaLR.x <= dBoss.x + dBoss.w){
			Golem_Vida -= 1;
			Imunidade_Mob = 150;
		}
	}

	if (dMagiaTD.y + dMagiaTD.h >= dGolem.y && dMagiaTD.y <= dBoss.y + dBoss.h && Imunidade_Mob == 0){
		if (dMagiaTD.x + dMagiaTD.w >= dBoss.x && dMagiaTD.x <= dBoss.x + dBoss.w){
			Golem_Vida -= 1;
			Imunidade_Mob = 150;
		}
	}
}

void Boss_Hit(){

	if (dPlayer.x + dPlayer.w >= dBoss.x && dPlayer.x <= dBoss.x + dBoss.w && Imunidade == 0){
		if (dPlayer.y + dPlayer.w >= dBoss.y && dPlayer.y <= dBoss.y + dBoss.h){
			player.Vida -= 15;
			Imunidade = 100;
		}
	}

	if (dPlayer.y + dPlayer.w >= dBoss.y && dPlayer.y <= dBoss.y + dBoss.h && Imunidade == 0){
		if (dPlayer.x + dPlayer.w >= dBoss.x && dPlayer.x <= dBoss.x + dBoss.w){
			player.Vida -= 15;
			Imunidade = 100;
		}
	}
}