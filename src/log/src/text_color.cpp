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

#include "text_color.h"

#include "utils/utils.h"

// Outer namespace
namespace SN {
// Inner namespace
namespace Log {

TextColor_C::TextColor_C()
    : m_attributes(DisplayAttributes_TP::NORMAL),
      m_foreground_color(FGColorCode_TP::DEFAULT),
      m_background_color(BGColorCode_TP::DEFAULT) {}

TextColor_C::~TextColor_C() {}

TextColor_C::TextColor_C(DisplayAttributes_TP attr, FGColorCode_TP fg_color,
                         BGColorCode_TP bg_color)
    : m_attributes(attr),
      m_foreground_color(fg_color),
      m_background_color(bg_color) {}

TextColor_C::TextColor_C(const TextColor_C& rhs)
    : m_attributes(rhs.m_attributes),
      m_foreground_color(rhs.m_foreground_color),
      m_background_color(rhs.m_background_color) {}

TextColor_C& TextColor_C::operator=(const TextColor_C& rhs) {
    m_attributes = rhs.m_attributes;
    m_foreground_color = rhs.m_foreground_color;
    m_background_color = rhs.m_background_color;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const TextColor_C& text_color) {
    return stream << "\033[" << Utils::ToUnderlying(text_color.m_attributes)
                  << "m"
                  << "\033["
                  << Utils::ToUnderlying(text_color.m_foreground_color) << "m"
                  << "\033["
                  << Utils::ToUnderlying(text_color.m_background_color) << "m";
}

}  // end namespace Log
}  // end namespace SN
