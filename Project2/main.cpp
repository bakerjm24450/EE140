/**
 * This program implements a simple image processor. You can load an image
 * and perform several different operations on it.
 *
 * DO NOT MODIFY THIS FILE! THERE IS NOTHING TO CHANGE FOR PROJECT 1!
 */

#ifndef ZYBOOKS

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

#include <iostream>
#include <string>
#include <cstdlib>

#include <tinyfiledialogs.h>

extern "C"
{
#include "image.h"
}

// forward declarations
void updateImage(sf::Texture& texture, Image *image);

int main()
{
    Image image;
    char *filename = NULL;

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "EE 140 Project 2");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    // create a texture for displaying the image
    sf::Texture texture;
    if (!texture.create(800, 600))
    {
        return -1;
    }
    sf::Sprite sprite(texture);

    // make sure our image is initially blank
    image.width = 800;
    image.height = 600;
    image.pixels = (Pixel *) malloc(image.width * image.height * sizeof(Pixel));
    if (image.pixels == NULL)
    {
        return -1;
    }
    memset(image.pixels, 0, image.width * image.height * sizeof(Pixel));

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
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

                    filename = tinyfd_openFileDialog("Open File", "Project2/images/", 1, &filetype, "", 1);

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
        sf::Vector2u imageSize(image.width, image.height);
        if (imageSize != window.getSize())
        {
            // resize the window
            window.create(sf::VideoMode(image.width, image.height), "EE 140 Project 2");

            // resize the texture
            if (!texture.create(image.width, image.height)) {
                std::cout << "Didn't resize texture\n";
            }
        }

        // update the displayed image
        updateImage(texture, &image);

        window.clear();

        // draw the sprite to view image
        sprite.setTexture(texture, true);
        window.draw(sprite);
        
        // draw the gui stuff
        ImGui::SFML::Render(window);
        
        window.display();

    }

    ImGui::SFML::Shutdown();
}

// Update our vertex array for the modified image
void updateImage(sf::Texture& texture, Image *image)
{
    sf::Color *pixels = new sf::Color[image->width*image->height];

    for (int row = 0; row < image->height; row++)
    {
        for (int col = 0; col < image->width; col++)
        {
            int ndx = row * image->width + col;
            pixels[ndx].r = image->pixels[ndx].r;
            pixels[ndx].g = image->pixels[ndx].g;
            pixels[ndx].b = image->pixels[ndx].b;

        }
    }

    // now update the texture
    texture.update((const sf::Uint8*) pixels, image->width, image->height, 0, 0);
}

#else

// This is for the auto-grading on zybooks

int main(void)
{
    return 0;
}

#endif