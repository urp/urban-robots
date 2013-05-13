/*
 * gtk-flatdoc
 * Copyright (C) Peter Urban 2009 <s9peurba@stud.uni-saarland.de>
 *
 * gtk-flatdoc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gtk-flatdoc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

# pragma once

# include <cassert>
# include <boost/lexical_cast.hpp>

# include "gl/headers.hpp"

# include <gtkmm.h>
# include <gtkglmm.h>

# include "gtk/gl_view/gl_canvas.hpp"


/* For testing propose use the local (not installed) glade file */
//# define GTK_GLVIEW_BUILDER_FILE PACKAGE_DATA_DIR"/gtk_flatdoc/glade/gl-view.ui" */
# define   GTK_GLVIEW_BUILDER_FILE "gtk/gl_view/gl_view.ui"

namespace gtk
{

  class GLView : public Gtk::VBox
  {
    public:

      struct Filename
      {
        boost::filesystem::path directory;
        boost::filesystem::path filename;
        size_t counter;
        boost::filesystem::path extension;

        Filename( const boost::filesystem::path& dir, const boost::filesystem::path& filename, const size_t& count, const boost::filesystem::path& ext )
        : directory( dir ), filename( filename ), counter( count ), extension( ext )
        {       }

        Filename()
        : directory(), filename("untitled"), counter(0), extension()
        {       }

        boost::filesystem::path operator()  ()
        {
          return ( directory / filename / boost::lexical_cast< std::string > ( counter++ ) ).replace_extension( extension );
        }
      };

    private:

      Glib::RefPtr<Gtk::Builder> m_builder;

      // widgets
      std::shared_ptr< GLCanvas > m_canvas;

      Gtk::CheckButton* m_origin_check;
      Gtk::CheckButton* m_pivot_check;

      //TODO: replace with connection
      Gtk::ToolButton*   m_save_frame_as_button;
      Gtk::ToggleToolButton* m_record_frames_toggle;
      Gtk::MenuToolButton*       m_render_target_menu;

      boost::signals::connection m_record_frames_connection;
      Filename m_record_filename;

      void on_origin_toggled();
      void on_pivot_toggled();

      /*void on_record_frames_toggled();
      void on_save_frame_as_clicked();*/
      void on_block_renderer_clicked();

      void on_record_frame( /*const Glib::RefPtr<Gdk::Pixmap>& pixmap*/ );

    public:

      GLView( BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder );

      ~GLView() {       }

      //void clear() { m_canvas->clear(); }

      void  force_redraw()
      {
        m_canvas->request_redraw();
      }

      std::shared_ptr< GLCanvas > get_canvas() const { return m_canvas; }

      static GLView* create()
      {
        // load the Glade file and instiate its widgets:
        Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file( GTK_GLVIEW_BUILDER_FILE );
        GLView* vp = 0;
        builder->get_widget_derived("gl_view_main_vbox",vp);
        return vp;
      }

  };// of GLView

} // of gtk::
