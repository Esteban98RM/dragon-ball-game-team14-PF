#ifndef VENTANAMENUPRINCIPAL_H
#define VENTANAMENUPRINCIPAL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QTimer>
#include <QSoundEffect>

class VentanaMenuPrincipal : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaMenuPrincipal(QWidget *parent = nullptr);

signals:
    void iniciarJuegoCompleto();  // Modo historia
    void mostrarNivel1();
    void mostrarNivel2();
    void mostrarNivel3();
    void verRecords();

private slots:
    void cambiarColorMarco();

private:
    QPushButton *botonJugar;
    QPushButton *botonNivel1;
    QPushButton *botonNivel2;
    QPushButton *botonNivel3;
    QPushButton *botonRecords;

    QLabel *logoLabel;
    QFrame *marcoLogo;
    QTimer *timerColor;
    QSoundEffect *efectoBoton;

    int colorIndex;
};

#endif // VENTANAMENUPRINCIPAL_H
