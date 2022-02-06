#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>

#include <stdio.h>
#include <math.h>

#include "util.c"

sfRenderWindow * create_window(unsigned int width, unsigned int height, char const *title)
{
    sfRenderWindow *Window;
    sfVideoMode mode;

    mode.width = width;
    mode.height = height;
    mode.bitsPerPixel = 256;
    Window = sfRenderWindow_create(mode, title, sfDefaultStyle, NULL);

    return (Window);
}

sfVector2f addVector(sfVector2f vector1, sfVector2f vector2) {

    sfVector2f* new_vector = malloc(sizeof(sfVector2f));

    new_vector->x = vector1.x + vector2.x;
    new_vector->y = vector1.y + vector2.y;

    return *new_vector;
}

sfVector2f create_sfVector2f(float x, float y) {

    sfVector2f increment;

    increment.x = x;
    increment.y = y;

    return increment;
}

void handle_circle_bounce(sfCircleShape* circle, sfRenderWindow* window, sfVector2f* speed) {

    sfVector2f circlePosition = sfCircleShape_getPosition(circle);
    sfVector2u windowSize = sfRenderWindow_getSize(window);

    if (circlePosition.y + 100 >= windowSize.y && speed->y > 0  || circlePosition.y < 0 && speed->y < 0) {

        speed->y = - speed->y;

        sfColor actual_color = sfCircleShape_getFillColor(circle);
        actual_color.r +=  10;

        sfCircleShape_setFillColor(circle, actual_color);

    }

    if ( circlePosition.x + 100 >= windowSize.x && speed->x > 0  || circlePosition.x < 0 && speed->x < 0) {
        speed->x = - speed->x;

        sfColor actual_color = sfCircleShape_getFillColor(circle);
        actual_color.g +=  10;

        sfCircleShape_setFillColor(circle, actual_color);

    }

    sfCircleShape_setPosition(circle, addVector(circlePosition, *speed));
}


int main()
{
    sfRenderWindow* window = create_window(800, 750, "CSFML");
    
    sfEvent event;
    
    // DESSIN DU CERCLE
    sfCircleShape* circle = sfCircleShape_create();
    sfCircleShape_setRadius(circle, 50);
    sfCircleShape_setFillColor(circle, sfColor_fromRGB(50,50,50));
    sfCircleShape_setPosition(circle, create_sfVector2f(-100,-100));


    sfCircleShape* circle2 = sfCircleShape_create();
    sfCircleShape_setRadius(circle2, 50);
    sfCircleShape_setFillColor(circle2, sfColor_fromRGB(50,50,50));
    sfCircleShape_setPosition(circle2, create_sfVector2f(800,750));

    sfVector2f speed1 = create_sfVector2f(1,1);
    sfVector2f speed2 = create_sfVector2f(-1,-1);
    

    while (sfRenderWindow_isOpen(window))
    {
        //sfRenderWindow_clear(window, sfBlack);

        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape)) {
                sfRenderWindow_close(window);
            }
   
        }

        /*
        // DESSIN CERCLE QUAND LE BOUTON GAUCHE EST APPUYE
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            sfVector2i mousePos = sfMouse_getPositionRenderWindow(window);

            sfCircleShape_setPosition(circle, vectorItoF(mousePos));

            sfRenderWindow_drawCircleShape(window, circle, NULL);
        }
        */

        handle_circle_bounce(circle, window, &speed1);
        handle_circle_bounce(circle2, window, &speed2);

        //printf("CIRCLE POS: x: %f | y: %f\n", sfCircleShape_getPosition(circle).x, sfCircleShape_getPosition(circle).y);
        
        sfRenderWindow_drawCircleShape(window, circle, NULL);
        sfRenderWindow_drawCircleShape(window, circle2, NULL);

        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
    return 0;
}
