#include <iostream>
#include <cstdlib>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Weapons ================================================
//Fire
//Bullet
extern sf::SoundBuffer bufBulletPistol;
    extern sf::Sound sndBulletPistol;
extern sf::SoundBuffer bufBulletRifle;
    extern sf::Sound sndBulletRifle;
extern sf::SoundBuffer bufBulletMinigun;
    extern sf::Sound sndBulletMinigun;
//Laser
extern sf::SoundBuffer bufLaserPistol;
    extern sf::Sound sndLaserPistol;
extern sf::SoundBuffer bufLaserRifle;
    extern sf::Sound sndLaserRifle;
extern sf::SoundBuffer bufLaserMinigun;
    extern sf::Sound sndLaserMinigun;
//Gauss
extern sf::SoundBuffer bufGaussPistol;
    extern sf::Sound sndGaussPistol;
extern sf::SoundBuffer bufGaussRifle;
    extern sf::Sound sndGaussRifle;
extern sf::SoundBuffer bufGaussMinigun;
    extern sf::Sound sndGaussMinigun;
extern sf::SoundBuffer bufGaussDestructeur;
    extern sf::Sound sndGaussDestructeur;


using namespace sf;

void InitSound()
{


    //Weapons ================================================
    //Fire
    //Bullet
    bufBulletPistol.LoadFromFile("data/sound/bullet_pistol.wav");
    sndBulletPistol.SetBuffer(bufBulletPistol);

    bufBulletRifle.LoadFromFile("data/sound/bullet_rifle.wav");
    sndBulletRifle.SetBuffer(bufBulletRifle);

    bufBulletMinigun.LoadFromFile("data/sound/bullet_minigun.wav");
    sndBulletMinigun.SetBuffer(bufBulletMinigun);
    //Laser
    bufLaserPistol.LoadFromFile("data/sound/laser_pistol.wav");
    sndLaserPistol.SetBuffer(bufLaserPistol);

    bufLaserRifle.LoadFromFile("data/sound/laser_rifle.wav");
    sndLaserRifle.SetBuffer(bufLaserRifle);

    bufLaserMinigun.LoadFromFile("data/sound/laser_minigun.wav");
    sndLaserMinigun.SetBuffer(bufLaserMinigun);
    //Gauss
    bufGaussPistol.LoadFromFile("data/sound/gauss_pistol.wav");
    sndGaussPistol.SetBuffer(bufGaussPistol);

    bufGaussRifle.LoadFromFile("data/sound/gauss_rifle.wav");
    sndGaussRifle.SetBuffer(bufGaussRifle);

    bufGaussMinigun.LoadFromFile("data/sound/gauss_minigun.wav");
    sndGaussMinigun.SetBuffer(bufGaussMinigun);

    bufGaussDestructeur.LoadFromFile("data/sound/gauss_destructeur.wav");
    sndGaussDestructeur.SetBuffer(bufGaussDestructeur);
    //Impact-----------------
    // TODO (crom#1#): init des sons d'impact

}
