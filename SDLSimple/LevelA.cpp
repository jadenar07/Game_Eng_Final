#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 100
#define LEVEL_HEIGHT 8
#define FIXED_TIMESTEP 0.0166666f

// Filepaths for textures and assets
constexpr char SPRITESHEET_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/215080.png";
constexpr char ROCKS_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/rocks.png";
constexpr char SMALL_HURDLE_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/ob.png";
constexpr char TRAIN_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/train.png";
constexpr char MAP_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/track.png";
constexpr char JUMP_SOUND_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/jump-up-245782.wav";

extern bool is_moving_right;
extern bool game_loss;

// Map layout data
unsigned int LEVELA_DATA[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, };

LevelA::~LevelA() {
    delete[] obstacles;
    delete m_game_state.player;
    delete m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelA::initialise() {
    m_game_state.next_scene_id = -1;

    // Load map
    GLuint map_texture_id = Utility::load_texture(MAP_TEXTURE_FILEPATH);
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1.0f, 4, 1);

    // Load player
    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);
    int player_walking_animation[4][4] = {
        {8, 9, 10, 11},    // left
        {5, 4, 7, 6},      // right
        {13, 12, 13, 14},  // up
        {1, 2, 3, 0}       // down
    };

    m_game_state.player = new Entity(player_texture_id, 5.0f, glm::vec3(0.0f, -4.81f, 0.0f), 5.0f,
                                     player_walking_animation, 0.0f, 4, 0, 4, 4, 1.0f, 1.0f, PLAYER);
    m_game_state.player->set_position(glm::vec3(1.0f, -5.0f, 0.0f));

    // Load obstacles
    GLuint rocks_texture_id = Utility::load_texture(ROCKS_TEXTURE_FILEPATH);
    GLuint small_hurdle_texture_id = Utility::load_texture(SMALL_HURDLE_TEXTURE_FILEPATH);
    GLuint train_texture_id = Utility::load_texture(TRAIN_TEXTURE_FILEPATH);

    obstacles = new Entity[OBSTACLE_COUNT];
    obstacles[0] = Entity(rocks_texture_id, 1.0f, 3.0f, 3.0f, ENEMY);
    obstacles[0].set_jumping_power(6.0f);

    obstacles[1] = Entity(small_hurdle_texture_id, 1.0f, 2.5f, 2.5f, ENEMY);

    obstacles[2] = Entity(train_texture_id, 2.0f, 8.0f, 8.0f, ENEMY, GUARD, WALKING);

    m_game_state.jump_sfx = Mix_LoadWAV(JUMP_SOUND_FILEPATH);
}

void LevelA::update(float delta_time) {
    // Update obstacles
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        obstacles[i].update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);
    }

    // Check for collisions with obstacles
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        if (m_game_state.player->check_collision(&obstacles[i])) {
            if (m_game_state.player->collided_with_enemy_x) {
                game_loss = true;
                m_game_state.player->deactivate();
                return;
            }
        }
    }
}

void LevelA::render(ShaderProgram* program) {
    // Render the map
    m_game_state.map->render(program);

    // Render the player
    m_game_state.player->render(program);
    
    // Render the obstacles
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        obstacles[i].render(program);
    }
    
    // Draw player-related text
    glm::vec3 player_position = m_game_state.player->get_position();
    player_position.y += 1.5f;
    player_position.x -= 1.0f;
    Utility::draw_text(program, Utility::get_font_id(), "Lives: 3", 0.3f, 0.025f, player_position);
}
