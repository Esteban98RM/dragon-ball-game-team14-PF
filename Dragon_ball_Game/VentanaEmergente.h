#ifndef VENTANAEMERGENTE_H
#define VENTANAEMERGENTE_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFontDatabase>

class VentanaEmergente : public QDialog {
    Q_OBJECT

public:
    enum TipoMensaje {
        GAME_OVER,
        NIVEL_COMPLETADO,
        JUEGO_COMPLETADO
    };

    explicit VentanaEmergente(TipoMensaje tipo, QWidget *parent = nullptr);

signals:

    void volverAlMenu();
    void siguienteNivel();
    void reintentarNivel();


private:
    void configurarEstilo();
};

#endif // VENTANAEMERGENTE_H
