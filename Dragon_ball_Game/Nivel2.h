#ifndef NIVEL2_H
#define NIVEL2_H

#include "Nivel.h"
#include "Personaje.h"
#include "Goku.h"

class Nivel2 : public Nivel
{
    Q_OBJECT

public:
    explicit Nivel2(QObject *parent = nullptr);
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

#endif // NIVEL2_H
