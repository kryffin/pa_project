#ifndef MENU_H
#define MENU_H

/* menu.c */
void render_text(char *string, SDL_Rect pos, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer);
int menu_controls(SDL_Event *event, intpoint_t *mouse_pos);
int main_menu_display (TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint_t *mouse_pos, SDL_Texture *player_tSprite);
bool mouse_hover_menu (intpoint_t mouse_pos, int targetx, int targety, int width, int height);
int option_menu_display (TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint_t *mouse_pos, SDL_Texture *player_tSprite);
int render_menu (bool *quit, TTF_Font *font, SDL_Color palette[15], SDL_Renderer *renderer, intpoint_t *mouse_pos, SDL_Texture *cursor);

#endif
