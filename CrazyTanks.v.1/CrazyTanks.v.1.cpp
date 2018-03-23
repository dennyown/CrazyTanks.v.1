// CrazyTanks.v.1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


#include "Game.h"
#include "Map.h"

#include <Windows.h>
#include <thread>
#include <mutex>

using namespace std;
void thread_one( Game& game, mutex& mtx );
void thread_two( Game& game, mutex& mtx );
void thread_three( Game& game, mutex& mtx );
int main()
{
	

	Map map = Map( Point( 4, 25 ), Point( 0, 50 ) );
	Game game = Game( map );
	game.start();

	mutex mtx;
	thread t1( thread_one, ref( game ), ref( mtx ) );
	thread t2( thread_two, ref( game ), ref( mtx ) );
	thread t3( thread_three, ref( game ), ref( mtx ) );
	
	thread_one( game, mtx );
	thread_two( game, mtx );
	thread_three( game, mtx );
	t1.join();
	t2.join();
	t3.detach();
	game.finish();
	Point( 25, 0 ).moveCursor();
	system( "pause" );
    return 0;
}
void thread_one( Game& game, mutex& mtx ) {
	
	while ( game.goon )
	{
		mtx.lock();
		game.control_player_tank();
		mtx.unlock();
	}
	
}
void thread_two( Game& game, mutex& mtx ) {
	
	while ( game.goon )
	{
		mtx.lock();
		game.control_enemy_tank();
		
		mtx.unlock();
		Sleep( 300 );
	}
	
}
void thread_three( Game& game, mutex& mtx ) {
	
	while ( game.goon )
	{
		mtx.lock();

		game.control_fly_bullet();
		
		mtx.unlock();
		Sleep( 50 );
	}
	
}

