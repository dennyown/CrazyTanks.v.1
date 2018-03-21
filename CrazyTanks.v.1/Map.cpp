#include "stdafx.h"
#include "Point.h"
#include "Player.h"
#include "Bullet.h"
#include "Tank.h"
#include "Map.h"

#include <vector>
#include <list>
#include <time.h>

Map::Map( Point height, Point width ) : height( height ), width( width )
{
	position_gold = Point( height.X - 2, width.X / 2 );
	
	player = Player( Point( height.X - 2, width.X / 2 - 3 ), '@', 3 );	
}

Map::~Map()
{
}
 void Map::draw()
{
	 //draw border
	 for ( int i = height.Y; i < height.X; i++ )
	 {
		 for ( int k = width.Y; k < width.X; k++ )
		 {
			 if ( i == height.Y || i == height.X - 1 )
			 {
				 Point( i, k ).setChar( border );
			 }
			 else
				 if ( k == width.Y && i != height.Y || k == width.X - 1 && i != height.X - 1 )
				 {
					 Point( i, k ).setChar( border );
				 }
				 else
				 {
					 Point( i, k ).setChar( ' ' );
				 }
		 }
	 }
	 //draw castle and gold
	 Point castle;
	 position_gold.setChar( gold );
	 //turn to right
	 castle = Point( position_gold.Y, position_gold.X + 1 );
	 castle.setChar( '#' );
	 walls.push_back( Wall( castle, '#', 3 ) );
	 //turn to left
	 castle = Point( position_gold.Y, position_gold.X - 1 );
	 castle.setChar( '#' );
	 walls.push_back( Wall( castle, '#', 3 ) );
	 //turn to up
	 castle = Point( position_gold.Y - 1, position_gold.X );
	 castle.setChar( '#' );
	 walls.push_back( Wall( castle, '#', 3 ) );
	 //turn to up-rigth
	 castle = Point( position_gold.Y - 1, position_gold.X + 1 );
	 castle.setChar( '#' );
	 walls.push_back( Wall( castle, '#', 3 ) );
	 //turn to up-left
	 castle = Point( position_gold.Y - 1, position_gold.X - 1 );
	 castle.setChar( '#' );
	 walls.push_back( Wall( castle, '#', 3 ) );
	 //draw tank of player
	 player.position.setChar( player.sign );
	 //draw walls
	 for ( int i = 0; i < 5 * 10; i++ )
	 {
		 Point points;
		 do
		 {
			 points.X = rand() % ( width.X - 1 );
			 points.Y = rand() % ( height.X - 1 );

		 } while ( points.X <= width.Y || points.Y <= height.Y || points == position_gold || points == player.position );

		 auto wall = Wall( points, '#', 3 );
		 wall.position.setChar( wall.sign );
		 walls.push_back( wall );
		 
		 int lengthWall = rand() % 5;
		 for ( int k = 0; k < lengthWall; k++ )
		 {
			 int direction = rand() % 3, point; Point temp; bool has = false;
			 switch ( direction )
			 {
			 case 0:
				 point = points.Y - 1; temp = Point( points.Y - 1, points.X );
				 if ( point <= height.Y || temp == player.position || temp == position_gold ) {
					 --k;
					 continue;
				 }
				 else {
					 points.Y = point;
				 }
				 break;
			 case 1:
				 point = points.X - 1; temp = Point( points.Y, points.X - 1 );
				 if ( point <= width.Y || temp == player.position || temp == position_gold ) {
					 --k;
					 continue;
				 }
				 else {
					 points.X = point;
				 }
				 break;
			 case 2:
				 point = points.X + 1; temp = Point( points.Y, points.X + 1 );
				 if ( point >= height.X || temp == player.position || temp == position_gold ) {
					 --k;
					 continue;
				 }
				 else {
					 points.X = point;
				 }
				 break;
			 case 3:
				 point = points.Y + 1; temp = Point( points.Y + 1, points.X );
				 if ( points.Y >= width.X || temp == player.position || temp == position_gold ) {
					 --k;
					 continue;
				 }
				 else {
					 points.Y = point;
				 }
				 break;
			 }

			 for ( auto wall : walls )
			 {
				 if ( wall.position == points )
				 {
					 has = true;
					 break;
				 }
			 }
			 if ( !has )
			 {
				 auto wall = Wall( points, '#', 3 );
				 wall.position.setChar( wall.sign );
				 walls.push_back( wall );
			 }
		 }
	 }
	 
}
 void Map::update()
{
}