#include "LevelB.h"
#include "Utility.h"

#define LEVEL_WIDTH 100
#define LEVEL_HEIGHT 8
#define FIXED_TIMESTEP 0.0166666f

constexpr char SPRITESHEET_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/215080.png";
constexpr char MAP_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/track.png";
constexpr char ROCKS_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/rocks.png";
constexpr char SMALL_HURDLE_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/ob.png";
constexpr char TRAIN_TEXTURE_FILEPATH[] = "/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/train.png";

bool game_loss_b = false;

unsigned int LEVELB_DATA[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, };

LevelB::~LevelB() {
    delete m_game_state.player;
    delete m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelB::initialise() {
    m_game_state.next_scene_id = -1;

    // Load map
    GLuint map_texture_id = Utility::load_texture(MAP_TEXTURE_FILEPATH);
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELB_DATA, map_texture_id, 1.0f, 4, 1);

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
        5.0f,                      // speed
        acceleration,              // acceleration
        5.0f,                      // jumping power
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
    
    m_game_state.enemies[0] = Entity(train_texture_id, 2.0f, 3.0f, 3.0f, ENEMY, GUARD, IDLE);
    m_game_state.enemies[1] = Entity(hurdle_texture_id, 1.0f, 2.5f, 2.5f, HURDLE);
    m_game_state.enemies[2] = Entity(rocks_texture_id, 1.0f, 2.0f, 2.0f, ROCKS, GUARD, IDLE);
    
    m_game_state.enemies[3] = Entity(train_texture_id, 2.0f, 3.0f, 3.0f, ENEMY, GUARD, IDLE);
    m_game_state.enemies[4] = Entity(hurdle_texture_id, 1.0f, 2.5f, 2.5f, HURDLE);
    m_game_state.enemies[5] = Entity(rocks_texture_id, 1.0f, 2.0f, 2.0f, ENEMY, GUARD, IDLE);
    
    m_game_state.enemies[6] = Entity(train_texture_id, 2.0f, 3.0f, 3.0f, ENEMY, GUARD, IDLE);
    m_game_state.enemies[7] = Entity(hurdle_texture_id, 1.0f, 2.5f, 2.5f, HURDLE);
    m_game_state.enemies[8] = Entity(rocks_texture_id, 1.0f, 2.0f, 2.0f, ROCKS, GUARD, IDLE);


    float start_x = 20.0f;
    for (int i = 0; i < ENEMY_COUNT; i++) {
        m_game_state.enemies[i].set_position(glm::vec3(start_x + i * 12.0f, -5.0f, 0.0f));
    }
    
    for (int i = 0; i < ENEMY_COUNT; i++) {
        if (m_game_state.enemies[i].get_entity_type() == ENEMY) {
            m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
        }
        
        if (m_game_state.enemies[i].get_entity_type() == HURDLE) {
            m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
            m_game_state.enemies[i].set_jumping_power(5.0f);
        }
        
        if (m_game_state.enemies[i].get_entity_type() == ROCKS) {
            m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
            m_game_state.enemies[i].set_jumping_power(5.0f);
        }
    }
    m_game_state.jump_sfx = Mix_LoadWAV("/Users/jadenritchie/Desktop/SDLSimple/SDLSimple/assets/madara.wav");
}

void LevelB::update(float delta_time) {
    m_game_state.player->update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);
    
    for (int i = 0; i < ENEMY_COUNT; i++) {
        m_game_state.enemies[i].update(FIXED_TIMESTEP, m_game_state.player, NULL, 0, m_game_state.map);
    }
    
    static float jump_timer = 0.0f;
    jump_timer += FIXED_TIMESTEP;
    const float jump_interval = 2.0f;
    if (jump_timer >= jump_interval) {
        for (int i = 0; i < ENEMY_COUNT; i++) {
            if (m_game_state.enemies[i].get_entity_type() == HURDLE) {
                m_game_state.enemies[i].jump();
                jump_timer = 0.0f;
            }
        }
    }

    // Check if player falls off the map
    if (m_game_state.player->get_position().y < -10.0f) {
        m_game_state.next_scene_id = 1;
    }
    
    if (m_game_state.player->get_position().x >= LEVEL_WIDTH - 8.0f) {
        m_game_state.player->set_position(glm::vec3(1.0f, m_game_state.player->get_position().y, 0.0f));
    }
}

void LevelB::render(ShaderProgram* program) {
    m_game_state.map->render(program);
    m_game_state.player->render(program);
    
    for (int i = 0; i < ENEMY_COUNT; i++) {
        m_game_state.enemies[i].render(program);
    }

    // Display "You Lost" message if the game is lost
    if (game_loss_b) {
        glm::vec3 player_position = m_game_state.player->get_position();
        glm::vec3 message_position = glm::vec3(player_position.x - 1.5f, player_position.y - 2.0f, 0.0f);
        Utility::draw_text(program, Utility::get_font_id(), "YOU LOST", 0.5f, 0.05f, message_position);
    }
}
