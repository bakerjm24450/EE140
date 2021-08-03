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

#include <imgui.h>
#include <imgui-SFML.h>

#include <iostream>
#include <string>

#include <tinyfiledialogs.h>

extern "C"
{
#include "image.h"
}

// forward declarations
void readImage(const char *filename, unsigned char image[512][512]);
void updateTexture(sf::Texture &texture, unsigned char image[512][512]);

int main()
{
    unsigned char image[512][512];
    char *filename = NULL;

    sf::RenderWindow window(sf::VideoMode(512, 512), "EE 140 Project 1");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    // create a texture and sprite for displaying the image
    sf::Texture texture;
    if (!texture.create(512, 512))
    {
        return -1;
    }
    sf::Sprite sprite(texture); // use a sprite to display the texture

    // make sure our image is initially blank
    memset(image, 0, 512 * 512);

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
                    const char *filetype = "*.pgm";

                    filename = tinyfd_openFileDialog("Open File", "Project1/images/", 1, &filetype, "", 1);

                    readImage(filename, image);
                }
                if (ImGui::MenuItem("Reload image"))
                {
                    readImage(filename, image);
                }
                if (ImGui::MenuItem("Exit"))
                {
                    window.close();
                }

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Tools"))
            {
                if (ImGui::MenuItem("Dim"))
                {
                    dim(image);
                }
                if (ImGui::MenuItem("Inverse"))
                {
                    inverse(image);
                }
                if (ImGui::MenuItem("Rotate"))
                {
                    rotate(image);
                }
                if (ImGui::MenuItem("Low Pass Filter"))
                {
                    lowpass(image);
                }
                if (ImGui::MenuItem("High Pass Filter"))
                {
                    highpass(image);
                }
                if (ImGui::MenuItem("Median Filter"))
                {
                    median(image);
                }

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Extra Credit"))
            {
                if (ImGui::MenuItem("Zoom"))
                {
                    zoom(image);
                }
                if (ImGui::MenuItem("Tile"))
                {
                    tile(image);
                }
                if (ImGui::MenuItem("Sobel Edge Detection"))
                {
                    edge(image);
                }
                if (ImGui::MenuItem("Threshold"))
                {
                    threshold(image);
                }
                if (ImGui::MenuItem("Histogram"))
                {
                    histogram(image);
                }

                ImGui::EndMenu();
            }

            // open Dialog Simple

            ImGui::EndMainMenuBar();
        }

        // update the displayed image
        updateTexture(texture, image);

        window.clear();
        window.draw(sprite);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

// Read a PGM image. Specifically, we expect a ascii grayscale image (P2 only), and the size must be 512x512.
void readImage(const char *filename, unsigned char image[512][512])
{
    char line[512];
    int width, height, maxval;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return; // bail out if we can't open the file
    }

    // read the first line
    if (fgets(line, 512, fp) == NULL)
    {
        fclose(fp);
        return; // bail out if file is empty
    }

    // is it P2?
    if (strncmp(line, "P2", 2) != 0)
    {
        fclose(fp);
        return; // not a P2 file
    }

    // get width and height (skipping any comments)
    do
    {
        if (fgets(line, 512, fp) == NULL)
        {
            fclose(fp);
            return; // hit EOF, so something's up
        }
    } while (line[0] == '#');

    // parse the line we read
    if (sscanf(line, "%d%d", &width, &height) != 2)
    {
        fclose(fp);
        return; // line didn't have width and height, so bail out
    }

    // 512x512?
    if ((width != 512) || (height != 512))
    {
        fclose(fp);
        return; // unsupported size
    }

    // get maximum pixel value
    do
    {
        if (fgets(line, 512, fp) == NULL)
        {
            fclose(fp);
            return;
        }
    } while (line[0] == '#');

    if (sscanf(line, "%d", &maxval) != 1)
    {
        fclose(fp);
        return;
    }

    if (maxval != 255)
    {
        fclose(fp);
        return;
    }

    // now we can read in the pixels
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int pixel;
            if (fscanf(fp, "%d", &pixel) != 1)
            {
                fclose(fp);
                return;
            }

            image[row][col] = (unsigned char)pixel;
        }
    }

    // we're done
    fclose(fp);
}

// Update the SFML texture to display the current image
void updateTexture(sf::Texture &texture, unsigned char image[512][512])
{
    sf::Color sfImage[512][512];

    for (int row = 0; row < 512; row++)
    {
        for (int col = 0; col < 512; col++)
        {
            sfImage[row][col].r = image[row][col];
            sfImage[row][col].g = image[row][col];
            sfImage[row][col].b = image[row][col];
        }
    }

    texture.update((const sf::Uint8 *)sfImage);
}

#else

// This is for the auto-grading on zybooks

int main(void)
{
    return 0;
}

#endif