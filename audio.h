//Implementa as coisas reltivas ao audio
#ifndef AUDIO_H
#define AUDIO_H

bool startGame = false;
bool gameOverAudio = false;
bool explosion = false;
bool atiraAudio = false;
bool audioLife = false;
bool audioApareceBonus = false;
bool audioPegaBonus = false;
bool audioHitMetal = false;

void playAudio(){
	if(startGame == false){
		PlaySound("sounds/gamestart.wav", NULL, SND_ASYNC|SND_FILENAME);
		startGame = true;
	}
	
	if(audioLife){
		PlaySound("sounds/life.wav", NULL, SND_ASYNC|SND_FILENAME);
		audioLife = false;
		audioPegaBonus = false;
	}
	
	if(audioHitMetal){
		PlaySound("sounds/hitMetal.wav", NULL, SND_ASYNC|SND_FILENAME);
		audioHitMetal = false;
	}
	
	if(audioPegaBonus){
		PlaySound("sounds/pegaBonus.wav", NULL, SND_ASYNC|SND_FILENAME);
		audioPegaBonus = false;
	}
	
	if(audioApareceBonus){
		PlaySound("sounds/bonusAparecendo.wav", NULL, SND_ASYNC|SND_FILENAME);
		audioApareceBonus = false;
	}
	
	if(gameOverAudio){
		PlaySound("sounds/gameover.wav", NULL, SND_ASYNC|SND_FILENAME);
		gameOverAudio = false;
	}
	
	if(explosion){
		PlaySound("sounds/explosion.wav", NULL, SND_ASYNC|SND_FILENAME);
		explosion = false;
	}
	
	if(atiraAudio){
		PlaySound("sounds/fire.wav", NULL, SND_ASYNC|SND_FILENAME);
		atiraAudio = false;
	}
}

#endif