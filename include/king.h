#ifndef KING
#define KING

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "moveable.h"
#include "layout.h"

#include "utility/progressBar.h"

/**
 * The player's avatar. Runs from explosive enemies and tries to collect cash
 * to hire soldiers/knights to help him defend himself.
*/
class King : public Moveable {
    public:
        const static int HEALTH;

        King(std::shared_ptr<Layout> layout, std::shared_ptr<sf::RenderWindow> window);
        virtual void update();
        virtual void draw();

        void takeDamage(int damage);
        bool getIsDead();

        int getGridX();
        int getGridY();
        ~King();
    private:
        sf::Texture image;
        sf::Sprite king;

        std::unique_ptr<ProgressBar> healthBar;
        bool isDead;

        sf::Text end;
};

#endif