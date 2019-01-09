#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#else
#error "Unrecognized configuration!"
#endif
#include <iostream>
#include "StageScreen.h"
#include "Controller.h"
#include "SingeltonSource.h"
#include "SingeltonSound.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>
#include <conio.h>  
#include <thread>
namespace fs = std::experimental::filesystem;

// Recursive function to load from a directory into the Singleton
// Skips files that contains exception in their name
template <class T>
void loadFromDirectory(const fs::path& path, const std::string& extension, const std::string& exception = ".")
{
	T temp;
	if (fs::exists(path))// test if path exists
	{
		for (auto& elem : fs::directory_iterator(path))
		{
			if (fs::is_regular_file(elem))
			{
				auto p = elem.path();
				if (p.extension().string() == extension)
					if (p.stem().string().find(exception) == std::string::npos)
					{
						temp.loadFromFile(p.string());
						Singleton<T>::getInstance()->addResource({ p.stem().string(), temp });
					}
			}
			else if (fs::is_directory(elem))
				loadFromDirectory<T>(elem.path(), extension, exception);
		}
	}
}


// Loads all types of resources into the Singletons using filesystem library.
// Will add all images, fonts and music in the '/Resources' directory 
void loadResources()
{
	loadFromDirectory<sf::Font>("Resources/Fonts", ".ttf");
	loadFromDirectory<sf::Texture>("Resources/Sprites", ".PNG");
	//loadFromDirectory<sf::SoundBuffer>("Resources/Sounds", ".wav", "music"); // Do not load music files
}


int main()
{
	//std::cout << "Loading resources... ";
	try
	{
		loadResources();
		SingeltonSound::instance();
		Controller c;
		c.run();
	}
		catch (Exception& exception) {
			sf::RenderWindow window(sf::VideoMode(SIZE_WINDOW.second, SIZE_WINDOW.first), "WARNING");
			sf::Text warning;
			//warning.setColor(sf::Color::Red);
			warning.setString(std::string(exception.getError()+"\nin one second the program is exit \n*you need to bring file with match ending \n\n\n\ngood bye:("));
			warning.setFont(*Singleton<sf::Font>::getInstance()->getResource("arial"));
			window.draw(sf::Sprite(*Singleton<sf::Texture>::getInstance()->getResource("background33")));
			window.draw(warning);
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(4500));	// sleep for to see the warning
			exit(EXIT_FAILURE);
		}

	
}