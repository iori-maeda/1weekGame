#include "BaseEnemy.h"

void BaseEnemy::StateUpdate()
{
	switch (mCurrentState)
	{
	case BaseEnemy::State::Idol:
		break;
	case BaseEnemy::State::Move:
		break;
	case BaseEnemy::State::Attack:
		break;
	case BaseEnemy::State::Dead:
		break;
	case BaseEnemy::State::Spawn:
		break;
	default:
		break;
	}
}

void BaseEnemy::Idol()
{

}

void BaseEnemy::Move()
{

}

void BaseEnemy::Attack()
{

}

void BaseEnemy::Dead()
{
}

void BaseEnemy::Spawn()
{
}