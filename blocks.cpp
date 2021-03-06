#include "blocks.h"
#include <iostream>
#include <SFML/Graphics.hpp>


void Block::setSize(int x, int y, int orX, int orY){
	Block::size = sf::Vector2f(x, y);
	sf::Sprite::scale((x / orX), (y / orY));
}

void Block::storeSize(int x, int y){
	Block::size = sf::Vector2f(x, y);
}

sf::Vector2f Block::getSize(){
	return Block::size;
}

bool Block::colliding(Block &player){
	sf::Vector2f blockPos = Block::getPosition();
	sf::Vector2f playerPos = player.getPosition();

	float xdiff = (Block::getSize().x / 2) + (player.getSize().x / 2);
	float ydiff = (Block::getSize().y / 2) + (player.getSize().y / 2);

	return playerPos.x > blockPos.x - xdiff && playerPos.x < blockPos.x + xdiff &&
		   playerPos.y > blockPos.y - ydiff && playerPos.y < blockPos.y + ydiff;
}

bool Block::colliding(Block &player, int margin){
	sf::Vector2f blockPos = Block::getPosition();
	sf::Vector2f playerPos = player.getPosition();

	float xdiff = (Block::getSize().x / 2) + (player.getSize().x / 2) + margin;
	float ydiff = (Block::getSize().y / 2) + (player.getSize().y / 2) + margin;

	return playerPos.x > blockPos.x - xdiff && playerPos.x < blockPos.x + xdiff &&
		   playerPos.y > blockPos.y - ydiff && playerPos.y < blockPos.y + ydiff;
}

/// moving blocks

sf::Vector2f MovingBlock::getSpeed(){
	return MovingBlock::speed;
}

void MovingBlock::defMove(){
	MovingBlock::move(MovingBlock::speed);
}

void MovingBlock::setSpeed(sf::Vector2f sp){
	MovingBlock::speed = sp;
}

void MovingBlock::setSpeed(float sp){
	MovingBlock::mvSpeed = sp;
}

float MovingBlock::getMvSpeed() {
	return MovingBlock::mvSpeed;
}

/// teleport blocks

bool TpBlock::linkBlocks(Block &toLink) {
	if(!linkedBlock) {
		TpBlock::linkedBlock = &toLink;
		return true;
	}
	return false;
}

void TpBlock::unlinkBlocks() {
	TpBlock::linkedBlock = nullptr;
}

bool TpBlock::teleport(Block &toTeleport) {
	if(linkedBlock) {
		toTeleport.setPosition(TpBlock::linkedBlock->getPosition());
		return true;
	}
	return false;
}

/// Entitys

void Entity::setOrigin(float orX, float orY){
	Entity::hitbox.setOrigin(orX, orY);
	Entity::main.setOrigin(orX, orY);
}

void Entity::storeSize(float x, float y){
	Entity::hitbox.storeSize(x, y);
	Entity::main.storeSize(x, y);
}

void Entity::setSpeed(float speed){
	Entity::speed = speed;
}

void Entity::setPosition(int x, int y){
	Entity::main.setPosition(x, y);
	Entity::hitbox.setPosition(x, y);
}

float Entity::getMvSpeed(){
	return Entity::speed;
}

void Entity::move(sf::Vector2f mv){
	Entity::main.move(mv);
	Entity::hitbox.move(mv);
}

sf::Vector2f Entity::getPosition(){
	return Entity::hitbox.getPosition();
}