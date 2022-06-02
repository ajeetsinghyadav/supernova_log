/* ---------------------------------------------------------------------
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the Apache License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Apache License 2.0 for more details.
 *
 * You should have received a copy of the Apache License
 * along with this program.  If not, see
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 * Copyright (C) 2021 Ajeet Singh Yadav [ er.ajeetsinghyadav@gmail.com ]
 *
 * Author:    Ajeet Singh Yadav
 * Created:   MAY-2021
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file text_color.h
 *
 * @brief TextColor_C class is used to format and set the foreground and
 * background color of the console output.
 *
 * @author Ajeet Singh Yadav
 * Contact: er.ajeetsinghyadav@gmail.com
 *
 */

#pragma once

// Standard Includes
#include <iostream>
#include <ostream>
#include <type_traits>

// Outer namespace
namespace SN {
// Inner namespace
namespace Log {

/**
 * @enum FGColorCode_TP
 *
 * @brief Option to set console log message color.
 *
 */
enum class FGColorCode_TP {
    BLACK = 30,          //!< Black foreground color(30)
    RED = 31,            //!< Red foreground color(31)
    GREEN = 32,          //!< Green foreground color(32)
    YELLOW = 33,         //!< Yellow foreground color(33)
    BLUE = 34,           //!< Blue foreground color(34)
    MAGENTA = 35,        //!< Magenta foreground color(35)
    CYAN = 36,           //!< Cyan foreground color(36)
    LIGHT_GRAY = 37,     //!< Light gray foreground color(37)
    DEFAULT = 39,        //!< Default console foreground color(39)
    DARK_GRAY = 90,      //!< Dark gray foreground color(90)
    LIGHT_RED = 91,      //!< Light red foreground color(91)
    LIGHT_GREEN = 92,    //!< Light green foreground color(92)
    LIGHT_YELLOW = 93,   //!< Light yellow foreground color(93)
    LIGHT_BLUE = 94,     //!< Light blue foreground color(94)
    LIGHT_MAGENTA = 95,  //!< Light magenta foreground color(95)
    LIGHT_CYAN = 96,     //!< Light cyan foreground color(96)
    WHITE = 97           //!< White foreground color(97)
};

/**
 * @enum BGColorCode_TP
 *
 * @brief Option to set background color to console log messages.
 *
 */
enum class BGColorCode_TP {
    BLACK = 40,           //!< Black background color(40)
    RED = 41,             //!< Red background color(41)
    GREEN = 42,           //!< Green background color(42)
    YELLOW = 43,          //!< Yellow background color(43)
    BLUE = 44,            //!< Blue background color(44)
    MAGENTA = 45,         //!< Magenta background color(45)
    CYAN = 46,            //!< Cyan background color(46)
    LIGHT_GRAY = 47,      //!< White background color(47)
    DEFAULT = 49,         //!< Default console background color(49)
    DARK_GRAY = 100,      //!< Dark gray foreground color(90)
    LIGHT_RED = 101,      //!< Light red foreground color(91)
    LIGHT_GREEN = 102,    //!< Light green foreground color(92)
    LIGHT_YELLOW = 103,   //!< Light yellow foreground color(93)
    LIGHT_BLUE = 104,     //!< Light blue foreground color(94)
    LIGHT_MAGENTA = 105,  //!< Light magenta foreground color(95)
    LIGHT_CYAN = 106,     //!< Light cyan foreground color(96)
    WHITE = 107           //!< White foreground color(97)
};

/**
 * @enum DisplayAttributes_TP
 *
 * @brief Option to set different display attribute parameters.
 *
 */
enum class DisplayAttributes_TP {
    NORMAL = 0,      //!< All attributes off(0)
    BOLD = 1,        //!< Bold or increased intensity(1)
    FAINT = 2,       //!< Faint, decreased intensity or dim(2)
    ITALIC = 3,      //!< Italic(3)
    UNDER_LINE = 4,  //!< Underline text(4)
    BLINK = 5,       //!< Slow blink (less than 150 per minute)(5)
    REVERSE = 7,     //!< Swap foreground and background colors(7)
    HIDDEN = 8       //!< To hide the console text(8)
};

/** SN::Log::TextColor_C
 *
 * @b Description
 * This class is used to color and format the console (terminal) text.
 * It supports most commonly used control sequence for formatting text.
 * Also, supports most commonly used foreground and background text color.
 *
 * @note
 * https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 * https://misc.flogisoft.com/bash/tip_colors_and_formatting
 */
class TextColor_C {
   public:
    /**
     * Default constructor.
     *
     * Initialize the attributes, foreground, and background
     * colors parameters.
     *
     */
    TextColor_C();

    /**
     * Default destructor
     *
     */
    ~TextColor_C();

    /**
     * Parametric constructor.
     *
     * @param attr display attribute enum value
     * @param fg_color text foreground color enum value
     * @param bg_color text background color enum value
     *
     */
    TextColor_C(DisplayAttributes_TP attr, FGColorCode_TP fg_color,
                BGColorCode_TP bg_color);

    /**
     * Copy constructor.
     *
     * @param rhs the object to make this object a copy of.
     *
     */
    TextColor_C(const TextColor_C& rhs);

    /**
     * Assignment operator.
     *
     * @param rhs the object to copy the state from.
     * @retval a reference to *this
     *
     */
    TextColor_C& operator=(const TextColor_C& rhs);

    /**
     * Stream operator<< for the log severity level
     *
     * @param stream output stream
     * @param text_color the object of the TextColor_C
     *
     * @retval output stream
     *
     */
    friend std::ostream& operator<<(std::ostream& stream,
                                    const TextColor_C& text_color);

   private:
    DisplayAttributes_TP m_attributes;
    FGColorCode_TP m_foreground_color;
    BGColorCode_TP m_background_color;
};  // end TextColor_C

}  // end namespace Log
}  // namespace SN
