//============================================================================
// Name        : cookie-crush.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Cookie  Crush...
//============================================================================
#define COOKIE_CRUSH_CPP
#define COOKIE_CRUSH_CPP

//#include <GL/gl.h>
//#include <GL/glut.h>
#include <iostream>
#include<string>
#include<cmath>
#include<fstream>
#include "util.h"
//#include<windows.h>
//#include<MMSystem.h>
using namespace std;
#define MAX(A,B) ((A) > (B) ? (A):(B)) // defining single line functions....
#define MIN(A,B) ((A) < (B) ? (A):(B))
#define ABS(A) ((A) < (0) ? -(A):(A))
#define FPS 10
int b=1;
#define KEY_ESC 27 // A
#define KEY_SPC 32 
#define KEY_c   99   //
#define KEY_s   115   // for starting game

// 20,30,30
int k=1;
const int bradius = 30; // Cookie radius in pixels...

int width = 1050, height = 740; // i have set my window size to be 800 x 600
int dball = 0; // difference between cookies center of 0 pixels
int byoffset = bradius + dball; // 2 * bradius + dball; // board yoffset
float dt = 0, lastframe = 0;
float score = 0;
//float highestscore=0,&Highscore;
int setcolor, psetcolor;

enum GameState { // Use to check different states of game...
	Ready, Shot, Over, RemoveCluster
};
GameState gamestate = Over;

const int ncookies = 6;
 enum Cookies {     //changing
	CK_BISCUIT, CK_BURGER, CK_CROISSONT, CK_CUPCAKE, CK_DONUT, CK_STAR
};
	Cookies RGcookies[10][15];      // canvas sized approx matrix for random cookies
	Cookies var;        
	Cookies sw1;			//variables for swapping cookies
	Cookies sw2; 
GLuint texture[ncookies];
GLuint tid[ncookies];   
string tnames[] = { "biscuit.png", "burger.png", "croissont.png", "cupcake.png",
		"donut.png", "star.png" };
GLuint mtid[ncookies];
int cwidth = 60, cheight = 60; // 60x60 pixels cookies width & height...


void RegisterTextures()
/*Function is used to load the textures from the files and display*/
// Please do not change it...
{
	// allocate a texture name
	glGenTextures(ncookies, tid);

	vector<unsigned char> data;
	ifstream ifile("image-data.bin", ios::binary | ios::in);
	if (!ifile) {
		cout << " Couldn't Read the Image Data file ";
		exit(-1);
	}
	// now load each cookies data...
	int length;
	ifile.read((char*) &length, sizeof(int));
	data.resize(length, 0);
	for (int i = 0; i < ncookies; ++i) {

		// Read current cookie

		ifile.read((char*) &data[0], sizeof(char) * length);

		mtid[i] = tid[i];
		// select our current texture
		glBindTexture( GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
				wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
				wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps( GL_TEXTURE_2D, 3, cwidth, cheight, GL_RGB,
		GL_UNSIGNED_BYTE, &data[0]);
	}
	ifile.close();
void InitRandomizer();
}
void DrawCookie(const Cookies &cname, int sx, int sy, int cwidth = 60,
		int cheight = 60)
		/*Draws a specfic cookie at given position coordinate
		 * sx = position of x-axis from left-bottom
		 * sy = position of y-axis from left-bottom
		 * cwidth= width of displayed cookie in pixels
		 * cheight= height of displayed cookiei pixels.
		 * */
		{
	float fwidth = (float) cwidth / width * 2, fheight = (float) cheight
			/ height * 2;
	float fx = (float) sx / width * 2 - 1, fy = (float) sy / height * 2 - 1;

	glPushMatrix();
	glEnable( GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, mtid[cname]);
	glTranslatef(0, 0, 0);
//	glRotatef(-M_PI / 2, 0, 0, 1);
	glBegin( GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();

	glColor4f(1, 1, 1, 1);

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}

void Cheat(){
	for(int i=0,h=0;i<10;i++,h=h+70)
	{
		for(int j=0,w=0;j<15;j++,w+=70)
		{
			if((RGcookies[i][j]==RGcookies[i+1][i+1])==RGcookies[i+2][i+2]){    //function for making combinations 									// and crushing them...........
				RGcookies[i][j]=Cookies(GetRandInRange(0,6));
				DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);

	
	
									}
	
				}
	
					} 
	} 


bool Check_rows(){       //checking consistent same cookies with count(counter) in rows and crushing them and increasing score
		int ans=0;
		for(int i=0,h=0;i<10;i+=1,h=h+70)
		{
	
			for(int j=0,w=0,count;j<15;j+=1,w+=70)
			{
				count=0;
				if(RGcookies[i][j]==RGcookies[i][j+1]){
	
					count+=1;
				if ((j+1)==14 || j+1==15 || j+1==16 )
					count=0;
										
	
	
				if(RGcookies[i][j+1]==RGcookies[i][j+2]){
					count+=1;
				if (RGcookies[i][j+2]==RGcookies[i][j+3]){
					count+=1;
					}
				if(RGcookies[i][j+3]==RGcookies[i][j+4]){
					count+=1;
					}
				//if(RGcookies[i][j+4]==RGcookies[i][j+5]){
					//count+=1;
					//}
				}
				else
					count=0;
	
				if(count>=2){
					ans+=2;
					if ((j+1)==14 ||(j+1)==15 || (j+1)==16 )
					count =0;
					if(count>=2){
					RGcookies[i][j]=Cookies(-1);
					DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);
					}
					if (j+1==15 || j+1==16 )
					count =0;
					else
	
	
					{j+=1;
					w+=70;}
					if(count>=2){
					RGcookies[i][j]=Cookies(-1);
					DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);
					}
					if ((j+1)==15 || j+1==16 )
					count =0;
					else{
					j+=1;
					w+=70;
						}
					if(count>=2){
					RGcookies[i][j]=Cookies(-1);
					DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);
					}
					if(count==3 && (j+1)<15){
						j+=1;
						w+=70;
						RGcookies[i][j]=Cookies(-1);
						DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);
						DrawString(width/2+200 , height - 40, width, height,
			"YUMMY :)" , colors[WHITE]);
			sleep(0.8);
							}
					if(count==4 &&(j+1)<15){
						j+=1;
						w+=70;
						RGcookies[i][j]=Cookies(-1);
						DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);
						DrawString(width/2+200 , height - 40, width, height,
			" DELICIOUS ;)" , colors[WHITE]);
	
					
					}
	
					if (gamestate != Over){
						score+=(count+1);
						}
					count=0;
									}
					else
						count=0;
	
	           				 }
	            
	
					}
	
	
	
						} 
			if (ans>=2)
						return True;
					else
						return False;
	
											}
//function for checking columns and crushing combinations
	
bool Check_columns(){
	int ans=0;
	for(int j=0,w=0;j<15;j+=1,w+=70){
	
		for(int i=0,h=0,count;i<10;i++,h=h+70){
			count=0;
			if(RGcookies[i][j]==RGcookies[i+1][j]){
				count+=1;
				if((i+1)==9 || (i+1)==10)
					count=0;
				if(RGcookies[i+1][j]==RGcookies[i+2][j]){
					count+=1;}
		
				if(RGcookies[i+2][j]==RGcookies[i+3][j]){
					count+=1;}
				if(RGcookies[i+3][j]==RGcookies[i+4][j]){
					count+=1;}
								}
			else
				count=0;
			//if(RGcookies[i+2][j]=RGcookies[i+3][j]);
	
			if(count>=2 )     {
				ans=2;
			if((i+1)==9 || (i+1)==10)
				count=0;	
			if(count>=2 ){
			RGcookies[i][j]=Cookies(-1);
			DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);
			}

	
			
			if((i+1)==9 || (i+1)==10)
				count=0;
			else{i+=1;
				h+=70;}
			
					                              //checking consistent 3 same cookies with count columns
	
			if(count>=2 ){
			RGcookies[i][j]=Cookies(-1);
			DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);
			}
			
			
			if((i+1)==9 || (i+1)==10)
				count=0;
			else
				{i+=1;
				h+=70;}
			
			
			if(count>=2 ){
			RGcookies[i][j]=Cookies(-1);
			DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);
			}
			if(count==3 && (i+1)<10 ){
				
				
				i+=1;
				h+=70;
				RGcookies[i][j]=Cookies(-1);
				DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);
				DrawString(width/2+200 , height - 40, width, height,
			"YUMMY :)" , colors[WHITE]);
			sleep(0.8);
					}
			if(count==4 && (i+1)<10 ){
				
				
				i+=1;
				h+=70;
				RGcookies[i][j]=Cookies(-1);
				DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);
				DrawString(width/2+200 , height - 40, width, height,
			" DELICIOUS ;)" , colors[WHITE]);
				sleep(0.8);
					}
				
	

			
			if (gamestate != Over){
				score+=(count+1);
				}
			count=0;
	
			}
		else
		count=0;
							//if first
								

						
						//2nd for
					}
						//first for braces
	
		}
		if(ans>=2)
			return True;
		else
			return False;
	//return True;
	
	}
	bool CHeck_columns(){
		int ans=0;
		for(int j=0,w=0;j<15;j+=1,w+=70){
	
			for(int i=0,h=0,count;i<10;i++,h=h+70){
				count=0;
				if(RGcookies[i][j]==RGcookies[i+1][j]){
					count+=1;
					if((i+1)==9 || (i+1)==10)
					count=0;
					if(RGcookies[i+1][j]==RGcookies[i+2][j])	{
					count+=1;
		
					if(RGcookies[i+2][j]==RGcookies[i+3][j]){
					count+=1;}
											}
											}
				else
				count=0;
	
				if(count>=2)
					ans=2;
						}
							}
					if(ans==2)
						return True;
					else
						return False;
					}
	
	
	
	
	
	
	bool CHeck_rows(){
	int ans=0;
	for(int i=0,h=0;i<10;i+=1,h=h+70)
	{
	
		for(int j=0,w=0,count;j<15;j+=1,w+=70)
		{
			count=0;
			if(RGcookies[i][j]==RGcookies[i][j+1]){
	
				count+=1;
				if ((j+1)==14 || j+1==15 || j+1==16 )
					count =0;
				
	

	                       //checking consistent 3 same cookies with count in rows
	
	
				if(RGcookies[i][j+1]==RGcookies[i][j+2]){
					count+=1;
				
				}
				else
				count=0;
	
				if(count>=2)
					ans=2;
					}
						}
						}
					if(ans==2)
						return True;
					else
						return False;
						}
//prototype for timer
void Timer(int );

void PrintableKeys(unsigned char , int , int );
	

float Distance(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
void Pixels2Cell(int px, int py, int & cx, int &cy) {
	

}
void Cell2Pixels(int cx, int cy, int & px, int &py)
// converts the cell coordinates to pixel coordinates...

	{

}


int cr=0.1,cg=0.1,cb=0.1;
void DisplayFunction() {
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim red and 1 means pure red and so on.
//#if 0
	glClearColor(0.0+cr/*Red Component*/, 0.0+cg/*Green Component*/,
			0.+cb/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors

// #----------------- Write your code here ----------------------------#
	//write your drawing commands here or call your drawing functions...
	
	

	// draw cookies..;

	float Time=(125-lastframe);     //time setting to 120 seconds
	
	if (Time<=0){
		Time = 0;   //since time is in float
		}
	
	
	
if(Time>121){
	DrawString(350 , height/2, width, height,
			" WELCOME TO KHIZAR's COOKIE CRUSH " , colors[WHITE]);
			
	//DrawCookie(CK_BURGER, 20,h, cwidth, cheight);
	DrawCookie(CK_CROISSONT, 70, height -240, cwidth, cheight);
	DrawCookie(CK_CUPCAKE, 70, height -310, cwidth, cheight);
	DrawCookie(CK_BISCUIT, 70, height -380, cwidth, cheight);
	DrawCookie(CK_BURGER, 70, height -450, cwidth, cheight);
	DrawCookie(CK_DONUT, 70, height -520, cwidth, cheight);
	DrawCookie(CK_STAR, 70, height -590, cwidth, cheight);
	//
	DrawCookie(CK_CROISSONT, 900, height -240-2, cwidth, cheight);
	DrawCookie(CK_CUPCAKE, 900, height -310-2, cwidth, cheight);
	DrawCookie(CK_BISCUIT,900, height -380-2, cwidth, cheight);
	DrawCookie(CK_BURGER, 900, height -450-2, cwidth, cheight);
	DrawCookie(CK_DONUT, 900, height -520-2, cwidth, cheight);
	DrawCookie(CK_STAR, 900, height -590-2, cwidth, cheight);
	
	DrawCookie(CK_CROISSONT, 645, height -180, cwidth, cheight);
	DrawCookie(CK_CUPCAKE, 295, height-180 , cwidth, cheight);
	DrawCookie(CK_BISCUIT,365, height -180, cwidth, cheight);
	DrawCookie(CK_BURGER, 435, height -180, cwidth, cheight);
	DrawCookie(CK_DONUT, 505, height -180, cwidth, cheight);
	DrawCookie(CK_STAR, 575, height -180, cwidth, cheight);
	
	DrawCookie(CK_CROISSONT, 645, height -660, cwidth, cheight);
	DrawCookie(CK_CUPCAKE, 295, height-660 , cwidth, cheight);
	DrawCookie(CK_BISCUIT,365, height -660, cwidth, cheight);
	DrawCookie(CK_BURGER, 435, height -660, cwidth, cheight);
	DrawCookie(CK_DONUT, 505, height -660, cwidth, cheight);
	DrawCookie(CK_STAR, 575, height -660, cwidth, cheight);
	
	
	

		}
	
	
if (Time<120 && Time!=0){
	
	for(int i=0,h=0;i<10;i++,h=h+70)
	{
		for(int j=0,w=0;j<15;j++,w+=70)        //Drawing random cookies which are created in array in main().....
		{
		DrawCookie(RGcookies[i][j], w,h, cwidth, cheight);
			}
	
				}
	
	
	
	Check_rows();
	Check_columns();      //using functions for checking rows and columns
	
	
	
	for(int j=0,w=0;j<15;j+=1,w+=70){        //USing bubble sorting for carrying empty cookies on top...
	
		for(int i=0,h=0;i<10;i++,h=h+70){
			for(int i=0,h=0;i<10;i++,h=h+70){
				if(RGcookies[i][j]==Cookies(-1)){
					var=RGcookies[i][j];
					RGcookies[i][j]=RGcookies[i+1][j];
					RGcookies[i+1][j]=var;
	
						}
				}
			}
		}
	
	
	
	for(int j=0,w=0;j<15;j+=1,w+=70){          // again creating random cookies in empty cookies
	
		for(int i=0,h=0;i<10;i++,h=h+70){
			if(RGcookies[i][j]==Cookies(-1)){
				RGcookies[i][j]=Cookies(GetRandInRange(0,6));
							}
					}
	
				}
				
				

	//DrawCookie(CK_BURGER, w,h, cwidth, cheight);
	//DrawCookie(CK_CROISSONT, 70, height / 2, cwidth, cheight);
	//DrawCookie(CK_CUPCAKE, 130, height / 2, cwidth, cheight);
	
	DrawString(width/2-20 , height - 40, width, height,
			"Time Left : " + Num2Str(Time), colors[WHITE]);
	DrawString(30 , height - 40, width, height,
			"Score " + Num2Str(score), colors[WHITE]);
		}
		//if(Check_rows && C)
		
		
		
if(Time==0){
	
	
	DrawString(435 , height/2, width, height,
			"GAME OVER " , colors[WHITE]);
	DrawString(465 , height/2-80, width, height,
			"YOUR SCORE " + Num2Str(score), colors[WHITE]);
	
	//DrawCookie(CK_BURGER, 20,h, cwidth, cheight);
	DrawCookie(CK_CROISSONT, 70, height -240, cwidth, cheight);
	DrawCookie(CK_CUPCAKE, 70, height -310, cwidth, cheight);
	DrawCookie(CK_BISCUIT, 70, height -380, cwidth, cheight);
	DrawCookie(CK_BURGER, 70, height -450, cwidth, cheight);
	DrawCookie(CK_DONUT, 70, height -520, cwidth, cheight);
	DrawCookie(CK_STAR, 70, height -590, cwidth, cheight);
	
	DrawCookie(CK_CROISSONT, 900, height -240-2, cwidth, cheight);
	DrawCookie(CK_CUPCAKE, 900, height -310-2, cwidth, cheight);
	DrawCookie(CK_BISCUIT,900, height -380-2, cwidth, cheight);
	DrawCookie(CK_BURGER, 900, height -450-2, cwidth, cheight);
	DrawCookie(CK_DONUT, 900, height -520-2, cwidth, cheight);
	DrawCookie(CK_STAR, 900, height -590-2, cwidth, cheight);
	
	DrawCookie(CK_CROISSONT, 645, height -180, cwidth, cheight);
	DrawCookie(CK_CUPCAKE, 295, height-180 , cwidth, cheight);
	DrawCookie(CK_BISCUIT,365, height -180, cwidth, cheight);
	DrawCookie(CK_BURGER, 435, height -180, cwidth, cheight);
	DrawCookie(CK_DONUT, 505, height -180, cwidth, cheight);
	DrawCookie(CK_STAR, 575, height -180, cwidth, cheight);
	
	DrawCookie(CK_CROISSONT, 645, height -660, cwidth, cheight);
	DrawCookie(CK_CUPCAKE, 295, height-660 , cwidth, cheight);
	DrawCookie(CK_BISCUIT,365, height -660, cwidth, cheight);
	DrawCookie(CK_BURGER, 435, height -660, cwidth, cheight);
	DrawCookie(CK_DONUT, 505, height -660, cwidth, cheight);
	DrawCookie(CK_STAR, 575, height -660, cwidth, cheight);
	
		
	DrawString(830 , height/2-320, width, height,
			"BReAtHe CoDinG (: " , colors[CRIMSON]);		
	gamestate=Over;
	
	
	
	
	}
		
	
	
	
	

       // DrawString(30 , height +20 , width, height,
			//"Time" + Num2Str(lastframe), colors[WHITE]);
// #----------------- Write your code till here ----------------------------#
	// do not modify below this
	glutSwapBuffers(); // do not modify this line..

}
/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
/*void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
}*/

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
	} else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	/*
	 glutPostRedisplay();
	 */
}
/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */

void MouseMoved(int x, int y) {

	cout << "Current Mouse Coordinates X=" << x << " Y= " << height - y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
int row=0,col=0,roww,coll;
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{

		if (state == GLUT_DOWN && gamestate == Ready) {
			cout << "Left Mouse Button Pressed at Coordinates X=" << x << " Y= "
					<< height - y << endl;
			row=(height-y)/70;                                   //code for swapping...........
		if(row >15)        //row cannot be greater than 15
			return;
		cout<<"row is "<<row<<endl;
		col=x/70;
		cout<<"column is "<<col<<endl;
		
				

	}
		if (state == GLUT_UP && gamestate == Ready) {
			cout << "Left Mouse Button released at Coordinates X=" << x << " Y= "
						<< height - y << endl;  
		roww=(height-y)/70;
		if(row >15)
			return;
		cout<<"row is "<<roww<<endl;
		coll=x/70;
		cout<<"column is "<<coll<<endl;
		if(roww>(row+1) || roww<(row-1))   
			return;
		if(row!=roww && col!=coll)   //when after swapping neither of the coordinates of the cookie match.....
			return;
		
		if(coll>(col+1) || coll<(col-1))  //if after swapping is out of range means bouncing from one ....
			return;
		if( ((roww==row+1) && (coll==col)) || ((roww==row-1) && (coll==col)) || ((roww==row) && (coll==col-1)) || ((roww==row) && 				(coll==col+1))  ){
			sw1=RGcookies[roww][coll];
			RGcookies[roww][coll]=RGcookies[row][col];
			RGcookies[row][col]=sw1;
				}
				
		if((CHeck_rows()==False) && (CHeck_columns()==False)){
			sw1=RGcookies[row][col];
			RGcookies[row][col]=RGcookies[roww][coll];
			RGcookies[roww][coll]=sw1;
			
			
			}
			
	

		
		
		
		}
		}
		

	 else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{

	}
	glutPostRedisplay();
}
/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */

void PrintableKeys(unsigned char key, int x, int y) {
	if (key == KEY_ESC/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	if (key == KEY_SPC){    //using space for pause
		
		
		
	cout<<"Enter a character : ";
	cin.get();
	cout<<"continue\n";
	}
	if(key == KEY_c){       //using key c for cheating
	
		Cheat();
		}
	//if(key == KEY_s){
	//gamestate=Ready;
	//}
}

/*
 * This function is called after every 1000.0 milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {
	
	dt = (m - lastframe) / 1000.0;
	
	glutPostRedisplay();
	lastframe = m;

	// dt is time elapsed between two frames..

	// implement your functionality here
	
	if (lastframe>9){       // to make sure that score will be 0  in starting....
		gamestate = Ready;
		}
	
	
	
	glutTimerFunc(1000, Timer, m + 1);
}
//    prototype for random function.......................
long GetRandInRange(const long &rmin, const long &rmax);

/*
 * our gateway main function
 * */                           

int main(int argc, char*argv[]) {
	InitRandomizer(); // seed the random number generator...
	//Write your code here for filling the canvas with different Cookies. You can use the GetCookie function for getting the random shaped cookies
	//PlaySound(TEXT("over.wav"),NULL,SND_SYNC);
	//system("pause");
	
	
	for(int i=0;i<10;i++)
		{
		for(int j=0;j<15;j++){
				RGcookies[i][j]=Cookies(GetRandInRange(0,6));
					}
		}
	
	
	
	

	//checkers 
	//while(Check_rows && Check_columns != False){
	
	
	//}
	
				
	
	
	
	
	
	
	



	glutInit(&argc, argv); // initialize the graphics library...
	

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Khizar's Cookie Crush"); // set the title of our game window
	//SetCanvasSize(width, height); // set the number of pixels...

	// Load the textures from the file..;
	RegisterTextures();
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.



	glutDisplayFunc(DisplayFunction); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	glutMouseFunc(MouseClicked);
	

//// This function tells the library to call our Timer function after 1000.0 milliseconds...
	glutTimerFunc(1000, Timer, 0);
	
//// now handle the control to library and it will call our registered functions when
//// it deems necessary...

	glutMainLoop();
	
	

	return 1;
}
/*#endif  */
