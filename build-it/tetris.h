#ifndef TETRIS_H
#define TETRIS_H

#include "setup.h"

#include <EEPROM.h>

//
// LA LOGIQUE DU JEU
//

// la vitesse du jeu
byte vitesse = 50;

// la vitesse selon le niveau de difficulté
byte tabVitesse[9] = {20, 15, 12, 10, 7, 5, 4, 3, 2};

// le compteur de cycle
long cycle = 0;

// la tempo pour afficher l'animation briques détruites
byte tempoDetruit = 10;

// le meilleur score
int record = 0;

// la durée de la fenêtre pour les effets sonores
#define DUREE_SON 20

//
// Les graphismes
//

// Les constantes
#define AIRE_JEU_X1 27
#define AIRE_JEU_Y1 0
#define AIRE_JEU_X2 56
#define AIRE_JEU_Y2 47

#define EST 0
#define SUD 1
#define OUEST 2
#define NORD 3

// position de départ de la piece
char colPiece = 3;
char ligPiece = 0;
char orientationPiece = EST;
byte typePiece = 0;
byte typePieceSuivante = 1;

// l'événement en cours
byte tetris_evenement;

// Les événements du jeu
#define RIEN 0
#define BLOQUE_PIECE 1
#define DETRUIT 2
#define ROTATION 3
#define FIN_PARTIE 99

// Les écrans du jeu
byte tetris_modeJeu = 0;
#define ACCUEIL 0
#define PARTIE 1
#define FINPARTIE 2
#define PAUSE 3

int score = 0;
int lignes = 0;
byte niveau = 1;
byte nivDebut = 1;
byte eclair = 1;

byte detruit[16] = {0, 0, 0, 0, 0, 0, 0};
// les cases immobiles du tableau (y compris 4 lignes au sol (invisibles)
byte cases[20][10] =
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// un pièce représentée sur 2 octets = 4 lignes de 4 bits
// 4 orientations (E,S,O,N)
// 7 pieces différentes I,O,T,S,Z,L,J
#define PIECE_I 0
#define PIECE_O 1
#define PIECE_T 2
#define PIECE_S 3
#define PIECE_Z 4
#define PIECE_L 5
#define PIECE_J 6
byte pieces[7][4][2] = {
    {{B00001111, B00000000}, {B01000100, B01000100}, {B00001111, B00000000}, {B01000100, B01000100}},
    {{B01100110, B00000000}, {B01100110, B00000000}, {B01100110, B00000000}, {B01100110, B00000000}},
    {{B00100111, B00000000}, {B01000110, B01000000}, {B01110010, B00000000}, {B00100110, B00100000}},
    {{B00110110, B00000000}, {B01000110, B00100000}, {B00110110, B00000000}, {B01000110, B00100000}},
    {{B01100011, B00000000}, {B00100110, B01000000}, {B01100011, B00000000}, {B00100110, B01000000}},
    {{B00101110, B00000000}, {B01000100, B01100000}, {B11101000, B00000000}, {B11000100, B01000000}},
    {{B01000111, B00000000}, {B01100100, B01000000}, {B01110001, B00000000}, {B00100010, B01100000}},
};

// La partie Setup concerne ce qui va être exécuté au démarrage de Kitco
void tetris_setup()
{
    lcdBegin();

    // mise à zéro du record
    //  EEPROM.write(0,0);
    //  EEPROM.write(1,0);

    record = EEPROM.read(0) + EEPROM.read(1) * 255;
}

#define dessineCase(l, c, dx, dy) setRect(AIRE_JEU_X1 + (c) * 3 + dx, (l) * 3 + dy, AIRE_JEU_X1 + (c) * 3 + 2 + dx, (l) * 3 + 2 + dy, false, BLACK)

// tracer la piece en cours
void tracePiece()
{
    if (pieces[typePiece][orientationPiece][0] & B10000000)
    {
        dessineCase(ligPiece, colPiece, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][0] & B01000000)
    {
        dessineCase(ligPiece, colPiece + 1, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][0] & B00100000)
    {
        dessineCase(ligPiece, colPiece + 2, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][0] & B00010000)
    {
        dessineCase(ligPiece, colPiece + 3, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][0] & B00001000)
    {
        dessineCase(ligPiece + 1, colPiece, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][0] & B00000100)
    {
        dessineCase(ligPiece + 1, colPiece + 1, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][0] & B00000010)
    {
        dessineCase(ligPiece + 1, colPiece + 2, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][0] & B00000001)
    {
        dessineCase(ligPiece + 1, colPiece + 3, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][1] & B10000000)
    {
        dessineCase(ligPiece + 2, colPiece, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][1] & B01000000)
    {
        dessineCase(ligPiece + 2, colPiece + 1, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][1] & B00100000)
    {
        dessineCase(ligPiece + 2, colPiece + 2, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][1] & B00010000)
    {
        dessineCase(ligPiece + 2, colPiece + 3, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][1] & B00001000)
    {
        dessineCase(ligPiece + 3, colPiece, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][1] & B00000100)
    {
        dessineCase(ligPiece + 3, colPiece + 1, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][1] & B00000010)
    {
        dessineCase(ligPiece + 3, colPiece + 2, 0, 0);
    }
    if (pieces[typePiece][orientationPiece][1] & B00000001)
    {
        dessineCase(ligPiece + 3, colPiece + 3, 0, 0);
    }
}

// tracer la piece suivante
void tracePieceSuivante()
{
#define LIGNECADRE 4
#define COLCADRE -6
    char decalY = 0;
    char decalX = 0;

    if (typePieceSuivante == PIECE_I)
        decalY = -1;
    if (typePieceSuivante == PIECE_T || typePieceSuivante == PIECE_S || typePieceSuivante == PIECE_Z || typePieceSuivante == PIECE_J)
        decalX = -1;
    if (typePieceSuivante == PIECE_L)
        decalX = +1;

    if (pieces[typePieceSuivante][EST][0] & B10000000)
    {
        dessineCase(LIGNECADRE, COLCADRE, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][0] & B01000000)
    {
        dessineCase(LIGNECADRE, COLCADRE + 1, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][0] & B00100000)
    {
        dessineCase(LIGNECADRE, COLCADRE + 2, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][0] & B00010000)
    {
        dessineCase(LIGNECADRE, COLCADRE + 3, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][0] & B00001000)
    {
        dessineCase(LIGNECADRE + 1, COLCADRE, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][0] & B00000100)
    {
        dessineCase(LIGNECADRE + 1, COLCADRE + 1, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][0] & B00000010)
    {
        dessineCase(LIGNECADRE + 1, COLCADRE + 2, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][0] & B00000001)
    {
        dessineCase(LIGNECADRE + 1, COLCADRE + 3, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][1] & B10000000)
    {
        dessineCase(LIGNECADRE + 2, COLCADRE, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][1] & B01000000)
    {
        dessineCase(LIGNECADRE + 2, COLCADRE + 1, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][1] & B00100000)
    {
        dessineCase(LIGNECADRE + 2, COLCADRE + 2, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][1] & B00010000)
    {
        dessineCase(LIGNECADRE + 2, COLCADRE + 3, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][1] & B00001000)
    {
        dessineCase(LIGNECADRE + 3, COLCADRE, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][1] & B00000100)
    {
        dessineCase(LIGNECADRE + 3, COLCADRE + 1, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][1] & B00000010)
    {
        dessineCase(LIGNECADRE + 3, COLCADRE + 2, decalX, decalY);
    }
    if (pieces[typePieceSuivante][EST][1] & B00000001)
    {
        dessineCase(LIGNECADRE + 3, COLCADRE + 3, decalX, decalY);
    }
}

// indique s'il y a intersection avec les cases dispo
byte intersect(byte orient)
{

    return (((pieces[typePiece][orient][0] & B10000000) && (cases[ligPiece][colPiece] || !((colPiece < 10) && (colPiece > -1) && (ligPiece < 16) && (ligPiece > -1)))) ||
            ((pieces[typePiece][orient][0] & B01000000) && (cases[ligPiece][colPiece + 1] || !((colPiece < 9) && (colPiece > -2) && (ligPiece < 16) && (ligPiece > -1)))) ||
            ((pieces[typePiece][orient][0] & B00100000) && (cases[ligPiece][colPiece + 2] || !((colPiece < 8) && (colPiece > -3) && (ligPiece < 16) && (ligPiece > -1)))) ||
            ((pieces[typePiece][orient][0] & B00010000) && (cases[ligPiece][colPiece + 3] || !((colPiece < 7) && (colPiece > -4) && (ligPiece < 16) && (ligPiece > -1)))) ||
            ((pieces[typePiece][orient][0] & B00001000) && (cases[ligPiece + 1][colPiece] || !((colPiece < 10) && (colPiece > -1) && (ligPiece < 15) && (ligPiece > -2)))) ||
            ((pieces[typePiece][orient][0] & B00000100) && (cases[ligPiece + 1][colPiece + 1] || !((colPiece < 9) && (colPiece > -2) && (ligPiece < 15) && (ligPiece > -2)))) ||
            ((pieces[typePiece][orient][0] & B00000010) && (cases[ligPiece + 1][colPiece + 2] || !((colPiece < 8) && (colPiece > -3) && (ligPiece < 15) && (ligPiece > -2)))) ||
            ((pieces[typePiece][orient][0] & B00000001) && (cases[ligPiece + 1][colPiece + 3] || !((colPiece < 7) && (colPiece > -4) && (ligPiece < 15) && (ligPiece > -2)))) ||
            ((pieces[typePiece][orient][1] & B10000000) && (cases[ligPiece + 2][colPiece] || !((colPiece < 10) && (colPiece > -1) && (ligPiece < 16) && (ligPiece > -3)))) ||
            ((pieces[typePiece][orient][1] & B01000000) && (cases[ligPiece + 2][colPiece + 1] || !((colPiece < 9) && (colPiece > -2) && (ligPiece < 16) && (ligPiece > -3)))) ||
            ((pieces[typePiece][orient][1] & B00100000) && (cases[ligPiece + 2][colPiece + 2] || !((colPiece < 8) && (colPiece > -3) && (ligPiece < 16) && (ligPiece > -3)))) ||
            ((pieces[typePiece][orient][1] & B00010000) && (cases[ligPiece + 2][colPiece + 3] || !((colPiece < 7) && (colPiece > -4) && (ligPiece < 16) && (ligPiece > -3)))) ||
            ((pieces[typePiece][orient][1] & B00001000) && (cases[ligPiece + 3][colPiece] || !((colPiece < 10) && (colPiece > -1) && (ligPiece < 16) && (ligPiece > -4)))) ||
            ((pieces[typePiece][orient][1] & B00000100) && (cases[ligPiece + 3][colPiece + 1] || !((colPiece < 9) && (colPiece > -2) && (ligPiece < 16) && (ligPiece > -4)))) ||
            ((pieces[typePiece][orient][1] & B00000010) && (cases[ligPiece + 3][colPiece + 2] || !((colPiece < 8) && (colPiece > -3) && (ligPiece < 16) && (ligPiece > -4)))) ||
            ((pieces[typePiece][orient][1] & B00000001) && (cases[ligPiece + 3][colPiece + 3] || !((colPiece < 7) && (colPiece > -4) && (ligPiece < 16) && (ligPiece > -4)))));
}

// indique si la piece en cours repose sur qqchose
byte piecePose()
{

    return (((pieces[typePiece][orientationPiece][0] & B10000000) && cases[ligPiece + 1][colPiece]) ||
            ((pieces[typePiece][orientationPiece][0] & B01000000) && cases[ligPiece + 1][colPiece + 1]) ||
            ((pieces[typePiece][orientationPiece][0] & B00100000) && cases[ligPiece + 1][colPiece + 2]) ||
            ((pieces[typePiece][orientationPiece][0] & B00010000) && cases[ligPiece + 1][colPiece + 3]) ||
            ((pieces[typePiece][orientationPiece][0] & B00001000) && cases[ligPiece + 2][colPiece]) ||
            ((pieces[typePiece][orientationPiece][0] & B00000100) && cases[ligPiece + 2][colPiece + 1]) ||
            ((pieces[typePiece][orientationPiece][0] & B00000010) && cases[ligPiece + 2][colPiece + 2]) ||
            ((pieces[typePiece][orientationPiece][0] & B00000001) && cases[ligPiece + 2][colPiece + 3]) ||
            ((pieces[typePiece][orientationPiece][1] & B10000000) && cases[ligPiece + 3][colPiece]) ||
            ((pieces[typePiece][orientationPiece][1] & B01000000) && cases[ligPiece + 3][colPiece + 1]) ||
            ((pieces[typePiece][orientationPiece][1] & B00100000) && cases[ligPiece + 3][colPiece + 2]) ||
            ((pieces[typePiece][orientationPiece][1] & B00010000) && cases[ligPiece + 3][colPiece + 3]) ||
            ((pieces[typePiece][orientationPiece][1] & B00001000) && cases[ligPiece + 4][colPiece]) ||
            ((pieces[typePiece][orientationPiece][1] & B00000100) && cases[ligPiece + 4][colPiece + 1]) ||
            ((pieces[typePiece][orientationPiece][1] & B00000010) && cases[ligPiece + 4][colPiece + 2]) ||
            ((pieces[typePiece][orientationPiece][1] & B00000001) && cases[ligPiece + 4][colPiece + 3]));
}

// ajouter la piece en cours dans les cases
void ajoutePiece()
{
    if (pieces[typePiece][orientationPiece][0] & B10000000)
    {
        cases[ligPiece][colPiece] = 1;
    }
    if (pieces[typePiece][orientationPiece][0] & B01000000)
    {
        cases[ligPiece][colPiece + 1] = 1;
    }
    if (pieces[typePiece][orientationPiece][0] & B00100000)
    {
        cases[ligPiece][colPiece + 2] = 1;
    }
    if (pieces[typePiece][orientationPiece][0] & B00010000)
    {
        cases[ligPiece][colPiece + 3] = 1;
    }
    if (pieces[typePiece][orientationPiece][0] & B00001000)
    {
        cases[ligPiece + 1][colPiece] = 1;
    }
    if (pieces[typePiece][orientationPiece][0] & B00000100)
    {
        cases[ligPiece + 1][colPiece + 1] = 1;
    }
    if (pieces[typePiece][orientationPiece][0] & B00000010)
    {
        cases[ligPiece + 1][colPiece + 2] = 1;
    }
    if (pieces[typePiece][orientationPiece][0] & B00000001)
    {
        cases[ligPiece + 1][colPiece + 3] = 1;
    }
    if (pieces[typePiece][orientationPiece][1] & B10000000)
    {
        cases[ligPiece + 2][colPiece] = 1;
    }
    if (pieces[typePiece][orientationPiece][1] & B01000000)
    {
        cases[ligPiece + 2][colPiece + 1] = 1;
    }
    if (pieces[typePiece][orientationPiece][1] & B00100000)
    {
        cases[ligPiece + 2][colPiece + 2] = 1;
    }
    if (pieces[typePiece][orientationPiece][1] & B00010000)
    {
        cases[ligPiece + 2][colPiece + 3] = 1;
    }
    if (pieces[typePiece][orientationPiece][1] & B00001000)
    {
        cases[ligPiece + 3][colPiece] = 1;
    }
    if (pieces[typePiece][orientationPiece][1] & B00000100)
    {
        cases[ligPiece + 3][colPiece + 1] = 1;
    }
    if (pieces[typePiece][orientationPiece][1] & B00000010)
    {
        cases[ligPiece + 3][colPiece + 2] = 1;
    }
    if (pieces[typePiece][orientationPiece][1] & B00000001)
    {
        cases[ligPiece + 3][colPiece + 3] = 1;
    }
}

// Gestion des graphismes
void tetris_afficheJeu()
{

    clearDisplay(BLACK);

    // 1 afficher le cadre du jeu
    setRect(AIRE_JEU_X1, 0, AIRE_JEU_X2 + 1, SCREEN_HEIGHT, true, WHITE);
    // ligneEcran(AIRE_JEU_X1-1, 0, AIRE_JEU_X1-1, SCREEN_HEIGHT-1, BLACK);
    // ligneEcran(AIRE_JEU_X2+1, 0, AIRE_JEU_X2+1, SCREEN_HEIGHT, BLACK);

    // 2 afficher le carré qui affiche la pièce suivante
    setRect(7, 7, 23, 22, true, WHITE);

    // 2 bis afficher la pièce suivante
    tracePieceSuivante();

    // 3 afficher le score
    setRect(AIRE_JEU_X2 + 2, 4, AIRE_JEU_X2 + 3 + 24, 12, true, WHITE);
    setChar('0' + score % 10, AIRE_JEU_X2 + 3 + 18, 5, BLACK);
    if (score >= 10)
        setChar('0' + (score / 10) % 10, AIRE_JEU_X2 + 3 + 12, 5, BLACK);
    if (score >= 100)
        setChar('0' + (score / 100) % 10, AIRE_JEU_X2 + 3 + 6, 5, BLACK);
    else
    {
        setChar('S', AIRE_JEU_X2 + 3, 5, BLACK);
        setChar(':', AIRE_JEU_X2 + 3 + 6, 5, BLACK);
    }
    if (score >= 1000)
        setChar('0' + (score / 1000) % 10, AIRE_JEU_X2 + 3, 5, BLACK);
    // setStr("9999",AIRE_JEU_X2+3,5,BLACK);

    setRect(AIRE_JEU_X2 + 2, 14, AIRE_JEU_X2 + 3 + 23, 22, false, WHITE);
    setStr("Niv ", AIRE_JEU_X2 + 3, 15, BLACK);
    setChar('0' + niveau, AIRE_JEU_X2 + 3 + 18, 15, BLACK);

    setRect(AIRE_JEU_X2 + 2, 24, AIRE_JEU_X2 + 3 + 23, 32, false, WHITE);
    setStr("Lig:", AIRE_JEU_X2 + 3, 25, BLACK);
    setStr("    ", AIRE_JEU_X2 + 3, 35, BLACK);

    setRect(AIRE_JEU_X2 + 2, 34, AIRE_JEU_X2 + 3 + 23, 42, false, WHITE);
    setChar('0' + lignes % 10, AIRE_JEU_X2 + 3 + 18, 35, BLACK);
    if (lignes >= 10)
        setChar('0' + (lignes / 10) % 10, AIRE_JEU_X2 + 3 + 12, 35, BLACK);
    if (lignes >= 100)
        setChar('0' + (lignes / 100) % 10, AIRE_JEU_X2 + 3 + 6, 35, BLACK);
    if (lignes >= 1000)
        setChar('0' + (lignes / 1000) % 10, AIRE_JEU_X2 + 3, 35, BLACK);

    // 4 afficher les briques posées
    for (byte c = 0; c < 10; c++)
    {
        for (byte l = 0; l < 16; l++)
        {
            if (cases[l][c])
            {
                // dans le  cas de destruction de ligne, on affiche en clignotant les lignes détruites
                if ((tetris_evenement != DETRUIT) || (!detruit[l]) || (cycle % 2))
                {
                    dessineCase(l, c, 0, 0);
                }
            }
        }
    }

    // 5 afficher la pièce en cours
    tracePiece();
    updateDisplay();
}

byte tetris_relache = true;

// Gestion des appuis touches
void tetris_gestionTouches()
{

    // si la tempo est OK et que la case de gauche est libre, on prend en compte l'appui gauche
    if (toucheGauche())
    {
        colPiece--;
        if (intersect(orientationPiece))
        {
            colPiece++;
        }
    }

    // si la tempo est OK et que la case de droite est libre, on prend en compte l'appui droite
    if (toucheDroite())
    {
        colPiece++;
        if (intersect(orientationPiece))
        {
            colPiece--;
        }
    }

    if (toucheBas())
    {

        // on teste si la pièce touche en dessous
        if (piecePose())
        { // alors on bloque la piece
            tetris_evenement = BLOQUE_PIECE;
        }
        else
        {
            ligPiece++;
        }
    }

    byte nouvelleOrientation = orientationPiece;
    if (toucheAux() && tetris_relache)
    {
        nouvelleOrientation = (orientationPiece + 3) % 4;
    }

    if ((!toucheAux()))
    {
        tetris_relache = true;
    }
    else
    {
        tetris_relache = false;
    }

    if (!intersect(nouvelleOrientation))
    {
        if (orientationPiece != nouvelleOrientation)
        {
            tetris_evenement = ROTATION;
            orientationPiece = nouvelleOrientation;
        }
    }
}

// gestion de la logique du jeu
void tetris_logiqueJeu()
{
    if (!(cycle % vitesse))
    {
        if (piecePose())
        { // alors on bloque la piece
            tetris_evenement = BLOQUE_PIECE;
        }
        else
        {
            ligPiece++;
        }
    }

    // est-ce que la pièce est bloquée ?
    if (tetris_evenement != BLOQUE_PIECE)
    { // non: on ne fait rien
        return;
    }
    // tetris_evenement = RIEN;

    // oui
    // on l'ajoute dans les cases
    ajoutePiece();

    // on teste si on a fait des lignes
    for (byte l = 0; l < 16; l++)
    {
        if (cases[l][0] & cases[l][1] & cases[l][2] & cases[l][3] & cases[l][4] & cases[l][5] & cases[l][6] & cases[l][7] & cases[l][8] & cases[l][9])
        {
            detruit[l] = 1;
            tetris_evenement = DETRUIT;
            tempoDetruit = 10;
        }
    }

    // on passe à la pièce suivante
    colPiece = 3;
    ligPiece = 0;
    orientationPiece = EST;
    typePiece = typePieceSuivante;
    typePieceSuivante = random(0, 7);

    if (intersect(orientationPiece))
    {
        tetris_evenement = FIN_PARTIE;
    }
}

void tetris_sonJeu()
{
    switch (tetris_evenement)
    {
    case FIN_PARTIE:
        tetris_evenement = RIEN;
        tetris_modeJeu = ACCUEIL;
        niveau = 1;
        if (score > record)
        {
            record = score;
            EEPROM.write(0, record % 255);
            EEPROM.write(1, record / 255);
        }

        while (!touche())
            ;
        while (touche())
            ;
        break;
    case BLOQUE_PIECE:
        tetris_evenement = RIEN;
        break;
    case ROTATION:
        tetris_evenement = RIEN;
        break;
    case DETRUIT:
        break;
    default:
        break;
    }
}

void retireLignes()
{
    byte nbLig = 0;
    byte scoreLig[] = {1, 2, 4, 8};
    for (byte i = 0; i < 16; i++)
    {
        if (detruit[i])
        {
            lignes++;
            nbLig++;
            niveau = min(9, nivDebut + (lignes / 10));
            vitesse = tabVitesse[min(8, niveau - 1)];
            detruit[i] = 0;
            for (byte j = i; j > 0; j--)
            {
                cases[j][0] = cases[j - 1][0];
                cases[j][1] = cases[j - 1][1];
                cases[j][2] = cases[j - 1][2];
                cases[j][3] = cases[j - 1][3];
                cases[j][4] = cases[j - 1][4];
                cases[j][5] = cases[j - 1][5];
                cases[j][6] = cases[j - 1][6];
                cases[j][7] = cases[j - 1][7];
                cases[j][8] = cases[j - 1][8];
                cases[j][9] = cases[j - 1][9];
            }
            cases[0][0] = 0;
            cases[0][1] = 0;
            cases[0][2] = 0;
            cases[0][3] = 0;
            cases[0][4] = 0;
            cases[0][5] = 0;
            cases[0][6] = 0;
            cases[0][7] = 0;
            cases[0][8] = 0;
            cases[0][9] = 0;
        }
    }
    score += scoreLig[nbLig - 1] * niveau;
}

byte tetris_sel = 0;

void afficheAccueil()
{
    byte CLIGNOTANT;

    if (((millis() / 500) % 2) == 0)
    {
        CLIGNOTANT = WHITE;
    }
    else
    {
        CLIGNOTANT = BLACK;
    }

    clearDisplay(WHITE);
    setStr("Tetris", 20, 5, BLACK);

    setStr("Record: ", 12, 13, BLACK);

    setChar('0' + record % 10, 72, 13, BLACK);
    if (record >= 10)
        setChar('0' + (record / 10) % 10, 67, 13, BLACK);
    if (record >= 100)
        setChar('0' + (record / 100) % 10, 62, 13, BLACK);
    if (record >= 1000)
        setChar('0' + (record / 1000) % 10, 57, 13, BLACK);

    if (tetris_sel == 0)
    {
        setStr("Niveau:", 12, 21, CLIGNOTANT);
        setChar('0' + niveau, 54, 21, CLIGNOTANT);
    }
    else
    {
        setStr("Niveau:", 12, 21, BLACK);
        setChar('0' + niveau, 54, 21, BLACK);
    }

    updateDisplay();
}

void tetris_initPartie()
{
    randomSeed(millis());
    score = 0;
    lignes = 0;
    typePiece = random(0, 7);
    typePieceSuivante = random(0, 7);
    vitesse = tabVitesse[niveau - 1];
    for (byte l = 0; l < 16; l++)
        for (byte c = 0; c < 10; c++)
            cases[l][c] = 0;
    nivDebut = niveau;
    tetris_modeJeu = PARTIE;
}

// byte tetris_relache = true;

void gestionTouchesAccueil()
{
    if (!touche())
    {
        tetris_relache = true;
    }
    if (toucheAux())
    {
        tetris_modeJeu = PARTIE;
        tetris_initPartie();
    }

    if (tetris_relache && toucheHaut() && tetris_sel > 0)
    {
        tetris_sel--;
    }

    if (tetris_relache && toucheBas() && tetris_sel < 2)
    {
        tetris_sel++;
    }

    if ((tetris_sel == 0) && tetris_relache && toucheDroite() && niveau < 9)
    {
        niveau++;
    }
    if ((tetris_sel == 0) && tetris_relache && toucheGauche() && niveau > 1)
    {
        niveau--;
    }

    if (touche())
    {
        tetris_relache = false;
    }
}

void loopAccueil()
{
    afficheAccueil();
    gestionTouchesAccueil();
}

void loopPartie()
{
    if (tetris_evenement != DETRUIT)
    {
        tetris_gestionTouches();
        tetris_logiqueJeu();
    }
    else
    {
        tempoDetruit--;
        if (tempoDetruit == 0)
        {
            retireLignes();
            tetris_evenement = RIEN;
        }
    }
    tetris_afficheJeu();
    tetris_sonJeu();
    cycle = cycle + 1;
}

// Loop est la boucle principale, va se lancer en boucle après Setup
void tetris_loop()
{
    switch (tetris_modeJeu)
    {
    case ACCUEIL:
        loopAccueil();
        break;
    case PARTIE:
        loopPartie();
        break;
    default:
        break;
    }
}


#endif