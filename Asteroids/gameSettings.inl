const float angularVelocity = 2 * pi / (1); //1 rotation per second
const float linearAcceleration = 1; // (m/s^2)
const float maxLinearVelocity = 1.0f;
const float linearDamping = 0.8f;
const float asteroidHeading = 0.5;
//const float asteroidTravelHeading = 30 / 180.0f * pi; //30 degrees in radian fly direction
const float ufoHeading = 0;
const bool enableMomentum = false;
const float respawnTimer = 0.5;
const float invincibleAfterSpawnTimer = 1;

// game difficulty
const float gameSpeed = 1;
const float ufoShootInterval = 0.8f; //ufo shoots every 0.8s
const float asteroidSpawnInterval = 3; //spawns 1 asteroid every 3 second
const float ufoSpawnInterval = 5; //ufo respawns after 5 sec