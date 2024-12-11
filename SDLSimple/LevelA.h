#ifndef LEVELA_H
#define LEVELA_H

#include "Scene.h"
#include "ShaderProgram.h"
#include "Entity.h"

class LevelA : public Scene {
public:
    LevelA(int& lives) : lives(lives) {}
    ~LevelA();

    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
    
    const int ENEMY_COUNT = 18;
    float spawn_timer = 0.0f;

private:
    // Player-specific
    glm::vec3 initial_player_position;
    int lives;

    // Obstacle management
    static const int OBSTACLE_COUNT = 3;
    Entity* obstacles;
    int active_obstacle_index;
    float obstacle_timer;
    float obstacle_switch_interval;

    void position_obstacle_in_front();   
};

#endif
