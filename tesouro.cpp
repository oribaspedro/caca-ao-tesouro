#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

int tamMatriz, qtdJogadores, quadrosRestantes, quilatesJogadores[4] = {0}, lixoJogadores[4] = {0}, qtdQuadros, qtdRodadas, rodadasRestantes, tabuleiroEscondido[26][26], auxQuilates;
string nomes[4], ids[4], tabuleiro[26][26], auxNomes, auxIds;

/*
tipos de itens da mina:
0: lixo
1: diamantes
2: tuneis sem saida
3: esconderijos
4: pistas
5: recicladora
6: totem de multiplicação
*/


void printTabuleiro() {
    cout << setw(3) << ' ';
    
    for(int i = 0; i < tamMatriz; i++) {
        cout << setw(3) << char(i+65);
    }
    
    cout << endl;
    
    for(int i = 0; i < tamMatriz; i++) {
        cout << setw(3) << i;
        for(int j = 0; j < tamMatriz; j++) {
            cout << setw(3) << tabuleiro[i][j];
        }
        cout << endl;
    }
}






void gerarItem (int tipoItem, float porcentagem) {
    int qtd = round(qtdQuadros*(porcentagem/100));
    for(int i = 0; i < qtd; i++) {
        int linha;
        int coluna;
        do {
            linha = rand()%tamMatriz;
            coluna = rand()%tamMatriz;
        } while (tabuleiroEscondido[linha][coluna] != 0);
        tabuleiroEscondido[linha][coluna] = tipoItem;
        quadrosRestantes--;
    }
}







void configJogo() {
    cout << "Quantos serão os jogadores?" << endl;
    do {
        cin >> qtdJogadores;
        if(qtdJogadores < 2 or qtdJogadores > 4) {
            cout << "O número de jogadores precisa estar entre 2 e 4" << endl;
        }
    } while(qtdJogadores < 2 or qtdJogadores > 4);

    for(int i = 0; i < qtdJogadores; i++) {
        cout << "Qual é o nome do " << i+1 << " jogador?" << endl;;
        cin >> nomes[i];
    }

    cout << "Cada jogador será identificado pela inicial do nome com o seu número da ordem de entrada ao lado (ex: 1 jogador chamado Joao = J1" << endl;

    for(int i = 0; i < qtdJogadores; i++) {
        string inicialAux = nomes[i];
        ids[i] = inicialAux[0] + to_string(i+1);
    }

    for(int i = 0; i < qtdJogadores; i++) {
        cout << ids[i] << endl;
    }

    cout << "Qual será o tamanho do tabuleiro? (um número que define a quantidade de linhas e colunas)" << endl;
    do {
        cin >> tamMatriz;
        if((tamMatriz*tamMatriz) % qtdJogadores != 0 or tamMatriz < 6 or tamMatriz > 26) {
            cout << "O tamanho da matriz precisa ser compativel com a quantidade de jogadores, além de não ser menor do que 6 e nem maior do que 26." << endl;
        }
    } while((tamMatriz*tamMatriz) % qtdJogadores != 0 or tamMatriz < 6 or tamMatriz > 26);
    
    qtdQuadros = tamMatriz*tamMatriz;
    quadrosRestantes = tamMatriz*tamMatriz;
    qtdRodadas = qtdQuadros / qtdJogadores;
    rodadasRestantes = qtdQuadros / qtdJogadores;
    
    for(int i = 0; i < tamMatriz; i++) {
        for(int j = 0; j < tamMatriz; j++) {
            tabuleiro[i][j] = " ";
            tabuleiroEscondido[i][j] = 0;
        }
    }
    
    int pctDiamantes = (rand()%41)+10; //gera um numero entre 10 e 50, que será a % de diamantes na mina
    
    gerarItem(1, pctDiamantes); //gerar diamantes
    gerarItem(2, 5); //gerar tuneis sem saida
    gerarItem(3, 5); //gerar esconderijos
    gerarItem(4, 5); //gerar pistas
    gerarItem(5, 2); //gerar recicladoras
    gerarItem(6, 2); // gerar totem de duplicacao

    cout << setw(3) << ' ';
    
    for(int i = 0; i < tamMatriz; i++) {
        cout << setw(3) << char(i+65);
    }
    
    cout << endl;
    for(int i = 0; i < tamMatriz; i++) {
        cout << setw(3) << i;
        for(int j = 0; j < tamMatriz; j++) {
            cout << setw(3) << tabuleiroEscondido[i][j];
        }
        cout << endl;
    }
}   




void ranking() {
    for(int i = 0; i < qtdJogadores; i++) {
        for(int j = i; j < qtdJogadores; j++) {
            if(quilatesJogadores[j] > quilatesJogadores[i]) {
                auxQuilates = quilatesJogadores[i];
                quilatesJogadores[i] = quilatesJogadores[j];
                quilatesJogadores[j] = auxQuilates;
                
                auxNomes = nomes[i];
                nomes[i] = nomes[j];
                nomes[j] = auxNomes;

                auxIds = ids[i];
                ids[i] = ids[j];
                ids[j] = auxIds;
            }
        }
        cout << i + 1 << " colocado: " << nomes[i] << "(" << ids[i] << ")" << ", com " << quilatesJogadores[i] << " quilates de diamante!" << endl;
    }
}




int main() {
    srand(time(NULL));

    configJogo();
    
    
    
    while(qtdRodadas) {
        for(int i = 0; i < qtdJogadores; i++) {
            int linha, evento;
            char coluna;
            
            cout << nomes[i] << "(" << ids[i] << "): Você tem " << quilatesJogadores[i] << " quilates de diamante e " << lixoJogadores[i] << " kgs de lixo no seu inventário." << endl;
            cout << "Escolha uma coordenada para efetuar a sua jogada. (Numero da linha seguido da letra da coluna em maiúsculo)" << endl;
            
            do {
                cin >> linha >> coluna;
                if(linha >= tamMatriz or linha < 0 or int(coluna-65) >= tamMatriz or int(coluna-65) < 0) {
                    cout << "Coordenada inválida, essa posicao não existe. Escolha outra coordenada. (a letra precisa estar em caixa alta)" << endl;
                }
                else {
                    if(tabuleiro[linha][int(coluna-65)] != " ") {
                        cout << "Esta posicao ja foi escolhida, escolha outra." << endl;
                    }
                }
            } while(linha > tamMatriz or linha < 0 or int(coluna-65) > tamMatriz or int(coluna-65) < 0 or (tabuleiro[linha][int(coluna-65)] != " "));
            
            tabuleiro[linha][int(coluna-65)] = ids[i];
            
            evento = tabuleiroEscondido[linha][int(coluna-65)];
            tabuleiroEscondido[linha][int(coluna-65)] = 0;
            cout << evento << endl;

            printTabuleiro();
            
            switch(evento) {
                case 0:
                {
                    int resposta, kgsLixo = (rand()%3)+1; //gera os kgs de lixo que serão acrescidos ao inventario do jogador, que será entre 1 e 3

                    tabuleiro[linha][int(coluna-65)] = ids[i];
                    cout << "Você encontrou " << kgsLixo << " de lixo, você quer guardar esse lixo no seu inventário? (responda com 1 para sim e 0 para não)" << endl;
                    cin >> resposta;
                    switch(resposta) {
                        case 0:
                            cout << "É apenas lixo, então você joga ele onde ninguém o encontrará, a fim de ser esquecido por toda a eternidade..." << endl;
                            break;
                        case 1:
                            cout << "Você pega o lixo e guarda ele junto com seus pertences." << endl;
                            cout << "*" << kgsLixo << " kgs de lixo foram adicionados ao seu inventário.*" << endl;
                            lixoJogadores[i] += kgsLixo;
                            break;
                        default:
                            cout << "Resposta inválida." << endl;
                            break;
                    }
                    break;
                }
                case 1:
                {
                    int resposta, quilates = (rand()%10)+1; //gera um numero de quilates para o diamante entre 0 e 10

                    tabuleiro[linha][int(coluna-65)] = ids[i];
                    cout << "Você percebe algo brilhando na escuridão da caverna... É um diamante de " << quilates << " quilates! Você quer guardar esse diamante no seu inventário? (responda com 1 para sim e 0 para não)" << endl;
                    cin >> resposta;
                    switch(resposta) {
                        case 0:
                            cout << "Você percebe o quão vã e sem sentido é a sua busca por riqueza e por tesouros e enterra o diamante onde ninguém o encontrará..." << endl;
                            break;
                        case 1:
                            cout << "Você pega o diamante e guarda ele junto com seus pertences." << endl;
                            cout << "*" << quilates << " quilates de diamante foram adicionados ao seu inventário*" << endl;
                            quilatesJogadores[i] += quilates;
                            break;
                        default:
                            cout << "Resposta inválida." << endl;
                            break;
                    }
                    break;
                }
                case 2:
                {
                    tabuleiro[linha][int(coluna-65)] = "O";
                    cout << "Você entra em um túnel sem saída, e ao dar a volta para retornar ao caminho correto alguns diamantes caem da sua bolsa..." << endl;
                    if(quilatesJogadores[i] < 10) {
                        cout << "*Você perdeu " << quilatesJogadores[i] << " quilates*" << endl;
                        quilatesJogadores[i] = 0;
                    }
                    else {
                        quilatesJogadores[i] -= 10;
                        cout << "*Você perdeu 10 quilates*" << endl;
                    }
                    break;
                }
                case 3:
                {
                    tabuleiro[linha][int(coluna-65)] = "-";
                    cout << "Você encontra um esconderijo e usa dele para se beneficiar dos seus oponentes..." << endl;
                    for(int j = 0; j < qtdJogadores; j++) {
                        if(j != i) {
                            if(quilatesJogadores[j] < 5) {
                                quilatesJogadores[j] = 0;
                            }
                            else {
                                quilatesJogadores[j] -= 5;
                            }
                        }
                    }
                    cout << "*Cada oponente seu perdeu 5 quilates*" << endl;
                    break;
                }
                case 4:
                {
                    int linha, coluna, pista;
                    do {
                        linha = rand()%tamMatriz;
                        coluna = rand()%tamMatriz;
                    } while((tabuleiroEscondido[linha][coluna] == 0) or (tabuleiroEscondido[linha][coluna] == 4));
                    pista = tabuleiroEscondido[linha][coluna];
                    tabuleiro[linha][int(coluna-65)] = ids[i] + "P";
                    switch(pista) {
                        case 1:
                            cout << "Existe um diamante em algum lugar da coluna " << char(coluna+65) << "!" << endl;
                            break;
                        case 2:
                            cout << "Cuidado! Tem um túnel sem saída em algum lugar da linha " << linha << "!" << endl;
                            break;
                        case 3:
                            cout << "Você pode encontrar um esconderijo secreto em algum lugar da coluna " << char(coluna+65) << " e ganhar uns quilates a mais em cima dos seus oponentes!" << endl;
                            break;
                        case 5:
                            cout << "Tem uma recicladora muito interessante em algum lugar na coluna " << char(coluna+65) << "! Talvez você devesse dar uma olhada, ainda mais se você anda carregando muito lixo, hehehe..." << endl;
                            break;
                        case 6:
                            cout << "Se você gosta de arriscar, saiba que existe um totem mágico que pode duplicar seus diamantes na linha " << linha << "!" << endl;
                            break;
                        default:
                            cout << "Nosso estoque de pistas acabou, volte mais tarde." << endl;
                    }
                    break;
                }
                case 5:
                {
                    tabuleiro[linha][int(coluna-65)] = "#";
                    if(lixoJogadores[i] > 0) {
                        cout << "Você encontrou uma recicladora que transforma 1 kg de lixo em um diamante de 1 quilate! Você colocou o lixo que coletou até aqui na máquina e ela o transformou em diamantes!" << endl;
                        quilatesJogadores[i] += lixoJogadores[i];
                        cout << "*" << lixoJogadores[i] << " quilates foram adicionados ao seu inventário*" << endl;
                        lixoJogadores[i] = 0;
                    }
                    else {
                        cout << "Você encontrou uma recicladora que transforma 1 kg de lixo em um diamante de 1 quilate! Porém infelizmente você não coletou nenhum kg de lixo, logo ela é inútil para você..." << endl;
                    }
                    break;
                }
                case 6:
                {
                    int resposta, duplicarDiamantes;

                    tabuleiro[linha][int(coluna-65)] = "$";
                    cout << "Você encontrou um totem duplicador de diamantes! Existem 50% de chance de seus diamantes serem duplicados e 50% de chance de você perder todos os seus diamantes. Você deseja tentar a sorte? (responda com 1 para sim e 0 para nao)" << endl;
                    cin >> resposta;
                    duplicarDiamantes = rand()%101;
                    switch(resposta) {
                        case 0:
                            cout << "Você apenas ignora o totem e nada acontece." << endl;
                            break;
                        case 1:
                            if(duplicarDiamantes > 50) {
                                cout << "O totem conseguiu duplicar seus diamantes!" << endl;
                                quilatesJogadores[i] *= 2;
                                cout << "*Seus quilates dobraram*" << endl;
                            }
                            else {
                                cout << "O totem não conseguiu duplicar seus diamantes!" << endl;
                                quilatesJogadores[i] = 0;
                                cout << "*Você perdeu todos os seus quilates*" << endl;
                            }
                            break;
                    }
                    break;
                }
            }
        }
        qtdRodadas--;
    }
    ranking();
    
    
    return 0;
}