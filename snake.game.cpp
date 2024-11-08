#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool fimdejogo;
const int largura = 20;
const int altura = 10;
int x, y, frutaX, frutaY, pontuacao;
int caudaX[100], caudaY[100];
int nCauda;
enum eDirecao { PARAR = 0, ESQUERDA, DIREITA, CIMA, BAIXO };
eDirecao dir;

void Configurar() {
    fimdejogo = false;
    dir = PARAR;
    x = largura / 2;
    y = altura / 2;
    frutaX = rand() % largura;
    frutaY = rand() % altura;
    pontuacao = 0;
    nCauda = 0;
}

void Desenhar() {
    system("cls");
    for (int i = 0; i < largura + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (j == 0)
                cout << "#"; 
            if (i == y && j == x)
                cout << "O"; 
            else if (i == frutaY && j == frutaX)
                cout << "F"; 
            else {
                bool imprimirCauda = false;
                for (int k = 0; k < nCauda; k++) {
                    if (caudaX[k] == j && caudaY[k] == i) {
                        cout << "o"; 
                        imprimirCauda = true;
                    }
                }
                if (!imprimirCauda)
                    cout << " ";
            }

            if (j == largura - 1)
                cout << "#"; 
        }
        cout << endl;
    }

    for (int i = 0; i < largura + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Pontuação: " << pontuacao << endl;
}

void Entrada() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = ESQUERDA;
                break;
            case 'd':
                dir = DIREITA;
                break;
            case 'w':
                dir = CIMA;
                break;
            case 's':
                dir = BAIXO;
                break;
            case 'x':
                fimdejogo = true;
                break;
        }
    }
}

void Algoritmo() {
    int prevX = caudaX[0];
    int prevY = caudaY[0];
    int prev2X, prev2Y;
    caudaX[0] = x;
    caudaY[0] = y;

    for (int i = 1; i < nCauda; i++) {
        prev2X = caudaX[i];
        prev2Y = caudaY[i];
        caudaX[i] = prevX;
        caudaY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case ESQUERDA:
            x--;
            break;
        case DIREITA:
            x++;
            break;
        case CIMA:
            y--;
            break;
        case BAIXO:
            y++;
            break;
        default:
            break;
    }

    if (x < 0 || x >= largura || y < 0 || y >= altura)
        fimdejogo = true;

    for (int i = 0; i < nCauda; i++) {
        if (caudaX[i] == x && caudaY[i] == y)
            fimdejogo = true;
    }

    if (x == frutaX && y == frutaY) {
        pontuacao += 10;
        frutaX = rand() % largura;
        frutaY = rand() % altura;
        nCauda++;
    }
}

void TelaInicial() {
    system("cls");
    cout << "=======================" << endl;
    cout << "      JOGO DA CEBOLINHA       " << endl;
    cout << "=======================" << endl;
    cout << "\nPressione 'ENTER' para começar o jogo." << endl;
    cout << "\nInstruções:" << endl;
    cout << "1. Use 'W' para mover para cima." << endl;
    cout << "2. Use 'A' para mover para a esquerda." << endl;
    cout << "3. Use 'S' para mover para baixo." << endl;
    cout << "4. Use 'D' para mover para a direita." << endl;
    cout << "5. Colete as frutas (F) para pontuar." << endl;
    cout << "6. Evite bater nas paredes ou na sua própria cauda." << endl;
    cout << "\nBoa sorte!" << endl;
    cout << "\nPressione 'ENTER' para começar..." << endl;
    while (_kbhit()) _getch(); 
    while (_getch() != 13); 
}

void TelaGameOver() {
    system("cls");
    cout << "=======================" << endl;
    cout << "       FIM DE JOGO       " << endl;
    cout << "=======================" << endl;
    cout << "\nSua pontuação: " << pontuacao << endl;
    cout << "\nPressione 'R' para reiniciar ou 'Q' para sair." << endl;

    while (_kbhit()) _getch(); 
    char escolha = _getch();
    if (escolha == 'r' || escolha == 'R') {
        Configurar();
        return; 
    } else if (escolha == 'q' || escolha == 'Q') {
        fimdejogo = true;
    }
}

int main() {
    TelaInicial();

    do {
        Configurar();
        while (!fimdejogo) {
            Desenhar();
            Entrada();
            Algoritmo();
            Sleep(10);
        }

        TelaGameOver(); 

    } while (!fimdejogo); 

    return 0;
}
