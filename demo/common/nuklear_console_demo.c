#include <string.h>

#include "../../nuklear_console.h"

#include "../../vendor/nuklear/demo/common/style.c"

struct nk_console* console;
static nk_size progressValue = 50;
static int weapon = 1;
static int property_int_test = 20;
static float property_float_test = 0.4f;
static int slider_int_test = 20;
static float slider_float_test = 0.4f;
static int theme = 4;

void button_clicked(struct nk_console* button) {
    if (strcmp(button->text, "Quit Game") == 0) {
        // Leverage the userdata to indicate whether or not we're to quit.
        button->context->userdata.id = 1;
    }
}
void theme_changed(struct nk_console* combobox) {
    set_style(combobox->context, theme);
}

void nuklear_console_demo_init(struct nk_context* ctx) {
    console = nk_console_init(ctx);

    // New Game
    nk_console* newgame = nk_console_add_button(console, "New Game");
    {
        newgame->button.symbol = NK_SYMBOL_PLUS;
        nk_console_add_label(newgame, "This would start a new game!");
        nk_console_add_button_onclick(newgame, "Back", nk_console_onclick_back);
    }

    // Options
    nk_console* options = nk_console_add_button(console, "Options");
    {
        nk_console_add_checkbox(options, "Show Window Title", &showWindowTitle);
        nk_console_add_progress(options, "Progress", &progressValue, 100);
        nk_console_add_combobox(options, "ComboBox", "Fists;Chainsaw;Pistol;Shotgun;Chaingun", ';', &weapon);
        nk_console_add_property_int(options, "Property Int", 10, &property_int_test, 30, 1, 1);
        nk_console_add_property_float(options, "Property Float", 0.0f, &property_float_test, 2.0f, 0.1f, 1);
        nk_console_add_slider_float(options, "Slider Float", 0.0f, &slider_float_test, 2.0f, 0.1f);
        nk_console_add_slider_int(options, "Slider Int", 0, &slider_int_test, 20, 1);

        nk_console_add_button_onclick(options, "Back", nk_console_onclick_back)->button.symbol = NK_SYMBOL_TRIANGLE_LEFT;
    }
    nk_console_add_combobox(console, "Theme", "Black;White;Red;Blue;Dark;Dracula;Default", ';', &theme)->onchange = theme_changed;
    set_style(ctx, theme);
    nk_console_add_button(console, "Save Game");
    nk_console_add_button(console, "Quit Game")->button.onclick = button_clicked;
}

nk_bool nuklear_console_demo_render() {
    nk_console_render(console);

    if (console->context->userdata.id == 1) {
        return nk_true;
    }

    return nk_false;
}

void nuklear_console_demo_free() {
    nk_console_free(console);
}
