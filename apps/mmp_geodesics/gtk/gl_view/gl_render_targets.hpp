/***************************************************************************
 *            gl_render_targets.hpp
 *
  *  Copyright  2011-2013 Peter Urban
 *  <urp@pks.mpg.de>
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

# include "gl/render_target.hpp"

# include <gtkmm.h>

# include <gtkglmm.h>

# define DBG_GTK_GL_RENDER_TARGETS

namespace gtk
{
  //---| GLContext

  class GLContext :  public uv::gl::Context
  {
      GLContext() = delete;
      GLContext( const GLContext& ) = delete;


      Glib::RefPtr< Gdk::GL::Context > m_gdk_context;
    protected:

      GLContext( const Glib::RefPtr< const Gdk::GL::Drawable > & gldrawable
               , const std::shared_ptr< const GLContext > &      share_list
               , bool  direct      = true
               , int   render_type = Gdk::GL::RGBA_TYPE
               )
      : uv::gl::Context( *share_list )
      , m_gdk_context( Gdk::GL::Context::create( gldrawable, *share_list, direct, render_type ) )
      { }

      GLContext( const Glib::RefPtr< const Gdk::GL::Drawable > & gldrawable
               , bool direct      = true
               , int  render_type = Gdk::GL::RGBA_TYPE
               )
      : uv::gl::Context()
      , m_gdk_context( Gdk::GL::Context::create( gldrawable, direct, render_type ) )
      { }


    public:

      static std::shared_ptr< GLContext > create( const Glib::RefPtr< const Gdk::GL::Drawable > & gldrawable
                                             , const std::shared_ptr< const GLContext > &         share_list
                                             , bool                                            direct      = true
                                             , int                                             render_type = Gdk::GL::RGBA_TYPE
                                             )
      {
        std::shared_ptr< GLContext > context( share_list
                                           ? new GLContext( gldrawable, share_list, direct, render_type )
                                           : new GLContext( gldrawable, direct, render_type )
                                           );

        assert( Glib::RefPtr< Gdk::GL::Context >( *context ) );

        return context;
      }

      operator Glib::RefPtr< Gdk::GL::Context > ()
      { return m_gdk_context; }

      operator Glib::RefPtr< const Gdk::GL::Context > () const
      { return m_gdk_context; }

      bool is_direct() const
      {
        return m_gdk_context and m_gdk_context->is_direct();
      }

      operator bool () const
      {
        return m_gdk_context;
      }

      // TODO: move out of class ???
      bool is_current() override
      {
        Glib::RefPtr< Gdk::GL::Context > current_context = Gdk::GL::Context::get_current() ;

        return current_context and ( current_context == m_gdk_context );
      }

  };

  //---| GLRenderTarget

  class GLRenderTarget : public uv::gl::RenderTarget
  {

      std::shared_ptr< GLContext > m_gl_context;

      std::shared_ptr< const GLContext > m_shared_gl_context;

    protected:

      void set_shared_gl_context( const std::shared_ptr< const GLContext >& new_shared_context )
      {
        m_shared_gl_context = new_shared_context;
      }

      const std::shared_ptr< const GLContext >& shared_gl_context() const
      {
        return m_shared_gl_context;
      }

      virtual Glib::RefPtr< Gdk::GL::Drawable > gl_drawable() = 0;

      virtual Glib::RefPtr< const Gdk::GL::Config > gl_config() = 0;

      virtual bool prefers_direct_context() const = 0;

      void invalidate_context()
      {
        m_gl_context.reset();
      }

      std::shared_ptr< GLContext > gl_context()
      {

        if( not m_gl_context )
        {
          std::clog << "gtk::GLRenderTarget::gl_context\t| creating new context."
                    << " sharing context " << bool( shared_gl_context() )
                    << " direct " << prefers_direct_context()
                    << " has_drawable " << bool( gl_drawable() )
                    << std::endl;

          // glx requires shared context to live in the same address space ( both direct or indirect, same thread )
          assert( not shared_gl_context() or shared_gl_context()->is_direct() == prefers_direct_context() );

          // direct rendering context

          //Gdk::GL::Context::create( gl_drawable(), shared_gl_context(), prefers_direct_context() );

          m_gl_context = GLContext::create( gl_drawable(), shared_gl_context(), prefers_direct_context() );

          gl_drawable()->make_current( *m_gl_context );

          GLenum err = glewInit();

          if (GLEW_OK != err)
          {
            std::cerr << "gtk::GLContext\t| Error: initGLEW :" << glewGetErrorString( err ) << std::endl;
            std::terminate();
          }

          m_gl_context->gl_info()->print();

          std::cerr << "OK3" << std::endl;

        }

        //std::clog << "gtk::GLRenderTarget::gl_context\t| success " << bool( m_gl_context ) << std::endl;

        return m_gl_context;
      }

      GLRenderTarget( const std::shared_ptr< const GLContext >& shared_gl_context )
      : m_gl_context(), m_shared_gl_context( shared_gl_context )
      { }

      GLRenderTarget( GLRenderTarget& other ) = delete;

    public:

      // define all functions required by uv::gl::RenderTarget
      // except uv::gl::RenderTarget::configure( size_t, size_t )

      bool gl_begin_context() override;

      void gl_end_context() override;

      void gl_flush() override;

  };


  //---| GLDrawingArea

  class GLDrawingArea : public GLRenderTarget, public Gtk::GL::DrawingArea
  {
    protected:

      // from GLRenderTarget

      Glib::RefPtr< Gdk::GL::Drawable > gl_drawable() override
      {
        return Gtk::GL::widget_get_gl_drawable( *this );
      }

      Glib::RefPtr< const Gdk::GL::Config > gl_config() override
      {
        return Gtk::GL::widget_get_gl_config( *this );
      }

      bool prefers_direct_context() const override { return true; }

      // from DrawingArea

      virtual void on_realize() override;

      virtual void on_unrealize() override;


      GLDrawingArea( const std::shared_ptr< const GLContext >& shared_context = std::shared_ptr< const GLContext >()
                   , const Glib::RefPtr< const Gdk::GL::Config >& gl_config = Glib::RefPtr< const Gdk::GL::Config >()
                   );

    public:

      Glib::RefPtr< GLDrawingArea > create( const std::shared_ptr< const GLContext >& shared_context = std::shared_ptr< GLContext >()
                                          , const Glib::RefPtr< const Gdk::GL::Config >& gl_config = Glib::RefPtr< const Gdk::GL::Config >()
                                          )
      {
        return Glib::RefPtr< GLDrawingArea >( new GLDrawingArea() );
      }

      virtual ~GLDrawingArea() {};

      bool is_gl_context_valid() override
      {
        const bool gl_cap = Gtk::GL::widget_is_gl_capable( *this );
        const bool realized = gl_cap and Gtk::DrawingArea::is_realized();
        const bool context = realized and gl_context();
        const bool gdk_context = context and *gl_context();
        const bool drawable = context and gl_drawable();

        const bool is_true = gl_cap and realized and context and gdk_context and drawable;

        std::clog << "gtk::GLDrawingArea::is_gl_context_valid\t| " << is_true << std::endl;

        if( not is_true )
          std::clog << "gtk::GLDrawingArea::is_gl_context_valid\t| context is INVALID"
                    << " gl capability " << gl_cap << " realized " << realized
                    << " gl context " << context
                    << " gdk context " << gdk_context << " gl drawable " << drawable
                    << std::endl;

        return is_true;
      }

      bool configure( const size_t width, const size_t height ) override;

  };

  //---| GLPixmap

  class GLPixmap : public GLRenderTarget
  {
    private:

      // refptr reference to which current pixmap is assigned

      Glib::RefPtr< Gdk::Pixmap > m_pixmap;

      Glib::RefPtr< const Gdk::GL::Config > m_gl_config;

      Glib::RefPtr< Gdk::GL::Drawable > m_gl_drawable;


      Glib::RefPtr< Gdk::GL::Drawable > gl_drawable() override
      {
        return m_gl_drawable;
      }

      Glib::RefPtr< const Gdk::GL::Config > gl_config() override
      {
        return m_gl_config;
      }

      bool prefers_direct_context() const override { return false; }

    public:

      GLPixmap( const size_t width = 400
              , const size_t height = 400
              , const std::shared_ptr< const GLContext > shared_context = std::shared_ptr< const GLContext >()
              );

      bool configure( const size_t width, const size_t height ) override;

      Glib::RefPtr< Gdk::Pixmap > pixmap()
      {
        return m_pixmap;
      }

      bool is_gl_context_valid() override
      {
        return m_pixmap
               && Gdk::GL::ext( m_pixmap ).is_gl_capable()
               && gl_context();
      }

  };

} // of namespace gtk
