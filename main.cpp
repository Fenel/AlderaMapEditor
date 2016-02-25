#include <iostream>
#include <SFML/Graphics.hpp>

#include "enums.h"
struct KeyStorage keyStorage;
#include "system.h"
#include "baseItems.h"
#include "creaturesManager.h"
#include "map.h"
#include "game.h"

sf::RenderWindow App;
sf::RenderTexture renderedMapTexture;
System System(800,600,32);
BaseItems BaseItems;
CreaturesManager CreaturesManager;
Map Map;
Game Game;

sf::Texture guiTexture;
sf::Texture guiCheckBox;
sf::Texture guiCheckBoxChecked;

int mouse_x = 0, mouse_y = 0, mouse_b = 0;

std::string intToStr(int n)
{
     std::string tmp;
     if(n < 0) {
          tmp = "-";
          n = -n;
     }
     if(n > 9)
          tmp += intToStr(n / 10);
     tmp += n % 10 + 48;
     return tmp;
}

int main(int argc, char *argv[])
{
	if (!guiTexture.loadFromFile("data/guiTexture.bmp"))
    return EXIT_FAILURE;

	if (!guiCheckBox.loadFromFile("data/guiCheckBox.bmp"))
		return EXIT_FAILURE;
	if (!guiCheckBoxChecked.loadFromFile("data/guiCheckBoxChecked.bmp"))
		return EXIT_FAILURE;

	Game.loop();

	return 0;
}

bool SFKeyToString(unsigned int keycode, char &keyStr, bool numbers = false) 
{  
	if(numbers)
	{
		switch (keycode)
		{
			case sf::Keyboard::Num0: (keyStr ='0'); break; 
			case sf::Keyboard::Num1: (keyStr ='1'); break; 
			case sf::Keyboard::Num2: (keyStr ='2'); break; 
			case sf::Keyboard::Num3: (keyStr ='3'); break; 
			case sf::Keyboard::Num4: (keyStr ='4'); break; 
			case sf::Keyboard::Num5: (keyStr ='5'); break; 
			case sf::Keyboard::Num6: (keyStr ='6'); break; 
			case sf::Keyboard::Num7: (keyStr ='7'); break; 
			case sf::Keyboard::Num8: (keyStr ='8'); break; 
			case sf::Keyboard::Num9: (keyStr ='9'); break; 
			case sf::Keyboard::Numpad0: (keyStr = '0'); break;
			case sf::Keyboard::Numpad1: (keyStr = '1'); break; 
			case sf::Keyboard::Numpad2: (keyStr = '2'); break; 
			case sf::Keyboard::Numpad3: (keyStr = '3'); break; 
			case sf::Keyboard::Numpad4: (keyStr = '4'); break; 
			case sf::Keyboard::Numpad5: (keyStr = '5'); break; 
			case sf::Keyboard::Numpad6: (keyStr = '6'); break; 
			case sf::Keyboard::Numpad7: (keyStr = '7'); break; 
			case sf::Keyboard::Numpad8: (keyStr = '8'); break; 
			case sf::Keyboard::Numpad9: (keyStr = '9'); break;
					        
			default:
			{
			    keyStr = '%c'; 
				return false;
			}
		}
		return true;
	}
	if(!keyStorage.shift)
	{
		switch (keycode)
		{
			case sf::Keyboard::A: (keyStr ='a'); break; 
			case sf::Keyboard::B: (keyStr ='b'); break; 
			case sf::Keyboard::C: (keyStr ='c'); break; 
			case sf::Keyboard::D: (keyStr ='d'); break; 
			case sf::Keyboard::E: (keyStr ='e'); break; 
			case sf::Keyboard::F: (keyStr ='f'); break; 
			case sf::Keyboard::G: (keyStr ='g'); break; 
			case sf::Keyboard::H: (keyStr ='h'); break; 
			case sf::Keyboard::I: (keyStr ='i'); break; 
			case sf::Keyboard::J: (keyStr ='j'); break; 
			case sf::Keyboard::K: (keyStr ='k'); break; 
			case sf::Keyboard::L: (keyStr ='l'); break; 
			case sf::Keyboard::M: (keyStr ='m'); break; 
			case sf::Keyboard::N: (keyStr ='n'); break; 
			case sf::Keyboard::O: (keyStr ='o'); break; 
			case sf::Keyboard::P: (keyStr ='p'); break; 
			case sf::Keyboard::Q: (keyStr ='q'); break; 
			case sf::Keyboard::R: (keyStr ='r'); break; 
			case sf::Keyboard::S: (keyStr ='s'); break; 
			case sf::Keyboard::T: (keyStr ='t'); break; 
			case sf::Keyboard::U: (keyStr ='u'); break; 
			case sf::Keyboard::V: (keyStr ='v'); break; 
			case sf::Keyboard::W: (keyStr ='w'); break; 
			case sf::Keyboard::X: (keyStr ='x'); break; 
			case sf::Keyboard::Y: (keyStr ='y'); break; 
			case sf::Keyboard::Z: (keyStr ='z'); break; 

			case sf::Keyboard::Num0: (keyStr ='0'); break; 
			case sf::Keyboard::Num1: (keyStr ='1'); break; 
			case sf::Keyboard::Num2: (keyStr ='2'); break; 
			case sf::Keyboard::Num3: (keyStr ='3'); break; 
			case sf::Keyboard::Num4: (keyStr ='4'); break; 
			case sf::Keyboard::Num5: (keyStr ='5'); break; 
			case sf::Keyboard::Num6: (keyStr ='6'); break; 
			case sf::Keyboard::Num7: (keyStr ='7'); break; 
			case sf::Keyboard::Num8: (keyStr ='8'); break; 
			case sf::Keyboard::Num9: (keyStr ='9'); break; 

			case sf::Keyboard::Space: (keyStr = ' '); break;
			case sf::Keyboard::SemiColon: (keyStr =';'); break; 
			case sf::Keyboard::Comma: (keyStr =','); break; 
			case sf::Keyboard::Period: (keyStr ='.'); break; 
			case sf::Keyboard::BackSlash: (keyStr = 92); break; 
			case sf::Keyboard::Slash: (keyStr ='/'); break; 
			case sf::Keyboard::Tilde: (keyStr ='~'); break; 
			case sf::Keyboard::Equal: (keyStr ='='); break; 
			case sf::Keyboard::Dash: (keyStr ='-'); break; 
			case sf::Keyboard::LBracket: (keyStr = '['); break; 
			case sf::Keyboard::RBracket: (keyStr = ']'); break; 
			case sf::Keyboard::Add: (keyStr ='='); break; 
			case sf::Keyboard::Subtract: (keyStr ='_'); break; 
			case sf::Keyboard::Multiply: (keyStr ='*'); break; 
			case sf::Keyboard::Divide: (keyStr ='/'); break; 


			case sf::Keyboard::Numpad0: (keyStr = '0'); break;
			case sf::Keyboard::Numpad1: (keyStr = '1'); break; 
			case sf::Keyboard::Numpad2: (keyStr = '2'); break; 
			case sf::Keyboard::Numpad3: (keyStr = '3'); break; 
			case sf::Keyboard::Numpad4: (keyStr = '4'); break; 
			case sf::Keyboard::Numpad5: (keyStr = '5'); break; 
			case sf::Keyboard::Numpad6: (keyStr = '6'); break; 
			case sf::Keyboard::Numpad7: (keyStr = '7'); break; 
			case sf::Keyboard::Numpad8: (keyStr = '8'); break; 
			case sf::Keyboard::Numpad9: (keyStr = '9'); break; 

					       
			default:
			{
				keyStr = '%c'; 
				return false;
			}
		}
	}
	else
	{
		switch (keycode)
		{	
			case sf::Keyboard::A: (keyStr ='A'); break; 
			case sf::Keyboard::B: (keyStr ='B'); break; 
			case sf::Keyboard::C: (keyStr ='C'); break; 
			case sf::Keyboard::D: (keyStr ='D'); break; 
			case sf::Keyboard::E: (keyStr ='E'); break; 
			case sf::Keyboard::F: (keyStr ='F'); break; 
			case sf::Keyboard::G: (keyStr ='G'); break; 
			case sf::Keyboard::H: (keyStr ='H'); break; 
			case sf::Keyboard::I: (keyStr ='I'); break; 
			case sf::Keyboard::J: (keyStr ='J'); break; 
			case sf::Keyboard::K: (keyStr ='K'); break; 
			case sf::Keyboard::L: (keyStr ='L'); break; 
			case sf::Keyboard::M: (keyStr ='M'); break; 
			case sf::Keyboard::N: (keyStr ='N'); break; 
			case sf::Keyboard::O: (keyStr ='O'); break; 
			case sf::Keyboard::P: (keyStr ='P'); break; 
			case sf::Keyboard::Q: (keyStr ='Q'); break; 
			case sf::Keyboard::R: (keyStr ='R'); break; 
			case sf::Keyboard::S: (keyStr ='S'); break; 
			case sf::Keyboard::T: (keyStr ='T'); break; 
			case sf::Keyboard::U: (keyStr ='U'); break; 
			case sf::Keyboard::V: (keyStr ='V'); break; 
			case sf::Keyboard::W: (keyStr ='W'); break; 
			case sf::Keyboard::X: (keyStr ='X'); break; 
			case sf::Keyboard::Y: (keyStr ='Y'); break; 
			case sf::Keyboard::Z: (keyStr ='Z'); break; 

			case sf::Keyboard::Num0: (keyStr =')'); break; 
			case sf::Keyboard::Num1: (keyStr ='!'); break; 
			case sf::Keyboard::Num2: (keyStr ='@'); break; 
			case sf::Keyboard::Num3: (keyStr ='#'); break; 
			case sf::Keyboard::Num4: (keyStr ='$'); break; 
			case sf::Keyboard::Num5: (keyStr ='%'); break; 
			case sf::Keyboard::Num6: (keyStr ='^'); break; 
			case sf::Keyboard::Num7: (keyStr ='&'); break; 
			case sf::Keyboard::Num8: (keyStr ='*'); break; 
			case sf::Keyboard::Num9: (keyStr ='('); break; 

			case sf::Keyboard::Space: (keyStr = ' '); break;
			case sf::Keyboard::SemiColon: (keyStr =':'); break; 
			case sf::Keyboard::Comma: (keyStr ='<'); break; 
			case sf::Keyboard::Period: (keyStr ='>'); break; 
			case sf::Keyboard::BackSlash: (keyStr = '|'); break; //= 124); break; 
			case sf::Keyboard::Slash: (keyStr ='?'); break; 
			case sf::Keyboard::Tilde: (keyStr ='`'); break; 
			case sf::Keyboard::Equal: (keyStr ='+'); break; 
			case sf::Keyboard::Dash: (keyStr ='_'); break; 
			case sf::Keyboard::LBracket: (keyStr = '{'); break; 
			case sf::Keyboard::RBracket: (keyStr = '}'); break; 

			case sf::Keyboard::Add: (keyStr ='+'); break; 
			case sf::Keyboard::Subtract: (keyStr ='-'); break; 
			case sf::Keyboard::Multiply: (keyStr ='*'); break; 
			case sf::Keyboard::Divide: (keyStr ='/'); break; 

			case sf::Keyboard::Numpad0: (keyStr = '0'); break; 
			case sf::Keyboard::Numpad1: (keyStr = '1'); break; 
			case sf::Keyboard::Numpad2: (keyStr = '2'); break; 
			case sf::Keyboard::Numpad3: (keyStr = '3'); break; 
			case sf::Keyboard::Numpad4: (keyStr = '4'); break; 
			case sf::Keyboard::Numpad5: (keyStr = '5'); break; 
			case sf::Keyboard::Numpad6: (keyStr = '6'); break; 
			case sf::Keyboard::Numpad7: (keyStr = '7'); break; 
			case sf::Keyboard::Numpad8: (keyStr = '8'); break; 
			case sf::Keyboard::Numpad9: (keyStr = '9'); break; 
					        
			default:
			{
			    keyStr = '%c'; 
				return false;
			}
		}
	}
	return true;
}

