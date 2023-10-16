#pragma once

#include <Crystal/Renderer/Texture.hpp>

#include <string>

//Global
inline uint32_t s_GlobalScale = 3;

inline float s_Gravity = 9.81f * (25 * s_GlobalScale);

//Window properties
inline const std::string s_WindowTitle = "Mario";
inline uint32_t s_WindowWidth = 1280;
inline uint32_t s_WindowHeight = 720;

//Entity properties
inline uint32_t s_EntityWidth = 16;
inline uint32_t s_EntityHeight = 16;

//Mario properties
inline float s_MarioSpeed = 75.0f * s_GlobalScale;

inline float s_MarioAnimationSwitchTime = 0.175f;

inline std::string s_MarioPath = "assets/textures/Small-Mario.png";

//Goomba properties
inline float s_GoombaAnimationSwitchTime = 0.35f;
inline float s_GoombaSpeed = -(50.0f * s_GlobalScale);

//Koopa properties
inline float s_KoopaAnimationSwitchTime = 0.35f;
inline float s_KoopaSpeed = -(35.0f * s_GlobalScale);

//Tile properties
inline uint32_t s_TileWidth = 16;
inline uint32_t s_TileHeight = 16;

//QuestionBlock
inline float s_QBAnimationSwitchTime = 0.15f;




//Tile paths
inline std::string s_GroundPath = "assets/textures/Map.png";
inline Crystal::TexCoords s_GroundTexCoords = Crystal::TexCoords(48, 0, s_TileWidth, s_TileHeight);