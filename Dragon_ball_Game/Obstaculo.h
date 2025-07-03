#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "ObjetoFisico.h"
#include "Personaje.h"
#include <QString>

class Obstaculo : public ObjetoFisico
{
public:
    explicit Obstaculo(const QString& tipo = "escombro", float dano = 1.0f);

    void afectarPersonaje(Personaje* personaje);
    float getDano() const;
    void setDano(float nuevoDano);
    QString getTipo() const;

private:
    float dano;
    QString tipoVisual;
};

#endif // OBSTACULO_H
