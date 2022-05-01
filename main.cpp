
#include <SFML/Graphics.hpp>
#include <iostream>
#pragma
//#include <SFML\Graphics.hpp>
//#include "Main_menu.h"

using namespace std;
using namespace sf;
// Difficulty
int level;
#define Max_level 3
int flag = 0;
int flag_main = 0;

int flag_Single = 0;
int flag_Player1 = 0;
int flag_Player2 = 0;
//------------------------------------------------------------------
//----------------  Header File of Main Menu -----------------------
// main Menu
int page_number;
#define Max_main_menu 2

class Main_menu // menuu
{
public:
    Main_menu(float width, float hight);
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();

    int mainMenuPressed()
    {
        return mainMenuSelected;
    }

    ~Main_menu();

private:
    int mainMenuSelected;
    sf::Font font;
    sf::Text mainMenu[Max_main_menu];
};
//--------------------------------------------------------------------

//-------------------------------------------------------------------------
//----------------------- Header File of Modes ----------------------------

// Single -Multi
int mode_number;
#define Max_mode_menu 2

class Mode_menu // menuu
{
public:
    Mode_menu(float width, float hight);
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();

    int modeMenuPressed()
    {
        return modeMenuSelected;
    }

private:
    int modeMenuSelected;
    sf::Font font;
    sf::Text modeMenu[Max_mode_menu];
};
//--------------------------------------------------------------------
#define side 15
#define size 208.5
//------------- Directions of the Train ------------------
enum direction
{
    up,
    down,
    sh,
    ymeen
};
//---------------------------Single Player --------------------------
//----------------  Header File of Snake Game -----------------------

//-------------- Node : The body of the Train -----------------
struct node
{
    int posx, posy;
    int direction;
    sf::Sprite *s;
    struct node *llink;
    struct node *rlink;
};
typedef struct node *NODE;

//-----------------------------

class Game
{
private:
    NODE head, tail, cur;
    int speed = 200;
    int count = 0;
    int score = -1;
    sf::Vector2f snoopyPos;
    String pl1Win = "Congratulation You Win !!";

private:
    sf::RenderWindow window;
    sf::Sprite TrainSprite;
    sf::Texture spriteSheet;
    sf::Sprite snoopy;
    sf::Event event;
    sf::Text Score;
    sf::Font font;
    sf::Texture Background;
    sf::Sprite bg;
    sf::RenderWindow window_Win;
    sf::Text WinText;

private:
    void Update();
    void Render();
    void Start();
    void LoadSprites();
    NODE insertHead(NODE head, sf::Sprite *sprite);
    NODE deleteTail(NODE tail);
    void processEvents();
    void WinCase();

private:
    void setTrailingSprite(NODE node, sf::Sprite *sp);
    void setHeadSprite(NODE node, sf::Sprite *sp);
    sf::Vector2f getSnoopyCoords();
    void HandleSnoopyTouched();
    bool isSnoopyTouched(NODE head, sf::Sprite *snoopy);
    void checkIntersection(NODE head, sf::RenderWindow *window);

public:
    void Run();
};

//-------------------------------------------------------------------

//----------------------- Cpp of Main Menu----------------------------
Main_menu::Main_menu(float width, float height)
{
    if (!font.loadFromFile("TIMES.ttf"))
    {
    }

    // play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(sf::Color::Blue);

    mainMenu[0].setString(sf::String("Play"));
    mainMenu[0].setCharacterSize(50);
    mainMenu[0].setPosition(sf::Vector2f((width / 2), height / (Max_main_menu + 1)));
    /*
        // options
        mainMenu[1].setFont(font);
        mainMenu[1].setFillColor(sf::Color::White);
        mainMenu[1].setString("options");
        mainMenu[1].setCharacterSize(50);
        mainMenu[1].setPosition(sf::Vector2f(width / 3, height / (Max_main_menu + 1) * 2));
    */
    // exit
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(sf::Color::White);
    mainMenu[1].setString("Exit");
    mainMenu[1].setCharacterSize(50);
    mainMenu[1].setPosition(sf::Vector2f(width / 2, height / (Max_main_menu + 1) * 3));

    mainMenuSelected = 0; // start from zero index (play)
}

Main_menu::~Main_menu()
{
}

//********************************Function of drawing main menu**********************************************//
void Main_menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < 2; i++)
    {
        window.draw(mainMenu[i]);
    }
}

//********************************Function of moving up***************************************************
void Main_menu::moveUp()
{
    if (mainMenuSelected - 1 >= -1) // check if not on the first item (play)

    {

        mainMenu[mainMenuSelected].setFillColor(sf::Color::White); // change the pervious item's color

        mainMenuSelected--; // move to the upper item
        if (mainMenuSelected == -1)
        {
            mainMenuSelected = 1;
        }
        mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue); // change the new item's color
    }
}

//********************************Function of moving down***************************************************
void Main_menu::moveDown()
{
    if (mainMenuSelected + 1 <= Max_main_menu) // check if not on the last item (exit)

    {
        mainMenu[mainMenuSelected].setFillColor(sf::Color::White); // change the pervious item's color

        mainMenuSelected++; // move to the lower item
        if (mainMenuSelected == 2)
        {
            mainMenuSelected = 0;
        }
        mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue); // change the new item's color
    }
}

//----------------------------------------------------------------

//----------------------- Cpp of Mode Menu----------------------------
Mode_menu::Mode_menu(float width, float height)
{
    if (!font.loadFromFile("TIMES.ttf"))
    {
    }

    // play Single Player
    modeMenu[0].setFont(font);
    modeMenu[0].setFillColor(sf::Color::Blue);
    modeMenu[0].setString(sf::String("Single Player"));
    modeMenu[0].setCharacterSize(50);
    modeMenu[0].setPosition(sf::Vector2f((width / 2), height / (Max_mode_menu + 1)));

    // Play Multiplayer
    modeMenu[1].setFont(font);
    modeMenu[1].setFillColor(sf::Color::White);
    modeMenu[1].setString("Multi-player");
    modeMenu[1].setCharacterSize(50);
    modeMenu[1].setPosition(sf::Vector2f(width / 2, height / (Max_mode_menu + 1) * 3));

    modeMenuSelected = 0; // start from zero index (play)
}

//********************************Function of drawing main menu**********************************************//
void Mode_menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < 2; i++)
    {
        window.draw(modeMenu[i]);
    }
}

//********************************Function of moving up***************************************************
void Mode_menu::moveUp()
{
    if (modeMenuSelected - 1 >= -1) // check if not on the first item (play)

    {
        // mms=0;
        modeMenu[modeMenuSelected].setFillColor(sf::Color::White); // change the pervious item's color
        modeMenuSelected--;                                        // move to the upper item
                                                                   // mms=-1
        if (modeMenuSelected == -1)
        {
            modeMenuSelected = 1;
        }
        modeMenu[modeMenuSelected].setFillColor(sf::Color::Blue); // change the new item's color
    }
}

//********************************Function of moving down***************************************************
void Mode_menu::moveDown()
{                                              // mode menu selectd = 0
    if (modeMenuSelected + 1 <= Max_mode_menu) // check if not on the last item (exit)

    {                                                              // mms=0
        modeMenu[modeMenuSelected].setFillColor(sf::Color::White); // change the pervious item's color
        modeMenuSelected++;                                        // move to the lower item
                                                                   // mms=1
        if (modeMenuSelected == 2)
        {
            modeMenuSelected = 0;
        }
        modeMenu[modeMenuSelected].setFillColor(sf::Color::Blue); // change the new item's color
    }
}
//--------------------------------------------------------------------------------------------------------------------

//---------------------------Game.cpp Single Player---------------------------------------
//---------------------- Start Implementation of the Snake Game Code -------------------
NODE Game::insertHead(NODE head, sf::Sprite *sprite)
{
    NODE temp;
    temp = (NODE)malloc(sizeof(struct node));
    switch (head->direction)
    {
    case direction(up):
        temp->posy = head->posy - side * 2;
        temp->posx = head->posx;
        break;
    case direction(down):
        temp->posy = head->posy + side * 2;
        temp->posx = head->posx;
        break;
    case direction(sh):
        temp->posx = head->posx - side * 2;
        temp->posy = head->posy;
        break;
    case direction(ymeen):
        temp->posx = head->posx + side * 2;
        temp->posy = head->posy;
        break;
    }
    temp->direction = head->direction;
    temp->s = sprite;
    temp->llink = NULL;
    temp->rlink = head;
    head->llink = temp;
    return temp;
}
//----- This function is for Motion of the Train-------
NODE Game::deleteTail(NODE tail)
{
    NODE temp;
    temp = tail->llink;
    temp->rlink = NULL;
    free(tail);
    tail = NULL;
    return temp;
}
// When the snake hits the wall
//----- Removing the tail and Insert the new node in the Head----
void Game::Update()
{
    // when the train hit the ymeen wall
    if (head->posx > 810)
        head->posx = 0;
    // when the train hit the sh wall
    if (head->posx < 0)
        head->posx = 810;
    // when the train  the ceil(up) wall
    if (head->posy > 600)
        head->posy = 0;
    // when the train  the bottom(down) wall
    if (head->posy < 0)
        head->posy = 600;
    HandleSnoopyTouched();
    head = insertHead(head, &TrainSprite);
    tail = deleteTail(tail);
    checkIntersection(head, &window);
    count = 0;
}

void Game::Start()
{
    LoadSprites();
    head = (NODE)malloc(sizeof(struct node));
    head->posx = 0;
    head->posy = 0;
    head->direction = ymeen;
    head->s = &TrainSprite;
    head->llink = head->rlink = NULL;
    tail = head;
    snoopy.setPosition(head->posx, head->posy);
    Score.setPosition(700, 10);
    Score.setString(sf::String(std::to_string(score + 1)));
    window.create(sf::VideoMode(800, 600), "Train", sf::Style::Titlebar | sf::Style::Close);
}

void Game::Run()
{
    Start();
    while (window.isOpen())
    {
        Render();
        processEvents();
        if (count == speed)
        {
            Update();
        }
        count++;
        if (score == 10)
        {
            flag_Single = 1;
            window.close();
        }
    }
    window_Win.create(sf::VideoMode(800, 800), "Win Case", sf::Style::Titlebar | sf::Style::Close);
    while (window_Win.isOpen())
    {
        sf::Event event;
        while (window_Win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_Win.close();

            Game::WinCase();
        }
        // window_Win.clear();
        window_Win.display();
    }
}

void Game::WinCase()
{

    font.loadFromFile("resources/Roboto-Bold.ttf");
    WinText.setFont(font);
    WinText.setFillColor(sf::Color::Blue);
    WinText.setPosition(200, 300);
    if (flag_Single)
        WinText.setString(sf::String(pl1Win));
    window_Win.draw(WinText);
    //  window_Win.display();
}
void Game::Render()
{
    window.clear();
    window.draw(bg);
    window.draw(Score);
    setHeadSprite(head, &TrainSprite);
    cur = head;
    while (cur != NULL)
    {
        if (cur != head)
            setTrailingSprite(cur, &TrainSprite);
        (*cur->s).setPosition(cur->posx, cur->posy);
        window.draw(*cur->s);
        cur = cur->rlink;
    }
    window.draw(snoopy);
    window.display();
}

void Game::LoadSprites()
{
    this->spriteSheet.loadFromFile("resources/trainsprite.png");
    TrainSprite.setTexture(spriteSheet);
    TrainSprite.setScale(sf::Vector2f(0.25, 0.25));
    TrainSprite.setOrigin(104.5, 104.5);

    snoopy.setTexture(spriteSheet);
    snoopy.setTextureRect(sf::IntRect(size * 3, size * 1, size, size));
    snoopy.setScale(0.2, 0.2);
    snoopy.setOrigin(104.5, 104.5);

    font.loadFromFile("resources/Roboto-Bold.ttf");
    Score.setFont(font);
    Score.setFillColor(sf::Color::Black);

    this->Background.loadFromFile("resources/sand.jpg");
    bg.setTexture(Background);
    bg.setScale(2, 2);
}

void Game::setHeadSprite(NODE node, sf::Sprite *sp)
{
    switch (head->direction)
    {
    case up:
        sp->setTextureRect(sf::IntRect(size * 1, size * 0, size, size));
        head->s = sp;
        break;
    case down:
        sp->setTextureRect(sf::IntRect(size * 0, size * 0, size, size));
        head->s = sp;
        break;
    case sh:
        sp->setTextureRect(sf::IntRect(size * 3, size * 0, size, size));
        head->s = sp;
        break;
    case ymeen:
        sp->setTextureRect(sf::IntRect(size * 2, size * 0, size, size));
        head->s = sp;
        break;
    }
}

void Game::setTrailingSprite(NODE node, sf::Sprite *sp)
{
    switch (node->direction)
    {
    case up:
        sp->setTextureRect(sf::IntRect(size * 1, size * 1, size, size));
        node->s = sp;
        break;
    case down:
        sp->setTextureRect(sf::IntRect(size * 2, size * 1, size, size));
        node->s = sp;
        break;
    case sh:
        sp->setTextureRect(sf::IntRect(size * 0, size * 1, size, size));
        node->s = sp;
        break;
    case ymeen:
        sp->setTextureRect(sf::IntRect(size * 0, size * 1, size, size));
        node->s = sp;
        break;
    }
}

void Game::processEvents()
{
    if (window.pollEvent(event))
    {
        switch (event.type)
        {
            // If we close the window --> Terminates the game
        case sf::Event::Closed:
            window.close();
            break;
            // Keyboard controll
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::W && head->direction != down)
            {
                head->direction = up;
            }
            else if (event.key.code == sf::Keyboard::S && head->direction != up)
            {
                head->direction = down;
            }
            else if (event.key.code == sf::Keyboard::A && head->direction != ymeen)
            {
                head->direction = sh;
            }
            else if (event.key.code == sf::Keyboard::D && head->direction != sh)
            {
                head->direction = ymeen;
            }
        }
    }
}

sf::Vector2f Game::getSnoopyCoords()
{
    return sf::Vector2f((rand() % 26 + 1) * side * 2, (rand() % 19 + 1) * side * 2);
}

void Game::HandleSnoopyTouched()
{
    if (isSnoopyTouched(head, &snoopy))
    {
        //--- to increse the length of the train --------
        head = insertHead(head, &TrainSprite);
        speed--;
        while (1)
        {
            snoopyPos = getSnoopyCoords();
            cur = head;
            while (cur != NULL)
            {
                if (cur->posx == snoopyPos.x && cur->posy == snoopyPos.y)
                {
                    break;
                }
                cur = cur->rlink;
            }
            if (cur == NULL)
                break;
        }
        snoopy.setPosition(getSnoopyCoords());
        score++;
        Score.setString(sf::String(std::to_string(score)));
    }
}

bool Game::isSnoopyTouched(NODE head, sf::Sprite *snoopy)
{
    // Vector 2f : Generate Coordinates of the plane
    return sf::Vector2f(head->posx, head->posy) == snoopy->getPosition();
}
//---- To Check When Train hit himself------------
void Game::checkIntersection(NODE head, sf::RenderWindow *window)
{
    NODE cur = head->rlink;
    while (cur != NULL)
    {
        // when the Head of the train hits the body of the train
        if (head->posx == cur->posx && head->posy == cur->posy)
        {
            // To close the game when the train hit himself
            window->close();
        }
        cur = cur->rlink;
    }
}
//--------------------------------------------------------------

//-------------------------------------------------------------------
//-------------------------------------------------------------
//------------------------Multiplier Mode ------------------------------
//----------------  Header File of Snake Game -----------------------
//-------------- Node : The body of the Train -----------------
struct nodeMulti
{ // ---- Train 1-------
    int posx1, posy1;
    int direction1;
    sf::Sprite *s1;
    struct nodeMulti *llink1;
    struct nodeMulti *rlink1;
    //---- Train 2-------
    int posx2, posy2;
    sf::Sprite *s2;
    int direction2;
    struct nodeMulti *llink2;
    struct nodeMulti *rlink2;
};
typedef struct nodeMulti *NODEMULTI;

class GameMulti
{
public:
    // ---- Train 1-------
    NODEMULTI head1, tail1, cur1;
    int speed1 = 200;
    int count1 = 0;
    int score1 = 0;
    sf::Vector2f snoopyPos;
    //---- Train 2-------
    NODEMULTI head2, tail2, cur2;
    int speed2 = 200;
    int count2 = 0;
    int score2 = 0;
    //------------------
    String pl1 = "Player 1:";
    String pl2 = "Player 2:";
    String pl1Win = "Congratulation Player 1 Wins !!";
    String pl2Win = "Congratulation Player 2 Wins !!";

private:
    // ---- Train 1-------
    sf::RenderWindow window;
    sf::RenderWindow window_Win;
    sf::Sprite TrainSprite1;
    sf::Texture spriteSheet;
    sf::Sprite snoopy;
    sf::Event event;
    sf::Text Score1;
    sf::Font font;
    sf::Texture Background;
    sf::Sprite bg;

    //--------Train2-----------
    sf::Sprite TrainSprite2;
    sf::Texture spriteSheet2;
    sf::Text Score2;
    //------------------------
    sf::Text Player1;
    sf::Text Player2;
    sf::Text WinText;
    //-------------------------
    sf::Vector2f snoopyPos2;
    sf::Sprite snoopy2;
    //-------------------------
    sf::Vector2f snoopyPos3;
    sf::Sprite snoopy3;
    //-------------------------
    sf::Vector2f bombPos;
    sf::Sprite bomb;
    sf::Texture spriteSheet3;

public:
    void Update();
    void Update2();
    void Render();
    void Render2();
    void Start();
    void LoadSprites();
    void LoadSprites2();
    NODEMULTI insertHead(NODEMULTI head, sf::Sprite *sprite);
    NODEMULTI insertHead2(NODEMULTI head, sf::Sprite *sprite);
    NODEMULTI deleteTail(NODEMULTI tail);
    NODEMULTI deleteTail2(NODEMULTI tail);
    void processEvents();
    void processEvents2();

public:
    void setTrailingSprite(NODEMULTI node, sf::Sprite *sp);
    void setTrailingSprite2(NODEMULTI node, sf::Sprite *sp);
    void setHeadSprite(NODEMULTI node, sf::Sprite *sp);
    void setHeadSprite2(NODEMULTI node, sf::Sprite *sp);
    sf::Vector2f getSnoopyCoords();
    sf::Vector2f getSnoopyCoords2();
    sf::Vector2f getSnoopyCoords3();
    sf::Vector2f getBombCoords();
    void HandleSnoopyTouched();
    void HandleSnoopyTouched2();
    void HandleSnoopy2Touched();
    void HandleSnoopy2Touched2();
    void HandleSnoopy3Touched();
    void HandleSnoopy3Touched2();
    void HandleBombTouched();
    void HandleBombTouched2();

    void WinCase();
    bool isSnoopyTouched(NODEMULTI head, sf::Sprite *snoopy);
    bool isSnoopyTouched2(NODEMULTI head, sf::Sprite *snoopy);
    bool isSnoopyTouched3(NODEMULTI head, sf::Sprite *snoopy);
    bool isBombTouched(NODEMULTI head, sf::Sprite *snoopy);
    bool isBombTouched2(NODEMULTI head, sf::Sprite *snoopy);
    void checkIntersection(NODEMULTI head, sf::RenderWindow *window);
    void checkIntersection2(NODEMULTI head, sf::RenderWindow *window);

public:
    void Run();
};

//-------------------------Multiplayer ---------------------------------
//---------------------------Game.cpp---------------------------------------
//---------------------- Start Implementation of the Snake Game Code -------------------
NODEMULTI GameMulti::insertHead(NODEMULTI head, sf::Sprite *sprite)
{
    NODEMULTI temp;
    temp = (NODEMULTI)malloc(sizeof(struct nodeMulti));

    switch (head->direction1)
    {
    case direction(up):
        temp->posy1 = head->posy1 - side * 2;
        temp->posx1 = head->posx1;
        break;
    case direction(down):
        temp->posy1 = head->posy1 + side * 2;
        temp->posx1 = head->posx1;
        break;
    case direction(sh):
        temp->posx1 = head->posx1 - side * 2;
        temp->posy1 = head->posy1;
        break;
    case direction(ymeen):
        temp->posx1 = head->posx1 + side * 2;
        temp->posy1 = head->posy1;
        break;
    }
    temp->direction1 = head->direction1;
    temp->s1 = sprite;
    temp->llink1 = NULL;
    temp->rlink1 = head;
    head->llink1 = temp;
    return temp;
}
NODEMULTI GameMulti::insertHead2(NODEMULTI head, sf::Sprite *sprite)
{
    NODEMULTI temp;
    temp = (NODEMULTI)malloc(sizeof(struct nodeMulti));

    switch (head->direction2)
    {
    case direction(up):
        temp->posy2 = head->posy2 - side * 2;
        temp->posx2 = head->posx2;
        break;
    case direction(down):
        temp->posy2 = head->posy2 + side * 2;
        temp->posx2 = head->posx2;
        break;
    case direction(sh):
        temp->posx2 = head->posx2 - side * 2;
        temp->posy2 = head->posy2;
        break;
    case direction(ymeen):
        temp->posx2 = head->posx2 + side * 2;
        temp->posy2 = head->posy2;
        break;
    }
    temp->direction2 = head->direction2;
    temp->s2 = sprite;
    temp->llink2 = NULL;
    temp->rlink2 = head;
    head->llink2 = temp;
    return temp;
}
//----- This function is for Motion of the Train-------
NODEMULTI GameMulti::deleteTail(NODEMULTI tail)
{
    NODEMULTI temp;
    temp = tail->llink1;
    temp->rlink1 = NULL;
    free(tail);
    tail = NULL;

    return temp;
}
NODEMULTI GameMulti::deleteTail2(NODEMULTI tail)
{
    NODEMULTI temp;
    temp = tail->llink2;
    temp->rlink2 = NULL;
    free(tail);
    tail = NULL;

    return temp;
}
// When the snake hits the wall
//----- Removing the tail and Insert the new node in the Head----
void GameMulti::Update()
{
    // when the train hit the ymeen wall
    if (head1->posx1 > 810)
        head1->posx1 = 0;
    // when the train hit the sh wall
    if (head1->posx1 < 0)
        head1->posx1 = 810;
    // when the train  the ceil(up) wall
    if (head1->posy1 > 600)
        head1->posy1 = 0;
    // when the train  the bottom(down) wall
    if (head1->posy1 < 0)
        head1->posy1 = 600;
    head1 = insertHead(head1, &TrainSprite1);
    tail1 = deleteTail(tail1);
    checkIntersection(head1, &window);
    HandleSnoopyTouched();
    HandleSnoopy2Touched();
    HandleSnoopy3Touched();
    HandleBombTouched();
    count1 = 0;
}

void GameMulti::Update2()
{

    //-------------- Train 2 -----------------
    if (head2->posx2 > 810)
        head2->posx2 = 0;
    // when the train hit the sh wall
    if (head2->posx2 < 0)
        head2->posx2 = 810;
    // when the train  the ceil(up) wall
    if (head2->posy2 > 600)
        head2->posy2 = 0;
    // when the train  the bottom(down) wall
    if (head2->posy2 < 0)
        head2->posy2 = 600;

    // oo
    head2 = insertHead2(head2, &TrainSprite2);
    tail2 = deleteTail2(tail2);
    checkIntersection2(head2, &window);
    HandleSnoopyTouched2();
    HandleSnoopy2Touched2();
    HandleSnoopy3Touched2();
    HandleBombTouched2();

    count2 = 0;
}

void GameMulti::Start()
{
    LoadSprites();
    head1 = (NODEMULTI)malloc(sizeof(struct nodeMulti));
    head1->posx1 = 0;
    head1->posy1 = 150;
    head1->direction1 = ymeen;
    head1->s1 = &TrainSprite1;
    head1->llink1 = head1->rlink1 = NULL;
    tail1 = head1;
    //-------------------------------
    // First Snoopy
    snoopy.setPosition(getSnoopyCoords());
    // snoopy.setPosition(head1->posx1, head1->posy1);

    // Second Snoop
    snoopy2.setPosition(getSnoopyCoords2());
    //--------------------------------
    // Third Snoop
    snoopy3.setPosition(getSnoopyCoords3());
    //--------------------------------
    // Bomb
    bomb.setPosition(getBombCoords());
    //--------------------------------
    Score1.setPosition(180, 10);
    //----- To Handle the Case of Eating first 2 snoopies and score becomes only 1 for player 1
    if (score1 == 0)
    {
        Score1.setString(sf::String(std::to_string(score1)));
        GameMulti::getSnoopyCoords();
    }

    else
        Score1.setString(sf::String(std::to_string(score1 + 1)));
    //--------------------------------------

    Player1.setPosition(50, 10);
    Player1.setString(sf::String(pl1));
    //--------------- Train 2 ---------------------
    LoadSprites2();
    head2 = (NODEMULTI)malloc(sizeof(struct nodeMulti));
    head2->posx2 = 0;
    head2->posy2 = 350;
    head2->direction2 = ymeen;
    // oo

    head2->s2 = &TrainSprite2;
    head2->llink2 = head2->rlink2 = NULL;
    tail2 = head2;
    //------ To Handle That the train Has only one part for both trains -----
    head1 = insertHead(head1, &TrainSprite1);
    head2 = insertHead2(head2, &TrainSprite2);
    //------------------------------------------------------------------
    Score2.setPosition(700, 10);
    //----- To Handle the Case of Eating first 2 snoopies and score becomes only 1
    if (score2 == 0)
    {
        Score2.setString(sf::String(std::to_string(score2)));
        GameMulti::getBombCoords();
        GameMulti::getSnoopyCoords();
        GameMulti::getSnoopyCoords2();
        GameMulti::getSnoopyCoords3();
    }
    else
        Score2.setString(sf::String(std::to_string(score2 + 1)));
    //--------------------------------------------------------------
    // ----------To Set the position of the Train 2----------------
    Player2.setPosition(570, 10);
    Player2.setString(sf::String(pl2));
    window.create(sf::VideoMode(800, 600), "Train", sf::Style::Titlebar | sf::Style::Close);

    // snoopy.setPosition(head2->posx2, head2->posy2);
    // REturn back here
    // window.create(sf::VideoMode(800, 600), "Train", sf::Style::Titlebar | sf::Style::Close);
}

void GameMulti::WinCase()
{

    // window.clear();
    // this->Background.loadFromFile("resources/sand.jpg");
    // bg.setTexture(Background);
    // bg.setScale(2, 2);
    font.loadFromFile("resources/Roboto-Bold.ttf");
    WinText.setFont(font);
    WinText.setFillColor(sf::Color::Blue);
    WinText.setPosition(200, 300);
    if (flag_Player1)
        WinText.setString(sf::String(pl1Win));
    else if (flag_Player2)
        WinText.setString(sf::String(pl2Win));
    window_Win.draw(WinText);
    //  window_Win.display();
}
void GameMulti::Run()
{
    Start();
    while (window.isOpen())
    {
        Render();
        processEvents();
        if (count1 == speed1)
        {
            Update();
        }
        count1++;
        // Train2
        if (count2 == speed2)
        {
            Update2();
        }
        count2++;
        if (score1 == 6)
        {
            flag_Player1 = 1;
            window.close();
        }

        if (score2 == 6)
        {
            flag_Player2 = 1;
            window.close();
        }
    }

    window_Win.create(sf::VideoMode(800, 800), "Win Case", sf::Style::Titlebar | sf::Style::Close);
    while (window_Win.isOpen())
    {
        sf::Event event;
        while (window_Win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_Win.close();

            GameMulti::WinCase();
        }
        // window_Win.clear();
        window_Win.display();
    }
}

void GameMulti::Render()
{
    window.clear();
    window.draw(bg);
    window.draw(Score1);
    window.draw(Player1);
    window.draw(Player2);
    setHeadSprite(head1, &TrainSprite1);
    cur1 = head1;
    while (cur1 != NULL)
    {
        if (cur1 != head1)
            setTrailingSprite(cur1, &TrainSprite1);
        (*cur1->s1).setPosition(cur1->posx1, cur1->posy1);
        window.draw(*cur1->s1);
        cur1 = cur1->rlink1;
    }

    GameMulti::Render2();
    window.draw(snoopy);
    window.draw(snoopy2);
    window.draw(snoopy3);
    window.draw(bomb);
    window.display();
}

void GameMulti::Render2()
{

    //------------ Train 2-------------
    window.draw(Score2);
    // oo
    setHeadSprite2(head2, &TrainSprite2);
    cur2 = head2;
    while (cur2 != NULL)
    {
        if (cur2 != head2)
            // oo
            setTrailingSprite2(cur2, &TrainSprite2);
        (*cur2->s2).setPosition(cur2->posx2, cur2->posy2);
        window.draw(*cur2->s2);
        cur2 = cur2->rlink2;
    }
    // window.clear();
    // window.display();
}

void GameMulti::LoadSprites()
{
    this->spriteSheet.loadFromFile("resources/trainsprite.png");
    TrainSprite1.setTexture(spriteSheet);
    TrainSprite1.setScale(sf::Vector2f(0.25, 0.25));
    TrainSprite1.setOrigin(104.5, 104.5);
    // Snoopy 1
    snoopy.setTexture(spriteSheet);
    snoopy.setTextureRect(sf::IntRect(size * 3, size * 1, size, size));
    snoopy.setScale(0.2, 0.2);
    snoopy.setOrigin(104.5, 104.5);
    // Snoopy 2
    snoopy2.setTexture(spriteSheet);
    snoopy2.setTextureRect(sf::IntRect(size * 3, size * 1, size, size));
    snoopy2.setScale(0.2, 0.2);
    snoopy2.setOrigin(104.5, 104.5);
    // Snoopy 3
    snoopy3.setTexture(spriteSheet);
    snoopy3.setTextureRect(sf::IntRect(size * 3, size * 1, size, size));
    snoopy3.setScale(0.2, 0.2);
    snoopy3.setOrigin(104.5, 104.5);
    // Bomb
    this->spriteSheet3.loadFromFile("resources/trainsprite3.png");
    bomb.setTexture(spriteSheet3);
    bomb.setTextureRect(sf::IntRect(size * 3, size * 1, size, size));
    bomb.setScale(0.2, 0.2);
    bomb.setOrigin(104.5, 104.5);

    font.loadFromFile("resources/Roboto-Bold.ttf");
    Score1.setFont(font);
    Score1.setFillColor(sf::Color::Black);

    this->Background.loadFromFile("resources/sand.jpg");
    bg.setTexture(Background);
    bg.setScale(2, 2);
}
void GameMulti::LoadSprites2()
{

    //------------- Train 2 -----------------
    this->spriteSheet2.loadFromFile("resources/trainsprite2.png");
    // oo
    TrainSprite2.setTexture(spriteSheet2);
    TrainSprite2.setScale(sf::Vector2f(0.25, 0.25));
    TrainSprite2.setOrigin(104.5, 104.5);

    font.loadFromFile("resources/Roboto-Bold.ttf");
    // To Represent Score of player 2 on the Screen
    Score2.setFont(font);
    Score2.setFillColor(sf::Color::Black);
    // To Represent (player 1 ) on the Screen
    Player1.setFont(font);
    Player1.setFillColor(sf::Color::Blue);
    // To Represent (player 2) on the Screen
    Player2.setFont(font);
    Player2.setFillColor(sf::Color::Blue);
}

void GameMulti::setHeadSprite(NODEMULTI node, sf::Sprite *sp)
{
    switch (head1->direction1)
    {
    case up:
        sp->setTextureRect(sf::IntRect(size * 1, size * 0, size, size));
        head1->s1 = sp;
        break;
    case down:
        sp->setTextureRect(sf::IntRect(size * 0, size * 0, size, size));
        head1->s1 = sp;
        break;
    case sh:
        sp->setTextureRect(sf::IntRect(size * 3, size * 0, size, size));
        head1->s1 = sp;
        break;
    case ymeen:
        sp->setTextureRect(sf::IntRect(size * 2, size * 0, size, size));
        head1->s1 = sp;
        break;
    }
}
void GameMulti::setHeadSprite2(NODEMULTI node, sf::Sprite *sp)
{
    //------------ TRAIN 2-----------------
    switch (head2->direction2)
    {
    case up:
        sp->setTextureRect(sf::IntRect(size * 1, size * 0, size, size));
        head2->s2 = sp;
        break;
    case down:
        sp->setTextureRect(sf::IntRect(size * 0, size * 0, size, size));
        head2->s2 = sp;
        break;
    case sh:
        sp->setTextureRect(sf::IntRect(size * 3, size * 0, size, size));
        head2->s2 = sp;
        break;
    case ymeen:
        sp->setTextureRect(sf::IntRect(size * 2, size * 0, size, size));
        head2->s2 = sp;
        break;
    }
}

void GameMulti::setTrailingSprite(NODEMULTI node, sf::Sprite *sp)
{

    switch (node->direction1)
    {
    case up:
        sp->setTextureRect(sf::IntRect(size * 1, size * 1, size, size));
        node->s1 = sp;
        break;
    case down:
        sp->setTextureRect(sf::IntRect(size * 2, size * 1, size, size));
        node->s1 = sp;
        break;
    case sh:
        sp->setTextureRect(sf::IntRect(size * 0, size * 1, size, size));
        node->s1 = sp;
        break;
    case ymeen:
        sp->setTextureRect(sf::IntRect(size * 0, size * 1, size, size));
        node->s1 = sp;
        break;
    }
}
void GameMulti::setTrailingSprite2(NODEMULTI node, sf::Sprite *sp)
{

    switch (node->direction2)
    {
    case up:
        sp->setTextureRect(sf::IntRect(size * 1, size * 1, size, size));
        node->s2 = sp;
        break;
    case down:
        sp->setTextureRect(sf::IntRect(size * 2, size * 1, size, size));
        node->s2 = sp;
        break;
    case sh:
        sp->setTextureRect(sf::IntRect(size * 0, size * 1, size, size));
        node->s2 = sp;
        break;
    case ymeen:
        sp->setTextureRect(sf::IntRect(size * 0, size * 1, size, size));
        node->s2 = sp;
        break;
    }
}

void GameMulti::processEvents()
{
    if (window.pollEvent(event))
    {
        switch (event.type)
        {
            // If we close the window --> Terminates the game
        case sf::Event::Closed:
            window.close();
            break;
            // Keyboard controll

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::W && head1->direction1 != down)
            {
                head1->direction1 = up;
            }
            else if (event.key.code == sf::Keyboard::S && head1->direction1 != up)
            {
                head1->direction1 = down;
            }
            else if (event.key.code == sf::Keyboard::A && head1->direction1 != ymeen)
            {
                head1->direction1 = sh;
            }
            else if (event.key.code == sf::Keyboard::D && head1->direction1 != sh)
            {
                head1->direction1 = ymeen;
            }
            //------------------
            if (event.key.code == sf::Keyboard::I && head2->direction2 != down)
            {
                head2->direction2 = up;
            }
            else if (event.key.code == sf::Keyboard::K && head2->direction2 != up)
            {
                head2->direction2 = down;
            }
            else if (event.key.code == sf::Keyboard::J && head2->direction2 != ymeen)
            {
                head2->direction2 = sh;
            }
            else if (event.key.code == sf::Keyboard::L && head2->direction2 != sh)
            {
                head2->direction2 = ymeen;
            }
        }
    }
}

sf::Vector2f GameMulti::getSnoopyCoords()
{
    return sf::Vector2f((rand() % 26 + 1) * side * 2, (rand() % 19 + 1) * side * 2);
}

sf::Vector2f GameMulti::getSnoopyCoords2()
{
    return sf::Vector2f((rand() % 26 + 1) * side * 2, (rand() % 19 + 1) * side * 2);
}

sf::Vector2f GameMulti::getSnoopyCoords3()
{
    return sf::Vector2f((rand() % 26 + 1) * side * 2, (rand() % 19 + 1) * side * 2);
}

sf::Vector2f GameMulti::getBombCoords()
{
    return sf::Vector2f((rand() % 26 + 1) * side * 2, (rand() % 19 + 1) * side * 2);
}

//------------------------------------------------
void GameMulti::HandleSnoopyTouched()
{
    if (isSnoopyTouched(head1, &snoopy))
    {
        //--- to increse the length of the train --------
        head1 = insertHead(head1, &TrainSprite1);
        speed1--;
        while (1)
        {
            // Generarted snopy pos is saved
            snoopyPos = getSnoopyCoords();
            cur1 = head1;
            while (cur1 != NULL)
            {
                if (cur1->posx1 == snoopyPos.x && cur1->posy1 == snoopyPos.y)
                {
                    break;
                }
                cur1 = cur1->rlink1;
            }
            if (cur1 == NULL)
                break;
        }
        snoopy.setPosition(getSnoopyCoords());
        score1++;
        Score1.setString(sf::String(std::to_string(score1)));
    }
}
void GameMulti::HandleSnoopyTouched2()
{
    if (isSnoopyTouched2(head2, &snoopy))
    {
        //--- to increse the length of the train --------
        // oo
        head2 = insertHead2(head2, &TrainSprite2);
        speed2--;
        while (1)
        {
            // Generarted snopy pos is saved
            snoopyPos = getSnoopyCoords();
            cur2 = head2;
            while (cur2 != NULL)
            {
                if (cur2->posx2 == snoopyPos.x && cur2->posy2 == snoopyPos.y)
                {
                    break;
                }
                cur2 = cur2->rlink2;
            }
            if (cur2 == NULL)
                break;
        }
        snoopy.setPosition(getSnoopyCoords());
        score2++;
        Score2.setString(sf::String(std::to_string(score2)));
    }
}
//-------------------------------------------------
void GameMulti::HandleSnoopy2Touched()
{
    if (isSnoopyTouched(head1, &snoopy2))
    {
        //--- to increse the length of the train --------
        head1 = insertHead(head1, &TrainSprite1);
        speed1--;
        while (1)
        {
            // Generarted snopy pos is saved
            snoopyPos2 = getSnoopyCoords2();
            cur1 = head1;
            while (cur1 != NULL)
            {
                if (cur1->posx1 == snoopyPos2.x && cur1->posy1 == snoopyPos2.y)
                {
                    break;
                }
                cur1 = cur1->rlink1;
            }
            if (cur1 == NULL)
                break;
        }
        snoopy2.setPosition(getSnoopyCoords2());
        score1++;
        Score1.setString(sf::String(std::to_string(score1)));
    }
}
void GameMulti::HandleSnoopy2Touched2()
{
    if (isSnoopyTouched2(head2, &snoopy2))
    {
        //--- to increse the length of the train --------
        // oo
        head2 = insertHead2(head2, &TrainSprite2);
        speed2--;
        while (1)
        {
            // Generarted snopy pos is saved
            snoopyPos2 = getSnoopyCoords2();
            cur2 = head2;
            while (cur2 != NULL)
            {
                if (cur2->posx2 == snoopyPos2.x && cur2->posy2 == snoopyPos2.y)
                {
                    break;
                }
                cur2 = cur2->rlink2;
            }
            if (cur2 == NULL)
                break;
        }
        snoopy2.setPosition(getSnoopyCoords2());
        score2++;
        Score2.setString(sf::String(std::to_string(score2)));
    }
}
//------------------------------------------------

void GameMulti::HandleSnoopy3Touched()
{
    if (isSnoopyTouched(head1, &snoopy3))
    {
        //--- to increse the length of the train --------
        head1 = insertHead(head1, &TrainSprite1);
        speed1--;
        while (1)
        {
            // Generarted snopy pos is saved
            snoopyPos3 = getSnoopyCoords3();
            cur1 = head1;
            while (cur1 != NULL)
            {
                if (cur1->posx1 == snoopyPos3.x && cur1->posy1 == snoopyPos3.y)
                {
                    break;
                }
                cur1 = cur1->rlink1;
            }
            if (cur1 == NULL)
                break;
        }
        snoopy3.setPosition(getSnoopyCoords3());
        score1++;
        Score1.setString(sf::String(std::to_string(score1)));
    }
}
void GameMulti::HandleSnoopy3Touched2()
{
    if (isSnoopyTouched2(head2, &snoopy3))
    {
        //--- to increse the length of the train --------
        // oo
        head2 = insertHead2(head2, &TrainSprite2);
        speed2--;
        while (1)
        {
            // Generarted snopy pos is saved
            snoopyPos3 = getSnoopyCoords3();
            cur2 = head2;
            while (cur2 != NULL)
            {
                if (cur2->posx2 == snoopyPos3.x && cur2->posy2 == snoopyPos3.y)
                {
                    break;
                }
                cur2 = cur2->rlink2;
            }
            if (cur2 == NULL)
                break;
        }
        snoopy3.setPosition(getSnoopyCoords2());
        score2++;
        Score2.setString(sf::String(std::to_string(score2)));
    }
}
//-------------------------------------------------

void GameMulti::HandleBombTouched()
{
    if (isBombTouched(head1, &bomb))
    {
        //--- to increse the length of the train --------
        tail1 = deleteTail(tail1);
        speed1++;
        while (1)
        {
            // Generarted snopy pos is saved
            bombPos = getBombCoords();
            cur1 = head1;
            while (cur1 != NULL)
            {
                if (cur1->posx1 == bombPos.x && cur1->posy1 == bombPos.y)
                {
                    break;
                }
                cur1 = cur1->rlink1;
            }
            if (cur1 == NULL)
                break;
        }
        bomb.setPosition(getBombCoords());
        score1--;
        if (score1 == -1)
        {
            flag_Player2 = 1;
            window.close();
        }
        Score1.setString(sf::String(std::to_string(score1)));
    }
}
void GameMulti::HandleBombTouched2()
{
    if (isBombTouched2(head2, &bomb))
    {
        //--- to increse the length of the train --------
        // oo
        tail2 = deleteTail2(tail2);
        speed2++;
        while (1)
        {
            // Generarted snopy pos is saved
            bombPos = getBombCoords();
            cur2 = head2;
            while (cur2 != NULL)
            {
                if (cur2->posx2 == bombPos.x && cur2->posy2 == bombPos.y)
                {
                    break;
                }
                cur2 = cur2->rlink2;
            }
            if (cur2 == NULL)
                break;
        }
        bomb.setPosition(getBombCoords());
        score2--;

        if (score2 == -1)
        {
            flag_Player1 = 1;
            window.close();
        }
        Score2.setString(sf::String(std::to_string(score2)));
    }
}

//----------------------  --------------------
bool GameMulti::isSnoopyTouched(NODEMULTI head, sf::Sprite *snoopy)
{
    // Vector 2f : Generate Coordinates of the plane
    return sf::Vector2f(head->posx1, head->posy1) == snoopy->getPosition();
}
bool GameMulti::isSnoopyTouched2(NODEMULTI head, sf::Sprite *snoopy)
{

    // Vector 2f : Generate Coordinates of the plane
    return sf::Vector2f(head->posx2, head->posy2) == snoopy->getPosition();
}

bool GameMulti::isBombTouched(NODEMULTI head, sf::Sprite *snoopy)
{
    // Vector 2f : Generate Coordinates of the plane
    return sf::Vector2f(head->posx1, head->posy1) == snoopy->getPosition();
}
bool GameMulti::isBombTouched2(NODEMULTI head, sf::Sprite *snoopy)
{
    // Vector 2f : Generate Coordinates of the plane
    return sf::Vector2f(head->posx2, head->posy2) == snoopy->getPosition();
}

//---- To Check When Train hit himself------------
void GameMulti::checkIntersection(NODEMULTI head, sf::RenderWindow *window)
{

    // Train 1
    NODEMULTI cur1 = head->rlink1;
    // Funciton for train 1
    while (cur1 != NULL)
    {
        // when the Head of the train hits the body of the train
        if (head->posx1 == cur1->posx1 && head->posy1 == cur1->posy1)
        {
            // To close the game when the train hit himself
            window->close();
        }
        cur1 = cur1->rlink1;
    }
}
void GameMulti::checkIntersection2(NODEMULTI head, sf::RenderWindow *window)
{

    // Train 1
    NODEMULTI cur2 = head->rlink2;
    // Funciton for train 1
    while (cur2 != NULL)
    {
        // when the Head of the train hits the body of the train
        if (head->posx2 == cur2->posx2 && head->posy2 == cur2->posy2)
        {
            // To close the game when the train hit himself
            window->close();
        }
        cur2 = cur2->rlink2;
    }
}

//-------------------------- Start of The Program ------------------------
//------------------------ Generating The Main Menu----------------------
int main()
{
    while (true)
    {
        sf::RenderWindow window(VideoMode(1000, 1000), "SFML_Make_Menu", sf::Style::Close);
        Main_menu menu(800, 500);
        Mode_menu mode(800, 500);
        Game game;
        GameMulti game2;

        // Game game;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    flag_main = 1;
                    window.close();
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu.moveUp();
                        break;
                    }
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        menu.moveDown();
                        break;
                    }

                    // choose page
                    if (event.key.code == sf::Keyboard::Return) // enter keyboard
                    {
                        // We move with arrows --> mainmenuSelected has certain value
                        // Funciton mainMenuPressed() returns this value
                        // if we pressed on it -> set the variable and close the  window
                        if (menu.mainMenuPressed() == 0)
                        {
                            window.close();
                            page_number = 0;
                        }
                        if (menu.mainMenuPressed() == 1)
                        {
                            window.close();
                            page_number = 1;
                        }
                        // if (menu.mainMenuPressed() == 2)
                        // {
                        //     window.close();
                        //     page_number = 2;
                        // }
                    }
                }
            } // Exit From While(Awaits Certain event)
            window.clear();
            menu.draw(window);
            window.display();
        } // Exit From(Window is open)
        if (flag_main)
            break;
        // Continue while(1)
        if (page_number == 0)
        {
            // play
            sf::RenderWindow window_play(VideoMode(1000, 1000), "Modes", sf::Style::Close);
            while (window_play.isOpen())
            {
                sf::Event event;
                while (window_play.pollEvent(event))
                {
                    //--------------------------------------------------------------------------------------------------------------------------
                    //-----------------------------------------------------------------------------------------------------------------------------------
                    if (event.type == sf::Event::Closed)
                    {
                        flag = 1;
                        window_play.close();
                    }
                    if (event.type == sf::Event::KeyReleased)
                    {
                        if (event.key.code == sf::Keyboard::Up)
                        {
                            mode.moveUp();
                            break;
                        }
                        if (event.key.code == sf::Keyboard::Down)
                        {
                            mode.moveDown();
                            break;
                        }

                        // choose page
                        if (event.key.code == sf::Keyboard::Return) // enter keyboard
                        {
                            // We move with arrows --> mainmenuSelected has certain value
                            // Funciton mainMenuPressed() returns this value
                            // if we pressed on it -> set the variable and close the  window
                            if (mode.modeMenuPressed() == 0)
                            {
                                window_play.close();
                                mode_number = 0;
                            }
                            if (mode.modeMenuPressed() == 1)
                            {
                                window_play.close();
                                mode_number = 1;
                            }
                        }
                    }
                } // Exit From While(Awaits Certain event)
                window_play.clear();
                mode.draw(window_play);
                window_play.display();

            } // Exit From(Window is open)
              // Continue while(1)
            if (flag)
                break;
            if (mode_number == 0)
            {
                game.Run();
            }
            if (mode_number == 1)
            {
                game2.Run();
                /*
                                sf::RenderWindow window_Win(VideoMode(1000, 1000), "WinCase ", sf::Style::Close);
                                while (window_Win.isOpen())
                                {
                                    sf::Event event;
                                    while (window_Win.pollEvent(event))
                                    {
                                        if (event.type == sf::Event::Closed)
                                            window_Win.close();

                                        game2.WinCase(*window);
                                    }
                                    window_Win.clear();
                                    window_Win.display();
                                }
                                */
            }
            break;
        }
        //--------------------------------------------------------------------------------------------------------------------------
        //--------------------------------------------------------------------------------------------------------------------------

        if (page_number == 1)
        {
            // exit
            break;
        }
    }
    return 0;
}
// if (page_number == 1)
// {
//     // options
//     sf::RenderWindow window_play(VideoMode(300, 300), "options", sf::Style::Close);
//     while (window_play.isOpen())
//     {
//         sf::Event event;
//         while (window_play.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window_play.close();
//         }
//         window_play.clear();
//         window_play.display();
//     }
// }

/*

Hit Border -- > Lose
Lose --> Screen Game Over



*/

/* to generate the white screen

// sf::RenderWindow window_game(VideoMode(1000, 1000), "Snake Game", sf::Style::Close);

                // while (window_game.isOpen())
                // {
                //     sf::Event event;
                //     while (window_game.pollEvent(event))
                //     {

                //         // To terminate the screen
                //         if (event.type == sf::Event::Closed)
                //             window_game.close();
                //         game.Run();
                //     }
                //     window_game.clear();
                //     window_game.display();
                // }

*/