/**
 * This program implements a simple image processor. You can load an image
 * and perform several different operations on it.
 *
 * DO NOT MODIFY THIS FILE! THERE IS NOTHING TO CHANGE FOR PROJECT 1!
 */

#ifndef ZYBOOKS

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>

#include "tinyfiledialogs.h"

extern "C"
{
#include "image.h"
}

// forward declarations
void updateImage(sf::Texture &texture, Image *image);

int main()
{
    Image image;
    char *filename = NULL;

    srand((unsigned int) time(NULL));

    // SFML 3 style: VideoMode takes a Vector2u
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "EE 140 Project 2");
    window.setVerticalSyncEnabled(true);
    assert(ImGui::SFML::Init(window));

    // create a texture for displaying the image (SFML 3 constructor with size)
    sf::Texture texture(sf::Vector2u(800, 600));
    sf::Sprite sprite(texture);

    // make sure our image is initially blank
    image.width = 800;
    image.height = 600;
    image.pixels = (Pixel *)malloc(image.width * image.height * sizeof(Pixel));
    if (image.pixels == NULL)
    {
        return -1;
    }
    memset(image.pixels, 0, image.width * image.height * sizeof(Pixel));

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        // SFML 3: pollEvent() returns std::optional<sf::Event>
        while (const auto event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // build the menu and handle menu items
        if (ImGui::BeginMainMenuBar())
        {

            // file menu
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open"))
                {
                    const char *filetype = "*.ppm";

                    filename = tinyfd_openFileDialog("Open File", "images/", 1, &filetype, "", 1);

                    readImage(filename, &image);
                }
                if (ImGui::MenuItem("Reload image"))
                {
                    readImage(filename, &image);
                }
                if (ImGui::MenuItem("Exit"))
                {
                    window.close();
                }

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Tools"))
            {
                if (ImGui::MenuItem("Grayscale"))
                {
                    grayscale(&image);
                }
                if (ImGui::MenuItem("Laplacian Edge Enhancement"))
                {
                    laplacian(&image);
                }

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Extra Credit"))
            {
                if (ImGui::MenuItem("Rotate"))
                {
                    double angle = 5.0 * (rand() % 7) + 30.0;
                    rotate(&image, angle);
                }
                if (ImGui::MenuItem("Reduce Size"))
                {
                    reduceSize(&image);
                }
                if (ImGui::MenuItem("Posterize"))
                {
                    posterize(&image);
                }
                if (ImGui::MenuItem("Grayscale+Red"))
                {
                    grayscaleRed(&image);
                }

                ImGui::EndMenu();
            }

            // open Dialog Simple

            ImGui::EndMainMenuBar();
        }

        // do we need to resize the window and texture? Image size might have changed
        sf::Vector2u imageSize(
            static_cast<unsigned>(image.width),
            static_cast<unsigned>(image.height));

        if (imageSize != window.getSize())
        {
            // resize the window
            window.create(sf::VideoMode(imageSize), "EE 140 Project 2");

            // resize the texture (SFML 3)
            if (!texture.resize(imageSize))
            {
                std::cout << "Didn't resize texture\n";
            }

            // keep sprite bound to the (possibly resized) texture
            sprite.setTexture(texture, true);
        }

        // update the displayed image
        updateImage(texture, &image);

        window.clear();

        // draw the sprite to view image
        window.draw(sprite);

        // draw the gui stuff
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
}

// Update our texture for the modified image
void updateImage(sf::Texture &texture, Image *image)
{
    // allocate an array of sf::Color pixels
    sf::Color *pixels = new sf::Color[image->width * image->height];

    for (int row = 0; row < image->height; row++)
    {
        for (int col = 0; col < image->width; col++)
        {
            int ndx = row * image->width + col;
            pixels[ndx].r = image->pixels[ndx].r;
            pixels[ndx].g = image->pixels[ndx].g;
            pixels[ndx].b = image->pixels[ndx].b;
            // alpha left at default (opaque)
        }
    }

    // SFML 3: update(texture) from raw RGBA bytes; size is taken from the texture itself
    texture.update((const uint8_t *)pixels);

    // optional cleanup (the original code leaked this, but it's safe to delete)
    delete[] pixels;
}

#else

// This is for the auto-grading on zybooks

int main(void)
{
    return 0;
}

#endif
