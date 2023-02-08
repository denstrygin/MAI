#include  <SFML/Graphics.hpp>
#include <cmath> // для hypot
using namespace sf;
 
int main() {
    RenderWindow window(VideoMode(500, 500), "laboratory work №2");
    VertexArray line(Lines, 2);
    line[0].position = Vector2f(0, 0);
    line[0].color = Color::Blue;
    line[1].position = Vector2f(500, 500);
 
    //======================================================
    // Конструктор линии с изменяемой толщиной
    //======================================================
    RectangleShape line2(Vector2f(hypot(500, 500), 5));
    // Устанавливаем позицию откуда начинать рисовать
    line2.setPosition(0, 500);
    line2.setFillColor(Color(255, 0, 0));
    // минус рисует вверх
    line2.rotate(-45);
 
    while (window.isOpen()) {
        // Конструктор обработчика событий
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        // Вызовы функций
        window.clear();
        window.draw(line);
        window.draw(line2);
        window.display();
 
    }
    return 0;
}