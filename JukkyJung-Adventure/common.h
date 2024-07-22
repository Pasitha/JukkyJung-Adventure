#pragma once
// STL
#include <iostream>
#include <sstream>
#include <fstream>
#include <functional>  // for function objects
#include <stdexcept> // for standard exceptions

#include <future>
#include <thread>
#include <mutex>

#include <chrono>  // for time-related functionalities
#include <ctime>   // for time manipulation

#include <unordered_map>
#include <queue>

#include <cmath>  // for math functions
#include <cstdlib> // for general utilities (e.g., atoi)
#include <csignal> // for signal handling

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Discord SDK
#include <discord.h>

#include "Discord.h"
#include "FileLoadException.h"
#include "FileManager.h"
#include "SpriteAnimation.h"
#include "MapManager.h"
#include "Button.h"
#include "UIElementManager.h"
#include "Character.h"
#include "Combat.h"
#include "Game.h"
