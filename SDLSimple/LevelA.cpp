#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 100
#define LEVEL_HEIGHT 8
#define FIXED_TIMESTEP 0.0166666f

constexpr char SPRITESHEET_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/215080.png";
constexpr char MAP_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/track.png";
constexpr char ROCKS_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/rocks.png";
constexpr char SMALL_HURDLE_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/ob.png";
constexpr char TRAIN_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/train.png";
constexpr char BACKGROUND_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/forest.jpg";



extern bool game_loss;
extern bool is_moving_right;
extern int g_score;
extern int coins;

constexpr float BASE_SCALE = 1.0f;
constexpr float MAX_AMPLITUDE = 0.1f;
constexpr float PULSE_SPEED = 20.0f;

int frame_counter = 0;


unsigned int LevelA_DATA[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, };

LevelA::~LevelA() {
    delete m_game_state.player;
    delete m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
    Mix_FreeChunk(m_game_state.sfx_coin);
    Mix_FreeChunk(m_game_state.sfx_defeat);

}

void LevelA::initialise() {
    
    m_game_state.next_scene_id = -1;

    GLuint background_texture_id = Utility::load_texture(BACKGROUND_TEXTURE_FILEPATH);
    if (background_texture_id == 0) {
        std::cout << "Failed to load background texture: " << BACKGROUND_TEXTURE_FILEPATH << std::endl;
    }

    m_game_state.background = new Entity(background_texture_id, 0.0f, 0.0f, 0.0f, BACKGROUND);
    
    m_game_state.background->set_width(1280);
    m_game_state.background->set_height(960);
    // Load map
    GLuint map_texture_id = Utility::load_texture(MAP_TEXTURE_FILEPATH);
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LevelA_DATA, map_texture_id, 1.0f, 4, 1);

    // Load player
    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);
    int player_walking_animation[4][4] = {
        {8, 9, 10, 11},  // left
        {5, 4, 7, 6},    // right
        {13, 12, 13, 14},// up
        {1, 2, 3, 0}     // down
    };

    glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);
    m_game_state.player = new Entity(
        player_texture_id,         // texture id
        4.0f,                      // speed
        acceleration,              // acceleration
        6.0f,                      // jumping power
        player_walking_animation,  // animation index sets
        0.0f,                      // animation time
        4,                         // animation frame amount
        0,                         // current animation index
        4,                         // animation column amount
        4,                         // animation row amount
        1.0f,                      // width
        1.0f,                      // height
        PLAYER                     // entity type
    );

    
    m_game_state.player->set_position(glm::vec3(1.0f, -5.0f, 0.0f));
    
    m_game_state.enemies = new Entity[ENEMY_COUNT];
    
    GLuint train_texture_id = Utility::load_texture(TRAIN_TEXTURE_FILEPATH);
    GLuint hurdle_texture_id = Utility::load_texture(SMALL_HURDLE_TEXTURE_FILEPATH);
    GLuint rocks_texture_id = Utility::load_texture(ROCKS_TEXTURE_FILEPATH);
    GLuint coin_texture_id = Utility::load_texture("/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/coin.png");
    
    float start_x = 20.0f;
    float start_y = -5.0f;
    float coin_y = -4.0f;

    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (i % 2 == 0) {
            if ((i / 2) % 3 == 0) {
                m_game_state.enemies[i] = Entity(train_texture_id, 2.0f, 6.0f, 6.0f, ENEMY, GUARD, IDLE);
            } else if ((i / 2) % 3 == 1) {
                m_game_state.enemies[i] = Entity(hurdle_texture_id, 1.0f, 2.5f, 2.5f, HURDLE);
            } else {
                m_game_state.enemies[i] = Entity(rocks_texture_id, 1.0f, 2.0f, 2.0f, ROCKS, WALKER, WALKING);
            }
            m_game_state.enemies[i].set_position(glm::vec3(start_x + i * 6.0f, start_y, 0.0f));
        } else {
            m_game_state.enemies[i] = Entity(coin_texture_id, 2.0f, 3.0f, 3.0f, COIN);
            m_game_state.enemies[i].set_position(glm::vec3(start_x + i * 6.0f, coin_y, 0.0f));
        }
    }

    
    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (m_game_state.enemies[i].get_entity_type() == ENEMY) {
            m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
        }
        
        if (m_game_state.enemies[i].get_entity_type() == HURDLE) {
            m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, -15.00f, 0.0f));
            m_game_state.enemies[i].set_jumping_power(3.0f);
        }
        
        if (m_game_state.enemies[i].get_entity_type() == ROCKS) {
            m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, -15.00f, 0.0f));
            m_game_state.enemies[i].set_jumping_power(3.0f);
        }
    }
    m_game_state.jump_sfx = Mix_LoadWAV("/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/jump-up-245782.wav");
    m_game_state.sfx_defeat = Mix_LoadWAV("/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/failure.wav");
    m_game_state.sfx_coin = Mix_LoadWAV("/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/coin_sound.wav");

    if (!m_game_state.sfx_defeat || !m_game_state.sfx_coin) {
        std::cout << "Failed to load sound effects: " << Mix_GetError() << std::endl;
    }
}

void LevelA::update(float delta_time) {
    frame_counter++;
    m_game_state.player->update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);

    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (m_game_state.enemies[i].get_entity_type() == ENEMY ||
            m_game_state.enemies[i].get_entity_type() == ROCKS) {
            m_game_state.enemies[i].ai_activate(m_game_state.player);
        }
        m_game_state.enemies[i].update(FIXED_TIMESTEP, m_game_state.player, NULL, 0, m_game_state.map);

        if (m_game_state.player->check_collision(&m_game_state.enemies[i])) {
            if (m_game_state.enemies[i].get_entity_type() == COIN) {
                if (m_game_state.enemies[i].get_is_active()) {
                    coins++;
                    m_game_state.enemies[i].deactivate();
                    Mix_PlayChannel(-1, m_game_state.sfx_coin, 0);
                    std::cout << "Coin collected! Total Coins: " << coins << std::endl;
                }
            } else {
                m_game_state.player->check_collision_x(&m_game_state.enemies[i], 1);
                if (m_game_state.player->get_collided_right()) {
                    game_loss = true;
                    is_moving_right = false;
                    Mix_PlayChannel(-1, m_game_state.sfx_defeat, 0);
                    std::cout << "Game Over!" << std::endl;
                }
            }
            break;
        }
        
    }

    static float jump_timer = 0.0f;
    jump_timer += FIXED_TIMESTEP;
    const float jump_interval = 2.0f;
    if (jump_timer >= jump_interval) {
        for (int i = 0; i < ENEMY_COUNT; i++) {
            if (m_game_state.enemies[i].get_entity_type() == HURDLE || m_game_state.enemies[i].get_entity_type() == ROCKS) {
                m_game_state.enemies[i].jump();
                jump_timer = 0.0f;
            }
        }
    }

    if (m_game_state.player->get_position().y < -10.0f) {
        m_game_state.next_scene_id = 1;
    }

    if (m_game_state.player->get_position().x >= LEVEL_WIDTH - 8.0f) {
        m_game_state.player->set_position(glm::vec3(1.0f, m_game_state.player->get_position().y, 0.0f));
        float start_x = 20.0f;
        for (int i = 0; i < ENEMY_COUNT; i++) {
            m_game_state.enemies[i].set_position(glm::vec3(start_x + i * 12.0f, -5.0f, 0.0f));
            if (m_game_state.enemies[i].get_entity_type() == COIN) {
                m_game_state.enemies[i].activate();
            }
        }
    }

}


void LevelA::render(ShaderProgram* program) {
    glm::vec3 player_position = m_game_state.player->get_position();
    float camera_left = player_position.x - 5.0f;
    float camera_top = player_position.y + 3.75f;
    
    glm::vec3 level_position = glm::vec3(camera_left + 2.5f, camera_top - 0.1f, 0.0f);
    Utility::draw_text(program, Utility::get_font_id(), "Level 1", 0.5f, 0.05f, level_position);
    
    m_game_state.map->render(program);
    m_game_state.player->render(program);

    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (m_game_state.enemies[i].get_is_active()) {
            m_game_state.enemies[i].render(program);
        }
    }


    glm::vec3 score_position = glm::vec3(camera_left + 0.5f, camera_top - 0.5f, 0.0f);
    Utility::draw_text(program, Utility::get_font_id(), std::to_string(g_score), 0.5f, 0.05f, score_position);

    glm::vec3 coin_position = glm::vec3(camera_left + 5.0f, camera_top - 0.5f, 0.0f);
    Utility::draw_text(program, Utility::get_font_id(), "Coins: " + std::to_string(coins), 0.5f, 0.05f, coin_position);

    if (game_loss) {
        glm::vec3 message_position = glm::vec3(player_position.x - 1.5f, player_position.y + 2.0f, 0.0f);
        Utility::draw_text(program, Utility::get_font_id(), "YOU LOST", 0.5f, 0.05f, message_position);
    }
}
