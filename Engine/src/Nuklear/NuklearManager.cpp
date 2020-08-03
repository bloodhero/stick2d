#include "pch.h"

#include "Nuklear/NuklearManager.h"
#include "Core/Application.h"
#include "Core/Logger.h"
#include "Core/Event.h"

#include "Nuklear/nuklear_sdl_gl3.h"

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024


namespace stick2d {

    void NuklearManager::onAttach()
    {
        m_ctx = nk_sdl_init(theApplication()->getNativeWindow());
        /* Load Fonts: if none of these are loaded a default font will be used  */
        /* Load Cursor: if you uncomment cursor loading please hide the cursor */
        {struct nk_font_atlas* atlas;
        nk_sdl_font_stash_begin(&atlas);
        /*struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);*/
        /*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 16, 0);*/
        /*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
        /*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
        /*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
        /*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
        nk_sdl_font_stash_end();
        /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
        /*nk_style_set_font(ctx, &roboto->handle);*/}

        LOG_TRACE("Nuklear on attach");
    }

    void NuklearManager::onDetach()
    {
        nk_sdl_shutdown();

        LOG_TRACE("Nuklear on detach");
    }

    void NuklearManager::begin()
    {

    }

    void NuklearManager::end()
    {
        nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
    }

    void NuklearManager::inputBegin()
    {
        nk_input_begin(m_ctx);
    }

    void NuklearManager::inputEnd()
    {
        nk_input_end(m_ctx);
    }

    void NuklearManager::onEvent(Event& e)
    {
        nk_sdl_handle_event(&e.event);
    }

}