#include "ObjetoFisico.h"

ObjetoFisico::ObjetoFisico()
    : masa(1.0f), velocidadX(0), velocidadY(0)
{
}

void ObjetoFisico::setMasa(float m) { masa = m; }
void ObjetoFisico::setVelocidad(float vx, float vy) {
    velocidadX = vx;
    velocidadY = vy;
}

float ObjetoFisico::getMasa() const { return masa; }
float ObjetoFisico::getVelocidadX() const { return velocidadX; }
float ObjetoFisico::getVelocidadY() const { return velocidadY; }
