#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib> 
#include <random> 

using namespace std;
using namespace sf; 

string d_desc = "N@#W$9876543210?!abc;:+=-,._";
string d_asc = "_.,-=+:;cba!?0123456789$W#@N";

vector<vector<int>> getPixelsAverages(sf::Image img, int height, int width){
    vector<vector<int>> array;
    for(int i=0; i<=height-1; i++){
        vector<int> a;
        for(int j=0; j<=width-1; j++){
            sf::Color col = img.getPixel(j, i);
            //int avg = (col.r + col.g + col.b) / 3;
            int avg = (col.r * 0.299) + (col.g * 0.587) + (col.b * 0.114);
            a.push_back(avg);
            //cout<<"here" << i << " " << j <<    " " << avg<<  endl;
        }
        array.push_back(a);
    }
    return array;
}

vector<vector<char>> mapToChar(vector<vector<int>> avrgs, string d){
    cout << d.length()<< "{"<< d  << "}" <<  d[0] <<endl;
    vector<vector<char>> str;
    for(int i=0; i<=avrgs.size()-1; i++){
        vector<char> a;
        for(int j=0; j<=avrgs[i].size()-1; j++){
            int x = round((static_cast<float>(d.size()-1) / 255) * (avrgs[i][j]));
            char s = d[x];
            a.push_back(s);
        }
        str.push_back(a);
    }
    return str;
}
Uint8 * createArrayOfPixels(vector<vector<int>> values){
    int full_size = ((values[0].size() *values.size()) * 4);
    Uint8 * array = (Uint8*) malloc(sizeof(Uint8) * full_size);

    int f = 0;
    for(int i=0; i<=values.size()-1; i++){
        for(int j=0; j<=values[i].size()-1; j++){
            array[f] = values[i][j];
            array[f+1] = values[i][j];
            array[f+2] = values[i][j];
            array[f+3] = values[i][j];
            f = f + 4; 
        }
    }
    return array;
}

// (d_des.len / 255) * pixel_val
int main(){
    
    cout << endl;
    
    sf::Image image;
    if (!image.loadFromFile("../res/r.jpeg")){
        cout << "could not load image" << endl;
        return 0;
    }else{
        cout << "loaded image" << endl;
    }

    sf::Vector2u vect = image.getSize();
    
    cout << "number of pixels " << vect.x * vect.y << endl;
    cout << "width X:  " << vect.x << endl;
    cout << "height Y: " << vect.y << endl;
    vector<vector<int>> avrgs =  getPixelsAverages(image, (int)vect.y, (int)vect.x);
    vector<vector<char>> str = mapToChar(avrgs, d_desc);

    ofstream myfile;
    myfile.open ("example.txt");
    for(vector<char> i: str){
        string h = "";
        for (char j: i){
            h += j;
        }
        myfile << h << endl;

    }   
    myfile.close();

    string xx = "";
    for(vector<char> i: str){
        string h = "";
        for (char j: i){
            h += j;
        }
        xx = xx + h + "\n";
    }  

    //image creation 
    sf::Image img;
    Uint8 * pixs = createArrayOfPixels(avrgs);
    img.create(vect.x, vect.y, pixs);
    img.saveToFile("r3.jpg");

    srand(time(0));


    //random generation 
    sf::Image img1;
    //Uint8 * pix = createArrayOfPixels(avrgs);
    for(int i = 0; i<=vect.x-1; i++){
        for(int j = 0; j<=vect.y-1; j++){
            //int r = floor(0.5 + ((double)rand() / RAND_MAX));
            sf::Color coll = image.getPixel(i, j);
            if(((coll.g >= 0 ) && ( coll.g <= 100))
            && ((coll.b >= 0 ) && ( coll.b <= 100))
            && ((coll.r >= 0 ) && ( coll.r <= 100))){
                coll.r = 255;
                coll.g = 188;
                coll.b = 5;
                image.setPixel(i,j, coll);
            }
        }
    }
    img1.create(vect.x, vect.y, image.getPixelsPtr());
    img1.saveToFile("r2.jpg");


    //random gen
    sf::Image img2;
    //Uint8 * pix = createArrayOfPixels(avrgs);
    for(int i = 0; i<=vect.x-1; i++){
        for(int j = 0; j<=vect.y-1; j++){
            int r = floor(0.5 + ((double)rand() / RAND_MAX));
            if(r ==3){
                sf::Color coll = image.getPixel(i, j);
                std::random_device rd;     // Only used once to initialise (seed) engine
                std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
                std::uniform_int_distribution<int> uniX(0,vect.x); // Guaranteed unbiased
                std::uniform_int_distribution<int> uniY(0,vect.y); // Guaranteed unbiased

                int rX = uniX(rng);
                int rY = uniY(rng);
                //cout << random_integer <<endl;

                image.setPixel(0,1, coll);
            }
        }
    }
    img2.create(vect.x, vect.y, image.getPixelsPtr());
    img2.saveToFile("r1.jpg");

    sf::RectangleShape blank;
    blank.setSize(sf::Vector2f(vect.x, vect.y));
    blank.setPosition(0,0);


    sf::Font font;
    if (!font.loadFromFile("Anonymous.ttf")){
        return 0;
    }
    sf::Text text;
    text.setFont(font);
    text.setString(xx);
    text.setCharacterSize(1);
    text.setFillColor(sf::Color::Black);

    sf::RenderWindow window(sf::VideoMode(vect.x, vect.y), "SFML works!");

/*    while (window.isOpen()){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(blank);
        window.draw(text);
        window.display(); 
    }*/

    return 0;
}