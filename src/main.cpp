#include <CLI/CLI.hpp>
#include <QApplication>
#include <QLabel>
#include <QScreen>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <spdlog/spdlog.h>
#include <sys/types.h>
#include <unistd.h> // fork(), setsid()

#include "version.hpp"

auto main( int argc, char** argv ) -> int
{
    CLI::App cli{ "Qt6 Popup Utility" };

    std::string message = "Default Message";
    cli.add_option( "message", message, "Message to display" )->required();

    int timeout_ms = 3000;
    cli.add_option( "--timeout", timeout_ms, "Timeout in milliseconds" )->check( CLI::PositiveNumber );

    bool forking = true;
    cli.add_flag( "--no-fork", forking, "Run in foreground (don’t fork)" );

    bool debug = false;
    cli.add_flag( "-d,--debug", debug, "Enable debug mode" );

    CLI11_PARSE( cli, argc, argv );
    spdlog::level::level_enum log_level = spdlog::level::info;

    if( debug ) {
        log_level = spdlog::level::debug;
    }

    spdlog::set_pattern( "[%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] [%s:%#] %v" );
    spdlog::set_level( log_level );

    if( forking ) {
        pid_t pid = fork();

        if( pid < 0 ) {
            SPDLOG_ERROR( "fork" );
            return 1;
        }

        if( pid > 0 ) {
            return 0;
        }

        setsid();
    }

    QApplication app( argc, argv );

    QWidget popup;
    popup.setWindowFlags( Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
    popup.setAttribute( Qt::WA_TranslucentBackground );
    popup.setStyleSheet( "background-color: black; color: white; border-radius: 10px;" );

    QVBoxLayout layout( &popup );
    QLabel label( QString::fromStdString( message ) );
    label.setWordWrap( true );
    label.setAlignment( Qt::AlignCenter );
    label.setStyleSheet( "font-size: 18px; padding: 20px;" );
    layout.addWidget( &label );

    popup.adjustSize();

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    popup.move( screenGeometry.center() - popup.rect().center() );

    popup.show();

    QTimer::singleShot( timeout_ms, &app, &QApplication::quit );

    SPDLOG_INFO( "Done." );
    return app.exec();
}
