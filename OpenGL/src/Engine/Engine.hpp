#pragma once

//Matematicas
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

//Eventos
#include "Eventos/IManejadorDeEventos.hpp"

//Plataforma
#include "Plataforma/Defines.hpp"
#include "Plataforma/Assert.hpp"
#include "Plataforma/Logger.hpp"
#include "Plataforma/Window.hpp"
#include "Plataforma/MouseBoton.hpp"
#include "Plataforma/TecladoTecla.hpp"
#include "Plataforma/Input.hpp"

//Excepciones
#include "Excepciones/Excepcion.hpp"

//Renderizador
#include "Renderizador/Shader.hpp"
#include "Renderizador/VertexBuffer.hpp"
#include "Renderizador/IndexBuffer.hpp"
#include "Renderizador/VertexArray.hpp"
#include "Renderizador/Imagen.hpp"
#include "Renderizador/Textura.hpp"
#include "Renderizador/Renderizador.hpp"
#include "Renderizador/Color.hpp"

//Gui
#include "Engine/Libs/imgui/imgui.h"
#include "Engine/Gui/Gui.hpp"

//Game
#include "Engine/Game/CamaraOrtografica.hpp"
#include "Engine/Game/ObjetoJuego.hpp"
