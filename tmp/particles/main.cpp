int main()
{
    // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(512, 256), "Particles");

    // on crée un système de 1000 particules
    ParticleSystem particles(1000);

    // on crée un chrono pour mesurer le temps écoulé
    sf::Clock clock;

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // on fait en sorte que l'émetteur des particules suive la souris
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        // on met à jour le système de particules
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        // on le dessine
        window.clear();
        window.draw(particles);
        window.display();
    }

    return 0;
}
