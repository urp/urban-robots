
/***************************************************************************
 *            gl-drawable.h
 *
 *  Fri Nov 13 20:00:40 2009
 *  Copyright  2009  Peter Urban
 *  <s9peurba@stud.uni-saarland.de>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

# pragma once

# include "gl/context.hpp"

# include <boost/signals.hpp>

# include <gtkmm/widget.h>

# include "common.hpp"

namespace uv
{
  namespace gl
  {
    class Drawable
    {
      public:

        typedef boost::signal<void()>     invalidate_signal;
        typedef boost::signal<void()>     remove_signal;

      private:

        // inform all views that drawable needs redraw
        invalidate_signal invalidate_drawable;

        // order all views to remove the drawable
        remove_signal remove_drawable;

      protected:

        Drawable()  {     }

        Drawable( const Drawable& ) = delete;

      public:

        virtual ~Drawable()
        {
          std::clog << "gl::Drawable::~Drawable\t|" << std::endl << std::flush;
        }

        boost::signals::connection connect_invalidator( invalidate_signal::slot_type invalidator )
        { return invalidate_drawable.connect( invalidator ); }

        boost::signals::connection connect_remover( remove_signal::slot_type remover )
        { return remove_drawable.connect( remover ); }

        void remove_from_all_views() { remove_drawable(); }

        void invalidate()
        {
          std::clog << "gl::Drawable::invalidate\t|invalidating drawable" << std::endl;
          invalidate_drawable();
        }

        virtual void gl_initialize_context( const std::shared_ptr< uv::gl::Context >& context ) = 0;

        virtual void gl_draw( const std::shared_ptr< uv::gl::Context >& context ) = 0;

        virtual void gl_remove_from_context( const std::shared_ptr< uv::gl::Context >& context ) = 0;

    };

  } // of gl::
} // of ::uv::
