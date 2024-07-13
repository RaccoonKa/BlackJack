#include <iostream>
#include <exception>

#include <string>
#include <vector>

#include <random>
#include <ctime>
#define NOMINMAX
#include <windows.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

namespace AVS
{
    class card // Класс, который описывает отдельную карту.
    {
    private:
        int c_value = 0;
        std::string path_to_texture;
    public:
        card() = default;

        card(int value)
        {
            set_value(value);
        }

        ~card() = default;

        void set_value(int value)
        {
            if (value < 1 || value > 13)
                throw std::exception("[card:setvalue] wrong value");
            c_value = value;
            switch (value)
            {
            case 1:
                path_to_texture = "assets\\cards\\A.png";
                return;
            case 11:
                path_to_texture = "assets\\cards\\J.png";
                return;
            case 12:
                path_to_texture = "assets\\cards\\Q.png";
                return;
            case 13:
                path_to_texture = "assets\\cards\\K.png";
                return;
            default:
                path_to_texture = "assets\\cards\\" + std::to_string(value) + ".png";
            }
       }

        int get_value()
        {
            return c_value;
        }
        std::string get_texture()
        {
            return path_to_texture;
        }
    };

    struct deck // грубо говоря массив для карт
    {
        std::vector<card> d_array;

        deck() = default;

        ~deck() = default;

        void add_card(int value)//добавить карту, заданую только значением
        {
            d_array.push_back(card(value));
        }

        void add_card(card A) // добавить заданную карту
        {
            d_array.push_back(A);
        }

        void fill_random(int size) // добавить случайные карты(всего size штук)
        {
            if (size < 1)
                throw std::exception("[deck:fill_r] wrong size");

            for (int i = 0; i < size; i++)
                add_card(rand() % 13 + 1);
        }

        void refill_random(int size) // Полностью перезаполнить случайными картами (опять size штук)
        {
            if (size < 1)
                throw std::exception("[deck:fill_r] wrong size");
            d_array.clear();
            for (int i = 0; i < size; i++)
                add_card(rand() % 13 + 1);
        }

        void clear_deck() //опустошить колоду
        {
            d_array.clear();
        }

        void fill_in_order(int size) //заполнить колоду по-порядку
        {
            if (size < 1)
                throw std::exception("[deck:fill_in_ord] wrong size");

            add_card(1);
            for (int i = 1; i < size; i++)
            {
                add_card(i % 13 + 1);
            }
        }
        void erase(int i)
        {
            if (i >= d_array.size() || i < 0)
                throw std::exception("[deck:erase] wrong element");

            d_array.erase(d_array.begin() + i);
        }

        int size()
        {
            return d_array.size();
        }

        card& operator[] (int i)
        {
            return d_array[i];
        }
    };

    class chip // фишка для ставки
    {
    private:
        int c_value = 0;
        std::string path_to_texture;
    public:
        chip() = default;

        chip(int value)
        {
            set_value(value);
        }

        ~chip() = default;

        bool set_value(int value)
        {
            switch (value)
            {
            case 0:
                c_value = 0;
                path_to_texture = "None";
                return true;
            case 100:
                c_value = value;
                path_to_texture = "assets\\chips\\100.png";
                return true;
            case 250:
                c_value = value;
                path_to_texture = "assets\\chips\\250.png";
                return true;
            case 500:
                c_value = value;
                path_to_texture = "assets\\chips\\500.png";
                return true;
            case 1000:
                c_value = value;
                path_to_texture = "assets\\chips\\1000.png";
                return true;
            case 2500:
                c_value = value;
                path_to_texture = "assets\\chips\\2500.png";
                return true;
            case 10000:
                c_value = value;
                path_to_texture = "assets\\chips\\10000.png";
                return true;
            default:
                return false;
            }
        }

        int get_value()
        {
            return c_value;
        }

        std::string get_texture_path()
        {
            return path_to_texture;
        }
    };

    class player //класс игрока отдельного, тут короче будут действия типо взять карту там и т.д.
    {
    private:
        deck p_deck_in_hand;
        chip p_bet = 0;
        bool dealer = false;
    public:

        player(bool is_dealer)
        {
            dealer = is_dealer;
        }

        void set_bet(chip bet)// по факту можно рассмотреть ставку не только из одной фишки, а из л/к фишек, которые унас есть, однако нужно тогда сделать то как они лежат
        {
            p_bet = bet;
        }

        chip get_bet()
        {
            return p_bet;
        }

        void take_card_from_deck(deck& other) // берется последняя карта в колоде
        {
            if (other.d_array.size() == 0)
                throw std::exception("[player:take_card_from_deck] empty deck");

            p_deck_in_hand.add_card(other[other.d_array.size() - 1]);
            other.erase(other.d_array.size() - 1);
        }

        void take_rand_card_from_deck(deck& other, sf::RenderWindow& wind, sf::Sprite background0, sf::Font fonttext) // берется случайная карта в колоде
        {
            if (other.d_array.size() == 0)
                throw std::exception("[player:take_rand_card_from_deck] empty deck");

            int i = rand() % other.d_array.size();
            p_deck_in_hand.add_card(other[i]);
            card tmp(other[i].get_value());
            other.erase(i);

            sf::Texture tmptexture;
            if (!tmptexture.loadFromFile(tmp.get_texture()))
            {
                std::cerr << "Error to upload image minibg1 :(" << std::endl;
                throw std::exception("[Player:take_rand_card_from_deck] texture not found");
            }
            sf::Sprite tmpsprite(tmptexture);
            tmpsprite.setPosition(sf::Vector2f(810, 325));

            sf::RectangleShape takemsgFrame(sf::Vector2f(300,60));
            takemsgFrame.setFillColor(sf::Color(255, 255, 255, 128));
            takemsgFrame.setOutlineColor(sf::Color::Black);
            takemsgFrame.setOutlineThickness(2);
            takemsgFrame.setScale(1.0f, 0.9f);
            takemsgFrame.setPosition(810, 245);

            sf::Text takemsgText;
            takemsgText.setFont(fonttext);
            takemsgText.setCharacterSize(40);
            takemsgText.setFillColor(sf::Color::Black);
            takemsgText.setPosition(820, 245);
            takemsgText.setOutlineThickness(0.2);

            if (dealer)
            {
                takemsgText.setString("Dealer take:");
                takemsgText.setPosition(820 + 20, 245);
            }
            else
            {
                takemsgText.setString("You take:");
                takemsgText.setPosition(820+40, 245);
            }
            wind.clear(sf::Color::White);
            wind.draw(background0);


            wind.draw(takemsgFrame);
            wind.draw(takemsgText);
            wind.draw(tmpsprite);
            wind.display();
            Sleep(2005);
        }

        void take_card(card A) // берется заданная карта
        {
            p_deck_in_hand.add_card(A);
        }

        int check_value_in_hand() // суммарное значение карт на руках
        {
            if (p_deck_in_hand.d_array.empty())
                return 0;
            int tmp = 0;
            for (int i = 0; i < p_deck_in_hand.size(); i++)
            {
                tmp += p_deck_in_hand[i].get_value();
            }
            return tmp;
        }

        void clear_deck() //опустошить колоду
        {
            p_deck_in_hand.clear_deck();
        }

        deck& get_deck()
        {
            return p_deck_in_hand;
        }
    };

    class Button {
    private:
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Vector2f normal;
        sf::Vector2i TextureSize;
        sf::Vector2i TextureStart;
        sf::RenderWindow* window;
        sf::Color ButtonColor;
        sf::Color BorderColor;
        bool BorderSet = false, ButtonTextureEnabled = false, BorderTextureEnabled, in = true;
        float BorderSize = 0;
        sf::Texture ButtonTexture;
        sf::Sprite ButtonSprite;
        sf::Mouse::Button MouseClickButton;
    public:
        Button(sf::Vector2f pos, sf::Vector2f sizes, sf::RenderWindow* wind) {
            position = pos;
            size = sizes;
            window = wind;
        }

        void setButtonColor(sf::Color col) {
            ButtonColor = col;
            ButtonTextureEnabled = false;
        }

        void setButtonTexture(std::string name, sf::Vector2i place, sf::Vector2i siz) {
            TextureSize = siz, TextureStart = place;
            if (!ButtonTexture.loadFromFile(name)) MessageBox(NULL, "Не удалось загрузить файл", "Ошибка", MB_ICONERROR);
            ButtonSprite.setTexture(ButtonTexture);
            ButtonTextureEnabled = true;
        }

        void setBorder(int sizew) {
            if (sizew % 2 != 0) { BorderSize = sizew + 1; }
            else BorderSize = sizew;
            BorderSet = true;
        }

        void setBorderColor(sf::Color col) {
            BorderColor = col;
            BorderSet = true;
        }

        void setMouseClickButton(sf::Mouse::Button click) {
            MouseClickButton = click;
        }
        bool check_mouse_click()
        {
            sf::Vector2i MouseCoords = sf::Mouse::getPosition(*window);
            sf::Vector2u WinSize = (*window).getSize();
            if (MouseCoords.x <= WinSize.x && MouseCoords.y <= WinSize.y && MouseCoords.x >= position.x && MouseCoords.x <= position.x + normal.x && MouseCoords.y >= position.y && MouseCoords.y <= position.x + normal.y && sf::Mouse::isButtonPressed(MouseClickButton)) {
                return true;
            }
            else return false;
        }
        void draw() {
            if (in) normal = size;
            if (size.x > TextureSize.x || size.y > TextureSize.y) size.x = TextureSize.y; size.y = TextureSize.y;
            if (!BorderSet && !ButtonTextureEnabled) {
                sf::RectangleShape button(size);
                button.setPosition(position);
                button.setFillColor(ButtonColor);
                (*window).draw(button);
            }
            if (!BorderSet && ButtonTextureEnabled) {
                ButtonSprite.setPosition(position);
                (*window).draw(ButtonSprite);
            }
            if (BorderSet && !ButtonTextureEnabled) {
                sf::Vector2f BorderVecSize = { BorderSize, BorderSize };
                sf::Vector2f BorderVecPos = { BorderSize / 2, BorderSize / 2 };

                sf::RectangleShape button(size - BorderVecSize);
                button.setPosition(position + BorderVecPos);
                button.setFillColor(ButtonColor);

                sf::RectangleShape border(size);
                border.setPosition(position);
                border.setFillColor(BorderColor);

                (*window).draw(border);
                (*window).draw(button);
            }
            if (BorderSet && ButtonTextureEnabled) {
                ButtonSprite.setTextureRect(sf::IntRect(TextureStart.x, TextureStart.y, size.x - BorderSize, size.y - BorderSize));
                ButtonSprite.setPosition(position.x + BorderSize / 2, position.x + BorderSize / 2);

                sf::RectangleShape border(normal);
                border.setPosition(position);
                border.setFillColor(BorderColor);


                sf::RectangleShape mask(sf::Vector2f(normal.x - BorderSize, normal.y - BorderSize));
                mask.setPosition(position.x + BorderSize / 2, position.x + BorderSize / 2);
                mask.setFillColor(sf::Color::Black);
                in = false;

                (*window).draw(border);
                (*window).draw(mask);
                (*window).draw(ButtonSprite);
            }
        }

    };

}


int main()
{
    //открытие окна
    //sf::Style::Fullscreen
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "BlackJack", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    //раздел шрифтов
    //шрифт 1 (для заголовков)
    sf::Font font;
    if (!font.loadFromFile("assets/different/LavirePersonalUse.otf"))
    {
        std::cerr << "Error to upload font :(" << std::endl;
        return 404;
    }

    //шрифт 2 (для текста)
    sf::Font fonttext;
    if (!fonttext.loadFromFile("assets/different/MagnetTrial-Light.ttf"))
    {
        std::cerr << "Error to upload fonttext :(" << std::endl;
        return 404;
    }

    //раздел орнаментов
    sf::Texture ornament1;
    if (!ornament1.loadFromFile("assets/different/ornament1.png"))
    {
        std::cerr << "Error to upload image ornament1 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureornament1(ornament1);
    textureornament1.setPosition(500, 400);

    sf::Texture ornament2;
    if (!ornament2.loadFromFile("assets/different/ornament2.png"))
    {
        std::cerr << "Error to upload image ornament2 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureornament2(ornament2);
    textureornament2.setPosition(900, 400);

    //раздел девушек :D
    sf::Texture devushka1;
    if (!devushka1.loadFromFile("assets/different/devushka1.png"))
    {
        std::cerr << "Error to upload image devushka1 :(" << std::endl;
        return 404;
    }
    sf::Sprite texturedevushka1(devushka1);
    texturedevushka1.setPosition(100, 430);

    sf::Texture devushka2;
    if (!devushka2.loadFromFile("assets/different/devushka2.png"))
    {
        std::cerr << "Error to upload image devushka2 :(" << std::endl;
        return 404;
    }
    sf::Sprite texturedevushka2(devushka2);
    texturedevushka2.setPosition(1400, 480);


    //раздел фонов игры
    //фон 0 как начальный (красный)
    sf::Texture backgroundTexture0;
    backgroundTexture0.loadFromFile("assets/backgrounds/background1.jpg");
    sf::Sprite background0(backgroundTexture0);
    background0.setScale(
        (float)window.getSize().x / backgroundTexture0.getSize().x,
        (float)window.getSize().y / backgroundTexture0.getSize().y
    );

    sf::Texture backgroundTexture1;
    if (!backgroundTexture1.loadFromFile("assets/backgrounds/background1.jpg"))
    {
        std::cerr << "Error to upload background1 :(" << std::endl;
        return 404;
    }
    sf::Sprite background1(backgroundTexture1);
    background1.setScale(
        (float)window.getSize().x / backgroundTexture1.getSize().x,
        (float)window.getSize().y / backgroundTexture1.getSize().y
    );

    sf::Texture backgroundTexture2;
    if (!backgroundTexture2.loadFromFile("assets/backgrounds/background2.jpg"))
    {
        std::cerr << "Error to upload background2 :(" << std::endl;
        return 404;
    }
    sf::Sprite background2(backgroundTexture2);
    background2.setScale(
        (float)window.getSize().x / backgroundTexture2.getSize().x,
        (float)window.getSize().y / backgroundTexture2.getSize().y
    );

    sf::Texture backgroundTexture3;
    if (!backgroundTexture3.loadFromFile("assets/backgrounds/background3.jpg"))
    {
        std::cerr << "Error to upload background3 :(" << std::endl;
        return 404;
    }
    sf::Sprite background3(backgroundTexture3);
    background3.setScale(
        (float)window.getSize().x / backgroundTexture3.getSize().x,
        (float)window.getSize().y / backgroundTexture3.getSize().y
    );

    //раздел музыки
    bool mus0 = true, redmus = false, greenmus = false, bluemus = false;
    sf::Music musicmain;
    if (!musicmain.openFromFile("assets/different/musicred.wav"))
    {
        std::cerr << "Error to upload musicred :(" << std::endl;
        return 404;
    }
    musicmain.setVolume(5);
    if (mus0)
    {
        musicmain.play();
        musicmain.setLoop(true);
    }
    else
    {
        musicmain.pause();
    }

    sf::Music musicred;
    if (!musicred.openFromFile("assets/different/musicred.wav"))
    {
        std::cerr << "Error to upload musicred :(" << std::endl;
        return 404;
    }
    musicred.setVolume(5);
    sf::Music musicgreen;
    if (!musicgreen.openFromFile("assets/different/musicgreen.wav"))
    {
        std::cerr << "Error to upload musicgreen :(" << std::endl;
        return 404;
    }
    musicgreen.setVolume(5);
    sf::Music musicblue;
    if (!musicblue.openFromFile("assets/different/musicblue.wav"))
    {
        std::cerr << "Error to upload musicblue :(" << std::endl;
        return 404;
    }
    musicblue.setVolume(5);
    sf::Texture muteTexture;
    if (!muteTexture.loadFromFile("assets/different/playmusic.png")) {
        std::cerr << "Error to upload image playmusic :(" << std::endl;
        return 404;
    }
    sf::Texture unmuteTexture;
    if (!unmuteTexture.loadFromFile("assets/different/mutemusic.png")) {
        std::cerr << "Error to upload image mutemusic :(" << std::endl;
        return 404;
    }
    sf::Sprite muteButton(muteTexture);
    muteButton.setPosition(1200.f, 350.f);

    //раздел кнопок гм
    //кнопка играть
    sf::RectangleShape playButton(sf::Vector2f(200, 50));
    playButton.setFillColor(sf::Color(255, 255, 255, 128));
    playButton.setOutlineColor(sf::Color::Black);
    playButton.setOutlineThickness(2);
    playButton.setScale(1.0f, 0.9f);
    playButton.setPosition(900, 400);

    //кнопка правил
    sf::RectangleShape rulesButton(sf::Vector2f(200, 50));
    rulesButton.setFillColor(sf::Color(255, 255, 255, 128));
    rulesButton.setOutlineColor(sf::Color::Black);
    rulesButton.setOutlineThickness(2);
    rulesButton.setScale(1.0f, 0.9f);
    rulesButton.setPosition(900, 450);

    //кнопка настроек
    sf::RectangleShape settingsButton(sf::Vector2f(200, 50));
    settingsButton.setFillColor(sf::Color(255, 255, 255, 128));
    settingsButton.setOutlineColor(sf::Color::Black);
    settingsButton.setOutlineThickness(2);
    settingsButton.setScale(1.0f, 0.9f);
    settingsButton.setPosition(900, 500);

    //кнопка авторов
    sf::RectangleShape authorsButton(sf::Vector2f(200, 50));
    authorsButton.setFillColor(sf::Color(255, 255, 255, 128));
    authorsButton.setOutlineColor(sf::Color::Black);
    authorsButton.setOutlineThickness(2);
    authorsButton.setScale(1.0f, 0.9f);
    authorsButton.setPosition(900, 550);

    //кнопка выхода
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color(255, 255, 255, 128));
    exitButton.setOutlineColor(sf::Color::Black);
    exitButton.setOutlineThickness(2);
    exitButton.setScale(1.0f, 0.9f);
    exitButton.setPosition(900, 600);
    sf::FloatRect exitButtonRect = exitButton.getGlobalBounds();

    //раздел содержания нажатия кнопок гм
    //текст blackjack
    sf::Text blackjack;
    blackjack.setFont(font);
    blackjack.setCharacterSize(150);
    blackjack.setString("BlackJack");
    blackjack.setFillColor(sf::Color(191, 174, 22, 255));
    blackjack.setPosition(635, 50);
    blackjack.setOutlineThickness(0.2);

    //раздел кнопки играть
    //текст играть
    sf::Text playText;
    playText.setFont(font);
    playText.setCharacterSize(40);
    playText.setString("Play");
    playText.setFillColor(sf::Color::Black);
    playText.setPosition(960, 397);
    playText.setOutlineThickness(0.2);

    sf::Texture player_menu;
    if (!player_menu.loadFromFile("assets/different/1player.png"))
    {
        std::cerr << "Error to upload image 1player :(" << std::endl;
        return 404;
    }
    sf::Sprite texture1player(player_menu);
    texture1player.setPosition(750, 400);

    sf::Texture players;
    if (!players.loadFromFile("assets/different/2players.png"))
    {
        std::cerr << "Error to upload image 2players :(" << std::endl;
        return 404;
    }
    sf::Sprite texture2players(players);
    texture2players.setPosition(1050, 400);

    sf::Text oneText;
    oneText.setFont(fonttext);
    oneText.setCharacterSize(30);
    oneText.setString("1 Player");
    oneText.setFillColor(sf::Color::White);
    oneText.setPosition(777, 600);
    oneText.setOutlineThickness(0.4);

    sf::Text twoText;
    twoText.setFont(fonttext);
    twoText.setCharacterSize(30);
    twoText.setString("2 Players");
    twoText.setFillColor(sf::Color::White);
    twoText.setPosition(1080, 600);
    twoText.setOutlineThickness(0.4);

    sf::Text soonText;
    soonText.setFont(fonttext);
    soonText.setCharacterSize(30);
    soonText.setString("Soon!");
    soonText.setFillColor(sf::Color::White);
    soonText.setPosition(1090, 350);
    soonText.setOutlineThickness(0.4);

    //раздел правил
    //текст правил
    sf::Text rulesText;
    rulesText.setFont(font);
    rulesText.setCharacterSize(40);
    rulesText.setString("Rules");
    rulesText.setFillColor(sf::Color::Black);
    rulesText.setPosition(953, 447);
    rulesText.setOutlineThickness(0.2);

    sf::Text mainrules;
    mainrules.setFont(font);
    mainrules.setCharacterSize(100);
    mainrules.setString("Rules of 'BlackJack'");
    mainrules.setOutlineThickness(2);
    mainrules.setFillColor(sf::Color::White);
    mainrules.setPosition(550, 40);
    mainrules.setOutlineThickness(0.4);

    sf::Text rulesContentText;
    rulesContentText.setFont(fonttext);
    rulesContentText.setCharacterSize(25);
    rulesContentText.setString(

        "Blackjack, also known as '21', has a simple essence:\n"
        "the player needs to score 21 points or the closest to that\n"
        "A digit has a value in its hand that exceeds the amount in\n"
        "dealer hand, but in no case exceeding 21. If\n"
        "the participant exceeds 21, he burns out. In the event, if\n"
        "the sum of points is the same for him and the dealer, the\n"
        "party ends in a draw and each side remains at\n"
        "your own scenario. In the case of cards that have\n"
        "numbers, you get as many points as written\n"
        "on the map. If there is no number on the card, then points\n"
        "They are given as follows: Ace - 1 point, Jack - 11 points,\n"
        "The Queen - 12 points, the King - 13 points.\n");

    rulesContentText.setFillColor(sf::Color::White);
    rulesContentText.setOutlineThickness(1);
    rulesContentText.setPosition(640, 240);
    rulesContentText.setOutlineThickness(0.2);

    //рамка правил
    sf::Texture ramka;
    if (!ramka.loadFromFile("assets/different/ramka.png"))
    {
        std::cerr << "Error to upload image ramka :(" << std::endl;
        return 404;
    }
    sf::Sprite textureramka(ramka);
    textureramka.setPosition(500, 150);


    //кнопка назад
    sf::RectangleShape backButton(sf::Vector2f(120, 40));
    backButton.setFillColor(sf::Color(255, 255, 255, 0));
    backButton.setScale(1.0f, 0.9f);
    backButton.setPosition(1270, 770);

    //текст назад
    sf::Text backText;
    backText.setFont(font);
    backText.setCharacterSize(50);
    backText.setString("Back");
    backText.setOutlineThickness(2);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(1250, 740);
    backText.setOutlineThickness(0.2);

    //раздел настроек
    //текст настроек
    sf::Text settingsText;
    settingsText.setFont(font);
    settingsText.setCharacterSize(40);
    settingsText.setString("Settings");
    settingsText.setFillColor(sf::Color::Black);
    settingsText.setPosition(931, 498);
    settingsText.setOutlineThickness(0.2);

    //Settings
    sf::Text settingText;
    settingText.setFont(font);
    settingText.setCharacterSize(150);
    settingText.setString("Settings");
    settingText.setFillColor(sf::Color::White);
    settingText.setPosition(700, 50);
    settingText.setOutlineThickness(0.2);

    //громкость музыки
    sf::Text valueText;
    valueText.setFont(fonttext);
    valueText.setCharacterSize(40);
    valueText.setString("Music volume:");
    valueText.setFillColor(sf::Color::White);
    valueText.setOutlineColor(sf::Color::Black);
    valueText.setPosition(845, 250);
    valueText.setOutlineThickness(0.4);

    //ползунок музыки
    sf::RectangleShape sliderBackground(sf::Vector2f(400.f, 50.f));
    sliderBackground.setFillColor(sf::Color(255, 255, 255, 150));
    sliderBackground.setPosition(776.f, 350.f);
    sf::RectangleShape sliderThumb(sf::Vector2f(50.f, 50.f));
    sliderThumb.setFillColor(sf::Color(186, 34, 33, 255));
    sliderThumb.setPosition(1127.f, 350.f);
    float volume = 1.0f;

    //Theme
    sf::Text themeText;
    themeText.setFont(fonttext);
    themeText.setCharacterSize(40);
    themeText.setString("Themes:");
    themeText.setFillColor(sf::Color::White);
    themeText.setOutlineColor(sf::Color::Black);
    themeText.setPosition(900, 450);
    themeText.setOutlineThickness(0.4);

    //темы
    sf::Texture minibg1;
    if (!minibg1.loadFromFile("assets/different/minibg1.png"))
    {
        std::cerr << "Error to upload image minibg1 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureminibg1(minibg1);
    textureminibg1.setPosition(800, 550);

    sf::Texture minibg2;
    if (!minibg2.loadFromFile("assets/different/minibg2.png"))
    {
        std::cerr << "Error to upload image minibg2 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureminibg2(minibg2);
    textureminibg2.setPosition(950, 550);

    sf::Texture minibg3;
    if (!minibg3.loadFromFile("assets/different/minibg3.png"))
    {
        std::cerr << "Error to upload image minibg3 :(" << std::endl;
        return 404;
    }
    sf::Sprite textureminibg3(minibg3);
    textureminibg3.setPosition(1100, 550);

    //подписи фонов
    sf::Text theme1Text;
    theme1Text.setFont(fonttext);
    theme1Text.setCharacterSize(30);
    theme1Text.setString("Red");
    theme1Text.setFillColor(sf::Color::White);
    themeText.setOutlineColor(sf::Color::Black);
    theme1Text.setPosition(805, 710);
    theme1Text.setOutlineThickness(0.4);

    sf::Text theme2Text;
    theme2Text.setFont(fonttext);
    theme2Text.setCharacterSize(30);
    theme2Text.setString("Green");
    theme2Text.setFillColor(sf::Color::White);
    theme2Text.setOutlineColor(sf::Color::Black);
    theme2Text.setPosition(943, 710);
    theme2Text.setOutlineThickness(0.4);

    sf::Text theme3Text;
    theme3Text.setFont(fonttext);
    theme3Text.setCharacterSize(30);
    theme3Text.setString("Blue");
    theme3Text.setFillColor(sf::Color::White);
    theme3Text.setOutlineColor(sf::Color::Black);
    theme3Text.setPosition(1105, 710);
    theme3Text.setOutlineThickness(0.4);

    //текст авторов
    sf::Text authorsText;
    authorsText.setFont(font);
    authorsText.setCharacterSize(40);
    authorsText.setString("Authors");
    authorsText.setFillColor(sf::Color::Black);
    authorsText.setPosition(928, 548);
    authorsText.setOutlineThickness(0.2);

    //Authors
    sf::Text authorText;
    authorText.setFont(font);
    authorText.setCharacterSize(150);
    authorText.setString("Authors");
    authorText.setFillColor(sf::Color::White);
    authorText.setPosition(1500, 1500);
    authorText.setOutlineThickness(0.2);

    //Kravchuk Svetozar
    sf::Text authorsContentText1;
    authorsContentText1.setFont(fonttext);
    authorsContentText1.setCharacterSize(25);
    authorsContentText1.setString("Kravchuk Svetozar");
    authorsContentText1.setFillColor(sf::Color::White);
    authorsContentText1.setOutlineThickness(1);
    authorsContentText1.setPosition(630, 630);
    authorsContentText1.setOutlineThickness(0.2);

    sf::Texture raccoonka;
    if (!raccoonka.loadFromFile("assets/different/raccoonka.png"))
    {
        std::cerr << "Error to upload image raccoonKa >:(" << std::endl;
        return 404;
    }
    sf::Sprite textureraccoonka(raccoonka);
    textureraccoonka.setPosition(600, 300);

    //Solovyevsky Mark
    sf::Text authorsContentText2;
    authorsContentText2.setFont(fonttext);
    authorsContentText2.setCharacterSize(25);
    authorsContentText2.setString("Solovyevsky Mark");
    authorsContentText2.setFillColor(sf::Color::White);
    authorsContentText2.setOutlineThickness(1);
    authorsContentText2.setPosition(1080, 632);
    authorsContentText2.setOutlineThickness(0.2);

    sf::Texture abonentvneseti;
    if (!abonentvneseti.loadFromFile("assets/different/abonentvneseti.png"))
    {
        std::cerr << "Error to upload image abonentvneseti >:(" << std::endl;
        return 404;
    }
    sf::Sprite textureabonentvneseti(abonentvneseti);
    textureabonentvneseti.setPosition(1050, 300);


    //текст выхода
    sf::Text exitText;
    exitText.setFont(font);
    exitText.setCharacterSize(40);
    exitText.setString("Exit");
    exitText.setFillColor(sf::Color::Black);
    exitText.setPosition(970, 597);
    exitText.setOutlineThickness(0.2);

    //раздел курсоров
    //курсор 0(начальный)
    sf::Texture cursorTexture0;
    if (!cursorTexture0.loadFromFile("assets/different/cursor1.png"))
    {
        std::cerr << "Error to upload cursor :(" << std::endl;
        return 404;
    }
    sf::Sprite cursorSprite0(cursorTexture0);
    cursorSprite0.setOrigin(cursorTexture0.getSize().x / 5.0f, cursorTexture0.getSize().y / 5.0f);
    cursorSprite0.setPosition(100.f, 100.f);
    cursorSprite0.setScale(0.04f, 0.04f);
    window.setMouseCursorVisible(false);

    sf::Texture cursorTexture1;
    if (!cursorTexture1.loadFromFile("assets/different/cursor1.png"))
    {
        std::cerr << "Error to upload cursor :(" << std::endl;
        return 404;
    }
    sf::Sprite cursorSprite1(cursorTexture1);
    cursorSprite1.setOrigin(cursorTexture1.getSize().x / 2.0f, cursorTexture1.getSize().y / 2.0f);
    cursorSprite1.setPosition(100.f, 100.f);
    cursorSprite1.setScale(0.05f, 0.05f);

    sf::Texture cursorTexture2;
    if (!cursorTexture2.loadFromFile("assets/different/cursor2.png"))
    {
        std::cerr << "Error to upload cursor :(" << std::endl;
        return 404;
    }
    sf::Sprite cursorSprite2(cursorTexture2);
    cursorSprite2.setOrigin(cursorTexture2.getSize().x / 2.0f, cursorTexture2.getSize().y / 2.0f);
    cursorSprite2.setPosition(100.f, 100.f);
    cursorSprite2.setScale(0.05f, 0.05f);

    sf::Texture cursorTexture3;
    if (!cursorTexture3.loadFromFile("assets/different/cursor3.png"))
    {
        std::cerr << "Error to upload cursor :(" << std::endl;
        return 404;
    }
    sf::Sprite cursorSprite3(cursorTexture3);
    cursorSprite3.setOrigin(cursorTexture3.getSize().x / 2.0f, cursorTexture3.getSize().y / 2.0f);
    cursorSprite3.setPosition(100.f, 100.f);
    cursorSprite3.setScale(0.05f, 0.05f);

    sf::Sprite* currentCursor = &cursorSprite0;




    //фишки
    //100
    sf::Texture sto;
    if (!sto.loadFromFile("assets/chips/100.png"))
    {
        std::cerr << "Error to upload 100 :(" << std::endl;
        return 404;
    }
    sf::Sprite stotexture(sto);
    //250
    sf::Texture dvesti;
    if (!dvesti.loadFromFile("assets/chips/250.png"))
    {
        std::cerr << "Error to upload 250 :(" << std::endl;
        return 404;
    }
    sf::Sprite dvestitexture(dvesti);
    //500
    sf::Texture pyatsot;
    if (!pyatsot.loadFromFile("assets/chips/500.png"))
    {
        std::cerr << "Error to upload 500 :(" << std::endl;
        return 404;
    }
    sf::Sprite pyatsottexture(pyatsot);
    //1000
    sf::Texture tisyacha;
    if (!tisyacha.loadFromFile("assets/chips/1000.png"))
    {
        std::cerr << "Error to upload 1000 :(" << std::endl;
        return 404;
    }
    sf::Sprite texturetisyacha(tisyacha);
    //2500
    sf::Texture dvepyat;
    if (!dvepyat.loadFromFile("assets/chips/2500.png"))
    {
        std::cerr << "Error to upload 2500 :(" << std::endl;
        return 404;
    }
    sf::Sprite dvepyattexture(dvepyat);
    //10000
    sf::Texture desyatk;
    if (!desyatk.loadFromFile("assets/chips/10000.png"))
    {
        std::cerr << "Error to upload 10000 :(" << std::endl;
        return 404;
    }
    sf::Sprite desyatktexture(desyatk);




    //карты
    //2
    sf::Texture two;
    if (!two.loadFromFile("assets/cards/2.png"))
    {
        std::cerr << "Error to upload 2 :(" << std::endl;
        return 404;
    }
    sf::Sprite twotexture(two);
    //3
    sf::Texture three;
    if (!three.loadFromFile("assets/cards/3.png"))
    {
        std::cerr << "Error to upload 3 :(" << std::endl;
        return 404;
    }
    sf::Sprite threetexture(three);
    //4
    sf::Texture four;
    if (!four.loadFromFile("assets/cards/4.png"))
    {
        std::cerr << "Error to upload 4 :(" << std::endl;
        return 404;
    }
    sf::Sprite fourtexture(four);
    //5
    sf::Texture five;
    if (!five.loadFromFile("assets/cards/5.png"))
    {
        std::cerr << "Error to upload 5 :(" << std::endl;
        return 404;
    }
    sf::Sprite fivetexture(five);
    //6
    sf::Texture six;
    if (!six.loadFromFile("assets/cards/6.png"))
    {
        std::cerr << "Error to upload 6 :(" << std::endl;
        return 404;
    }
    sf::Sprite sixtexture(six);
    //7
    sf::Texture seven;
    if (!seven.loadFromFile("assets/cards/7.png"))
    {
        std::cerr << "Error to upload 7 :(" << std::endl;
        return 404;
    }
    sf::Sprite seventexture(seven);
    //8
    sf::Texture eight;
    if (!eight.loadFromFile("assets/cards/8.png"))
    {
        std::cerr << "Error to upload 8 :(" << std::endl;
        return 404;
    }
    sf::Sprite eighttexture(eight);
    //9
    sf::Texture nine;
    if (!nine.loadFromFile("assets/cards/9.png"))
    {
        std::cerr << "Error to upload 3 :(" << std::endl;
        return 404;
    }
    sf::Sprite ninetexture(nine);
    //10
    sf::Texture ten;
    if (!ten.loadFromFile("assets/cards/10.png"))
    {
        std::cerr << "Error to upload 10 :(" << std::endl;
        return 404;
    }
    sf::Sprite tentexture(ten);
    //J
    sf::Texture J;
    if (!J.loadFromFile("assets/cards/J.png"))
    {
        std::cerr << "Error to upload J :(" << std::endl;
        return 404;
    }
    sf::Sprite Jtexture(J);
    //Q
    sf::Texture Q;
    if (!Q.loadFromFile("assets/cards/Q.png"))
    {
        std::cerr << "Error to upload Q :(" << std::endl;
        return 404;
    }
    sf::Sprite Qtexture(Q);
    //K
    sf::Texture K;
    if (!K.loadFromFile("assets/cards/K.png"))
    {
        std::cerr << "Error to upload K :(" << std::endl;
        return 404;
    }
    sf::Sprite Ktexture(K);
    //A
    sf::Texture A;
    if (!A.loadFromFile("assets/cards/A.png"))
    {
        std::cerr << "Error to upload A :(" << std::endl;
        return 404;
    }
    sf::Sprite Atexture(A);




    //рубашки карт
    //красная
    sf::Texture sr;
    if (!sr.loadFromFile("assets/cards/shirtred.png"))
    {
        std::cerr << "Error to upload shirtred :(" << std::endl;
        return 404;
    }
    sf::Sprite srtexture(sr);
    //зелёная
    sf::Texture sg;
    if (!sg.loadFromFile("assets/cards/shirtgreen.png"))
    {
        std::cerr << "Error to upload shirtgreen :(" << std::endl;
        return 404;
    }
    sf::Sprite sgtexture(sg);
    //синяя
    sf::Texture sb;
    if (!sb.loadFromFile("assets/cards/shirtblue.png"))
    {
        std::cerr << "Error to upload shirtblue :(" << std::endl;
        return 404;
    }
    sf::Sprite sbtexture(sb);

    bool mutingmusic = false;
    bool showPlay = false, showRules = false, showSettings = false, showAuthors = false;

    bool jump = false;

    //базовые настройки.
    bool menu = true;
    bool game = false;
    srand(time(NULL));

    AVS::player player(false);
    AVS::player dealer(true);

    int all_money = 10000;//все деньги
    short start_size = 52;// размер колоды
    AVS::deck X; // колода откуда берутся карты

    bool first_move = true; // первый ход
    bool chosing_bet = true;// выбор ставки
    bool dealers_move = false; // ход дилера
    bool win = false; // в случае победы
    bool lose = false; // в случае поражения
    bool push = false; // в случае пуша

    bool get_move = false;
    bool pass_move = false;
    bool restart_move = false;

    //кнопки
    //взять карту
    sf::RectangleShape getButton(sf::Vector2f(300, 120));
    getButton.setFillColor(sf::Color(255, 255, 255, 128));
    getButton.setOutlineColor(sf::Color::Black);
    getButton.setOutlineThickness(2);
    getButton.setScale(1.0f, 0.9f);
    getButton.setPosition(50, 750);

    sf::Text getText;
    getText.setFont(font);
    getText.setCharacterSize(60);
    getText.setString("Get");
    getText.setFillColor(sf::Color::Black);
    getText.setPosition(50 + 100, 750 + 20);
    getText.setOutlineThickness(0.2);

    //передать ход
    sf::RectangleShape passButton(sf::Vector2f(300, 120));
    passButton.setFillColor(sf::Color(255, 255, 255, 128));
    passButton.setOutlineColor(sf::Color::Black);
    passButton.setOutlineThickness(2);
    passButton.setScale(1.0f, 0.9f);
    passButton.setPosition(50, 900);

    sf::Text passText;
    passText.setFont(font);
    passText.setCharacterSize(60);
    passText.setString("Enough");
    passText.setFillColor(sf::Color::Black);
    passText.setPosition(50 + 60, 900 + 20);
    passText.setOutlineThickness(0.2);

    //restart
    sf::RectangleShape restartButton(sf::Vector2f(300, 120));
    restartButton.setFillColor(sf::Color(255, 255, 255, 128));
    restartButton.setOutlineColor(sf::Color::Black);
    restartButton.setOutlineThickness(2);
    restartButton.setScale(1.0f, 0.9f);
    restartButton.setPosition(50, 900);

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setCharacterSize(60);
    restartText.setString("Restart");
    restartText.setFillColor(sf::Color::Black);
    restartText.setPosition(50 + 45, 900 + 15);
    restartText.setOutlineThickness(0.2);

    //кнопки ставок
    AVS::Button* set_bet_100 = new AVS::Button(sf::Vector2f(500, 200), sf::Vector2f(300, 300), &window);
    (*set_bet_100).setButtonTexture("assets/chips/100.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_100).setMouseClickButton(sf::Mouse::Button::Left);

    AVS::Button* set_bet_250 = new AVS::Button(sf::Vector2f(810, 200), sf::Vector2f(300, 300), &window);
    (*set_bet_250).setButtonTexture("assets/chips/250.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_250).setMouseClickButton(sf::Mouse::Button::Left);

    AVS::Button* set_bet_500 = new AVS::Button(sf::Vector2f(1120, 200), sf::Vector2f(300, 300), &window);
    (*set_bet_500).setButtonTexture("assets/chips/500.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_500).setMouseClickButton(sf::Mouse::Button::Left);

    AVS::Button* set_bet_1000 = new AVS::Button(sf::Vector2f(500, 550), sf::Vector2f(300, 300), &window);
    (*set_bet_1000).setButtonTexture("assets/chips/1000.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_1000).setMouseClickButton(sf::Mouse::Button::Left);

    AVS::Button* set_bet_2500 = new AVS::Button(sf::Vector2f(810, 550), sf::Vector2f(300, 300), &window);
    (*set_bet_2500).setButtonTexture("assets/chips/2500.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_2500).setMouseClickButton(sf::Mouse::Button::Left);

    AVS::Button* set_bet_10000 = new AVS::Button(sf::Vector2f(1120, 550), sf::Vector2f(300, 300), &window);
    (*set_bet_10000).setButtonTexture("assets/chips/10000.png", sf::Vector2i(0, 0), sf::Vector2i(300, 300));
    (*set_bet_10000).setMouseClickButton(sf::Mouse::Button::Left);

    //выход в меню
    sf::RectangleShape exit_from_game_Button(sf::Vector2f(300, 120));
    exit_from_game_Button.setFillColor(sf::Color(255, 255, 255, 128));
    exit_from_game_Button.setOutlineColor(sf::Color::Black);
    exit_from_game_Button.setOutlineThickness(2);
    exit_from_game_Button.setScale(1.0f, 0.9f);
    exit_from_game_Button.setPosition(1570, 900);

    sf::Text exit_from_game_Text;
    exit_from_game_Text.setFont(font);
    exit_from_game_Text.setCharacterSize(60);
    exit_from_game_Text.setString("Exit");
    exit_from_game_Text.setFillColor(sf::Color::Black);
    exit_from_game_Text.setPosition(1570 + 100, 900 + 20);
    exit_from_game_Text.setOutlineThickness(0.2);

    //тексты значений
    //все деньги
    std::string all_money_str = std::to_string(all_money);

    sf::RectangleShape moneyFrame(sf::Vector2f(240 + 27 * (all_money_str.size()), 60));
    moneyFrame.setFillColor(sf::Color(255, 255, 255, 128));
    moneyFrame.setOutlineColor(sf::Color::Black);
    moneyFrame.setOutlineThickness(2);
    moneyFrame.setScale(1.0f, 0.9f);
    moneyFrame.setPosition(10, 10);

    sf::Text moneyText;
    moneyText.setFont(fonttext);
    moneyText.setCharacterSize(40);
    moneyText.setString("All money: " + all_money_str);
    moneyText.setFillColor(sf::Color::Black);
    moneyText.setPosition(20, 10);
    moneyText.setOutlineThickness(0.2);

    //Игрок счет
    std::string player_score_str = std::to_string(0);

    sf::RectangleShape PlayerScoreFrame(sf::Vector2f(430, 60));
    PlayerScoreFrame.setFillColor(sf::Color(255, 255, 255, 128));
    PlayerScoreFrame.setOutlineColor(sf::Color::Black);
    PlayerScoreFrame.setOutlineThickness(2);
    PlayerScoreFrame.setScale(1.0f, 0.9f);
    PlayerScoreFrame.setPosition(1470, 550);

    sf::Text PlayerScoreText;
    PlayerScoreText.setFont(fonttext);
    PlayerScoreText.setCharacterSize(40);
    PlayerScoreText.setString("Player's score: " + player_score_str);
    PlayerScoreText.setFillColor(sf::Color::Black);
    PlayerScoreText.setPosition(1470, 550);
    PlayerScoreText.setOutlineThickness(0.2);

    //Деалер счет
    std::string dealer_score_str = std::to_string(0);

    sf::RectangleShape dealerScoreFrame(sf::Vector2f(430, 60));
    dealerScoreFrame.setFillColor(sf::Color(255, 255, 255, 128));
    dealerScoreFrame.setOutlineColor(sf::Color::Black);
    dealerScoreFrame.setOutlineThickness(2);
    dealerScoreFrame.setScale(1.0f, 0.9f);
    dealerScoreFrame.setPosition(1470, 470);

    sf::Text dealerScoreText;
    dealerScoreText.setFont(fonttext);
    dealerScoreText.setCharacterSize(40);
    dealerScoreText.setString("Dealer's score: " + player_score_str);
    dealerScoreText.setFillColor(sf::Color::Black);
    dealerScoreText.setPosition(1470, 470);
    dealerScoreText.setOutlineThickness(0.2);

    //текущая ставка

    std::string bet_str;

    sf::RectangleShape curr_bet_Frame(sf::Vector2f(115 + 27, 60));
    curr_bet_Frame.setFillColor(sf::Color(255, 255, 255, 128));
    curr_bet_Frame.setOutlineColor(sf::Color::Black);
    curr_bet_Frame.setOutlineThickness(2);
    curr_bet_Frame.setScale(1.0f, 0.9f);
    curr_bet_Frame.setPosition(10, 80);

    sf::Text curr_bet_Text;
    curr_bet_Text.setFont(fonttext);
    curr_bet_Text.setCharacterSize(40);
    curr_bet_Text.setString("bet: 0");
    curr_bet_Text.setFillColor(sf::Color::Black);
    curr_bet_Text.setPosition(20, 80);
    curr_bet_Text.setOutlineThickness(0.2);

    //текст при выборе ставки
    //текущая ставка
    sf::RectangleShape chose_bet_frame(sf::Vector2f(365, 60));
    chose_bet_frame.setFillColor(sf::Color(255, 255, 255, 128));
    chose_bet_frame.setOutlineColor(sf::Color::Black);
    chose_bet_frame.setOutlineThickness(2);
    chose_bet_frame.setScale(1.0f, 0.9f);
    chose_bet_frame.setPosition(500, 130);

    sf::Text chose_bet_text;
    chose_bet_text.setFont(fonttext);
    chose_bet_text.setCharacterSize(40);
    chose_bet_text.setString("Choose your bet!");
    chose_bet_text.setFillColor(sf::Color::Black);
    chose_bet_text.setPosition(510, 130);
    chose_bet_text.setOutlineThickness(0.2);

    //текст при проигрыше всех денег
    sf::RectangleShape full_lose_frame(sf::Vector2f(700, 200));
    full_lose_frame.setFillColor(sf::Color(255, 255, 255, 128));
    full_lose_frame.setOutlineColor(sf::Color::Black);
    full_lose_frame.setOutlineThickness(2);
    full_lose_frame.setScale(1.0f, 0.9f);
    full_lose_frame.setPosition(610, 440);

    sf::Text full_lose_text;
    full_lose_text.setFont(fonttext);
    full_lose_text.setCharacterSize(40);
    full_lose_text.setString("You lose all your money!\nSo, to prevent you from leaving,\n we gave you some money.");
    full_lose_text.setFillColor(sf::Color::Black);
    full_lose_text.setPosition(620, 440);
    full_lose_text.setOutlineThickness(0.2);

    //lose text
    sf::RectangleShape end_message_frame(sf::Vector2f(350, 120));
    end_message_frame.setFillColor(sf::Color(255, 255, 255, 128));
    end_message_frame.setOutlineColor(sf::Color::Black);
    end_message_frame.setOutlineThickness(2);
    end_message_frame.setScale(1.0f, 0.9f);

    sf::Text end_message_text;
    end_message_text.setFont(font);
    end_message_text.setCharacterSize(80);
    end_message_text.setFillColor(sf::Color::Black);
    end_message_text.setOutlineThickness(0.2);

    while (window.isOpen())
    {
        if (menu)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (!showPlay && !showRules && !showSettings && !showAuthors && exitButtonRect.contains(mousePos.x, mousePos.y))
                    {
                        window.close();
                    }
                    if (!showRules && !showSettings && !showAuthors && playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        showPlay = true;
                    }
                    if (showPlay && texture1player.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        menu = false;
                        game = true;
                        jump = true;
                    }
                    else if (!showPlay && !showRules && !showSettings && rulesButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        showRules = true;
                    }
                    else if (!showPlay && !showRules && !showAuthors && settingsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        showSettings = true;

                    }
                    else if (!showPlay && !showRules && !showSettings && authorsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        showAuthors = true;
                    }
                    if ((showPlay || showRules || showAuthors || showSettings) && backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        showPlay = false;
                        showRules = false;
                        showSettings = false;
                        showAuthors = false;
                    }

                    //раздел настроек
                    if (showSettings)
                    {
                        //ползунок звука
                        if (!showPlay && !showRules && !showAuthors && sliderBackground.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                        {
                            float sliderX = mousePos.x - sliderBackground.getPosition().x;
                            volume = sliderX / sliderBackground.getSize().x;
                            sliderThumb.setPosition(sliderBackground.getPosition().x + sliderX - sliderThumb.getSize().x / 2, sliderBackground.getPosition().y);
                            musicred.setVolume(volume * 5);
                            musicblue.setVolume(volume * 5);
                            musicgreen.setVolume(volume * 5);
                            musicmain.setVolume(volume * 5);
                        }
                        //кнопка мута звука для каждой из песен темы
                        if (muteButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                        {
                            mutingmusic = !mutingmusic;
                            if (mus0)
                            {
                                if (mutingmusic)
                                {
                                    musicmain.pause();
                                    muteButton.setTexture(unmuteTexture);
                                }
                                else
                                {
                                    musicmain.play();
                                    muteButton.setTexture(muteTexture);
                                }
                            }
                            else if (redmus)
                            {
                                if (mutingmusic)
                                {
                                    musicred.pause();
                                    muteButton.setTexture(unmuteTexture);
                                }
                                else
                                {
                                    musicred.play();
                                    muteButton.setTexture(muteTexture);
                                }
                            }
                            else if (greenmus)
                            {
                                if (mutingmusic)
                                {
                                    musicgreen.pause();
                                    muteButton.setTexture(unmuteTexture);
                                }
                                else
                                {
                                    musicgreen.play();
                                    muteButton.setTexture(muteTexture);
                                }
                            }
                            else if (bluemus)
                            {
                                if (mutingmusic)
                                {
                                    musicblue.pause();
                                    muteButton.setTexture(unmuteTexture);
                                }
                                else
                                {
                                    musicblue.play();
                                    muteButton.setTexture(muteTexture);
                                }
                            }

                        }

                        //замена фона
                        if (textureminibg1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                        {
                            currentCursor = &cursorSprite1;
                            sliderThumb.setFillColor(sf::Color(186, 34, 33, 255));
                            background0.setTexture(backgroundTexture1);
                            background0.setScale(
                                (float)window.getSize().x / backgroundTexture1.getSize().x,
                                (float)window.getSize().y / backgroundTexture1.getSize().y
                            );
                            mus0 = false, redmus = true, greenmus = false, bluemus = false;
                            if (redmus && !greenmus && !bluemus)
                            {
                                musicmain.pause();
                                musicblue.pause();
                                musicgreen.pause();
                                if (!mutingmusic) musicred.play();
                                musicred.setLoop(true);
                            }
                        }
                        else if (textureminibg2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                        {
                            currentCursor = &cursorSprite2;
                            sliderThumb.setFillColor(sf::Color(78, 123, 50, 255));
                            background0.setTexture(backgroundTexture2);
                            background0.setScale(
                                (float)window.getSize().x / backgroundTexture2.getSize().x,
                                (float)window.getSize().y / backgroundTexture2.getSize().y
                            );
                            mus0 = false, redmus = false, greenmus = true, bluemus = false;
                            if (!redmus && greenmus && !bluemus)
                            {
                                musicmain.pause();
                                musicred.pause();
                                musicblue.pause();
                                if (!mutingmusic) musicgreen.play();
                                musicgreen.setLoop(true);
                            }
                        }
                        else if (textureminibg3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                        {
                            currentCursor = &cursorSprite3;
                            sliderThumb.setFillColor(sf::Color(44, 72, 160, 255));
                            background0.setTexture(backgroundTexture3);
                            background0.setScale(
                                (float)window.getSize().x / backgroundTexture3.getSize().x,
                                (float)window.getSize().y / backgroundTexture3.getSize().y
                            );
                            mus0 = false, redmus = false, greenmus = false, bluemus = true;
                            if (!redmus && !greenmus && bluemus)
                            {
                                musicmain.pause();
                                musicred.pause();
                                musicgreen.pause();
                                if (!mutingmusic) musicblue.play();
                                musicblue.setLoop(true);
                            }
                        }
                    }
                }
            }

            //давайте рисовать!
            window.clear(sf::Color::White);
            window.draw(background0);
            //играть
            if (showPlay)
            {
                window.draw(textureramka);
                window.draw(texturedevushka1);
                window.draw(texturedevushka2);
                window.draw(texture1player);
                window.draw(texture2players);
                window.draw(soonText);
                window.draw(twoText);
                window.draw(oneText);
                window.draw(backButton);
                window.draw(backText);
            }

            //настройки
            else if (showSettings)
            {
                window.draw(settingText);
                window.draw(backButton);
                window.draw(backText);
                window.draw(valueText);
                window.draw(muteButton);
                window.draw(sliderBackground);
                window.draw(sliderThumb);
                window.draw(themeText);
                window.draw(textureminibg1);
                window.draw(textureminibg2);
                window.draw(textureminibg3);
                window.draw(theme1Text);
                window.draw(theme2Text);
                window.draw(theme3Text);
            }
            //авторы
            else if (showAuthors)
            {
                window.draw(authorText);
                window.draw(backButton);
                window.draw(backText);
                window.draw(authorsContentText1);
                window.draw(textureraccoonka);
                window.draw(authorsContentText2);
                window.draw(textureabonentvneseti);
            }
            //правила
            else if (showRules)
            {
                window.draw(textureramka);
                window.draw(mainrules);
                window.draw(rulesContentText);
                window.draw(backButton);
                window.draw(backText);
            }
            //главное меню
            else
            {
                window.draw(textureornament1);
                window.draw(textureornament2);
                window.draw(texturedevushka1);
                window.draw(texturedevushka2);
                window.draw(blackjack);
                window.draw(playButton);
                window.draw(rulesButton);
                window.draw(settingsButton);
                window.draw(authorsButton);
                window.draw(exitButton);
                window.draw(playText);
                window.draw(rulesText);
                window.draw(settingsText);
                window.draw(authorsText);
                window.draw(exitText);
            }
        }
        if (jump)
        {
            Sleep(500);
        }
        if (game)
        {
            jump = false;
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (exit_from_game_Button.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        game = false;
                        menu = true;
                    }
                    if (!first_move && !dealers_move && getButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        get_move = true;
                    }
                    if (!first_move && !dealers_move && passButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && !(win || lose || push))
                    {
                        pass_move = true;
                    }
                    if (!first_move && restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && (win || lose || push))
                    {
                        restart_move = true;
                    }
                }
            }

            window.clear(sf::Color::White);
            window.draw(background0);
            if (chosing_bet) //выбор ставки
            {
                window.clear(sf::Color::White);
                window.draw(background0);
                if (all_money < 100)
                {
                    window.draw(full_lose_frame);
                    window.draw(full_lose_text);
                    window.display();
                    Sleep(2500);
                    all_money = 2500;
                    all_money_str = std::to_string(all_money);
                    moneyFrame.setSize(sf::Vector2f(240 + 27 * (all_money_str.size()), 60));
                    moneyText.setString("All money: " + all_money_str);
                }
                else
                {
                    if (all_money >= 100) (*set_bet_100).draw();
                    if (all_money >= 250) (*set_bet_250).draw();
                    if (all_money >= 500) (*set_bet_500).draw();
                    if (all_money >= 1000) (*set_bet_1000).draw();
                    if (all_money >= 2500) (*set_bet_2500).draw();
                    if (all_money >= 10000) (*set_bet_10000).draw();

                    if ((*set_bet_1000).check_mouse_click())
                    {
                        if (chosing_bet && all_money >= 1000) player.set_bet(1000);
                        chosing_bet = false;
                    }
                    if ((*set_bet_2500).check_mouse_click())
                    {
                        if (chosing_bet && all_money >= 2500) player.set_bet(2500);
                        chosing_bet = false;
                    }
                    if ((*set_bet_10000).check_mouse_click())
                    {
                        if (chosing_bet && all_money >= 10000) player.set_bet(10000);
                        chosing_bet = false;
                    }
                    if ((*set_bet_100).check_mouse_click())
                    {
                        if (chosing_bet && all_money >= 100) player.set_bet(100);
                        chosing_bet = false;
                    }
                    if ((*set_bet_250).check_mouse_click())
                    {
                        if (chosing_bet && all_money >= 250) player.set_bet(250);
                        chosing_bet = false;
                    }
                    if ((*set_bet_500).check_mouse_click())
                    {
                        if (chosing_bet && all_money >= 500) player.set_bet(500);
                        chosing_bet = false;
                    }
                    if (!chosing_bet)
                    {
                        bet_str = std::to_string(player.get_bet().get_value());
                        curr_bet_Frame.setSize(sf::Vector2f(115 + 27 * (bet_str.size()), 60));
                        curr_bet_Text.setString("bet: " + bet_str);

                        all_money -= player.get_bet().get_value();

                        all_money_str = std::to_string(all_money);
                        moneyFrame.setSize(sf::Vector2f(240 + 27 * (all_money_str.size()), 60));
                        moneyText.setString("All money: " + all_money_str);
                    }
                    window.draw(chose_bet_frame);
                    window.draw(chose_bet_text);
                }
            }
            else if (first_move)
            {
                X.fill_in_order(start_size);//перезаполняем колоду

                for (int i = 0; i < 2; i++) //берутся по 2 карты игроку и дилеру, можно добавить сразу две анимации
                {
                    player.take_rand_card_from_deck(X, window, background0, fonttext);
                    dealer.take_rand_card_from_deck(X, window, background0, fonttext);
                }

                player_score_str = std::to_string(player.check_value_in_hand());
                PlayerScoreText.setString("Player score: " + player_score_str);


                dealer_score_str = std::to_string(dealer.check_value_in_hand());
                dealerScoreText.setString("Dealer score: " + dealer_score_str);

                first_move = false;
            }
            else if (!dealers_move)
            {
                if (get_move)
                {
                    player.take_rand_card_from_deck(X, window, background0, fonttext);
                    get_move = false;

                    player_score_str = std::to_string(player.check_value_in_hand());
                    PlayerScoreText.setString("Player score: " + player_score_str);
                }
                if (pass_move)
                {
                    dealers_move = true;
                    pass_move = false;
                }
            }
            else if (dealers_move)
            {
                if (dealer.check_value_in_hand() <= player.check_value_in_hand())
                {
                    Sleep(300);
                    dealer.take_rand_card_from_deck(X, window, background0, fonttext);
                    window.clear();
                    window.draw(background0);
                    dealer_score_str = std::to_string(dealer.check_value_in_hand());
                    dealerScoreText.setString("Dealer score: " + dealer_score_str);
                }
            }
            {//check_win
                short pltmp = player.check_value_in_hand();
                short dltmp = dealer.check_value_in_hand();

                if (pltmp == dltmp && pltmp >= 21)
                    push = true;
                else if (pltmp == 21)
                    win = true;
                else if (dltmp == 21)
                    lose = true;
                else if (pltmp > 21 && dltmp < 21)
                    lose = true;
                else if (pltmp < 21 && dltmp > 21)
                    win = true;
                else if (pltmp > 21 && dltmp > 21)
                {
                    if (pltmp < dltmp)
                        win = true;
                    else
                        lose = true;
                }
                else if (dltmp > pltmp && dealers_move)
                    lose = true;
            }
            if (win || lose || push)
            {
                if (win)
                {
                    end_message_frame.setSize(sf::Vector2f(310, 120));
                    end_message_text.setString("You win!");
                    end_message_frame.setPosition((1920 - 310) / 2, (1080 - 120) / 2);
                    end_message_text.setPosition((1920 - 310) / 2 + 10, (1080 - 120) / 2);

                    all_money += 2 * player.get_bet().get_value();
                    player.set_bet(0);

                    all_money_str = std::to_string(all_money);
                    moneyFrame.setSize(sf::Vector2f(240 + 27 * (all_money_str.size()), 60));
                    moneyText.setString("All money: " + all_money_str);


                    bet_str = std::to_string(player.get_bet().get_value());
                    curr_bet_Frame.setSize(sf::Vector2f(115 + 27 * (bet_str.size()), 60));
                    curr_bet_Text.setString("bet: " + bet_str);
                }
                else if (lose)
                {
                    end_message_frame.setSize(sf::Vector2f(350, 120));
                    end_message_text.setString("You lose!");
                    end_message_frame.setPosition((1920 - 350) / 2, (1080 - 120) / 2);
                    end_message_text.setPosition((1920 - 350) / 2 + 10, (1080 - 120) / 2);

                    player.set_bet(0);

                    all_money_str = std::to_string(all_money);
                    moneyFrame.setSize(sf::Vector2f(240 + 27 * (all_money_str.size()), 60));
                    moneyText.setString("All money: " + all_money_str);


                    bet_str = std::to_string(player.get_bet().get_value());
                    curr_bet_Frame.setSize(sf::Vector2f(115 + 27 * (bet_str.size()), 60));
                    curr_bet_Text.setString("bet: " + bet_str);
                }
                else
                {
                    end_message_frame.setSize(sf::Vector2f(195, 120));
                    end_message_text.setString("Push!");
                    end_message_frame.setPosition((1920 - 195) / 2, (1080 - 120) / 2);
                    end_message_text.setPosition((1920 - 195) / 2 + 10, (1080 - 120) / 2);

                    all_money += player.get_bet().get_value();
                    player.set_bet(0);

                    all_money_str = std::to_string(all_money);
                    moneyFrame.setSize(sf::Vector2f(240 + 27 * (all_money_str.size()), 60));
                    moneyText.setString("All money: " + all_money_str);


                    bet_str = std::to_string(player.get_bet().get_value());
                    curr_bet_Frame.setSize(sf::Vector2f(115 + 27 * (bet_str.size()), 60));
                    curr_bet_Text.setString("bet: " + bet_str);
                }

                window.draw(end_message_frame);
                window.draw(end_message_text);

                window.draw(restartButton);
                window.draw(restartText);

                if (restart_move)
                {
                    first_move = true;
                    chosing_bet = true;
                    dealers_move = false;

                    win = false;
                    lose = false;
                    push = false;

                    player.set_bet(0);
                    player.clear_deck();
                    dealer.clear_deck();
                    restart_move = false;
                }
            }

            if (!first_move)
            {
                window.draw(PlayerScoreFrame);
                window.draw(PlayerScoreText);
                window.draw(dealerScoreFrame);
                window.draw(dealerScoreText);
            }

            if (!first_move && !dealers_move && !(win || lose || push))
            {
                window.draw(passButton);
                window.draw(passText);
                window.draw(getButton);
                window.draw(getText);
            }

            window.draw(moneyFrame);
            window.draw(moneyText);

            window.draw(curr_bet_Frame);
            window.draw(curr_bet_Text);

            window.draw(exit_from_game_Button);
            window.draw(exit_from_game_Text);
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        currentCursor->setPosition(static_cast<sf::Vector2f>(mousePos));
        window.draw(*currentCursor);

        //if (menu) break;
        window.display();

    }


    delete set_bet_100;
    delete set_bet_250;
    delete set_bet_500;
    delete set_bet_1000;
    delete set_bet_2500;
    delete set_bet_10000;
    return 0;
}