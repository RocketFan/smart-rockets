#include "../../include/GameObjects/Rocket.h"

#include "../../include/Game.h"
#include "../../include/GameObjects/Ray.h"
#include "../../include/GameObjects/Target.h"
#include "../../include/GameObjects/GameObjectBuilder.h"
#include "../../include/GeneticAlgorithm/DNA.h"

Rocket::Rocket() : Rectangle() {
    this->collisionType = CollisionType::Dynamic;
    this->gameObjectType = GameObjectType::Rocket;

    setColor(sf::Color::Blue);
}

void Rocket::update() {
    if (!stop) {
        (*inputs)(0, 0) = dir.x;
        (*inputs)(0, 1) = dir.y;
        (*inputs)(0, 2) = dna->targetDir.x;
        (*inputs)(0, 3) = dna->targetDir.y;
        (*inputs)(0, 4) = dna->targetDist / 800;

        for(int i = 0; i < rays.size(); i++)
            (*inputs)(0, 5 + i) = rays[i]->getDistance();

        auto outputs = dna->predict(*inputs);

        vel = outputs[0] * 2.f;
        float diffAngle = (outputs[1] - 0.5) * 24;

//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//            diffAngle = -2;
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//            diffAngle = 2;

        float angle = diffAngle + getRotation();
        setRotation(angle);
        move(dir * vel + dir * 2.f);
        dir.rotate(diffAngle);

//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//            move(dir * vel);
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//            move(-1.f * dir * vel);

        for (const auto &ray : rays) {
            ray->setPosition(getPosition());
            ray->rotate(diffAngle);
            ray->update();
        }
    }
}

void Rocket::updateCollision(GameObject *collidedGameObj) {
    if (collidedGameObj->gameObjectType == GameObjectType::Asteroid ||
        collidedGameObj->gameObjectType == GameObjectType::Target)
        Rectangle::updateCollision(collidedGameObj);
}

void Rocket::updateOnCollision(GameObject *collidedGameObj) {
    if (hit) {
        setColor(sf::Color::Red);
        this->stop = true;

        if(collidedGameObj->gameObjectType == GameObjectType::Target)
            dna->hitTarget = true;
    }
}

void Rocket::render(sf::RenderTarget &target) {
//    for (const auto &ray : rays)
//        ray->render(target);

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = getPosition();
    line[0].color = sf::Color::Green;
    line[1].position = getPosition() + dna->targetDir * 20.f;
    line[1].color = sf::Color::Green;

    target.draw(getShape());
    target.draw(line);

    for (const auto &point : getPoints()) {
        float edgeRadius = 2;

        sf::CircleShape edge(edgeRadius);
        edge.setFillColor(sf::Color::Green);
        edge.setPosition(point.x - edgeRadius, point.y - edgeRadius);

        target.draw(edge);
    }
}

void Rocket::reset(Vector2f spawnPos) {
    this->stop = false;
    this->dir = Vector2f(0, -1);
    this->setRotation(0);

    createRays();
    setColor(sf::Color::Blue);
    setPosition(spawnPos);
}

void Rocket::setRays(int nRays, float fieldOfView) {
    this->fieldOfView = fieldOfView;
    this->rays = std::vector<std::shared_ptr<class Ray>>(nRays);

    createRays();
}

void Rocket::setDNA(DNA *dna) {
    this->dna = dna;

    this->inputs = std::make_shared<Matrix>(1, dna->nn->size[0]);
}

void Rocket::setTarget(class Target *target) {
    auto targetVec = (target->getPosition() - getPosition());
    float dist = targetVec.magnitude();

    this->dna->targetDist = dist;
    this->dna->targetDir = targetVec / dist;
}

void Rocket::createRays() {
    float diffAngle = fieldOfView / (rays.size() - 1);
    float currAngle = 0;

    for (int i = 0; i < rays.size(); i++) {
        auto ray = GameObjectBuilder<class Ray>(game)
                .setPosition(getPosition())
                .build();

        ray->rotate(currAngle - fieldOfView / 2);
        currAngle += diffAngle;

        this->rays[i] = ray;
    }
}

bool Rocket::getHitTarget() const {
    return dna->hitTarget;
}