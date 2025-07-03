#ifndef NIVEL3_H
#define NIVEL3_H

#include "Nivel.h"
#include "Personaje.h"
#include "Goku.h"

class Nivel3 : public Nivel
{
    Q_OBJECT

public:
    explicit Nivel3(QObject *parent = nullptr);
    Personaje* getPersonaje() const override;
    bool verificarObjetivoCompleto();

protected:
    void cargarFondo() override;
    void cargarElementos() override;
    void crearPersonaje() override;
    void agregarItems() override;
    void reiniciarNivel() override;

private:
    Goku* goku;

};

#endif // NIVEL3_H
