#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
#include <QStackedLayout>
#include <QGraphicsView>
#include <QMainWindow>

#include "VentanaMenuPrincipal.h"
#include "PanelInformacion.h"
#include "VentanaEmergente.h"
#include "Nivel.h"

class Juego : public QWidget
{
    Q_OBJECT

public:
    explicit Juego(QWidget *parent = nullptr);
    void cargarNivel(TipoNivel tipo);
    void volverAlMenu();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void mostrarNivel1();
    void mostrarNivel2();
    void mostrarNivel3();
    void iniciarJuegoCompleto();

    void mostrarTransicionNivel();
    void mostrarGameOver();
    void verificarGameOver();

private:
    VentanaMenuPrincipal* menu;
    QGraphicsView* vistaNivel;
    Nivel* nivelActual;
    PanelInformacion* panelInfo;

    QStackedLayout* layoutPrincipal;
    QWidget* widgetJuego;
    QHBoxLayout* layoutJuego;
    QTimer* timerActualizacionPanel;

    void conectarSenales();
    void eliminarNivelActual();
    void actualizarPanelInfo();

    void mostrarVentanaEmergente(VentanaEmergente::TipoMensaje tipo, int siguienteNivel = -1);
};

#endif // JUEGO_H
