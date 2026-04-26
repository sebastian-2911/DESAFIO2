cmake_minimum_required(VERSION 3.16)

project(DESAFIO2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DESAFIO2 main.cpp
    torneo.h torneo.cpp
    fase.h fase.cpp
    equipo.h equipo.cpp
    jugador.h jugador.cpp
    grupo.h grupo.cpp
    partido.h partido.cpp
    eliminatoria.h eliminatoria.cpp
    archivo.h archivo.cpp
    util.h util.cpp
    metricas.h metricas.cpp
    estadisticas.h
    clasificado.h)

include(GNUInstallDirs)
install(TARGETS DESAFIO2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
