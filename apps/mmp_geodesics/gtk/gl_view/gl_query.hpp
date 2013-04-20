
// flatter - gl_tools.h
// Copyright (C) 2006-2011  Peter Urban (peter.urban@s2003.tu-chemnitz.de)
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#pragma once

#include "gtk/gl_view/gl_canvas.hpp"

namespace gtk
{

  //
  // OpenGL frame buffer configuration utilities.
  //

  struct gl_query
  {
    static void print_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig,
                                const char* attrib_str,
                                int attrib,
                                bool is_boolean);

    static void examine_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig);
  };
}
