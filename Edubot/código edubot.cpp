#include <iostream>
#include <stdlib.h>
#include "libs/EdubotLib.hpp"

#define MIN_DIST 0.07 // distancia minima frontal
#define SPEED 0.2     // velocidade
#define TIME 2000     // tempo de movimento em milissegundos

#define MIN_DIST_SIDE (3 * MIN_DIST) // distancia minima lateral, 3x a distancia frontal

EdubotLib *edubot = new EdubotLib(); // criando instancia do edubot

// rotina pra lidar com colisao
bool colisionRoutine()
{
    // verifica se algum dos bumpers do edubot foi ativado
    if (edubot->getBumper(0) || edubot->getBumper(1) || edubot->getBumper(2) || edubot->getBumper(3))
    {
        float speed = (edubot->getBumper(0) || edubot->getBumper(1)) ? -SPEED / 2 : SPEED / 2;

        // para o edubot e move ele pra frente ou pra tras devagar
        edubot->stop();
        edubot->move(speed);
        edubot->sleepMilliseconds(1000); // espera um pouquinho enquanto move
        edubot->stop();                  // para de novo
        edubot->sleepMilliseconds(1000); // espera um segundo

        double angle = edubot->getTheta(); // pega o angulo atual
        // rotaciona o edubot com base no angulo atual pra evitar colisao
        if (angle < 90)
            edubot->rotate(-angle);
        else if (angle < 180)
            edubot->rotate(-(angle - 90));
        else if (angle < 270)
            edubot->rotate(angle - 180);
        else
            edubot->rotate(angle - 270);

        edubot->sleepMilliseconds(2000); // espera dois segundos
        edubot->stop();                  // para depois de rotacionar

        return true; // retorna que houve colisao
    }
    return false; // retorna que nao houve colisao
}

int main()
{
    // tenta conectar ao edubot
    if (edubot->connect())
    {
        edubot->sleepMilliseconds(2000); // espera um pouquinho pra estabilizar a conexao

        // loop principal enquanto o edubot ta conectado
        while (edubot->isConnected())
        {
            // se nao houver colisao
            if (!colisionRoutine())
            {
                edubot->move(SPEED); // comeca a mover com a velocidade definida

                // continua movendo enquanto a distancia ta segura
                while (edubot->getSonar(3) >= MIN_DIST && (edubot->getSonar(6) <= MIN_DIST_SIDE || edubot->getSonar(0) <= MIN_DIST_SIDE))
                    ;

                // se as distancias estiverem seguras, segue em frente
                if (edubot->getSonar(3) >= MIN_DIST && edubot->getSonar(6) >= MIN_DIST_SIDE && edubot->getSonar(0) >= MIN_DIST_SIDE)
                {
                    edubot->move(SPEED / 2);         // vai mais devagar
                    edubot->sleepMilliseconds(TIME); // move por um tempo definido
                    edubot->stop();                  // para
                    edubot->sleepMilliseconds(1000); // espera um segundo

                    // escolhe aleatoriamente entre girar 90 graus pra esquerda ou direita
                    switch (rand() % 3)
                    {
                    case 0:
                        edubot->rotate(90);
                        break;
                    case 1:
                        edubot->rotate(-90);
                        break;
                    }
                    edubot->sleepMilliseconds(2000); // espera dois segundos depois de girar
                    edubot->stop();                  // para de novo
                    edubot->move(3 * SPEED);         // continua movendo
                }
                else
                {
                    edubot->stop(); // para o robô

                    // se estiver muito perto de algo dos dois lados, gira 180 graus
                    if (edubot->getSonar(6) <= MIN_DIST_SIDE && edubot->getSonar(0) <= MIN_DIST_SIDE)
                        edubot->rotate(180);

                    // senao, gira 90 graus pro lado mais seguro
                    else
                        edubot->rotate(edubot->getSonar(6) <= MIN_DIST_SIDE ? -90 : 90);

                    edubot->sleepMilliseconds(2000);
                    // espera dois segundos depois de girar
                }
            }
        }
        edubot->disconnect(); // desconecta o edubot quando terminar
    }
    else
    {
        std::cout << "Could not connect to robot!\n";
        // mensagem se a conexao falhar
    }

    return 0;
}