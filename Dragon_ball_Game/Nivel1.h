#ifndef NIVEL1_H
#define NIVEL1_H

#include "Nivel.h"
#include "Fisica.h"
#include "Goku.h"
#include "Personaje.h"

#include <QTimer>

class Nivel1 : public Nivel
{
    Q_OBJECT

public:
    explicit Nivel1(QObject *parent = nullptr);
    Personaje* getPersonaje() const override;
    bool verificarObjetivoCompleto();

    void detenerTodasLasPlataformas();
    void animarPlataformaFinalYMostrarVentana();
    bool estaEnPlataformaFinal() const;

protected:
    void cargarFondo() override;
    void cargarElementos() override;
    void crearPersonaje() override;
    void agregarItems() override;
    void reiniciarNivel() override;

private:
    void crearSuelosInvisibles();
    void configurarGravedad();
    void agregarPlataformas();
    void actualizarFisica();

    QList<Plataforma*> plataformas;
    QList<QGraphicsRectItem*> suelosInvisibles;

    Goku* goku;
    QTimer* timerCaida;
    float velocidadCaida;
    QTimer* timerFisica;
    Fisica fisica;
    float limiteInferiorY = 600;

    // Variables para gestión de objetivos
    bool objetivoCompletado = false;
    bool plataformasDetenidas = false;
    bool bugReinicioAnulado = false;
};

#endif // NIVEL1_H
