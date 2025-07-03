#ifndef FISICA_H
#define FISICA_H

#include "Personaje.h"
#include "Caparazon.h"
#include "Plataforma.h"
#include "ObjetoFisico.h"

class Fisica
{
public:
    Fisica();

    void aplicarGravedad(Personaje* personaje);
    bool verificarColisionSuelo(Personaje* personaje, Plataforma* plataforma);

    void calcularTiroParabolico(float angulo, float velocidad);
    void calcularTiroRecto(float velocidad);

    void aplicarResistencia(Personaje* personaje, const Caparazon& caparazon);
    void afectarObjeto(ObjetoFisico* objeto);  // placeholder para más adelante

    void actualizarFisicaSalto(Personaje* personaje, const QList<QGraphicsItem*>& colisiones);
};

#endif // FISICA_H
