#include<SFML/Graphics.hpp>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>

using namespace std;
using namespace sf;

bool mouseBusy(bool, bool, bool, bool);

int main(){
    srand(time(NULL));
    int xRes = 800, yRes = 800, brush = 15;
    int brushColor[3] = {0,0,0};
    bool lDown = false, sliderActive = false, redActive = false, greenActive = false, blueActive = false;
    /*
    cout << "Enter your X resolution:" << endl;
    cin >> xRes;
    cout << "Enter your Y resolution:" << endl;
    cin >> yRes;
    *///I don't want this to work currently, but the functionality is there for the future

    RenderWindow window(VideoMode(xRes+200, yRes), "KR Paint"); //I add 200 to the X resolution to allocate for the tool bar
    window.setFramerateLimit(1000);

    Image image;
    image.create(xRes, yRes, sf::Color::White);
    Texture canvasT;
    Font font;

    if (!font.loadFromFile("Raleway.ttf")){
        cout << "Could not load Raleway.ttf" << endl;
    }
    if (!canvasT.loadFromImage(image)){
        cout << "Could not load image" << endl;
    }
    Texture sliderBarT;
    if (!sliderBarT.loadFromFile("slider bar.png")){
        cout << "Could not load slider bar.png" << endl;
    }
    Texture redSliderT;
    if (!redSliderT.loadFromFile("red slider.png")){
        cout << "Could not load red slider.png" << endl;
    }
    Texture greenSliderT;
    if (!greenSliderT.loadFromFile("green slider.png")){
        cout << "Could not load green slider.png" << endl;
    }
    Texture blueSliderT;
    if (!blueSliderT.loadFromFile("blue slider.png")){
        cout << "Could not load blue slider.png" << endl;
    }
    Texture sliderT;
    if (!sliderT.loadFromFile("slidey part.png")){
        cout << "Could not load slidey part.png" << endl;
    }
    Texture eraserT;
    if (!eraserT.loadFromFile("eraser.png")){
        cout << "Could not load eraser.png" << endl;
    }
    Texture resetT;
    if (!resetT.loadFromFile("reset.png")){
        cout << "Could not load reset.png" << endl;
    }
    Texture saveT;
    if (!saveT.loadFromFile("save.png")){
        cout << "Could not load save.png" << endl;
    }
    Sprite canvas;
    canvas.setPosition(200, 0);
    canvas.setTexture(canvasT);

    RectangleShape toolBar(Vector2f(200, yRes));
    toolBar.setFillColor(Color(50,50,50));
    toolBar.setPosition(0,0);

    Text sizeText;
    sizeText.setFont(font);
    sizeText.setString("Brush Size");
    sizeText.setCharacterSize(20);
    sizeText.setFillColor(Color::White);
    sizeText.setPosition(20, 25);

    RectangleShape sliderBar(Vector2f(150, 32));
    sliderBar.setPosition(25, 50);
    sliderBar.setTexture(&sliderBarT);
    RectangleShape slider(Vector2f(11, 32));
    slider.setPosition(25, 50);
    slider.setTexture(&sliderT);
    slider.setOrigin(6,0);

    Text colorText;
    colorText.setFont(font);
    colorText.setString("Brush Color (R,G,B)");
    colorText.setCharacterSize(20);
    colorText.setFillColor(Color::White);
    colorText.setPosition(20, 100);

    RectangleShape redSliderBar(Vector2f(150, 32));
    redSliderBar.setPosition(25, 125);
    redSliderBar.setTexture(&redSliderT);
    RectangleShape redSlider(Vector2f(11, 32));
    redSlider.setPosition(25, 125);
    redSlider.setTexture(&sliderT);
    redSlider.setOrigin(6,0);

    RectangleShape greenSliderBar(Vector2f(150, 32));
    greenSliderBar.setPosition(25, 175);
    greenSliderBar.setTexture(&greenSliderT);
    RectangleShape greenSlider(Vector2f(11, 32));
    greenSlider.setPosition(25, 175);
    greenSlider.setTexture(&sliderT);
    greenSlider.setOrigin(6,0);

    RectangleShape blueSliderBar(Vector2f(150, 32));
    blueSliderBar.setPosition(25, 225);
    blueSliderBar.setTexture(&blueSliderT);
    RectangleShape blueSlider(Vector2f(11, 32));
    blueSlider.setPosition(25, 225);
    blueSlider.setTexture(&sliderT);
    blueSlider.setOrigin(6,0);

    RectangleShape eraser(Vector2f(50, 50));
    eraser.setPosition(25, 275);
    eraser.setTexture(&eraserT);

    RectangleShape reset(Vector2f(50, 50));
    reset.setPosition(125, 275);
    reset.setTexture(&resetT);

    RectangleShape save(Vector2f(50, 50));
    save.setPosition(75, 350);
    save.setTexture(&saveT);

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
        }
        bool mouseIsBusy = mouseBusy(sliderActive, redActive, greenActive, blueActive);

        if (Mouse::isButtonPressed(Mouse::Left) && lDown == false){
            lDown = true;
        }
        if (!Mouse::isButtonPressed(Mouse::Left) && lDown == true){
            lDown = false;
        }
        if (lDown == true){
            if (Mouse::getPosition(window).x-200 < xRes && Mouse::getPosition(window).x-200 > 0 && Mouse::getPosition(window).y < yRes && Mouse::getPosition(window).y > 0 && !mouseIsBusy){
                for (int yy = 0; yy < brush; yy++){
                    for (int xx = 0; xx < brush; xx++){
                        if (Mouse::getPosition(window).x-200+xx-(brush/2) > 0 && Mouse::getPosition(window).x-200+xx-(brush/2) < xRes && Mouse::getPosition(window).y+yy-(brush/2) > 0 && Mouse::getPosition(window).y+yy-(brush/2) < yRes){
                            image.setPixel(Mouse::getPosition(window).x-200+xx-(brush/2), Mouse::getPosition(window).y+yy-(brush/2), Color(brushColor[0],brushColor[1],brushColor[2]));
                        }
                    }
                }
                canvasT.update(image);
            }
            //Brush size slider
            if (sliderBar.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && !mouseIsBusy){
                sliderActive = true;
            }
            if (sliderActive && Mouse::getPosition(window).x < 175 && Mouse::getPosition(window).x > 25){
                slider.setPosition(Mouse::getPosition(window).x, 50);
                brush = (slider.getPosition().x-24)/2;//Divided by 2 to scale the slider
            }
            //Red slider
            if (redSliderBar.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && !mouseIsBusy){
                redActive = true;
            }
            if (redActive && Mouse::getPosition(window).x < 175 && Mouse::getPosition(window).x > 25){
                redSlider.setPosition(Mouse::getPosition(window).x, 125);
                brushColor[0] = (redSlider.getPosition().x-25)*1.7;//Multiplied by 1.7 to set the scale from 1 - 255
            }
            //Green slider
            if (greenSliderBar.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && !mouseIsBusy){
                greenActive = true;
            }
            if (greenActive && Mouse::getPosition(window).x < 175 && Mouse::getPosition(window).x > 25){
                greenSlider.setPosition(Mouse::getPosition(window).x, 175);
                brushColor[1] = (greenSlider.getPosition().x-25)*1.7;//Multiplied by 1.7 to set the scale from 1 - 255
            }
            //Blue slider
            if (blueSliderBar.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && !mouseIsBusy){
                blueActive = true;
            }
            if (blueActive && Mouse::getPosition(window).x < 175 && Mouse::getPosition(window).x > 25){
                blueSlider.setPosition(Mouse::getPosition(window).x, 225);
                brushColor[2] = (blueSlider.getPosition().x-25)*1.7;//Multiplied by 1.7 to set the scale from 1 - 255
            }
            //Eraser
            if (eraser.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && !mouseIsBusy){
                redSlider.setPosition(175, 125);
                greenSlider.setPosition(175, 175);
                blueSlider.setPosition(175, 225);
                brushColor[0] = 255;
                brushColor[1] = 255;
                brushColor[2] = 255;
            }
            //Reset
            if (reset.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && !mouseIsBusy){
                redSlider.setPosition(25, 125);
                greenSlider.setPosition(25, 175);
                blueSlider.setPosition(25, 225);
                brushColor[0] = 0;
                brushColor[1] = 0;
                brushColor[2] = 0;

                for (int ii = 0; ii < yRes; ii ++){
                    for (int cc = 0; cc < xRes; cc++){
                        image.setPixel(cc, ii, Color(255, 255, 255));
                    }
                }
                canvasT.update(image);
            }
            //Save
            if (save.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && !mouseIsBusy){
                if (image.saveToFile("Your Painting.png")){
                    cout << "Image saved successfully" << endl;
                }
            }
        }
        if (lDown == false){
            sliderActive = false;
            redActive = false;
            greenActive = false;
            blueActive = false;
        }

        window.clear();

        window.draw(toolBar);
        window.draw(sliderBar);
        window.draw(slider);
        window.draw(redSliderBar);
        window.draw(redSlider);
        window.draw(greenSliderBar);
        window.draw(greenSlider);
        window.draw(blueSliderBar);
        window.draw(blueSlider);
        window.draw(eraser);
        window.draw(reset);
        window.draw(save);
        window.draw(canvas);
        window.draw(sizeText);
        window.draw(colorText);
        window.display();
    }
}

bool mouseBusy(bool slider1, bool slider2, bool slider3, bool slider4){
    if (slider1 || slider2 || slider3 || slider4){
        return true;
    }
    else {
        return false;
    }
}
