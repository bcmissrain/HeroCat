#ifndef  __BASEDEFINE_H__
#define  __BASEDEFINE_H__

#define ACTION_TAG_RUN 10001
#define ACTION_TAG_JUMP_UP 10002
#define ACTION_TAG_JUMP_UP_2 10003
#define ACTION_TAG_JUMP_DOWN 10004

#define ELEMENT_HERO_TAG 1393650
#define ELEMENT_WEAPON_TAG 1393651
#define ELEMENT_FLOOR_TAG 1393652
#define ELEMENT_ENEMY_TAG 1393653

#define WEAPON_TEACH_DOOR_NAME "tec_door"
#define WEAPON_BISCUIT_NAME "biscuit"
#define WEAPON_BIANBIAN_NAME "bian"
#define WEAPON_SHIELD_NAME "shield"
#define WEAPON_LECTION_NAME "lection"
#define WEAPON_CANNON_NAME "cannon"

#define EVENT_TEACH_DOOR "event_teach_door"
#define EVENT_WEAPON_CREATE "event_weapon_create"
#define EVENT_BISCAKE_EAT "event_biscake_eat"
#define EVENT_MAKE_UP "event_make_up"

#define TAG_HERO 15829383718
//baseElement
enum class DropState
{
	Still,
	Up,
	Down,
};

//hero
enum class ActionState
{
	Stand = 0,
	Run,
	Stop,
	JumpUp,
	JumpUp2,
	JumpDown,
	JumpFinish,
};

enum class MoveState
{
	None = 0,
	MoveLeft,
	MoveRight
};

enum class Direction
{
	Left = 0,
	Right
};

enum class CollideState
{
	NoneSupport = 0,
	HaveSupport,
	HeadCollide
};

enum class ClickState
{
	None = 0,
	Begin,
	Still,
	End
};

enum class CollideOperate
{
	CollideLeft = 0,
	CollideRight,
	CollideUp,		//floor front
	CollideDown		//floor back
};

enum class AttackState
{
	NotAttack,
	Attacking
};

enum class HeroType
{
	CheetahCat,
	HuluCat,
	CaptainCat,
	TangShengCat,
	IronCat
};

//floor
enum class FloorType
{
	Normal,
	SuperJump,
	MoveHorizon,
	MoveUpDown
};

//weapon
enum class WeaponEventType
{
	None = 0,
	ThrowShield,
	ThrowBianbian,
	ThrowCannon,
	CreateLection
};

enum class WeaponType
{
	None = 0,
	Biscuit,
	Hand,
	Hulu,
	Shoot
};

enum class WeaponMoveWays
{
	Horizontal,
	Vertical
};

enum class WeaponDirection
{
	Right = 0,
	Left
};

//enemy
enum class EnemyType
{
	Small,
	Big,
	Fly,
	Boss
};

enum class EnemyDieType
{
	Transparent,
	ScaleDown
};

#endif