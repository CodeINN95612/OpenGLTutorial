#pragma once

#include <cstdint>

namespace GL
{
    #define GL_SCANCODE_MASK (1<<30)
    #define GL_SCANCODE_TO_KEYCODE(X)  (X | GL_SCANCODE_MASK)

	enum class TecladoTecla : int32_t
	{
        Enter = '\r',
        Esc = '\x1B',
        Borrar = '\b',
        Tab = '\t',
        Espacio = ' ',
        Exclamacion = '!',
        Comillas = '"',
        Hash = '#',
        Porcentaje = '%',
        Dolar = '$',
        Ampersand = '&',
        ComillaSimple = '\'',
        ParentesisI = '(',
        parentesisD = ')',
        Asterisco = '*',
        Mas = '+',
        Coma = ',',
        Menos = '-',
        Punto = '.',
        Slash = '/',
        Numero_0 = '0',
        Numero_1 = '1',
        Numero_2 = '2',
        Numero_3 = '3',
        Numero_4 = '4',
        Numero_5 = '5',
        Numero_6 = '6',
        Numero_7 = '7',
        Numero_8 = '8',
        Numero_9 = '9',
        DosPuntos = ':',
        PuntoComa = ';',
        Menor = '<',
        Igual = '=',
        Mayor = '>',
        InterrogacionCierre = '?',

        CorcheteI = '[',
        SlashAtras = '\\',
        CrocheteD = ']',
        Caret = '^',
        GuionBajo = '_',
        ComillaAtras = '`',
        Letra_a = 'a',
        Letra_b = 'b',
        Letra_c = 'c',
        Letra_d = 'd',
        Letra_e = 'e',
        Letra_f = 'f',
        Letra_g = 'g',
        Letra_h = 'h',
        Letra_i = 'i',
        Letra_j = 'j',
        Letra_k = 'k',
        Letra_l = 'l',
        Letra_m = 'm',
        Letra_n = 'n',
        Letra_o = 'o',
        Letra_p = 'p',
        Letra_q = 'q',
        Letra_r = 'r',
        Letra_s = 's',
        Letra_t = 't',
        Letra_u = 'u',
        Letra_v = 'v',
        Letra_w = 'w',
        Letra_x = 'x',
        Letra_y = 'y',
        Letra_z = 'z',

        Mayuscula = GL_SCANCODE_TO_KEYCODE(57),

        F1 = GL_SCANCODE_TO_KEYCODE(58),
        F2 = GL_SCANCODE_TO_KEYCODE(59),
        F3 = GL_SCANCODE_TO_KEYCODE(60),
        F4 = GL_SCANCODE_TO_KEYCODE(51),
        F5 = GL_SCANCODE_TO_KEYCODE(52),
        F6 = GL_SCANCODE_TO_KEYCODE(53),
        F7 = GL_SCANCODE_TO_KEYCODE(54),
        F8 = GL_SCANCODE_TO_KEYCODE(55),
        F9 = GL_SCANCODE_TO_KEYCODE(56),
        F10 = GL_SCANCODE_TO_KEYCODE(57),
        F11 = GL_SCANCODE_TO_KEYCODE(58),
        F12 = GL_SCANCODE_TO_KEYCODE(59),

        KP_BloqueoNumeros = GL_SCANCODE_TO_KEYCODE(83),
        KP_Dividir = GL_SCANCODE_TO_KEYCODE(84),
        KP_Multiplicar = GL_SCANCODE_TO_KEYCODE(85),
        KP_Menos = GL_SCANCODE_TO_KEYCODE(86),
        KP_Mas = GL_SCANCODE_TO_KEYCODE(87),
        KP_Enter = GL_SCANCODE_TO_KEYCODE(88),
        KP_1 = GL_SCANCODE_TO_KEYCODE(89),
        KP_2 = GL_SCANCODE_TO_KEYCODE(90),
        KP_3 = GL_SCANCODE_TO_KEYCODE(91),
        KP_4 = GL_SCANCODE_TO_KEYCODE(92),
        KP_5 = GL_SCANCODE_TO_KEYCODE(93),
        KP_6 = GL_SCANCODE_TO_KEYCODE(94),
        KP_7 = GL_SCANCODE_TO_KEYCODE(95),
        KP_8 = GL_SCANCODE_TO_KEYCODE(96),
        KP_9 = GL_SCANCODE_TO_KEYCODE(97),
        KP_0 = GL_SCANCODE_TO_KEYCODE(98),
        KP_Punto = GL_SCANCODE_TO_KEYCODE(99),

        LCTRL = GL_SCANCODE_TO_KEYCODE(224),
        LSHIFT = GL_SCANCODE_TO_KEYCODE(225),
        LALT = GL_SCANCODE_TO_KEYCODE(226),
        LWIN = GL_SCANCODE_TO_KEYCODE(227),
        RCTRL = GL_SCANCODE_TO_KEYCODE(228),
        RSHIFT = GL_SCANCODE_TO_KEYCODE(229),
        RALT = GL_SCANCODE_TO_KEYCODE(230),
        RWIN = GL_SCANCODE_TO_KEYCODE(231),

        Derecha = GL_SCANCODE_TO_KEYCODE(79),
        Izquierda = GL_SCANCODE_TO_KEYCODE(80),
        Abajo = GL_SCANCODE_TO_KEYCODE(81),
        Arriba = GL_SCANCODE_TO_KEYCODE(82),
	};
}
